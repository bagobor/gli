///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2012-11-19
// Updated : 2012-11-19
// Licence : This source is under MIT licence
// File    : test/core/core_addressing.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <gli/core/addressing.hpp>
#include <gli/core/format.hpp>

int test_addressing_layers()
{
	int Error(0);

	{
		gli::detail::storage Storage(
			2, 
			gli::faceCount(gli::FACE_DEFAULT), 
			1, 
			gli::detail::storage::dimensions3_type(4, 4, 1), 
			gli::block_size(gli::RGBA8U), 
			gli::block_dimensions(gli::RGBA8U));

		gli::detail::storage::size_type Offset = gli::detail::linearAddressing(Storage, 1, 0, 0);
		gli::detail::storage::size_type Size = Storage.size();

		Error += Offset == 64 ? 0 : 1;
		Error += Size == 128 ? 0 : 1;
	}

	{
		gli::detail::storage Storage(
			2, 
			gli::faceCount(gli::FACE_DEFAULT), 
			1, 
			gli::detail::storage::dimensions3_type(4, 4, 1), 
			gli::block_size(gli::DXT1), 
			gli::block_dimensions(gli::DXT1));

		gli::detail::storage::size_type Offset = gli::detail::linearAddressing(Storage, 1, 0, 0);
		gli::detail::storage::size_type Size = Storage.size();

		Error += Offset == 8 ? 0 : 1;
		Error += Size == 16 ? 0 : 1;
	}

	return Error;
}

int main()
{
	int Error(0);

	Error += test_addressing_layers();

	return Error;
}
