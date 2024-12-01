#ifndef FAST_WRITER
#define FAST_WRITER

#include <fstream>
#include "FileBase.h"

namespace Azul {

	struct FWHandler
	{
		std::fstream* _fstream;
		char* _wBuffer;
		size_t _fillSize;

		FWHandler(){
			_fstream = nullptr;
			_wBuffer = nullptr;
			_fillSize = 0;
		}

		~FWHandler() {
			delete[] _wBuffer;
			delete _fstream;
		}
	};

	class FastWrite : public FileBase
	{
	private:
		static const size_t WRITE_BUFFER_SIZE = 1024 * 1024; // 1Mb

	private:
		// Inherited via FileBase
		Error Open(Handle& fh, const char* const fileName, Mode mode) noexcept override;
		Error Close(Handle& fh) noexcept override;
		Error Write(Handle fh, const void* const buffer, const DWORD inSize) noexcept override;
		Error Read(Handle fh, void* const _buffer, const DWORD _size) noexcept override;
		Error Seek(Handle fh, Position location, int offset) noexcept override;
		Error Tell(Handle fh, DWORD& offset) noexcept override;
		Error Flush(Handle fh) noexcept override;
		bool IsHandleValid(Handle fh) noexcept override;

		std::ios::openmode privExtractFileAccessType(Mode mode);
		std::ios::seek_dir privExtractMoveMethod(Position _pos);
	};
}

#endif //!FAST_WRITER