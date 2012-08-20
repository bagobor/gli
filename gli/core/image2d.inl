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
		imageBase(Image.InternalFormat, Image.Data),
		Dimensions(Image.Dimensions)
	{}

	inline image2D::image2D   
	(
		image2D::format_type const & InternalFormat,
		image2D::dimensions_type const & Dimensions
	) :
		imageBase(InternalFormat, glm::compMul(Dimensions)),
		Dimensions(Dimensions)
	{}

	template <typename genType>
	inline image2D::image2D   
	(
		image2D::format_type const & InternalFormat, 
		image2D::dimensions_type const & Dimensions,
		genType const & Value
	) :
		imageBase(InternalFormat, glm::compMul(Dimensions)),
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
		imageBase(InternalFormat, glm::compMul(Dimensions)),
		Dimensions(Dimensions)
	{
		memcpy(&this->Data[0], &Data[0], Data.size());
	}

	inline image2D::~image2D()
	{}

	inline image2D & image2D::operator= (image2D const & Image)
	{
		imageBase::operator=(Image);
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
		size_type Index = this->dimensions().x * TexelCoord.y + TexelCoord.x;
		*(this->data<genType>() + Index) = TexelData;
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

	inline void image2D::copy
	(
		image2D const & ImageSrc,
		image2D::dimensions_type const & OffsetSrc,
		image2D::dimensions_type const & OffsetDst,
		image2D::dimensions_type const & Size
	)
	{
		assert(this->block_size() == ImageSrc.block_size()); // The formats are "compatible"
		assert(this->block_dimensions() == ImageSrc.block_dimensions()); // The formats are "compatible"
		assert(OffsetSrc.x + Size.x <= ImageSrc.dimensions().x);
		assert(OffsetSrc.y + Size.y <= ImageSrc.dimensions().y);
		assert(OffsetDst.x + Size.x <= this->dimensions().x);
		assert(OffsetDst.y + Size.y <= this->dimensions().y);

		size_type BlockSize = this->block_size();

		for(size_type i = 0; i < Size.y / ImageSrc.block_dimensions().y; ++i)
		{
			size_type IndexSrc = OffsetSrc.x + (i + OffsetSrc.y) * ImageSrc.dimensions().x;
			size_type IndexDst = OffsetDst.x + (i + OffsetDst.y) * this->dimensions().x;

			memcpy(
				reinterpret_cast<glm::byte*>(this->data()) + IndexDst * BlockSize, 
				reinterpret_cast<glm::byte const * const>(ImageSrc.data()) + IndexSrc * BlockSize, 
				BlockSize * Size.x / ImageSrc.block_dimensions().x);
		}
	}

	inline image2D::dimensions_type image2D::dimensions() const
	{
		return this->Dimensions;
	}

	inline image2D::dimensions_type image2D::block_dimensions() const
	{
		return dimensions_type(
			gli::detail::getFormatInfo(this->format()).BlockWidth,
			gli::detail::getFormatInfo(this->format()).BlockHeight);
	}

}//namespace gli
