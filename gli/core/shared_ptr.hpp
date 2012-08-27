///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-12-19
// Updated : 2005-06-13
// Licence : This source is under MIT License
// File    : gli/fetch.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_SHARED_PTR_INCLUDED
#define GLI_SHARED_PTR_INCLUDED

namespace gli
{
    template <typename T>
    class shared_ptr
    {
/* TODO: make_shared
		template typename T
		class refcounter
		{
			Long Counter;
			T Data;
		};
*/

    public:
        shared_ptr();
        shared_ptr(shared_ptr const & SharedPtr);
        explicit shared_ptr(T * Pointer);
        ~shared_ptr();

        T & operator*() const;
        T * operator->() const;
		T * get() const;
        //T const & operator*() const;
        //T const * const operator->() const;
        shared_ptr& operator=(shared_ptr const & SharedPtr);
        shared_ptr& operator=(T * Pointer);
	    bool operator==(shared_ptr const & SharedPtr) const;
	    bool operator!=(shared_ptr const & SharedPtr) const;
		
		void reset();
        void reset(T * Pointer);
		long use_count() const;
		bool unique() const;

    private:
        long * Counter;
        T * Pointer;
    };
}//namespace gli

#include "shared_ptr.inl"

#endif //GLI_SHARED_PTR_INCLUDED
