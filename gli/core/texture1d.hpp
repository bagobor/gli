///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2012-06-25
// Updated : 2012-10-16
// Licence : This source is under MIT License
// File    : gli/core/texture1d.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_CORE_TEXTURE1D_INCLUDED 
#define GLI_CORE_TEXTURE1D_INCLUDED

#include "image.hpp"

namespace gli
{
	//template <template <typename> class mem>
	class texture1D
	{
	public:
		typedef gli::detail::storage::dimensions1_type dimensions_type;
		typedef gli::detail::storage::texcoord1_type texcoord_type;
		typedef gli::detail::storage::size_type size_type;
		typedef gli::format format_type;
		typedef glm::byte data_type;

	public:
		texture1D();

		explicit texture1D(
			size_type const & Levels,
			format_type const & InternalFormat,
			dimensions_type const & Dimensions);
/*
		template <typename genType>
		explicit texture1D(
			size_type const & Levels,
			format_type const & InternalFormat, 
			dimensions_type const & Dimensions,
			genType const & Texel);
*/
		~texture1D();

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

	private:
		detail::storage Storage;
		std::vector<image> Images;
		format_type const Format;
		size_type Offset;
	};

}//namespace gli

#include "texture1d.inl"

#endif//GLI_CORE_TEXTURE1D_INCLUDED
