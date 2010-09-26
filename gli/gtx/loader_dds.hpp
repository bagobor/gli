///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-09-08
// Updated : 2010-09-08
// Licence : This source is under MIT License
// File    : gli/gtx/loader_dds.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_GTX_LOADER_DDS_INCLUDED
#define GLI_GTX_LOADER_DDS_INCLUDED

#include "loader.hpp"

namespace gli{
namespace gtx
{
	namespace loader
	{
		template<>
		image importFile<DDS>(
			std::string const & Filename);

		template<>
		void exportFile<DDS>(
			image const & Image, 
			std::string const & Filename);

	}//namespace loader
}//namespace gtx
}//namespace gli

#include "loader_dds.inl"

#endif//GLI_GTX_LOADER_DDS_INCLUDED
