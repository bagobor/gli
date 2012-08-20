///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2011-10-11
// Updated : 2011-10-11
// Licence : This source is under MIT licence
// File    : test/core/texture_2d.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <gli/gli.hpp>
/*
inline GLuint createTexture2D(std::string const & Filename)
{
	gli::texture2D Texture = gli::load(Filename);
	if(Texture.empty())
		return 0;

	detail::texture_desc TextureDesc = detail::gli2ogl_cast(Texture.format());

	GLint Alignment = 0;
	glGetIntegerv(GL_UNPACK_ALIGNMENT, &Alignment);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	GLuint Name = 0;
	glGenTextures(1, &Name);
	glBindTexture(GL_TEXTURE_2D, Name);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Texture.levels() > 1 ? GL_NEAREST_MIPMAP_NEAREST : GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if(size(Texture, BIT_PER_PIXEL) == size(Texture, BLOCK_SIZE) << 3)
	{
		for(gli::texture2D::level_type Level = 0; Level < Texture.levels(); ++Level)
		{
			glTexImage2D(
				GL_TEXTURE_2D, 
				GLint(Level), 
				TextureDesc.InternalFormat,
				GLsizei(Texture[Level].dimensions().x), 
				GLsizei(Texture[Level].dimensions().y), 
				0,  
				TextureDesc.ExternalFormatRev, 
				TextureDesc.Type, 
				Texture[Level].data());
		}
	}
	else
	{
		for(gli::texture2D::level_type Level = 0; Level < Texture.levels(); ++Level)
		{
			glCompressedTexImage2D(
				GL_TEXTURE_2D,
				GLint(Level),
				TextureDesc.InternalFormat,
				GLsizei(Texture[Level].dimensions().x), 
				GLsizei(Texture[Level].dimensions().y), 
				0, 
				GLsizei(Texture[Level].capacity()), 
				Texture[Level].data());
		}
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	glPixelStorei(GL_UNPACK_ALIGNMENT, Alignment);

	return Name;
}
*/
int test_texture_2d_clear()
{
	int Error = 0;

	glm::u8vec4 const Orange(255, 127, 0, 255);

	gli::texture2D Texture(gli::texture2D::size_type(glm::log2(16u)), gli::RGBA8U, gli::texture2D::dimensions_type(16));

	//Texture.clear<glm::u8vec4>(Cyan);

	return Error;
}


int main()
{
	int Error = 0;

	Error += test_texture_2d_clear();

	return Error;
}

