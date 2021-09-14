#pragma once

#include "pch.h"
namespace fr::Audio{
    class Sound {
    private:
    FRuint buffer;
    int SrcToUse;
    int loop;

    public:
    Sound() = default;
    ~Sound() = default;
    Sound(FRuint _buffer, int _SrcToUse, int _loop) : buffer(_buffer), SrcToUse(_SrcToUse), loop(_loop) {}

    void Load(const char* filename);
    void Play();

    FRuint GetBuffer() { return buffer; }
    };
}