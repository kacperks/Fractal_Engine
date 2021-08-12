#pragma once

#include <memory.h>
#include <string.h>
#include <malloc.h>
#include <iostream>

namespace fr {
    static const char* MakeString(char c) {
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
            data = (char*)malloc(strlen(str));
            memcpy(data, str, strlen(str) + 1);
            data[strlen(str)] = '\0';
            size = strlen(str);
        }

        void operator=(const String& other) {
            String::operator=(other.data);
        }

        void operator=(std::string other){
            String::operator=(other.c_str());
        }

        void operator=(char c) {
            String::operator=(MakeString(c));
        }

        bool operator==(const char* str) {
            return strcmp(data, str) == 0;
        }

        bool operator==(const String& str) {
            return strcmp(data, str.data) == 0;
        }

        bool operator==(char c) {
            return strcmp(data, MakeString(c)) == 0;
        }

        bool operator!=(const char* str) {
            return strcmp(data, str);
        }

        bool operator!=(const String& str) {
            return strcmp(data, str.data);
        }

        bool operator!=(char c) {
            return strcmp(data, MakeString(c));
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