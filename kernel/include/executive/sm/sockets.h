/*
 * Arquivo: sockets.h
 *
 * Descri��o:
 *     Header para gerenciamento de sockets.
 *
 *    "Um soquete � composto por um endere�o de ip,
 *     concatenado com um n�mero de porta, ip_addres:port"
 *
 * Vers�o 1.0, 2016.
 */


/*
 * struct sockets_d:
 *     ex: 192.168.1.1:80
 */
typedef struct sockets_d sockets_t;
struct sockets_d
{
	object_type_t objectType;
	object_class_t objectClass;
	
	unsigned long ip_address;
    short port;	
	
	//struct ip_address_d *ip_address;    //@todo: deletar.
};
sockets_t *CurrentSocket;



//unsigned long socketList[16];


//
//fim.
//

