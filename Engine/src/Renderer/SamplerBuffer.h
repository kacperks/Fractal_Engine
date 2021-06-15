#pragma once

using namespace fr;

class SamplerBuffer {

public:
	SamplerBuffer(): bufferID(0), renderID(0), textureID(0), width(0), height(0) { }

	SamplerBuffer(GLsizei w, GLsizei h): width(w), height(h) {
		GLCALL(glGenTextures(1, &textureID));
		GLCALL(glBindTexture(GL_TEXTURE_2D, textureID));
		GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCALL(glBindTexture(GL_TEXTURE_2D, 0));

		GLCALL(glGenRenderbuffers(1, &renderID));
		GLCALL(glBindRenderbuffer(GL_RENDERBUFFER, renderID));
		GLCALL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height));
		GLCALL(glBindRenderbuffer(GL_RENDERBUFFER, 0));

		// attach to fbo
		GLCALL(glGenFramebuffers(1, &bufferID));
		GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, bufferID));
		
		GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0));
		GLCALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderID));

		assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE && "FAILED TO CREATE FBO");
		GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	~SamplerBuffer() {
		glDeleteTextures(1, &textureID);
		glDeleteRenderbuffers(1, &renderID);
		glDeleteFramebuffers(1, &bufferID);
	}

	void SetSize(GLsizei w, GLsizei h) {
		width = w;
		height = h;
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
		//GLCALL(glClearColor(0.87, 0.87, 0.85, 1.0));
		GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
	}

	void BlitTo(GLuint targetBufferID) {
		GLCALL(glBindFramebuffer(GL_READ_FRAMEBUFFER, bufferID));
		GLCALL(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, targetBufferID));
		glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
		GLCALL(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));
	}

	const GLuint TexID() const {
		return textureID;
	}

	const GLuint GetID() const {
		return textureID;
	}

private:
	GLsizei width, height;
	GLuint bufferID, renderID, textureID;
};

//GLCALL(glGenTextures(1, &textureID));
		//GLCALL(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, textureID));
		//GLCALL(glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, width, height, GL_TRUE));
		//GLCALL(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0));

		//GLCALL(glGenRenderbuffers(1, &renderID));
		//GLCALL(glBindRenderbuffer(GL_RENDERBUFFER, renderID));
		//GLCALL(glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, width, height));
		//GLCALL(glBindRenderbuffer(GL_RENDERBUFFER, 0));

		//// attach to fbo
		//GLCALL(glGenFramebuffers(1, &bufferID));
		//GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, bufferID));
		//GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, textureID, 0));
		//GLCALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderID));

		//assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE && "FAILED TO CREATE FBO");
		//GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));