#include "FileBase.h"
#include "WinFileSlow.h"
#include "FastWrite.h"

FileBase* FileSystem::FileBase::GetInstance(FileType type)
{
	FileBase* fb = nullptr;

	switch (type)
	{
	case FileType::WIN_SLOW:
		fb = new WinFileSlow();
		break;
	case FileType::FAST_WRITE:
		fb = new FastWrite();
	default:
		std::cout << "Select a File Reader Type.\n";
		assert(false);
		break;
	}

	return fb;
}
