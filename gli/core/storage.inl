///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2012 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2012-06-21
// Updated : 2012-06-21
// Licence : This source is under MIT License
// File    : gli/core/storage.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace gli{
namespace detail
{
	inline storage::header::header() :
		Layers(0),
		FaceFlag(0),
		FaceCount(0),
		Levels(0),
		Format(0),
		Dimensions(0)
	{}
	
    inline header
    (
        size_type const & Layers,
        glm::uint const & FaceFlag,
        size_type const & FaceCount,
        size_type const & Levels,
        format const & Format,
        dimensions_type const & Dimensions
    ) :
    	Layers(Layers),
    	FaceFlag(FaceFlag),
    	FaceCount(FaceCount),
    	Levels(Levels),
    	Format(Format),
    	Dimensions(Dimensions)
    {}
	
	inline storage::storage()
	{}

	inline storage::storage
	(
		size_type const & Layers, 
    	glm::uint const & FaceFlag,
    	size_type const & Faces,
        size_type const & Levels,
        format const & Format,
        dimensions_type const & Dimensions
    ) : 
    	header(Layers, FaceFlag, Faces, Levels, Format, Dimensions)
    {}

    inline storage::size_type storage::levelSize
    (
        storage::size_type const & Level
    ) const
    {
        size_type const TexelSize = gli::detail::getFormatInfo(this->format()).BBP;
        
        dimensions_type const Dimensions = glm::max(this->dimensions() >> glm::uint(Level), dimensions_type(1));
        return Dimensions.x * Dimensions.y * Dimensions.z * TexelSize;
    }
    
    inline storage::size_type storage::faceSize() const
    {
        size_type FaceSize(0);
        size_type const TexelSize = gli::detail::getFormatInfo(this->format()).BBP;
        
        // The size of a face is the sum of the size of each level.
        for(storage::size_type Level(0); Level < this->levels(); ++Level)
        {
            dimensions_type const Dimensions = glm::max(this->dimensions() >> glm::uint(Level), dimensions_type(1));
            size_type const LevelSize = Dimensions.x * Dimensions.y * Dimensions.z * TexelSize;
            FaceSize += LevelSize;
        }
        
        return FaceSize * TexelSize;    
    }
    
    inline storage::size_type storage::layerSize() const
    {
        // The size of a layer is the sum of the size of each face.
        // All the faces have the same size.
        return face_size() * this->faces();
    }
    
	inline storage::size_type storage::linearImageAddressing
	(
		storage::size_type const & Layer, 
		storage::size_type const & Face, 
		storage::size_type const & Level
	) const
	{
		size_type Offset(0);
		size_type const TexelSize = gli::detail::getFormatInfo(this->format()).BBP;

		dimensions_type Dimensions = this->dimensions();

		for(storage::size_type LevelCurrent(0); LevelCurrent <= Level; ++LevelCurrent)
		{
			Dimensions >>= LevelCurrent;
			Dimensions = glm::max(Dimensions, dimensions_type(1));
			size_type LevelSize = Dimensions.x * Dimensions.y * Dimensions.z * TexelSize;
			Offset += LevelSize;
		}

		return Offset;
	}

}//namespace detail
}//namespace gli
