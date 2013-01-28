#define GLM_SWIZZLE_XYZW
#include <glm/glm.hpp>
#include <glm/gtc/type_precision.hpp>

#include <gli/gli.hpp>
#include <gli/gtx/fetch.hpp>
#include <gli/gtx/gradient.hpp>
#include <gli/gtx/loader_dds10.hpp>

#include <vector>

//#include <boost/format.hpp>

int test_image_wip()
{
	int Error(0);
	//gli::wip::texture2D<glm::u8vec3, gli::wip::plain> Texture;
	//gli::wip::texture2D<glm::u8vec3, gli::wip::plain>::image Mipmap = Texture[0];

	//glm::vec2 Texcoord(0);
	//Texture[0](Texcoord);

	//gli::wip::plain<glm::u8vec3> Surface;
	//gli::wip::fetch(Surface);
	//gli::wip::fetch(Texture);

	return Error;
}

int test_image_export()
{
	int Error(0);
	//gli::texture2D Texture = gli::load<gli::TGA>("../test_rgb8.tga");
	//gli::texture2D TextureMipmaped = gli::generateMipmaps(Texture, 0);

	//gli::save(TextureMipmaped, 0, "../test0.tga");
	//gli::save(TextureMipmaped, 1, "../test1.tga");
	//gli::save(TextureMipmaped, 2, "../test2.tga");
	//gli::save(TextureMipmaped, 3, "../test3.tga");

	return Error;
}

int test_image_export_dds()
{
	int Error(0);

	{
		gli::texture2D Texture(gli::loadStorageDDS("../../data/test_rgb8.dds"));
		assert(!Texture.empty());
		gli::saveStorageDDS(Texture, "../../data/test_dds2ddsEXT.dds");
	}
	{
		gli::texture2D Texture(gli::loadStorageDDS("../../data/test_dxt1.dds"));
		assert(!Texture.empty());
		gli::saveStorageDDS(Texture, "../../data/test_dxt2dxtEXT.dds");
	}
	{
		gli::texture2D Texture(gli::loadStorageDDS("../../data/test_bc1.dds"));
		assert(!Texture.empty());
		gli::saveStorageDDS(Texture, "../../data/test_bc12bc1EXT.dds");
	}

	return Error;
}

int test_image_fetch()
{
	int Error(0);

	gli::texture2D Texture(gli::loadStorageDDS("../../data/test_rgb8.dds"));
	if(!Texture.empty())
	{
		gli::texture2D::dimensions_type Size = Texture.dimensions();

		glm::u8vec3 TexelA = gli::textureLod<glm::u8vec3>(Texture, gli::texture2D::texcoord_type(0.0f, 0.0f), 0);
		//glm::u8vec3 TexelB = gli::textureLod<glm::u8vec3>(Texture, gli::texture2D::texcoord_type(0.5f, 0.5f), 0);

		glm::u8vec3 TexelC = gli::texelFetch<glm::u8vec3>(Texture, gli::texture2D::dimensions_type(7, 7), 0);
		glm::u8vec3 TexelD = gli::texelFetch<glm::u8vec3>(Texture, gli::texture2D::dimensions_type(7, 0), 0);
		glm::u8vec3 TexelE = gli::texelFetch<glm::u8vec3>(Texture, gli::texture2D::dimensions_type(0, 7), 0);
	}

	return Error;
}

int test_image_gradient()
{
	int Error(0);

	{
		gli::texture2D Texture = gli::radial(glm::uvec2(256), glm::vec2(0.25f), 128.0f, glm::vec2(0.5f));
		gli::saveStorageDDS(Texture, "../../data/gradient_radial.dds");
	}

	{
		gli::texture2D Texture = gli::linear(glm::uvec2(256), glm::vec2(0.25f), glm::vec2(0.75f));
		gli::saveStorageDDS(Texture, "../../data/gradient_linear.dds");
	}

	return 0;
}

/*
int test_texture1d()
{
	int Error(0);

	{
		gli::texture1D Texture(
			gli::texture1D::size_type(1), 
			gli::RGBA8U, 
			gli::texture1D::dimensions_type(256));

		for(gli::texture1D::size_type TexelIndex = 0; TexelIndex < Texture.size<glm::u8vec4>(); ++TexelIndex)
			*(Texture.data<glm::u8vec4>() + TexelIndex) = glm::u8vec4(255, 128, 0, 255);

		gli::saveDDS10(Texture, "../../data/texture1D_1level_rgba8u_256.dds");
	}

	{
		gli::texture1D Texture(
			gli::texture1D::size_type(glm::log2(256.f)), 
			gli::RGBA8U, 
			gli::texture1D::dimensions_type(256));

		for(gli::texture1D::size_type TexelIndex = 0; TexelIndex < Texture.size<glm::u8vec4>(); ++TexelIndex)
			*(Texture.data<glm::u8vec4>() + TexelIndex) = glm::u8vec4(255, 128, 0, 255);

		gli::saveDDS10(Texture, "../../data/texture1D_mipmaps_rgba8u_256.dds");
	}

	return 0;
}
*/

