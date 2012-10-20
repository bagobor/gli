///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2011-10-07
// Updated : 2011-10-07
// Licence : This source is under MIT licence
// File    : test/core/core.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <gli/gli.hpp>

int test_create_texture_storage()
{
	int Error(0);

	gli::texture2D Texture(
		gli::texture2D::size_type(glm::log2(256.f)), 
		gli::RGBA8U, 
		gli::texture2D::dimensions_type(256));
	gli::texture2D::size_type Levels = Texture.levels();

	assert(!Texture.empty());

	void * Pointer = Texture[0].data<void>();

	glm::u8vec4 TexelA = Texture[0].data<glm::u8vec4>()[0];
	glm::u8vec4 TexelB = Texture[0].data<glm::u8vec4>()[1];
	glm::u8vec4 TexelC = Texture[0].data<glm::u8vec4>()[2];
	glm::u8vec4 TexelD = Texture[0].data<glm::u8vec4>()[3];

	return Error;
}

int main()
{
	int Error(0);

	Error += test_create_texture_storage();
		
	return Error;
}
