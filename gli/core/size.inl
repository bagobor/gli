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
	struct format_desc
	{
		image::size_type BlockSize;
		image::size_type BBP;
	};

	inline format_desc getFormatInfo(gli::format const & Format)
	{
		format_desc Desc[] =
		{
			{0, 0}
		};

		return Desc[Format];
	};

	inline image::size_type sizeBlock
	(
		mipmap const & Mipmap
	)
	{
		switch(Mipmap.format())
		{
		default:
			return 0;
		case DXT1:
			return 8;
		case DXT3:
			return 16;
		case DXT5:
			return 16;
		case R16F:
			return 2;
		case RG16F:
			return 4;
		case RGBA16F:
			return 8;
		case R32F:
			return 4;
		case RG32F:
			return 8;
		case RGBA32F:
			return 16;
		}
	}

	inline image::size_type sizeBlock
	(
		image const & Image
	)
	{
		return sizeBlock(Image[0]);
	}

	inline image::size_type sizeLinear
	(
		mipmap const & Mipmap
	)
	{
		image::size_type Result = 0;
		 
		image::dimensions_type Dimension = Mipmap.dimensions();
		Dimension = glm::max(Dimension, image::dimensions_type(1));

		image::size_type BlockCount = ((Dimension.x + 3) >> 2) * ((Dimension.y + 3) >> 2);
		image::size_type BlockSize = sizeBlock(Mipmap.format());
		Result = BlockCount * BlockSize;

		return Result;
	}

	inline image::size_type sizeLinear
	(
		image const & Image
	)
	{
		image::size_type Result = 0;
		for(image::level_type Level = 0; Level < Image.levels(); ++Level)
			Result += sizeLinear(Image[Level]);
		return Result;
	}

	inline image::size_type sizeBitPerPixel
	(
		mipmap const & Mipmap
	)
	{
		switch(Mipmap.format())
		{
		default:
			return 0;
		case DXT1:
			return 4;
		case DXT3:
			return 8;
		case DXT5:
			return 8;
		case R16F:
			return 16;
		case RG16F:
			return 32;
		case RGBA16F:
			return 64;
		case R32F:
			return 32;
		case RG32F:
			return 64;
		case RGBA32F:
			return 128;
		}
	}

	inline image::size_type sizeBitPerPixel
	(
		image const & Image
	)
	{
		return sizeBitPerPixel(Image[0]);
	}

}//namespace detail

	inline image::size_type size
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
		};
	}

	inline image::size_type size
	(
		image const & Image,
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
		};
	}

/*
	template <>
	image::size_type size<LINEAR_SIZE>
	(
		image const & Image
	)
	{
		image::size_type Result = 0;
		for(image::level_type Level = 0; Level < Image.levels(); ++Level)
			Result += size<LINEAR_SIZE>(Image[Level]);
		return Result;
	}

	template <>
	image::size_type size<LINEAR_SIZE>
	(
		mipmap const & Mipmap
	)
	{
		image::size_type Result = 0;
		 
		image::dimensions_type Dimension = Mipmap.dimensions();
		Dimension = glm::max(Dimension, image::dimensions_type(1));

		image::size_type BlockCount = ((Dimension.x + 3) >> 2) * ((Dimension.y + 3) >> 2);
		image::size_type BlockSize = size<BLOCK_SIZE>(Mipmap.format());
		Result = BlockCount * BlockSize;

		return Result;
	}

	template <>
	image::size_type size<BLOCK_SIZE>
	(
		image const & Image
	)
	{
		return size<BLOCK_SIZE>(Image[0]);
	}

	template <>
	image::size_type size<BLOCK_SIZE>
	(
		mipmap const & Mipmap
	)
	{
		switch(Mipmap.format())
		{
		default:
			return 0;
		case DXT1:
			return 8;
		case DXT3:
			return 16;
		case DXT5:
			return 16;
		case R16F:
			return 2;
		case RG16F:
			return 4;
		case RGBA16F:
			return 8;
		case R32F:
			return 4;
		case RG32F:
			return 8;
		case RGBA32F:
			return 16;
		}
	}

	template <>
	image::size_type size<BIT_PER_PIXEL>
	(
		image const & Image
	)
	{
		return size<BIT_PER_PIXEL>(Image[0]);
	}

	template <>
	image::size_type size<BIT_PER_PIXEL>
	(
		mipmap const & Mipmap
	)
	{
		switch(Mipmap.format())
		{
		default:
			return 0;
		case DXT1:
			return 4;
		case DXT3:
			return 8;
		case DXT5:
			return 8;
		case R16F:
			return 16;
		case RG16F:
			return 32;
		case RGBA16F:
			return 64;
		case R32F:
			return 32;
		case RG32F:
			return 64;
		case RGBA32F:
			return 128;
		}
	}
*/
}//namespace
