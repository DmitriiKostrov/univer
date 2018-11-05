#include "stdio.h"
#include "string.h"
#include "malloc.h"
#include "3des.h"

#undef IO_TEST
#define GEN_ASM

#define RESULT_FILE_NAME_APPEND "__res"

void printUsage(const char* usage);
size_t getMsgSize(uchar* buff);
bool openFiles(const char *fName, FILE **fi, FILE **fo);
void crypt_gamma(ulong &Hi, ulong &l);

int main_io(int argc, char* argv[]);
int main_gen_asm();
int main_auto(int argc, char* argv[]);
//void devideDataBlock(ulong *ll, ulong *rl, ulong *l, uchar stepNum);//remove this later
//void prepareDataBlock(ulong *ll, ulong *rl, ulong *l, uchar stepNum);//and this!