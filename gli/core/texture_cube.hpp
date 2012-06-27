///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2011-04-06
// Updated : 2011-04-06
// Licence : This source is under MIT License
// File    : gli/core/texture_cube.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_CORE_TEXTURE_CUBE_INCLUDED
#define GLI_CORE_TEXTURE_CUBE_INCLUDED

#include "storage.hpp"
#include "texture2d.hpp"

namespace gli
{
	enum face
	{
		POSITIVE_X,
		NEGATIVE_X,
		POSITIVE_Y,
		NEGATIVE_Y,
		POSITIVE_Z,
		NEGATIVE_Z,
		FACE_MAX
	};

	class textureCube
	{
	public:
		typedef detail::storage::texcoord2_type dimensions_type;
        typedef detail::storage::texcoord2_type texcoord_type;
		typedef detail::storage::size_type size_type;
		typedef detail::storage::format_type format_type;
		typedef detail::storage::data_type data_type;
		typedef detail::storage::face_type face_type;

	public:
		textureCube();

		explicit textureCube(
            size_type const & Faces,
            size_type const & Levels,
            format_type const & InternalFormat,
            dimensions_type const & Dimensions);

		~textureCube();

		texture2D & operator[] (
			size_type const & Face);
		texture2D const & operator[] (
			size_type const & Face) const;

		bool empty() const;
		format_type format() const;
		size_type levels() const;
        size_type faces() const;

        bool isTexture1D const {return false;}
        bool isTexture1DArray const {return false;}
        bool isTexture2D const {return false;}
        bool isTexture2DArray const {return false;}
        bool isTexture3D const {return false;}
        bool isTextureCube const {return true;}
        bool isTextureCubeArray const {return false;}
        
	private:
		detail::storage Storage;
	};

}//namespace gli

#include "texture_cube.inl"

#endif//GLI_CORE_TEXTURE_CUBE_INCLUDED
