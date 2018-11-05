#include "stdio.h"
#include "string.h"
#include "malloc.h"
#include <fstream>

using namespace std;
//numbers after code - layer number! (8 max)
#ifdef BOOKMARK_TEST
const char *code0   = 
						"\tjmp0:\
						\r\t\tmov esi, offset init\
						\r\t\tadd esi, 5\
						\r\t\tmov edi, esi\
						\r\t\tadd edi, 9f6h\
						\r\t\tmov eax, ll\
						\r\t\tmov [eax], 0\
						\r\t\tmov edx, l\
						\r\t\tmov  _buff[0], 1\
						\r\t\tmov bl, byte ptr [edx]\
						\r\t\tmov  [eax], bl\
						\r\t\txor ecx, ecx\
						\r\t\tmov cl, stepNum\
						\r\t\tpush ecx\
						\r\t\ttest [edx], 10000000b\
						\r\t\tjnz _0\
						\r\t\tadd esi,5\
						\r\t\t_0:\
						\r\t\t\tjmp esi\n"; 
						
const char *code1_25_6 = 	"\tjmp%d:\
						\r\t\tadd esi, %d\
						\r\t\tinc edx\
						\r\t\tinc eax\
						\r\t\tmov  _buff[%d], 1\
						\r\t\tmov bl, byte ptr [edx]\
						\r\t\tmov  [eax], bl\
						\r\t\ttest [edx], 10000000b\
						\r\t\tjnz _%d\
						\r\t\tadd esi,5\
						\r\t\t_%d:\
						\r\t\t\tjmp esi\n";
						
const char *code3 = 	"\tjmp%d:\
						\r\t\tadd esi, %d\
						\r\t\tinc edx\
						\r\t\tinc eax\
						\r\t\tmov  _buff[%d], 1\
						\r\t\tmov ecx, _lk\
						\r\t\tpush ecx\
						\r\t\tmov bl, byte ptr [edx]\
						\r\t\tmov  [eax], bl\
						\r\t\tmov  eax, rl\
						\r\t\tmov [eax], 0\
						\r\t\ttest [edx], 10000000b\
						\r\t\tjnz _%d\
						\r\t\tadd esi,5\
						\r\t\t_%d:\
						\r\t\t\tjmp esi\n";
						
const char *code4 = 	"\tjmp%d:\
						\r\t\tadd esi, %d\
						\r\t\tinc edx\
						\r\t\tmov  _buff[%d], 1\
						\r\t\txor ecx, ecx\
						\r\t\tpush ecx\
						\r\t\tmov bl, byte ptr [edx]\
						\r\t\tmov  [eax], bl\
						\r\t\ttest [edx], 10000000b\
						\r\t\tjnz _%d\
						\r\t\tadd esi,5\
						\r\t\t_%d:\
						\r\t\t\tjmp esi\n";

const char *code7 = 	"\tjmp%d:\
						\r\t\tadd esi, %d\
						\r\t\tinc edx\
						\r\t\tinc eax\
						\r\t\tmov  _buff[%d], 1\
						\r\t\tmov bl, byte ptr [edx]\
						\r\t\tmov  [eax], bl\
						\r\t\tpop ebx\
						\r\t\tpop eax\
						\r\t\tpop ecx\
						\r\t\ttest cx, 11b\
						\r\t\tjz _%da\
						\r\t\tjmp edi\
						\r\t\t_%da:\
						\r\t\ttest [edx], 10000000b\
						\r\t\tjnz _%d\
						\r\t\tadd esi,5\
						\r\t\t_%d:\
						\r\t\t\tmov cx, 110000000b\
						\r\t\t\tjmp esi\n";
						
const char *code8_mask = 	"\tjmp%d:\
							\r\t\tmov [eax], bl\
							\r\t\tinc eax\
							\r\t\tmov  _buff[%d], 1\
							\r\t\tdec cx\
							\r\t\ttest cx, 111111111b\
							\r\t\tjz _%d\
							\r\t\tjmp esi\
							\r\t\t_%d:\
							\r\t\tjmp edi\n";
							
const char *code8_nomask = 	"\tjmp%d:\
							\r\t\tadd [eax], bl\
							\r\t\tinc eax\
							\r\t\tmov  _buff[%d], 1\
							\r\t\tdec cx\
							\r\t\ttest cx, 111111111b\
							\r\t\tjz _%d\
							\r\t\tjmp esi\
							\r\t\t_%d:\
							\r\t\tjmp edi\n";
#else
const char *code0	 =	"\tjmp0:\
						\r\t\tmov esi, offset init\
						\r\t\tadd esi, 5\
						\r\t\tmov edi, esi\
						\r\t\tadd edi, 9f6h\
						\r\t\tmov eax, ll\
						\r\t\tmov [eax], 0\
						\r\t\tmov edx, l\
						\r\t\tmov bl, byte ptr [edx]\
						\r\t\tmov  [eax], bl\
						\r\t\txor ecx, ecx\
						\r\t\tmov cl, stepNum\
						\r\t\tpush ecx\
						\r\t\ttest [edx], 10000000b\
						\r\t\tjnz _0\
						\r\t\tadd esi,5\
						\r\t\t_0:\
						\r\t\t\tjmp esi\n"; 
						
const char *code1_25_6 = 	"\tjmp%d:\
						\r\t\tadd esi, %d\
						\r\t\tinc edx\
						\r\t\tinc eax\
						\r\t\tmov bl, byte ptr [edx]\
						\r\t\tmov  [eax], bl\
						\r\t\ttest [edx], 10000000b\
						\r\t\tjnz _%d\
						\r\t\tadd esi,5\
						\r\t\t_%d:\
						\r\t\t\tjmp esi\n";
						
