///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2012-06-25
// Updated : 2012-06-25
// Licence : This source is under MIT License
// File    : gli/core/texture1darray.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_CORE_TEXTURE1DARRAY_INCLUDED
#define GLI_CORE_TEXTURE1DARRAY_INCLUDED

#include "storage.hpp"
#include "image1d.hpp"

namespace gli
{
	//template <template <typename> class mem>
	class texture1DArray
	{
	public:
		typedef gli::detail::storage::dimensions1_type dimensions_type;
        typedef gli::detail::storage::texcoord1_type texcoord_type;
		typedef gli::detail::storage::size_type size_type;
		typedef gli::detail::storage::format_type format_type;
        typedef gli::detail::storage::data_type data_type;
        
	public:
		texture1DArray();
        
		explicit texture1DArray(
            size_type const & Layers,
            size_type const & Levels,
            format_type const & InternalFormat,
            dimensions_type const & Dimensions);
               
		~texture1DArray();
        
		texture1D operator[] (size_type const & Level);
		texture1D const operator[] (size_type const & Level) const;
        
		bool empty() const;
		format_type format() const;
        dimensions_type dimensions() const;
		size_type levels() const;
		size_type memorySize() const;
        
        bool isTexture1D const {return false;}
        bool isTexture1DArray const {return true;}
        bool isTexture2D const {return false;}
        bool isTexture2DArray const {return false;}
        bool isTexture3D const {return false;}
        bool isTextureCube const {return false;}
        bool isTextureCubeArray const {return false;}
        
	private:
        detail::storage Storage;
	};
    
}//namespace gli

#include "texture1d_array.inl"

#endif//GLI_CORE_TEXTURE1DARRAY_INCLUDED
