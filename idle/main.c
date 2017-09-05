/*
 * File: main.c 
 *
 * Descri��o: 
 *     Arquivo principal de IDLE.BIN.
 *     IDLE.BIN � um processo com apenas uma thread.
 *     IDLE.BIN � um aplicativo de 32bit em user mode. 
 *
 *     Esse programa dever� ser chamado sempre que o sistema estiver ocioso,
 * ou com falta de op��es vi�veis. Ent�o esse programa deve ficar respons�vel 
 * por alguma rotina de manuten��o do equil�brio de sitema, ou por ger�ncia de 
 * energia, com o objetivo de poupar energia nesse momento de ociosidade.
 *
 * O processo idle pode solicitar que processos de gerencia de energia entrem em
 * atua��o. Pois a chamada do processo idle em si j� � um indicativo de ociosidade
 * do sistema. Pode-se tamb�m organizar bancos de dados, registros, mem�ria, buffer,
 * cache etc.
 *
 *     O sistema pode configurar o que esse processo faz quando a m�quina 
 * est� em idle mode. Quando n�o h� nenhum processo pra rodar ou a cpu se 
 * encontra ociosa, pode-se usar alguma rotina otimizada presente neste 
 * programa. Parece que a intel oferece sujest�es pra esse caso, n�o sei.
 * 
 * Obs: O entry point est� em head.s
 *      Agora idle pode fazer systemcalls. 
 *
 * @todo: Criar argumento de entrada.
 *
 * Hist�rico:
 *     Vers�o 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *     Vers�o 1.0, 2016 - Revis�o.
 *     ...
 */
 
 
//
// Includes.
// 
 
#include "api.h"      //api.
#include "stdio.h"    //libC em user mode.
#include "stddef.h"   //libC em user mode. 


//
// Vari�veis internas.
//

//Idle application support.
int idleStatus;
int idleError;
//...

//Idle driver support.
int driverInitialized;
//...

/*
struct idle
{
	struct thread_d *current_idle_thread;
	//int
}
*/


//Idle process.
int idleInit(); //processo sendo consideredo cliente.

//Idle as a driver.
void driverInitialize(); //processo sendo considerado um driver servidor.
void driverUninitialize(); // desinicializa.


/*

// System Library - SL - Essa � a classe principla que ser� colocada na biblioteca SL.BIN
// em user mode, por enquanto est� aqui do programa IDLE. Isso porque, esse padr�o pode se
// repetir em outros processos servidores acessados pelo kernel.

//Prototypes.
void *slSystemRam(unsigned long arg1,unsigned long arg2,unsigned long arg3,unsigned long arg4);
void *slSystemIoCpu(unsigned long arg1,unsigned long arg2,unsigned long arg3,unsigned long arg4);
void *slSystemIoDma(unsigned long arg1,unsigned long arg2,unsigned long arg3,unsigned long arg4);
void *slSystemDevicesUnblocked(unsigned long arg1,unsigned long arg2,unsigned long arg3,unsigned long arg4);
void *slSystemDevicesBlocked(unsigned long arg1,unsigned long arg2,unsigned long arg3,unsigned long arg4);
void *slSystemThings(unsigned long arg1,unsigned long arg2,unsigned long arg3,unsigned long arg4);
//Functions.
void *slSystemRam(unsigned long arg1,unsigned long arg2,unsigned long arg3,unsigned long arg4){ return NULL;}; //switch
void *slSystemIoCpu(unsigned long arg1,unsigned long arg2,unsigned long arg3,unsigned long arg4){ return NULL; };//switch
void *slSystemIoDma(unsigned long arg1,unsigned long arg2,unsigned long arg3,unsigned long arg4){ return NULL; };//switch
void *slSystemDevicesUnblocked(unsigned long arg1,unsigned long arg2,unsigned long arg3,unsigned long arg4){ return NULL; };//switch
void *slSystemDevicesBlocked(unsigned long arg1,unsigned long arg2,unsigned long arg3,unsigned long arg4){ return NULL; };//switch
void *slSystemThings(unsigned long arg1,unsigned long arg2,unsigned long arg3,unsigned long arg4){ return NULL; };//switch
*/


/*
 * appMain:
 *     Fun��o principal de IDLE.BIN.
 *     Obs: O entry poit est� em head.s.
 * @todo: Criar argumento de entrada.
 *
 * Como teste, o processo Idle cumpre dois pap�is: � o processo que cont�m a 
 * thread Idle, que ser� usada quando o sistema ficar ocioso, mas tamb�m � um 
 * processo servidor que ser� chamado por outro processo em user mode. O 
 * processo cliente chama o kernel, que chama o processo servidor.
 *
 * Obs: Quando for chamado por um processo e selecionar uma raz�o, ent�o 
 * devemos retornar. Dependendo da raz�o, n�o precisa retornar, porque 
 * foi o kernel quem chamou e atribuiu tempo de cpu para o processo servidor.
 * Se o processo servidor ficar preso em um loop n�o h� problemas. O scheduler
 * seleciona outra thread pra execuss�o ap�s o fim do quantum.
 */
