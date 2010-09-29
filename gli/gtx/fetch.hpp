///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-12-19
// Updated : 2010-09-27
// Licence : This source is under MIT License
// File    : gli/gtx/fetch.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_GTX_FETCH_INCLUDED
#define GLI_GTX_FETCH_INCLUDED

#include "../gli.hpp"

namespace gli{
namespace gtx{
namespace fetch
{
	template <typename genType>
	genType texelFetch(
		texture const & Texture, 
		texture::dimensions_type const & Texcoord,
		texture::level_type const & Level);

	template <typename genType>
	genType textureLod(
		texture const & Texture, 
		texture::texcoord_type const & Texcoord,
		texture::level_type const & Level);

	template <typename genType>
	void texelWrite(
		texture & Texture,
		texture::dimensions_type const & Texcoord,
		texture::level_type const & Level,
		genType const & Color);

}//namespace fetch
}//namespace gtx
}//namespace gli

namespace gli{using namespace gtx::fetch;}

#include "fetch.inl"

#endif//GLI_GTX_FETCH_INCLUDED
