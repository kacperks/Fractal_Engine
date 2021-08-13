#pragma once

#include "pch.h"

class Renderer {
public:
	Renderer() = default;
	~Renderer() = default;
	Renderer(const Renderer&) = default;

	Renderer(int width, int height);
	Renderer(Vec2 Size);

	void EnableRenderer(GLenum cap) { glEnable(cap); }
	void DisableRenderer(GLenum cap) { glDisable(cap); }

	SamplerBuffer GetSamplerBuffer() { return _SamplerBuffer; }
	DepthBuffer GetDepthBuffer() { return _DepthBuffer; }
	void SetViewport(int x, int y, int w, int h) { glViewport(x, y, w, h); }
	void SetViewport(Vec4 w) { glViewport(w.x, w.y, w.z, w.w); }

private:
	SamplerBuffer _SamplerBuffer;
	DepthBuffer _DepthBuffer;
};