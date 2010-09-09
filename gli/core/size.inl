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
	inline glm::uint32 getFormatBlockSize(format const & Format)
	{
		switch(Format)
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
}//namespace detail

	inline image::size_type size
	(
		image const & Image, 
		size_type const & SizeType
	)
	{
		image::size_type Result = 0;
		for(image::level_type Level = 0; Level < Image.levels(); ++Level)
			Result += size(Image[Level], SizeType);
		return Result;
	}

	inline image::size_type size
	(
		mipmap const & Mipmap, 
		size_type const & SizeType
	)
	{
		image::size_type Result = 0;
		 
		image::dimensions_type Dimension = Mipmap.dimensions();
		Dimension = glm::max(Dimension, image::dimensions_type(1));

		image::size_type BlockCount = ((Dimension.x + 3) >> 2) * ((Dimension.y + 3) >> 2);
		image::size_type BlockSize = detail::getFormatBlockSize(Mipmap.format());
		Result = BlockCount * BlockSize;

		return Result;
	}

}//namespace
