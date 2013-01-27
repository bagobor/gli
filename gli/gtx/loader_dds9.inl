///////////////////////////////////////////////////////////////////////////////////
/// OpenGL Image (gli.g-truc.net)
///
/// Copyright (c) 2008 - 2013 G-Truc Creation (www.g-truc.net)
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///
/// @ref core
/// @file gli/gtx/loader_dds9.inl
/// @date 2010-09-08 / 2013-01-13
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

namespace gli{
namespace detail
{
	// DDS Documentation
	/*
		http://msdn.microsoft.com/en-us/library/bb943991(VS.85).aspx#File_Layout1
		http://msdn.microsoft.com/en-us/library/bb943992.aspx
	*/

	#define GLI_MAKEFOURCC(ch0, ch1, ch2, ch3) \
	  (glm::uint32)( \
		(((glm::uint32)(glm::uint8)(ch3) << 24) & 0xFF000000) | \
		(((glm::uint32)(glm::uint8)(ch2) << 16) & 0x00FF0000) | \
		(((glm::uint32)(glm::uint8)(ch1) <<  8) & 0x0000FF00) | \
		 ((glm::uint32)(glm::uint8)(ch0)        & 0x000000FF) )

	//enum dds_format
	//{
	//	GLI_D3DFMT_R8G8B8               = 20,
	//	GLI_D3DFMT_A8R8G8B8             = 21,
	//	GLI_D3DFMT_X8R8G8B8             = 22,
	//	GLI_D3DFMT_A8                   = 28,
	//	GLI_D3DFMT_A2B10G10R10          = 31,
	//	GLI_D3DFMT_A8B8G8R8             = 32,
	//	GLI_D3DFMT_X8B8G8R8             = 33,
	//	GLI_D3DFMT_G16R16               = 34,
	//	GLI_D3DFMT_A2R10G10B10          = 35,
	//	GLI_D3DFMT_A16B16G16R16         = 36,

	//	GLI_D3DFMT_L8                   = 50,
	//	GLI_D3DFMT_A8L8                 = 51,

	//	GLI_D3DFMT_DXT1                 = GLI_MAKEFOURCC('D', 'X', 'T', '1'),
	//	GLI_D3DFMT_DXT2                 = GLI_MAKEFOURCC('D', 'X', 'T', '2'),
	//	GLI_D3DFMT_DXT3                 = GLI_MAKEFOURCC('D', 'X', 'T', '3'),
	//	GLI_D3DFMT_DXT4                 = GLI_MAKEFOURCC('D', 'X', 'T', '4'),
	//	GLI_D3DFMT_DXT5                 = GLI_MAKEFOURCC('D', 'X', 'T', '5'),
	//	GLI_D3DFMT_DX10                 = GLI_MAKEFOURCC('D', 'X', '1', '0'),

	//	GLI_D3DFMT_D32                  = 71,
	//	GLI_D3DFMT_D24S8                = 75,
	//	GLI_D3DFMT_D24X8                = 77,
	//	GLI_D3DFMT_D16                  = 80,
	//	GLI_D3DFMT_L16                  = 81,
	//	GLI_D3DFMT_D32F_LOCKABLE        = 82,
	//	GLI_D3DFMT_D24FS8               = 83,

	//	GLI_D3DFMT_R16F                 = 111,
	//	GLI_D3DFMT_G16R16F              = 112,
	//	GLI_D3DFMT_A16B16G16R16F        = 113,

	//	GLI_D3DFMT_R32F                 = 114,
	//	GLI_D3DFMT_G32R32F              = 115,
	//	GLI_D3DFMT_A32B32G32R32F        = 116
	//};

	enum ddsCubemapflag
	{
		GLI_DDSCAPS2_CUBEMAP				= 0x00000200,
		GLI_DDSCAPS2_CUBEMAP_POSITIVEX		= 0x00000400,
		GLI_DDSCAPS2_CUBEMAP_NEGATIVEX		= 0x00000800,
		GLI_DDSCAPS2_CUBEMAP_POSITIVEY		= 0x00001000,
		GLI_DDSCAPS2_CUBEMAP_NEGATIVEY		= 0x00002000,
		GLI_DDSCAPS2_CUBEMAP_POSITIVEZ		= 0x00004000,
		GLI_DDSCAPS2_CUBEMAP_NEGATIVEZ		= 0x00008000,
		GLI_DDSCAPS2_VOLUME					= 0x00200000
	};

