#include "File.h"

using namespace Azul;

//default initialization
FileBase* File::fBase = FileBase::GetInstance(FileType::DEFAULT);

bool File::IsHandleValid(Handle fh) noexcept
{
	return File::fBase->IsHandleValid(fh);
}

bool File::SetInstnace(FileType type)
{
	bool success = false;

	if (!File::fBase) {
		File::fBase = FileBase::GetInstance(type);
		success = true;
	}

	return success;
}

Error File::Open(Handle& fh, const char* const fileName, Mode mode) noexcept
{
	return File::fBase->Open(fh, fileName, mode);
}

Error File::Close(Handle &fh) noexcept
{
	return File::fBase->Close(fh);
}

Error File::Write(Handle fh, const void* const buffer, const DWORD inSize) noexcept
{
	return File::fBase->Write(fh, buffer, inSize);
}

Error File::Read(Handle fh, void* const buffer, const DWORD inSize) noexcept
{
	return File::fBase->Read(fh, buffer, inSize);
}

Error File::Seek(Handle fh, Position location, int offset) noexcept
{
	return File::fBase->Seek(fh, location, offset);
}

Error File::Tell(Handle fh, DWORD& offset) noexcept
{
	return File::fBase->Tell(fh, offset);
}

Error File::Flush(Handle fh) noexcept
{
	return File::fBase->Flush(fh);
}

// --- End of File ---
