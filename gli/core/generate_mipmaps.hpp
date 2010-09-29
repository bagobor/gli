///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-09-27
// Updated : 2010-09-27
// Licence : This source is under MIT License
// File    : gli/core/generate_mipmaps.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_GENERATE_MIPMAPS_INCLUDED
#define GLI_GENERATE_MIPMAPS_INCLUDED

#include "texture.hpp"

namespace gli
{
	texture generateMipmaps(
		texture const & Texture, 
		texture::level_type const & BaseLevel);

}//namespace gli

#include "generate_mipmaps.inl"

#endif//GLI_GENERATE_MIPMAPS_INCLUDED
