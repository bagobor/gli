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

	gli::image ImageA(
		gli::image::dimensions_type(4, 4, 1, 1), 
		gli::RGBA8U);
	gli::image ImageB(
		gli::image::dimensions_type(4, 4, 1, 1), 
		4, 
		gli::image::dimensions_type(1));
	gli::image ImageC = ImageA;

	Error += ImageA == ImageB ? 0 : 1;
	Error += ImageC == ImageB ? 0 : 1;

	return Error;
}

int test_image_data()
{
	int Error(0);

	gli::image ImageA;
	Error += ImageA.empty() ? 0 : 1;
	assert(!Error);

	gli::image ImageB(
		gli::image::dimensions_type(1, 1, 1, 1), 
		sizeof(glm::u8vec4), 
		gli::image::dimensions_type(1, 1, 1, 1));
	Error += ImageB.size() == sizeof(glm::u8vec4) ? 0 : 1;

	*ImageB.data<glm::u8vec4>() = glm::u8vec4(255, 127, 0, 255);
	Error += !ImageB.empty() ? 0 : 1;
	assert(!Error);

	gli::shared_ptr<gli::detail::storage> Storage(new gli::detail::storage(
		2, 1, 1, 
		gli::detail::storage::dimensions3_type(1), 
		sizeof(glm::u8vec4),
		gli::detail::storage::dimensions3_type(1)));

	std::vector<glm::u8vec4> Data(2);
	Data[0] = glm::u8vec4(  0, 127, 255, 255);
	Data[1] = glm::u8vec4(255, 127,   0, 255);

	memcpy(Storage->data(), &Data[0][0], Data.size() * sizeof(glm::u8vec4));

	gli::image ImageC(Storage, gli::detail::view(0, 0, gli::FACE_DEFAULT, 0, 1));
	Error += !ImageC.empty() ? 0 : 1;
	assert(!Error);

	glm::u8vec4 ValueB = *(ImageB.data<glm::u8vec4>() + 0);
	glm::u8vec4 ValueC = *(ImageC.data<glm::u8vec4>() + 1);
	glm::u8vec4 ValueD = *(ImageC.data<glm::u8vec4>() + 0);

	Error += glm::all(glm::equal(ValueB, ValueC)) ? 0 : 1;
	assert(!Error);

	return Error;
}

int test_image_query()
{
	int Error(0);

	gli::image Image(gli::image::dimensions_type(1, 1, 1, 1), sizeof(glm::u8vec4), gli::image::dimensions_type(1, 1, 1, 1));

	Error += Image.size() == sizeof(glm::u8vec4) ? 0 : 1;
	Error += !Image.empty() ? 0 : 1;
	Error += Image.dimensions().x == 1 ? 0 : 1;
	Error += Image.dimensions().y == 1 ? 0 : 1;
	Error += Image.dimensions().z == 1 ? 0 : 1;
	Error += Image.dimensions().w == 1 ? 0 : 1;

	return Error;
}

int main()
{
	int Error(0);

	Error += test_image_ctor();
	Error += test_image_data();
	Error += test_image_query();
		
	return Error;
}

