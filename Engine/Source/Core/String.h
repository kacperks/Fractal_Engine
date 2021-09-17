#pragma once

#include <string.h>
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
        return strcmp(f, s);
    }

    class String {
    private:
        char* data;
        size_t size;
    public:
        void Resize(size_t len) {
            if(size != len) {
               if(!size) {
                   data = new char[len];
               } else {
                   char* new_data = new char[len];
                   fr_memcpy(new_data, data, len);
                   delete data;
                   data = new_data;
               }
               size = len;
            }
            data[len] = 0;
        }
        
        void Assign(const char* str, size_t len) {
            data = new char[len];
            fr_memcpy(data, str, len);
            data[len] = 0;
            size = len;
        }
        
        String(const char* str, size_t len) {
            Assign(str, len);
        }
        
        String(const char* str) {
            Assign(str, fr_strlen(str));
        }

        String(String&& other) {
            data = other.data;
            size = other.size;
        }

        String(const String& other) {
            Assign(other.data, other.size);
        }

        const char At(int i) const {
            return data[i];   
        }
        
        char& At(int i) {
            return data[i];   
        }
        
        const char operator[](int i) const {
            return data[i];  
        }
        
        char& operator[](int i) {
            return data[i];   
        }
        
        void operator=(const String& other) {
            String::operator=(other.data);
        }

        bool operator==(const String& str) {
            return fr_strcmp(data, str.data) == 0;
        }
        
        bool operator!=(const String& str) {
            return fr_strcmp(data, str.data);
        }
        
        bool operator>=(const String& other) {
            return fr_strcmp(data, other.data) >= 0;
        }
        
        bool operator<=(const String& other) {
            return fr_strcmp(data, other.data) <= 0;
        }
        
        bool operator>(const String& other) {
            return fr_strcmp(data, other.data) > 0;
        }
        
        bool operator<(const String& other) {
            return fr_strcmp(data, other.data) < 0;
        }
        
        void operator+=(const String& other) {
            Append(other);   
        }
        
        void Append(const char* str, size_t len) {
            const int old = (int)size;
            Resize(old + len);
            fr_memcpy(data + old, str, len);
        }
        
        void Append(const String& other) {
            Append(other.data);
        }
        
        void Clear() {
            Resize(0);   
        }

        String substr(int start, int end) {
            return String(data + start, end);   
        }
        
        size_t Size() const {
            return size;
        }

        char* Data() {
            return data;   
        }
        
        const char* CString() const {
            return data;
        }
    };
    
    String operator+(const char* f, String s) {
        String result = String(f);
        result += s;
        return result;
    }
}
