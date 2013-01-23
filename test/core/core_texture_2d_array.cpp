///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2011-10-11
// Updated : 2013-01-23
// Licence : This source is under MIT licence
// File    : test/core/core_texture_2d_array.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <gli/core/texture2d_array.hpp>

int test_texture2DArray_clear()
{
	int Error(0);

	glm::u8vec4 const Orange(255, 127, 0, 255);

	gli::texture2DArray Texture(
		2,
		gli::texture2DArray::size_type(glm::log2(16u) + 1),
		gli::RGBA8U,
		gli::texture2DArray::dimensions_type(16));

	//Texture.clear<glm::u8vec4>(Cyan);

	return Error;
}

int test_texture2DArray_query()
{
	int Error(0);

	gli::texture2DArray::size_type Layers(2);
	gli::texture2DArray::size_type Levels(2);

	gli::texture2DArray Texture(
		Layers, 
		Levels,
		gli::RGBA8U,
		gli::texture2DArray::dimensions_type(2));

	gli::texture2DArray::size_type Size = Texture.size();

	Error += Size == sizeof(glm::u8vec4) * 5 * Layers ? 0 : 1;
	Error += Texture.format() == gli::RGBA8U ? 0 : 1;
	Error += Texture.layers() == Layers ? 0 : 1;
	Error += Texture.levels() == Levels ? 0 : 1;
	Error += !Texture.empty() ? 0 : 1;
	Error += Texture.dimensions().x == 2 ? 0 : 1;
	Error += Texture.dimensions().y == 2 ? 0 : 1;

	return Error;
}

int test_texture2DArray_access()
{
	int Error(0);

	{
		glm::u8vec4 const Orange(255, 127, 0, 255);

		gli::image Image0(gli::image::dimensions_type(2, 2, 1), sizeof(glm::u8vec4), gli::image::dimensions_type(1));
		for(std::size_t i = 0; i < Image0.size(); ++i)
			*(Image0.data<glm::byte>() + i) = glm::byte(i);

		gli::image Image1(gli::image::dimensions_type(1, 1, 1), sizeof(glm::u8vec4), gli::image::dimensions_type(1));
		for(std::size_t i = 0; i < Image1.size(); ++i)
			*(Image1.data<glm::byte>() + i) = glm::byte(i + 100);

		gli::texture2D Texture(
			gli::texture2D::size_type(2),
			gli::RGBA8U,
			gli::texture2D::dimensions_type(2));

		/// TODO
		//Texture[0] = Image0;
		//Texture[1] = Image1;

		//Error += Texture[0] == Image0 ? 0 : 1;
		//Error += Texture[1] == Image1 ? 0 : 1;
	}

	{
		gli::texture2D Texture(
			gli::texture2D::size_type(2),
			gli::RGBA8U,
			gli::texture2D::dimensions_type(2));
		assert(!Texture.empty());

		gli::image Image0 = Texture[0];
		gli::image Image1 = Texture[1];
		
		std::size_t Size0 = Image0.size();
		std::size_t Size1 = Image1.size();

		Error += Size0 == sizeof(glm::u8vec4) * 4 ? 0 : 1;
		Error += Size1 == sizeof(glm::u8vec4) * 1 ? 0 : 1;

		*Image0.data<glm::u8vec4>() = glm::u8vec4(255, 127, 0, 255);
		*Image1.data<glm::u8vec4>() = glm::u8vec4(0, 127, 255, 255);

		glm::u8vec4 * PointerA = Image0.data<glm::u8vec4>();
		glm::u8vec4 * PointerB = Image1.data<glm::u8vec4>();

		glm::u8vec4 * Pointer0 = Texture.data<glm::u8vec4>() + 0;
		glm::u8vec4 * Pointer1 = Texture.data<glm::u8vec4>() + 4;

		Error += PointerA == Pointer0 ? 0 : 1;
		Error += PointerB == Pointer1 ? 0 : 1;

		glm::u8vec4 ColorA = *Image0.data<glm::u8vec4>();
		glm::u8vec4 ColorB = *Image1.data<glm::u8vec4>();

		glm::u8vec4 Color0 = *Pointer0;
		glm::u8vec4 Color1 = *Pointer1;

		Error += glm::all(glm::equal(Color0, glm::u8vec4(255, 127, 0, 255))) ? 0 : 1;
		Error += glm::all(glm::equal(Color1, glm::u8vec4(0, 127, 255, 255))) ? 0 : 1;
	}

	{
		gli::texture2D Texture(
			gli::texture2D::size_type(1),
			gli::RGBA8U,
			gli::texture2D::dimensions_type(2));

		std::size_t SizeA = Texture.size();
		Error += SizeA == sizeof(glm::u8vec4) * 4 ? 0 : 1;

		gli::image Image0 = Texture[0];
		
		std::size_t Size0 = Image0.size();
		Error += Size0 == sizeof(glm::u8vec4) * 4 ? 0 : 1;

		*Image0.data<glm::u8vec4>() = glm::u8vec4(255, 127, 0, 255);

		glm::u8vec4 * PointerA = Image0.data<glm::u8vec4>();
		glm::u8vec4 * Pointer0 = Texture.data<glm::u8vec4>() + 0;
		Error += PointerA == Pointer0 ? 0 : 1;

		glm::u8vec4 ColorA = *PointerA;
		glm::u8vec4 Color0 = *Pointer0;
		Error += glm::all(glm::equal(Color0, glm::u8vec4(255, 127, 0, 255))) ? 0 : 1;
	}

	return Error;
}

int test_texture2DArray_size()
{
	int Error(0);

	struct test
	{
		test(
			gli::format const & Format,
			gli::texture2D::dimensions_type const & Dimensions,
			gli::texture2D::size_type const & Size) :
			Format(Format),
			Dimensions(Dimensions),
			Size(Size)
		{}

		gli::format Format;
		gli::texture2D::dimensions_type Dimensions;
		gli::texture2D::size_type Size;
	};

	std::vector<test> Tests;
	Tests.push_back(test(gli::RGBA8U, gli::texture2D::dimensions_type(4), 64));
	Tests.push_back(test(gli::R8U, gli::texture2D::dimensions_type(4), 16));
	Tests.push_back(test(gli::DXT1, gli::texture2D::dimensions_type(4), 8));
	Tests.push_back(test(gli::DXT1, gli::texture2D::dimensions_type(2), 8));
	Tests.push_back(test(gli::DXT1, gli::texture2D::dimensions_type(1), 8));
	Tests.push_back(test(gli::DXT5, gli::texture2D::dimensions_type(4), 16));

	for(std::size_t i = 0; i < Tests.size(); ++i)
	{
		gli::texture2D Texture(
			gli::texture2D::size_type(1),
			Tests[i].Format,
			gli::texture2D::dimensions_type(4));

		Error += Texture.size() == Tests[i].Size ? 0 : 1;
		assert(!Error);
	}

	for(std::size_t i = 0; i < Tests.size(); ++i)
	{
		gli::texture2D Texture(
			gli::texture2D::size_type(1),
			Tests[i].Format,
			gli::texture2D::dimensions_type(4));

		gli::image Image = Texture[0];

		Error += Image.size() == Tests[i].Size ? 0 : 1;
		assert(!Error);
	}

	return Error;
}

int main()
{
	int Error(0);

	Error += test_texture2DArray_size();
	Error += test_texture2DArray_query();
	Error += test_texture2DArray_clear();
	Error += test_texture2DArray_access();

	return Error;
}

