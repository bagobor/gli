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
/// @file gli/core/texture1d_array.inl
/// @date 2012-06-27 / 2013-01-12
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

namespace gli
{
	inline texture1DArray::texture1DArray() :
		Storage(0),
		View(0, 0, 0, 0, 0, 0),
		Format(FORMAT_NULL)
	{}

	inline texture1DArray::texture1DArray
	(
		size_type const & Layers,
		size_type const & Levels,
		format_type const & Format,
		dimensions_type const & Dimensions
	) :
		Storage(shared_ptr<storage>(new storage(
			Layers, 1, Levels,
			storage::dimensions_type(Dimensions, 1, 1),
			block_size(Format),
			block_dimensions(Format)))),
		View(0, Layers - 1, 0, 0, 0, Levels - 1),
		Format(Format)
	{}

	inline texture1D texture1DArray::operator[]
	(
		size_type const & Layer
	) const
	{
		assert(Layer < this->layers());

		return texture1D(
			this->format(),
			this->Storage,
			detail::view(
				Layer, 
				Layer, 
				this->View.BaseFace,
				this->View.MaxFace,
				this->View.BaseLevel,
				this->View.MaxLevel));
	}

	inline bool texture1DArray::empty() const
	{
		if(this->Storage.get() == 0)
			return true;
		return this->Storage->empty();
	}

	inline texture1DArray::size_type texture1DArray::size() const
	{
		return this->Storage->layerSize() * this->layers();
	}

	template <typename genType>
	inline texture1DArray::size_type texture1DArray::size() const
	{
		assert(sizeof(genType) <= this->Storage->blockSize());
		return this->size() / sizeof(genType);
	}

	inline texture1DArray::dimensions_type texture1DArray::dimensions() const
	{
		return texture1DArray::dimensions_type(this->Storage->dimensions(this->View.BaseLevel).x);
	}

	inline texture1DArray::format_type texture1DArray::format() const
	{
		return this->Format;
	}

	inline texture1DArray::size_type texture1DArray::layers() const
	{
		return this->View.MaxLayer - this->View.BaseLayer + 1;
	}

	inline texture1DArray::size_type texture1DArray::faces() const
	{
		return this->View.MaxFace - this->View.BaseFace + 1;
	}

	inline texture1DArray::size_type texture1DArray::levels() const
	{
		return this->View.MaxLevel - this->View.BaseLevel + 1;
	}

	inline void * texture1DArray::data()
	{
		assert(!this->empty());

		size_type const offset = detail::linearAddressing(
			*this->Storage, this->View.BaseLayer, this->View.BaseFace, this->View.BaseLevel);

		return this->Storage->data() + offset;
	}

	inline void const * texture1DArray::data() const
	{
		assert(!this->empty());

		size_type const offset = detail::linearAddressing(
			*this->Storage, this->View.BaseLayer, this->View.BaseFace, this->View.BaseLevel);

		return this->Storage->data() + offset;
	}

	template <typename genType>
	inline genType * texture1DArray::data()
	{
		assert(!this->empty());
		assert(this->Storage->blockSize() >= sizeof(genType));

		return reinterpret_cast<genType *>(this->data());
	}

	template <typename genType>
	inline genType const * texture1DArray::data() const
	{
		assert(!this->empty());
		assert(this->Storage->blockSize() >= sizeof(genType));

		return reinterpret_cast<const genType *>(this->data());
	}
}//namespace gli
