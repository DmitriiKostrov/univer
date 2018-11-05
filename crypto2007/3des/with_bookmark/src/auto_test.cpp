////////////////////////////////////////////////////
////////////3DES decrypt/encrypt with bookmark  - all masks test
/////////////Dmitry Kostrov 2007
/////////////////////////////////
#include "3des.h"
#include "main.h"
#include "time.h"
#include "stdlib.h"

extern uchar _buff[];
int main_auto(int argc, char* argv[])
{
#ifdef BOOKMARK_TEST
	// 3DES keys
	ulong key1 = 0;  
	ulong key2 = 0;
	ulong key3 = 0;
	//random activate
	time_t time;
	_time64(&time);
	srand(time);
	key1 = (ulong)rand(); 
	key2 = (ulong)rand(); 
	key3 = (ulong)rand();
	if(argc > 1)
	{
		memcpy(&key1, argv[1], (strlen(argv[1]) > 8) ? 8 : strlen(argv[1])) ;
	}
	if(argc > 2)
	{
		memcpy(&key2, argv[2], (strlen(argv[2]) > 8) ? 8 : strlen(argv[2])) ;
	}
	if(argc > 3)
	{
		memcpy(&key3, argv[3], (strlen(argv[3]) > 8) ? 8 : strlen(argv[3])) ;
	}
	printf("key1 = 0x%x%x; key2 = 0x%x%x; key3 = 0x%x%x\n", key1, key1 << 32, key2, key2 << 32, key3, key3 << 32);
	// 3des bookmark algoritm checks 1st 8 bite of 64 bite data block
	// so encrypt/decrypt all available values of first data block byte
	// and see results
	printf("#Automat test starting!\n");
	int collisionAll = 0;
	int collision;
	ulong l;
	for(int i = 0x00; i <= 0xff; i++)
	{
		l = i;
		collision = 0;
		while(true)
		{
			prepareKeys(key1, key2, key3, false);
			des3Encode(l);
			prepareKeys(key1, key2, key3, true);
			des3Decode(l);
			if((l & i) != i)
			{
				printf("i = 0x%x: collision #%d\n", i, ++collision);
				collisionAll++;
				l = i + 0x100 * collision;
				continue;
			}
			break;
		}
	}
	printf("#Test finished: 0x%x collisions detected\n", collisionAll);
	int automatNodesChecked = 0;
	for(int i = 0; i < 0x1ff; i++)
	{
		automatNodesChecked += (int)_buff[i];
	}
	printf("#Test %s: 0x%x nodes from 0x1ff checked\n", (automatNodesChecked == 0x1ff) ? "SUCCEEDED" : "FAILED", automatNodesChecked);
#endif	
	return 0;
}