int test_texture2d_load()
{
	int Error(0);

	{
		gli::texture2D Texture(gli::loadStorageDDS("../../data/test_rgb8.dds"));

		gli::texture2D::format_type Format = Texture.format();

	}

	return Error;
}

int test_texture2d()
{
	int Error(0);

	{
		gli::texture2D Texture(
			gli::texture2D::size_type(1), 
			gli::RGBA8_UNORM, 
			gli::texture2D::dimensions_type(256));

		for(gli::texture2D::size_type TexelIndex = 0; TexelIndex < Texture.size<glm::u8vec4>(); ++TexelIndex)
			*(Texture.data<glm::u8vec4>() + TexelIndex) = glm::u8vec4(255, 128, 0, 255);

		gli::saveStorageDDS(Texture, "../../data/texture2D_1level_rgba8_unorm_256.dds");
	}

	{
		gli::texture2D Texture(
			gli::texture2D::size_type(1), 
			gli::RGBA16_UNORM, 
			gli::texture2D::dimensions_type(256));

		for(gli::texture2D::size_type TexelIndex = 0; TexelIndex < Texture.size<glm::u16vec4>(); ++TexelIndex)
			*(Texture.data<glm::u16vec4>() + TexelIndex) = glm::u16vec4(65535, 32768, 0, 65535);

		gli::saveStorageDDS(Texture, "../../data/texture2D_1level_rgba16_unorm_256.dds");
	}

	{
		gli::texture2D Texture(
			gli::texture2D::size_type(glm::log2(256.f)), 
			gli::RGBA8_UNORM, 
			gli::texture2D::dimensions_type(256));

		for(gli::texture2D::size_type TexelIndex = 0; TexelIndex < Texture.size<glm::u8vec4>(); ++TexelIndex)
			*(Texture.data<glm::u8vec4>() + TexelIndex) = glm::u8vec4(255, 128, 0, 255);

		gli::saveStorageDDS(Texture, "../../data/texture2D_mipmaps_rgba8_unorm_256.dds");
	}

	{
		gli::texture2D Texture(
			gli::texture2D::size_type(glm::log2(256.f)), 
			gli::RGBA16_UNORM, 
			gli::texture2D::dimensions_type(256));

		for(gli::texture2D::size_type TexelIndex = 0; TexelIndex < Texture.size<glm::u16vec4>(); ++TexelIndex)
			*(Texture.data<glm::u16vec4>() + TexelIndex) = glm::u16vec4(65535, 32768, 0, 65535);

		gli::saveStorageDDS(Texture, "../../data/texture2D_mipmaps_rgba16_unorm_256.dds");
	}

	return 0;
}

int test_texture2DArray()
{
	int Error(0);

	{
		gli::texture2DArray Texture(
			gli::texture2D::size_type(2),
			gli::texture2D::size_type(1), 
			gli::RGBA8_UNORM, 
			gli::texture2D::dimensions_type(256));

		std::vector<glm::u8vec4> Color;
		Color.push_back(glm::u8vec4(255, 128,   0, 255));
		Color.push_back(glm::u8vec4(  0, 128, 255, 255));

		for(gli::texture2DArray::size_type LayerIndex = 0; LayerIndex < Texture.layers(); ++LayerIndex)
		for(gli::texture2D::size_type TexelIndex = 0; TexelIndex < Texture[LayerIndex].size<glm::u8vec4>(); ++TexelIndex)
			*(Texture[LayerIndex].data<glm::u8vec4>() + TexelIndex) = Color[LayerIndex];

		gli::saveStorageDDS(Texture, "../../data/texture2DArray_rgba8u_256.dds");
	}

	return 0;
}

int test_textureCube()
{
	int Error(0);

	{
		gli::textureCube Texture(
			gli::textureCube::size_type(6),
			gli::textureCube::size_type(1), 
			gli::RGBA8_UNORM, 
			gli::textureCube::dimensions_type(256));

		std::vector<glm::u8vec4> Color;
		Color.push_back(glm::u8vec4(255,   0,   0, 255));
		Color.push_back(glm::u8vec4(255, 128,   0, 255));
		Color.push_back(glm::u8vec4(255, 255,   0, 255));
		Color.push_back(glm::u8vec4(  0, 255,   0, 255));
		Color.push_back(glm::u8vec4(  0, 128, 255, 255));
		Color.push_back(glm::u8vec4(  0,   0, 255, 255));

		for(gli::textureCube::size_type FaceIndex = 0; FaceIndex < Texture.faces(); ++FaceIndex)
		for(gli::texture2D::size_type TexelIndex = 0; TexelIndex < Texture[FaceIndex].size<glm::u8vec4>(); ++TexelIndex)
			*(Texture[FaceIndex].data<glm::u8vec4>() + TexelIndex) = Color[FaceIndex];

		gli::saveStorageDDS(Texture, "../../data/textureCube_rgba8u_256.dds");
	}

	return 0;
}

int main()
{
	int Error(0);

	Error += test_texture2d_load();
	Error += test_texture2d();
	Error += test_texture2DArray();
	Error += test_textureCube();
	Error += test_image_wip();
	Error += test_image_fetch();
	Error += test_image_gradient();
	Error += test_image_export_dds();

	return Error;
}
