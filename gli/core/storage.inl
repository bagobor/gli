///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2012 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2012-06-21
// Updated : 2012-06-21
// Licence : This source is under MIT License
// File    : gli/core/storage.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace gli{
namespace detail
{
	inline storage::header::header() :
		Layers(0),
		FaceFlags(0),
		FaceCount(0),
		Levels(0),
		Format(FORMAT_NULL),
		Dimensions(0)
	{}
	
    inline storage::header::header
    (
        size_type const & Layers,
        glm::uint const & FaceFlags,
        size_type const & FaceCount,
        size_type const & Levels,
        format_type const & Format,
        glm::uvec3 const & Dimensions
    ) :
    	Layers(Layers),
    	FaceFlags(FaceFlags),
    	FaceCount(FaceCount),
    	Levels(Levels),
    	Format(Format),
    	Dimensions(Dimensions)
    {}
	
	inline storage::storage()
	{}

	inline storage::storage
	(
		size_type const & Layers, 
    	glm::uint const & FaceFlags,
    	size_type const & Faces,
        size_type const & Levels,
        format_type const & Format,
        glm::uvec3 const & Dimensions
    ) : 
    	Header(Layers, FaceFlags, Faces, Levels, Format, Dimensions)
    {}

    inline bool storage::empty() const
    {
        return this->Data.empty();
    }
    
    inline storage::size_type storage::layers() const
    {
        return this->Header.Layers;
    }
    
    inline storage::size_type storage::faces() const
    {
        return this->Header.FaceCount;
    }

	inline glm::uint storage::faceFlags() const
	{
		return this->Header.FaceFlags;
	}
    
    inline storage::size_type storage::levels() const
    {
        return this->Header.Levels;
    }
    
    inline storage::format_type storage::format() const
    {
        return this->Header.Format;
    }
    
    inline storage::dimensions3_type storage::dimensions() const
    {
        return this->Header.Dimensions;
    }
    
    inline storage::size_type storage::memorySize() const
    {
        return this->Data.size();
    }
    
    inline storage::data_type* storage::data()
    {
        return &this->Data[0];
    }
    
    inline storage::data_type const * const storage::data() const
    {
        return &this->Data[0];
    }
    
    inline storage::size_type storage::levelSize
    (
        storage::size_type const & Level
    ) const
    {
        size_type const TexelSize = gli::detail::getFormatInfo(this->format()).BBP;
        
        dimensions3_type const Dimensions = glm::max(this->dimensions() >> glm::uint(Level), dimensions3_type(1));
        return Dimensions.x * Dimensions.y * Dimensions.z * TexelSize;
    }
    
    inline storage::size_type storage::faceSize() const
    {
        size_type FaceSize(0);
        size_type const TexelSize = gli::detail::getFormatInfo(this->format()).BBP;
        
        // The size of a face is the sum of the size of each level.
        for(storage::size_type Level(0); Level < this->levels(); ++Level)
        {
            dimensions3_type const Dimensions = glm::max(this->dimensions() >> glm::uint(Level), dimensions3_type(1));
            size_type const LevelSize = Dimensions.x * Dimensions.y * Dimensions.z * TexelSize;
            FaceSize += LevelSize;
        }
        
        return FaceSize * TexelSize;    
    }
    
    inline storage::size_type storage::layerSize() const
    {
        // The size of a layer is the sum of the size of each face.
        // All the faces have the same size.
        return faceSize() * this->faces();
    }
    
	inline storage::size_type storage::linearTextureAddressing
	(
		size_type const & LayerOffset, 
		size_type const & FaceOffset, 
		size_type const & LevelOffset
	) const
	{
        size_type BaseOffset = this->layerSize() * LayerOffset + this->faceSize() * FaceOffset; 
        
        for(size_type LevelIndex = 0; LevelIndex < LevelOffset; ++LevelIndex)
            BaseOffset += this->levelSize(LevelIndex);
        
        return BaseOffset;
	}

    inline storage extractLayers
    (
        storage const & Storage, 
        storage::size_type const & Offset, 
        storage::size_type const & Size
    )
    {
        assert(Storage.layers() > 1);
        assert(Storage.layers() >= Size);
        assert(Storage.faces() > 0);
        assert(Storage.levels() > 0);
        
        storage SubStorage(
            Size, 
			Storage.faceFlags(), 
			Storage.faces(), 
            Storage.levels(),
            Storage.format(),
            Storage.dimensions());
        
        memcpy(
            SubStorage.data(), 
            Storage.data() + Storage.linearTextureAddressing(Offset, 0, 0), 
            Storage.layerSize() * Size);
        
        return SubStorage;
    }
    
    inline storage extractFace
    (
        storage const & Storage, 
        face const & Face
    )
    {
        assert(Storage.faces() > 1);
        assert(Storage.levels() > 0);
        
        storage SubStorage(
            Storage.layers(),
			1, 
			Face, 
            Storage.levels(),
            Storage.format(),
            Storage.dimensions());
        
        memcpy(
            SubStorage.data(), 
            Storage.data() + Storage.linearTextureAddressing(0, storage::size_type(Face), 0), 
            Storage.faceSize());
        
        return SubStorage;        
    }
    
    inline storage extractLevel
    (
        storage const & Storage, 
        storage::size_type const & Level
    )
    {
        assert(Storage.layers() == 1);
        assert(Storage.faces() == 1);
        assert(Storage.levels() >= 1);
        
        storage SubStorage(
            1, // layer
			glm::uint(FACE_POSITIVEX),
            1, // face
            1, // level
            Storage.format(),
            Storage.dimensions());
        
        memcpy(
            SubStorage.data(), 
            Storage.data() + Storage.linearTextureAddressing(0, 0, Level), 
            Storage.levelSize(Level));
        
        return SubStorage;       
    }
    
}//namespace detail
}//namespace gli
