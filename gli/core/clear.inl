///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-09-27
// Updated : 2010-09-27
// Licence : This source is under MIT License
// File    : gli/core/clear.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace gli
{
	template <typename genType>
	inline image2D clear
	(
		image2D const & Image, 
		genType const & Texel
	)
	{
		image2D Result = Image;
		for(std::size_t i = 0; i < Image.capacity() / sizeof(genType); ++i)
			Image.data<genType>()[i] = Texel;
		return Result;
	}

}//namespace gli
