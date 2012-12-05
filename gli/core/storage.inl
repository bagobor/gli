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
	inline storage::desc::desc() :
		Layers(0),
		Faces(0),
		Levels(0),
		Dimensions(0),
		BlockSize(0),
		BlockDimensions(0)
	{}
	
	inline storage::desc::desc
	(
		size_type const & Layers,
		size_type const & Faces,
		size_type const & Levels,
		glm::uvec3 const & Dimensions,
		size_type const & BlockSize,
		glm::uvec3 const & BlockDimensions
	) :
		Layers(Layers),
		Faces(Faces),
		Levels(Levels),
		Dimensions(Dimensions),
		BlockSize(BlockSize),
		BlockDimensions(BlockDimensions)
	{}
	
	inline storage::storage()
	{}

	inline storage::storage
	(
		size_type const & Layers, 
		size_type const & Faces,
		size_type const & Levels,
		dimensions3_type const & Dimensions,
		size_type const & BlockSize,
		glm::uvec3 const & BlockDimensions
	) : 
		Desc(Layers, Faces, Levels, Dimensions, BlockSize, BlockDimensions),
		Data(this->layerSize() * Layers)
	{}

	inline storage::~storage()
	{}

	inline bool storage::empty() const
	{
		return this->Data.empty();
	}

	inline storage::size_type storage::layers() const
	{
		return this->Desc.Layers;
	}

	inline storage::size_type storage::faces() const
	{
		return this->Desc.Faces;
	}

	inline storage::size_type storage::levels() const
	{
		return this->Desc.Levels;
	}

	inline storage::size_type storage::blockSize() const
	{
		return this->Desc.BlockSize;
	}

	inline storage::dimensions3_type storage::blockDimensions() const
	{
		return this->Desc.BlockDimensions;
	}

	inline storage::dimensions3_type storage::dimensions
	(
		size_type const & Level
	) const
	{
		assert(Level < this->Desc.Levels);

		return glm::max(this->Desc.Dimensions >> storage::dimensions3_type(Level), storage::dimensions3_type(1));
	}

	inline storage::size_type storage::size() const
	{
		return this->Data.size();
	}

	inline glm::byte * storage::data()
	{
		assert(!this->empty());
		return &this->Data[0];
	}

	inline glm::byte const * const storage::data() const
	{
		assert(!this->empty());
		return &this->Data[0];
	}

	inline storage::size_type storage::levelSize
	(
		storage::size_type const & Level
	) const
	{
		assert(Level < this->Desc.Levels);

		return this->blockSize() * glm::compMul(glm::higherMultiple(
			this->dimensions(Level), 
			this->blockDimensions()) / this->blockDimensions()); 
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

	inline bool storage::isSubset(detail::view const & View) const
	{


		return false;
	}

	/*
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
*/
/*
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
*/
/*
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
*/
/*
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
*/
}//namespace detail
}//namespace gli
