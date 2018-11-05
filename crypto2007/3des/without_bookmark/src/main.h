#include "stdio.h"
#include "string.h"
#include "malloc.h"
#include "3des.h"

#define IO_TEST
#undef HASH_TEST
#undef GAMMA_TEST
#undef SERVER_TEST
#undef CLIENT_TEST

#define RESULT_FILE_NAME_APPEND "__res"

void printUsage(const char* usage);
size_t getMsgSize(uchar* buff);
bool openFiles(const char *fName, FILE **fi, FILE **fo);
void crypt_gamma(ulong &Hi, ulong &l);

int main_io(int argc, char* argv[]);
int main_hash(int argc, char* argv[]);
int main_gamma(int argc, char* argv[]);
int main_server(int argc, char* argv[]);
int main_client(int argc, char* argv[]);
