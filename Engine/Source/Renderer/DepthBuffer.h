#pragma once

#include "pch.h"

using namespace fr;

class DepthBuffer {

public:
	DepthBuffer() : bufferID(0), depthMapID(0) { }

	DepthBuffer(GLsizei width, GLsizei height) {
		GLCALL(glGenTextures(1, &depthMapID));
		GLCALL(glBindTexture(GL_TEXTURE_2D, depthMapID));
		GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

		// attach to fbo
		GLCALL(glGenFramebuffers(1, &bufferID));
		GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, bufferID));
		GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMapID, 0));
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE && "FAILED TO CREATE FBO");
		GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
	}

	~DepthBuffer() {
		glDeleteTextures(1, &depthMapID);
		glDeleteFramebuffers(1, &bufferID);
	}

	void SetSize(GLsizei width, GLsizei height) {
		GLCALL(glBindTexture(GL_TEXTURE_2D, depthMapID));
		GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));
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
		GLCALL(glClear(GL_DEPTH_BUFFER_BIT));
	}

	const GLuint GetMapID() const {
		return depthMapID;
	}

	const GLuint GetBufferID() const {
		return depthMapID;
	}

private:
	GLuint bufferID;
	GLuint depthMapID;
};