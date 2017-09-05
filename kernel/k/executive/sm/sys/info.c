/*
 * File: info.c
 *
 * Descri��o:
 *     Rotinas de informa��es sobre o sistema.
 *
 *    Vers�o 1.0, 2015, 2016. 
 */
 

#include <kernel.h>


/*
 * KeInformation: 
 *    @todo:
 *    Mostra em informa��es sobre o kernel.
 *    Chama m�dulo externo (Server em user mode) para
 *    mostrar informa��es sobre o kernel ou sobre o sistema.
 *
 *    Obs: As inform��es podem ser salvas em um arquivo
 *         de sa�da padr�o.
 */
void KeInformation()
{	
	return;    //Ainda n�o implementada.
};


/*
 * KiInformation: 
 * Mostra uma lista de informa��es sobre o Sistema.
 * Obs: @todo: A lista de informa��es de ser bem completa, pois servir�
 * de ajuda ao desenvolvedor. Deve conter de tudo, abordando todas as 
 * camadas do sistema. 
 * 
 * Ordem por classe:
 * ================
 * RAM: ram, sm, uigm, uitm.
 * IO: cpu, dma.
 * DEVICES: umblocked, blocked
 * THINGS:
 *
 *
 * Obs: As inform��es podem ser salvas em um arquivo de sa�da padr�o.
 */
void KiInformation()
{
	//
	// Messages.
	//
	
	//OS info.
	//printf("%s %",OS_NAME ,OS_VERSION);
	printf("System version: %d.%d.%d.%d \n" ,SYSTEM_VERSIONMAJOR
	                                        ,SYSTEM_VERSIONMINOR
										    ,SYSTEM_VERSIONBUILT
										    ,SYSTEM_VERSIONREVISION );
	
	//Kernel info.
	//Version and time running.	
	printf("Kernel Info:\n");
	printf("Kernel version: %s Time running: %d \n",KERNEL_VERSION
	                                               ,kernel_tick_total );

												   
    //ShowUserInfo(int user_id);												   
												   
	//
    // Show status.
    //
	
	//Status do mecanismo de task switch.
	switch(task_switch_status)
	{
	    case LOCKED:
		    printf("Task switch is LOCKED.\n");
			break; 
	    case UNLOCKED:
		    printf("Task switch is UNLOCKED.\n");
		    break; 	
	};

	//Status do Scheduler.
	switch(g_scheduler_status)
	{
	    case LOCKED:
		    printf("Scheduler is LOCKED.\n");
		    break; 
	    case UNLOCKED:
		    printf("Scheduler is UNLOCKED.\n");
		    break; 
	};
		
	//
	// Mostra o n�mero de vezes que um crit�rio de sele��o de thread 
	// foi usado pelo scheduler.
	//
	
	printf("Criterios de Dispatch:\n");
	printf("cIdle={%d} cInit={%d} cNext={%d} cCur={%d} cAny={%d} cIdeal={%d} cDisp={%d}\n",DispatchCountBlock->SelectIdleCount
	    ,DispatchCountBlock->SelectInitializedCount
	    ,DispatchCountBlock->SelectNextCount
	    ,DispatchCountBlock->SelectCurrentCount
	    ,DispatchCountBlock->SelectAnyCount
        ,DispatchCountBlock->SelectIdealCount
	    ,DispatchCountBlock->SelectDispatcherQueueCount);
		
	
    //
	// Mostra Heap e Stack do kernel..
	//

	
	unsigned long HeapTotal = ((kernel_heap_end - kernel_heap_start)/1024);
	unsigned long StackTotal = ((kernel_stack_start - kernel_stack_end)/1024);
	
    printf("Kernel Heap and Stack info:\n");
	printf("HEAP: Start={%x} | End={%x} | Total={%d KB} \n",kernel_heap_start ,kernel_heap_end ,HeapTotal);	
    printf("AvailableHeap={%d KB}\n",g_available_heap/1024);
	printf("STACK: Start={%x} | End={%x} | Total={%d KB} \n",kernel_stack_start ,kernel_stack_end ,StackTotal);

	
	//Video mode.
	printf("The video option is %x \n",g_video_mode);
	printf("Frontbuffer={%x} Backbuffer={%x} \n",g_frontbuffer_buffer_address ,g_backbuffer_address);
	
	//Group and user.
	printf("Group={%d} User={%d} \n",current_group,current_user);
	
	//user session, window station, desktop.
	printf("UserSession={%d} DesktopPool={%d} Desktop={%d} \n",current_usersession
	                                                          ,current_windowstation
															  ,current_desktop);
															
	
    //process, thrad.
	printf("CurrentProcess={%d} CurrentThread={%d} \n",current_process ,current_thread);
	
	
	ShowUserInfo(0);  //#bugbug
	
	//More?!
	
//Done
done:
	if(VideoBlock.useGui == 1){
	    //N�o precisa disso se foi chamado pelo procesimento do sistema.
		refresh_screen();
	};
    return;	
};

/*
 Salva as informa��es em um arquivo de texto.
void infoSaveInfo();
void infoSaveInfo()
{
	return;
}
*/

/*
 * @todo:
 *
void infoShowKernelInfo();
void infoShowKernelInfo()
{
	return;
};
*/


//
// Fim.
//