	glm::uint32 const GLI_DDSCAPS2_CUBEMAP_ALLFACES = (
		GLI_DDSCAPS2_CUBEMAP_POSITIVEX | GLI_DDSCAPS2_CUBEMAP_NEGATIVEX |
		GLI_DDSCAPS2_CUBEMAP_POSITIVEY | GLI_DDSCAPS2_CUBEMAP_NEGATIVEY |
		GLI_DDSCAPS2_CUBEMAP_POSITIVEZ | GLI_DDSCAPS2_CUBEMAP_NEGATIVEZ);

	enum ddsSurfaceflag
	{
		GLI_DDSCAPS_COMPLEX				= 0x00000008,
		GLI_DDSCAPS_MIPMAP				= 0x00400000,
		GLI_DDSCAPS_TEXTURE				= 0x00001000
	};

	struct ddsPixelFormat
	{
		glm::uint32 size; // 32
		glm::uint32 flags;
		glm::uint32 fourCC;
		glm::uint32 bpp;
		glm::uint32 redMask;
		glm::uint32 greenMask;
		glm::uint32 blueMask;
		glm::uint32 alphaMask;
	};

	struct ddsHeader
	{
		glm::uint32 size;
		glm::uint32 flags;
		glm::uint32 height;
		glm::uint32 width;
		glm::uint32 pitch;
		glm::uint32 depth;
		glm::uint32 mipMapLevels;
		glm::uint32 reserved1[11];
		ddsPixelFormat format;
		glm::uint32 surfaceFlags;
		glm::uint32 cubemapFlags;
		glm::uint32 reserved2[3];
	};

	glm::uint32 const GLI_D3DFMT_R8G8B8  = 20;
	glm::uint32 const GLI_D3DFMT_A8R8G8B8 = 21;
	glm::uint32 const GLI_D3DFMT_X8R8G8B8 = 22;
	glm::uint32 const GLI_D3DFMT_R5G6B5 = 23;
	glm::uint32 const GLI_D3DFMT_X1R5G5B5 = 24;
	glm::uint32 const GLI_D3DFMT_A1R5G5B5 = 25;
	glm::uint32 const GLI_D3DFMT_A4R4G4B4 = 26;
	glm::uint32 const GLI_D3DFMT_X4R4G4B4 = 30;
	glm::uint32 const GLI_D3DFMT_A2B10G10R10 = 31;
	glm::uint32 const GLI_D3DFMT_A8B8G8R8 = 32;
	glm::uint32 const GLI_D3DFMT_X8B8G8R8 = 33;
	glm::uint32 const GLI_D3DFMT_G16R16 = 34;
	glm::uint32 const GLI_D3DFMT_A2R10G10B10 = 35;
	glm::uint32 const GLI_D3DFMT_A16B16G16R16 = 36;

	glm::uint32 const GLI_FOURCC_DXT1 = GLI_MAKEFOURCC('D', 'X', 'T', '1');
	glm::uint32 const GLI_FOURCC_DXT2 = GLI_MAKEFOURCC('D', 'X', 'T', '2');
	glm::uint32 const GLI_FOURCC_DXT3 = GLI_MAKEFOURCC('D', 'X', 'T', '3');
	glm::uint32 const GLI_FOURCC_DXT4 = GLI_MAKEFOURCC('D', 'X', 'T', '4');
	glm::uint32 const GLI_FOURCC_DXT5 = GLI_MAKEFOURCC('D', 'X', 'T', '5');
	glm::uint32 const GLI_FOURCC_ATI1 = GLI_MAKEFOURCC('A', 'T', 'I', '1');			// ATI1
	glm::uint32 const GLI_FOURCC_ATI2 = GLI_MAKEFOURCC('A', 'T', 'I', '2');			// ATI2 (AKA 3Dc)
	glm::uint32 const GLI_FOURCC_DX10 = GLI_MAKEFOURCC('D', 'X', '1', '0');
	glm::uint32 const GLI_FOURCC_BC4U = GLI_MAKEFOURCC('B', 'C', '4', 'U');
	glm::uint32 const GLI_FOURCC_BC4S = GLI_MAKEFOURCC('B', 'C', '4', 'S');
	glm::uint32 const GLI_FOURCC_BC5U = GLI_MAKEFOURCC('B', 'C', '5', 'U');
	glm::uint32 const GLI_FOURCC_BC5S = GLI_MAKEFOURCC('B', 'C', '5', 'S');
	glm::uint32 const GLI_FOURCC_BC6H = GLI_MAKEFOURCC('B', 'C', '6', 'H');
	glm::uint32 const GLI_FOURCC_BC7  = GLI_MAKEFOURCC('B', 'C', '7', 'U');

