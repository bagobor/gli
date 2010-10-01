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
		inline texture2D::image duplicate(texture2D::image const & Mipmap2D)
		{
			texture2D::image Result(Mipmap2D.dimensions(), Mipmap2D.format());
			memcpy(Result.data(), Mipmap2D.data(), Mipmap2D.capacity());
			return Result;	
		}

		inline texture2D::image flip(texture2D::image const & Mipmap2D)
		{
			texture2D::image Result(Mipmap2D.dimensions(), Mipmap2D.format());
			
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

		inline texture2D::image mirror(texture2D::image const & Mipmap2D)
		{
			texture2D::image Result(Mipmap2D.dimensions(), Mipmap2D.format());

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

		inline texture2D::image swizzle
		(
			texture2D::image const & Mipmap, 
			glm::uvec4 const & Channel
		)
		{
			texture2D::image Result = detail::duplicate(Mipmap);

			glm::byte * DataDst = Result.data();
			glm::byte const * const DataSrc = Mipmap.data();

			gli::texture2D::size_type CompSize = Mipmap.value_size() / Mipmap.components();
			gli::texture2D::size_type TexelCount = Mipmap.capacity() / Mipmap.value_size();

			for(gli::texture2D::size_type t = 0; t < TexelCount; ++t)
			for(gli::texture2D::size_type c = 0; c < Mipmap.components(); ++c)
			{
				gli::texture2D::size_type IndexSrc = t * Mipmap.components() + Channel[glm::uvec4::size_type(c)];
				gli::texture2D::size_type IndexDst = t * Mipmap.components() + c;

				memcpy(DataDst + IndexDst, DataSrc + IndexSrc, CompSize);
			}

			return Result;
		}

		inline texture2D::image crop
		(
			texture2D::image const & Mipmap, 
			texture2D::dimensions_type const & Position, 
			texture2D::dimensions_type const & Size
		)
		{
			assert((Position.x + Size.x) <= Mipmap.dimensions().x && (Position.y + Size.y) <= Mipmap.dimensions().y);

			texture2D::image Result(Size, Mipmap.format());

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

		inline texture2D::image copy
		(
			texture2D::image const & SrcMipmap, 
			texture2D::dimensions_type const & SrcPosition,
			texture2D::dimensions_type const & SrcSize,
			texture2D::image & DstMipmap, 
			texture2D::dimensions_type const & DstPosition
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

	inline texture2D duplicate(texture2D const & Image2D)
	{
		texture2D Result(Image2D.levels());
		for(texture2D::level_type Level = 0; Level < Image2D.levels(); ++Level)
			Result[Level] = detail::duplicate(Image2D[Level]);
		return Result;
	}

	inline texture2D flip(texture2D const & Image2D)
	{
		texture2D Result(Image2D.levels());
		for(texture2D::level_type Level = 0; Level < Image2D.levels(); ++Level)
			Result[Level] = detail::flip(Image2D[Level]);
		return Result;
	}

	inline texture2D mirror(texture2D const & Image2D)
	{
		texture2D Result(Image2D.levels());
		for(texture2D::level_type Level = 0; Level < Image2D.levels(); ++Level)
			Result[Level] = detail::mirror(Image2D[Level]);
		return Result;
	}

	inline texture2D crop
	(
		texture2D const & Texture,
		texture2D::dimensions_type const & Position,
		texture2D::dimensions_type const & Size
	)
	{
		texture2D Result(Texture.levels());
		for(texture2D::level_type Level = 0; Level < Texture.levels(); ++Level)
			Result[Level] = detail::crop(Texture[Level], Position >> Level, Size >> Level);
		return Result;
	}

	inline texture2D swizzle
	(
		texture2D const & Texture,
		glm::uvec4 const & Channel
	)
	{
		texture2D Result(Texture.levels());
		for(texture2D::level_type Level = 0; Level < Texture.levels(); ++Level)
			Result[Level] = detail::swizzle(Texture[Level], Channel);
		return Result;
	}

	inline texture2D copy
	(
		texture2D const & SrcImage, 
		texture2D::level_type const & SrcLevel,
		texture2D::dimensions_type const & SrcPosition,
		texture2D::dimensions_type const & SrcDimensions,
		texture2D & DstMipmap, 
		texture2D::level_type const & DstLevel,
		texture2D::dimensions_type const & DstDimensions
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
