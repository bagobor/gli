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
		View(0, 0, 0, 0, 0, Levels - 1),
        Format(Format)
	{}

	inline texture1D const & texture1DArray::operator[]
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


	inline texture1DArray::size_type texture1DArray::layers() const
	{
		return this->View.MaxLayer - this->View.BaseLayer + 1;
	}
    
	inline texture1DArray::size_type texture1DArray::faces() const
	{
		return 1;
	}
    
	inline texture1DArray::size_type texture1DArray::levels() const
	{
		return this->View.MaxLevel - this->View.BaseLevel + 1;
	}
    
}//namespace gli
