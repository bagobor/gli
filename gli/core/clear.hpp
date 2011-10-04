#ifndef gli_core_clear
#define gli_core_clear

#include "texture2d.hpp"

namespace gli
{
	template <typename genType>
	image2D clear(image2D const & Image, genType const & Texel);

}//namespace gli

#include "clear.inl"

#endif//gli_core_clear
