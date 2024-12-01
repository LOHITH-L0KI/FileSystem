
#ifndef FILE_BASE_H
#define FILE_BASE_H

#include "Util.h"

namespace Azul {

	class FileBase
	{
	public:
		virtual Error Open(Handle& fh, const char* const fileName, Mode mode) noexcept = 0;
		virtual Error Close(Handle& fh) noexcept = 0;
		virtual Error Write(Handle fh, const void* const buffer, const DWORD inSize) noexcept = 0;
		virtual Error Read(Handle fh, void* const _buffer, const DWORD _size) noexcept = 0;
		virtual Error Seek(Handle fh, Position location, int offset) noexcept = 0;
		virtual Error Tell(Handle fh, DWORD& offset) noexcept = 0;
		virtual Error Flush(Handle fh) noexcept = 0;
		virtual bool IsHandleValid(Handle fh) noexcept = 0;

		static FileBase* GetInstance(FileType type);
	};
}

using namespace Azul;

#endif // !FILE_BASE_H
