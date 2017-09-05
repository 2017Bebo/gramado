/*
 * File: main.c 
 *
 * Descri��o:
 *     Arquivo principal do aplicativo Task Manager em user mode. 
 *     O nome do utilit�rio � TASKMAN.BIN.
 *     � um aplicativo de 32bit, em user mode, para gerenciar o sistema.
 *     
 * Atribui��es:
 *     Mostrar estat�sticas e status sobre processos e threads, realizar
 * opera��es em processos e threads como criar fechar, etc ...
 *    
 * *IMPORTANTE: ESSE � O GERENCIADOR DE TAREFAS , ELE PODE SOLICITAR
 * MUITAS INFORMA��ES AO KERNEL AJUDANDO O DESENVOLVEDOR A TRABALHAR
 * ESSAS CHAMADAS. � IDEAL PARA TESTES.
 *
 *     Tipo: P3 - Processos em ring3, User Mode.	
 *          
 * Obs:
 *     +O entry point est� em head.s.
 *     +...
 * @todo: + Incluir bibliotecas dispon�veis.
 *        + Dar algum sinal de vida na tela.
 *
 * Historico:
 *     Vers�o 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *     Vers�o 1.0, 2016 - Aprimoramento geral das rotinas b�sicas.
 *     ...
 */


 
//
// Includes.
//
 
#include "api.h"
#include "stdio.h"
#include "stddef.h"



//
// Vari�veis internas.
//

int taskmanagerStatus;
int taskmanagerError;

//
// Buffer support.
//

#define TASKMANAGER_BUFFER_SIZE 512

char taskmanagerBuffer[32];  //TASKMANAGER_BUFFER_SIZE
int taskmanagerBufferPos;
//...


//FILE *taskmanOutput;


//
// Prot�tipos de fun��es internas.
//
 
 
//Prot�tipo do procedimento de janela.
int tmProc(int junk, int message, unsigned long long1 , unsigned long long2);

//Prot�tipos de fun��es internas.
void tmUpdateStatus();

//Inicializa��es.
int tmInit();


void tmSetCursor(unsigned long x, unsigned long y);


/*
tmCreateTaskBar: 
    Barra para mostrar informa��es.
	
Atribui��es:
    +Cria uma barra em baixo na tela com �cones que representam os processos 
da lista de processos, ou que indique atividade de processos.
    +Sondar se o processo existe na lista de processos l� no kernel.
    +Para cada processo encontrado na lista, cria uma janelinha onde ficar� um 
    �cone que representa o processo.
    +...
	
Obs: 
    No futuro, pegaremos essa lista inteira de uma vez s�, atrav�z de �rea 
compartilhada e usaremos a lista aqui em user mode.
    
 */

 
#define MAGIC (1234)


int tmProbeProcessList(int pid);
int tmCreateTaskBar(); 
void tmSleep(unsigned long ms); 


//
//
//


/*
 * sleep:
 *     Apenas uma espera, um delay.
 *     Essa n�o � a fun��o que coloca uma tarefa pra dormir no caso de evento.
 */
void tmSleep(unsigned long ms) 
{
    unsigned long t = (ms*512);
	
	do{
	    --t;
	}while(t > 0);

done:	
	return;
};


/*
 * tmProbeProcessList:
 *     Sonda para ver se o processo est� presente e � v�lido.
 *     Se retornar 1234 (MAGIC) � um processo v�lido.
 *
 */
int tmProbeProcessList(int pid)
{
	//if(pid < 1){
	//    return (int) -1; //error.	
	//};
	
	return (int) system_call( SYSTEMCALL_88, pid, pid, pid );
};

 
/*
 * tmCreateTaskBar:
 *     ??
 */
int tmCreateTaskBar()
{
	int i;
	int j=0;
	int Magic;
	
	g_cursor_x = 0;
	g_cursor_y = 0;
	
	//@todo: Vari�vel para n�mero m�ximo.
	for(i=0; i<256; i++)
	{
	    Magic = (int) tmProbeProcessList(i);
	    
		if(Magic == MAGIC)
		{
			    //APICreateWindow( 1, 1, 1,"Process",     
                //                 0, j, 20, 20,    
                //                 0, 0, 0 , COLOR_WINDOW );
		        // j = j+22;
				
			
			//@TODO: #BUGBUG: Esta bagun�ando tudo,
			//pintando strings na �rea de cliente de otro processo.
			printf("process magic %d\n",i);	
		};
		//Nothing
	};
	
	
	//nothing
	
Done:
	return (int) 0;
};


/*
 * appMain:
 *     Fun��o principal do Task Manager.
 * 
 * @todo:
 *     +... 
 */
 
