///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-09-08
// Updated : 2010-09-08
// Licence : This source is under MIT License
// File    : gli/core/size.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_CORE_SIZE_INCLUDED
#define GLI_CORE_SIZE_INCLUDED

#include "texture1d.hpp"
#include "texture1d_array.hpp"
#include "texture2d.hpp"
#include "texture2d_array.hpp"
#include "texture3d.hpp"
#include "texture_cube.hpp"
#include "texture_cube_array.hpp"

namespace gli
{
	//template <size_type sizeType>
	image::size_type size(
		image const & Image, 
		image::size_type const & SizeType);

	//template <size_type sizeType>
	texture2D::size_type size(
		texture2D const & Texture, 
		texture2D::size_type const & SizeType);

}//namespace gli

#include "size.inl"

#endif//GLI_CORE_SIZE_INCLUDED
