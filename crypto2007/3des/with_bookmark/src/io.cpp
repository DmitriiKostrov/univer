////////////////////////////////////////////////////
////////////3DES decrypt/encrypt with bookmark file input/output test 
/////////////Dmitry Kostrov 2007
/////////////////////////////////
#include "3des.h"
#include "main.h"
//////////////////////////////////////////////////////
char usage_io[] =  "[arguments]\n\
	1:	file to encrypt\n\
	2:	1st key\n\
	3:	2nd key\n\
	4:	3rd key\n\
	5:	specify wheather to decrypt(optional, any word)\n\n\
[usage]:\n\
	to encrypt file 'file1' with keys\n\
	'qwerqwer', 'asdfasdf', 'zxcvzxcv' type:\n\
		'3DES file1 qwerqwer asdfasdf zxcvzxcv'\n\
	to decrypt file 'file1' using keys\n\
	'qwerqwer', 'asdfasdf', 'zxcvzxcv' type:\n\
		'3DES file1 qwerqwer asdfasdf zxcvzxcv dec'\n\
\n";

FILE *_fi = NULL;  // input file
FILE *_fo = NULL;  // output file
/************************************************/
void readWrite(bool doDecode, ulong key1, ulong key2, ulong key3);
//////////////////////////////////////////////
///main func
////////////////////////////////
int main_io(int argc, char* argv[])
{
	if(argc != 3 && argc != 6 && argc != 5)
	{
		printUsage(usage_io);
		return 0;
	}
	bool doDecode = false;
	if(argc == 6 || argc == 3)
		doDecode = true;
	// 3DES keys
	ulong key1 = 0;  
	ulong key2 = 0;
	ulong key3 = 0;
	if(argc > 3)
	{
		memcpy(&key1, argv[2], (strlen(argv[2]) > 8) ? 8 : strlen(argv[2])) ;
		memcpy(&key2, argv[3], (strlen(argv[3]) > 8) ? 8 : strlen(argv[3]));
		memcpy(&key3, argv[4], (strlen(argv[4]) > 8) ? 8 : strlen(argv[4]));
	}
	if(!openFiles(argv[1], &_fi, &_fo))
		return 0;
	readWrite(doDecode, key1, key2, key3);
	printf("**************************************************\n\
		  \r%s succeded! See result in '%s__res' file\n\
		  \r**************************************************\n", 
			(doDecode) ? "Decode" : "Encode", argv[1]);
	return 1;
}
////////////////////////////////////////////////////////////
//read from file, encode end write to out file
//////////////////////
void readWrite(bool doDecode, ulong key1, ulong key2, ulong key3)
{
	// prepare keys. just do it 1 time!
	prepareKeys(key1, key2, key3, doDecode);
	// used 2 buffers to prevent writing unnecessary end nulls of last data block 
	uchar buff[8];
	uchar buff1[8];
	// fill buffesr with 0's
	memset(buff, 0, 8);
	memset(buff1, 0, 8);
	//data block(64 bit)
	ulong l = 0;
	//encoding block count
	ulong count = 1;
	//read cycle
	fread(buff, sizeof( uchar ), 8, _fi);
	while( fread(buff1, sizeof( uchar ), 8, _fi) > 0)
	{
		count++;
		memcpy(&l, buff, 8);
		(doDecode) ? des3Decode(l) : des3Encode(l);
		memcpy(buff, &l, 8);
		fwrite(buff,  sizeof( uchar ), 8, _fo);
		memcpy(buff, buff1, 8);
		memset(buff1, 0, 8);
		l = 0;
	}
	memcpy(&l, buff, 8);
	(doDecode) ? des3Decode(l) : des3Encode(l);
	memcpy(buff, &l, 8);
	size_t finalBlockSize = getMsgSize(buff);
	if(count == 1 && finalBlockSize == 0)
		count--;
	else
		fwrite(buff,  sizeof( uchar ), finalBlockSize, _fo);
	printf("---------------------\n\
		   \r0x%x blocks processed!\n\
		   \r----------------------\n", 
		count);
	fclose(_fo);
	fclose(_fi);
}