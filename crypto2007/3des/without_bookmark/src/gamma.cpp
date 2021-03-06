////////////////////////////////////////////////////
////////////3DES decrypt/encrypt file test 
/////////////Dmitry Kostrov 2007
/////////////////////////////////
#include "3des.h"
#include "main.h"
//////////////////////////////////////////////////////
char usage_gamma[] =  "[arguments]\n\
	1:	file to crypt\n\
	2:	1st key\n\
	3:	2nd key\n\
	4:	3rd key\n\n\
[usage]:\n\
	to crypt file 'file1' with keys\n\
	'qwerqwer', 'asdfasdf', 'zxcvzxcv' type:\n\
		'3DES file1 qwerqwer asdfasdf zxcvzxcv'\n\
\n";

FILE *_fi_g = NULL;  // input file
FILE *_fo_g = NULL;  // output file
ulong _H0 = 0x10;  // initial gamma value
/************************************************/
void readWrite_gamma(ulong key1, ulong key2, ulong key3);
//////////////////////////////////////////////
///main func
////////////////////////////////
int main_gamma(int argc, char* argv[])
{
	//return test_gamma();
	if(argc < 5)
	{
		printUsage(usage_gamma);
		return 0;
	}
	// 3DES keys
	ulong key1 = 0;  
	ulong key2 = 0;
	ulong key3 = 0;
	memcpy(&key1, argv[2], (strlen(argv[2]) > 8) ? 8 : strlen(argv[2])) ;
	memcpy(&key2, argv[3], (strlen(argv[3]) > 8) ? 8 : strlen(argv[3]));
	memcpy(&key3, argv[4], (strlen(argv[4]) > 8) ? 8 : strlen(argv[4]));
	if(!openFiles(argv[1], &_fi_g, &_fo_g))
		return 0;
	readWrite_gamma(key1, key2, key3);
	printf("**************************************************\n\
		  \rCrypt succeded! See result in '%s__res' file\n\
		  \r**************************************************\n", 
		  argv[1]);
	return 1;
}
////////////////////////////////////////////////////////////
//read from file, encode end write to out file
//////////////////////
void readWrite_gamma(ulong key1, ulong key2, ulong key3)
{
	// prepare keys. just do it 1 time!
	prepareKeys(key1, key2, key3, false);
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
	fread(buff, sizeof( uchar ), 8, _fi_g);
	ulong Hi = _H0;
	while( fread(buff1, sizeof( uchar ), 8, _fi_g) > 0)
	{
		count++;
		memcpy(&l, buff, 8);
		crypt_gamma(Hi, l);
		memcpy(buff, &l, 8);
		fwrite(buff,  sizeof( uchar ), 8, _fo_g);
		memcpy(buff, buff1, 8);
		memset(buff1, 0, 8);
		l = 0;
	}
	memcpy(&l, buff, 8);
	crypt_gamma(Hi, l);
	memcpy(buff, &l, 8);
	size_t finalBlockSize = getMsgSize(buff);
	if(count == 1 && finalBlockSize == 0)
		count--;
	else
		fwrite(buff,  sizeof( uchar ), finalBlockSize, _fo_g);
	printf("---------------------\n\
		   \r0x%x blocks processed!\n\
		   \r----------------------\n", 
		count);
	fclose(_fo_g);
	fclose(_fi_g);
}