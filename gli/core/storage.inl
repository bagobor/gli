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
		Faces(0),
		Levels(0),
		BlockSize(0),
		Dimensions(0),
        BaseOffset(0)
	{}
	
    inline storage::header::header
    (
        size_type const & Layers,
        flag_type const & Faces,
        size_type const & Levels,
        size_type const & BlockSize,
        glm::uvec3 const & Dimensions,
        size_type const & BaseOffset
    ) :
    	Layers(Layers),
    	Faces(Faces),
    	Levels(Levels),
    	BlockSize(BlockSize),
    	Dimensions(Dimensions),
        BaseOffset(BaseOffset)
    {}
	
	inline storage::storage()
	{}

	inline storage::storage
	(
		size_type const & Layers, 
    	flag_type const & Faces,
        size_type const & Levels,
        size_type const & BlockSize,
        glm::uvec3 const & Dimensions
        //size_type const & BaseOffset
    ) : 
    	Header(Layers, Faces, Levels, BlockSize, Dimensions, 0),
        Data(this->layerSize() * Layers * BlockSize)
    {}

	inline storage::~storage()
	{}

    inline bool storage::empty() const
    {
        return this->Data.empty();
    }
    
    inline storage::size_type storage::layers() const
    {
        return this->Header.Layers;
    }
    
    inline storage::flag_type storage::faces() const
    {
        return this->Header.Faces;
    }
    
    inline storage::size_type storage::levels() const
    {
        return this->Header.Levels;
    }
    
    inline storage::size_type storage::blockSize() const
    {
        return this->Header.BlockSize;
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
        //size_type const TexelSize = this->blockSize();//gli::detail::getFormatInfo(this->layout()).BBP;
        
        dimensions3_type const Dimensions = glm::max(this->dimensions() >> glm::uint(Level), dimensions3_type(1));
        return Dimensions.x * Dimensions.y * Dimensions.z;// * TexelSize;
    }
    
    inline storage::size_type storage::faceSize() const
    {
        size_type FaceSize(0);
        //size_type const TexelSize = this->blockSize();//gli::detail::getFormatInfo(this->layout()).BBP;
        
        // The size of a face is the sum of the size of each level.
        for(storage::size_type Level(0); Level < this->levels(); ++Level)
        {
            dimensions3_type const Dimensions = glm::max(this->dimensions() >> glm::uint(Level), dimensions3_type(1));
            size_type const LevelSize = Dimensions.x * Dimensions.y * Dimensions.z;// * TexelSize;
            FaceSize += LevelSize;
        }
        
        return FaceSize;// * TexelSize;    
    }
    
    inline storage::size_type storage::layerSize() const
    {
        // The size of a layer is the sum of the size of each face.
        // All the faces have the same size.
        return this->faceSize() * this->faces();
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
        
        return BaseOffset;// * this->blockSize();
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
			Storage.faces(), 
            Storage.levels(),
            Storage.blockSize(),
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
			Face, 
            Storage.levels(),
            Storage.blockSize(),
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
			glm::uint(FACE_DEFAULT),
            1, // level
            Storage.blockSize(),
            Storage.dimensions());
        
        memcpy(
            SubStorage.data(), 
            Storage.data() + Storage.linearTextureAddressing(0, 0, Level), 
            Storage.levelSize(Level));
        
        return SubStorage;       
    }
    
}//namespace detail
}//namespace gli
