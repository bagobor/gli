///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-12-19
// Updated : 2010-09-08
// Licence : This source is under MIT License
// File    : gli/core/size.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace gli{
namespace detail
{
	enum format
	{
		FORMAT_NULL,

		// Unsigned integer formats
		R8U,
		RG8U,
		RGB8U,
		RGBA8U,

		R16U,
		RG16U,
		RGB16U,
		RGBA16U,

		R32U,
		RG32U,
		RGB32U,
		RGBA32U,

		// Signed integer formats
		R8I,
		RG8I,
		RGB8I,
		RGBA8I,

		R16I,
		RG16I,
		RGB16I,
		RGBA16I,

		R32I,
		RG32I,
		RGB32I,
		RGBA32I,

		// Floating formats
		R16F,
		RG16F,
		RGB16F,
		RGBA16F,

		R32F,
		RG32F,
		RGB32F,
		RGBA32F,

		// Packed formats
		RGBE8,
		RGB9E5,
		RG11B10F,
		RGB565,
		RGBA4,
		RGB10A2,

		// Depth formats
		D16,
		D24X8,
		D24S8,
		D32F,
		D32FS8X24,

		// Compressed formats
		DXT1,
		DXT3,
		DXT5,
		ATI1N,
		ATI2N,
		BP_FLOAT,
		BP,

		FORMAT_MAX
	};

	struct format_desc
	{
		texture::size_type BlockSize;
		texture::size_type BBP;
		texture::size_type Component;
	};

	inline format_desc getFormatInfo(gli::format const & Format)
	{
		format_desc Desc[FORMAT_MAX] =
		{
			{  0,  0,  0},	//FORMAT_NULL
			//// Unsigned integer formats
			{  1,   8,  1},	//R8U,
			{  2,  16,  2},	//RG8U,
			{  3,  24,  3},	//RGB8U,
			{  4,  32,  4},	//RGBA8U,

			{  2,  16,  1},	//R16U,
			{  4,  32,  2},	//RG16U,
			{  6,  48,  3},	//RGB16U,
			{  8,  64,  4},	//RGBA16U,

			{  4,  32,  1},	//R32U,
			{  8,  64,  2},	//RG32U,
			{ 12,  96,  3},	//RGB32U,
			{ 16, 128,  4},	//RGBA32U,

			//// Signed integer formats
			{  4,  32,  1},	//R8I,
			{  8,  64,  2},	//RG8I,
			{ 12,  96,  3},	//RGB8I,
			{ 16, 128,  4},	//RGBA8I,

			{  2,  16,  1},	//R16I,
			{  4,  32,  2},	//RG16I,
			{  6,  48,  3},	//RGB16I,
			{  8,  64,  4},	//RGBA16I,

			{  4,  32,  1},	//R32I,
			{  8,  64,  2},	//RG32I,
			{ 12,  96,  3},	//RGB32I,
			{ 16, 128,  4},	//RGBA32I,

			//// Floating formats
			{  2,  16,  1},	//R16F,
			{  4,  32,  2},	//RG16F,
			{  6,  48,  3},	//RGB16F,
			{  8,  64,  4},	//RGBA16F,

			{  4,  32,  1},	//R32F,
			{  8,  64,  2},	//RG32F,
			{ 12,  96,  3},	//RGB32F,
			{ 16, 128,  4},	//RGBA32F,

			//// Packed formats
			{  4,  32,  3},	//RGBE8,
			{  4,  32,  3},	//RGB9E5,
			{  4,  32,  3},	//RG11B10F,
			{  2,  16,  3},	//RGB565,
			{  2,  16,  4},	//RGBA4,
			{  4,  32,  3},	//RGB10A2,

			//// Depth formats
			{  2,  16,  1},	//D16,
			{  4,  32,  1},	//D24X8,
			{  4,  32,  2},	//D24S8,
			{  4,  32,  1},	//D32F,
			{  8,  64,  2},	//D32FS8X24,

			//// Compressed formats
			{  8,   4,  4},	//DXT1,
			{ 16,   8,  4},	//DXT3,
			{ 16,   8,  4},	//DXT5,
			{  8,   4,  1},	//ATI1N,
			{ 16,   8,  2},	//ATI2N,
			{ 32,   8,  3},	//BP_FLOAT,
			{ 32,   8,  4},	//BP,
		};

		return Desc[Format];
	};

	inline texture::size_type sizeBlock
	(
		mipmap const & Mipmap
	)
	{
		return getFormatInfo(Mipmap.format()).BlockSize;
	}

	inline texture::size_type sizeBlock
	(
		texture const & Image
	)
	{
		return sizeBlock(Image[0]);
	}

	inline texture::size_type sizeBitPerPixel
	(
		mipmap const & Mipmap
	)
	{
		return getFormatInfo(Mipmap.format()).BBP;
	}

	inline texture::size_type sizeBitPerPixel
	(
		texture const & Image
	)
	{
		return sizeBitPerPixel(Image[0]);
	}

	inline texture::size_type sizeLinear
	(
		mipmap const & Mipmap
	)
	{
		texture::dimensions_type Dimension = Mipmap.dimensions();
		Dimension = glm::max(Dimension, texture::dimensions_type(1));

		texture::size_type BlockSize = sizeBlock(Mipmap);
		texture::size_type BPP = sizeBitPerPixel(Mipmap);
		texture::size_type BlockCount = 0;
		if((BlockCount << 3) == BPP)
			BlockCount = Dimension.x * Dimension.y;
		else
			BlockCount = ((Dimension.x + 3) >> 2) * ((Dimension.y + 3) >> 2);			

		return BlockCount * BlockSize;
	}

	inline texture::size_type sizeLinear
	(
		texture const & Image
	)
	{
		texture::size_type Result = 0;
		for(texture::level_type Level = 0; Level < Image.levels(); ++Level)
			Result += sizeLinear(Image[Level]);
		return Result;
	}

	inline texture::size_type sizeComponent
	(
		mipmap const & Mipmap
	)
	{
		return getFormatInfo(Mipmap.format()).Component;
	}

	inline texture::size_type sizeComponent
	(
		texture const & Image
	)
	{
		return sizeComponent(Image[0]);
	}

}//namespace detail

	inline texture::size_type size
	(
		mipmap const & Mipmap,
		size_type const & SizeType
	)
	{
		switch(SizeType)
		{
		case LINEAR_SIZE:
			return detail::sizeLinear(Mipmap);
		case BLOCK_SIZE:
			return detail::sizeBlock(Mipmap);
		case BIT_PER_PIXEL:
			return detail::sizeBitPerPixel(Mipmap);
		case COMPONENT:
			return detail::sizeComponent(Mipmap);
		default:
			assert(0);
			return 0;
		};
	}

	inline texture::size_type size
	(
		texture const & Image,
		size_type const & SizeType
	)
	{
		switch(SizeType)
		{
		case LINEAR_SIZE:
			return detail::sizeLinear(Image);
		case BLOCK_SIZE:
			return detail::sizeBlock(Image);
		case BIT_PER_PIXEL:
			return detail::sizeBitPerPixel(Image);
		case COMPONENT:
			return detail::sizeComponent(Image);
		default:
			assert(0);
			return 0;
		};
	}

}//namespace
