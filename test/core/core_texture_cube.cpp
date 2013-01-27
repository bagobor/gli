///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2011-01-10
// Updated : 2013-01-10
// Licence : This source is under MIT licence
// File    : test/core/texture_cube.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <gli/core/texture_cube.hpp>

int test_textureCube_query()
{
	int Error(0);

	gli::textureCube Texture(
		6,
		gli::textureCube::size_type(2),
		gli::RGBA8U,
		gli::textureCube::dimensions_type(2));

	Error += Texture.size() == sizeof(glm::u8vec4) * 5 * 6 ? 0 : 1;
	Error += Texture.format() == gli::RGBA8U ? 0 : 1;
	Error += Texture.levels() == 2 ? 0 : 1;
	Error += !Texture.empty() ? 0 : 1;
	Error += Texture.dimensions().x == 2 ? 0 : 1;
	Error += Texture.dimensions().y == 2 ? 0 : 1;

	return Error;
}

int test_textureCube_texture2D_access()
{
	int Error(0);

	{
		gli::texture2D Texture2DA(1, gli::RGBA8U, gli::texture2D::dimensions_type(2, 2));
		for(std::size_t i = 0; i < Texture2DA.size(); ++i)
			*(Texture2DA.data<glm::byte>() + i) = glm::byte(i);

		gli::texture2D Texture2DB(1, gli::RGBA8U, gli::texture2D::dimensions_type(2, 2));
		for(std::size_t i = 0; i < Texture2DB.size(); ++i)
			*(Texture2DB.data<glm::byte>() + i) = glm::byte(i + 100);

		gli::textureCube TextureCube(
			6,
			gli::textureCube::size_type(2),
			gli::RGBA8U,
			gli::textureCube::dimensions_type(2));

		/// Todo
		/// gli::copy(TextureCube, 0, Texture2DA);
		/// gli::copy(TextureCube, 1, Texture2DB);

		/// Error += TextureCube[0] == Texture2DA ? 0 : 1;
		/// Error += TextureCube[1] == Texture2DB ? 0 : 1;
	}

	{
		gli::textureCube TextureCube(
			6,
			gli::textureCube::size_type(1),
			gli::RGBA8U,
			gli::textureCube::dimensions_type(2));
		assert(!TextureCube.empty());

		std::vector<glm::u8vec4> Colors;
		Colors.push_back(glm::u8vec4(255,   0,   0, 255));
		Colors.push_back(glm::u8vec4(255, 255,   0, 255));
		Colors.push_back(glm::u8vec4(  0, 255,   0, 255));
		Colors.push_back(glm::u8vec4(  0, 255, 255, 255));
		Colors.push_back(glm::u8vec4(  0,   0, 255, 255));
		Colors.push_back(glm::u8vec4(255, 255,   0, 255));

		for(std::size_t ColorIndex = 0; ColorIndex < Colors.size(); ++ColorIndex)
		{
			gli::texture2D & Texture2D = TextureCube[ColorIndex];
			for(std::size_t PixelIndex = 0; PixelIndex < 4; ++PixelIndex)
			{
				glm::u8vec4 Color = Colors[ColorIndex];
				*(Texture2D.data<glm::u8vec4>() + PixelIndex) = Color;
			}
		}

		for(std::size_t TexelIndex = 0; TexelIndex < TextureCube.size() / sizeof(glm::u8vec4); ++TexelIndex)
			Error += glm::all(glm::equal(*(TextureCube.data<glm::u8vec4>() + TexelIndex), Colors[TexelIndex / 4])) ? 0 : 1;
	}

	{
		gli::textureCube TextureCube(
			6,
			gli::textureCube::size_type(2),
			gli::RGBA8U,
			gli::textureCube::dimensions_type(2));
		assert(!TextureCube.empty());

		gli::texture2D TextureA = TextureCube[0];
		gli::texture2D TextureB = TextureCube[1];
		
		std::size_t Size0 = TextureA.size();
		std::size_t Size1 = TextureB.size();

		Error += Size0 == sizeof(glm::u8vec4) * 5 ? 0 : 1;
		Error += Size1 == sizeof(glm::u8vec4) * 5 ? 0 : 1;

		*TextureA.data<glm::u8vec4>() = glm::u8vec4(255, 127, 0, 255);
		*TextureB.data<glm::u8vec4>() = glm::u8vec4(0, 127, 255, 255);

		glm::u8vec4 * PointerA = TextureA.data<glm::u8vec4>();
		glm::u8vec4 * PointerB = TextureB.data<glm::u8vec4>();

		glm::u8vec4 * Pointer0 = TextureCube.data<glm::u8vec4>() + 0;
		glm::u8vec4 * Pointer1 = TextureCube.data<glm::u8vec4>() + 5;

		Error += PointerA == Pointer0 ? 0 : 1;
		Error += PointerB == Pointer1 ? 0 : 1;

		glm::u8vec4 ColorA = *TextureA.data<glm::u8vec4>();
		glm::u8vec4 ColorB = *TextureB.data<glm::u8vec4>();

		glm::u8vec4 Color0 = *Pointer0;
		glm::u8vec4 Color1 = *Pointer1;

		Error += glm::all(glm::equal(Color0, glm::u8vec4(255, 127, 0, 255))) ? 0 : 1;
		Error += glm::all(glm::equal(Color1, glm::u8vec4(0, 127, 255, 255))) ? 0 : 1;
	}

	{
		gli::textureCube TextureCube(
			1,
			gli::textureCube::size_type(1),
			gli::RGBA8U,
			gli::textureCube::dimensions_type(2));

		std::size_t SizeA = TextureCube.size();
		Error += SizeA == sizeof(glm::u8vec4) * 4 ? 0 : 1;

		gli::texture2D Texture2D = TextureCube[0];
		
		std::size_t Size0 = Texture2D.size();
		Error += Size0 == sizeof(glm::u8vec4) * 4 ? 0 : 1;

		*Texture2D.data<glm::u8vec4>() = glm::u8vec4(255, 127, 0, 255);

		glm::u8vec4 * PointerA = Texture2D.data<glm::u8vec4>();
		glm::u8vec4 * Pointer0 = TextureCube.data<glm::u8vec4>();
		Error += PointerA == Pointer0 ? 0 : 1;

		glm::u8vec4 ColorA = *PointerA;
		glm::u8vec4 Color0 = *Pointer0;
		Error += glm::all(glm::equal(ColorA, glm::u8vec4(255, 127, 0, 255))) ? 0 : 1;
		Error += glm::all(glm::equal(Color0, glm::u8vec4(255, 127, 0, 255))) ? 0 : 1;
	}

	return Error;
}

