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
/// @file gli/core/storage.inl
/// @date 2012-06-21 / 2013-01-12
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

namespace gli{
namespace detail
{
	enum ddsFORMAT
	{
		DDS_UNKNOWN                     = 0,
		DDS_R32G32B32A32_TYPELESS       = 1,
		DDS_R32G32B32A32_FLOAT          = 2,
		DDS_R32G32B32A32_UINT           = 3,
		DDS_R32G32B32A32_SINT           = 4,
		DDS_R32G32B32_TYPELESS          = 5,
		DDS_R32G32B32_FLOAT             = 6,
		DDS_R32G32B32_UINT              = 7,
		DDS_R32G32B32_SINT              = 8,
		DDS_R16G16B16A16_TYPELESS       = 9,
		DDS_R16G16B16A16_FLOAT          = 10,
		DDS_R16G16B16A16_UNORM          = 11,
		DDS_R16G16B16A16_UINT           = 12,
		DDS_R16G16B16A16_SNORM          = 13,
		DDS_R16G16B16A16_SINT           = 14,
		DDS_R32G32_TYPELESS             = 15,
		DDS_R32G32_FLOAT                = 16,
		DDS_R32G32_UINT                 = 17,
		DDS_R32G32_SINT                 = 18,
		DDS_R32G8X24_TYPELESS           = 19,
		DDS_D32_FLOAT_S8X24_UINT        = 20,
		DDS_R32_FLOAT_X8X24_TYPELESS    = 21,
		DDS_X32_TYPELESS_G8X24_UINT     = 22,
		DDS_R10G10B10A2_TYPELESS        = 23,
		DDS_R10G10B10A2_UNORM           = 24,
		DDS_R10G10B10A2_UINT            = 25,
		DDS_R11G11B10_FLOAT             = 26,
		DDS_R8G8B8A8_TYPELESS           = 27,
		DDS_R8G8B8A8_UNORM              = 28,
		DDS_R8G8B8A8_UNORM_SRGB         = 29,
		DDS_R8G8B8A8_UINT               = 30,
		DDS_R8G8B8A8_SNORM              = 31,
		DDS_R8G8B8A8_SINT               = 32,
		DDS_R16G16_TYPELESS             = 33,
		DDS_R16G16_FLOAT                = 34,
		DDS_R16G16_UNORM                = 35,
		DDS_R16G16_UINT                 = 36,
		DDS_R16G16_SNORM                = 37,
		DDS_R16G16_SINT                 = 38,
		DDS_R32_TYPELESS                = 39,
		DDS_D32_FLOAT                   = 40,
		DDS_R32_FLOAT                   = 41,
		DDS_R32_UINT                    = 42,
		DDS_R32_SINT                    = 43,
		DDS_R24G8_TYPELESS              = 44,
		DDS_D24_UNORM_S8_UINT           = 45,
		DDS_R24_UNORM_X8_TYPELESS       = 46,
		DDS_X24_TYPELESS_G8_UINT        = 47,
		DDS_R8G8_TYPELESS               = 48,
		DDS_R8G8_UNORM                  = 49,
		DDS_R8G8_UINT                   = 50,
		DDS_R8G8_SNORM                  = 51,
		DDS_R8G8_SINT                   = 52,
		DDS_R16_TYPELESS                = 53,
		DDS_R16_FLOAT                   = 54,
		DDS_D16_UNORM                   = 55,
		DDS_R16_UNORM                   = 56,
		DDS_R16_UINT                    = 57,
		DDS_R16_SNORM                   = 58,
		DDS_R16_SINT                    = 59,
		DDS_R8_TYPELESS                 = 60,
		DDS_R8_UNORM                    = 61,
		DDS_R8_UINT                     = 62,
		DDS_R8_SNORM                    = 63,
		DDS_R8_SINT                     = 64,
		DDS_A8_UNORM                    = 65,
		DDS_R1_UNORM                    = 66,
		DDS_R9G9B9E5_SHAREDEXP          = 67,
		DDS_R8G8_B8G8_UNORM             = 68,
		DDS_G8R8_G8B8_UNORM             = 69,
		DDS_BC1_TYPELESS                = 70,
		DDS_BC1_UNORM                   = 71,
		DDS_BC1_UNORM_SRGB              = 72,
		DDS_BC2_TYPELESS                = 73,
		DDS_BC2_UNORM                   = 74,
		DDS_BC2_UNORM_SRGB              = 75,
		DDS_BC3_TYPELESS                = 76,
		DDS_BC3_UNORM                   = 77,
		DDS_BC3_UNORM_SRGB              = 78,
		DDS_BC4_TYPELESS                = 79,
		DDS_BC4_UNORM                   = 80,
		DDS_BC4_SNORM                   = 81,
		DDS_BC5_TYPELESS                = 82,
		DDS_BC5_UNORM                   = 83,
		DDS_BC5_SNORM                   = 84,
		DDS_B5G6R5_UNORM                = 85,
		DDS_B5G5R5A1_UNORM              = 86,
		DDS_B8G8R8A8_UNORM              = 87,
		DDS_B8G8R8X8_UNORM              = 88,
		DDS_R10G10B10_XR_BIAS_A2_UNORM  = 89,
		DDS_B8G8R8A8_TYPELESS           = 90,
		DDS_B8G8R8A8_UNORM_SRGB         = 91,
		DDS_B8G8R8X8_TYPELESS           = 92,
		DDS_B8G8R8X8_UNORM_SRGB         = 93,
		DDS_BC6H_TYPELESS               = 94,
		DDS_BC6H_UF16                   = 95,
		DDS_BC6H_SF16                   = 96,
		DDS_BC7_TYPELESS                = 97,
		DDS_BC7_UNORM                   = 98,
		DDS_BC7_UNORM_SRGB              = 99,
		DDS_AYUV                        = 100,
		DDS_Y410                        = 101,
		DDS_Y416                        = 102,
		DDS_NV12                        = 103,
		DDS_P010                        = 104,
		DDS_P016                        = 105,
		DDS_420_OPAQUE                  = 106,
		DDS_YUY2                        = 107,
		DDS_Y210                        = 108,
		DDS_Y216                        = 109,
		DDS_NV11                        = 110,
		DDS_AI44                        = 111,
		DDS_IA44                        = 112,
		DDS_P8                          = 113,
		DDS_A8P8                        = 114,
		DDS_B4G4R4A4_UNORM              = 115,
		DDS_FORCE_UINT                  = 0xffffffffUL
	};

