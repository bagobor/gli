///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2012 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2012-06-21
// Updated : 2012-06-21
// Licence : This source is under MIT License
// File    : gli/core/texture2d.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_CORE_TEXTURE2D_INCLUDED
#define GLI_CORE_TEXTURE2D_INCLUDED

#include "image2d.hpp"

namespace gli{
namespace detail
{
	class storage
	{
	public:
		typedef glm::uvec3 dimensions_type;
		typedef std::size_t size_type;
		typedef gli::format format_type;
		typedef glm::byte data_type;
        
	private:
		struct header
		{
            header();
            header(
                size_type const & Layers,
                glm::uint const & FaceFlag,
                size_type const & FaceCount,
                size_type const & Levels,
                format const & Format,
                dimensions_type const & Dimensions);
            
			size_type Layers; 
			glm::uint FaceFlag;
			size_type FaceCount;
			size_type Levels;
			format Format;
			dimensions_type Dimensions;
		};
        
	public:
		storage();
        
		explicit storage(
            size_type const & Layers, 
            glm::uint const & FaceFlag,
            size_type const & Faces,
            size_type const & Levels,
            format const & Format,
            dimensions_type const & Dimensions);
        
		~storage();
        
		bool empty() const;
		size_type layers() const;
		size_type faces() const;
		size_type levels() const;
		format_type format() const;
		dimensions_type dimensions() const;
		size_type memorySize() const;
		data_type* data();
		data_type const * const data() const;
        
		size_type linearImageAddressing(
            size_type const & Layer, 
            size_type const & Face, 
            size_type const & Level) const;
        
		template <typename genType>
		void swizzle(glm::comp X, glm::comp Y, glm::comp Z, glm::comp W);
        
	private:
		header Header;
		std::vector<data_type> Data;
        
        storage::size_type levelSize(size_type const & Level) const;
        storage::size_type faceSize() const;
        storage::size_type layerSize() const;
	};

}//namespace detail
}//namespace gli

#include "storage.inl"

#endif//GLI_CORE_TEXTURE2D_INCLUDED
