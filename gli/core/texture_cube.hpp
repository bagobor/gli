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

#include "texture2d.hpp"

namespace gli
{
	class textureCube
	{
	public:
		typedef detail::storage::texcoord2_type dimensions_type;
		typedef detail::storage::texcoord2_type texcoord_type;
		typedef detail::storage::size_type size_type;
		typedef detail::storage::format_type format_type;

	public:
		textureCube();

		/// Allocate a new storage constructor
		explicit textureCube(
			size_type const & Faces,
			size_type const & Levels,
			format_type const & Format,
			dimensions_type const & Dimensions);

		/// Reference an exiting storage constructor
		explicit textureCube(
			format_type const & Format,
			shared_ptr<detail::storage> const & Storage,
			detail::view const & View);

		~textureCube();

		texture2D & operator=(texture2D const & Texture2D);

		texture2D operator[] (
			face const & Face);
		texture2D const operator[] (
			face const & Face) const;

		bool empty() const;
		size_type size() const;
		dimensions_type dimensions() const;
		size_type levels() const;
		size_type faces() const;
		format_type format() const;

		void * data();
		void const * const data() const;

		template <typename genType>
		genType * data();
		template <typename genType>
		genType const * const data() const;

	private:
		shared_ptr<detail::storage> Storage;
		detail::view const View;
		format_type const Format;
	};

}//namespace gli

#include "texture_cube.inl"

#endif//GLI_CORE_TEXTURE_CUBE_INCLUDED