	glm::uint32 const GLI_FOURCC_R16F                          = 0x0000006f;         // 16-bit float Red
	glm::uint32 const GLI_FOURCC_G16R16F                       = 0x00000070;         // 16-bit float Red/Green
	glm::uint32 const GLI_FOURCC_A16B16G16R16F                 = 0x00000071;         // 16-bit float RGBA
	glm::uint32 const GLI_FOURCC_R32F                          = 0x00000072;         // 32-bit float Red
	glm::uint32 const GLI_FOURCC_G32R32F                       = 0x00000073;         // 32-bit float Red/Green
	glm::uint32 const GLI_FOURCC_A32B32G32R32F                 = 0x00000074;         // 32-bit float RGBA

	glm::uint32 const GLI_DDPF_ALPHAPIXELS							= 0x00000001; // The surface has alpha channel information in the pixel format.
	glm::uint32 const GLI_DDPF_ALPHA								= 0x00000002; // The pixel format contains alpha only information
	glm::uint32 const GLI_DDPF_FOURCC                               = 0x00000004; // The FourCC code is valid.
	glm::uint32 const GLI_DDPF_RGB									= 0x00000040; // The RGB data in the pixel format structure is valid.
	//glm::uint32 const GLI_DDPF_COMPRESSED							= 0x00000080; // The surface will accept pixel data in the format specified and compress it during the write.
	//glm::uint32 const GLI_DDPF_RGBTOYUV								= 0x00000100; // The surface will accept RGB data and translate it during the write to YUV data.
	glm::uint32 const GLI_DDPF_YUV                                  = 0x00000200; // Pixel format is YUV - YUV data in pixel format struct is valid.
	//glm::uint32 const GLI_DDPF_ZBUFFER                              = 0x00000400; // Pixel format is a z buffer only surface
	//glm::uint32 const GLI_DDPF_ZPIXELS                              = 0x00002000; // The surface contains Z information in the pixels
	//glm::uint32 const GLI_DDPF_STENCILBUFFER                        = 0x00004000; // The surface contains stencil information along with Z
	//glm::uint32 const GLI_DDPF_ALPHAPREMULT                         = 0x00008000; // Premultiplied alpha format -- the color components have been premultiplied by the alpha component.
	glm::uint32 const GLI_DDPF_LUMINANCE                            = 0x00020000; // Luminance data in the pixel format is valid.
	//glm::uint32 const GLI_DDPF_BUMPLUMINANCE                        = 0x00040000; // Use this flag for luminance-only or luminance+alpha surfaces, the bit depth is then ddpf.dwLuminanceBitCount.
	//glm::uint32 const GLI_DDPF_BUMPDUDV                             = 0x00080000; // Bump map dUdV data in the pixel format is valid.

	glm::uint32 const GLI_DDSD_CAPS				= 0x00000001;
	glm::uint32 const GLI_DDSD_HEIGHT			= 0x00000002;
	glm::uint32 const GLI_DDSD_WIDTH			= 0x00000004;
	glm::uint32 const GLI_DDSD_PITCH			= 0x00000008;
	glm::uint32 const GLI_DDSD_PIXELFORMAT		= 0x00001000;
	glm::uint32 const GLI_DDSD_MIPMAPCOUNT		= 0x00020000;
	glm::uint32 const GLI_DDSD_LINEARSIZE		= 0x00080000;
	glm::uint32 const GLI_DDSD_DEPTH			= 0x00800000;

	struct DDLoader
	{
		glm::uint32 BlockSize;
		glm::uint32 BPP;
		gli::format Format;
	};

	enum format_type
	{
		FORMAT_TYPE_NULL,
		FORMAT_RGBA,
		FORMAT_FOURCC
	};

