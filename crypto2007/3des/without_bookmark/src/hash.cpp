////////////////////////////////////////////////////
////////////3DES decrypt/encrypt file test 
/////////////Dmitry Kostrov 2007
/////////////////////////////////
#include "3des.h"
#include "main.h"
//////////////////////////////////////////////////////
char usage_hash[] =  "[arguments]\n\
	1:	file to make hash on\n\n\
[usage]:\n\
	to get hash from file 'file1' type:\n\
		3des file1\
\n";

FILE *_fi_h = NULL;  // input file
FILE *_fo_h = NULL;  // output file
/************************************************/
void makeHash(ulong key1, ulong key2, ulong key3, ulong hash);
//////////////////////////////////////////////
///main hash func
////////////////////////////////
int main_hash(int argc, char* argv[])
{
	if(argc < 2)
	{
		printUsage(usage_hash);
		return 0;
	}
	// 3DES keys
	ulong key1 = 4444444;  
	ulong key2 = 3333333;
	ulong key3 = 2222222;
	ulong hash    = 1234567;
	if(!openFiles(argv[1], &_fi_h, &_fo_h))
		return 0;
	makeHash(key1, key2, key3, hash);
	printf("**************************************************\n\
		  \rHash prepared. See result in '%s__res' file\n\
		  \r**************************************************\n"
			, argv[1]);
	return 1;
}
////////////////////////////////////////////////////////////
//read from file, encode end write to out file
//////////////////////
void makeHash(ulong key1, ulong key2, ulong key3, ulong hash)
{
	// prepare keys. just do it 1 time!
	prepareKeys(key1, key2, key3, true);
	uchar buff[8];
	// fill buffesr with 0's
	memset(buff, 0, 8);
	//data block(64 bit)
	ulong l = 0;
	//read cycle
	while( fread(buff, sizeof( uchar ), 8, _fi_h) > 0)
	{
		memcpy(&l, buff, 8);
		des3Decode(hash);
		hash ^= l;
		memset(buff, 0, 8);
		l = 0;
	}

	memcpy(buff, &hash, 8);
	size_t finalBlockSize = getMsgSize(buff);
	fwrite(buff,  sizeof( uchar ), finalBlockSize, _fo_h);


	fclose(_fo_h);
	fclose(_fi_h);
}