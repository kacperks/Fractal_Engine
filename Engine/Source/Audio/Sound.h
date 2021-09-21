#pragma once

#include "pch.h"
namespace fr::Audio {
    class Sound {
    private:
        FRuint m_buffer;
        int m_source;
        int m_loop;

    public:
        Sound() = default;
        ~Sound() = default;
        Sound(FRuint _buffer, int _SrcToUse, int _loop) : m_buffer(_buffer), m_source(_SrcToUse), m_loop(_loop) {}

        void Load(const char* filename);
        void Play();

        FRuint GetBuffer() { return m_buffer; }
    };
}