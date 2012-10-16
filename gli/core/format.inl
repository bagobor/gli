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
		std::size_t BlockSize;
		std::size_t BlockWidth;
		std::size_t BlockHeight;
		std::size_t BBP;
		std::size_t Component;
		bool Compressed;
	};

	inline format_desc const getFormatInfo(format const & Format)
	{
		format_desc const Desc[FORMAT_MAX] =
		{
			{  0,  0, 0, 0,  0, false},	//FORMAT_NULL

			// Unsigned integer formats
			{  1, 1, 1,  8,  1, false},	//R8U,
			{  2, 1, 1, 16,  2, false},	//RG8U,
			{  3, 1, 1, 24,  3, false},	//RGB8U,
			{  4, 1, 1, 32,  4, false},	//RGBA8U,

			{  2, 1, 1, 16,  1, false},	//R16U,
			{  4, 1, 1, 32,  2, false},	//RG16U,
			{  6, 1, 1, 48,  3, false},	//RGB16U,
			{  8, 1, 1, 64,  4, false},	//RGBA16U,

			{  4, 1, 1,  32,  1, false},	//R32U,
			{  8, 1, 1,  64,  2, false},	//RG32U,
			{ 12, 1, 1,  96,  3, false},	//RGB32U,
			{ 16, 1, 1, 128,  4, false},	//RGBA32U,

			//// Signed integer formats
			{  4, 1, 1,  32,  1, false},	//R8I,
			{  8, 1, 1,  64,  2, false},	//RG8I,
			{ 12, 1, 1,  96,  3, false},	//RGB8I,
			{ 16, 1, 1, 128,  4, false},	//RGBA8I,

			{  2, 1, 1, 16,  1, false},	//R16I,
			{  4, 1, 1, 32,  2, false},	//RG16I,
			{  6, 1, 1, 48,  3, false},	//RGB16I,
			{  8, 1, 1, 64,  4, false},	//RGBA16I,

			{  4, 1, 1,  32,  1, false},	//R32I,
			{  8, 1, 1,  64,  2, false},	//RG32I,
			{ 12, 1, 1,  96,  3, false},	//RGB32I,
			{ 16, 1, 1, 128,  4, false},	//RGBA32I,

			//// Floating formats
			{  2, 1, 1, 16,  1, false},	//R16F,
			{  4, 1, 1, 32,  2, false},	//RG16F,
			{  6, 1, 1, 48,  3, false},	//RGB16F,
			{  8, 1, 1, 64,  4, false},	//RGBA16F,

			{  4, 1, 1,  32,  1, false},	//R32F,
			{  8, 1, 1,  64,  2, false},	//RG32F,
			{ 12, 1, 1,  96,  3, false},	//RGB32F,
			{ 16, 1, 1, 128,  4, false},	//RGBA32F,

			//// Packed formats
			{  4, 1, 1, 32,  3, false},	//RGBE8,
			{  4, 1, 1, 32,  3, false},	//RGB9E5,
			{  4, 1, 1, 32,  3, false},	//RG11B10F,
			{  2, 1, 1, 16,  3, false},	//R5G6B5,
			{  2, 1, 1, 16,  4, false},	//RGBA4,
			{  4, 1, 1, 32,  3, false},	//RGB10A2,

			//// Depth formats
			{  2, 1, 1, 16,  1, false},	//D16,
			{  4, 1, 1, 32,  1, false},	//D24X8,
			{  4, 1, 1, 32,  2, false},	//D24S8,
			{  4, 1, 1, 32,  1, false},	//D32F,
			{  8, 1, 1, 64,  2, false},	//D32FS8X24,

			//// Compressed formats
			{  8, 4, 4, 4,  4, true},	//DXT1,
			{ 16, 4, 4, 8,  4, true},	//DXT3,
			{ 16, 4, 4, 8,  4, true},	//DXT5,
			{  8, 4, 4, 4,  1, true},	//ATI1N_UNORM,
			{  8, 4, 4, 4,  1, true},	//ATI1N_SNORM,
			{ 16, 4, 4, 8,  2, true},	//ATI2N_UNORM,
			{ 16, 4, 4, 8,  2, true},	//ATI2N_SNORM,
			{ 16, 4, 4, 8,  3, true},	//BP_UF16,
			{ 16, 4, 4, 8,  3, true},	//BP_SF16,
			{ 16, 4, 4, 8,  4, true},	//BP,
		};

		return Desc[Format];
	};
}//namespace detail

	inline std::size_t block_size(format const & Format)
	{
		return detail::getFormatInfo(Format).BlockSize;
	}

	inline std::size_t block_width(format const & Format)
	{
		return detail::getFormatInfo(Format).BlockWidth;
	}

	inline std::size_t block_height(format const & Format)
	{
		return detail::getFormatInfo(Format).BlockHeight;
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
}//namespace gli
