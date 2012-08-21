///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2011-10-07
// Updated : 2011-10-07
// Licence : This source is under MIT licence
// File    : test/core/image_2d.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <gli/core/image.hpp>

int test_image_ctor()
{
	int Error(0);

	gli::image ImageA;
	Error += ImageA.empty() ? 0 : 1;

	gli::image ImageB(gli::image::dimension_type(1, 1, 1, 1), sizeof(glm::u8vec4));
	*ImageB.data<glm::u8vec4>() = glm::u8vec4(255, 127, 0, 255);

	gli::detail::storage Storage(
		1, gli::FACE_DEFAULT, 1, 
		gli::detail::storage::dimensions3_type(1), 
		sizeof(glm::u8vec4));

	return Error;
}

int main()
{
	int Error = 0;

	Error += test_image_ctor();
		
	return Error;
}

