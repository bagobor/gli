///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2011-04-06
// Updated : 2011-04-06
// Licence : This source is under MIT License
// File    : gli/core/texture2d_array.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_CORE_TEXTURE2D_ARRAY_INCLUDED
#define GLI_CORE_TEXTURE2D_ARRAY_INCLUDED

#include "texture2d.hpp"

namespace gli
{
	class texture2DArray
	{
	public:
		typedef glm::uvec2 dimensions_type;
		typedef storage::size_type size_type;
		typedef gli::format format_type;
        
	public:
		texture2DArray();
        
		explicit texture2DArray(size_type const & Levels);
        
		explicit texture2DArray(
            size_type const & Layers,
            size_type const & Levels,
            format_type const & InternalFormat,
            dimensions_type const & Dimensions);
        
		template <typename genType>
		explicit texture2DArray(
            size_type const & Layers,
            size_type const & Levels,
            format_type const & InternalFormat, 
            dimensions_type const & Dimensions,
            genType const & Texel);
        
		texture2DArray();
        
		texture2D operator[] (size_type const & Level);
		texture2D const operator[] (size_type const & Level) const;
        
		bool empty() const;
		format_type format() const;
		size_type levels() const;
        size_type layers() const;
		size_type memorySize() const;
        
        bool isTexture1D const {return false;}
        bool isTexture1DArray const {return false;}
        bool isTexture2D const {return false;}
        bool isTexture2DArray const {return true;}
        bool isTexture3D const {return false;}
        bool isTextureCube const {return false;}
        bool isTextureCubeArray const {return false;}
        
	private:
        detail::storage Storage;
	};

}//namespace gli

#include "texture2d_array.inl"

#endif//GLI_CORE_TEXTURE2D_ARRAY_INCLUDED
