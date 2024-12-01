#include "WinFileSlow.h"
#include <fileapi.h>


Error FileSystem::WinFileSlow::Open(Handle& fh, const char* const fileName, Mode mode) noexcept
{
    Error res = Error::OPEN_FAIL;

    if (fileName == nullptr)
    {
        std::cout << "WinFileSlow::Open:: Invalide fileName.\n";
    }
    else
    {
        DWORD accessType = this->privExtractFileAccessType(mode);
        fh = CreateFile(fileName, accessType, 0, NULL, OPEN_ALWAYS, 0, NULL);
        
        if (IsHandleValid(fh) == false)
        {
            std::cout << "WinFileSlow::Open:: Error in Handle Creation, Error CODE: " << GetLastError() << "./n";
        }
        else
        {
            res = Error::SUCCESS;
        }
    }

    return res;
}

Error FileSystem::WinFileSlow::Close(Handle& fh) noexcept{
    Error res = Error::CLOSE_FAIL;

    if (IsHandleValid(fh) == false)
    {
        std::cout << ("WinFileSlow::Close:: Invalide Handle.\n");
    }
    else
    {
        if (CloseHandle(fh))
        {
            res = Error::SUCCESS;
            fh = INVALID_HANDLE_VALUE;
        }
        else
        {
            std::cout << "WinFileSlow::Close:: Error in Closing Handle, Error CODE: " << GetLastError() << "./n";
        }
    }

    return res;
}

Error FileSystem::WinFileSlow::Read(Handle handle, void* const buffer, const DWORD inSize) noexcept
{
    Error res = Error::READ_FAIL;

    if (IsHandleValid(handle) == false)
    {
        std::cout << ("WinFileSlow::Read:: Invalide Handle.\n");
    }
    else
    {
        DWORD bytesRead = 0;

        if (ReadFile(handle, (LPDWORD)buffer, inSize, &bytesRead, NULL))
        {
            res = Error::SUCCESS;
        }
        else
        {
            std::cout << ("WinFileSlow::Read:: Error in Reading File, Error CODE: ")  << GetLastError() << "./n";
        }
    }

    return res;
}

Error FileSystem::WinFileSlow::Write(Handle handle, const void* const buffer, const DWORD inSize) noexcept
{
    Error res = Error::WRITE_FAIL;
    
    if (IsHandleValid(handle) == false)
    {
        std::cout << ("WinFileSlow::Write:: Invalide Handle.\n");
    }
    else
    {
        DWORD bytesWritten = 0;
        if (WriteFile(handle, buffer, inSize, &bytesWritten, NULL))
        {
            res = Error::SUCCESS;
        }
        else
        {
            std::cout << ("WinFileSlow::Write:: Error in Writing to File, Error CODE: ") << GetLastError() << "./n";
        }
    }
    return res;
}

Error FileSystem::WinFileSlow::Seek(Handle handle, Position location, int offset) noexcept
{
    Error res = Error::SEEK_FAIL;

    if (IsHandleValid(handle) == false)
    {
        std::cout << ("WinFileSlow::Seek:: Invalide Handle.\n");
    }
    else
    {
        DWORD moveMethod = WinFileSlow::privExtractMoveMethod(location);
        if (INVALID_SET_FILE_POINTER == SetFilePointer(handle, offset, NULL, moveMethod))
        {
            std::cout << ("WinFileSlow::Seek:: Error in Seeking position in file, Error CODE: ") << GetLastError() << "./n";
        }
        else
        {
            res = Error::SUCCESS;
        }

    }

    return res;
}

Error FileSystem::WinFileSlow::Tell(Handle handle, DWORD& offset) noexcept
{
    Error res = Error::TELL_FAIL;
    if (IsHandleValid(handle) == false)
    {
        std::cout << ("WinFileSlow::Tell:: Invalide Handle.\n");
    }
    else
    {
        int shiftBy = 0;    // this is set to 0 so that the handler dosen't 
                            //shift its position and we get the current position of the file.
        if (INVALID_SET_FILE_POINTER == (offset = SetFilePointer(handle, shiftBy, NULL, FILE_CURRENT)))
        {
            std::cout << ("WinFileSlow::Tell:: Error in Fetching position in file, Error CODE: ") << GetLastError() << ".\n";
        }
        else
        {
            res = Error::SUCCESS;
        }
    }

    return res;
}

Error FileSystem::WinFileSlow::Flush(Handle handle) noexcept
{
    Error res = Error::FLUSH_FAIL;
    if (IsHandleValid(handle) == false)
    {
        std::cout << ("WinFileSlow::Flush:: Invalide Handle.\n");
    }
    else
    {
        if (FlushFileBuffers(handle) == 0)
        {
            std::cout << ("WinFileSlow::Flush:: Error in Flushing file buffers, Error CODE: ") << GetLastError() << "./n";
        }
        else
        {
            res = Error::SUCCESS;
        }
    }
    return res;
}

bool FileSystem::WinFileSlow::IsHandleValid(Handle handle) noexcept
{
    bool res = true;
    DWORD flags;
    if ((handle == INVALID_HANDLE_VALUE) || GetHandleInformation(handle, &flags) == false)
    { 
        res = false;
        std::cout << ("proIsHandleValid:: Invalid Handle.\n");
    }

    return res;
}

DWORD WinFileSlow::privExtractFileAccessType(Mode _mode)
{
    DWORD accessMode = 0;

    switch (_mode)
    {
    case Mode::READ:
    {
        accessMode = GENERIC_READ;
        break;
    }
    case Mode::WRITE:
    {
        accessMode = GENERIC_WRITE;
        break;
    }
    case Mode::READ_WRITE:
    {
        accessMode = GENERIC_READ | GENERIC_WRITE;
        break;
    }
    default:
        std::cout << ("Invalid Access Mode Sent.\n");
    }

    return accessMode;
}

DWORD WinFileSlow::privExtractMoveMethod(Position _pos)
{
    DWORD moveMethod = 0;

    switch (_pos)
    {
    case Position::BEGIN:
    {
        moveMethod = FILE_BEGIN;
        break;
    }
    case Position::CURRENT:
    {
        moveMethod = FILE_CURRENT;
        break;
    }
    case Position::END:
    {
        moveMethod = FILE_END;
        break;
    }
    default:
        std::cout << ("Invalid Position Sent.\n");
    }

    return moveMethod;
}