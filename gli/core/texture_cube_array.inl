///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2011-04-06
// Updated : 2011-04-06
// Licence : This source is under MIT License
// File    : gli/core/texture_cube_array.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace gli
{
	inline textureCubeArray::textureCubeArray() :
		Storage(0),
		View(0, 0, 0, 0, 0, 0),
		Format(FORMAT_NULL)
	{}

	inline textureCubeArray::textureCubeArray
	(
        size_type const & Layers,
		size_type const & Faces,
		size_type const & Levels,
		format_type const & Format,
		dimensions_type const & Dimensions
	) :
		Storage(shared_ptr<storage>(new storage(
			Layers, 1, Levels,
			storage::dimensions_type(Dimensions),
			block_size(Format),
			block_dimensions(Format)))),
		View(0, Layers - 1, 0, Faces - 1, 0, Levels - 1),
		Format(Format)
	{}

	inline textureCubeArray::textureCubeArray
	(
		format_type const & Format,
		shared_ptr<storage> const & Storage,
		detail::view const & View
	) :
		Storage(Storage),
		View(View),
		Format(Format)
	{}

	inline textureCube const & textureCubeArray::operator[] 
	(
		size_type const & Layer
	) const
	{
		assert(Layer < this->layers());

		return textureCube(
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

	inline bool textureCubeArray::empty() const
	{
		if(this->Storage.get() == 0)
			return true;
		return this->Storage->empty();
	}
    
	inline textureCubeArray::size_type textureCubeArray::size() const
	{
		return this->Storage->layerSize() * this->layers();
	}
    
	inline textureCubeArray::dimensions_type textureCubeArray::dimensions() const
	{
		return textureCubeArray::dimensions_type(this->Storage->dimensions(this->View.BaseLevel));
	}
    
	inline textureCube::format_type textureCubeArray::format() const
	{
		return this->Format;
	}
    
	inline textureCubeArray::size_type textureCubeArray::layers() const
	{
		return this->View.MaxLayer - this->View.BaseLayer + 1;
	}
    
	inline textureCubeArray::size_type textureCubeArray::faces() const
	{
		return this->View.MaxFace - this->View.BaseFace + 1;
	}
    
	inline textureCubeArray::size_type textureCubeArray::levels() const
	{
		return this->View.MaxLevel - this->View.BaseLevel + 1;
	}

	inline void * textureCubeArray::data()
	{
		assert(!this->empty());
        
		size_type const offset = detail::linearAddressing(
            *this->Storage, this->View.BaseLayer, this->View.BaseFace, this->View.BaseLevel);
        
		return this->Storage->data() + offset;
	}
    
	inline void const * textureCubeArray::data() const
	{
		assert(!this->empty());
		
		size_type const offset = detail::linearAddressing(
            *this->Storage, this->View.BaseLayer, this->View.BaseFace, this->View.BaseLevel);
        
		return this->Storage->data() + offset;
	}
    
	template <typename genType>
	inline genType * textureCubeArray::data()
	{
		assert(!this->empty());
		assert(this->Storage->blockSize() >= sizeof(genType));
        
		return reinterpret_cast<genType *>(this->Storage->data());
	}
    
	template <typename genType>
	inline genType const * textureCubeArray::data() const
	{
		assert(!this->empty());
		assert(this->Storage->blockSize() >= sizeof(genType));
        
		return reinterpret_cast<genType const * const>(this->Storage->data());
	}
    
}//namespace gli
