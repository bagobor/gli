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
		Dimensions(0),
		BlockSize(0)
	{}
	
    inline storage::header::header
    (
        size_type const & Layers,
        flag_type const & Faces,
        size_type const & Levels,
		glm::uvec3 const & Dimensions,
		size_type const & BlockSize
    ) :
    	Layers(Layers),
    	Faces(Faces),
    	Levels(Levels),
    	Dimensions(Dimensions),
    	BlockSize(BlockSize)
    {}
	
	inline storage::storage()
	{}

	inline storage::storage
	(
		size_type const & Layers, 
    	flag_type const & Faces,
        size_type const & Levels,
        dimensions3_type const & Dimensions,
		size_type const & BlockSize
    ) : 
    	Header(Layers, Faces, Levels, Dimensions, BlockSize),
        Data(layerSize() * Layers * BlockSize)
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
    
    inline storage::dimensions3_type storage::dimensions
    (
        size_type const & Level
    ) const
    {
        return glm::max(this->Header.Dimensions >> storage::dimensions3_type(Level), storage::dimensions3_type(1));
    }
    
    inline storage::size_type storage::memorySize() const
    {
        return this->Data.size();
    }
    
    inline storage::data_type* storage::data()
    {
		assert(!this->empty());
        return &this->Data[0];
    }
    
    inline storage::data_type const * const storage::data() const
    {
		assert(!this->empty());
        return &this->Data[0];
    }
    
    inline storage::size_type storage::levelSize
    (
        storage::size_type const & Level
    ) const
    {
        return glm::compMul(this->dimensions(Level)); 
    }
    
    inline storage::size_type storage::faceSize() const
    {
        size_type FaceSize(0);
        
        // The size of a face is the sum of the size of each level.
        for(storage::size_type Level(0); Level < this->levels(); ++Level)
            FaceSize += this->levelSize(Level);
        
        return FaceSize;// * TexelSize;    
    }
    
    inline storage::size_type storage::layerSize() const
    {
        // The size of a layer is the sum of the size of each face.
        // All the faces have the same size.
        return this->faceSize() * this->faces();
    }
    
	inline storage::size_type storage::linearAddressing
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
            Storage.dimensions(0),
			Storage.blockSize());
        
        memcpy(
            SubStorage.data(), 
            Storage.data() + Storage.linearAddressing(Offset, 0, 0), 
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
            Storage.dimensions(0),
			Storage.blockSize());
        
        memcpy(
            SubStorage.data(), 
            Storage.data() + Storage.linearAddressing(0, storage::size_type(Face), 0), 
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
			Storage.dimensions(0),
            Storage.blockSize());
        
        memcpy(
            SubStorage.data(), 
            Storage.data() + Storage.linearAddressing(0, 0, Level), 
            Storage.levelSize(Level));
        
        return SubStorage;       
    }
    
	inline void copy_layers
	(
		storage const & SourceStorage, 
		storage::size_type const & SourceLayerOffset,
		storage::size_type const & SourceLayerSize,
		storage & DestinationStorage, 
		storage::size_type const & DestinationLayerOffset
	)
	{
		assert(DestinationStorage.blockSize() == SourceStorage.blockSize());
		assert(DestinationStorage.layers() <= SourceStorage.layers());
        assert(SourceStorage.layers() <= SourceLayerOffset + SourceLayerSize);
        assert(DestinationStorage.layers() <= DestinationLayerOffset + SourceLayerSize);

		std::size_t OffsetSrc = SourceStorage.linearAddressing(SourceLayerOffset, 0, 0);
		std::size_t OffsetDst = DestinationStorage.linearAddressing(DestinationLayerOffset, 0, 0);
    
		memcpy(
			DestinationStorage.data() + OffsetDst * DestinationStorage.blockSize(), 
			SourceStorage.data() + OffsetSrc * SourceStorage.blockSize(), 
			SourceStorage.layerSize() * SourceLayerSize * SourceStorage.blockSize());
	}

}//namespace detail
}//namespace gli
