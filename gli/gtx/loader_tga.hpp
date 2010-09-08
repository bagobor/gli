///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-09-08
// Updated : 2010-09-08
// Licence : This source is under MIT License
// File    : gli/gtx/loader_tga.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_GTX_LOADER_TGA_INCLUDED
#define GLI_GTX_LOADER_TGA_INCLUDED

#include "loader.hpp"

namespace gli{
namespace gtx
{
	namespace loader
	{
		template<>
		image importFile<TGA>(
			std::string const & Filename);

		template<>
		void exportFile<TGA>(
			image const & Image, 
			std::string const & Filename);

	}//namespace loader
}//namespace gtx
}//namespace gli

#include "loader_tga.inl"

namespace gli{using namespace gtx::loader;}

#endif//GLI_GTX_LOADER_TGA_INCLUDED
