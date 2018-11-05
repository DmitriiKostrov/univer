////////////////////////////////////////////////////
////////////3DES decrypt/encrypt file test 
/////////////Dmitry Kostrov 2007
/////////////////////////////////
#include "3des.h"
#include "main.h"
#include "winsock2.h"
#include "time.h"
//////////////////////////////////////////////////////
char usage_client[] =  "[arguments]\n\
	1: addres to connect(127.0.0.1)\
[usage]:\n\
	to connect to 10.96.6.7 server type\n\
		3des 10.96.6.7\
	\n";

/************************************************/
void client_play(const char *inetAddr);
SOCKET createConnection_client(const char* ipAddr);
ulong _cH0;
//////////////////////////////////////////////
///main func
////////////////////////////////
int main_client(int argc, char* argv[])
{
	//return test_gamma();
	if(argc < 2)
	{
		printUsage(usage_client);
		return 0;
	}
	client_play(argv[1]);
	return 1;
}
////////////////////////////////////////////////////////////
//read from file, encode end write to out file
//////////////////////
void client_play(const char *inetAddr)
{
	/////////////////////////////////////////////////////////////////////
	SOCKET sock = createConnection_client(inetAddr);
	int bytesRecv = SOCKET_ERROR;
	char recBuf[8*52];
	_cH0 = rand();
	// 3DES keys
	ulong key1 = rand();  
	ulong key2 = rand();
	ulong key3 = rand();
	////////////////////////////////////////////////////////////////
	bytesRecv = recv( sock, recBuf, 8*52, 0 );
	if ( bytesRecv == 0 || bytesRecv == WSAECONNRESET )
	{
		printf( "Connection Closed.\n");
		printf("\n...Game Over...\n");
		return;
	}
	if (bytesRecv < 0)
		return;
	ulong crypt_cards[52];
	memcpy(crypt_cards, recBuf, 8*52);
	printf("#Received 52 server-crypted cards from server\n\n", bytesRecv);
	//////////////////////////////////////////////////////
	prepareKeys(key1, key2, key3, false);
	ulong doubleCryptCards[5];
	ulong H0;
	// crypt cards with gamma
	printf("#Sending 5 client-server-crypted cards to server\n\n");
	int ii;
	time_t time;
	_time64(&time);
	srand(time);
	for(int i = 0; i < 5; i++)
	{
		H0 = _cH0;
		while(1)
		{
			ii = rand() % 52;
			if(crypt_cards[ii] == 0)
				continue;
			doubleCryptCards[i] = crypt_cards[ii];
			crypt_cards[ii] = 0;
			break;
		}
		crypt_gamma(H0, doubleCryptCards[i]);
	}
	///////////////////////////////////////////////////////////
	//send 5 client-server crypt scards
	int bytesSent = (int)send( sock, (char*)doubleCryptCards, 8*5, 0 );
	//receive 5 clint crypt cards
	bytesRecv = recv( sock, recBuf, 8*5, 0 );
	memcpy(doubleCryptCards, recBuf, 8*5);
	//get clean cards!!!
	printf("####Your cards####\n");
	for(int i = 0; i < 5; i++)
	{
		H0 = _cH0;
		crypt_gamma(H0, doubleCryptCards[i]);
		printf("0x%x\t", doubleCryptCards[i]);
	}
	// crypt cards with gamma
	printf("\n#Sending 5 server-crypted cards to server\n\n");
	for(int i = 0; i < 5; i++)
	{
		//H0 = 0x55;
		while(1)
		{
			ii = rand() % 52;
			if(crypt_cards[ii] == 0)
				continue;
			doubleCryptCards[i] = crypt_cards[ii];
			crypt_cards[ii] = 0;
			break;
		}
	}
	bytesSent = (int)send( sock, (char*)doubleCryptCards, 8*5, 0 );
	printf("\n...Game Over...\n");
}
/////////////////////////////
//creates connection
///////////////////
SOCKET createConnection_client(const char* ipAddr)
{
	WSADATA wsaData;
	int iResult = WSAStartup( MAKEWORD(2,2), &wsaData );
	if ( iResult != NO_ERROR )
		printf("Error at WSAStartup()\n");
	
	SOCKET m_socket;
	m_socket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	if ( m_socket == INVALID_SOCKET )
	{
		printf( "Error at socket(): %ld\n", WSAGetLastError() );
		WSACleanup();
		return (SOCKET)-1;
	}
	
	sockaddr_in clientService;

	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr( ipAddr);
	clientService.sin_port = htons( 27015 );

	
	if ( connect( m_socket, (SOCKADDR*) &clientService, sizeof(clientService) ) == SOCKET_ERROR)
	{
		printf( "Failed to connect.\n" );
		WSACleanup();
		return (SOCKET)-1;
	}
	return m_socket;
}