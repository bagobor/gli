///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2011-10-07
// Updated : 2011-10-07
// Licence : This source is under MIT licence
// File    : test/core/core.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <gli/gli.hpp>

int test_storage_size()
{
	int Error(0);
    
	gli::detail::storage Storage(
        2, gli::FACE_DEFAULT, 1, 
        4, 
        gli::detail::storage::dimensions3_type(2, 2, 1));   
    
	std::vector<glm::u8vec4> Data(8, glm::u8vec4(0));
	for(std::size_t i = 0; i < 4; ++i)
		Data[i + 0] = glm::u8vec4(255, 127, 0, 255);
	for(std::size_t i = 0; i < 4; ++i)
		Data[i + 4] = glm::u8vec4(0, 127, 255, 255);
    
	memcpy(Storage.data(), &Data[0][0], Data.size() * sizeof(glm::u8vec4));
    
    Error += Storage.blockSize() == 4 ? 0 : 1;
    Error += Storage.levelSize(0) == 4 ? 0 : 1;
    Error += Storage.faceSize() == 4 ? 0 : 1;
    Error += Storage.layerSize() == 4 ? 0 : 1;
    Error += Storage.memorySize() == 32 ? 0 : 1;
    
    return Error;
}

int test_linearTextureAddressing_layer()
{
	int Error(0);

	gli::detail::storage StorageSrc(
		2, gli::FACE_DEFAULT, 1, 
		sizeof(glm::u8vec4), 
		gli::detail::storage::dimensions3_type(2, 2, 1));   

	std::vector<glm::u8vec4> Data(8, glm::u8vec4(0));
	for(std::size_t i = 0; i < 4; ++i)
		Data[i + 0] = glm::u8vec4(255, 127, 0, 255);
	for(std::size_t i = 0; i < 4; ++i)
		Data[i + 4] = glm::u8vec4(0, 127, 255, 255);

    std::size_t MemorySizeSrc = StorageSrc.memorySize();
    
	memcpy(StorageSrc.data(), &Data[0][0], MemorySizeSrc);
/*
    for(std::size_t i = 0; i < 8; ++i)
    {
        glm::u8vec4 Value = *((glm::u8vec4*)&StorageSrc.data()[0] + i);
        printf("texel: %d, %d, %d, %d\n", Value.r, Value.g, Value.b, Value.a);
    }
*/    
	gli::detail::storage StorageDst(
		1, 
		StorageSrc.faces(), 
		StorageSrc.levels(), 
		StorageSrc.blockSize(), 
		StorageSrc.dimensions());  

    gli::detail::storage::size_type LayerSize = StorageSrc.layerSize();
    
    std::size_t OffsetSrc = StorageSrc.linearTextureAddressing(1, 0, 0);
    std::size_t OffsetDst = 0;
    
	memcpy(
		(glm::u8vec4*)&StorageDst.data()[0] + OffsetDst, 
		(glm::u8vec4*)&StorageSrc.data()[0] + OffsetSrc, 
		LayerSize * StorageSrc.blockSize());
 
    for(std::size_t i(0); i < LayerSize; ++i)
    {
        glm::u8vec4 SrcValue = *((glm::u8vec4*)StorageSrc.data() + OffsetSrc + i);
        glm::u8vec4 DstValue = *((glm::u8vec4*)StorageDst.data() + OffsetDst + i);
        Error += glm::all(glm::equal(DstValue, SrcValue)) ? 0 : 1; 
    }

	return Error;
}

int main()
{
	int Error(0);

    Error += test_storage_size();
	Error += test_linearTextureAddressing_layer();
		
    assert(!Error);
    
	return Error;
}
