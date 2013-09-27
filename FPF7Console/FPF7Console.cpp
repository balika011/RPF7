#include <Windows.h>
#include <stdio.h>
#include <AES.h>
#include <lzx.h>
#include <deflate.h>

#include "RPF7.h"
#include "CString.h"
#include "platforms.h"

#define IS_XBOX360 1
#define IS_PS3 0

FILE* file;
platforms* platform;

unsigned char* read(int offset, int size)
{
	fseek(file, offset, SEEK_SET);

	unsigned char* buffer = new unsigned char[size];
	if (buffer == NULL)
		return 0;

	if (fread(buffer, 1, size, file) != size)
		return 0;

	return buffer;
}

void listEntry(char* path, FILE* file, unsigned char* entries, RPF7HeaderTools* header, RPF7EntryTools* entry)
{
	fprintf(file, "offset: %X\n", entry->getOffset());

	fprintf(file, "resource: %s\n", entry->isResource() ? "true" : "false");

	fprintf(file, "compressedSize: %i\n", entry->getCompressedSize());

	fprintf(file, "filenameOffset: %X\n", entry->getFilenameOffset() << header->getFilenamesShift());
	
	fprintf(file, "filename: %s\\%s\n", path, entries + header->getEntriesCount() * sizeof(RPF7Entry) +(entry->getFilenameOffset() << header->getFilenamesShift()));

	if (entry->getOffset() == 0x7FFFFF)
	{
		if (entry->isResource())
		{
			printf("WTF?!\n");
			return;
		}

		CreateDirectory((char*) CString("%s\\%s", path, entries + header->getEntriesCount() * sizeof(RPF7Entry) +(entry->getFilenameOffset() << header->getFilenamesShift())).Get(), NULL);

		for (int i = 0; i < entry->getSubentriesCount(); ++i)
			listEntry((char*) CString("%s\\%s", path, entries + header->getEntriesCount() * sizeof(RPF7Entry) +(entry->getFilenameOffset() << header->getFilenamesShift())).Get(), file, entries, header, new RPF7EntryTools(entries + (entry->getSubentriesStartIndex() + i) * sizeof(RPF7Entry)));
	}
	else if (entry->isResource())
	{
		printf("!!! resource !!! - %s\n", CString("%s\\%s", path, entries + header->getEntriesCount() * sizeof(RPF7Entry) +(entry->getFilenameOffset() << header->getFilenamesShift())).Get());
	}
	else
	{
		if (entry->getCompressedSize() == 0)
		{
			if (entry->isEncrypted())
			{
				printf("WTF?!\n");
				return;
			}
			fprintf(file, "uncompressedSize: %i\n", entry->getUncompressedSize());
			fprintf(file, "isEncrypted: %s\n", entry->isEncrypted() ? "true" : "false");

			FILE* out;
			fopen_s(&out, (char*) CString("%s\\%s", path, entries + header->getEntriesCount() * sizeof(RPF7Entry) +(entry->getFilenameOffset() << header->getFilenamesShift())).Get(), "wb");

			fwrite(read(entry->getOffset() << 9, entry->getUncompressedSize()), 1, entry->getUncompressedSize(), out);

			fclose(out);

		}
		else
		{
			fprintf(file, "uncompressedSize: %i\n", entry->getUncompressedSize());
			fprintf(file, "isEncrypted: %s\n", entry->isEncrypted() ? "true" : "false");

			unsigned char* filebuffer = read(entry->getOffset() << 9, entry->getCompressedSize());

			if (entry->isEncrypted())
			{
				AESContext context;
				AesSetKey(&context, platform->getAESkey());
				AesDecrypt(&context,
				filebuffer,
				filebuffer,
				entry->getCompressedSize());
			}

			FILE* out;
			fopen_s(&out, (char*) CString("%s\\%s", path, entries + header->getEntriesCount() * sizeof(RPF7Entry) +(entry->getFilenameOffset() << header->getFilenamesShift())).Get(), "wb");

			unsigned char* outbuffer = new unsigned char[entry->getUncompressedSize()];

			platform->decompressBuffer(filebuffer, outbuffer, entry->getCompressedSize(), entry->getUncompressedSize());

			fwrite(outbuffer, 1, entry->getUncompressedSize(), out);

			fclose(out);

			delete [] filebuffer;
		}
	}

	delete entry;
}

int main(int argc, char* argv[])
{
#if IS_XBOX360
	platform = new xbox360();
	fopen_s(&file, "C:\\Users\\Home\\Desktop\\GTA V XBOX360\\disc1\\common.rpf", "rb");
#elif IS_PS3
	platform = new ps3();
	fopen_s(&file, "C:\\Users\\Home\\Downloads\\Grand.Theft.Auto.V.PS3-DUPLEX\\BLES01807-[Grand Theft Auto V]\\PS3_GAME\\USRDIR\\audio_rel.rpf", "rb");
#else
#error NOT SUPPORTED!!!
#endif
	if (file == NULL)
		goto exit;

	RPF7HeaderTools* header = new RPF7HeaderTools(read(0, sizeof(RPF7Header)));

	if (strcmp(header->getMagic(), "RPF7") != 0)
	{
		printf("This file in not RPF7!\n");
		goto exit;
	}

	unsigned char* entries = read(sizeof(RPF7Header), header->getEntriesCount() * sizeof(RPF7Entry) +header->getFilenamesLength());

	AESContext context;
	AesSetKey(&context, platform->getAESkey());
	AesDecrypt(&context, entries, entries, header->getEntriesCount() * sizeof(RPF7Entry) + header->getFilenamesLength());

	FILE* out;
	fopen_s(&out, "list.txt", "w");
	listEntry("dump", out, entries, header, new RPF7EntryTools(entries));
	fclose(out);

	fclose(file);
exit:
	system("pause");
	return 0;
}