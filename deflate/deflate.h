#ifndef deflate_h
#define deflate_h

int __cdecl deflate(unsigned char* in, unsigned char*& out, int insize);
void __cdecl inflate(unsigned char* in, unsigned char* out, int insize, int outsize);

#endif