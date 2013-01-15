///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2011-01-10
// Updated : 2013-01-10
// Licence : This source is under MIT licence
// File    : test/core/texture_cube_array.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <gli/core/texture_cube_array.hpp>

int test_textureCubeArray_query()
{
	int Error(0);

	{
		gli::textureCubeArray TextureCubeArray(
			1, 
			6,
			gli::textureCubeArray::size_type(2),
			gli::RGBA8U,
			gli::textureCubeArray::dimensions_type(2));

		Error += TextureCubeArray.size() == sizeof(glm::u8vec4) * 5 * 6 ? 0 : 1;
		Error += TextureCubeArray.format() == gli::RGBA8U ? 0 : 1;
		Error += TextureCubeArray.levels() == 2 ? 0 : 1;
		Error += !TextureCubeArray.empty() ? 0 : 1;
		Error += TextureCubeArray.dimensions().x == 2 ? 0 : 1;
		Error += TextureCubeArray.dimensions().y == 2 ? 0 : 1;
	}

	{
		gli::image Image(
			gli::RGBA8U,
			gli::image::dimensions_type(2, 2, 1));

		gli::texture2D Texture2D(
			gli::texture2D::size_type(1),
			gli::RGBA8U,
			gli::texture2D::dimensions_type(2));

		gli::textureCube TextureCube(
			1,
			gli::textureCube::size_type(1),
			gli::RGBA8U,
			gli::textureCube::dimensions_type(2));

		gli::textureCubeArray TextureCubeArray(
			1, 
			1,
			gli::textureCubeArray::size_type(1),
			gli::RGBA8U,
			gli::textureCubeArray::dimensions_type(2));

		std::size_t ImageSize = Image.size();
		std::size_t Texture2DSize = Texture2D.size();
		std::size_t TextureCubeSize = TextureCube.size();
		std::size_t TextureCubeArraySize = TextureCubeArray.size();

		Error += ImageSize == sizeof(glm::u8vec4) * 4 * 1 ? 0 : 1;
		Error += !Image.empty() ? 0 : 1;
		Error += Image.dimensions().x == 2 ? 0 : 1;
		Error += Image.dimensions().y == 2 ? 0 : 1;

		Error += Texture2DSize == sizeof(glm::u8vec4) * 4 * 1 ? 0 : 1;
		Error += Texture2D.format() == gli::RGBA8U ? 0 : 1;
		Error += Texture2D.levels() == 1 ? 0 : 1;
		Error += !Texture2D.empty() ? 0 : 1;
		Error += Texture2D.dimensions().x == 2 ? 0 : 1;
		Error += Texture2D.dimensions().y == 2 ? 0 : 1;

		Error += TextureCubeSize == sizeof(glm::u8vec4) * 4 * 1 ? 0 : 1;
		Error += TextureCube.format() == gli::RGBA8U ? 0 : 1;
		Error += TextureCube.levels() == 1 ? 0 : 1;
		Error += !TextureCube.empty() ? 0 : 1;
		Error += TextureCube.dimensions().x == 2 ? 0 : 1;
		Error += TextureCube.dimensions().y == 2 ? 0 : 1;

		Error += TextureCubeArraySize == sizeof(glm::u8vec4) * 4 * 1 ? 0 : 1;
		Error += TextureCubeArray.format() == gli::RGBA8U ? 0 : 1;
		Error += TextureCubeArray.levels() == 1 ? 0 : 1;
		Error += !TextureCubeArray.empty() ? 0 : 1;
		Error += TextureCubeArray.dimensions().x == 2 ? 0 : 1;
		Error += TextureCubeArray.dimensions().y == 2 ? 0 : 1;
	}

	{
		gli::textureCubeArray TextureCubeArray(
			2, 
			1,
			gli::textureCubeArray::size_type(1),
			gli::RGBA8U,
			gli::textureCubeArray::dimensions_type(2));

		std::size_t TextureCubeArraySize = TextureCubeArray.size();

		Error += TextureCubeArraySize == sizeof(glm::u8vec4) * 4 * 2 ? 0 : 1;
		Error += TextureCubeArray.format() == gli::RGBA8U ? 0 : 1;
		Error += TextureCubeArray.levels() == 1 ? 0 : 1;
		Error += !TextureCubeArray.empty() ? 0 : 1;
		Error += TextureCubeArray.dimensions().x == 2 ? 0 : 1;
		Error += TextureCubeArray.dimensions().y == 2 ? 0 : 1;
	}

	return Error;
}

