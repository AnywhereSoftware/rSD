#pragma once
#include "B4RDefines.h"
//~dependson: <SPI.h>
//~dependson: <SD.h>
namespace B4R {
	//~Version: 1.03
	//~shortname: File
	class B4RFile {
		private:
			B4RString stringBackend;
		public:
			//~hide
			File file;
			//Returns the file size (number of bytes).
			ULong getSize();
			//Returns true if this file entry is a directory.
			bool getIsDirectory();
			//Returns the file name.
			B4RString* getName();
	};
	//~hide
	class FileIterator : public Iterator{
		public:
			Object o;
			B4RFile* current;
			uint8_t backend[sizeof(B4RFile)];
			File dir;
			virtual bool MoveNext() override;
			virtual Object* Get() override;
						
	};
	
	
	//~shortname: SD
	class B4RSD {
		private:
			B4RFile b4rfile;
			B4RStream stream;
			bool open(B4RString* FileName, Int mode);
		public:
			//~hide
			B4RSD();
			/**
			*Initializes the SD card. Returns true if the sd card was successfully initialized.
			*CSPin - Pin connected to the chip select line of the sd card.
			*/
			bool Initialize(Byte CSPin);
			//Opens a file in read only mode. Returns true if the file was opened successfully.
			bool OpenRead (B4RString* FileName);
			//Opens a file in read and write mode. Returns true if the file was opened successfully.
			bool OpenReadWrite (B4RString* FileName);
			/**
			*Can be used in a For Each loop to iterate over the files in the folder.
			*Example:<code>
			 *For Each f As File In sd.ListFiles("/")
			 *	Log("Name: ", f.Name, ", Size: ", f.Size)
			 *Next</code>
			*/
			FileIterator* ListFiles(B4RString* DirName);
			//Returns the current open file.
			B4RFile* getCurrentFile();
			//Returns the stream of the current open file.
			B4RStream* getStream();
			//Gets or sets the position in the current open file.
			ULong getPosition();
			void setPosition(ULong p);
			//Closes the current open file.
			void Close();
			//Checks whether the given file or directory exist.
			bool Exists(B4RString* FileName);
			//Deletes the given file. Returns true if the file was successfully deleted.
			bool Remove(B4RString* FileName);
		
	};
	
}