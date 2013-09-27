using namespace System;
using namespace System::IO;
using namespace System::IO::Compression;

namespace deflater
{
	static String^ ByteArrayToString(array<Byte>^ input)
	{
		String^ retVal = "";

		for (int i = 0; i < input->Length; i++)
		{
			retVal += input[i].ToString("X2") + " ";
		}

		return retVal;
	}

	int deflate(unsigned char* input, unsigned char*& output, int insize)
	{
		array<Byte>^ result = gcnew array<Byte>(insize);
		for (int i = 0; i < insize; i++)
			result[i] = input[i];

		MemoryStream^ stream = gcnew MemoryStream;

		DeflateStream^ compressor = gcnew DeflateStream(stream, CompressionMode::Compress, true);

		compressor->Write(result, 0, insize);
		delete [] result;
		compressor->Close();

		stream->Position = 0;
		array<Byte>^ tmpout = gcnew array<Byte>(stream->Length);
		stream->Read(tmpout, 0, stream->Length);

		output = new unsigned char[stream->Length + 1];
		for (int i = 0; i < stream->Length; i++)
			output[i] = tmpout[i];
		output[stream->Length] = '\0';
		delete [] tmpout;

		return stream->Length;
	}

	void inflate(unsigned char* input, unsigned char* output, int insize, int outsize)
	{
		array<Byte>^ result = gcnew array<Byte>(insize);
		for (int i = 0; i < insize; i++)
			result[i] = input[i];

		MemoryStream^ stream = gcnew MemoryStream(result);
		delete [] result;

		stream->Position = 0;
		DeflateStream^ compressor = gcnew DeflateStream(stream, CompressionMode::Decompress);

		array<Byte>^ tmpout = gcnew array<Byte>(outsize);
		compressor->Read(tmpout, 0, outsize);
		compressor->Close();

		for (int i = 0; i < outsize; i++)
			output[i] = tmpout[i];
		delete [] tmpout;
	}
}

__declspec(dllexport) int __cdecl deflate(unsigned char* in, unsigned char*& out, int insize)
{
	return deflater::deflate(in, out, insize);
}

__declspec(dllexport) void __cdecl inflate(unsigned char* in, unsigned char* out, int insize, int outsize)
{
	deflater::inflate(in, out, insize, outsize);
}