#include "B4RDefines.h"

namespace B4R {
	B4RSD::B4RSD(){
		stream.wrappedStream = &b4rfile.file;
	}
	bool B4RSD::Initialize(Byte CSPin) {
		return SD.begin(CSPin);
	}
#if ESP32
	bool B4RSD::open(B4RString* FileName, const char* mode) {
#else
	bool B4RSD::open(B4RString* FileName, Byte mode) {
#endif
		b4rfile.file.close();
		b4rfile.file = SD.open(FileName->data, mode);
		if (b4rfile.file == true) {
			b4rfile.file.seek(0);
			return true;
		}
		return false;
			
	}
	bool B4RSD::OpenRead(B4RString* FileName) {
		return open(FileName, FILE_READ);
	}
	bool B4RSD::OpenReadWrite (B4RString* FileName) {
		return open(FileName, FILE_WRITE);
	}
	B4RStream* B4RSD::getStream() {
		return &stream;
	}
	ULong B4RSD::getPosition() {
		return b4rfile.file.position();
	}
	void B4RSD::setPosition(ULong p) {
		b4rfile.file.seek(p);
	}
	
	B4RFile* B4RSD::getCurrentFile() {
		return &b4rfile;
	}
	void B4RSD::Close() {
		return b4rfile.file.close();
	}
	bool B4RSD::Exists(B4RString* FileName) {
		return SD.exists(FileName->data);
	}
	bool B4RSD::Remove (B4RString* FileName) {
		return SD.remove(FileName->data);
	}
	
	FileIterator* B4RSD::ListFiles(B4RString* DirName) {
		FileIterator* it = CreateStackMemoryObject (FileIterator);
		it->dir = SD.open(DirName->data, FILE_READ);
		it->dir.rewindDirectory();
		it->current = new (it->backend) B4RFile();
		it->o.wrapPointer(it->current);
		return it;
	}
	ULong B4RFile::getSize() {
		return file.size();
	}
	bool B4RFile::getIsDirectory() {
		if (!file)
			return false;
		return file.isDirectory();
	}
	B4RString* B4RFile::getName() {
		stringBackend.wrap(file.name());
		return &stringBackend;
	}
	
	bool FileIterator::MoveNext() {
		current->file.close();
		current->file = dir.openNextFile(FILE_READ);
		if (current->file == false) {
			dir.close();
			return false;
		}
		return true;
	}
	Object* FileIterator::Get() {
		return &o;
	}
}