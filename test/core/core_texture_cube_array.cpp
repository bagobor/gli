///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2011-01-10
// Updated : 2013-01-10
// Licence : This source is under MIT licence
// File    : test/core/texture_cube_array.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <gli/core/texture_cube_array.hpp>

int test_texture_cube_clear()
{
	int Error(0);

	glm::u8vec4 const Orange(255, 127, 0, 255);

	gli::textureCubeArray Texture(
        1,
        1,
		gli::textureCubeArray::size_type(glm::log2(16u) + 1),
		gli::RGBA8U,
		gli::textureCubeArray::dimensions_type(16));

	//Texture.clear<glm::u8vec4>(Cyan);

	return Error;
}

int test_texture_cube_query()
{
	int Error(0);

	gli::textureCubeArray Texture(
        1,
        1,
		gli::textureCube::size_type(2),
		gli::RGBA8U,
		gli::textureCube::dimensions_type(2));

	Error += Texture.size() == sizeof(glm::u8vec4) * 5 ? 0 : 1;
	Error += Texture.format() == gli::RGBA8U ? 0 : 1;
	Error += Texture.levels() == 2 ? 0 : 1;
	Error += !Texture.empty() ? 0 : 1;
	Error += Texture.dimensions().x == 2 ? 0 : 1;
	Error += Texture.dimensions().y == 2 ? 0 : 1;

	return Error;
}

int test_texture_cube_image_access()
{
	int Error(0);

	{
		glm::u8vec4 const Orange(255, 127, 0, 255);

		gli::image Image0(gli::image::dimensions_type(2, 2, 1, 1), sizeof(glm::u8vec4), gli::image::dimensions_type(1));
		for(std::size_t i = 0; i < Image0.size(); ++i)
			*(Image0.data<glm::byte>() + i) = glm::byte(i);

		gli::image Image1(gli::image::dimensions_type(1, 1, 1, 1), sizeof(glm::u8vec4), gli::image::dimensions_type(1));
		for(std::size_t i = 0; i < Image1.size(); ++i)
			*(Image1.data<glm::byte>() + i) = glm::byte(i + 100);

		gli::textureCubeArray Texture(
            1, 1,
			gli::textureCube::size_type(2),
			gli::RGBA8U,
			gli::textureCube::dimensions_type(2));
	}

	{
		gli::textureCubeArray Texture(
            1, 1,
			gli::textureCube::size_type(2),
			gli::RGBA8U,
			gli::textureCube::dimensions_type(2));
		assert(!Texture.empty());

		gli::textureCube TextureCubeA = Texture[0];
		gli::textureCube TextureCubeB = Texture[1];
		
		std::size_t Size0 = TextureCubeA.size();
		std::size_t Size1 = TextureCubeB.size();

		Error += Size0 == sizeof(glm::u8vec4) * 4 ? 0 : 1;
		Error += Size1 == sizeof(glm::u8vec4) * 1 ? 0 : 1;

		*TextureCubeA.data<glm::u8vec4>() = glm::u8vec4(255, 127, 0, 255);
		*TextureCubeB.data<glm::u8vec4>() = glm::u8vec4(0, 127, 255, 255);

		glm::u8vec4 * PointerA = TextureCubeA.data<glm::u8vec4>();
		glm::u8vec4 * PointerB = TextureCubeB.data<glm::u8vec4>();

		glm::u8vec4 const * Pointer0 = Texture.data<glm::u8vec4>() + 0;
		glm::u8vec4 const * Pointer1 = Texture.data<glm::u8vec4>() + 4;

		Error += PointerA == Pointer0 ? 0 : 1;
		Error += PointerB == Pointer1 ? 0 : 1;

		glm::u8vec4 ColorA = *TextureCubeA.data<glm::u8vec4>();
		glm::u8vec4 ColorB = *TextureCubeB.data<glm::u8vec4>();

		glm::u8vec4 Color0 = *Pointer0;
		glm::u8vec4 Color1 = *Pointer1;

		Error += glm::all(glm::equal(Color0, glm::u8vec4(255, 127, 0, 255))) ? 0 : 1;
		Error += glm::all(glm::equal(Color1, glm::u8vec4(0, 127, 255, 255))) ? 0 : 1;
	}

	{
		gli::textureCubeArray TextureCubeArray(
            1, 1,
			gli::textureCube::size_type(1),
			gli::RGBA8U,
			gli::textureCube::dimensions_type(2));

		std::size_t SizeA = TextureCubeArray.size();
		Error += SizeA == sizeof(glm::u8vec4) * 4 ? 0 : 1;

		gli::textureCube TextureCube = TextureCubeArray[0];
		
		std::size_t Size0 = TextureCube.size();
		Error += Size0 == sizeof(glm::u8vec4) * 4 ? 0 : 1;

		*TextureCube.data<glm::u8vec4>() = glm::u8vec4(255, 127, 0, 255);

		glm::u8vec4 * PointerA = TextureCube.data<glm::u8vec4>();
		glm::u8vec4 * Pointer0 = TextureCubeArray.data<glm::u8vec4>() + 0;
		Error += PointerA == Pointer0 ? 0 : 1;

		glm::u8vec4 ColorA = *PointerA;
		glm::u8vec4 Color0 = *Pointer0;
		Error += glm::all(glm::equal(Color0, glm::u8vec4(255, 127, 0, 255))) ? 0 : 1;
	}

	return Error;
}

int test_texture_cube_image_size()
{
	int Error(0);

	struct test
	{
		test(
			gli::format const & Format,
			gli::textureCube::dimensions_type const & Dimensions,
			gli::textureCube::size_type const & Size) :
			Format(Format),
			Dimensions(Dimensions),
			Size(Size)
		{}

		gli::format Format;
		gli::textureCube::dimensions_type Dimensions;
		gli::textureCube::size_type Size;
	};

	std::vector<test> Tests;
	Tests.push_back(test(gli::RGBA8U, gli::textureCube::dimensions_type(4), 64));
	Tests.push_back(test(gli::R8U, gli::textureCube::dimensions_type(4), 16));
	Tests.push_back(test(gli::DXT1, gli::textureCube::dimensions_type(4), 8));
	Tests.push_back(test(gli::DXT1, gli::textureCube::dimensions_type(2), 8));
	Tests.push_back(test(gli::DXT1, gli::textureCube::dimensions_type(1), 8));
	Tests.push_back(test(gli::DXT5, gli::textureCube::dimensions_type(4), 16));

	for(std::size_t i = 0; i < Tests.size(); ++i)
	{
		gli::textureCubeArray Texture(
            1, 1,
			gli::textureCubeArray::size_type(1),
			Tests[i].Format,
			gli::textureCubeArray::dimensions_type(4));

		Error += Texture.size() == Tests[i].Size ? 0 : 1;
		assert(!Error);
	}

	for(std::size_t i = 0; i < Tests.size(); ++i)
	{
		gli::textureCubeArray TextureCubeArray(
            1, 1,
			gli::textureCubeArray::size_type(1),
			Tests[i].Format,
			gli::textureCubeArray::dimensions_type(4));

		gli::textureCube TextureCube = TextureCubeArray[0];

		Error += TextureCube.size() == Tests[i].Size ? 0 : 1;
		assert(!Error);
	}

	return Error;
}

int main()
{
	int Error(0);

	Error += test_texture_cube_image_size();
	Error += test_texture_cube_query();
	Error += test_texture_cube_clear();
	Error += test_texture_cube_image_access();

	return Error;
}