	struct format_desc
	{
		std::size_t BlockSize;
		glm::uvec3 BlockDimensions;
		std::size_t BBP;
		std::size_t Component;
		bool Compressed;
		internalFormat Internal;
		externalFormat External;
		externalFormat ExternalShuffle;
		typeFormat Type;
		glm::uint32 FormatDDS; //http://msdn.microsoft.com/en-us/library/windows/desktop/bb173059(v=vs.85).aspx
		//glm::uint32 FourCC;
	};

	inline format_desc const getFormatInfo(format const & Format)
	{
		format_desc const Desc[FORMAT_MAX] =
		{
			{  0,  glm::uvec3(0), 0,  0, false, INTERNAL_NONE, EXTERNAL_NONE, EXTERNAL_NONE, TYPE_NONE, DDS_UNKNOWN},					//FORMAT_NULL

			// unorm formats
			{  1, glm::uvec3(1),  8,  1, false, INTERNAL_R8_UNORM, EXTERNAL_RED, EXTERNAL_RED, TYPE_U8, DDS_R8_UNORM},					//R8_UNORM,
			{  2, glm::uvec3(1), 16,  2, false, INTERNAL_RG8_UNORM, EXTERNAL_RG, EXTERNAL_RG, TYPE_U8, DDS_R8G8_UNORM},					//RG8_UNORM,
			{  3, glm::uvec3(1), 24,  3, false, INTERNAL_RGB8_UNORM, EXTERNAL_RGB, EXTERNAL_BGR, TYPE_U8, DDS_UNKNOWN},					//RGB8_UNORM,
			{  4, glm::uvec3(1), 32,  4, false, INTERNAL_RGBA8_UNORM, EXTERNAL_RGBA, EXTERNAL_BGRA, TYPE_U8, DDS_R8G8B8A8_UNORM},		//RGBA8_UNORM,

			{  2, glm::uvec3(1), 16,  1, false, INTERNAL_R16_UNORM, EXTERNAL_RED, EXTERNAL_RED, TYPE_U16, DDS_R16_UNORM},				//R16_UNORM,
			{  4, glm::uvec3(1), 32,  2, false, INTERNAL_RG16_UNORM, EXTERNAL_RG, EXTERNAL_RG, TYPE_U16},								//RG16_UNORM,
			{  6, glm::uvec3(1), 48,  3, false, INTERNAL_RGB16_UNORM, EXTERNAL_RGB, EXTERNAL_BGR, TYPE_U16},							//RGB16_UNORM,
			{  8, glm::uvec3(1), 64,  4, false, INTERNAL_RGBA16_UNORM, EXTERNAL_RGBA, EXTERNAL_BGRA, TYPE_U16, DDS_R16G16B16A16_UNORM},	//RGBA16_UNORM,
			
			// snorm formats
			{  1, glm::uvec3(1),  8,  1, false, INTERNAL_R8_SNORM, EXTERNAL_RED, EXTERNAL_RED, TYPE_I8, DDS_R8_SNORM},					//R8_SNORM,
			{  2, glm::uvec3(1), 16,  2, false, INTERNAL_RG8_SNORM, EXTERNAL_RG, EXTERNAL_RG, TYPE_I8, DDS_R8G8_SNORM},					//RG8_SNORM,
			{  3, glm::uvec3(1), 24,  3, false, INTERNAL_RGB8_SNORM, EXTERNAL_RGB, EXTERNAL_BGR, TYPE_I8, DDS_UNKNOWN},					//RGB8_SNORM,
			{  4, glm::uvec3(1), 32,  4, false, INTERNAL_RGBA8_SNORM, EXTERNAL_RGBA, EXTERNAL_BGRA, TYPE_I8, DDS_R8G8B8A8_SNORM},		//RGBA8_SNORM,

			{  2, glm::uvec3(1), 16,  1, false, INTERNAL_R16_SNORM, EXTERNAL_RED, EXTERNAL_RED, TYPE_I16, DDS_R16_SNORM},				//R16_SNORM,
			{  4, glm::uvec3(1), 32,  2, false, INTERNAL_RG16_SNORM, EXTERNAL_RG, EXTERNAL_RG, TYPE_I16, DDS_R16G16_SNORM},				//RG16_SNORM,
			{  6, glm::uvec3(1), 48,  3, false, INTERNAL_RGB16_SNORM, EXTERNAL_RGB, EXTERNAL_BGR, TYPE_I16, DDS_UNKNOWN},				//RGB16_SNORM,
			{  8, glm::uvec3(1), 64,  4, false, INTERNAL_RGBA16_SNORM, EXTERNAL_RGBA, EXTERNAL_BGRA, TYPE_I16, DDS_R16G16B16A16_SNORM},	//RGBA16_SNORM,

			// Unsigned integer formats
			{  1, glm::uvec3(1),  8,  1, false, INTERNAL_R8U, EXTERNAL_RED_INTEGER, EXTERNAL_RED_INTEGER, TYPE_U8, DDS_R8_UINT},			//R8U,
			{  2, glm::uvec3(1), 16,  2, false, INTERNAL_RG8U, EXTERNAL_RG_INTEGER, EXTERNAL_RG_INTEGER, TYPE_U8, DDS_R8G8_UINT},			//RG8U,
			{  3, glm::uvec3(1), 24,  3, false, INTERNAL_RGB8U, EXTERNAL_RGB_INTEGER, EXTERNAL_BGR_INTEGER, TYPE_U8, DDS_UNKNOWN},			//RGB8U,
			{  4, glm::uvec3(1), 32,  4, false, INTERNAL_RGBA8U, EXTERNAL_RGBA_INTEGER, EXTERNAL_BGRA_INTEGER, TYPE_U8, DDS_R8G8B8A8_UINT},	//RGBA8U,

			{  2, glm::uvec3(1), 16,  1, false, INTERNAL_R16U, EXTERNAL_RED_INTEGER, EXTERNAL_RED_INTEGER, TYPE_U16, DDS_R16_UINT},					//R16U,
			{  4, glm::uvec3(1), 32,  2, false, INTERNAL_RG16U, EXTERNAL_RG_INTEGER, EXTERNAL_RG_INTEGER, TYPE_U16, DDS_R16G16_UINT},				//RG16U,
			{  6, glm::uvec3(1), 48,  3, false, INTERNAL_RGB16U, EXTERNAL_RGB_INTEGER, EXTERNAL_BGR_INTEGER, TYPE_U16, DDS_UNKNOWN},				//RGB16U,
			{  8, glm::uvec3(1), 64,  4, false, INTERNAL_RGBA16U, EXTERNAL_RGBA_INTEGER, EXTERNAL_BGRA_INTEGER, TYPE_U16, DDS_R16G16B16A16_UINT},	//RGBA16U,

			{  4, glm::uvec3(1),  32,  1, false, INTERNAL_R32U, EXTERNAL_RED_INTEGER, EXTERNAL_RED_INTEGER, TYPE_U32, DDS_R32_UINT},				//R32U,
			{  8, glm::uvec3(1),  64,  2, false, INTERNAL_RG32U, EXTERNAL_RG_INTEGER, EXTERNAL_RG_INTEGER, TYPE_U32, DDS_R32G32_UINT},				//RG32U,
			{ 12, glm::uvec3(1),  96,  3, false, INTERNAL_RGB32U, EXTERNAL_RGB_INTEGER, EXTERNAL_RGB_INTEGER, TYPE_U32, DDS_R32G32B32_UINT},		//RGB32U,
			{ 16, glm::uvec3(1), 128,  4, false, INTERNAL_RGBA32U, EXTERNAL_RGBA_INTEGER, EXTERNAL_RGBA_INTEGER, TYPE_U32, DDS_R32G32B32A32_UINT},	//RGBA32U,

			/// Signed integer formats
			{  1, glm::uvec3(1),  32,  1, false, INTERNAL_R8I, EXTERNAL_RED_INTEGER, EXTERNAL_RED_INTEGER, TYPE_I8, DDS_R8_SINT},				//R8I,
			{  2, glm::uvec3(1),  64,  2, false, INTERNAL_RG8I, EXTERNAL_RED_INTEGER, EXTERNAL_RG_INTEGER, TYPE_I8, DDS_R8G8_SINT},				//RG8I,
			{  3, glm::uvec3(1),  96,  3, false, INTERNAL_RGB8I, EXTERNAL_RED_INTEGER, EXTERNAL_RGB_INTEGER, TYPE_I8, DDS_UNKNOWN},				//RGB8I,
			{  4, glm::uvec3(1), 128,  4, false, INTERNAL_RGBA8I, EXTERNAL_RED_INTEGER, EXTERNAL_RGBA_INTEGER, TYPE_I8, DDS_R8G8B8A8_SINT},		//RGBA8I,

			{  2, glm::uvec3(1), 16,  1, false, INTERNAL_R16I, EXTERNAL_RED_INTEGER, EXTERNAL_RED_INTEGER, TYPE_I16, DDS_R16_SINT},					//R16I,
			{  4, glm::uvec3(1), 32,  2, false, INTERNAL_RG16I, EXTERNAL_RED_INTEGER, EXTERNAL_RG_INTEGER, TYPE_I16, DDS_R16G16_SINT},				//RG16I,
			{  6, glm::uvec3(1), 48,  3, false, INTERNAL_RGB16I, EXTERNAL_RED_INTEGER, EXTERNAL_RGB_INTEGER, TYPE_I16, DDS_UNKNOWN},				//RGB16I,
			{  8, glm::uvec3(1), 64,  4, false, INTERNAL_RGBA16I, EXTERNAL_RED_INTEGER, EXTERNAL_RGBA_INTEGER, TYPE_I16, DDS_R16G16B16A16_SINT},	//RGBA16I,

			{  4, glm::uvec3(1),  32,  1, false, INTERNAL_R32I, EXTERNAL_RED_INTEGER, EXTERNAL_RED_INTEGER, TYPE_I32, DDS_R32_SINT},				//R32I,
			{  8, glm::uvec3(1),  64,  2, false, INTERNAL_RG32I, EXTERNAL_RED_INTEGER, EXTERNAL_RG_INTEGER, TYPE_I32, DDS_R32G32_SINT},				//RG32I,
			{ 12, glm::uvec3(1),  96,  3, false, INTERNAL_RGB32I, EXTERNAL_RED_INTEGER, EXTERNAL_RGB_INTEGER, TYPE_I32, DDS_R32G32B32_SINT},		//RGB32I,
			{ 16, glm::uvec3(1), 128,  4, false, INTERNAL_RGBA32I, EXTERNAL_RED_INTEGER, EXTERNAL_RGBA_INTEGER, TYPE_I32, DDS_R32G32B32A32_SINT},	//RGBA32I,

			/// Floating formats
			{  2, glm::uvec3(1), 16,  1, false, INTERNAL_R16F, EXTERNAL_RED, EXTERNAL_RED, TYPE_F16, DDS_R16_FLOAT},							//R16F,
			{  4, glm::uvec3(1), 32,  2, false, INTERNAL_RG16F, EXTERNAL_RG, EXTERNAL_RG, TYPE_F16, DDS_R16G16_FLOAT},							//RG16F,
			{  6, glm::uvec3(1), 48,  3, false, INTERNAL_RGB16F, EXTERNAL_RGB, EXTERNAL_RGB, TYPE_F16, DDS_UNKNOWN},							//RGB16F,
			{  8, glm::uvec3(1), 64,  4, false, INTERNAL_RGBA16F, EXTERNAL_RGBA, EXTERNAL_RGBA, TYPE_F16, DDS_R16G16B16A16_FLOAT},				//RGBA16F,

			{  4, glm::uvec3(1),  32,  1, false, INTERNAL_R32F, EXTERNAL_RED, EXTERNAL_RED, TYPE_F32, DDS_R32_FLOAT},							//R32F,
			{  8, glm::uvec3(1),  64,  2, false, INTERNAL_RG32F, EXTERNAL_RG, EXTERNAL_RG, TYPE_F32, DDS_R32G32_FLOAT},							//RG32F,
			{ 12, glm::uvec3(1),  96,  3, false, INTERNAL_RGB32F, EXTERNAL_RGB, EXTERNAL_RGB, TYPE_F32, DDS_R32G32B32_FLOAT},					//RGB32F,
			{ 16, glm::uvec3(1), 128,  4, false, INTERNAL_RGBA32F, EXTERNAL_RGBA, EXTERNAL_RGBA, TYPE_F32, DDS_R32G32B32A32_FLOAT},				//RGBA32F,

			/// Packed formats
			{  4, glm::uvec3(1), 32,  3, false, INTERNAL_RGB9E5, EXTERNAL_RGBA, EXTERNAL_BGRA, TYPE_UINT32_RGB9_E5, DDS_R9G9B9E5_SHAREDEXP},	//RGB9E5,
			{  4, glm::uvec3(1), 32,  3, false, INTERNAL_RG11B10F, EXTERNAL_RGBA, EXTERNAL_BGRA, TYPE_UINT32_RG11B10F},							//RG11B10F,
			{  1, glm::uvec3(1),  8,  3, false, INTERNAL_RG3B2, EXTERNAL_RGB, EXTERNAL_BGR, TYPE_UINT8_RG3B2, DDS_UNKNOWN},						//RG3B2,
			{  2, glm::uvec3(1), 16,  3, false, INTERNAL_R5G6B5, EXTERNAL_RGB, EXTERNAL_BGR, TYPE_UINT16_R5G6B5, DDS_B5G6R5_UNORM},				//R5G6B5,
			{  2, glm::uvec3(1), 16,  4, false, INTERNAL_RGB5A1, EXTERNAL_RGBA, EXTERNAL_BGRA, TYPE_UINT16_RGB5A1, DDS_B5G5R5A1_UNORM},			//RGB5A1,
			{  2, glm::uvec3(1), 16,  4, false, INTERNAL_RGBA4, EXTERNAL_RGBA, EXTERNAL_BGRA, TYPE_UINT16_RGBA4, DDS_B4G4R4A4_UNORM},			//RGBA4,
			{  4, glm::uvec3(1), 32,  4, false, INTERNAL_RGB10A2, EXTERNAL_RGBA, EXTERNAL_BGRA, TYPE_UINT32_RGB10A2, DDS_R10G10B10A2_UNORM},	//RGB10A2,

			/// Depth formats
			{  2, glm::uvec3(1), 16,  1, false, INTERNAL_D16, EXTERNAL_DEPTH, EXTERNAL_DEPTH, TYPE_NONE, DDS_D16_UNORM},						//D16,
			{  4, glm::uvec3(1), 32,  1, false, INTERNAL_D24, EXTERNAL_DEPTH, EXTERNAL_DEPTH, TYPE_NONE, DDS_UNKNOWN},							//D24X8,
			{  4, glm::uvec3(1), 32,  2, false, INTERNAL_D24S8, EXTERNAL_DEPTH, EXTERNAL_DEPTH, TYPE_NONE, DDS_D24_UNORM_S8_UINT},				//D24S8,
			{  4, glm::uvec3(1), 32,  1, false, INTERNAL_D32F, EXTERNAL_DEPTH, EXTERNAL_DEPTH, TYPE_NONE, DDS_D32_FLOAT},						//D32F,
			{  8, glm::uvec3(1), 64,  2, false, INTERNAL_D32FS8X24, EXTERNAL_DEPTH, EXTERNAL_DEPTH, TYPE_NONE, DDS_D32_FLOAT_S8X24_UINT},		//D32FS8X24,

			/// Compressed formats
			{  8, glm::uvec3(4, 4, 1), 4,  3, true, INTERNAL_RGB_DXT1, EXTERNAL_NONE, EXTERNAL_NONE, TYPE_NONE, DDS_BC1_UNORM},					//RGB_DXT1,
			{  8, glm::uvec3(4, 4, 1), 4,  4, true, INTERNAL_RGBA_DXT1, EXTERNAL_NONE, EXTERNAL_NONE, TYPE_NONE, DDS_BC1_UNORM},				//RGBA_DXT1,
			{ 16, glm::uvec3(4, 4, 1), 8,  4, true, INTERNAL_RGBA_DXT3, EXTERNAL_NONE, EXTERNAL_NONE, TYPE_NONE, DDS_BC2_UNORM},				//RGBA_DXT3,
			{ 16, glm::uvec3(4, 4, 1), 8,  4, true, INTERNAL_RGBA_DXT5, EXTERNAL_NONE, EXTERNAL_NONE, TYPE_NONE, DDS_BC3_UNORM},				//RGBA_DXT5,
			{  8, glm::uvec3(4, 4, 1), 4,  1, true, INTERNAL_R_ATI1N_UNORM, EXTERNAL_NONE, EXTERNAL_NONE, TYPE_NONE, DDS_BC4_UNORM},			//R_ATI1N_UNORM,
			{  8, glm::uvec3(4, 4, 1), 4,  1, true, INTERNAL_R_ATI1N_SNORM, EXTERNAL_NONE, EXTERNAL_NONE, TYPE_NONE, DDS_BC4_SNORM},			//R_ATI1N_SNORM,
			{ 16, glm::uvec3(4, 4, 1), 8,  2, true, INTERNAL_RG_ATI2N_UNORM, EXTERNAL_NONE, EXTERNAL_NONE, TYPE_NONE, DDS_BC5_UNORM},			//RG_ATI2N_UNORM,
			{ 16, glm::uvec3(4, 4, 1), 8,  2, true, INTERNAL_RG_ATI2N_SNORM, EXTERNAL_NONE, EXTERNAL_NONE, TYPE_NONE, DDS_BC5_SNORM},			//RG_ATI2N_SNORM,
			{ 16, glm::uvec3(4, 4, 1), 8,  3, true, INTERNAL_RGB_BP_UNSIGNED_FLOAT, EXTERNAL_NONE, EXTERNAL_NONE, TYPE_NONE, DDS_BC6H_UF16},	//RGB_BP_UF16,
			{ 16, glm::uvec3(4, 4, 1), 8,  3, true, INTERNAL_RGB_BP_SIGNED_FLOAT, EXTERNAL_NONE, EXTERNAL_NONE, TYPE_NONE, DDS_BC6H_SF16},		//RGB_BP_SF16,
			{ 16, glm::uvec3(4, 4, 1), 8,  3, true, INTERNAL_RGB_BP_UNORM, EXTERNAL_NONE, EXTERNAL_NONE, TYPE_NONE, DDS_BC7_UNORM},				//RGB_BP_UNORM,

			// sRGB formats
			{  3, glm::uvec3(1), 24,  3, false, INTERNAL_SRGB8, EXTERNAL_RGB, EXTERNAL_BGR, TYPE_U8, DDS_B8G8R8X8_UNORM_SRGB},						//SRGB8,
			{  4, glm::uvec3(1), 32,  4, false, INTERNAL_SRGB8_ALPHA8, EXTERNAL_RGBA, EXTERNAL_BGRA, TYPE_U8, DDS_R8G8B8A8_UNORM_SRGB},				//SRGB8_ALPHA8,
			{  8, glm::uvec3(4, 4, 1), 4,  3, true, INTERNAL_SRGB_DXT1, EXTERNAL_NONE, EXTERNAL_NONE, TYPE_NONE, DDS_BC1_UNORM_SRGB},				//sRGB_DXT1,
			{  8, glm::uvec3(4, 4, 1), 4,  4, true, INTERNAL_SRGB_ALPHA_DXT1, EXTERNAL_NONE, EXTERNAL_NONE, TYPE_NONE, DDS_BC1_UNORM_SRGB},			//sRGB_DXT1,
			{ 16, glm::uvec3(4, 4, 1), 8,  4, true, INTERNAL_SRGB_ALPHA_DXT3, EXTERNAL_NONE, EXTERNAL_NONE, TYPE_NONE, DDS_BC2_UNORM_SRGB},			//sRGB_DXT3,
			{ 16, glm::uvec3(4, 4, 1), 8,  4, true, INTERNAL_SRGB_ALPHA_DXT5, EXTERNAL_NONE, EXTERNAL_NONE, TYPE_NONE, DDS_BC3_UNORM_SRGB},			//sRGB_DXT5,
			{ 16, glm::uvec3(4, 4, 1), 8,  3, true, INTERNAL_SRGB_BP_UNORM, EXTERNAL_NONE, EXTERNAL_NONE, TYPE_NONE, DDS_BC7_UNORM_SRGB},			//sRGB_BP,
		};

		return Desc[Format];
	};
}//namespace detail

