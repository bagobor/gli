///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2011-04-06
// Updated : 2011-04-06
// Licence : This source is under MIT License
// File    : gli/core/texture_cube_array.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_CORE_TEXTURE_CUBE_ARRAY_INCLUDED
#define GLI_CORE_TEXTURE_CUBE_ARRAY_INCLUDED

#include "storage.hpp"
#include "texture_cube.hpp"

namespace gli
{
	class textureCubeArray
	{
	public:
		typedef detail::storage::texcoord2_type dimensions_type;
        typedef detail::storage::texcoord2_type texcoord_type;
		typedef detail::storage::size_type size_type;
		typedef detail::storage::format_type format_type;
		typedef detail::storage::data_type data_type;
		typedef detail::storage::face_type face_type;

	public:
		textureCubeArray();

		explicit textureCubeArray(
			size_type const & Layers, 
            size_type const & Faces,
			size_type const & Levels,
            format_type const & InternalFormat,
            dimensions_type const & Dimensions);

		~textureCubeArray();

		textureCube & operator[] (
			size_type const & Layer);
		textureCube const & operator[] (
			size_type const & Layer) const;

		bool empty() const;
		format_type format() const;
		size_type layers() const;
        size_type faces() const;
		size_type levels() const;

        bool isTexture1D const {return false;}
        bool isTexture1DArray const {return false;}
        bool isTexture2D const {return false;}
        bool isTexture2DArray const {return false;}
        bool isTexture3D const {return false;}
        bool isTextureCube const {return false;}
        bool isTextureCubeArray const {return true;}
        
	private:
		detail::storage Storage;
	};

}//namespace gli

#include "texture_cube_array.inl"

#endif//GLI_CORE_TEXTURE_CUBE_ARRAY_INCLUDED
