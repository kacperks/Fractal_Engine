#pragma once

#include <malloc.h>
#include <iostream>
#include "MemoryFunctions.h"

namespace fr {
    inline size_t fr_strlen(const char* str) {
        size_t count = 0;
        while (*str != '\0') {
            ++count;
            ++str;
        }
        return count;
    }

    inline bool fr_strcmp(const char* f, const char* s) {
        return fr_memcmp(f, s, fr_strlen(s));
    }

    inline const char* MakeString(char c) {
        char* result = (char*)malloc(2);
        result[0] = c;
        result[1] = '\0';
        return result;
    }

    class String {
    private:
        char* data;
        size_t size;
    public:
        String(const char* str) {
            String::operator=(str);
        }

        String(String&& other) {
            data = other.data;
            size = other.size;
        }

        String(const String& other) {
            String::operator=(other);
        }

        String(char c) {
            String::operator=(c);
        }

        void operator=(const char* str) {
            data = (char*)malloc(fr_strlen(str));
            fr_memcpy(data, str, fr_strlen(str) + 1);
            data[fr_strlen(str)] = '\0';
            size = fr_strlen(str);
        }

        void operator=(const String& other) {
            String::operator=(other.data);
        }

        void operator=(std::string other) {
            String::operator=(other.c_str());
        }

        void operator=(char c) {
            String::operator=(MakeString(c));
        }

        bool operator==(const char* str) {
            return fr_strcmp(data, str) == 0;
        }

        bool operator==(const String& str) {
            return fr_strcmp(data, str.data) == 0;
        }

        bool operator==(char c) {
            return fr_strcmp(data, MakeString(c)) == 0;
        }

        bool operator!=(const char* str) {
            return fr_strcmp(data, str);
        }

        bool operator!=(const String& str) {
            return fr_strcmp(data, str.data);
        }

        bool operator!=(char c) {
            return fr_strcmp(data, MakeString(c));
        }

        void Append(char c) {
            Append(MakeString(c));
        }

        void Append(const String& other) {
            Append(other.data);
        }

        size_t Size() const {
            return size;
        }

        const char* CString() const {
            return data;
        }
    };
}