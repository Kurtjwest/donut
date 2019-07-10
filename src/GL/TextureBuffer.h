#pragma once

#include <glad/glad.h>
#include <vector>

namespace Donut::GL {

class TextureBuffer {

public:
    TextureBuffer();
	~TextureBuffer();

    void Bind();
    void Unbind();
    void SetBuffer(void* buffer, unsigned int length);

protected:
    GLuint m_handle;
    GLuint m_bufferHandle;
};
} // namespace Donut::GL
