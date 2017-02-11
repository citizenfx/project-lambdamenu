/*
	THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
				http://dev-c.com			
			(C) Alexander Blade 2015
*/

#pragma once

#include "main.h"

template <typename T>
inline void nativePush(T val)
{
	UINT64 val64 = 0;
	if (sizeof(T) > sizeof(UINT64))
	{
		throw "error, value size > 64 bit";
	}
	*reinterpret_cast<T *>(&val64) = val; // &val + sizeof(dw) - sizeof(val)
	nativePush64(val64);
}

template<>
inline void nativePush(const char* val)
{
	nativePushString(val);
}

template<>
inline void nativePush(char* val)
{
	nativePushString(val);
}

template<>
inline void nativePush(BOOL val)
{
	nativePushInt(val);
}

template<>
inline void nativePush(uint32_t val)
{
	nativePushInt(val);
}

template<>
inline void nativePush(float val)
{
	nativePushFloat(val);
}

template<>
inline void nativePush(double val)
{
	nativePush(static_cast<float>(val));
}

template<>
inline void nativePush(Vector3* ptr)
{
	nativePushPtr(4, ptr);
}

template<>
inline void nativePush(float* ptr)
{
	nativePushPtr(3, ptr);
}

template<>
inline void nativePush(uint32_t* ptr)
{
	nativePushPtr(2, ptr);
}

template<>
inline void nativePush(int* ptr)
{
	nativePushPtr(1, ptr);
}

template<>
inline void nativePush(void* ptr)
{
	nativePushPtr(0, ptr);
}

template<typename TRet>
inline TRet nativeCallTemplated()
{
	//static_assert(false, "don't!");
	nativeCall();
}

template<>
inline void nativeCallTemplated()
{
	nativeCall();
}

template<>
inline int* nativeCallTemplated()
{
	return nullptr;
}

template<>
inline uint32_t* nativeCallTemplated()
{
	return nullptr;
}

template<>
inline int nativeCallTemplated()
{
	return nativeCallInt();
}

template<>
inline unsigned int nativeCallTemplated()
{
	return nativeCallInt();
}

template<>
inline char* nativeCallTemplated()
{
	return nativeCallString();
}

template<>
inline const char* nativeCallTemplated()
{
	return nativeCallString();
}

template<>
inline float nativeCallTemplated()
{
	return nativeCallFloat();
}

template<>
inline Vector3 nativeCallTemplated()
{
	float x, y, z;
	nativeCallVector3(&x, &y, &z);

	Vector3 v;
	v.x = x;
	v.y = y;
	v.z = z;

	return v;
}

struct pass
{
	template<typename ...T> pass(T...) {}
};

template <typename R, typename... Args>
static inline R invoke(UINT64 hash, Args... args)
{
	char hashString[64];
	sprintf(hashString, "%llx", hash);

	nativeInit(hashString);

	pass{ ([&] ()
	{
		nativePush(args);
	}(), 1)... };

	return nativeCallTemplated<R>();
}