int appMain(int argc, char *argv[]) 
{
	int Flag;
	//int Status;
	void *P;
    struct window_d *hWindow;	
	
	tmInit();  //Initializing ...
	
	//
	// Esses s�o os processos que taskman tem que criar.
	//

	//Logon.
	P = (void*) apiCreateProcess( 0x400000, PRIORITY_HIGH,"LOGON");
	if( (void*) P == NULL  ){
		printf("Fail creating process LOGON.\n");
	};
	
	//Object Manager. (Pertence ao Security Control).
	P = (void*) apiCreateProcess( 0x400000, PRIORITY_HIGH,"OM");
	if( (void*) P == NULL  ){
		printf("Fail creating process OM.\n");
	};

	//System Security. (Pertence ao Security Control).
	P = (void*) apiCreateProcess( 0x400000, PRIORITY_HIGH,"SS");
    if( (void*) P == NULL ){ 
	    printf("Fail creating process SS.\n");
	};
	
    /*
     * @todo: 
	 *     O recurso de criar janelas est� rasoavelmente funcionando. 
	 * Mas n�o criar ainda. O recurso de janelas est� sendo testado e aprimorado 
	 * na aplica��o terminal. Na verdade conv�m testar tudo no terminal.
	 */
	 
	 
	// 
    // Create window.
	//
	
	/*
	
	//Tentando enviar strings pra propria janela.
	
	//@todo: Obter o ponteiro para a janela que repressenta a �rea de trabalho.
	//Ou deveria ter uma flag que indicasse, que a janela deve ter como janela mae a �rea
	//de trabalho...
	
	hWindow = (void*) APICreateWindow( WT_OVERLAPPED, 1, 1,"TaskMan Window",     
                                       2, 2, 128, 64,    
                                       0, 0, 0 , COLOR_WINDOW );
	
	if( (void*) hWindow != NULL )
	{
        //Registrar.
	    APIRegisterWindow(hWindow);
	
	    //Configurar como ativa.
	    //APISetActiveWindow(hWindow);
	
	    //Setar foco.
	    //APISetFocus(hWindow);
		
		//Sondando processos. criando �cones.
	    //@todo #bugbug esta pintando na area de cliente de outro processo.
		//tmCreateTaskBar();
	    
		//refresh_screen();
        
        //...		
	};	
	*/

    //
	// @todo: 
	//     Fazer alguns testes antes do loop.
	//
    
	
	//Show info (chamadas seguras.)
	
	
	//PCI info
    //system_call( SYSTEMCALL_SHOW_PCI_INFORMATION, 0, 0, 0 );
				   
	//kernel info			   
    //system_call( SYSTEMCALL_SHOW_KERNEL_INFORMATION, 0, 0, 0 );	
	
	
	
	//@todo: Testar carregar uma bmp .
    //carrega_bitmap_16x16( unsigned long img_address, unsigned long x, unsigned long y);	
	//system_call( SYSTEMCALL_LOAD_BITMAP_16x16, 0, 0, 0 );	
	
    //Message Box testing... (funcionou.)
   // system_call( SYSTEMCALL_MESSAGE_BOX, 1, "Process", "TASKMAN.BIN");	
	

	
	//1-Tipo de janela, (popup,normal,...).
	//2-Estado da janela, (ativa ou n�o).
	//3-(min, max ...).
	//4-T�tulo.
	//5-Deslocamento em rela��o �s margens do Desktop.
	//6-Deslocamento em rela��o �s margens do Desktop.
	//7-Largura da janela.
	//8-Altura da janela.
	//9-Endere�o da estrutura da janela m�e.
	//10-Ambiente.( Est�o no desktop, barra, cliente ...)
	//11-? reservado.
	//12 - COLOR.
   
/*
    APICreateWindow( 1, 1, 1,"Task Manager1",     
                      100, 100, 100, 100,    
                      0, 0, 0 , COLOR_WINDOW );
					  
					  
    APICreateWindow( 2, 1, 2,"Task Manager2",     
                      100, 100, 100, 100,    
                      0, 0, 0 , COLOR_WINDOW );
					  
					  
					  
    APICreateWindow( 3, 1, 0,"Task Manager3",     
                      100, 100, 100, 100,    
                      0, 0, 0 , COLOR_WINDOW );
					  
					  
					  
    APICreateWindow( 4, 1, 1,"Task Manager4",     
                      100, 100, 100, 100,    
                      0, 0, 0 , COLOR_WINDOW );
					  
  */
  
	//Chamar esse message box esta atrapalhando o logion por enquanto, mas funciona bem.
	//system_call( SYSTEMCALL_MESSAGE_BOX, 1, "Process", "TASKMAN.BIN");	
	
	//refresh screen
	//system_call( SYSTEMCALL_REFRESHSCREEN, 0, 0, 0 );	
	
	
	//Testing String 		
	//system_call( SYSTEMCALL_DRAWTEXT, 0,  0, (unsigned long) "/TASKMAN.BIN Testing strings...");
		
		
	//Refresh screen
	//system_call( SYSTEMCALL_REFRESHSCREEN, 0, 0, 0);
	
	

	
   	//
	// * Hang.
	//
	
    while(1)
	{
        //
        // Test: 		
        // Aproveitando para testar chamadas.		
		// Usando o loop para cauasr um pouco de stress, com muitas chamadas.
		//
		
		//system_call( SYSTEMCALL_NULL, 0, 0, 0 );
        //system_call( SYSTEMCALL_DEAD_THREAD_COLLECTOR, 0, 0, 0 );
		//...
		
		//
		// Sinal de vida.
		// Pintando caracteres no canto superior esquerdo da janela.
		//
		
	    tmSetCursor(0,0);		
		printf("\\");
		tmSleep(12345);

	    tmSetCursor(0,0);		
		printf(" "); 
		tmSleep(12345); 		

	    tmSetCursor(0,0);	
		printf("|");
		tmSleep(12345);

	    tmSetCursor(0,0);		
		printf(" "); 
		tmSleep(12345); 		

	    tmSetCursor(0,0);	
		printf("/");
		tmSleep(12345);

	    tmSetCursor(0,0);		
		printf(" "); 
		tmSleep(12345); 		

	    tmSetCursor(0,0);	
		printf("-"); 
		tmSleep(12345);

	    tmSetCursor(0,0);		
		printf(" "); 
		tmSleep(12345); 		

	    tmSetCursor(0,0);	
		printf("|"); 
		tmSleep(12345);

	    tmSetCursor(0,0);		
		printf(" "); 
		tmSleep(12345); 		

	    tmSetCursor(0,0);	
		printf("-");
		tmSleep(12345);

	    tmSetCursor(0,0);		
		printf(" "); 
		tmSleep(12345); 		

		//
		//taskmanagerStatus
		//
		
		if(Flag == 1234){
			goto done;
		}
		
		//if(Flag == 1234){}
		//if(Flag == 1234){}
		//if(Flag == 1234){}
		//...
	};	
	
   
    //
    //Obs: O exit funcionou corretamente no teste.
    //     Mas n�o usaremos exit ainda pois temos poucas threads no sistema.
	//
	
done:   
   exit(0);        //Obs: exit n�o usado ainda. 
   return (int) 0; //Obs: Retorno n�o usado ainda.
};


