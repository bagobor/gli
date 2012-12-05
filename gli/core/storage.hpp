///////////////////////////////////////////////////////////////////////////////////
/// OpenGL Image (gli.g-truc.net)
///
/// Copyright (c) 2008 - 2012 G-Truc Creation (www.g-truc.net)
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
/// 
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///
/// @ref core
/// @file gli/core/storage.hpp
/// @date 2012-06-21 / 2012-10-19
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_CORE_STORAGE_INCLUDED
#define GLI_CORE_STORAGE_INCLUDED

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
#include <glm/gtx/multiple.hpp>

#include "shared_ptr.hpp"
#include "header.hpp"

namespace gli{
namespace detail
{
	class storage
	{
	public:
		typedef glm::uint dimensions1_type;
		typedef glm::uvec2 dimensions2_type;
		typedef glm::uvec3 dimensions3_type;
		typedef glm::uvec4 dimensions4_type;
		typedef float texcoord1_type;
		typedef glm::vec2 texcoord2_type;
		typedef glm::vec3 texcoord3_type;
		typedef std::size_t size_type;

	private:
		struct desc
		{
			desc();
			desc(
				size_type const & Layers,
				size_type const & Faces,
				size_type const & Levels,
				glm::uvec3 const & Dimensions, 
				size_type const & BlockSize,
				dimensions3_type const & BlockDimensions);

			size_type const Layers; 
			size_type const Faces;
			size_type const Levels;
			dimensions3_type const Dimensions;
			size_type const BlockSize;
			dimensions3_type const BlockDimensions;
		};

	public:
		storage();

		explicit storage(
			size_type const & Layers, 
			size_type const & Faces,
			size_type const & Levels,
			dimensions3_type const & Dimensions,
			size_type const & BlockSize,
			dimensions3_type const & BlockDimensions);

		~storage();

		bool empty() const;
		size_type layers() const; // Express in number of element
		size_type faces() const; // Express in number of element
		size_type levels() const; // Express in number of element
		size_type blockSize() const; // Express is bytes
		dimensions3_type blockDimensions() const; // Express is bytes
		dimensions3_type dimensions(
			size_type const & Level) const;
		size_type size() const; // Express is bytes
		glm::byte * data();
		glm::byte const * const data() const;

		size_type levelSize(
			size_type const & Level) const;
		size_type faceSize() const;
		size_type layerSize() const;

		bool isSubset(detail::view const & View) const;

	private:
		desc const Desc;
		std::vector<glm::byte> Data;
	};

/*
	storage extractLayers(
		storage const & Storage, 
		storage::size_type const & Offset, 
		storage::size_type const & Size);
*/
/*
	storage extractFace(
		storage const & Storage, 
		face const & Face);
*/
/*
	storage extractLevels(
		storage const & Storage, 
		storage::size_type const & Offset, 
		storage::size_type const & Size);
*/
/*
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
*/
}//namespace detail
}//namespace gli

#include "storage.inl"

#endif//GLI_CORE_STORAGE_INCLUDED
