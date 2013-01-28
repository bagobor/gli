///////////////////////////////////////////////////////////////////////////////////
/// OpenGL Image (gli.g-truc.net)
///
/// Copyright (c) 2008 - 2013 G-Truc Creation (www.g-truc.net)
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
/// @file gli/core/save_dds.inl
/// @date 2013-01-28 / 2013-01-28
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

namespace gli
{
	inline void saveStorageDDS
	(
		storage const & Storage, 
		std::string const & Filename
	)
	{
		if(Storage.empty())
			return;

		std::ofstream File(Filename.c_str(), std::ios::out | std::ios::binary);
		if (!File)
			return;

		detail::format_desc const & Desc = detail::getFormatInfo(Storage.format());

		char const * Magic = "DDS ";
		File.write((char*)Magic, sizeof(char) * 4);

		glm::uint32 Caps = detail::DDSD_CAPS | detail::DDSD_WIDTH | detail::DDSD_PIXELFORMAT | detail::DDSD_MIPMAPCOUNT;
		Caps |= Storage.dimensions(0).y > 1 ? detail::DDSD_HEIGHT : 0;
		Caps |= Storage.dimensions(0).z > 1 ? detail::DDSD_DEPTH : 0;
		//Caps |= Storage.levels() > 1 ? detail::DDSD_MIPMAPCOUNT : 0;
		Caps |= Desc.Compressed ? detail::DDSD_LINEARSIZE : detail::DDSD_PITCH;

		detail::ddsHeader HeaderDesc;
		memset(HeaderDesc.reserved1, 0, sizeof(HeaderDesc.reserved1));
		memset(HeaderDesc.reserved2, 0, sizeof(HeaderDesc.reserved2));
		HeaderDesc.size = sizeof(detail::ddsHeader);
		HeaderDesc.flags = Caps;
		HeaderDesc.width = Storage.dimensions(0).x;
		HeaderDesc.height = Storage.dimensions(0).y;
		HeaderDesc.pitch = glm::uint32(Desc.Compressed ? Storage.size() : 32);
		HeaderDesc.depth = Storage.dimensions(0).z > 1 ? Storage.dimensions(0).z : 0;
		HeaderDesc.mipMapLevels = glm::uint32(Storage.levels());
		HeaderDesc.format.size = sizeof(detail::ddsPixelFormat);
		HeaderDesc.format.flags = Storage.layers() > 1 ? detail::DDPF_FOURCC : Desc.Flags;
		HeaderDesc.format.fourCC = Storage.layers() > 1 ? detail::DDPF_FOURCC : Desc.FourCC;
		HeaderDesc.format.bpp = glm::uint32(Desc.BBP);
		HeaderDesc.format.redMask = 0x000000ff;
		HeaderDesc.format.greenMask = 0x0000ff00;
		HeaderDesc.format.blueMask = 0x00ff0000;
		HeaderDesc.format.alphaMask = 0xff000000;
		//HeaderDesc.surfaceFlags = detail::DDSCAPS_TEXTURE | (Storage.levels() > 1 ? detail::DDSCAPS_MIPMAP : 0);
		HeaderDesc.surfaceFlags = detail::DDSCAPS_TEXTURE | detail::DDSCAPS_MIPMAP;
		HeaderDesc.cubemapFlags = 0;

		// Cubemap
		if(Storage.faces() > 1)
		{
			assert(Storage.faces() == 6);
			HeaderDesc.cubemapFlags |= detail::DDSCAPS2_CUBEMAP_ALLFACES;
		}

		// Texture3D
		if(Storage.dimensions(0).z > 1)
			HeaderDesc.cubemapFlags |= detail::DDSCAPS2_VOLUME;


		storage::size_type DepthCount = 1;
		if(HeaderDesc.cubemapFlags & detail::DDSCAPS2_VOLUME)
				DepthCount = HeaderDesc.depth;

		File.write((char*)&HeaderDesc, sizeof(HeaderDesc));

		if(HeaderDesc.format.fourCC == detail::D3DFMT_DX10)
		{
			detail::ddsHeader10 HeaderDesc10;
			HeaderDesc10.arraySize = glm::uint32(Storage.layers());
			HeaderDesc10.resourceDimension = detail::D3D10_RESOURCE_DIMENSION_TEXTURE2D;
			HeaderDesc10.miscFlag = 0;//Storage.levels() > 0 ? detail::D3D10_RESOURCE_MISC_GENERATE_MIPS : 0;
			HeaderDesc10.dxgiFormat = detail::DXGI_FORMAT(Desc.Format);
			HeaderDesc10.reserved = 0;
			File.write((char*)&HeaderDesc10, sizeof(HeaderDesc10));
		}

		std::size_t Size = Storage.size();
		File.write((char*)(Storage.data()), Size);

		assert(!File.fail() && !File.bad());
	}
}//namespace gli
