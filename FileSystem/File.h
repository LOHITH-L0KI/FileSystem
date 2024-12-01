#ifndef FILE_H
#define FILE_H

#include "FileBase.h"

namespace FileSystem
{

	class File
	{
	
	private:
		static FileBase* fBase;

	public:

		// Constants for the library
		static const uint32_t MAJOR_VERSION = 3;
		static const uint32_t MINOR_VERSION = 1;

	public:
		static Error Open(Handle& fh, const char* const fileName, Mode mode) noexcept;
		static Error Close(Handle& fh) noexcept;
		static Error Write(Handle fh, const void* const buffer, const DWORD inSize) noexcept;
		static Error Read(Handle fh, void* const _buffer, const DWORD _size) noexcept;
		static Error Seek(Handle fh, Position location, int offset) noexcept;
		static Error Tell(Handle fh, DWORD& offset) noexcept;
		static Error Flush(Handle fh) noexcept;
		static bool IsHandleValid(Handle fh) noexcept;
		static bool SetInstnace(FileType type);
		
	};
}

using namespace FileSystem;
#endif

// --- End of File ---