/*
 * tmProc:
 *     Procedimento de janela do Task Manager.
 *     O procedimento intercepta algumas mensagens e as mensagens de sistema
 * s�o passadas para o procedimento do sistema na op��o default.
 */
int tmProc( int junk, int message, unsigned long long1, unsigned long long2)
{
    //Filtrar mensagem.
	
	switch(message)
	{
	    case MSG_KEYDOWN:
    		switch(long1)
			{
			    case '1':
					printf("1");
				    break;
					
			    case '9':
				    //taskmanagerStatus = 1234;  
					apiReboot();
				    break;
	
			    case 'a':
				    printf("a");
					break;
			    case KEY_TAB:
				    printf("tab");
				    break;
                default:
				    printf("default key down\n");
					break;
			};
			break;
	    
		case MSG_KEYUP:
		    break;
	
        case MSG_CREATE:
            break; 		
	
	    //...
		
		default:
		    //Falta passar a janela.
			//system_call(SYSTEMCALL_CALL_SYSTEMPROCEDURE, message, long1, long2);			
            break;		
	};

	//Nothing.
	
done:
    return (int) 0;
};


/*
 * tmUpdateStatus:
 *
 */
void tmUpdateStatus()
{
	int CpuStep;
    int ActiveWindow;	
	int wFocus;
	
	//@todo: O n�mero dos servi�os est�o desatualizados.
	
	//pega o valor do step do processador. quantas vezes ele rodou tarefa.
	//CpuStep = system_call(83,0,0,0);
	
	//pega a janela com o foco de entrada.
	//wFocus = system_call(47,0,0,0);
	
	//peaga o numero da janela ativa.
	//ActiveWindow = system_call(45,0,0,0);
	
	
	//tmDrawBar(0x7f);
	tmSetCursor(1,0);
		
	printf("Task Manager: wFocus[%d] | ActiveWindow[%d] | CpuStep[%d]",wFocus
	                                                                  ,ActiveWindow
	                                                                  ,CpuStep );
		
	
	
	//Cursor.
	tmSetCursor(0,1);

	//...
	
done:	
	return;
};


/*
 * tmDrawBar:
 *     Desenhar uma barra em modo texto.
 *    #bugbug N�o � esse o ambiente que estamos. @todo
 */
int tmDrawBar(int color)
{
    unsigned int i = 0;	
	char *vm = (char *) 0x00800000;  //g_current_vm; //phis=0x000B8000; 
	
	//
	// @todo: Usar alguma fun��o de uma biblioteca GUI em user mode.
	//
	
	while(i < ( SCREEN_WIDTH * 2) ) 
    { 
        vm[i] = 219; 
        i++; 
        
        vm[i] = color; 
        i++; 
    };
	
	
	//Cursor.
	tmSetCursor(0,0);
    
	
	
done:	
    return (int) 0; 
};


/*
 * tmSetCursor:
 *     Configurando o cursor. (stdio.h).
 */
void tmSetCursor(unsigned long x, unsigned long y){
    g_cursor_x = (unsigned long) x;
    g_cursor_y = (unsigned long) y;	
	return;
};


/*
 * tmInit:
 *     Inicializa��es.
 */
int tmInit()
{
	taskmanagerStatus = 0;
	taskmanagerError = 0;
	//taskmanagerBuffer = '\0'
	taskmanagerBufferPos = 0;
	
	
	tmSetCursor(0,0);
	//...
	
done:
    return (int) 0;
};


//
// End.
//

