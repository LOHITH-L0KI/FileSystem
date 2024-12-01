#ifndef UTIL_H
#define UTIL_H

#include <Windows.h>
#include <cstdint>
#include <iostream>
#include <assert.h>

namespace FileSystem {

	typedef void* Handle;

	enum class Mode : uint32_t
	{
		READ,
		WRITE,
		READ_WRITE
	};

	enum class Position : uint32_t
	{
		BEGIN,
		CURRENT,
		END
	};

	enum class Error : uint32_t
	{
		SUCCESS,
		OPEN_FAIL,
		CLOSE_FAIL,
		WRITE_FAIL,
		READ_FAIL,
		SEEK_FAIL,
		TELL_FAIL,
		FLUSH_FAIL,
		UNDEFINED
	};

	enum class FileType : uint32_t
	{
		WIN_SLOW,
		FAST_WRITE,
		DEFAULT = WIN_SLOW
	};
}

#endif // !UTIL_H
