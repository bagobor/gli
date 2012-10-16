///////////////////////////////////////////////////////////////////////////////////
/// OpenGL Image (gli.g-truc.net)
///
/// Copyright (c) 2008 - 2012 G-Truc Creation (www.g-truc.net)
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
/// @file gli/core/format.inl
/// @date 2012-10-16 / 2012-10-16
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

namespace gli{
namespace detail
{
	struct format_desc
	{
		storage::size_type BlockSize;
		storage::size_type BlockWidth;
		storage::size_type BlockHeight;
		storage::size_type BBP;
		storage::size_type Component;
	};

	inline format_desc const getFormatInfo(format const & Format)
	{
		format_desc const Desc[FORMAT_MAX] =
		{
			{  0,  0, 0, 0,  0},	//FORMAT_NULL

			// Unsigned integer formats
			{  1, 1, 1,  8,  1},	//R8U,
			{  2, 1, 1, 16,  2},	//RG8U,
			{  3, 1, 1, 24,  3},	//RGB8U,
			{  4, 1, 1, 32,  4},	//RGBA8U,

			{  2, 1, 1, 16,  1},	//R16U,
			{  4, 1, 1, 32,  2},	//RG16U,
			{  6, 1, 1, 48,  3},	//RGB16U,
			{  8, 1, 1, 64,  4},	//RGBA16U,

			{  4, 1, 1,  32,  1},	//R32U,
			{  8, 1, 1,  64,  2},	//RG32U,
			{ 12, 1, 1,  96,  3},	//RGB32U,
			{ 16, 1, 1, 128,  4},	//RGBA32U,

			//// Signed integer formats
			{  4, 1, 1,  32,  1},	//R8I,
			{  8, 1, 1,  64,  2},	//RG8I,
			{ 12, 1, 1,  96,  3},	//RGB8I,
			{ 16, 1, 1, 128,  4},	//RGBA8I,

			{  2, 1, 1, 16,  1},	//R16I,
			{  4, 1, 1, 32,  2},	//RG16I,
			{  6, 1, 1, 48,  3},	//RGB16I,
			{  8, 1, 1, 64,  4},	//RGBA16I,

			{  4, 1, 1,  32,  1},	//R32I,
			{  8, 1, 1,  64,  2},	//RG32I,
			{ 12, 1, 1,  96,  3},	//RGB32I,
			{ 16, 1, 1, 128,  4},	//RGBA32I,

			//// Floating formats
			{  2, 1, 1, 16,  1},	//R16F,
			{  4, 1, 1, 32,  2},	//RG16F,
			{  6, 1, 1, 48,  3},	//RGB16F,
			{  8, 1, 1, 64,  4},	//RGBA16F,

			{  4, 1, 1,  32,  1},	//R32F,
			{  8, 1, 1,  64,  2},	//RG32F,
			{ 12, 1, 1,  96,  3},	//RGB32F,
			{ 16, 1, 1, 128,  4},	//RGBA32F,

			//// Packed formats
			{  4, 1, 1, 32,  3},	//RGBE8,
			{  4, 1, 1, 32,  3},	//RGB9E5,
			{  4, 1, 1, 32,  3},	//RG11B10F,
			{  2, 1, 1, 16,  3},	//R5G6B5,
			{  2, 1, 1, 16,  4},	//RGBA4,
			{  4, 1, 1, 32,  3},	//RGB10A2,

			//// Depth formats
			{  2, 1, 1, 16,  1},	//D16,
			{  4, 1, 1, 32,  1},	//D24X8,
			{  4, 1, 1, 32,  2},	//D24S8,
			{  4, 1, 1, 32,  1},	//D32F,
			{  8, 1, 1, 64,  2},	//D32FS8X24,

			//// Compressed formats
			{  8, 4, 4, 4,  4},	//DXT1,
			{ 16, 4, 4, 8,  4},	//DXT3,
			{ 16, 4, 4, 8,  4},	//DXT5,
			{  8, 4, 4, 4,  1},	//ATI1N_UNORM,
			{  8, 4, 4, 4,  1},	//ATI1N_SNORM,
			{ 16, 4, 4, 8,  2},	//ATI2N_UNORM,
			{ 16, 4, 4, 8,  2},	//ATI2N_SNORM,
			{ 16, 4, 4, 8,  3},	//BP_UF16,
			{ 16, 4, 4, 8,  3},	//BP_SF16,
			{ 16, 4, 4, 8,  4},	//BP,
		};

		return Desc[Format];
	};
}//namespace detail
}//namespace gli
