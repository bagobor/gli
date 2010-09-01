#include <glm/setup.hpp>
#define GLM_SWIZZLE GLM_SWIZZLE_XYZW
#include <glm/glm.hpp>
#include <glm/gtc/type_precision.hpp>

#include <gli/gli.hpp>

#include "bug.hpp"
#include "core.hpp"

#include <vector>

//#include <boost/format.hpp>

bool test_image_wip()
{
	//gli::wip::image<glm::u8vec3, gli::wip::plain> Image;
	//gli::wip::image<glm::u8vec3, gli::wip::plain>::mipmap Mipmap = Image[0];

	//glm::vec2 Texcoord(0);
	//Image[0](Texcoord);

	//gli::wip::plain<glm::u8vec3> Surface;
	//gli::wip::fetch(Surface);
	//gli::wip::fetch(Image);

	return true;
}

bool test_image_export()
{
	gli::image Image = gli::import_as("../test.tga");
	gli::image ImageMipmaped = gli::generateMipmaps(Image, 0);

	gli::export_as(ImageMipmaped, 0, "../test0.tga");
	gli::export_as(ImageMipmaped, 1, "../test1.tga");
	gli::export_as(ImageMipmaped, 2, "../test2.tga");
	gli::export_as(ImageMipmaped, 3, "../test3.tga");

	return true;
}

bool test_image_export_dds()
{
	gli::image Image = gli::import_as("../test.dds");

	gli::export_as(Image, "../test_exported.dds");

	return true;
}

bool test_image_fetch()
{
	gli::image Image = gli::import_as("../test.tga");
	if(!Image.empty())
	{
		gli::image::dimensions_type Size = Image[0].dimensions();

		glm::u8vec3 TexelA = gli::textureLod<glm::u8vec3>(Image, glm::vec2(0.0f), 0);
		glm::u8vec3 TexelB = gli::textureLod<glm::u8vec3>(Image, glm::vec2(0.5f), 0);

		glm::u8vec3 TexelC = gli::texelFetch<glm::u8vec3>(Image, glm::ivec2(7, 7), 0);
		glm::u8vec3 TexelD = gli::texelFetch<glm::u8vec3>(Image, glm::ivec2(7, 0), 0);
		glm::u8vec3 TexelE = gli::texelFetch<glm::u8vec3>(Image, glm::ivec2(0, 7), 0);
	}

	return true;
}

bool test_image_gradient()
{
	{
		gli::image Image = gli::radial(glm::uvec2(256), glm::vec2(0.25f), 128.0f, glm::vec2(0.5f));
		gli::export_as(Image, "../gradient_radial.tga");
	}

	{
		gli::image Image = gli::linear(glm::uvec2(256), glm::vec2(0.25f), glm::vec2(0.75f));
		gli::export_as(Image, "../gradient_linear.tga");
	}

	return true;
}

int main()
{
	glm::vec4 v1(1, 2, 3, 4);
	glm::vec4 v2;
	glm::vec4 v3;
	glm::vec4 v4;
	v2.wyxz = v1.zyxw;
	v3 = v1.xzyw;
	v4.xzyw = v1;

	test_image_wip();
	test_image_fetch();
	test_image_gradient();
	test_image_export();
	test_image_export_dds();

	//// Set image
	//gli::wip::image<glm::u8vec3> Texture = gli::wip::import_as(TEXTURE_DIFFUSE);
	//for(gli::wip::image<glm::u8vec3>::level_type Level = 0; Level < Texture.levels(); ++Level)
	//{
	//	glTexImage2D(
	//		GL_TEXTURE_2D, 
	//		GLint(Level), 
	//		GL_RGB, 
	//		GLsizei(Image[Level]->size().x), 
	//		GLsizei(Image[Level]->size().y), 
	//		0,  
	//		GL_BGR, 
	//		GL_UNSIGNED_BYTE, 
	//		Image[Level]->data());
	//}

	return 0;
}
