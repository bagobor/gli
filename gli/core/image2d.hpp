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

namespace gli{

enum size_type
{
	LINEAR_SIZE,
	BLOCK_SIZE,
	BIT_PER_PIXEL, 
	COMPONENT
};

class image2D
{
public:
	typedef glm::uvec2 dimensions_type;
	typedef glm::vec2 texcoord_type;
	typedef glm::uint32 size_type;
	//typedef glm::byte value_type;
	typedef gli::format format_type;
	typedef std::vector<glm::byte> data_type;

public:
	image2D();
	image2D(
		image2D const & Image);

	explicit image2D(
		dimensions_type const & Dimensions,
		format_type const & Format);

	template <typename genType>
	explicit image2D(
		dimensions_type const & Dimensions,
		format_type const & Format, 
		genType const & Texel);

	template <typename genType>
	explicit image2D(
		dimensions_type const & Dimensions,
		format_type const & Format, 
		std::vector<genType> const & Data);

	~image2D();

	image2D & operator= (image2D const & Image);

	template <typename genType>
	void store(
		dimensions_type const & TexelCoord,
		genType const & TexelData);

	template <typename genType>
	void clear(
		genType const & Texel);

	size_type value_size() const;
	size_type capacity() const;
	dimensions_type dimensions() const;
	size_type components() const;
	format_type format() const;
		
	void * data();
	void const * const data() const;

	template <typename genType>
	genType * data();

	template <typename genType>
	genType const * const data() const;

private:
	data_type Data;
	dimensions_type Dimensions;
	format_type Format;
};

}//namespace gli

#include "image2d.inl"

#endif//GLI_CORE_image2d
