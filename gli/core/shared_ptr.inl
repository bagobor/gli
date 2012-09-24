///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2012-09-01
// Updated : 2012-09-23
// Licence : This source is under MIT License
// File    : gli/shared_ptr.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace gli
{
	template <typename T>
	inline shared_ptr<T>::shared_ptr() :
		Counter(0),
		Pointer(0)
	{}

	template <typename T>
	inline shared_ptr<T>::shared_ptr(shared_ptr<T> const & SharedPtr) :
		Counter(SharedPtr.Counter),
		Pointer(SharedPtr.Pointer)
	{
		if(this->Counter)
			(*this->Counter)++;
	}

	template <typename T>
	inline shared_ptr<T>::shared_ptr(T * Pointer) :
		Counter(new long(1)),
		Pointer(Pointer)
	{}

	template <typename T>
	inline shared_ptr<T>::~shared_ptr()
	{
		this->reset();
	}

	template <typename T>
	inline shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr<T> const & SharedPtr)
	{
		// Self assignment
		if(this == &SharedPtr)
			return *this;

		if(this->Pointer)
		{
			(*this->Counter)--;
			if(*this->Counter <= 0)
			{
				delete this->Counter;
				delete this->Pointer;
			}
		}

		this->Counter = SharedPtr.Counter;
		this->Pointer = SharedPtr.Pointer;
		(*this->Counter)++;

		return *this;
	}

	template <typename T>
	inline shared_ptr<T> & shared_ptr<T>::operator=(T * Pointer)
	{
		if(this->Pointer)
		{
			(*this->Counter)--;
			if(*this->Counter <= 0)
			{
				delete this->Counter;
				delete this->Pointer;
			}
		}

		this->Counter = new long(1);
		this->Pointer = Pointer;
		//(*this->Reference) = 1;

		return *this;
	}

	template <typename T>
	inline bool shared_ptr<T>::operator==(shared_ptr<T> const & SharedPtr) const
	{
		return this->Pointer == SharedPtr.Pointer;
	}

	template <typename T>
	inline bool shared_ptr<T>::operator!=(shared_ptr<T> const & SharedPtr) const
	{
		return this->Pointer != SharedPtr.Pointer;
	}
/*
	template <typename T>
	inline T& shared_ptr<T>::operator*()
	{
		return *this->Pointer;
	}

	template <typename T>
	inline T * shared_ptr<T>::operator->()
	{
		return this->Pointer;
	}
*/

	template <typename T>
	inline T * shared_ptr<T>::get() const
	{
		return this->Pointer;
	}

	template <typename T>
	inline T const & shared_ptr<T>::operator*() const
	{
		return *this->Pointer;
	}

	template <typename T>
	inline T & shared_ptr<T>::operator*()
	{
		return *this->Pointer;
	}

	template <typename T>
	inline T const * const shared_ptr<T>::operator->() const
	{
		return this->Pointer;
	}

	template <typename T>
	inline T * shared_ptr<T>::operator->()
	{
		return this->Pointer;
	}

	template <typename T>
	inline void shared_ptr<T>::reset()
	{
		if(!this->Pointer)
			return;

		(*this->Counter)--;
		if(*this->Counter <= 0)
		{
			delete this->Counter;
			delete this->Pointer;
		}

		this->Counter = 0;
		this->Pointer = 0;
	}

	template <typename T>
	inline void shared_ptr<T>::reset(T * Pointer)
	{
		this->reset();
		this->Counter = new long(1);
		this->Pointer = Pointer;
	}

	template <typename T>
	inline long shared_ptr<T>::use_count() const
	{
		return this->Counter ? *this->Counter : 0;
	}

	template <typename T>
	inline bool shared_ptr<T>::unique() const
	{
		return this->Counter ? *this->Counter == 1 : false;
	}
}//namespace gli
