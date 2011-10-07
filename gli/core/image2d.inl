///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2011-04-05
// Updated : 2011-04-05
// Licence : This source is under MIT License
// File    : gli/core/image2d.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace gli
{
	inline image2D::image2D() :
		Dimensions(0)
	{}

	inline image2D::image2D
	(
		image2D const & Image
	) :
		image(Image.InternalFormat, Image.Data),
		Dimensions(Image.Dimensions)
	{}

	inline image2D::image2D   
	(
		image2D::format_type const & InternalFormat,
		image2D::dimensions_type const & Dimensions
	) :
		image(InternalFormat, glm::compMul(Dimensions)),
		Dimensions(Dimensions)
	{}

	template <typename genType>
	inline image2D::image2D   
	(
		image2D::format_type const & InternalFormatt, 
		image2D::dimensions_type const & Dimensions,
		genType const & Value
	) :
		image(InternalFormat, glm::compMul(Dimensions)),
		Dimensions(Dimensions)
	{
		this->clear<genType>(Value);
	}

	template <typename genType>
	inline image2D::image2D
	(
		image2D::format_type const & InternalFormat,
		image2D::dimensions_type const & Dimensions,
		std::vector<genType> const & Data
	) :
		image(InternalFormat, glm::compMul(Dimensions)),
		Dimensions(Dimensions)
	{
		memcpy(&this->Data[0], &Data[0], Data.size());
	}

	inline image2D::~image2D()
	{}

	inline image2D & image2D::operator= (image2D const & Image)
	{
		image::operator=(Image);
		this->Dimensions = Image.Dimensions;
		return *this;
	}

	template <typename genType>
	inline genType image2D::load
	(
		image2D::dimensions_type const & TexelCoord
	)
	{
		size_type Index = this->dimensions().x * TexelCoord.y + TexelCoord.x;
		return *(this->data<genType>() + Index);
	}

	template <typename genType>
	inline void image2D::store
	(
		image2D::dimensions_type const & TexelCoord,
		genType const & TexelData
	)
	{
		size_type Index = this->dimensions().x * sizeof(genType) * TexelCoord.y + sizeof(genType) * TexelCoord.x;
		memcpy(this->data() + Index, &TexelData[0], sizeof(genType));
	}

	template <typename genType>
	inline void image2D::clear
	(
		genType const & Texel
	)
	{
		for(data_type::size_type i(0); i < Data.size() / sizeof(Texel); ++i)
			this->data<genType>()[i] = Texel;
	}

	inline void copy
	(
		image2D const & ImageSrc,
		image2D::dimensions_type const & OffsetSrc,
		image2D::dimensions_type const & OffsetDst,
		image2D::dimensions_type const & SizeSrc
	)
	{
		// TODO
		assert(0);
	}

	inline image2D::dimensions_type image2D::dimensions() const
	{
		return this->Dimensions;
	}

}//namespace gli
