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
/// @file gli/gtx/loader_dds10.inl
/// @date 2010-09-26 / 2013-01-13
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

#include "loader_dds9.hpp"

namespace gli{
namespace detail{
namespace dds10
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

	enum DXGI_FORMAT 
	{
		DXGI_FORMAT_UNKNOWN                      = 0,
		DXGI_FORMAT_R32G32B32A32_TYPELESS        = 1,
		DXGI_FORMAT_R32G32B32A32_FLOAT           = 2,
		DXGI_FORMAT_R32G32B32A32_UINT            = 3,
		DXGI_FORMAT_R32G32B32A32_SINT            = 4,
		DXGI_FORMAT_R32G32B32_TYPELESS           = 5,
		DXGI_FORMAT_R32G32B32_FLOAT              = 6,
		DXGI_FORMAT_R32G32B32_UINT               = 7,
		DXGI_FORMAT_R32G32B32_SINT               = 8,
		DXGI_FORMAT_R16G16B16A16_TYPELESS        = 9,
		DXGI_FORMAT_R16G16B16A16_FLOAT           = 10,
		DXGI_FORMAT_R16G16B16A16_UNORM           = 11,
		DXGI_FORMAT_R16G16B16A16_UINT            = 12,
		DXGI_FORMAT_R16G16B16A16_SNORM           = 13,
		DXGI_FORMAT_R16G16B16A16_SINT            = 14,
		DXGI_FORMAT_R32G32_TYPELESS              = 15,
		DXGI_FORMAT_R32G32_FLOAT                 = 16,
		DXGI_FORMAT_R32G32_UINT                  = 17,
		DXGI_FORMAT_R32G32_SINT                  = 18,
		DXGI_FORMAT_R32G8X24_TYPELESS            = 19,
		DXGI_FORMAT_D32_FLOAT_S8X24_UINT         = 20,
		DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS     = 21,
		DXGI_FORMAT_X32_TYPELESS_G8X24_UINT      = 22,
		DXGI_FORMAT_R10G10B10A2_TYPELESS         = 23,
		DXGI_FORMAT_R10G10B10A2_UNORM            = 24,
		DXGI_FORMAT_R10G10B10A2_UINT             = 25,
		DXGI_FORMAT_R11G11B10_FLOAT              = 26,
		DXGI_FORMAT_R8G8B8A8_TYPELESS            = 27,
		DXGI_FORMAT_R8G8B8A8_UNORM               = 28,
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB          = 29,
		DXGI_FORMAT_R8G8B8A8_UINT                = 30,
		DXGI_FORMAT_R8G8B8A8_SNORM               = 31,
		DXGI_FORMAT_R8G8B8A8_SINT                = 32,
		DXGI_FORMAT_R16G16_TYPELESS              = 33,
		DXGI_FORMAT_R16G16_FLOAT                 = 34,
		DXGI_FORMAT_R16G16_UNORM                 = 35,
		DXGI_FORMAT_R16G16_UINT                  = 36,
		DXGI_FORMAT_R16G16_SNORM                 = 37,
		DXGI_FORMAT_R16G16_SINT                  = 38,
		DXGI_FORMAT_R32_TYPELESS                 = 39,
		DXGI_FORMAT_D32_FLOAT                    = 40,
		DXGI_FORMAT_R32_FLOAT                    = 41,
		DXGI_FORMAT_R32_UINT                     = 42,
		DXGI_FORMAT_R32_SINT                     = 43,
		DXGI_FORMAT_R24G8_TYPELESS               = 44,
		DXGI_FORMAT_D24_UNORM_S8_UINT            = 45,
		DXGI_FORMAT_R24_UNORM_X8_TYPELESS        = 46,
		DXGI_FORMAT_X24_TYPELESS_G8_UINT         = 47,
		DXGI_FORMAT_R8G8_TYPELESS                = 48,
		DXGI_FORMAT_R8G8_UNORM                   = 49,
		DXGI_FORMAT_R8G8_UINT                    = 50,
		DXGI_FORMAT_R8G8_SNORM                   = 51,
		DXGI_FORMAT_R8G8_SINT                    = 52,
		DXGI_FORMAT_R16_TYPELESS                 = 53,
		DXGI_FORMAT_R16_FLOAT                    = 54,
		DXGI_FORMAT_D16_UNORM                    = 55,
		DXGI_FORMAT_R16_UNORM                    = 56,
		DXGI_FORMAT_R16_UINT                     = 57,
		DXGI_FORMAT_R16_SNORM                    = 58,
		DXGI_FORMAT_R16_SINT                     = 59,
		DXGI_FORMAT_R8_TYPELESS                  = 60,
		DXGI_FORMAT_R8_UNORM                     = 61,
		DXGI_FORMAT_R8_UINT                      = 62,
		DXGI_FORMAT_R8_SNORM                     = 63,
		DXGI_FORMAT_R8_SINT                      = 64,
		DXGI_FORMAT_A8_UNORM                     = 65,
		DXGI_FORMAT_R1_UNORM                     = 66,
		DXGI_FORMAT_R9G9B9E5_SHAREDEXP           = 67,
		DXGI_FORMAT_R8G8_B8G8_UNORM              = 68,
		DXGI_FORMAT_G8R8_G8B8_UNORM              = 69,
		DXGI_FORMAT_BC1_TYPELESS                 = 70,
		DXGI_FORMAT_BC1_UNORM                    = 71,
		DXGI_FORMAT_BC1_UNORM_SRGB               = 72,
		DXGI_FORMAT_BC2_TYPELESS                 = 73,
		DXGI_FORMAT_BC2_UNORM                    = 74,
		DXGI_FORMAT_BC2_UNORM_SRGB               = 75,
		DXGI_FORMAT_BC3_TYPELESS                 = 76,
		DXGI_FORMAT_BC3_UNORM                    = 77,
		DXGI_FORMAT_BC3_UNORM_SRGB               = 78,
		DXGI_FORMAT_BC4_TYPELESS                 = 79,
		DXGI_FORMAT_BC4_UNORM                    = 80,
		DXGI_FORMAT_BC4_SNORM                    = 81,
		DXGI_FORMAT_BC5_TYPELESS                 = 82,
		DXGI_FORMAT_BC5_UNORM                    = 83,
		DXGI_FORMAT_BC5_SNORM                    = 84,
		DXGI_FORMAT_B5G6R5_UNORM                 = 85,
		DXGI_FORMAT_B5G5R5A1_UNORM               = 86,
		DXGI_FORMAT_B8G8R8A8_UNORM               = 87,
		DXGI_FORMAT_B8G8R8X8_UNORM               = 88,
		DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM   = 89,
		DXGI_FORMAT_B8G8R8A8_TYPELESS            = 90,
		DXGI_FORMAT_B8G8R8A8_UNORM_SRGB          = 91,
		DXGI_FORMAT_B8G8R8X8_TYPELESS            = 92,
		DXGI_FORMAT_B8G8R8X8_UNORM_SRGB          = 93,
		DXGI_FORMAT_BC6H_TYPELESS                = 94,
		DXGI_FORMAT_BC6H_UF16                    = 95,
		DXGI_FORMAT_BC6H_SF16                    = 96,
		DXGI_FORMAT_BC7_TYPELESS                 = 97,
		DXGI_FORMAT_BC7_UNORM                    = 98,
		DXGI_FORMAT_BC7_UNORM_SRGB               = 99,
		DXGI_FORMAT_FORCE_UINT                   = 0xffffffffUL 
	};

