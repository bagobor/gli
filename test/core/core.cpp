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
	int Error = 0;

	gli::texture2D Texture(
		gli::texture2D::size_type(glm::log2(256.f)), 
		gli::RGBA8U, 
		gli::texture2D::dimensions_type(256));
	gli::texture2D::size_type Levels = Texture.levels();

	void * Pointer = Texture[0].data();

	glm::u8vec4 TexelA = Texture[0].data<glm::u8vec4>()[0];
	glm::u8vec4 TexelB = Texture[0].data<glm::u8vec4>()[1];
	glm::u8vec4 TexelC = Texture[0].data<glm::u8vec4>()[2];
	glm::u8vec4 TexelD = Texture[0].data<glm::u8vec4>()[3];

	return Error;
}

int test_create_texture_from_image()
{
	int Error = 0;

	gli::texture2D Texture(1, gli::RGBA8U, gli::texture2D::dimensions_type(256));

	gli::image2D ImageA(gli::RGBA8U, gli::image2D::dimensions_type(256));
	gli::image2D ImageB(gli::RGBA8U, gli::image2D::dimensions_type(256), glm::u8vec4(255, 127, 0, 255));

	Texture[0] = ImageB;

	glm::u8vec4 TexelA = ((glm::u8vec4 const * const)Texture[0].data())[0];
	glm::u8vec4 TexelB = ((glm::u8vec4 const * const)Texture[0].data())[1];
	glm::u8vec4 TexelC = ((glm::u8vec4 const * const)Texture[0].data())[2];
	glm::u8vec4 TexelD = ((glm::u8vec4 const * const)Texture[0].data())[3];

	glm::u8vec4 Texel0 = ((glm::u8vec4 const * const)ImageB.data())[0];
	glm::u8vec4 Texel1 = ((glm::u8vec4 const * const)ImageB.data())[1];
	glm::u8vec4 Texel2 = ((glm::u8vec4 const * const)ImageB.data())[2];
	glm::u8vec4 Texel3 = ((glm::u8vec4 const * const)ImageB.data())[3];

	Error += TexelA == Texel0 ? 0 : 1;
	Error += TexelB == Texel1 ? 0 : 1;
	Error += TexelC == Texel2 ? 0 : 1;
	Error += TexelD == Texel3 ? 0 : 1;

	return Error;
}

int main()
{
	int Error = 0;

	Error += test_create_texture_storage();
	Error += test_create_texture_from_image();
		
	return Error;
}
