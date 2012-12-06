#define GLM_SWIZZLE_XYZW
#include <glm/glm.hpp>
#include <glm/gtc/type_precision.hpp>

#include <gli/gli.hpp>
#include <gli/gtx/fetch.hpp>
#include <gli/gtx/gradient.hpp>
#include <gli/gtx/loader.hpp>

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
		gli::texture2D Texture = gli::loadDDS9("../../data/test_rgb8.dds");
		assert(!Texture.empty());
		gli::saveDDS9(Texture, "../../data/test_dds2ddsEXT.dds");
	}
	{
		gli::texture2D Texture = gli::loadDDS9("../../data/test_dxt1.dds");
		assert(!Texture.empty());
		gli::saveDDS9(Texture, "../../data/test_dxt2dxtEXT.dds");
	}
	{
		gli::texture2D Texture = gli::loadDDS10("../../data/test_bc1.dds");
		assert(!Texture.empty());
		gli::saveDDS10(Texture, "../../data/test_bc12bc1EXT.dds");
	}

	return Error;
}

int test_image_fetch()
{
	int Error(0);

	gli::texture2D Texture = gli::loadDDS10("../../data/test_rgb8.dds");
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
		gli::saveDDS10(Texture, "../../data/gradient_radial.dds");
	}

	{
		gli::texture2D Texture = gli::linear(glm::uvec2(256), glm::vec2(0.25f), glm::vec2(0.75f));
		gli::saveDDS10(Texture, "../../data/gradient_linear.dds");
	}

	return 0;
}

int main()
{
	int Error(0);
/*
	glm::vec4 v1(1, 2, 3, 4);
	glm::vec4 v2;
	glm::vec4 v3;
	glm::vec4 v4;
	v2.wyxz = v1.zyxw;
	v3 = v1.xzyw;
	v4.xzyw = v1;

	gli::texture2D TextureBC7 = gli::load("../data/kueken256-bc7.dds");
	assert(!TextureBC7.empty());

	gli::texture2D TextureBC7_0 = gli::load("../data/kueken256-bc7-0.dds");
	assert(!TextureBC7_0.empty());

	TextureBC7[0] = TextureBC7_0[0];
	gli::save(TextureBC7, "../data/kueken256-bc7-saved.dds");

	{
		gli::texture2D TextureLoad[] =
		{
			gli::loadDDS10("../data/kueken256-rgb8_BC7.dds"), 
			gli::loadDDS10("../data/kueken128-rgb8_BC7.dds"), 
			gli::loadDDS10("../data/kueken64-rgb8_BC7.dds"), 
			gli::loadDDS10("../data/kueken32-rgb8_BC7.dds"), 
			gli::loadDDS10("../data/kueken16-rgb8_BC7.dds"), 
			gli::loadDDS10("../data/kueken8-rgb8_BC7.dds"), 
			gli::loadDDS10("../data/kueken4-rgb8_BC7.dds"), 
			gli::loadDDS10("../data/kueken4-rgb8_BC7.dds"), 
			gli::loadDDS10("../data/kueken4-rgb8_BC7.dds")
		};

		gli::texture2D Texture(sizeof(TextureLoad) / sizeof(gli::texture2D), gli::BP, TextureLoad[0].dimensions());

		for(gli::texture2D::size_type Level = 0; Level < Texture.levels(); ++Level)
			Texture[Level] = TextureLoad[Level][0];

		assert(!Texture.empty());
		gli::saveDDS10(Texture, "../kueken256-bc7.dds");
	}
*/
	Error += test_image_wip();
	Error += test_image_fetch();
	Error += test_image_gradient();
	Error += test_image_export_dds();

	return Error;
}
