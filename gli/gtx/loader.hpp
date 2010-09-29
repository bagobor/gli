///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-09-08
// Updated : 2010-09-27
// Licence : This source is under MIT License
// File    : gli/gtx/loader.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_GTX_LOADER_INCLUDED
#define GLI_GTX_LOADER_INCLUDED

#include "../gli.hpp"
#include "../gtx/loader_dds9.hpp"
#include "../gtx/loader_dds10.hpp"
#include "../gtx/loader_tga.hpp"

namespace gli{
namespace gtx{
namespace loader
{
	texture load(
		std::string const & Filename);

	void save(
		texture const & Image, 
		std::string const & Filename);

}//namespace loader
}//namespace gtx
}//namespace gli

namespace gli{using namespace gtx::loader;}

#include "loader.inl"

#endif//GLI_GTX_LOADER_INCLUDED
