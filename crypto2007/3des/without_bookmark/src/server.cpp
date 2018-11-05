////////////////////////////////////////////////////
////////////3DES decrypt/encrypt file test 
/////////////Dmitry Kostrov 2007
/////////////////////////////////
#include "3des.h"
#include "main.h"
#include "winsock2.h"
#include "time.h" 

//////////////////////////////////////////////////////
char usage_server[] =  "[arguments]\n\
	1: addres to bind in(127.0.0.1)\n\
[usage]:\n\
	to create server on 10.96.6.7 server type\n\
		3des 10.96.6.7\
	\n";

/************************************************/
void server_play(const char *inetAddr);
SOCKET createConnection_server(const char* ipAddr);
void fillCards();
/*****************************************/
ulong _cards[52];
ulong _sH0;
//////////////////////////////////////////////
///main func
////////////////////////////////
int main_server(int argc, char* argv[])
{
	
	if(argc < 2)
	{
		printUsage(usage_server);
		return 0;
	}
	server_play(argv[1]);
	return 1;
}
////////////////////////////////////////////////////////////
//read from file, encode end write to out file
//////////////////////
void server_play(const char *inetAddr)
{
	//init radnomize
	time_t time;
	_time64(&time);
	srand(time);
	_sH0 = rand();
	fillCards();
	// 3DES keys
	ulong key1 = rand();  
	ulong key2 = rand();
	ulong key3 = rand();
	// prepare keys. just do it 1 time!
	prepareKeys(key1, key2, key3, false);
	ulong cards[52];
	ulong H0;
	int ii;
	ulong cardsTmp[52];
	memcpy(cardsTmp, _cards, 52*8);
	// crypt cards using gamma
	for(int i = 0; i < 52; i++)
	{
		H0 = _sH0;
		while(1)
		{
			ii = rand() % 52;
			if(cardsTmp[ii] == 0)
				continue;
			cards[i] = cardsTmp[ii];
			cardsTmp[ii] = 0;
			break;
		}
		crypt_gamma(H0, cards[i]);
	}
	//create connection
	SOCKET srv_sock = createConnection_server(inetAddr);
	if(srv_sock == -1)
		return;
	//wait for client
	printf("###Waiting for client###\n");
	SOCKET acceptSocket = accept( srv_sock, NULL, NULL );
	if (acceptSocket == INVALID_SOCKET)
	{
		printf("accept failed: %d\n", WSAGetLastError());
		closesocket(srv_sock);
		WSACleanup();
		return;
	} 
	else 
		printf("####Client connected####\n\n");
    int bytesSent = (int)send( acceptSocket, (char*)cards, 8*52, 0 );
	printf("#Sent 52 server-crypted cards to client\n\n");
	/////////////////////////////////////////////////////////
	//waiting for 5 double encrypted cards
	char recBuf[8*5];
	int bytesRecv = recv( acceptSocket, recBuf, 8*5, 0 );
	printf("#Received 5 server-client-crypted cards from client\n\n");
	memcpy(cards, recBuf, 8*5);
	for(int i = 0; i < 5; i++)
	{
		H0 = _sH0;
		crypt_gamma(H0, cards[i]);
	}
	bytesSent = (int)send( acceptSocket, (char*)cards, 8*5, 0 );
	printf("#Sent 5 client-crypted cards to client\n\n");
	bytesRecv = recv( acceptSocket, recBuf, 8*5, 0 );
	memcpy(cards, recBuf, 8*5);
	printf("###Your cards###\n");
	for(int i = 0; i < 5; i++)
	{
		H0 = _sH0;
		crypt_gamma(H0, cards[i]);
		printf("0x%x\t", cards[i]);
	}
	// No longer need server socket
	closesocket(srv_sock);
	
	WSACleanup();
	printf("\n\n\n...Game Over...\n");
}
/////////////////////////////
//creates connection
///////////////////
SOCKET createConnection_server(const char* ipAddr)
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
    clientService.sin_addr.s_addr = inet_addr(ipAddr);
    clientService.sin_port = htons( 27015 );

 
    if(bind(m_socket, (struct sockaddr*)&clientService, sizeof(clientService))<0)
	{
		printf( "error at bind socket(): %ld\n", WSAGetLastError() );
        WSACleanup();
        return (SOCKET)-1;

    }
	
	if ( listen( m_socket, 1 ) == SOCKET_ERROR )
	{
		printf( "Error at bind(): %ld\n", WSAGetLastError() );
		closesocket(m_socket);
		WSACleanup();
		return -1;
	}
	return m_socket;
}

void fillCards()
{
	printf("Available cards are:\n\n");
	ulong tmp;
	int j;
	for(int i = 0; i < 52; i++)
	{
		tmp = rand() % 0xffffffff  + 0x1000000 + 0x100000 + i * 100;
		for(j = 0; j < i; j++)
		{
			if(_cards[j] == tmp)
				break;
		}
		if(j != i && i)
		{
			i--;
			continue;
		}
		_cards[i] = tmp;
		printf("0x%x\t", _cards[i]);
	}
	printf("\n\n");
}