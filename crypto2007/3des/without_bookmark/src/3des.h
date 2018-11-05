//////////3DES.h
///////created 4.12.2007 by Dmitry Kostrov
///////////////////////////////////////////////////
#ifndef DES3_H_
#define DES3_H_

typedef unsigned long long ulong;
typedef unsigned char uchar;

void des3Encode(ulong &l);
void des3Decode(ulong &l);
void prepareKeys(ulong _key1, ulong _key2, ulong _key3, bool doDecode);

#endif // DES3_H