	inline glm::uint32 getFormatFourCC(gli::texture2D const & Image)
	{
		switch(Image.format())
		{
		default:
			return 0;
		case RGBA_DXT1:
			return GLI_FOURCC_DXT1;
		case RGBA_DXT3:
			return GLI_FOURCC_DXT3;
		case RGBA_DXT5:
			return GLI_FOURCC_DXT5;
		case R_ATI1N_UNORM:
		case R_ATI1N_SNORM:
		case RG_ATI2N_UNORM:
		case RG_ATI2N_SNORM:
		case RGB_BP_UNSIGNED_FLOAT:
		case RGB_BP_SIGNED_FLOAT:
		case RGB_BP_UNORM:
			return GLI_FOURCC_DX10;
		case R16F:
			return GLI_FOURCC_R16F;
		case RG16F:
			return GLI_FOURCC_G16R16F;
		case RGBA16F:
			return GLI_FOURCC_A16B16G16R16F;
		case R32F:
			return GLI_FOURCC_R32F;
		case RG32F:
			return GLI_FOURCC_G32R32F;
		case RGBA32F:
			return GLI_FOURCC_A32B32G32R32F;
		}
	}

	inline glm::uint32 getFormatFlags(gli::texture2D const & Image)
	{
		glm::uint32 Result = 0;

		switch(Image.format())
		{
		default: 
			break;
		case R8U:
		case RG8U:
		case RGB8U:
		case RGBA8U:
		case R16U:
		case RG16U:
		case RGB16U:
		case RGBA16U:
		case R32U:
		case RG32U:
		case RGB32U:
		case RGBA32U:
		case R8I:
		case RG8I:
		case RGB8I:
		case RGBA8I:
		case R16I:
		case RG16I:
		case RGB16I:
		case RGBA16I:
		case R32I:
		case RG32I:
		case RGB32I:
		case RGBA32I:
			Result |= GLI_DDPF_RGB;
			break;
		case R16F:
		case RG16F:
		case RGB16F:
		case RGBA16F:
		case R32F:
		case RG32F:
		case RGB32F:
		case RGBA32F:
		case RGB9E5:
		case RG11B10F:
		case R5G6B5:
		case RGBA4:
		case RGB10A2:
		case D16:
		case D24X8:
		case D24S8:
		case D32F:
		case D32FS8X24:
		case RGBA_DXT1:
		case RGBA_DXT3:
		case RGBA_DXT5:
		case R_ATI1N_UNORM:
		case R_ATI1N_SNORM:
		case RG_ATI2N_UNORM:
		case RG_ATI2N_SNORM:
		case RGB_BP_UNSIGNED_FLOAT:
		case RGB_BP_SIGNED_FLOAT:
		case RGB_BP_UNORM:
			Result |= GLI_DDPF_FOURCC;
			break;
		};

		return Result;
	}
}//namespace detail

