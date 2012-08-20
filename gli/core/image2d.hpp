///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2011-04-05
// Updated : 2011-04-05
// Licence : This source is under MIT License
// File    : gli/core/image2d.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_CORE_image2d
#define GLI_CORE_image2d GLI_VERSION

#include "image.hpp"

namespace gli
{
	class image2D : public imageBase<>
	{
        friend class texture2d;
        
	public:
		typedef glm::uvec2 dimensions_type;
		typedef glm::vec2 texcoord_type;

	public:
		image2D();
		image2D(
			image2D const & Image);

		explicit image2D(
			format_type const & InternalFormat,
			dimensions_type const & Dimensions);

		template <typename genType>
		explicit image2D(
			format_type const & InternalFormat, 
			dimensions_type const & Dimensions,
			genType const & Texel);

		template <typename genType>
		explicit image2D(
			format_type const & InternalFormat, 
			dimensions_type const & Dimensions,
			std::vector<genType> const & Data);

		virtual ~image2D();

		image2D & operator= (image2D const & Image);

		template <typename genType>
		genType load(
			dimensions_type const & TexelCoord);

		template <typename genType>
		void store(
			dimensions_type const & TexelCoord,
			genType const & TexelData);

		template <typename genType>
		void clear(
			genType const & Texel);

		void copy(
			image2D const & ImageSrc,
			dimensions_type const & OffsetSrc,
			dimensions_type const & OffsetDst,
			dimensions_type const & Size);

		dimensions_type dimensions() const;
		dimensions_type block_dimensions() const;

	private:
		dimensions_type Dimensions;
	};
}//namespace gli

#include "image2d.inl"

#endif//GLI_CORE_image2d
