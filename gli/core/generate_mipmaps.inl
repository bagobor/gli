///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-09-27
// Updated : 2010-09-27
// Licence : This source is under MIT License
// File    : gli/core/generate_mipmaps.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace gli
{
	inline texture2D generateMipmaps
	(
		texture2D const & Texture, 
		texture2D::size_type const & BaseLevel
	)
	{
		assert(BaseLevel < Texture.levels());
		texture2D::format_type const Format = Texture.format();
		texture2D::size_type const ValueSize = detail::getFormatInfo(Format).BlockSize;
		texture2D::size_type const Components = detail::getFormatInfo(Format).Component;

		assert(Format == R8U || Format == RG8U || Format == RGB8U || Format == RGBA8U);
		texture2D::size_type Levels = std::size_t(glm::log2(float(glm::compMax(Texture[0].dimensions())))) + 1;

		texture2D Result(Levels, Format, Texture.dimensions());

		for(texture2D::size_type Level = BaseLevel; Level < Levels - 1; ++Level)
		{
			std::size_t BaseWidth = Result[Level + 0].dimensions().x;
			glm::byte * DataSrc = reinterpret_cast<glm::byte *>(Result[Level + 0].data());

			texture2D::dimensions_type LevelDimensions = texture2D::dimensions_type(Result[Level + 0].dimensions()) >> texture2D::dimensions_type(1);
			LevelDimensions = glm::max(LevelDimensions, texture2D::dimensions_type(1));

			std::vector<detail::storage::data_type> DataDst(detail::storage::size_type(glm::compMul(LevelDimensions)) * Components);

			for(std::size_t j = 0; j < LevelDimensions.y; ++j)
			for(std::size_t i = 0; i < LevelDimensions.x;  ++i)
			for(std::size_t c = 0; c < Components; ++c)
			{
				std::size_t x = (i << 1);
				std::size_t y = (j << 1);

				std::size_t Index00 = ((x + 0) + (y + 0) * BaseWidth) * Components + c;
				std::size_t Index01 = ((x + 0) + (y + 1) * BaseWidth) * Components + c;
				std::size_t Index11 = ((x + 1) + (y + 1) * BaseWidth) * Components + c;
				std::size_t Index10 = ((x + 1) + (y + 0) * BaseWidth) * Components + c;

				glm::u32 Data00 = reinterpret_cast<glm::byte *>(DataSrc)[Index00];
				glm::u32 Data01 = reinterpret_cast<glm::byte *>(DataSrc)[Index01];
				glm::u32 Data11 = reinterpret_cast<glm::byte *>(DataSrc)[Index11];
				glm::u32 Data10 = reinterpret_cast<glm::byte *>(DataSrc)[Index10];

				glm::byte Result = (Data00 + Data01 + Data11 + Data10) >> 2;
				glm::byte * Data = &DataDst[0];

				*(Data + ((i + j * LevelDimensions.x) * Components + c)) = Result;
			}

			memcpy(Result[Level + 1].data(), &DataDst[0], DataDst.size());
		}

		return Result;
	}

}//namespace gli
