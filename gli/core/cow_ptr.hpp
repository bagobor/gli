///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2012-09-24
// Updated : 2012-09-24
// Licence : This source is under MIT License
// File    : gli/core/cow_ptr.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_COW_PTR_INCLUDED
#define GLI_COW_PTR_INCLUDED

#include "shared_ptr.hpp"

namespace gli
{
	template <typename T>
	class cow_ptr
	{
	public:
		cow_ptr(T* Pointer) :
			Pointer(Pointer)
		{}

		cow_ptr(shared_ptr<T> const & SharedPtr) :
			Pointer(SharedPtr)
		{}

		cow_ptr(cow_ptr<T> const & CowPtr) :
			Pointer(CowPtr.Pointer)
		{}

		cow_ptr & operator=(cow_ptr<T> const & CowPtr)
		{
			// no need to check for self-assignment with shared_ptr

			this->SharedPtr = CowPtr.SharedPtr; 
			return *this;
		}

		T const & operator*() const
		{
			return *this->SharedPtr;
		}

		T & operator*()
		{
			this->detach();
			return *this->SharedPtr;
		}

		T const * operator->() const
		{
			return this->SharedPtr.operator->();
		}

		T * operator->()
		{
			this->detach();
			return this->SharedPtr.operator->();
		}

	private:
		void detach()
		{
			T* Tmp = this->SharedPtr.get();
			if(!(Tmp == 0 || this->SharedPtr.unique()))
				this->SharedPtr = cow_ptr<T>(new T(*Tmp));
		}

		shared_ptr<T> SharedPtr;
	};
}//namespace gli

#endif//GLI_COW_PTR_INCLUDED
