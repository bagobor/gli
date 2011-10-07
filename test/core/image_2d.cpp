///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2011-10-07
// Updated : 2011-10-07
// Licence : This source is under MIT licence
// File    : test/core/image_2d.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <gli/gli.hpp>

int test_image_2d_clear()
{
	int Error = 0;

	gli::image2D Image(gli::RGBA8U, gli::image2D::dimensions_type(16), glm::u8vec4(255, 127, 0, 255));

	return Error;
}

int main()
{
	int Error = 0;

	Error += test_image_2d_clear();
		
	return Error;
}

