///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-12-19
// Updated : 2010-09-08
// Licence : This source is under MIT License
// File    : gli/core/operation.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstring>

namespace gli
{
	namespace detail
	{
		inline texture::image duplicate(texture::image const & Mipmap2D)
		{
			texture::image Result(Mipmap2D.dimensions(), Mipmap2D.format());
			memcpy(Result.data(), Mipmap2D.data(), Mipmap2D.capacity());
			return Result;	
		}

		inline texture::image flip(texture::image const & Mipmap2D)
		{
			texture::image Result(Mipmap2D.dimensions(), Mipmap2D.format());
			
			std::size_t ValueSize = Result.value_size();
			glm::byte * DstPtr = Result.data();
			glm::byte const * const SrcPtr = Mipmap2D.data();

			for(std::size_t j = 0; j < Result.dimensions().y; ++j)
			for(std::size_t i = 0; i < Result.dimensions().x; ++i)
			{
				std::size_t DstIndex = (i + j * Result.dimensions().y) * ValueSize;
				std::size_t SrcIndex = (i + (Result.dimensions().y - j) * Result.dimensions().x) * ValueSize;
				memcpy(DstPtr + DstIndex, SrcPtr + SrcIndex, ValueSize);
			}

			return Result;
		}

		inline texture::image mirror(texture::image const & Mipmap2D)
		{
			texture::image Result(Mipmap2D.dimensions(), Mipmap2D.format());

			std::size_t ValueSize = Mipmap2D.value_size();
			glm::byte * DstPtr = Result.data();
			glm::byte const * const SrcPtr = Mipmap2D.data();

			for(std::size_t j = 0; j < Result.dimensions().y; ++j)
			for(std::size_t i = 0; i < Result.dimensions().x; ++i)
			{
				std::size_t DstIndex = (i + j * Result.dimensions().x) * ValueSize;
				std::size_t SrcIndex = ((Result.dimensions().x - i) + j * Result.dimensions().x) * ValueSize;
				memcpy(DstPtr + DstIndex, SrcPtr + SrcIndex, ValueSize);
			}

			return Result;
		}

		inline texture::image swizzle
		(
			texture::image const & Mipmap, 
			glm::uvec4 const & Channel
		)
		{
			texture::image Result = detail::duplicate(Mipmap);

			glm::byte * DataDst = Result.data();
			glm::byte const * const DataSrc = Mipmap.data();

			gli::texture::size_type CompSize = Mipmap.value_size() / Mipmap.components();
			gli::texture::size_type TexelCount = Mipmap.capacity() / Mipmap.value_size();

			for(gli::texture::size_type t = 0; t < TexelCount; ++t)
			for(gli::texture::size_type c = 0; c < Mipmap.components(); ++c)
			{
				gli::texture::size_type IndexSrc = t * Mipmap.components() + Channel[glm::uvec4::size_type(c)];
				gli::texture::size_type IndexDst = t * Mipmap.components() + c;

				memcpy(DataDst + IndexDst, DataSrc + IndexSrc, CompSize);
			}

			return Result;
		}

		inline texture::image crop
		(
			texture::image const & Mipmap, 
			texture::dimensions_type const & Position, 
			texture::dimensions_type const & Size
		)
		{
			assert((Position.x + Size.x) <= Mipmap.dimensions().x && (Position.y + Size.y) <= Mipmap.dimensions().y);

			texture::image Result(Size, Mipmap.format());

			glm::byte* DstData = Result.data();
			glm::byte const * const SrcData = Mipmap.data();

			for(std::size_t j = 0; j < Size.y; ++j)
			{
				std::size_t DstIndex = 0                                + (0          + j) * Size.x         * Mipmap.value_size();
				std::size_t SrcIndex = Position.x * Mipmap.value_size() + (Position.y + j) * Mipmap.dimensions().x * Mipmap.value_size();
				memcpy(DstData + DstIndex, SrcData + SrcIndex, Mipmap.value_size() * Size.x);	
			}

			return Result;
		}

