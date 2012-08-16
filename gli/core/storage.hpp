///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2012 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2012-06-21
// Updated : 2012-06-21
// Licence : This source is under MIT License
// File    : gli/core/storage.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_CORE_storage
#define GLI_CORE_storage

#include "image2d.hpp"

namespace gli{
namespace detail
{
	class storage
	{
	public:
        typedef glm::uint dimensions1_type;
        typedef glm::uvec2 dimensions2_type;
		typedef glm::uvec3 dimensions3_type;
		typedef glm::uint flag_type;
        typedef float texcoord1_type;
        typedef glm::vec2 texcoord2_type;
		typedef glm::vec3 texcoord3_type;
		typedef std::size_t size_type;
		typedef glm::byte data_type;
        typedef gli::face face_type;
        
	private:
		struct header
		{
            header();
            header(
                size_type const & Layers,
                flag_type const & Faces,
                size_type const & Levels,
                size_type const & BlockSize,
                glm::uvec3 const & Dimensions, 
                size_type const & BaseOffset);
            
			size_type const Layers; 
			flag_type const Faces;
			size_type const Levels;
			size_type const BlockSize;
			glm::uvec3 const Dimensions;
            size_type const BaseOffset;
		};
        
	public:
		storage();
        
		explicit storage(
            size_type const & Layers, 
            flag_type const & Faces,
            size_type const & Levels,
            size_type const & BlockSize,
            dimensions3_type const & Dimensions);
			//size_type const & BaseOffset);
        
		~storage();
        
		bool empty() const;
		size_type layers() const;
		flag_type faces() const;
		size_type levels() const;
		size_type blockSize() const;
		dimensions3_type dimensions() const;
		size_type memorySize() const;
		data_type* data();
		data_type const * const data() const;
        
		size_type linearTextureAddressing(
            size_type const & Layer, 
            size_type const & Face, 
            size_type const & Level) const;
        size_type levelSize(
			size_type const & Level) const;
        size_type faceSize() const;
        size_type layerSize() const;

		template <typename genType>
		void swizzle(glm::comp X, glm::comp Y, glm::comp Z, glm::comp W);
        
	private:
		header const Header;
		std::vector<data_type> Data;
	};

    storage extractLayers(
        storage const & Storage, 
        storage::size_type const & Offset, 
		storage::size_type const & Size);
    
    storage extractFace(
        storage const & Storage, 
        face const & Face);
    
    storage extractLevels(
        storage const & Storage, 
        storage::size_type const & Offset, 
		storage::size_type const & Size);

}//namespace detail
}//namespace gli

#include "storage.inl"

#endif//GLI_CORE_storage
