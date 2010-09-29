///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-09-27
// Updated : 2010-09-27
// Licence : This source is under MIT License
// File    : gli/core/texture.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace gli
{
	namespace detail
	{
		struct format_desc
		{
			texture::size_type BlockSize;
			texture::size_type BBP;
			texture::size_type Component;
		};

		inline format_desc getFormatInfo(format const & Format)
		{
			format_desc Desc[FORMAT_MAX] =
			{
				{  0,  0,  0},	//FORMAT_NULL
				//// Unsigned integer formats
				{  1,   8,  1},	//R8U,
				{  2,  16,  2},	//RG8U,
				{  3,  24,  3},	//RGB8U,
				{  4,  32,  4},	//RGBA8U,

				{  2,  16,  1},	//R16U,
				{  4,  32,  2},	//RG16U,
				{  6,  48,  3},	//RGB16U,
				{  8,  64,  4},	//RGBA16U,

				{  4,  32,  1},	//R32U,
				{  8,  64,  2},	//RG32U,
				{ 12,  96,  3},	//RGB32U,
				{ 16, 128,  4},	//RGBA32U,

				//// Signed integer formats
				{  4,  32,  1},	//R8I,
				{  8,  64,  2},	//RG8I,
				{ 12,  96,  3},	//RGB8I,
				{ 16, 128,  4},	//RGBA8I,

				{  2,  16,  1},	//R16I,
				{  4,  32,  2},	//RG16I,
				{  6,  48,  3},	//RGB16I,
				{  8,  64,  4},	//RGBA16I,

				{  4,  32,  1},	//R32I,
				{  8,  64,  2},	//RG32I,
				{ 12,  96,  3},	//RGB32I,
				{ 16, 128,  4},	//RGBA32I,

				//// Floating formats
				{  2,  16,  1},	//R16F,
				{  4,  32,  2},	//RG16F,
				{  6,  48,  3},	//RGB16F,
				{  8,  64,  4},	//RGBA16F,

				{  4,  32,  1},	//R32F,
				{  8,  64,  2},	//RG32F,
				{ 12,  96,  3},	//RGB32F,
				{ 16, 128,  4},	//RGBA32F,

				//// Packed formats
				{  4,  32,  3},	//RGBE8,
				{  4,  32,  3},	//RGB9E5,
				{  4,  32,  3},	//RG11B10F,
				{  2,  16,  3},	//RGB565,
				{  2,  16,  4},	//RGBA4,
				{  4,  32,  3},	//RGB10A2,

				//// Depth formats
				{  2,  16,  1},	//D16,
				{  4,  32,  1},	//D24X8,
				{  4,  32,  2},	//D24S8,
				{  4,  32,  1},	//D32F,
				{  8,  64,  2},	//D32FS8X24,

				//// Compressed formats
				{  8,   4,  4},	//DXT1,
				{ 16,   8,  4},	//DXT3,
				{ 16,   8,  4},	//DXT5,
				{  8,   4,  1},	//ATI1N,
				{ 16,   8,  2},	//ATI2N,
				{ 32,   8,  3},	//BP_FLOAT,
				{ 32,   8,  4},	//BP,
			};

			return Desc[Format];
		};

		inline texture::size_type sizeBlock
		(
			format const & Format
		)
		{
			return getFormatInfo(Format).BlockSize;
		}

		inline texture::size_type sizeBitPerPixel
		(
			format const & Format
		)
		{
			return getFormatInfo(Format).BBP;
		}

		inline texture::size_type sizeComponent
		(
			format const & Format
		)
		{
			return getFormatInfo(Format).Component;
		}

		inline texture::size_type sizeLinear
		(
			image const & Mipmap
		)
		{
			texture::dimensions_type Dimension = Mipmap.dimensions();
			Dimension = glm::max(Dimension, texture::dimensions_type(1));

			texture::size_type BlockSize = sizeBlock(Mipmap.format());
			texture::size_type BPP = sizeBitPerPixel(Mipmap.format());
			texture::size_type BlockCount = 0;
			if((BlockCount << 3) == BPP)
				BlockCount = Dimension.x * Dimension.y;
			else
				BlockCount = ((Dimension.x + 3) >> 2) * ((Dimension.y + 3) >> 2);			

			return BlockCount * BlockSize;
		}

		inline texture::size_type sizeLinear
		(
			texture const & Image
		)
		{
			texture::size_type Result = 0;
			for(texture::level_type Level = 0; Level < Image.levels(); ++Level)
				Result += sizeLinear(Image[Level]);
			return Result;
		}

/*
		texture::size_type const NA = -1;

		inline texture::size_type getComponents(texture::format_type const & Format)
		{
			static texture::size_type Component[FORMAT_MAX] =
			{
				0,

				//// Unsigned integer formats
				1, //R8U,
				2, //RG8U,
				3, //RGB8U,
				4, //RGBA8U,

				1, //R16U,
				2, //RG16U,
				3, //RGB16U,
				4, //RGBA16U,

				1, //R32U,
				2, //RG32U,
				3, //RGB32U,
				4, //RGBA32U,

				//// Signed integer formats
				1, //R8I,
				2, //RG8I,
				3, //RGB8I,
				4, //RGBA8I,

				1, //R16I,
				2, //RG16I,
				3, //RGB16I,
				4, //RGBA16I,

				1, //R32I,
				2, //RG32I,
				3, //RGB32I,
				4, //RGBA32I,

				//// Floating formats
				1, //R16F,
				2, //RG16F,
				3, //RGB16F,
				4, //RGBA16F,

				1, //R32F,
				2, //RG32F,
				3, //RGB32F,
				4, //RGBA32F,

				//// Packed formats
				NA, //RGBE8,
				NA, //RGB9E5,
				NA, //RG11B10F,
				NA, //RGB565,
				NA, //RGBA4,
				NA, //RGB10A2,

				//// Depth formats
				NA, //D16,
				NA, //D24X8,
				NA, //D24S8,
				NA, //D32F,
				NA, //D32FS8X24,

				//// Compressed formats
				NA, //DXT1,
				NA, //DXT3,
				NA, //DXT5,
				NA, //ATI1N,
				NA  //ATI2N,
			};

			return Component[Format];
		}

		inline texture::size_type getBitPerTexels(texture::format_type const & Format)
		{
			static texture::size_type BitsPerTexels[FORMAT_MAX] =
			{
				0,

				//// Unsigned integer formats
				8, //R8U,
				16, //RG8U,
				24, //RGB8U,
				32, //RGBA8U,

				16, //R16U,
				32, //RG16U,
				48, //RGB16U,
				64, //RGBA16U,

				32, //R32U,
				64, //RG32U,
				96, //RGB32U,
				128, //RGBA32U,

				//// Signed integer formats
				8, //R8I,
				16, //RG8I,
				24, //RGB8I,
				32, //RGBA8I,

				16, //R16I,
				32, //RG16I,
				48, //RGB16I,
				64, //RGBA16I,

				32, //R32I,
				64, //RG32I,
				96, //RGB32I,
				128, //RGBA32I,

				//// Floating formats
				16, //R16F,
				32, //RG16F,
				48, //RGB16F,
				64, //RGBA16F,

				32, //R32F,
				64, //RG32F,
				96, //RGB32F,
				128, //RGBA32F,

				//// Packed formats
				32, //RGBE8,
				32, //RGB9E5,
				32, //RG11B10F,
				16, //RGB565,
				16, //RGBA4,
				32, //RGB10A2,

				//// Depth formats
				16, //D16,
				32, //D24X8,
				32, //D24S8,
				32, //D32F,
				64, //D32FS8X24,

				//// Compressed formats
				4, //DXT1,
				8, //DXT3,
				8, //DXT5,
				4, //ATI1N,
				8,  //ATI2N,
				16, //BP_FLOAT
				16, //BP
			};

			assert(sizeof(BitsPerTexels) / sizeof(texture::size_type) == FORMAT_MAX);

			return BitsPerTexels[Format];
		}
*/
	}//namespace detail

	inline texture::image_impl::image_impl() :
		Data(0),
		Dimensions(0),
		Format(FORMAT_NULL)
	{}

	inline texture::image_impl::image_impl
	(
		texture::image const & Mipmap2D
	) :
		Data(Mipmap2D.Data),
		Dimensions(Mipmap2D.Dimensions),
		Format(Mipmap2D.Format)
	{}

	inline texture::image_impl::image_impl    
	(
		dimensions_type const & Dimensions,
		format_type const & Format
	) :
		Data(new value_type[glm::compMul(Dimensions) * detail::sizeBitPerPixel(Format) >> 3]),
		Dimensions(Dimensions),
		Format(Format)
	{}

	inline texture::image_impl::image_impl
	(
		dimensions_type const & Dimensions,
		format_type const & Format,
		std::vector<value_type> const & Data
	) :
		Data(new value_type[Data.size()]),
		Dimensions(Dimensions),
		Format(Format)
	{
		memcpy(this->Data.get(), &Data[0], Data.size());
	}

	inline texture::image_impl::image_impl
	(
		dimensions_type const & Dimensions,
		format_type const & Format,
		data_type const & Data
	) :
		Data(Data),
		Dimensions(Dimensions),
		Format(Format)
	{}

	inline texture::image_impl::~image_impl()
	{}

	template <typename genType>
	inline void texture::image_impl::setPixel
	(
		glm::uvec2 const & TexelCoord,
		genType const & TexelData
	)
	{
		size_type Index = this->dimensions().x * sizeof(genType) * TexelCoord.y + sizeof(genType) * TexelCoord.x;
		memcpy(this->data() + Index, &TexelData[0], sizeof(genType));
	}

	inline texture::size_type texture::image_impl::value_size() const
	{
		return detail::sizeBitPerPixel(this->format());
	}

	inline texture::size_type texture::image_impl::capacity() const
	{
		return detail::sizeLinear(*this);
	}

	inline texture::dimensions_type texture::image_impl::dimensions() const
	{
		return this->Dimensions;
	}

	inline texture::size_type texture::image_impl::components() const
	{
		return detail::sizeComponent(this->format());
	}

	inline texture::format_type texture::image_impl::format() const
	{
		return this->Format;
	}

	inline texture::value_type * texture::image_impl::data()
	{
		return this->Data.get();
	}

	inline texture::value_type const * const texture::image_impl::data() const
	{
		return this->Data.get();
	}

	namespace detail
	{

	}//namespace detail

	inline texture::texture()
	{}

	inline texture::texture
	(
		level_type const & Levels
	)
	{
		this->Images.resize(Levels);
	}

	//inline texture::texture
	//(
	//	image const & Mipmap, 
	//	bool GenerateMipmaps // ToDo
	//)
	//{
	//	//std::size_t Levels = !GenerateMipmaps ? 1 : std::size_t(glm::log2(float(glm::max(Mipmap.width(), Mipmap.height()))));
	//	texture::level_type Levels = !GenerateMipmaps ? 1 : std::size_t(glm::log2(float(glm::compMax(Mipmap.dimensions()))));
	//	this->Mipmaps.resize(Levels);
	//	this->Mipmaps[0] = Mipmap;

	//	if(GenerateMipmaps)
	//		this->generateMipmaps(0);
	//}

	inline texture::~texture()
	{}

	inline texture::image & texture::operator[] (level_type const & Level)
	{
		return this->Images[Level];
	}

	inline texture::image const & texture::operator[] (level_type const & Level) const
	{
		return this->Images[Level];
	}

	inline bool texture::empty() const
	{
		return this->Images.size() == 0;
	}

	inline texture::level_type texture::levels() const
	{
		return this->Images.size();
	}

	inline texture::format_type texture::format() const
	{
		return this->Images.empty() ? FORMAT_NULL : this->Images[0].format();
	}

	template <typename genType>
	inline void texture::swizzle(glm::comp X, glm::comp Y, glm::comp Z, glm::comp W)
	{
		for(texture::level_type Level = 0; Level < this->levels(); ++Level)
		{
			genType * Data = reinterpret_cast<genType*>(this->Images[Level].data());
			texture::size_type Components = this->Images[Level].components();
			//gli::detail::getComponents(this->Images[Level].format());
			texture::size_type Size = (glm::compMul(this->Images[Level].dimensions()) * Components) / sizeof(genType);

			for(texture::size_type i = 0; i < Size; ++i)
			{
				genType Copy = Data[i];
				if(Components > 0)
					Data[i][0] = Copy[X];
				if(Components > 1)
					Data[i][1] = Copy[Y];
				if(Components > 2)
					Data[i][2] = Copy[Z];
				if(Components > 3)
					Data[i][3] = Copy[W];
			}
		}
	}

/*
	template <typename T>
	inline T texture<T>::texture2D(float x, float y) const
	{
        size_type x_below = size_type(std::floor(x * (_width - 1)));
		size_type x_above = size_type(std::ceil(x * (_width - 1)));
        size_type y_below = size_type(std::floor(y * (_height - 1)));
        size_type y_above = size_type(std::ceil(y * (_height - 1)));

        float x_step = 1.0f / float(_width);
        float y_step = 1.0f / float(_height);

        float x_below_normalized = float(x_below) / float(_width - 1);
        float x_above_normalized = float(x_above) / float(_width - 1);
        float y_below_normalized = float(y_below) / float(_height - 1);
        float y_above_normalized = float(y_above) / float(_height - 1);
		
		T value1 = _data[x_below + y_below * _width];
		T value2 = _data[x_above + y_below * _width];
		T value3 = _data[x_above + y_above * _width];
		T value4 = _data[x_below + y_above * _width];

		T valueA = glm::mix(value1, value2, x - x_below_normalized);
		T valueB = glm::mix(value4, value3, x - x_below_normalized);
		T valueC = glm::mix(valueA, valueB, y - y_below_normalized);
		return valueC;
	}
*/
/*
	template <typename T>
	inline T texture2D(const texture<T>& Image2D, const glm::vec2& TexCoord)
	{
		texture<T>::size_type s_below = texture<T>::size_type(std::floor(TexCoord.s * (Image2D.width() - 1)));
		texture<T>::size_type s_above = texture<T>::size_type(std::ceil(TexCoord.s * (Image2D.width() - 1)));
        texture<T>::size_type t_below = texture<T>::size_type(std::floor(TexCoord.t * (Image2D.height() - 1)));
        texture<T>::size_type t_above = texture<T>::size_type(std::ceil(TexCoord.t * (Image2D.height() - 1)));

		glm::vec2::value_type s_step = 1.0f / glm::vec2::value_type(Image2D.width());
        glm::vec2::value_type t_step = 1.0f / glm::vec2::value_type(Image2D.height());

        glm::vec2::value_type s_below_normalized = glm::vec2::value_type(s_below) / glm::vec2::value_type(Image2D.width() - 1);
        glm::vec2::value_type s_above_normalized = glm::vec2::value_type(s_above) / glm::vec2::value_type(Image2D.width() - 1);
        glm::vec2::value_type t_below_normalized = glm::vec2::value_type(t_below) / glm::vec2::value_type(Image2D.height() - 1);
        glm::vec2::value_type t_above_normalized = glm::vec2::value_type(t_above) / glm::vec2::value_type(Image2D.height() - 1);
		
		T value1 = Image2D[s_below + t_below * Image2D.width()];
		T value2 = Image2D[s_above + t_below * Image2D.width()];
		T value3 = Image2D[s_above + t_above * Image2D.width()];
		T value4 = Image2D[s_below + t_above * Image2D.width()];

		T valueA = glm::mix(value1, value2, TexCoord.s - s_below_normalized);
		T valueB = glm::mix(value4, value3, TexCoord.s - s_below_normalized);
		T valueC = glm::mix(valueA, valueB, TexCoord.t - t_below_normalized);
		return valueC;
	}

	template <typename T>
	inline T texture2DNearest(const texture<T>& Image2D, const glm::vec2& TexCoord)
	{
		texture<T>::size_type s = texture<T>::size_type(glm::roundGTX(TexCoord.s * (Image2D.width() - 1)));
        texture<T>::size_type t = texture<T>::size_type(std::roundGTX(TexCoord.t * (Image2D.height() - 1)));

		return Image2D[s + t * Image2D.width()];
	}
*/

namespace wip
{
	////////////////
	// image
/*
	// 
	template
	<
		typename coordType
	>
	template
	<
		typename genType, 
		template <typename> class surface
	>
	typename texture<genType, surface>::value_type & 
	texture<genType, surface>::image_impl<coordType>::operator() 
	(
		coordType const & Coord
	)
	{
		
	}
*/
/*
	// 
	template
	<
		typename coordType
	>
	template
	<
		typename genType, 
		template <typename> class surface
	>
	typename texture<genType, surface>::value_type const & 
	texture<genType, surface>::image_impl::operator()
	(
		coordType const & Coord
	) const
	{
		return value_type(0);
	}
*/
/*
	//
	template
	<
		typename coordType
	>
	template
	<
		typename genType, 
		template <typename> class surface
	>
	void texture<genType, surface>::image_impl::operator()
	(
		coordType const & Coord
	) const
	{
		
	}
*/
	////
	//template
	//<
	//	typename genType, 
	//	template <typename> class surface
	//>
	//template
	//<
	//	typename coordType
	//>
	//typename texture<genType, surface>::value_type const & 
	//texture<genType, surface>::image_impl::operator()
	//(
	//	coordType const & Coord
	//) const
	//{
	//	return value_type(0);
	//}

	//////////////////
	//// texture

	//// 
	//template
	//<
	//	typename genType, 
	//	template <typename> class surface
	//>
	//typename texture<genType, surface>::level_type texture<genType, surface>::levels() const
	//{
	//	return this->Mipmaps.size();
	//}

	//// 
	//template
	//<
	//	typename genType, 
	//	template <typename> class surface
	//>
	//typename texture<genType, surface>::image & texture<genType, surface>::operator[] 
	//(
	//	typename texture<genType, surface>::level_type Level
	//)
	//{
	//	return this->Mipmaps[Level];
	//}

	//// 
	//template
	//<
	//	typename genType, 
	//	template <typename> class surface
	//>
	//typename texture<genType, surface>::image const & texture<genType, surface>::operator[] 
	//(
	//	typename texture<genType, surface>::level_type Level
	//) const
	//{
	//	return this->Mipmaps[Level];
	//}

}//namespace wip
}//namespace gli
