///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2011-10-07
// Updated : 2012-09-23
// Licence : This source is under MIT licence
// File    : test/core/core.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <gli/core/storage.hpp>

int test_storage_size()
{
	int Error(0);

	gli::detail::storage Storage(
		2, 1, 1,
		gli::detail::storage::dimensions3_type(2, 2, 1),
		sizeof(glm::u8vec4),
		gli::detail::storage::dimensions3_type(1));

	std::vector<glm::u8vec4> Data(8, glm::u8vec4(0));
	for(std::size_t i = 0; i < 4; ++i)
		Data[i + 0] = glm::u8vec4(255, 127, 0, 255);
	for(std::size_t i = 0; i < 4; ++i)
		Data[i + 4] = glm::u8vec4(0, 127, 255, 255);

	memcpy(Storage.data(), &Data[0][0], Data.size() * sizeof(glm::u8vec4));

	Error += Storage.blockSize() == sizeof(glm::u8vec4) ? 0 : 1;
	Error += Storage.levelSize(0) == sizeof(glm::u8vec4) * 2 * 2 ? 0 : 1;
	Error += Storage.faceSize() == sizeof(glm::u8vec4) * 2 * 2 ? 0 : 1;
	Error += Storage.layerSize() == sizeof(glm::u8vec4) * 2 * 2 ? 0 : 1;
	Error += Storage.size() == sizeof(glm::u8vec4) * 2 * 2 * 2 ? 0 : 1;

	return Error;
}

int main()
{
	int Error(0);

	Error += test_storage_size();

	assert(!Error);

	return Error;
}