	inline storage::impl::impl() :
		Layers(0),
		Faces(0),
		Levels(0),
		Format(FORMAT_NULL),
		Dimensions(0),
		BlockSize(0),
		BlockDimensions(0)
	{}
	
	inline storage::impl::impl
	(
		size_type const & Layers,
		size_type const & Faces,
		size_type const & Levels,
		format_type const & Format,
		dimensions_type const & Dimensions,
		size_type const & BlockSize,
		dimensions_type const & BlockDimensions
	) :
		Layers(Layers),
		Faces(Faces),
		Levels(Levels),
		Format(Format),
		Dimensions(Dimensions),
		BlockSize(BlockSize),
		BlockDimensions(BlockDimensions)
	{}
	
	inline storage::storage()
	{}

	inline storage::storage
	(
		size_type const & Layers, 
		size_type const & Faces,
		size_type const & Levels,
		format_type const & Format,
		dimensions_type const & Dimensions
	) :
		Impl(new impl(
			Layers, 
			Faces, 
			Levels, 
			Format, 
			Dimensions, 
			gli::block_size(Format), 
			gli::block_dimensions(Format)))
	{
		Impl->Data.resize(this->layerSize() * Layers);
	}

	inline storage::storage
	(
		size_type const & Layers, 
		size_type const & Faces,
		size_type const & Levels,
		dimensions_type const & Dimensions,
		size_type const & BlockSize,
		dimensions_type const & BlockDimensions
	) : 
		Impl(new impl(
			Layers, 
			Faces, 
			Levels, 
			FORMAT_NULL, 
			Dimensions, 
			BlockSize, 
			BlockDimensions))
	{
		Impl->Data.resize(this->layerSize() * Layers);	
	}