	enum D3D10_RESOURCE_DIMENSION 
	{
		D3D10_RESOURCE_DIMENSION_UNKNOWN     = 0,
		D3D10_RESOURCE_DIMENSION_BUFFER      = 1,
		D3D10_RESOURCE_DIMENSION_TEXTURE1D   = 2,
		D3D10_RESOURCE_DIMENSION_TEXTURE2D   = 3,
		D3D10_RESOURCE_DIMENSION_TEXTURE3D   = 4 
	};

	enum D3D10_RESOURCE_MISC_FLAG 
	{
		D3D10_RESOURCE_MISC_GENERATE_MIPS       = 0x1L,
		D3D10_RESOURCE_MISC_SHARED              = 0x2L,
		D3D10_RESOURCE_MISC_TEXTURECUBE         = 0x4L,
		D3D10_RESOURCE_MISC_SHARED_KEYEDMUTEX   = 0x10L,
		D3D10_RESOURCE_MISC_GDI_COMPATIBLE      = 0x20L 
	};

	enum dds_format
	{
		GLI_D3DFMT_R8G8B8               = 20,
		GLI_D3DFMT_A8R8G8B8             = 21,
		GLI_D3DFMT_X8R8G8B8             = 22,
		GLI_D3DFMT_A8                   = 28,
		GLI_D3DFMT_A2B10G10R10          = 31,
		GLI_D3DFMT_A8B8G8R8             = 32,
		GLI_D3DFMT_X8B8G8R8             = 33,
		GLI_D3DFMT_G16R16               = 34,
		GLI_D3DFMT_A2R10G10B10          = 35,
		GLI_D3DFMT_A16B16G16R16         = 36,

