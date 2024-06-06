#pragma once

#include "Renderer.h"

#include <string>

class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP; // m_BPP = Bits Per Pixel
public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void UnBind() const;

	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }

};

