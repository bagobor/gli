///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-12-19
// Updated : 2010-01-09
// Licence : This source is under MIT License
// File    : gli/operation.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_OPERATION_INCLUDED
#define GLI_OPERATION_INCLUDED

#include "image.hpp"

namespace gli
{
	texture duplicate(texture const & Image);
	texture flip(texture const & Image);
	texture mirror(texture const & Image);
	texture swizzle(
		texture const & Image, 
		glm::uvec4 const & Channel);
	texture crop(
		texture const & Image, 
		glm::uvec2 const & Position,
		glm::uvec2 const & Size);

	texture::image crop(
		texture::image const & Mipmap, 
		glm::uvec2 const & Position,
		glm::uvec2 const & Size);

	texture::image copy(
		texture::image const & SrcMipmap, 
		glm::uvec2 const & SrcPosition,
		glm::uvec2 const & SrcSize,
		texture::image & DstMipmap, 
		glm::uvec2 const & DstPosition);

	//image operator+(image const & MipmapA, image const & MipmapB);
	//image operator-(image const & MipmapA, image const & MipmapB);
	//image operator*(image const & MipmapA, image const & MipmapB);
	//image operator/(image const & MipmapA, image const & MipmapB);

	//namespace wip
	//{
	//	template <typename GENTYPE, template <typename> class SURFACE>
	//	GENTYPE fetch(SURFACE<GENTYPE> const & Image)
	//	{
	//		return GENTYPE();
	//	}

	//	template
	//	<
	//		typename GENTYPE, 
	//		template 
	//		<
	//			typename
	//		>
	//		class SURFACE,
	//		template 
	//		<
	//			typename, 
	//			template 
	//			<
	//				typename
	//			>
	//			class
	//		> 
	//		class IMAGE
	//	>
	//	GENTYPE fetch(IMAGE<GENTYPE, SURFACE> const & Image)
	//	{
	//		return GENTYPE();
	//	}
	//}//namespace wip

}//namespace gli

#include "operation.inl"

#endif//GLI_OPERATION_INCLUDED
