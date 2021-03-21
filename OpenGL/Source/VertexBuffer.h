#pragma once

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer();
	VertexBuffer(const void* data, const unsigned int size);
	~VertexBuffer();

	void Init(const void* data, const unsigned int size);
	void Bind() const;
	void Unbind() const;
};

