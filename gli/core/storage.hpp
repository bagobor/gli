///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2012 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2012-06-21
// Updated : 2012-06-21
// Licence : This source is under MIT License
// File    : gli/core/storage.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_CORE_storage
#define GLI_CORE_storage GLI_VERSION

// STD
#include <vector>
#include <queue>
#include <cassert>
#include <cmath>
#include <cstring>

// GLM
#include <glm/glm.hpp>
#include <glm/gtx/number_precision.hpp>
#include <glm/gtx/raw_data.hpp>
#include <glm/gtx/gradient_paint.hpp>
#include <glm/gtx/component_wise.hpp>
#include <glm/gtx/integer.hpp>

#include "shared_ptr.hpp"

namespace gli
{
	enum face
	{
		FACE_DEFAULT   = 0x00000001,
		FACE_POSITIVEX = FACE_DEFAULT,
		FACE_NEGATIVEX = 0x00000002,
		FACE_POSITIVEY = 0x00000004,
		FACE_NEGATIVEY = 0x00000008,
		FACE_POSITIVEZ = 0x00000010,
		FACE_NEGATIVEZ = 0x00000020,
		FACE_ALL       = FACE_POSITIVEX | FACE_NEGATIVEX | FACE_POSITIVEY | FACE_NEGATIVEY | FACE_POSITIVEZ | FACE_NEGATIVEZ
	};

namespace detail
{
	class storage
	{
	public:
        typedef glm::uint dimensions1_type;
        typedef glm::uvec2 dimensions2_type;
		typedef glm::uvec3 dimensions3_type;
        typedef glm::uvec4 dimensions4_type;
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
				glm::uvec3 const & Dimensions, 
				size_type const & BlockSize);
            
			size_type const Layers; 
			flag_type const Faces;
			size_type const Levels;
			dimensions3_type const Dimensions;
			size_type const BlockSize;
		};
        
	public:
		storage();
        
		explicit storage(
            size_type const & Layers, 
            flag_type const & Faces,
            size_type const & Levels,
			dimensions3_type const & Dimensions,
            size_type const & BlockSize);
        
		~storage();
        
		bool empty() const;
		size_type layers() const; // Express in number of element
		flag_type faces() const; // Express in number of element
		size_type levels() const; // Express in number of element
		size_type blockSize() const; // Express is bytes
		dimensions3_type dimensions(
            size_type const & Level) const;
		size_type memorySize() const; // Express is bytes
		data_type * data();
		data_type const * const data() const;
        
		size_type linearAddressing(
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

	void copy_layers(
		storage const & SourceStorage, 
		storage::size_type const & SourceLayerOffset,
		storage::size_type const & SourceLayerSize,
		storage & DestinationStorage, 
		storage::size_type const & DestinationLayerOffset);

	void copy_faces(
		storage const & SourceStorage, 
		storage::size_type const & SourceLayerOffset,
		storage::size_type const & SourceFaceOffset,
		storage::size_type const & SourceLayerSize,
		storage & DestinationStorage, 
		storage::size_type const & DestinationLayerOffset,
		storage::size_type const & DestinationFaceOffset);

	void copy_levels(
		storage const & SourceStorage, 
		storage::size_type const & SourceLayerOffset,
		storage::size_type const & SourceFaceOffset,
		storage::size_type const & SourceLevelOffset,
		storage::size_type const & SourceLayerSize,
		storage & DestinationStorage, 
		storage::size_type const & DestinationLayerOffset,
		storage::size_type const & DestinationFaceOffset,
		storage::size_type const & DestinationlevelOffset);

}//namespace detail
}//namespace gli

#include "storage.inl"

#endif//GLI_CORE_storage
