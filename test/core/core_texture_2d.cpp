///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2011-10-11
// Updated : 2011-10-11
// Licence : This source is under MIT licence
// File    : test/core/texture_2d.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <gli/gli.hpp>

int test_texture_2d_clear()
{
	int Error = 0;

	glm::u8vec4 const Orange(255, 127, 0, 255);

	gli::texture2D Texture(gli::texture2D::size_type(glm::log2(16u)), gli::RGBA8U, gli::texture2D::dimensions_type(16));

	//Texture.clear<glm::u8vec4>(Cyan);

	return Error;
}


int main()
{
	int Error = 0;

	Error += test_texture_2d_clear();

	return Error;
}

