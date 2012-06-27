///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2012-06-27
// Updated : 2012-06-27
// Licence : This source is under MIT License
// File    : gli/core/texture1d_array.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace gli
{
	inline texture1DArray::texture1DArray()
	{}

	inline texture1DArray::texture1DArray
	(
		texture1DArray::size_type const & Layers, 
		texture1DArray::size_type const & Levels
	) :

	{

	}

	inline texture1DArray::texture1DArray()
	{}

	inline texture1D texture1DArray::operator[] 
	(
		size_type const & Layer
	)
	{
		return this->Storage.layers();
	}

	inline texture1D const texture1DArray::operator[] 
	(
		size_type const & Layer
	) const
	{
		return this->Arrays[Layer];
	}

	inline bool texture1DArray::empty() const
	{
		return this->Arrays.empty();
	}

	inline texture1DArray::format_type texture1DArray::format() const
	{
		return this->Arrays.empty() ? FORMAT_NULL : this->Arrays[0].format();
	}

	inline texture1DArray::size_type texture1DArray::layers() const
	{
		return this->Storage.layers();
	}

	inline texture1DArray::size_type texture1DArray::levels() const
	{
		if(this->empty())
			return 0;
		return this->Arrays[0].levels();
	}
    
	inline texture1DArray::size_type texture1DArray::levels() const
	{
		if(this->empty())
			return 0;
		return this->Arrays[0].levels();
	}

}//namespace gli
