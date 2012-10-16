///////////////////////////////////////////////////////////////////////////////////
/// OpenGL Image (gli.g-truc.net)
///
/// Copyright (c) 2008 - 2012 G-Truc Creation (www.g-truc.net)
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
/// 
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///
/// @ref core
/// @file gli/core/texture2d.hpp
/// @date 2010-01-09 / 2012-10-16
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_CORE_TEXTURE2D_INCLUDED
#define GLI_CORE_TEXTURE2D_INCLUDED

#include "image.hpp"

namespace gli
{
	//template <template <typename> class mem>
	class texture2D
	{
	public:
		typedef gli::detail::storage::dimensions2_type dimensions_type;
		typedef gli::detail::storage::texcoord2_type texcoord_type;
		typedef gli::detail::storage::size_type size_type;
		typedef gli::format format_type;
		typedef gli::detail::storage::data_type data_type;

	private:
/*
		explicit texture2D(
			size_type const & Levels,
			format_type const & Format,
			dimensions_type const & Dimensions,
			shared_ptr<detail::storage> const & Storage,
			size_type const & Offset);
*/
	public:
		texture2D();

		explicit texture2D(
			size_type const & Levels,
			format_type const & Format,
			dimensions_type const & Dimensions);
/*
		template <typename genType>
		explicit texture2D(
			size_type const & Levels,
			format_type const & Format, 
			dimensions_type const & Dimensions,
			genType const & Texel);
*/
		~texture2D();

		image & operator[] (
			size_type const & Level);
		image const & operator[] (
			size_type const & Level) const;

		bool empty() const;
		format_type format() const;
		dimensions_type dimensions() const;
		size_type levels() const;
		size_type size() const;
		data_type * data();
		data_type const * const data() const;

	private:
		shared_ptr<detail::storage> Storage;
		std::vector<image> Images;
		format_type const Format;
		size_type Offset;
	};

}//namespace gli

#include "texture2d.inl"

#endif//GLI_CORE_TEXTURE2D_INCLUDED