		inline texture::image copy
		(
			texture::image const & SrcMipmap, 
			texture::dimensions_type const & SrcPosition,
			texture::dimensions_type const & SrcSize,
			texture::image & DstMipmap, 
			texture::dimensions_type const & DstPosition
		)
		{
			assert((SrcPosition.x + SrcSize.x) <= SrcMipmap.dimensions().x && (SrcPosition.y + SrcSize.y) <= SrcMipmap.dimensions().y);
			assert(SrcMipmap.format() == DstMipmap.format());

			glm::byte * DstData = DstMipmap.data();
			glm::byte const * const SrcData = SrcMipmap.data();

			std::size_t SizeX = std::min(std::size_t(SrcSize.x + SrcPosition.x), std::size_t(DstMipmap.dimensions().x  + DstPosition.x));
			std::size_t SizeY = std::min(std::size_t(SrcSize.y + SrcPosition.y), std::size_t(DstMipmap.dimensions().y + DstPosition.y));

			for(std::size_t j = 0; j < SizeY; ++j)
			{
				std::size_t DstIndex = DstPosition.x * DstMipmap.value_size() + (DstPosition.y + j) * DstMipmap.dimensions().x * DstMipmap.value_size();
				std::size_t SrcIndex = SrcPosition.x * SrcMipmap.value_size() + (SrcPosition.y + j) * SrcMipmap.dimensions().x * SrcMipmap.value_size();
				memcpy(DstData + DstIndex, SrcData + SrcIndex, SrcMipmap.value_size() * SizeX);	
			}

			return DstMipmap;
		}

	}//namespace detail

	inline texture duplicate(texture const & Image2D)
	{
		texture Result(Image2D.levels());
		for(texture::level_type Level = 0; Level < Image2D.levels(); ++Level)
			Result[Level] = detail::duplicate(Image2D[Level]);
		return Result;
	}

	inline texture flip(texture const & Image2D)
	{
		texture Result(Image2D.levels());
		for(texture::level_type Level = 0; Level < Image2D.levels(); ++Level)
			Result[Level] = detail::flip(Image2D[Level]);
		return Result;
	}

	inline texture mirror(texture const & Image2D)
	{
		texture Result(Image2D.levels());
		for(texture::level_type Level = 0; Level < Image2D.levels(); ++Level)
			Result[Level] = detail::mirror(Image2D[Level]);
		return Result;
	}

	inline texture crop
	(
		texture const & Texture,
		texture::dimensions_type const & Position,
		texture::dimensions_type const & Size
	)
	{
		texture Result(Texture.levels());
		for(texture::level_type Level = 0; Level < Texture.levels(); ++Level)
			Result[Level] = detail::crop(Texture[Level], Position >> Level, Size >> Level);
		return Result;
	}

	inline texture swizzle
	(
		texture const & Texture,
		glm::uvec4 const & Channel
	)
	{
		texture Result(Texture.levels());
		for(texture::level_type Level = 0; Level < Texture.levels(); ++Level)
			Result[Level] = detail::swizzle(Texture[Level], Channel);
		return Result;
	}

	inline texture copy
	(
		texture const & SrcImage, 
		texture::level_type const & SrcLevel,
		texture::dimensions_type const & SrcPosition,
		texture::dimensions_type const & SrcDimensions,
		texture & DstMipmap, 
		texture::level_type const & DstLevel,
		texture::dimensions_type const & DstDimensions
	)
	{
		detail::copy(
			SrcImage[SrcLevel], 
			SrcPosition, 
			SrcDimensions,
			DstMipmap[DstLevel],
			DstDimensions);
		return DstMipmap;
	}

	//inline image operator+(image const & MipmapA, image const & MipmapB)
	//{
	//	
	//}

	//inline image operator-(image const & MipmapA, image const & MipmapB)
	//{
	//	
	//}

	//inline image operator*(image const & MipmapA, image const & MipmapB)
	//{
	//	
	//}

	//inline image operator/(image const & MipmapA, image const & MipmapB)
	//{
	//	
	//}

}//namespace gli
