/*
 * Arquivo: logoff.h
 *
 * Descri��o:
 *     Header de suporte ao logoff.
 *
 *     OBS:
 *     O Logoff deve seu pr�prio desktop. 
 *     As rotinas de Logoff podem estar em um processo em User Mode.
 *     Ou em um m�dulo externo em kernel mode.     
 *
 * Vers�o 1.0, 2015, 2016.
 */
 
int init_logoff(int argc, char *argv[]);
int StartLogoff(int argc, char *argv[]);


//
//fim.
//

