///////////////////////////////////////////////////////////////////////////////////
/// OpenGL Image (gli.g-truc.net)
///
/// Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
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
/// @file gli/core/image.inl
/// @date 2011-10-06 / 2011-10-06
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

namespace gli{
namespace detail
{
	struct format_desc
	{
		imageBase<>::size_type BlockSize;
		imageBase<>::size_type BlockWidth;
		imageBase<>::size_type BlockHeight;
		imageBase<>::size_type BBP;
		imageBase<>::size_type Component;
	};

	inline format_desc const getFormatInfo(format const & Format)
	{
		format_desc const Desc[FORMAT_MAX] =
		{
			{  0,  0, 0, 0,  0},	//FORMAT_NULL

			// Unsigned integer formats
			{  1, 1, 1,  8,  1},	//R8U,
			{  2, 1, 1, 16,  2},	//RG8U,
			{  3, 1, 1, 24,  3},	//RGB8U,
			{  4, 1, 1, 32,  4},	//RGBA8U,

			{  2, 1, 1, 16,  1},	//R16U,
			{  4, 1, 1, 32,  2},	//RG16U,
			{  6, 1, 1, 48,  3},	//RGB16U,
			{  8, 1, 1, 64,  4},	//RGBA16U,

			{  4, 1, 1,  32,  1},	//R32U,
			{  8, 1, 1,  64,  2},	//RG32U,
			{ 12, 1, 1,  96,  3},	//RGB32U,
			{ 16, 1, 1, 128,  4},	//RGBA32U,

			//// Signed integer formats
			{  4, 1, 1,  32,  1},	//R8I,
			{  8, 1, 1,  64,  2},	//RG8I,
			{ 12, 1, 1,  96,  3},	//RGB8I,
			{ 16, 1, 1, 128,  4},	//RGBA8I,

			{  2, 1, 1, 16,  1},	//R16I,
			{  4, 1, 1, 32,  2},	//RG16I,
			{  6, 1, 1, 48,  3},	//RGB16I,
			{  8, 1, 1, 64,  4},	//RGBA16I,

			{  4, 1, 1,  32,  1},	//R32I,
			{  8, 1, 1,  64,  2},	//RG32I,
			{ 12, 1, 1,  96,  3},	//RGB32I,
			{ 16, 1, 1, 128,  4},	//RGBA32I,

			//// Floating formats
			{  2, 1, 1, 16,  1},	//R16F,
			{  4, 1, 1, 32,  2},	//RG16F,
			{  6, 1, 1, 48,  3},	//RGB16F,
			{  8, 1, 1, 64,  4},	//RGBA16F,

			{  4, 1, 1,  32,  1},	//R32F,
			{  8, 1, 1,  64,  2},	//RG32F,
			{ 12, 1, 1,  96,  3},	//RGB32F,
			{ 16, 1, 1, 128,  4},	//RGBA32F,

			//// Packed formats
			{  4, 1, 1, 32,  3},	//RGBE8,
			{  4, 1, 1, 32,  3},	//RGB9E5,
			{  4, 1, 1, 32,  3},	//RG11B10F,
			{  2, 1, 1, 16,  3},	//R5G6B5,
			{  2, 1, 1, 16,  4},	//RGBA4,
			{  4, 1, 1, 32,  3},	//RGB10A2,

			//// Depth formats
			{  2, 1, 1, 16,  1},	//D16,
			{  4, 1, 1, 32,  1},	//D24X8,
			{  4, 1, 1, 32,  2},	//D24S8,
			{  4, 1, 1, 32,  1},	//D32F,
			{  8, 1, 1, 64,  2},	//D32FS8X24,

			//// Compressed formats
			{  8, 4, 4, 4,  4},	//DXT1,
			{ 16, 4, 4, 8,  4},	//DXT3,
			{ 16, 4, 4, 8,  4},	//DXT5,
			{  8, 4, 4, 4,  1},	//ATI1N_UNORM,
			{  8, 4, 4, 4,  1},	//ATI1N_SNORM,
			{ 16, 4, 4, 8,  2},	//ATI2N_UNORM,
			{ 16, 4, 4, 8,  2},	//ATI2N_SNORM,
			{ 16, 4, 4, 8,  3},	//BP_UF16,
			{ 16, 4, 4, 8,  3},	//BP_SF16,
			{ 16, 4, 4, 8,  4},	//BP,
		};

		return Desc[Format];
	};

