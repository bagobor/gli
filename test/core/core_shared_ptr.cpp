///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2012 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2012-10-07
// Updated : 2012-10-07
// Licence : This source is under MIT licence
// File    : test/core/core_shared_ptr.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <gli/gli.hpp>

int main()
{
	int Error(0);

	gli::shared_ptr<int> DataA(new int(76));

	Error += DataA.unique() ? 0 : 1;

	gli::shared_ptr<int> DataB = DataA;

	Error += DataA.use_count() == 2 ? 0 : 1;
	Error += DataB.use_count() == 2 ? 0 : 1;

	{
		DataB.reset();
		long CountA = DataA.use_count();
		long CountB = DataB.use_count();
		Error += CountA == 1 ? 0 : 1;
		Error += CountB == 0 ? 0 : 1;
	}

	{
		DataA.reset();
		long CountA = DataA.use_count();
		long CountB = DataB.use_count();
		Error += CountA == 0 ? 0 : 1;
		Error += CountB == 0 ? 0 : 1;
	}

	{

	}

    assert(!Error);
    
	return Error;
}