int test_textureCubeArray_textureCube_access()
{
	int Error(0);

	{
		gli::texture2D Texture2DA(1, gli::RGBA8U, gli::texture2D::dimensions_type(2, 2));
		for(std::size_t i = 0; i < Texture2DA.size(); ++i)
			*(Texture2DA.data<glm::byte>() + i) = glm::byte(i);

		gli::texture2D Texture2DB(1, gli::RGBA8U, gli::texture2D::dimensions_type(2, 2));
		for(std::size_t i = 0; i < Texture2DB.size(); ++i)
			*(Texture2DB.data<glm::byte>() + i) = glm::byte(i + 100);

		gli::textureCubeArray TextureCubeArray(
			1,
			6,
			gli::textureCubeArray::size_type(2),
			gli::RGBA8U,
			gli::textureCubeArray::dimensions_type(2));

		/// Todo
		/// gli::copy(TextureCube, 0, Texture2DA);
		/// gli::copy(TextureCube, 1, Texture2DB);

		/// Error += TextureCube[0] == Texture2DA ? 0 : 1;
		/// Error += TextureCube[1] == Texture2DB ? 0 : 1;
	}

	{
		gli::textureCubeArray TextureCubeArray(
			1,
			6,
			gli::textureCubeArray::size_type(2),
			gli::RGBA8U,
			gli::textureCubeArray::dimensions_type(2));
		assert(!TextureCubeArray.empty());

		gli::textureCube TextureA = TextureCubeArray[0];
		
		std::size_t Size0 = TextureA.size();

		Error += Size0 == sizeof(glm::u8vec4) * 4 ? 0 : 1;

		*TextureA.data<glm::u8vec4>() = glm::u8vec4(255, 127, 0, 255);

		glm::u8vec4 * PointerA = TextureA.data<glm::u8vec4>();

		glm::u8vec4 * Pointer0 = TextureCubeArray.data<glm::u8vec4>() + 0;

		Error += PointerA == Pointer0 ? 0 : 1;

		glm::u8vec4 ColorA = *TextureA.data<glm::u8vec4>();

		glm::u8vec4 Color0 = *Pointer0;

		Error += glm::all(glm::equal(Color0, glm::u8vec4(255, 127, 0, 255))) ? 0 : 1;
	}

	{
		gli::textureCubeArray TextureCubeArray(
			1,
			6,
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

int test_textureCubeArray_textureCube_size()
{
	int Error(0);

	struct test
	{
		test(
			gli::format const & Format,
			gli::textureCubeArray::dimensions_type const & Dimensions,
			gli::textureCubeArray::size_type const & Size) :
			Format(Format),
			Dimensions(Dimensions),
			Size(Size)
		{}

		gli::format Format;
		gli::textureCubeArray::dimensions_type Dimensions;
		gli::textureCubeArray::size_type Size;
	};

	std::vector<test> Tests;
	Tests.push_back(test(gli::RGBA8U, gli::textureCubeArray::dimensions_type(4), 384));
	Tests.push_back(test(gli::R8U, gli::textureCubeArray::dimensions_type(4), 96));
	Tests.push_back(test(gli::DXT1, gli::textureCubeArray::dimensions_type(4), 48));
	Tests.push_back(test(gli::DXT1, gli::textureCubeArray::dimensions_type(2), 48));
	Tests.push_back(test(gli::DXT1, gli::textureCubeArray::dimensions_type(1), 48));
	Tests.push_back(test(gli::DXT5, gli::textureCubeArray::dimensions_type(4), 96));

	for(std::size_t i = 0; i < Tests.size(); ++i)
	{
		gli::textureCubeArray Texture(
			1,
			6,
			gli::textureCubeArray::size_type(1),
			Tests[i].Format,
			gli::textureCubeArray::dimensions_type(4));

		gli::textureCubeArray::size_type Size = Texture.size();
		Error += Size == Tests[i].Size ? 0 : 1;
		assert(!Error);
	}

	return Error;
}

int main()
{
	int Error(0);

	Error += test_textureCubeArray_textureCube_size();
	Error += test_textureCubeArray_query();
	Error += test_textureCubeArray_textureCube_access();

	return Error;
}


