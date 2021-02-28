#pragma once

#include "../fractal.hpp"
#include "../Errors/ErrorLog.h"

class FrameBuffer {

public:
	FrameBuffer(): frameBuffer(0), RenderBuffer(0), textureID(0) {}

	FrameBuffer(GLsizei width, GLsizei height) {		
		GLCALL(glGenTextures(1, &textureID));
		GLCALL(glGenFramebuffers(1, &frameBuffer));
		GLCALL(glGenRenderbuffers(1, &RenderBuffer));
		SetSize(width, height);
	}

	~FrameBuffer() {
		glDeleteRenderbuffers(1, &RenderBuffer);
		glDeleteFramebuffers(1, &frameBuffer);
		glDeleteTextures(1, &textureID);
	}

	void SetSize(GLsizei width, GLsizei height) {
		GLCALL(glBindTexture(GL_TEXTURE_2D, textureID));
		GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

		GLCALL(glBindRenderbuffer(GL_RENDERBUFFER, RenderBuffer));
		GLCALL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height));

		GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer));
		GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0));
		GLCALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RenderBuffer));

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			std::cerr << "ERROR::FRAMEBUFFER::IS NOT COMPLETE!" << std::endl;
		}

		GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	void Bind() {
		GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer));
	}

	void UnBind() {
		GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	void Clear() {
		GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer));
		GLCALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
	}

	GLuint GetTexID() const {
		return textureID;
	}

private:
	GLuint textureID;
	GLuint frameBuffer;
	GLuint RenderBuffer;
};