	template <class dimensionType>
	inline std::size_t memory_size
	(
		gli::format const & InternalFormat,
		dimensionType const & Dimension
	)
	{
		std::size_t const BlockSize = detail::getFormatInfo(InternalFormat).BlockSize;
		std::size_t const BPP = detail::getFormatInfo(InternalFormat).BBP;

		dimensionType DimensionClamped = glm::max(Dimension, dimensionType(1));
		if((BlockSize << 3) != BPP)
			DimensionClamped = (DimensionClamped + dimensionType(3)) >> dimensionType(2);

		std::size_t const BlockCount = glm::compMul(DimensionClamped);
		return BlockCount * BlockSize;
	}

}//namespace detail
	
template <typename valType, class container> 
imageBase<valType, container>::imageBase() :
	InternalFormat(FORMAT_NULL)
{}

template <typename valType, class container> 
imageBase<valType, container>::imageBase
(
	imageBase const & Image
) :
	Data(Image.Data),
	InternalFormat(Image.InternalFormat)
{}

template <typename valType, class container> 
imageBase<valType, container>::imageBase
(
	format_type const & InternalFormat, 
	size_type const & Size
) :
	InternalFormat(InternalFormat)
{
	this->Data.resize((Size * gli::detail::getFormatInfo(this->format()).BBP) >> size_type(3));
}

template <typename valType, class container> 
template <typename genType>
imageBase<valType, container>::imageBase
(
	format_type const & InternalFormat, 
	std::vector<genType> const & Data
) :
	InternalFormat(InternalFormat)
{
	this->Data.resize((Data.size() * gli::detail::getFormatInfo(this->format()).BBP) >> size_type(3));
	//this->Data.resize((Data.size() + sizeof(genType)) / sizeof(image::data_type::value_type));
	memcpy(&this->Data[0], &Data[0], this->Data.size());
}

template <typename valType, class container> 
imageBase<valType, container> & imageBase<valType, container>::operator= (imageBase<valType, container> const & Image)
{
	this->Data = Image.Data;
	this->InternalFormat = Image.InternalFormat;
	return *this;
}

template <typename valType, class container> 
typename imageBase<valType, container>::size_type imageBase<valType, container>::memory_size() const
{
	return this->Data.size();
}

template <typename valType, class container> 
typename imageBase<valType, container>::size_type imageBase<valType, container>::size() const
{
	return (this->Data.size() << size_type(3)) / detail::getFormatInfo(this->format()).BBP;
}

template <typename valType, class container> 
typename imageBase<valType, container>::size_type imageBase<valType, container>::texel_size() const
{
	return gli::detail::getFormatInfo(this->format()).BBP;
}

template <typename valType, class container> 
typename imageBase<valType, container>::size_type imageBase<valType, container>::block_size() const
{
	return gli::detail::getFormatInfo(this->format()).BlockSize;
}

template <typename valType, class container> 
typename imageBase<valType, container>::size_type imageBase<valType, container>::bit_per_pixel() const
{
	return gli::detail::getFormatInfo(this->format()).BBP;
}

template <typename valType, class container> 
typename imageBase<valType, container>::size_type imageBase<valType, container>::capacity() const
{
	return this->Data.size();// * sizeof(image::data_type::value_type);
}

template <typename valType, class container> 
typename imageBase<valType, container>::size_type imageBase<valType, container>::components() const
{
	return gli::detail::getFormatInfo(this->format()).Component;
}

template <typename valType, class container> 
typename imageBase<valType, container>::format_type imageBase<valType, container>::format() const
{
	return this->InternalFormat;
}

template <typename valType, class container> 
bool imageBase<valType, container>::empty() const
{
	return this->format() == FORMAT_NULL;
}

template <typename valType, class container> 
void * imageBase<valType, container>::data()
{
	return &this->Data[0];
}

template <typename valType, class container> 
void const * const imageBase<valType, container>::data() const
{
	return &this->Data[0];
}
		
template <typename valType, class container> 
template <typename genType>
genType * imageBase<valType, container>::data()
{
	return reinterpret_cast<genType*>(&this->Data[0]);
}

template <typename valType, class container> 
template <typename genType>
genType const * const imageBase<valType, container>::data() const
{
	return reinterpret_cast<genType*>(&this->Data[0]);
}