	inline bool storage::empty() const
	{
		if(this->Impl.get() == 0)
			return true;
		return this->Impl->Data.empty();
	}

	inline storage::format_type storage::format() const
	{
		assert(!this->empty());

		return this->Impl->Format;
	}

	inline storage::size_type storage::layers() const
	{
		return this->Impl->Layers;
	}

	inline storage::size_type storage::faces() const
	{
		return this->Impl->Faces;
	}

	inline storage::size_type storage::levels() const
	{
		return this->Impl->Levels;
	}

	inline storage::size_type storage::blockSize() const
	{
		return this->Impl->BlockSize;
	}

	inline storage::dimensions_type storage::blockDimensions() const
	{
		return this->Impl->BlockDimensions;
	}

	inline storage::dimensions_type storage::dimensions
	(
		size_type const & Level
	) const
	{
		assert(Level < this->Impl->Levels);

		return glm::max(this->Impl->Dimensions >> storage::dimensions_type(Level), storage::dimensions_type(1));
	}

	inline storage::size_type storage::size() const
	{
		assert(!this->empty());

		return this->Impl->Data.size();
	}

	inline glm::byte const * storage::data() const
	{
		assert(!this->empty());

		return &this->Impl->Data[0];
	}

	inline glm::byte * storage::data()
	{
		assert(!this->empty());

		return &this->Impl->Data[0];
	}

