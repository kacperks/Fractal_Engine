#pragma once

#include "pch.h"

namespace fr {
	inline void* fr_memcpy(void* dst, const void* src, size_t size) {
		FRuchar* byteDst = (FRuchar*)dst;
		const FRuchar* byteSrc = (const FRuchar*)src;
		size_t count = size;
		if (byteDst == nullptr || byteSrc == nullptr)
			return nullptr;
		while (count > 0)
		{
			*(byteDst++) = *(byteSrc++);
			--count;
		}
		return dst;
	}

	inline bool fr_memcmp(const void* f, const void* s, size_t size) {
		const FRuchar* bytef = (const FRuchar*)f;
		const FRuchar* bytes = (const FRuchar*)s;
		size_t count = size;
		if (bytef == nullptr || bytes == nullptr)
			return false;
		while (count > 0)
		{
			if (*(bytef++) == *(bytes++))
			{
				return true;
				break;
			}
			--count;
		}
		return false;
	}
}
