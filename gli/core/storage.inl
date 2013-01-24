///////////////////////////////////////////////////////////////////////////////////
/// OpenGL Image (gli.g-truc.net)
///
/// Copyright (c) 2008 - 2013 G-Truc Creation (www.g-truc.net)
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
/// 
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///
/// @ref core
/// @file gli/core/storage.inl
/// @date 2012-06-21 / 2013-01-12
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

namespace gli{
namespace detail
{
	struct format_desc
	{
		std::size_t BlockSize;
		glm::uvec3 BlockDimensions;
		std::size_t BBP;
		std::size_t Component;
		bool Compressed;
	};

	inline format_desc const getFormatInfo(format const & Format)
	{
		format_desc const Desc[FORMAT_MAX] =
		{
			{  0,  glm::uvec3(0), 0,  0, false},	//FORMAT_NULL

			// Unsigned integer formats
			{  1, glm::uvec3(1),  8,  1, false},	//R8U,
			{  2, glm::uvec3(1), 16,  2, false},	//RG8U,
			{  3, glm::uvec3(1), 24,  3, false},	//RGB8U,
			{  4, glm::uvec3(1), 32,  4, false},	//RGBA8U,

			{  2, glm::uvec3(1), 16,  1, false},	//R16U,
			{  4, glm::uvec3(1), 32,  2, false},	//RG16U,
			{  6, glm::uvec3(1), 48,  3, false},	//RGB16U,
			{  8, glm::uvec3(1), 64,  4, false},	//RGBA16U,

			{  4, glm::uvec3(1),  32,  1, false},	//R32U,
			{  8, glm::uvec3(1),  64,  2, false},	//RG32U,
			{ 12, glm::uvec3(1),  96,  3, false},	//RGB32U,
			{ 16, glm::uvec3(1), 128,  4, false},	//RGBA32U,

			//// Signed integer formats
			{  1, glm::uvec3(1),  32,  1, false},	//R8I,
			{  2, glm::uvec3(1),  64,  2, false},	//RG8I,
			{  3, glm::uvec3(1),  96,  3, false},	//RGB8I,
			{  4, glm::uvec3(1), 128,  4, false},	//RGBA8I,

			{  2, glm::uvec3(1), 16,  1, false},	//R16I,
			{  4, glm::uvec3(1), 32,  2, false},	//RG16I,
			{  6, glm::uvec3(1), 48,  3, false},	//RGB16I,
			{  8, glm::uvec3(1), 64,  4, false},	//RGBA16I,

			{  4, glm::uvec3(1),  32,  1, false},	//R32I,
			{  8, glm::uvec3(1),  64,  2, false},	//RG32I,
			{ 12, glm::uvec3(1),  96,  3, false},	//RGB32I,
			{ 16, glm::uvec3(1), 128,  4, false},	//RGBA32I,

			//// Floating formats
			{  2, glm::uvec3(1), 16,  1, false},	//R16F,
			{  4, glm::uvec3(1), 32,  2, false},	//RG16F,
			{  6, glm::uvec3(1), 48,  3, false},	//RGB16F,
			{  8, glm::uvec3(1), 64,  4, false},	//RGBA16F,

			{  4, glm::uvec3(1),  32,  1, false},	//R32F,
			{  8, glm::uvec3(1),  64,  2, false},	//RG32F,
			{ 12, glm::uvec3(1),  96,  3, false},	//RGB32F,
			{ 16, glm::uvec3(1), 128,  4, false},	//RGBA32F,

			//// Packed formats
			{  4, glm::uvec3(1), 32,  3, false},	//RGBE8,
			{  4, glm::uvec3(1), 32,  3, false},	//RGB9E5,
			{  4, glm::uvec3(1), 32,  3, false},	//RG11B10F,
			{  2, glm::uvec3(1), 16,  3, false},	//R5G6B5,
			{  2, glm::uvec3(1), 16,  4, false},	//RGBA4,
			{  4, glm::uvec3(1), 32,  3, false},	//RGB10A2,

			//// Depth formats
			{  2, glm::uvec3(1), 16,  1, false},	//D16,
			{  4, glm::uvec3(1), 32,  1, false},	//D24X8,
			{  4, glm::uvec3(1), 32,  2, false},	//D24S8,
			{  4, glm::uvec3(1), 32,  1, false},	//D32F,
			{  8, glm::uvec3(1), 64,  2, false},	//D32FS8X24,

			//// Compressed formats
			{  8, glm::uvec3(4, 4, 1), 4,  4, true},	//DXT1,
			{ 16, glm::uvec3(4, 4, 1), 8,  4, true},	//DXT3,
			{ 16, glm::uvec3(4, 4, 1), 8,  4, true},	//DXT5,
			{  8, glm::uvec3(4, 4, 1), 4,  1, true},	//ATI1N_UNORM,
			{  8, glm::uvec3(4, 4, 1), 4,  1, true},	//ATI1N_SNORM,
			{ 16, glm::uvec3(4, 4, 1), 8,  2, true},	//ATI2N_UNORM,
			{ 16, glm::uvec3(4, 4, 1), 8,  2, true},	//ATI2N_SNORM,
			{ 16, glm::uvec3(4, 4, 1), 8,  3, true},	//BP_UF16,
			{ 16, glm::uvec3(4, 4, 1), 8,  3, true},	//BP_SF16,
			{ 16, glm::uvec3(4, 4, 1), 8,  4, true},	//BP,
		};

		return Desc[Format];
	};
}//namespace detail

