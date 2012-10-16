///////////////////////////////////////////////////////////////////////////////////
/// OpenGL Image (gli.g-truc.net)
///
/// Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
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
/// @file gli/core/image.hpp
/// @date 2011-10-06 / 2011-10-06
/// @author Christophe Riccio
///
/// @defgroup core_image Image 
/// @ingroup core
/// 
/// Image1D 
///////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_CORE_image
#define GLI_CORE_image GLI_VERSION

#include "storage.hpp"
#include "format.hpp"

namespace gli
{
/*
template<class _Myvec>
	class _Vector_iterator
		: public _Vector_const_iterator<_Myvec>
	{	// iterator for mutable vector
public:
	typedef _Vector_iterator<_Myvec> _Myiter;
	typedef _Vector_const_iterator<_Myvec> _Mybase;
	typedef random_access_iterator_tag iterator_category;

	typedef typename _Myvec::value_type value_type;
	typedef typename _Myvec::difference_type difference_type;
	typedef typename _Myvec::pointer pointer;
	typedef typename _Myvec::reference reference;

	_Vector_iterator()
		{	// construct with null vector pointer
		}

	_Vector_iterator(pointer _Parg, const _Container_base *_Pvector)
		: _Mybase(_Parg, _Pvector)
		{	// construct with pointer _Parg
		}

	typedef pointer _Unchecked_type;

	_Myiter& _Rechecked(_Unchecked_type _Right)
		{	// reset from unchecked iterator
		this->_Ptr = _Right;
		return (*this);
		}

	_Unchecked_type _Unchecked() const
		{	// make an unchecked iterator
		return (_Unchecked_type(this->_Ptr));
		}

	reference operator*() const
		{	// return designated object
		return ((reference)**(_Mybase *)this);
		}

	pointer operator->() const
		{	// return pointer to class object
		return (&**this);
		}

	_Myiter& operator++()
		{	// preincrement
		++*(_Mybase *)this;
		return (*this);
		}

	_Myiter operator++(int)
		{	// postincrement
		_Myiter _Tmp = *this;
		++*this;
		return (_Tmp);
		}

	_Myiter& operator--()
		{	// predecrement
		--*(_Mybase *)this;
		return (*this);
		}

	_Myiter operator--(int)
		{	// postdecrement
		_Myiter _Tmp = *this;
		--*this;
		return (_Tmp);
		}

	_Myiter& operator+=(difference_type _Off)
		{	// increment by integer
		*(_Mybase *)this += _Off;
		return (*this);
		}

	_Myiter operator+(difference_type _Off) const
		{	// return this + integer
		_Myiter _Tmp = *this;
		return (_Tmp += _Off);
		}

	_Myiter& operator-=(difference_type _Off)
		{	// decrement by integer
		return (*this += -_Off);
		}

	_Myiter operator-(difference_type _Off) const
		{	// return this - integer
		_Myiter _Tmp = *this;
		return (_Tmp -= _Off);
		}

	difference_type operator-(const _Mybase& _Right) const
		{	// return difference of iterators
		return (*(_Mybase *)this - _Right);
		}

	reference operator[](difference_type _Off) const
		{	// subscript
		return (*(*this + _Off));
		}
	};
*/

	class image
	{
	public:
		typedef detail::storage::size_type size_type;
		typedef detail::storage::dimensions4_type dimensions_type;

		image();
		image(
			image const & Image);

		explicit image(
			shared_ptr<detail::storage> const & Storage);

		/// Reference an exiting texture storage constructor
		/// 
		/// @param Offset Data offset in the texture storage expressed in bytes.
		explicit image(
			shared_ptr<detail::storage> const & Storage, 
			size_type const & Offset,
			dimensions_type const & Dimensions);

		/// Allocate a new texture storage constructor
		template <typename genType>
		explicit image(
			dimensions_type const & Dimensions,
			std::vector<genType> const & Data);

		/// Allocate a new texture storage constructor and copy data
		explicit image(
			dimensions_type const & Dimensions,
			size_type const & BlockSize);

		~image();

		image & operator= (image const & Image);

		/// Allocate the storage for the image of exactly the memory size required by the image 
		bool resize();

		dimensions_type dimensions() const;

		bool empty() const;
		size_type size() const;
		void * data();
		void const * const data() const;

		template <typename genType>
		genType * data();

		template <typename genType>
		genType const * const data() const;

	private:
		shared_ptr<detail::storage> Storage;
		dimensions_type Dimensions;
		size_type Offset;
	};

	bool operator== (image const & ImageA, image const & ImageB);
	bool operator!= (image const & ImageA, image const & ImageB);
}//namespace gli

#include "image.inl"

#endif//GLI_CORE_image
