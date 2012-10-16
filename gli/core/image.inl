///////////////////////////////////////////////////////////////////////////////////
/// OpenGL Image (gli.g-truc.net)
///
/// Copyright (c) 2008 - 2012 G-Truc Creation (www.g-truc.net)
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
	template <class dimensionType>
	inline std::size_t memory_size
	(
		gli::format const & InternalFormat,
		dimensionType const & Dimension
	)
	{
		std::size_t const BlockSize = gli::block_size(Format);
		std::size_t const BPP = gli::bits_per_pixel(Format);

		dimensionType DimensionClamped = glm::max(Dimension, dimensionType(1));
		if((BlockSize << 3) != BPP)
			DimensionClamped = (DimensionClamped + dimensionType(3)) >> dimensionType(2);

		std::size_t const BlockCount = glm::compMul(DimensionClamped);
		return BlockCount * BlockSize;
	}

}//namespace detail

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

	inline bool operator== (image const & ImageA, image const & ImageB)
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

	inline bool operator!= (image const & ImageA, image const & ImageB)
	{
		return !(ImageA == ImageB);
	}
}//namespace gli