int appMain(unsigned long arg1, unsigned long arg2, unsigned long arg3, unsigned long arg4) 
{	
    int Status;
	void *P;
	
	
	//
	// Checando a raz�o.
	//     No momento todos argumentos devem conter a raz�o,
	// no futuro ser� apenas um.
	//     Obs: Se a raz�o for 1,2,3 ou 4 ent�o foi uma
	//          chamada de um processo cliente.
    //          caso contr�rio, a chamada veio do kernel	
	// atrav�s de um iretd.
	//
	// @todo: Esse c�digo de raz�o precisa ser melhorado.
	//        colocar um unsigned long diferente como:0xDEADBEEF.
	//
	
/*
	
	switch(arg1)
	{
		//Processo cliente chamou usado raz�o 1.
		case 1:
	
		//Processo cliente chamou usado raz�o 2.
		case 2:

		//Processo cliente chamou usado raz�o 3.
		case 3:

		//Processo cliente chamou usado raz�o 4.
		case 4:

		//
		// #bugbug: Se um cliente chamar com outa raz�o,
		//          seleciona o kernel.
		//          Analisar melhor essa qust�o das raz�es.
		//
		
		//Kernel chamou.
        default:
		    kernelChamouIdle
            break;		
	};
*/
   
    //Nothing
	
kernelChamouIdle:
	
	idleInit();
	
	
	//
	// @todo: 
	// Criar o processo Logoff. (LOGOFF.BIN).
	// 

	//Logoff.
	P = (void*) apiCreateProcess( 0x400000, PRIORITY_HIGH,"LOGOFF");
	if( (void*) P == NULL  ){
		printf("Fail creating process LOGOFF :)\n");
	};	
	
    //...
	
	while(1){
        // Idle n�o sai.
        // Aqui poderia ficar o acionador de uma rotina
        // que s� funcione quando o processador estiver ocioso.
	};		
    //Nothing		
done:	
	//exit(0);
	return (int) 0;  //Status
};


/*
 * idleInit:
 *     Inicializando a aplica��o Idle.
 */
int idleInit()
{
	idleStatus = 0;
	idleError = 0;
	
	printf("Idle: Initializing idle application ..\n");
	refresh_screen();
	//...
	return (int) 0;
};


/*
 * driverInitialize:
 *     O Kernel solicitou a rotina de inicializa��o do processo Idle na forma 
 * de driver. Faremos uma chamada ao Kernel dizendo que o driver est� 
 * inicializado. Na chamada passaremos alguns par�metros, como: O n�mero do 
 * servi�o, 129 e o c�digo de confirma��o, 1234. 4321.
 *
 */
void driverInitialize()
{
	printf("Idle: Initializing driver ...\n");
	refresh_screen();

	driverInitialized = 1;	
	system_call( 129, 4321, 4321, 4321 );	
	
	printf("Idle: Initialized.\n");
	refresh_screen();
	
	//
	// Aqui n�o podemos retornar ao Kernel pois o Kernel chamou
	// via iret.
	//
	
hang:
	while(1){}
	return;
};


/*
 * driverUninitialize:
 *     This method is called to uninitialize the driver object. In a real 
 * driver, this is where the driver would clean up any resources held by 
 * this driver. (m$)
 */
void driverUninitialize()
{
	//
	// D�vidas??
	// Devemos nos preparar para desinicializar o driver.
	// Desalocaremos os recursos usadados pelo driver, como mem�ria, 
	// arquivos abertos ...
	// Obs: N�o sei se atribui��o do pr�prio driver liberar os recursos.
	// Mas de toda forma, no m�nimo devemos avisar o Kernel que os recursos 
	// n�o s�o mais necess�rios.
	// @todo: Podemos enviar um comando para o kernel pedindo pra que ele n�o 
	// link esse driver ao sistema, ou que deixe ele n�o inicializado.
	//

	printf("Idle: Unitializing driver ...\n");
	refresh_screen();

	driverInitialized = 0;	
	
	//Faremos uma chamada para o Kernel 'deslinkar' o driver.
	//talvez 128. 127 126..???
	//system_call( ?? , 4321, 4321, 4321 ); 		
	
	printf("Idle: Uninitialized.\n");
	refresh_screen();
	
	//
	// Aqui n�o podemos retornar ao Kernel pois o Kernel chamou
	// via iret.
	//
	
hang:
	while(1){}
	return;
};

//
// End.
//

