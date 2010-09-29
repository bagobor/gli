///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-12-19
// Updated : 2010-09-27
// Licence : This source is under MIT License
// File    : gli/gtx/fetch.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_FETCH_INCLUDED
#define GLI_FETCH_INCLUDED

#include "../gli.hpp"

namespace gli
{
	template <typename genType>
	genType texelFetch(
		texture const & Texture, 
		glm::ivec2 const & TexCoord,
		texture::level_type const & Level);

	template <typename genType>
	genType textureLod(
		texture const & Texture, 
		glm::vec2 const & TexCoord,
		texture::level_type const & Level);

	template <typename genType>
	void texelWrite(
		texture & Texture,
		glm::uvec2 const & Texcoord,
		texture::level_type const & Level,
		genType const & Color);

}//namespace gli

#include "fetch.inl"

#endif//GLI_FETCH_INCLUDED
