///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-09-08
// Updated : 2010-09-08
// Licence : This source is under MIT License
// File    : gli/gtx/loader.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_GTX_LOADER_INCLUDED
#define GLI_GTX_LOADER_INCLUDED

#include "loader.hpp"

namespace gli{
namespace gtx
{
	namespace loader
	{
		enum format
		{
			DDS,
			TGA
		};

		template<format Format>
		image importFile<Format>(
			std::string const & Filename);

		template<format Format>
		void exportFile<Format>(
			image const & Image, 
			std::string const & Filename);
	}//namespace loader
}//namespace gtx
}//namespace gli

#include "loader.inl"

#endif//GLI_GTX_LOADER_INCLUDED