const char *code3 = 	"\tjmp%d:\
						\r\t\tadd esi, %d\
						\r\t\tinc edx\
						\r\t\tinc eax\
						\r\t\tmov ecx, _lk\
						\r\t\tpush ecx\
						\r\t\tmov bl, byte ptr [edx]\
						\r\t\tmov  [eax], bl\
						\r\t\tmov  eax, rl\
						\r\t\tmov [eax], 0\
						\r\t\ttest [edx], 10000000b\
						\r\t\tjnz _%d\
						\r\t\tadd esi,5\
						\r\t\t_%d:\
						\r\t\t\tjmp esi\n";
						
const char *code4 = 	"\tjmp%d:\
						\r\t\tadd esi, %d\
						\r\t\tinc edx\
						\r\t\txor ecx, ecx\
						\r\t\tpush ecx\
						\r\t\tmov bl, byte ptr [edx]\
						\r\t\tmov  [eax], bl\
						\r\t\ttest [edx], 10000000b\
						\r\t\tjnz _%d\
						\r\t\tadd esi,5\
						\r\t\t_%d:\
						\r\t\t\tjmp esi\n";

const char *code7 = 	"\tjmp%d:\
						\r\t\tadd esi, %d\
						\r\t\tinc edx\
						\r\t\tinc eax\
						\r\t\tmov bl, byte ptr [edx]\
						\r\t\tmov  [eax], bl\
						\r\t\tpop ebx\
						\r\t\tpop eax\
						\r\t\tpop ecx\
						\r\t\ttest cx, 11b\
						\r\t\tjz _%da\
						\r\t\tjmp edi\
						\r\t\t_%da:\
						\r\t\ttest [edx], 10000000b\
						\r\t\tjnz _%d\
						\r\t\tadd esi,5\
						\r\t\t_%d:\
						\r\t\t\tmov cx, 110000000b\
						\r\t\t\tjmp esi\n";
						
const char *code8_mask = 	"\tjmp%d:\
							\r\t\tmov [eax], bl\
							\r\t\tinc eax\
							\r\t\tdec cx\
							\r\t\ttest cx, 111111111b\
							\r\t\tjz _%d\
							\r\t\tjmp esi\
							\r\t\t_%d:\
							\r\t\tjmp edi\n";
							
const char *code8_nomask = 	"\tjmp%d:\
							\r\t\tadd [eax], bl\
							\r\t\tinc eax\
							\r\t\tdec cx\
							\r\t\ttest cx, 111111111b\
							\r\t\tjz _%d\
							\r\t\tjmp esi\
							\r\t\t_%d:\
							\r\t\tjmp edi\n";
#endif
							
ofstream fo("asm.cpp");
////////////////////////
//open file
///////////////
int main_gen_asm()
{
	//write first jmps
	char buff[1024];
	memset(buff, 0, 1024);
	strcpy(buff, "\tinit:\n");
	fo << buff;
	int k;
	int count = 0;
	int j;
	int i;
	for(i = 0; i < 9; i++)
	{
		k = 1 << i;
		for(int j = 0; j < k; j++)
		{
			sprintf(buff, "\t\tjmp jmp%d\n", count);
			fo << buff;
			memset(buff, 0, 1024);
			count++;
		}
	}
	
	fo << "\t\tjmp end\n\n";
	
	//1st jmp
	fo << code0;

	//steps 1 - 2
	count = 1;
	for(i = 1; i < 3; i++)
	{
		k = 1 << i;
		for(j = 0; j < k; j++)
		{
			sprintf(buff, code1_25_6, count, (count + 1) * 5, count, count, count);
			fo << buff;
			memset(buff, 0, 1024);
			count++;
		}
	}
	//step 3
	k = 1 << 3;
	for(j = 0; j < k; j++)
	{
		sprintf(buff, code3, count, (count + 1) * 5, count, count, count);
		fo << buff;
		memset(buff, 0, 1024);
		count++;
	}
	//step 4
	k = 1 << 4;
	for(j = 0; j < k; j++)
	{
		sprintf(buff, code4, count, (count + 1) * 5, count, count, count);
		fo << buff;
		memset(buff, 0, 1024);
		count++;
	}
	
	//steps 5 - 6
	for(i = 5; i < 7; i++)
	{
		k = 1 << i;
		for(j = 0; j < k; j++)
		{
			sprintf(buff, code1_25_6, count, (count + 1) * 5, count, count, count);
			fo << buff;
			memset(buff, 0, 1024);
			count++;
		}
	}
	
	//step 7
	k = 1 << 7;
	for(j = 0; j < k; j++)
	{
		sprintf(buff, code7, count, (count + 1) * 5, count, count, count, count, count);
		fo << buff;
		memset(buff, 0, 1024);
		count++;
	}
	
	//step8 - func with out mask!!!!
	sprintf(buff, code8_mask, count, count, count, count);
	fo << buff;
	memset(buff, 0, 1024);
	count++;
	
	//step8 all func without our mask
	k = 1 << 8;
	for(j = 1; j < k; j++)
	{
		sprintf(buff, code8_nomask, count, count, count, count);
		fo << buff;
		memset(buff, 0, 1024);
		count++;
	}
	
	//end label
	fo << "\tend:\n";
	
	return 0;
}



