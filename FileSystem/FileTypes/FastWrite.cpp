#include "FastWrite.h"


Error FileSystem::FastWrite::Open(Handle& _fh, const char* const fileName, Mode mode) noexcept
{
	Error res = Error::OPEN_FAIL;

	if (!fileName)
		std::cout << "Invalid FileName Provided.\n";
	else {
		FWHandler* fh = new FWHandler();
		fh->_fstream = new std::fstream(fileName, privExtractFileAccessType(mode));
		fh->_wBuffer = new char[FastWrite::WRITE_BUFFER_SIZE];

		//clear write buff memory
		memset(fh->_wBuffer, 0x0, FastWrite::WRITE_BUFFER_SIZE);

		_fh = fh;

		if (IsHandleValid(fh)) {
			res = Error::SUCCESS;
		}
		else {
			std::cout << "Error in file open.\n";
		}
	}
	return res;
}

Error FileSystem::FastWrite::Close(Handle& _fh) noexcept
{
	Error res = Error::CLOSE_FAIL;
	FWHandler* fh = (FWHandler*)_fh;

	if (IsHandleValid(fh)) {

		//check if there is any data in the buffer
		if (fh->_fillSize > 0) {
			fh->_fstream->write(fh->_wBuffer, fh->_fillSize);
		}

		//flush anything in the stream to file
		fh->_fstream->flush();

		//close it now
		fh->_fstream->close();
		
		//check if file is closed
		if (!fh->_fstream->is_open()){
			res = Error::SUCCESS;

			//delete the handler
			delete fh;
			fh = nullptr;
		}
		else {
			std::cout << "Error in file close.\n";
		}
	}

	return res;
}

Error FileSystem::FastWrite::Write(Handle _fh, const void* const buffer, const DWORD inSize) noexcept
{
	Error res = Error::WRITE_FAIL;
	FWHandler* fh = (FWHandler*)_fh;

	if (IsHandleValid(fh)) {

		//check if buffer has enough space
		if (fh->_fillSize + inSize > FastWrite::WRITE_BUFFER_SIZE) {
			//write current buffer to file
			fh->_fstream->write(fh->_wBuffer, fh->_fillSize);
			if (fh->_fstream->fail()) {
				std::cout << "Error in writing to file.\n";
				return res;
			}
		}

		//add data to buffer
		if (memcpy_s(fh->_wBuffer + inSize, FastWrite::WRITE_BUFFER_SIZE - fh->_fillSize, buffer, inSize) == 0) {
			fh->_fillSize += inSize;
			res = Error::SUCCESS;
		}
	}

	return res;;
}

Error FileSystem::FastWrite::Read(Handle _fh, void* const _buffer, const DWORD _size) noexcept
{
	Error res = Error::READ_FAIL;
	FWHandler* fh = (FWHandler*)_fh;
	
	if (IsHandleValid(fh)) {
		long long readSize = fh->_fstream->readsome((char*)_buffer, _size);

		if (readSize < _size) {
			//read from buffer
			if (memcpy_s((char*)_buffer + _size - readSize, _size - readSize, fh->_wBuffer, fh->_fillSize) != 0) {
				std::cout << "Error in reading data from file.\n";
				return res;
			}
			res = Error::SUCCESS;
		}
	}

	return res;
}

Error FileSystem::FastWrite::Seek(Handle _fh, Position location, int offset) noexcept
{
	//do nothing
	//this is disabled
	return Error();
}

Error FileSystem::FastWrite::Tell(Handle _fh, DWORD& offset) noexcept
{
	//do nothing
	//disabled
	return Error();
}

Error FileSystem::FastWrite::Flush(Handle _fh) noexcept
{
	Error res = Error::FLUSH_FAIL;
	FWHandler* fh = (FWHandler*)_fh;

	if (this->IsHandleValid(fh)) {
		fh->_fstream->write(fh->_wBuffer, fh->_fillSize);
		fh->_fstream->flush();

		if (!fh->_fstream->fail()) {
			res = Error::SUCCESS;
		}
		else {
			std::cout << "Error in Flushing the data to file.\n";
		}

	}

	return res;
}

bool FileSystem::FastWrite::IsHandleValid(Handle _fh) noexcept
{
	bool valid = false;
	FWHandler* fh = (FWHandler*)_fh;

	if (fh && fh->_fstream)
		valid = fh->_fstream->good();

	return valid;
}

std::ios::openmode FileSystem::FastWrite::privExtractFileAccessType(Mode mode)
{
	std::ios::openmode fMode = std::ios::app;

	switch (mode)
	{
	case FileSystem::Mode::READ:
		fMode = std::ios::out;
		break;
	case FileSystem::Mode::WRITE:
		fMode = std::ios::in;
		break;
	case FileSystem::Mode::READ_WRITE:
		fMode = std::ios::in | std::ios::out;
		break;
	default:
		fMode = std::ios::app;
		break;
	}

	return fMode;
}

std::ios::seek_dir FileSystem::FastWrite::privExtractMoveMethod(Position _pos)
{
	std::ios_base::seek_dir seek = std::ios_base::cur;

	switch (_pos)
	{
	case FileSystem::Position::BEGIN:
		seek = std::ios_base::beg;
		break;
	case FileSystem::Position::CURRENT:
		seek = std::ios_base::cur;
		break;
	case FileSystem::Position::END:
		seek = std::ios_base::end;
		break;
	default:
		seek = std::ios_base::cur;
		break;
	}

	return std::ios::seek_dir();
}