		GLI_D3DFMT_L8                   = 50,
		GLI_D3DFMT_A8L8                 = 51,

		GLI_D3DFMT_DXT1                 = GLI_MAKEFOURCC('D', 'X', 'T', '1'),
		GLI_D3DFMT_DXT2                 = GLI_MAKEFOURCC('D', 'X', 'T', '2'),
		GLI_D3DFMT_DXT3                 = GLI_MAKEFOURCC('D', 'X', 'T', '3'),
		GLI_D3DFMT_DXT4                 = GLI_MAKEFOURCC('D', 'X', 'T', '4'),
		GLI_D3DFMT_DXT5                 = GLI_MAKEFOURCC('D', 'X', 'T', '5'),
		GLI_D3DFMT_DX10                 = GLI_MAKEFOURCC('D', 'X', '1', '0'),

		GLI_D3DFMT_D32                  = 71,
		GLI_D3DFMT_D24S8                = 75,
		GLI_D3DFMT_D24X8                = 77,
		GLI_D3DFMT_D16                  = 80,
		GLI_D3DFMT_L16                  = 81,
		GLI_D3DFMT_D32F_LOCKABLE        = 82,
		GLI_D3DFMT_D24FS8               = 83,

		GLI_D3DFMT_R16F                 = 111,
		GLI_D3DFMT_G16R16F              = 112,
		GLI_D3DFMT_A16B16G16R16F        = 113,

		GLI_D3DFMT_R32F                 = 114,
		GLI_D3DFMT_G32R32F              = 115,
		GLI_D3DFMT_A32B32G32R32F        = 116
	};

	struct ddsHeader10
	{
		ddsHeader10() :
			dxgiFormat(DXGI_FORMAT_UNKNOWN),
			resourceDimension(D3D10_RESOURCE_DIMENSION_UNKNOWN),
			miscFlag(0),
			arraySize(1),
			reserved(0)
		{}

		DXGI_FORMAT					dxgiFormat;
		D3D10_RESOURCE_DIMENSION	resourceDimension;
		glm::uint32					miscFlag; // D3D10_RESOURCE_MISC_GENERATE_MIPS
		glm::uint32					arraySize;
		glm::uint32					reserved;
	};

	inline gli::format format_fourcc2gli_cast(glm::uint32 const & FourCC)
	{
		switch(FourCC)
		{
		case GLI_FOURCC_DXT1:
			return RGBA_DXT1;
		case GLI_FOURCC_DXT2:
		case GLI_FOURCC_DXT3:
			return RGBA_DXT3;
		case GLI_FOURCC_DXT4:
		case GLI_FOURCC_DXT5:
			return RGBA_DXT5;
		case GLI_FOURCC_R16F:
			return R16F;
		case GLI_FOURCC_G16R16F:
			return RG16F;
		case GLI_FOURCC_A16B16G16R16F:
			return RGBA16F;
		case GLI_FOURCC_R32F:
			return R32F;
		case GLI_FOURCC_G32R32F:
			return RG32F;
		case GLI_FOURCC_A32B32G32R32F:
			return RGBA32F;

		case GLI_D3DFMT_R8G8B8:
			return RGB8U;
		case GLI_D3DFMT_A8R8G8B8:
		case GLI_D3DFMT_X8R8G8B8:
		case GLI_D3DFMT_A8B8G8R8:
		case GLI_D3DFMT_X8B8G8R8:
			return RGBA8U;
		case GLI_D3DFMT_R5G6B5:
			return R5G6B5;
		case GLI_D3DFMT_A4R4G4B4:
		case GLI_D3DFMT_X4R4G4B4:
			return RGBA4;
		case GLI_D3DFMT_G16R16:
			return RG16U;
		case GLI_D3DFMT_A16B16G16R16:
			return RGBA16U;
		case GLI_D3DFMT_A2R10G10B10:
		case GLI_D3DFMT_A2B10G10R10:
			return RGB10A2;
		default:
			assert(0);
			return FORMAT_NULL;
		}
	}

