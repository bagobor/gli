///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2011-10-07
// Updated : 2011-10-07
// Licence : This source is under MIT licence
// File    : test/core/core.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <gli/gli.hpp>

int test_linearTextureAddressing_layer()
{
	int Error(0);

	gli::detail::storage StorageSrc(
		2, gli::FACE_DEFAULT, 1, 
		gli::detail::storage::SIZE1X32, 
		gli::detail::storage::dimensions3_type(2, 2, 1));   

	std::vector<glm::u8vec4> Data(8, glm::u8vec4(0));
	for(std::size_t i = 0; i < 4; ++i)
		Data[i + 0] = glm::u8vec4(255, 127, 0, 255);
	for(std::size_t i = 0; i < 4; ++i)
		Data[i + 4] = glm::u8vec4(0, 127, 255, 255);

	memcpy(StorageSrc.data(), &Data[0][0], Data.size() * sizeof(glm::u8vec4));

	gli::detail::storage StorageDst(
		1, 
		StorageSrc.faces(), 
		StorageSrc.levels(), 
		StorageSrc.layout(), 
		StorageSrc.dimensions());  

	memcpy(
		StorageSrc.data() + StorageSrc.linearTextureAddressing(1, 0, 0), 
		StorageDst.data(), 
		StorageSrc.layerSize());



	return Error;
}

int main()
{
	int Error(0);

	Error += test_linearTextureAddressing_layer();
		
	return Error;
}
