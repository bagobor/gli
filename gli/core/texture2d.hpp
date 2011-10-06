///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-01-09
// Updated : 2010-01-09
// Licence : This source is under MIT License
// File    : gli/core/texture2d.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_CORE_TEXTURE2D_INCLUDED
#define GLI_CORE_TEXTURE2D_INCLUDED

#include "image2d.hpp"

namespace gli
{
	//template <template <typename> class mem>
	class texture2D
	{
	public:
		typedef image2D::dimensions_type dimensions_type;
		typedef image2D::texcoord_type texcoord_type;
		typedef image2D::size_type size_type;
		//typedef image2D::value_type value_type;
		typedef image2D::format_type format_type;
		typedef image2D::data_type data_type;
		typedef std::vector<image2D>::size_type level_type;

	public:
		texture2D();

		explicit texture2D(
			level_type const & Levels);

		explicit texture2D(
			level_type const & Levels,
			format const & Format,
			dimensions_type const & Dimensions);
		//texture2D(image const & Mipmap, bool GenerateMipmaps = false);

		~texture2D();

		image2D & operator[] (
			level_type const & Level);
		image2D const & operator[] (
			level_type const & Level) const;

		bool empty() const;
		format_type format() const;
		level_type levels() const;
		size_type memory_size() const;

		void resize(level_type const & Levels);

		template <typename genType>
		void swizzle(glm::comp X, glm::comp Y, glm::comp Z, glm::comp W);

	private:
		std::vector<image2D> Images;
	};

}//namespace gli

#include "texture2d.inl"

#endif//GLI_CORE_TEXTURE2D_INCLUDED
