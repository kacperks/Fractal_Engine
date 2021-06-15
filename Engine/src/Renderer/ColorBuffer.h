#pragma once

#pragma once

using namespace fr;

class ColorBuffer {

public:
	ColorBuffer() : bufferID(0), textureID(0) { }

	ColorBuffer(GLsizei width, GLsizei height) {
		GLCALL(glGenTextures(1, &textureID));
		GLCALL(glBindTexture(GL_TEXTURE_2D, textureID));
		GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCALL(glBindTexture(GL_TEXTURE_2D, 0));

		// attach to fbo
		GLCALL(glGenFramebuffers(1, &bufferID));
		GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, bufferID));
		GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0));
		assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE && "FAILED TO CREATE FBO");
		GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	~ColorBuffer() {
		glDeleteTextures(1, &textureID);
		glDeleteFramebuffers(1, &bufferID);
	}

	void SetSize(GLsizei width, GLsizei height) {
		GLCALL(glBindTexture(GL_TEXTURE_2D, textureID));
		GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
		GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
	}

	void Bind() {
		GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, bufferID));
	}

	void UnBind() {
		GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	void Clear() {
		GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, bufferID));
		GLCALL(glClear(GL_COLOR_BUFFER_BIT));
	}

	const GLuint TexID() const {
		return textureID;
	}

	const GLuint GetID() const {
		return textureID;
	}

private:
	GLuint bufferID;
	GLuint textureID;
};