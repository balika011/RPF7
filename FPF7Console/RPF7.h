#ifndef RPF7_H
#define RPF7_H

#pragma pack(push, 1)
struct RPF7Header
{
	char magic[4];
	int entries;
	int infos;
	int flags;
};

struct RPF7Entry //size: 16
{
	byte offset_part0;
	byte offset_part1;
	byte offset_part2;

	byte compressedsize_part0;
	byte compressedsize_part1;
	byte compressedsize_part2;

	short nameoffset;

	int subindex_or_systemFlag_or_uncompressedSize;
	int subcount_or_graphicsFlag_or_isEncrypted;
};
#pragma pack(pop)

class RPF7HeaderTools
{
private:
	RPF7Header* header;
public:
	RPF7HeaderTools(RPF7Header* header) : header(header) {}
	RPF7HeaderTools(void* buffer) : header((RPF7Header*) buffer) {}
	~RPF7HeaderTools() {}

	char* getMagic() { return header->magic; }
	void setMagic(char* magic) { memcpy(header->magic, magic, 4); }

	int getEntriesCount() { return _byteswap_ulong(header->entries); }
	void setEntriesCount(int count) { header->entries = _byteswap_ulong(count); }

	byte getPlatform() { return (_byteswap_ulong(header->infos) >> 31) & 1; }
	void setPlatform(byte platform) { header->infos |= _byteswap_ulong((platform & 1) << 31); }

	byte getFilenamesShift() { return (_byteswap_ulong(header->infos) >> 28) & 7; }
	void setFilenamesShift(byte shift) { header->infos |= _byteswap_ulong((shift & 7) << 28); }

	int getFilenamesLength() { return _byteswap_ulong(header->infos) & 0x0FFFFFFF; }
	void setFilenamesLength(int length) { header->infos |= _byteswap_ulong(length & 0x0FFFFFFF); }

	int getFlags() { return _byteswap_ulong(header->flags); }
	void setFlags(int flags) { header->flags = _byteswap_ulong(flags); }
};

class RPF7EntryTools
{
private:
	RPF7Entry* entry;
public:
	RPF7EntryTools(RPF7Entry* entry) : entry(entry) {}
	RPF7EntryTools(void* buffer) : entry((RPF7Entry*) buffer) {}
	~RPF7EntryTools() {}

	int getOffset()
	{
		int tmp = entry->offset_part0 << 16;
		tmp |= entry->offset_part1 << 8;
		tmp |= entry->offset_part2;

		return tmp & 0x7FFFFF;
	}
	void setOffset(int offset)
	{
		bool tmp = isResource();
		offset = offset & 0x7FFFFF;
		entry->offset_part0 = (offset >> 16) & 0xFF;
		entry->offset_part1 = (offset >> 8) & 0xFF;
		entry->offset_part2 = offset & 0xFF;
		setIsResource(tmp);
	}

	bool isResource() { return (entry->offset_part0 >> 7) & 1; }
	void setIsResource(bool is) { entry->offset_part0 |= (is & 1) << 7; }

	int getCompressedSize()
	{
		int tmp = entry->compressedsize_part0 << 16;
		tmp |= entry->compressedsize_part1 << 8;
		tmp |= entry->compressedsize_part2;

		return tmp;
	}
	void setCompressedSize(int size)
	{
		entry->compressedsize_part0 = (size >> 16) & 0xFF;
		entry->compressedsize_part1 = (size >> 8) & 0xFF;
		entry->compressedsize_part2 = size & 0xFF;
	}

	int getFilenameOffset() { return _byteswap_ushort(entry->nameoffset); }
	void setFilenameOffset(int offset) { entry->nameoffset = _byteswap_ushort((short)offset); }

	int getSubentriesStartIndex() { return _byteswap_ulong(entry->subindex_or_systemFlag_or_uncompressedSize); }
	void setSubentriesStartIndex(int index) { entry->subindex_or_systemFlag_or_uncompressedSize = _byteswap_ulong(index); }

	int getSubentriesCount() { return _byteswap_ulong(entry->subcount_or_graphicsFlag_or_isEncrypted); }
	void setSubentriesCount(int count) { entry->subcount_or_graphicsFlag_or_isEncrypted = _byteswap_ulong(count); }

	int getUncompressedSize() { return _byteswap_ulong(entry->subindex_or_systemFlag_or_uncompressedSize); }
	void setUncompressedSize(int size) { entry->subindex_or_systemFlag_or_uncompressedSize = _byteswap_ulong(size); }

	bool isEncrypted() { return _byteswap_ulong(entry->subcount_or_graphicsFlag_or_isEncrypted) == 1; }
	void setIsEncrypted(bool is) { entry->subcount_or_graphicsFlag_or_isEncrypted = _byteswap_ulong(is); }
};
#endif //RPF7_H