	inline storage::size_type storage::levelSize
	(
		storage::size_type const & Level
	) const
	{
		assert(Level < this->Impl->Levels);

		return this->blockSize() * glm::compMul(glm::higherMultiple(
			this->dimensions(Level), 
			this->blockDimensions()) / this->blockDimensions()); 
	}

	inline storage::size_type storage::faceSize() const
	{
		size_type FaceSize(0);

		// The size of a face is the sum of the size of each level.
		for(storage::size_type Level(0); Level < this->levels(); ++Level)
			FaceSize += this->levelSize(Level);

		return FaceSize;// * TexelSize;
	}

	inline storage::size_type storage::layerSize() const
	{
		// The size of a layer is the sum of the size of each face.
		// All the faces have the same size.
		return this->faceSize() * this->faces();
	}

/*
	inline storage extractLayers
	(
		storage const & Storage, 
		storage::size_type const & Offset, 
		storage::size_type const & Size
	)
	{
		assert(Storage.layers() > 1);
		assert(Storage.layers() >= Size);
		assert(Storage.faces() > 0);
		assert(Storage.levels() > 0);

		storage SubStorage(
			Size, 
			Storage.faces(), 
			Storage.levels(),
			Storage.dimensions(0),
			Storage.blockSize());

		memcpy(
			SubStorage.data(), 
			Storage.data() + Storage.linearAddressing(Offset, 0, 0), 
			Storage.layerSize() * Size);

		return SubStorage;
	}
*/
/*
	inline storage extractFace
	(
		storage const & Storage, 
		face const & Face
	)
	{
		assert(Storage.faces() > 1);
		assert(Storage.levels() > 0);

		storage SubStorage(
			Storage.layers(),
			Face, 
			Storage.levels(),
			Storage.dimensions(0),
			Storage.blockSize());

		memcpy(
			SubStorage.data(), 
			Storage.data() + Storage.linearAddressing(0, storage::size_type(Face), 0), 
			Storage.faceSize());

		return SubStorage;
	}
*/
/*
	inline storage extractLevel
	(
		storage const & Storage, 
		storage::size_type const & Level
	)
	{
		assert(Storage.layers() == 1);
		assert(Storage.faces() == 1);
		assert(Storage.levels() >= 1);

		storage SubStorage(
			1, // layer
			glm::uint(FACE_DEFAULT),
			1, // level
			Storage.dimensions(0),
			Storage.blockSize());

		memcpy(
			SubStorage.data(), 
			Storage.data() + Storage.linearAddressing(0, 0, Level), 
			Storage.levelSize(Level));

		return SubStorage;
	}
*/
/*
	inline void copy_layers
	(
		storage const & SourceStorage, 
		storage::size_type const & SourceLayerOffset,
		storage::size_type const & SourceLayerSize,
		storage & DestinationStorage, 
		storage::size_type const & DestinationLayerOffset
	)
	{
		assert(DestinationStorage.blockSize() == SourceStorage.blockSize());
		assert(DestinationStorage.layers() <= SourceStorage.layers());
		assert(SourceStorage.layers() <= SourceLayerOffset + SourceLayerSize);
		assert(DestinationStorage.layers() <= DestinationLayerOffset + SourceLayerSize);

		std::size_t OffsetSrc = SourceStorage.linearAddressing(SourceLayerOffset, 0, 0);
		std::size_t OffsetDst = DestinationStorage.linearAddressing(DestinationLayerOffset, 0, 0);

		memcpy(
			DestinationStorage.data() + OffsetDst * DestinationStorage.blockSize(), 
			SourceStorage.data() + OffsetSrc * SourceStorage.blockSize(), 
			SourceStorage.layerSize() * SourceLayerSize * SourceStorage.blockSize());
	}
*/
	inline std::size_t block_size(format const & Format)
	{
		return detail::getFormatInfo(Format).BlockSize;
	}

	inline glm::uvec3 block_dimensions(format const & Format)
	{
		return detail::getFormatInfo(Format).BlockDimensions;
	}

	inline std::size_t bits_per_pixel(format const & Format)
	{
		return detail::getFormatInfo(Format).BBP;
	}

	inline std::size_t component_count(format const & Format)
	{
		return detail::getFormatInfo(Format).Component;
	}

	inline bool is_compressed(format const & Format)
	{
		return detail::getFormatInfo(Format).Compressed;
	}

	inline internalFormat internal_format(format const & Format)
	{
		return detail::getFormatInfo(Format).Internal;
	}

	inline externalFormat external_format(format const & Format)
	{
		return detail::getFormatInfo(Format).External;
	}

	inline typeFormat type_format(format const & Format)
	{
		return detail::getFormatInfo(Format).Type;
	}
}//namespace gli