int test_textureCube_texture2D_size()
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
	Tests.push_back(test(gli::RGBA8U, gli::textureCube::dimensions_type(4), 384));
	Tests.push_back(test(gli::R8U, gli::textureCube::dimensions_type(4), 96));
	Tests.push_back(test(gli::RGBA_DXT1, gli::textureCube::dimensions_type(4), 48));
	Tests.push_back(test(gli::RGBA_DXT1, gli::textureCube::dimensions_type(2), 48));
	Tests.push_back(test(gli::RGBA_DXT1, gli::textureCube::dimensions_type(1), 48));
	Tests.push_back(test(gli::RGBA_DXT5, gli::textureCube::dimensions_type(4), 96));

	for(std::size_t i = 0; i < Tests.size(); ++i)
	{
		gli::textureCube Texture(
			6,
			gli::textureCube::size_type(1),
			Tests[i].Format,
			gli::textureCube::dimensions_type(4));

		gli::textureCube::size_type Size = Texture.size();
		Error += Size == Tests[i].Size ? 0 : 1;
		assert(!Error);
	}

	return Error;
}

int main()
{
	int Error(0);

	Error += test_textureCube_texture2D_size();
	Error += test_textureCube_query();
	Error += test_textureCube_texture2D_access();

	return Error;
}

