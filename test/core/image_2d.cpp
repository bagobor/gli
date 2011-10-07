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

	glm::u8vec4 const Orange(255, 127, 0, 255);
	glm::u8vec4 const Cyan(0, 127, 255, 255);

	gli::image2D Image(gli::RGBA8U, gli::image2D::dimensions_type(16), Orange);
	glm::u8vec4 TexelA = Image.load<glm::u8vec4>(gli::image2D::dimensions_type(0));
	Error += TexelA == Orange ? 0 : 1;

	Image.clear<glm::u8vec4>(Cyan);

	glm::u8vec4 TexelB = Image.load<glm::u8vec4>(gli::image2D::dimensions_type(0, 0));
	Error += TexelB == Cyan ? 0 : 1;
	glm::u8vec4 TexelC = Image.load<glm::u8vec4>(gli::image2D::dimensions_type(1, 0));
	Error += TexelC == Cyan ? 0 : 1;
	glm::u8vec4 TexelD = Image.load<glm::u8vec4>(gli::image2D::dimensions_type(0, 1));
	Error += TexelD == Cyan ? 0 : 1;
	glm::u8vec4 TexelE = Image.load<glm::u8vec4>(gli::image2D::dimensions_type(15, 15));
	Error += TexelE == Cyan ? 0 : 1;

	return Error;
}

int test_image_2d_load_store()
{
	int Error = 0;

	gli::image2D Image(gli::RGBA8U, gli::image2D::dimensions_type(16), glm::u8vec4(255, 127, 0, 255));
	glm::u8vec4 TexelA = Image.load<glm::u8vec4>(gli::image2D::dimensions_type(0));
	Error += TexelA == glm::u8vec4(255, 127, 0, 255) ? 0 : 1;

	Image.store<glm::u8vec4>(gli::image2D::dimensions_type(15), glm::u8vec4(0, 127, 255, 255));
	glm::u8vec4 TexelB = Image.load<glm::u8vec4>(gli::image2D::dimensions_type(15));
	Error += TexelB == glm::u8vec4(0, 127, 255, 255) ? 0 : 1;

	glm::u8vec4 TexelC = Image.load<glm::u8vec4>(gli::image2D::dimensions_type(15, 14));
	Error += TexelC == glm::u8vec4(255, 127, 0, 255) ? 0 : 1;

	glm::u8vec4 TexelD = Image.load<glm::u8vec4>(gli::image2D::dimensions_type(14, 15));
	Error += TexelD == glm::u8vec4(255, 127, 0, 255) ? 0 : 1;

	return Error;
}

int test_image_2d_copy()
{
	int Error = 0;

	gli::image2D Image32(
		gli::RGBA8U, 
		gli::image2D::dimensions_type(4), 
		glm::u8vec4(1, 2, 3, 4));
	gli::image2D Image16(
		gli::RGBA8U, 
		gli::image2D::dimensions_type(2), 
		glm::u8vec4(5, 6, 7, 8));

	Image32.copy(
		Image16, 
		gli::image2D::dimensions_type(0),
		gli::image2D::dimensions_type(1),
		Image16.dimensions());

	glm::u8vec4 TexelA = Image32.load<glm::u8vec4>(gli::image2D::dimensions_type(1, 1));
	Error += TexelA == glm::u8vec4(5, 6, 7, 8) ? 0 : 1;

	glm::u8vec4 TexelB = Image32.load<glm::u8vec4>(gli::image2D::dimensions_type(0, 0));
	Error += TexelB == glm::u8vec4(1, 2, 3, 4) ? 0 : 1;

	//for(std::size_t i = 0; i < Image32.size(); ++i)
	//{
	//	glm::u8vec4 TexelA = Image32.data<glm::u8vec4>()[i];
	//	printf("rgba(%d, %d, %d, %d), ", TexelA.r, TexelA.g, TexelA.b, TexelA.a);
	//	if(!((i + 1) % 4))
	//		printf("\n");
	//}

	return Error;
}

int main()
{
	int Error = 0;

	Error += test_image_2d_clear();
	Error += test_image_2d_load_store();
	Error += test_image_2d_copy();
		
	return Error;
}

