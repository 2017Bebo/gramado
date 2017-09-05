/*
 * File: ip.h
 *
 * Descri��o:
 *    IP protocol info.
 *
 *
 * Vers�o 1.0, 2016.
 */

 
 
/*
    Pilha de protocolos TCP/IP:
    ==========================

Camada de aplica��o
BGP DHCP DNS FTP HTTP IMAP LDAP MGCP NNTP NTP 
POP ONC/RPC RTP RTSP RIP SIP SMTP SNMP SSH Telnet TLS/SSL XMPP outros...

Camada de transporte
TCP UDP DCCP SCTP RSVP outros...

Camada de interconex�o
IP IPv4 IPv6 ICMP ICMPv6 ECN IGMP IPsec outros...

Camada de enlace
ARP NDP OSPF t�neis... L2TP PPP MAC Ethernet DSL RDIS FDDI outros...

*/ 


/*
 Lightweight TCP/IP - um conjunto de c�digos abertos projetado para sistemas embarcados.
 KA9Q NOS, a pilha e um conjunto de protocolos associados para sistemas de radio amador e 
 computadores pessoais conectados atrav�s de linhas seriais.
 
 
*/ 
 
/* 
typedef struct ip_string_d ip_string_t; 
struct ip_string_d
{
    char String[4 * 4];
};	
ip_string_t *ipString;
*/ 

typedef struct ip_address_d ip_address_t; 
struct ip_address_d
{
	object_type_t objectType;
	object_class_t objectClass;
	
	//netid + hostid.
    unsigned long ip_address;
	//unsigned long ip_mask;
	
	int version;    //IPv4, IPv6.
	
	//Armazena os valores dos quatro bytes em decimal na forma de string com pontos.
	//char string[4*4]; 
};
ip_address_t *ip_address;
//...


// We need adapter info: like: name, description
//so n�o sei se informa��es sobre o adaptador deveria ficar nesse arquivos.


//
// End.
//

