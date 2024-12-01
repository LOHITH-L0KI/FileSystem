#ifndef WIN_FILE_SLOW
#define WIN_FILE_SLOW

#include "FileBase.h"

namespace Azul
{
	class WinFileSlow : public FileBase
	{

	private:
		static DWORD privExtractFileAccessType(Mode _mode);
		static DWORD privExtractMoveMethod(Position _pos);


		// Inherited via File
		Error Open(Handle& fh, const char* const fileName, Mode mode) noexcept override;
		Error Close(Handle& fh) noexcept override;
		Error Write(Handle fh, const void* const buffer, const DWORD inSize) noexcept override;
		Error Read(Handle fh, void* const _buffer, const DWORD _size) noexcept override;
		Error Seek(Handle fh, Position location, int offset) noexcept override;
		Error Tell(Handle fh, DWORD& offset) noexcept override;
		Error Flush(Handle fh) noexcept override;
		bool IsHandleValid(Handle fh) noexcept override;
	};

}


#endif // !WIN_FILE_SLOW