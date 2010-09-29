///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-09-27
// Updated : 2010-09-27
// Licence : This source is under MIT License
// File    : gli/core/generate_mipmaps.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace gli
{
	inline texture generateMipmaps
	(
		texture const & Image, 
		texture::level_type const & BaseLevel
	)
	{
		assert(BaseLevel < Image.levels());
		texture::format_type Format = Image[BaseLevel].format();

		assert(Format == R8U || Format == RG8U || Format == RGB8U || Format == RGBA8U);
		texture::level_type Levels = std::size_t(glm::log2(float(glm::compMax(Image[0].dimensions())))) + 1;

		texture Result(Levels);
		for(texture::level_type Level = 0; Level <= BaseLevel; ++Level)
			Result[Level] = detail::duplicate(Image[Level]);

		for(texture::level_type Level = BaseLevel; Level < Levels - 1; ++Level)
		{
			std::size_t BaseWidth = Result[Level + 0].dimensions().x;
			texture::value_type * DataSrc = Result[Level + 0].data();

			texture::dimensions_type LevelDimensions = Result[Level + 0].dimensions() >> texture::dimensions_type(1);
			LevelDimensions = glm::max(LevelDimensions, texture::dimensions_type(1));
			texture::size_type ValueSize = Result[Level + 0].value_size();
			texture::size_type Components = Result[Level + 0].components();

			texture::data_type DataDst(new texture::value_type[glm::compMul(LevelDimensions) * Components]);

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

				glm::u32 Data00 = reinterpret_cast<texture::value_type*>(DataSrc)[Index00];
				glm::u32 Data01 = reinterpret_cast<texture::value_type*>(DataSrc)[Index01];
				glm::u32 Data11 = reinterpret_cast<texture::value_type*>(DataSrc)[Index11];
				glm::u32 Data10 = reinterpret_cast<texture::value_type*>(DataSrc)[Index10];

				texture::value_type Result = (Data00 + Data01 + Data11 + Data10) >> 2;
				texture::value_type * Data = reinterpret_cast<texture::value_type*>(DataDst.get());

				*(Data + ((i + j * LevelDimensions.x) * Components + c)) = Result;
			}

			Result[Level + 1] = texture::mipmap(LevelDimensions, Format, DataDst);
		}

		return Result;
	}

}//namespace gli