	/////////////////////////////////
	// image

	inline image::image() :
		Storage(0),
		Dimensions(0),
		Offset(0)
	{}

	inline image::image
	(
		image const & Image
	) : 
		Storage(Image.Storage),
		Dimensions(Image.Dimensions),
		Offset(Image.Offset)
	{}

	inline image::image
	(
		shared_ptr<detail::storage> const & Storage
	) :
		Storage(Storage),
		Dimensions(dimensions_type(Storage->dimensions(0), 1)),
		Offset(0)
	{}

	inline image::image
	(
		shared_ptr<detail::storage> const & Storage,
		size_type const & Offset,
		dimensions_type const & Dimensions
	) :
		Storage(Storage),
		Dimensions(Dimensions),
		Offset(Offset)
	{}

	// Allocate a new texture storage constructor
	template <typename genType>
	inline image::image
	(
		dimensions_type const & Dimensions,
		std::vector<genType> const & Data
	) :
		Storage(shared_ptr<detail::storage>(new detail::storage(
			detail::storage::size_type(1),
			detail::storage::flag_type(1),
			detail::storage::size_type(1),
			detail::storage::dimensions3_type(Dimensions),
			sizeof(genType)))),
		Dimensions(Dimensions),
		Offset(0)
	{
		assert(glm::compMul(Dimensions) <= Data.size());
		memcpy(this->data(), &Data[0], Data.size() * sizeof(genType));
	}

	// Allocate a new texture storage constructor and copy data
	inline image::image
	(
		dimensions_type const & Dimensions,
		size_type const & BlockSize
	) :
		Storage(new detail::storage(
			1, 1, 1, detail::storage::dimensions3_type(Dimensions), BlockSize)),
		Dimensions(Dimensions),
		Offset(0)
	{}

	inline image::~image()
	{

	}

	inline image & image::operator= (image const & Image)
	{
		this->Storage = Image.Storage;
		this->Offset = Image.Offset;
		this->Dimensions = Image.Dimensions;
		return *this;
	}

	inline image::dimensions_type image::dimensions() const
	{
		return this->Dimensions;
	}

	inline bool image::empty() const
	{
		return this->Storage.get() == 0;
	}

	inline image::size_type image::size() const
	{
		return this->Storage->memorySize();
	}

	inline void * image::data()
	{
		return this->Storage->data() + this->Offset;
	}

	inline void const * const image::data() const
	{
		return this->Storage->data() + this->Offset;
	}

	template <typename genType>
	inline genType * image::data()
	{
		return reinterpret_cast<genType*>(this->Storage->data() + this->Offset);
	}

	template <typename genType>
	inline genType const * const image::data() const
	{
		return reinterpret_cast<genType const * const>(this->Storage->data() + this->Offset);
	}

	bool operator== (image const & ImageA, image const & ImageB)
	{
		if(ImageA.data() == ImageB.data())
			return true;

		if(!glm::all(glm::equal(ImageA.dimensions(), ImageB.dimensions())))
			return false;

		if(ImageA.size() != ImageB.size())
			return false;

		for(image::size_type i(0); i < ImageA.size(); ++i)
			if(*(ImageA.data<glm::byte>() + i) != *(ImageB.data<glm::byte>() + i))
				return false;

		return true;
	}

	bool operator!= (image const & ImageA, image const & ImageB)
	{
		return !(ImageA == ImageB);
	}
}//namespace gli
