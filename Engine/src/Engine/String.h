#pragma once

#include "pch.h"

namespace fr {
	class string
	{
	private:
		~string() = default;
		const char* charptr;
	public:
		string(const char* str) { charptr = str; }
		string() = default;

		string& operator=(const char* str) {
			charptr = str;
			return *this;
		}

		const char* operator+(const char* str) {
			return (charptr, str);
		}

		const char* operator+(const string& other) {
			return charptr, charptr;
		}

		const char* Get(uint32_t size) {
			for (int i = 0; i < size; i++) {
				return charptr;
			}
			return nullptr;
		}

		string& GetString(uint32_t size) {
			string str = ((char*)Get(size));
			return str;
		}

		uint32_t GetSize() { return (sizeof(charptr) * sizeof(char)); }
		const char* GetCharPtr() { return charptr; }
	};

	using FRstring = string;
}