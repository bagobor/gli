///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2011-04-06
// Updated : 2011-04-06
// Licence : This source is under MIT License
// File    : gli/core/texture2d_array.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_CORE_texture2d_array
#define GLI_CORE_texture2d_array GLI_VERSION

#include "storage.hpp"
#include "texture2d.hpp"

namespace gli
{
	class texture2DArray
	{
	public:
		typedef gli::detail::storage::dimensions3_type dimensions_type;
        typedef gli::detail::storage::texcoord3_type texcoord_type;
		typedef gli::detail::storage::size_type size_type;
		typedef gli::detail::storage::format_type format_type;
        typedef gli::detail::storage::data_type data_type;
        
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
        
		~texture2DArray();
        
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

		shared_ptr<detail::storage> Storage;
		std::size_t Offset;
		format_type Format;
	};

}//namespace gli

#include "texture2d_array.inl"

#endif//GLI_CORE_texture2d_array
