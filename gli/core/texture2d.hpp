///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-01-09
// Updated : 2010-01-09
// Licence : This source is under MIT License
// File    : gli/core/texture2d.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_CORE_texture2d
#define GLI_CORE_texture2d

#include "image.hpp"
/// TODO: Remove include image2d.hpp
#include "image2d.hpp"

namespace gli
{
	//template <template <typename> class mem>
	class texture2D
	{
	public:
		typedef gli::detail::storage::dimensions2_type dimensions_type;
		typedef gli::detail::storage::texcoord2_type texcoord_type;
		typedef gli::detail::storage::size_type size_type;
		typedef gli::format format_type;
		typedef gli::detail::storage::data_type data_type;

	private:
/*
		explicit texture2D(
			size_type const & Levels,
			format_type const & Format,
			dimensions_type const & Dimensions,
			shared_ptr<detail::storage> const & Storage,
			size_type const & Offset);
*/
	public:
		texture2D();

		explicit texture2D(
			size_type const & Levels,
			format_type const & Format,
			dimensions_type const & Dimensions);
/*
		template <typename genType>
		explicit texture2D(
			size_type const & Levels,
			format_type const & Format, 
			dimensions_type const & Dimensions,
			genType const & Texel);
*/
		~texture2D();

		image & operator[] (
			size_type const & Level);
		image const & operator[] (
			size_type const & Level) const;

		bool empty() const;
		format_type format() const;
		dimensions_type dimensions() const;
		size_type levels() const;
		size_type size() const;
		data_type * data();
		data_type const * const data() const;
/*        
        bool isTexture1D const {return false;}
        bool isTexture1DArray const {return false;}
        bool isTexture2D const {return true;}
        bool isTexture2DArray const {return false;}
        bool isTexture3D const {return false;}
        bool isTextureCube const {return false;}
        bool isTextureCubeArray const {return false;}
*/
	private:
		shared_ptr<detail::storage> Storage;
		std::vector<image> Images;
		format_type const Format;
		size_type Offset;
	};

}//namespace gli

#include "texture2d.inl"

#endif//GLI_CORE_texture2d