	inline void saveDDS9
	(
		texture2D const & Texture, 
		std::string const & Filename
	)
	{
		std::ofstream FileOut(Filename.c_str(), std::ios::out | std::ios::binary);
		if (!FileOut)
			return;

		detail::format_desc const & Desc = detail::getFormatInfo(Texture.format());

		char const * Magic = "DDS ";
		FileOut.write((char*)Magic, sizeof(char) * 4);

		glm::uint32 Caps = detail::GLI_DDSD_CAPS | detail::GLI_DDSD_HEIGHT | detail::GLI_DDSD_WIDTH | detail::GLI_DDSD_PIXELFORMAT;

		detail::ddsHeader HeaderDesc;
		HeaderDesc.size = sizeof(detail::ddsHeader);
		HeaderDesc.flags = Caps | (Desc.Compressed ? detail::GLI_DDSD_LINEARSIZE : detail::GLI_DDSD_PITCH) | (Texture.levels() > 1 ? detail::GLI_DDSD_MIPMAPCOUNT : 0); //659463;
		HeaderDesc.width = Texture[0].dimensions().x;
		HeaderDesc.height = Texture[0].dimensions().y;
		HeaderDesc.pitch = glm::uint32(Desc.Compressed ? Texture.size() : 32);
		HeaderDesc.depth = 0;
		HeaderDesc.mipMapLevels = glm::uint32(Texture.levels());
		HeaderDesc.format.size = sizeof(detail::ddsPixelFormat);
		HeaderDesc.format.flags = detail::getFormatFlags(Texture);
		HeaderDesc.format.fourCC = detail::getFormatFourCC(Texture);
		HeaderDesc.format.bpp = glm::uint32(Desc.BBP);
		HeaderDesc.format.redMask = 0;
		HeaderDesc.format.greenMask = 0;
		HeaderDesc.format.blueMask = 0;
		HeaderDesc.format.alphaMask = 0;
		HeaderDesc.surfaceFlags = detail::GLI_DDSCAPS_TEXTURE | (Texture.levels() > 1 ? detail::GLI_DDSCAPS_MIPMAP : 0);
		HeaderDesc.cubemapFlags = 0;

		FileOut.write((char*)&HeaderDesc, sizeof(HeaderDesc));

		for(texture2D::size_type Level = 0; Level < Texture.levels(); ++Level)
		{
			texture2D::size_type ImageSize = Texture[Level].size();
			FileOut.write((char*)(Texture[Level].data()), ImageSize);
		}

		if(FileOut.fail() || FileOut.bad())
			return;

		FileOut.close ();
	}
/*
	inline void saveTextureCubeDDS9
	(
		textureCube const & Texture, 
		std::string const & Filename
	)
	{
		std::ofstream FileOut(Filename.c_str(), std::ios::out | std::ios::binary);
		if (!FileOut || Texture.empty())
			return;

		char const * Magic = "DDS ";
		FileOut.write((char*)Magic, sizeof(char) * 4);

		glm::uint32 Caps = detail::dds9::GLI_DDSD_CAPS | detail::dds9::GLI_DDSD_HEIGHT | detail::dds9::GLI_DDSD_WIDTH | detail::dds9::GLI_DDSD_PIXELFORMAT | detail::dds9::GLI_DDSCAPS_COMPLEX;

		detail::dds9::ddsHeader SurfaceDesc;
		SurfaceDesc.size = sizeof(detail::dds9::ddsHeader);
		SurfaceDesc.flags = Caps | (detail::dds9::isCompressed(Texture[POSITIVE_X]) ? detail::dds9::GLI_DDSD_LINEARSIZE : detail::dds9::GLI_DDSD_PITCH) | (Texture.levels() > 1 ? detail::dds9::GLI_DDSD_MIPMAPCOUNT : 0); //659463;
		SurfaceDesc.width = Texture[POSITIVE_X][0].dimensions().x;
		SurfaceDesc.height = Texture[POSITIVE_X][0].dimensions().y;
		SurfaceDesc.pitch = glm::uint32(detail::dds9::isCompressed(Texture[POSITIVE_X]) ? Texture[POSITIVE_X].memory_size() : 32);
		SurfaceDesc.depth = 0;
		SurfaceDesc.mipMapLevels = glm::uint32(Texture.levels());
		SurfaceDesc.format.size = sizeof(detail::dds9::ddsPixelFormat);
		SurfaceDesc.format.flags = detail::dds9::getFormatFlags(Texture[POSITIVE_X]);
		SurfaceDesc.format.fourCC = detail::dds9::getFormatFourCC(Texture[POSITIVE_X]);
		SurfaceDesc.format.bpp = detail::dds9::getFormatBPP(Texture[POSITIVE_X]);
		SurfaceDesc.format.redMask = 0;
		SurfaceDesc.format.greenMask = 0;
		SurfaceDesc.format.blueMask = 0;
		SurfaceDesc.format.alphaMask = 0;
		SurfaceDesc.surfaceFlags = detail::dds9::GLI_DDSCAPS_TEXTURE | (Texture.levels() > 1 ? detail::dds9::GLI_DDSCAPS_MIPMAP : 0);
		SurfaceDesc.cubemapFlags = 
			detail::dds9::GLI_DDSCAPS2_CUBEMAP | detail::dds9::GLI_DDSCAPS2_CUBEMAP_POSITIVEX | detail::dds9::GLI_DDSCAPS2_CUBEMAP_NEGATIVEX | detail::dds9::GLI_DDSCAPS2_CUBEMAP_POSITIVEY | detail::dds9::GLI_DDSCAPS2_CUBEMAP_NEGATIVEY | detail::dds9::GLI_DDSCAPS2_CUBEMAP_POSITIVEZ | detail::dds9::GLI_DDSCAPS2_CUBEMAP_NEGATIVEZ;

		FileOut.write((char*)&SurfaceDesc, sizeof(SurfaceDesc));

		for(textureCube::size_type Face = 0; Face < FACE_MAX; ++Face)
		for(texture2D::level_type Level = 0; Level < Texture.levels(); ++Level)
		{
			texture2D::size_type ImageSize = Texture[textureCube::face_type(Face)][Level].memory_size();
			FileOut.write((char*)(Texture[textureCube::face_type(Face)][Level].data()), ImageSize);
		}

		if(FileOut.fail() || FileOut.bad())
			return;

		FileOut.close ();
	}
*/
}//namespace gli
