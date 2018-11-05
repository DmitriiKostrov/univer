/*****************************************************************************
****constants.cpp
****3des constants definition
****created by Dmitry Kostrov
*************************************************************************/
#include "main.h"
/*************************************************************************
**************************************************************************/
//////////////////////////////////////////////////////
//just prints application usage output
///////////////////////////////////////////
void printUsage(const char* usage)
{
	printf(usage);
}
////////////////////////////
//get real last msg size(to prevent end NULLS)
//////////////
size_t getMsgSize(uchar* buff)
{
	int size = 0;
	for(int i = 7; i > -1; i--)
	{
		if(buff[i] != 0)
			break;;
		size++;
	}
	return 8 - size;
}
///////////////////////////////////////////////
//opens intout and output files
//returns: TRUE - success; FALSE otherwise
////////////////////////////////////////
bool openFiles(const char* fName, FILE **fi, FILE **fo)
{
	fopen_s(fi, fName, "r+b");
	if(*fi == NULL)
	{	
		printf("failed to open file '%s'\n", fName);
		return 0;
	}
	size_t foSize = strlen(fName) + strlen(RESULT_FILE_NAME_APPEND) + 1; 
	char *foName = (char*)malloc(foSize);
	strcpy_s(foName, foSize, fName);
	strcat_s(foName, foSize, RESULT_FILE_NAME_APPEND);
	fopen_s(fo, foName, "w+b");
	if(*fo == NULL)
	{	
		printf("failed to open file '%s'\n", foName);
		return 0;
	}
	return 1;
}
/////////////////////////////////////////
////main func
////////////////////
int main(int argc, char* argv[])
{
#ifdef IO_TEST
	return main_io(argc, argv);
#endif

#ifdef GEN_ASM
	return main_gen_asm();
#endif

#ifdef BOOKMARK_TEST
	return main_auto(argc, argv);
#endif
}