	inline gli::format format_dds2gli_cast(DXGI_FORMAT const & Format)
	{
		gli::format Cast[] = 
		{
			gli::FORMAT_NULL,	//DXGI_FORMAT_UNKNOWN                      = 0,
			gli::RGBA32U,		//DXGI_FORMAT_R32G32B32A32_TYPELESS        = 1,
			gli::RGBA32F,		//DXGI_FORMAT_R32G32B32A32_FLOAT           = 2,
			gli::RGBA32U,		//DXGI_FORMAT_R32G32B32A32_UINT            = 3,
			gli::RGBA32I,		//DXGI_FORMAT_R32G32B32A32_SINT            = 4,
			gli::RGB32U,			//DXGI_FORMAT_R32G32B32_TYPELESS           = 5,
			gli::RGB32F,			//DXGI_FORMAT_R32G32B32_FLOAT              = 6,
			gli::RGB32U,			//DXGI_FORMAT_R32G32B32_UINT               = 7,
			gli::RGB32I,			//DXGI_FORMAT_R32G32B32_SINT               = 8,
			gli::RGBA16U,		//DXGI_FORMAT_R16G16B16A16_TYPELESS        = 9,
			gli::RGBA16F,		//DXGI_FORMAT_R16G16B16A16_FLOAT           = 10,
			gli::RGBA16U,		//DXGI_FORMAT_R16G16B16A16_UNORM           = 11,
			gli::RGBA16I,		//DXGI_FORMAT_R16G16B16A16_UINT            = 12,
			gli::RGBA16I,		//DXGI_FORMAT_R16G16B16A16_SNORM           = 13,
			gli::RGBA16I,		//DXGI_FORMAT_R16G16B16A16_SINT            = 14,
			gli::RG32U,			//DXGI_FORMAT_R32G32_TYPELESS              = 15,
			gli::RG32F,			//DXGI_FORMAT_R32G32_FLOAT                 = 16,
			gli::RG32U,			//DXGI_FORMAT_R32G32_UINT                  = 17,
			gli::RG32I,			//DXGI_FORMAT_R32G32_SINT                  = 18,
			gli::FORMAT_NULL,	//DXGI_FORMAT_R32G8X24_TYPELESS            = 19,
			gli::D32FS8X24,		//DXGI_FORMAT_D32_FLOAT_S8X24_UINT         = 20,
			gli::FORMAT_NULL,	//DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS     = 21,
			gli::FORMAT_NULL,	//DXGI_FORMAT_X32_TYPELESS_G8X24_UINT      = 22,
			gli::RGB10A2,		//DXGI_FORMAT_R10G10B10A2_TYPELESS         = 23,
			gli::RGB10A2,		//DXGI_FORMAT_R10G10B10A2_UNORM            = 24,
			gli::RGB10A2,		//DXGI_FORMAT_R10G10B10A2_UINT             = 25,
			gli::RG11B10F,		//DXGI_FORMAT_R11G11B10_FLOAT              = 26,
			gli::RGBA8U,			//DXGI_FORMAT_R8G8B8A8_TYPELESS            = 27,
			gli::RGBA8U,			//DXGI_FORMAT_R8G8B8A8_UNORM               = 28,
			gli::RGBA8U,			//DXGI_FORMAT_R8G8B8A8_UNORM_SRGB          = 29,
			gli::RGBA8U,			//DXGI_FORMAT_R8G8B8A8_UINT                = 30,
			gli::RGBA8I,			//DXGI_FORMAT_R8G8B8A8_SNORM               = 31,
			gli::RGBA8I,			//DXGI_FORMAT_R8G8B8A8_SINT                = 32,
			gli::RG16U,			//DXGI_FORMAT_R16G16_TYPELESS              = 33,
			gli::RG16F,			//DXGI_FORMAT_R16G16_FLOAT                 = 34,
			gli::RG16U,			//DXGI_FORMAT_R16G16_UNORM                 = 35,
			gli::RG16U,			//DXGI_FORMAT_R16G16_UINT                  = 36,
			gli::RG16I,			//DXGI_FORMAT_R16G16_SNORM                 = 37,
			gli::RG16I,			//DXGI_FORMAT_R16G16_SINT                  = 38,
			gli::R32F,			//DXGI_FORMAT_R32_TYPELESS                 = 39,
			gli::D32F,			//DXGI_FORMAT_D32_FLOAT                    = 40,
			gli::R32F,			//DXGI_FORMAT_R32_FLOAT                    = 41,
			gli::R32U,			//DXGI_FORMAT_R32_UINT                     = 42,
			gli::R32I,			//DXGI_FORMAT_R32_SINT                     = 43,
			gli::FORMAT_NULL,	//DXGI_FORMAT_R24G8_TYPELESS               = 44,
			gli::FORMAT_NULL,	//DXGI_FORMAT_D24_UNORM_S8_UINT            = 45,
			gli::FORMAT_NULL,	//DXGI_FORMAT_R24_UNORM_X8_TYPELESS        = 46,
			gli::FORMAT_NULL,	//DXGI_FORMAT_X24_TYPELESS_G8_UINT         = 47,
			gli::RG8U,			//DXGI_FORMAT_R8G8_TYPELESS                = 48,
			gli::RG8U,			//DXGI_FORMAT_R8G8_UNORM                   = 49,
			gli::RG8U,			//DXGI_FORMAT_R8G8_UINT                    = 50,
			gli::RG8I,			//DXGI_FORMAT_R8G8_SNORM                   = 51,
			gli::RG8I,			//DXGI_FORMAT_R8G8_SINT                    = 52,
			gli::R16U,			//DXGI_FORMAT_R16_TYPELESS                 = 53,
			gli::R16F,			//DXGI_FORMAT_R16_FLOAT                    = 54,
			gli::D16,			//DXGI_FORMAT_D16_UNORM                    = 55,
			gli::R16U,			//DXGI_FORMAT_R16_UNORM                    = 56,
			gli::R16U,			//DXGI_FORMAT_R16_UINT                     = 57,
			gli::R16I,			//DXGI_FORMAT_R16_SNORM                    = 58,
			gli::R16I,			//DXGI_FORMAT_R16_SINT                     = 59,
			gli::R8U,			//DXGI_FORMAT_R8_TYPELESS                  = 60,
			gli::R8U,			//DXGI_FORMAT_R8_UNORM                     = 61,
			gli::R8U,			//DXGI_FORMAT_R8_UINT                      = 62,
			gli::R8I,			//DXGI_FORMAT_R8_SNORM                     = 63,
			gli::R8I,			//DXGI_FORMAT_R8_SINT                      = 64,
			gli::R8U,			//DXGI_FORMAT_A8_UNORM                     = 65,
			gli::FORMAT_NULL,	//DXGI_FORMAT_R1_UNORM                     = 66,
			gli::RGB9E5,			//DXGI_FORMAT_R9G9B9E5_SHAREDEXP           = 67,
			gli::FORMAT_NULL,	//DXGI_FORMAT_R8G8_B8G8_UNORM              = 68,
			gli::FORMAT_NULL,	//DXGI_FORMAT_G8R8_G8B8_UNORM              = 69,
			gli::RGBA_DXT1,			//DXGI_FORMAT_BC1_TYPELESS                 = 70,
			gli::RGBA_DXT1,			//DXGI_FORMAT_BC1_UNORM                    = 71,
			gli::RGBA_DXT1,			//DXGI_FORMAT_BC1_UNORM_SRGB               = 72,
			gli::RGBA_DXT3,			//DXGI_FORMAT_BC2_TYPELESS                 = 73,
			gli::RGBA_DXT3,			//DXGI_FORMAT_BC2_UNORM                    = 74,
			gli::RGBA_DXT3,			//DXGI_FORMAT_BC2_UNORM_SRGB               = 75,
			gli::RGBA_DXT5,			//DXGI_FORMAT_BC3_TYPELESS                 = 76,
			gli::RGBA_DXT5,			//DXGI_FORMAT_BC3_UNORM                    = 77,
			gli::RGBA_DXT5,			//DXGI_FORMAT_BC3_UNORM_SRGB               = 78,
			gli::R_ATI1N_UNORM,	//DXGI_FORMAT_BC4_TYPELESS                 = 79,
			gli::R_ATI1N_UNORM,	//DXGI_FORMAT_BC4_UNORM                    = 80,
			gli::R_ATI1N_SNORM,	//DXGI_FORMAT_BC4_SNORM                    = 81,
			gli::RG_ATI2N_UNORM,	//DXGI_FORMAT_BC5_TYPELESS                 = 82,
			gli::RG_ATI2N_UNORM,	//DXGI_FORMAT_BC5_UNORM                    = 83,
			gli::RG_ATI2N_SNORM,	//DXGI_FORMAT_BC5_SNORM                    = 84,
			gli::FORMAT_NULL,	//DXGI_FORMAT_B5G6R5_UNORM                 = 85,
			gli::FORMAT_NULL,	//DXGI_FORMAT_B5G5R5A1_UNORM               = 86,
			gli::RGBA8U,			//DXGI_FORMAT_B8G8R8A8_UNORM               = 87,
			gli::RGBA8U,			//DXGI_FORMAT_B8G8R8X8_UNORM               = 88,
			gli::FORMAT_NULL,	//DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM   = 89,
			gli::RGBA8U,			//DXGI_FORMAT_B8G8R8A8_TYPELESS            = 90,
			gli::RGBA8U,			//DXGI_FORMAT_B8G8R8A8_UNORM_SRGB          = 91,
			gli::RGBA8U,			//DXGI_FORMAT_B8G8R8X8_TYPELESS            = 92,
			gli::RGBA8U,			//DXGI_FORMAT_B8G8R8X8_UNORM_SRGB          = 93,
			gli::RGB_BP_UNSIGNED_FLOAT,		//DXGI_FORMAT_BC6H_TYPELESS                = 94,
			gli::RGB_BP_UNSIGNED_FLOAT,		//DXGI_FORMAT_BC6H_UF16                    = 95,
			gli::RGB_BP_SIGNED_FLOAT,		//DXGI_FORMAT_BC6H_SF16                    = 96,
			gli::RGB_BP_UNORM,				//DXGI_FORMAT_BC7_TYPELESS                 = 97,
			gli::RGB_BP_UNORM,				//DXGI_FORMAT_BC7_UNORM                    = 98,
			gli::RGB_BP_UNORM,				//DXGI_FORMAT_BC7_UNORM_SRGB               = 99,
			gli::R32U			//DXGI_FORMAT_FORCE_UINT                   = 0xffffffffUL 
		};

		return Cast[Format];
	}
}//namespace dds10
}//namespace detail

	inline storage loadStorageDDS
	(
		std::string const & Filename
	)
	{
		std::ifstream FileIn(Filename.c_str(), std::ios::in | std::ios::binary);
		assert(!FileIn.fail());

		if(FileIn.fail())
			return storage();

		detail::ddsHeader HeaderDesc;
		detail::dds10::ddsHeader10 HeaderDesc10;
		char Magic[4]; 

		//* Read magic number and check if valid .dds file 
		FileIn.read((char*)&Magic, sizeof(Magic));

		assert(strncmp(Magic, "DDS ", 4) == 0);

		// Get the surface descriptor 
		FileIn.read((char*)&HeaderDesc, sizeof(HeaderDesc));
		if(HeaderDesc.format.flags & detail::GLI_DDPF_FOURCC && HeaderDesc.format.fourCC == detail::GLI_FOURCC_DX10)
			FileIn.read((char*)&HeaderDesc10, sizeof(HeaderDesc10));

		detail::DDLoader Loader;
		if(HeaderDesc.format.fourCC == detail::GLI_FOURCC_DX10)
			Loader.Format = detail::dds10::format_dds2gli_cast(HeaderDesc10.dxgiFormat);
		else if(HeaderDesc.format.flags & detail::GLI_DDPF_FOURCC)
			Loader.Format = detail::dds10::format_fourcc2gli_cast(HeaderDesc.format.fourCC);
		else if(HeaderDesc.format.flags & detail::GLI_DDPF_RGB)
		{
			switch(HeaderDesc.format.bpp)
			{
			case 8:
				Loader.Format = R8_UNORM;
				break;
			case 16:
				Loader.Format = RG8_UNORM;
				break;
			case 24:
				Loader.Format = RGB8_UNORM;
				break;
			case 32:
				Loader.Format = RGBA8_UNORM;
				break;
			}
		}
		else
			assert(0);

		gli::format const Format = Loader.Format;

		Loader.BlockSize = glm::uint32(gli::block_size(Format));
		Loader.BPP = glm::uint32(gli::bits_per_pixel(Format));

		std::streamoff Curr = FileIn.tellg();
		FileIn.seekg(0, std::ios_base::end);
		std::streamoff End = FileIn.tellg();
		FileIn.seekg(Curr, std::ios_base::beg);

		texture2D::size_type const MipMapCount = (HeaderDesc.flags & detail::GLI_DDSD_MIPMAPCOUNT) ? 
			HeaderDesc.mipMapLevels : 1;

		texture2D::size_type FaceCount(1);
		if(HeaderDesc.flags & detail::GLI_DDSCAPS2_CUBEMAP)
			FaceCount = int(glm::bitCount(HeaderDesc.flags & detail::GLI_DDSCAPS2_CUBEMAP_ALLFACES));

		texture2D::size_type DepthCount = 1;
		if(HeaderDesc.cubemapFlags & detail::GLI_DDSCAPS2_VOLUME)
				DepthCount = HeaderDesc.depth;

		storage Storage(
			HeaderDesc10.arraySize, 
			FaceCount,
			MipMapCount,
			Format,
			storage::dimensions_type(HeaderDesc.width, HeaderDesc.height, DepthCount));

		FileIn.read((char*)Storage.data(), std::size_t(End - Curr));

		return Storage;
	}

	inline void saveDDS
	(
		gli::texture2D const & Texture, 
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
		HeaderDesc.format.flags = detail::GLI_DDPF_FOURCC;
		HeaderDesc.format.fourCC = detail::GLI_FOURCC_DX10;
		HeaderDesc.format.bpp = glm::uint32(Desc.BBP);
		HeaderDesc.format.redMask = 0;
		HeaderDesc.format.greenMask = 0;
		HeaderDesc.format.blueMask = 0;
		HeaderDesc.format.alphaMask = 0;
		HeaderDesc.surfaceFlags = detail::GLI_DDSCAPS_TEXTURE | (Texture.levels() > 1 ? detail::GLI_DDSCAPS_MIPMAP : 0);
		HeaderDesc.cubemapFlags = 0;
		FileOut.write((char*)&HeaderDesc, sizeof(HeaderDesc));

		detail::dds10::ddsHeader10 HeaderDesc10;
		HeaderDesc10.arraySize = glm::uint32(Texture.layers());
		HeaderDesc10.resourceDimension = detail::dds10::D3D10_RESOURCE_DIMENSION_TEXTURE2D;
		HeaderDesc10.miscFlag = 0;//Image.levels() > 0 ? detail::D3D10_RESOURCE_MISC_GENERATE_MIPS : 0;
		HeaderDesc10.dxgiFormat = detail::dds10::DXGI_FORMAT(Desc.FormatDDS);
		HeaderDesc10.reserved = 0;

		FileOut.write((char*)&HeaderDesc10, sizeof(HeaderDesc10));
		FileOut.write((char*)(Texture.data()), Texture.size());

		if(FileOut.fail() || FileOut.bad())
			return;

		FileOut.close ();
	}

}//namespace gli