	inline storage::desc::desc() :
		Layers(0),
		Faces(0),
		Levels(0),
		Format(FORMAT_NULL),
		Dimensions(0),
		BlockSize(0),
		BlockDimensions(0)
	{}
	
	inline storage::desc::desc
	(
		size_type const & Layers,
		size_type const & Faces,
		size_type const & Levels,
		format_type const & Format,
		dimensions_type const & Dimensions,
		size_type const & BlockSize,
		dimensions_type const & BlockDimensions
	) :
		Layers(Layers),
		Faces(Faces),
		Levels(Levels),
		Format(Format),
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
		format_type const & Format,
		dimensions_type const & Dimensions
	) :
		Desc(Layers, Faces, Levels, Format, Dimensions, gli::block_size(Format), gli::block_dimensions(Format)),
		Data(this->layerSize() * Layers)
	{}

	inline storage::storage
	(
		size_type const & Layers, 
		size_type const & Faces,
		size_type const & Levels,
		dimensions_type const & Dimensions,
		size_type const & BlockSize,
		dimensions_type const & BlockDimensions
	) : 
		Desc(Layers, Faces, Levels, FORMAT_NULL, Dimensions, BlockSize, BlockDimensions),
		Data(this->layerSize() * Layers)
	{}

	inline bool storage::empty() const
	{
		return this->Data.empty();
	}

	inline storage::format_type storage::format() const
	{
		return this->Desc.Format;
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

	inline storage::dimensions_type storage::blockDimensions() const
	{
		return this->Desc.BlockDimensions;
	}

	inline storage::dimensions_type storage::dimensions
	(
		size_type const & Level
	) const
	{
		assert(Level < this->Desc.Levels);

		return glm::max(this->Desc.Dimensions >> storage::dimensions_type(Level), storage::dimensions_type(1));
	}

	inline storage::size_type storage::size() const
	{
		return this->Data.size();
	}

	inline glm::byte const * storage::data() const
	{
		assert(!this->empty());
		return &this->Data[0];
	}

	inline glm::byte * storage::data()
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
	inline std::size_t block_size(format const & Format)
	{
		return detail::getFormatInfo(Format).BlockSize;
	}

	inline glm::uvec3 block_dimensions(format const & Format)
	{
		return detail::getFormatInfo(Format).BlockDimensions;
	}

	inline std::size_t bits_per_pixel(format const & Format)
	{
		return detail::getFormatInfo(Format).BBP;
	}

	inline std::size_t component_count(format const & Format)
	{
		return detail::getFormatInfo(Format).Component;
	}

	inline bool is_compressed(format const & Format)
	{
		return detail::getFormatInfo(Format).Compressed;
	}
}//namespace gli
