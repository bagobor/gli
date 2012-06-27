///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2011-04-06
// Updated : 2011-04-06
// Licence : This source is under MIT License
// File    : gli/core/texture2d_array.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace gli
{
	inline texture2DArray::texture2DArray()
	{}

	inline texture2DArray::texture2DArray
	(
		texture2DArray::size_type const & Layers, 
		texture2DArray::size_type const & Levels
	) :
		Arrays(Layers)
	{
		for(texture2DArray::size_type i = 0; i < this->Arrays.size(); ++i)
			this->Arrays[i].resize(Levels);
	}

	inline texture2DArray::~texture2DArray()
	{}

	inline texture2D texture2DArray::operator[] 
	(
		size_type const & Layer
	)
	{
		return this->Storage.layers();
	}

	inline texture2D const texture2DArray::operator[] 
	(
		size_type const & Layer
	) const
	{
		return this->Arrays[Layer];
	}

	inline bool texture2DArray::empty() const
	{
		return this->Arrays.empty();
	}

	inline texture2DArray::format_type texture2DArray::format() const
	{
		return this->Arrays.empty() ? FORMAT_NULL : this->Arrays[0].format();
	}

	inline texture2DArray::size_type texture2DArray::layers() const
	{
		return this->Storage.layers();
	}

	inline texture2DArray::size_type texture2DArray::levels() const
	{
		if(this->empty())
			return 0;
		return this->Arrays[0].levels();
	}
    
	inline texture2DArray::size_type texture2DArray::levels() const
	{
		if(this->empty())
			return 0;
		return this->Arrays[0].levels();
	}

}//namespace gli
