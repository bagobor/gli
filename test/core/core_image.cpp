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
	assert(!Error);

	gli::image ImageB(gli::image::dimensions_type(1, 1, 1, 1), sizeof(glm::u8vec4));
	*ImageB.data<glm::u8vec4>() = glm::u8vec4(255, 127, 0, 255);
	Error += !ImageB.empty() ? 0 : 1;
	assert(!Error);

	gli::shared_ptr<gli::detail::storage> Storage(new gli::detail::storage(
		2, gli::FACE_DEFAULT, 1, 
		gli::detail::storage::dimensions3_type(1), 
		sizeof(glm::u8vec4)));

	std::vector<glm::u8vec4> Data(2);
	Data[0] = glm::u8vec4(  0, 127, 255, 255);
	Data[1] = glm::u8vec4(255, 127,   0, 255);

	memcpy(Storage->data(), &Data[0][0], Data.size() * sizeof(glm::u8vec4));

	gli::image ImageC(Storage);
	Error += !ImageC.empty() ? 0 : 1;
	assert(!Error);

	glm::u8vec4 ValueB = *(ImageB.data<glm::u8vec4>() + 0);
	glm::u8vec4 ValueC = *(ImageC.data<glm::u8vec4>() + 1);
	glm::u8vec4 ValueD = *(ImageC.data<glm::u8vec4>() + 0);

	Error += glm::all(glm::equal(ValueB, ValueC)) ? 0 : 1;
	assert(!Error);

	return Error;
}

int main()
{
	int Error(0);

	Error += test_image_ctor();
		
	return Error;
}

