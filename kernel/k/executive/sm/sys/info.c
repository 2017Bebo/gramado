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
//void infoShowKernelInfo() 
void KiInformation()
{
	
	//
	// Messages.
	//
	
	printf("\n[System Info:]\n");
	//OS info.
	printf("%s ",OS_NAME);
	printf("Version: %d.%d.%d.%d \n\n" ,SYSTEM_VERSIONMAJOR
	                                        ,SYSTEM_VERSIONMINOR
										    ,SYSTEM_VERSIONBUILT
										    ,SYSTEM_VERSIONREVISION );
	
	
	//
	// Kernel info.
	//
	
	//Version and time running.	
	printf("\n[Kernel Info:]\n");
	printf("Kernel version: %s\n",KERNEL_VERSION );
	printf("Ticks running: %d\n",kernel_tick_total );

												   
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
	
	printf("Dispatch criteria:\n");
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

	
	//
	// Video info
	//
	
	printf("\n[Video Info:]\n");
	
	//Video mode.
	//printf("The video option is %x \n",g_video_mode);
	printf("FrontbufferPA={%x} FrontbufferVA={%x} BackbufferVA={%x} \n",g_frontbuffer_buffer_address ,g_frontbuffer_buffer_va ,g_backbuffer_address);
	
	
	//
	// user info
	//
	
	printf("\n[User Info:]\n");
	
	//Group and user.
	printf("Group={%d} User={%d} \n",current_group,current_user);
	
	//user session, window station, desktop.
	printf("UserSession={%d} DesktopPool={%d} Desktop={%d} \n",current_usersession
	                                                          ,current_windowstation
															  ,current_desktop);
															
	ShowUserInfo(0);  //#bugbug
	
	
	//
	// Process and thread info
	//
	
	printf("\n[Process Info:]\n");	
    //process, thread.
	printf("CurrentProcess={%d} CurrentThread={%d} \n\n",current_process ,current_thread);
	
	
	
	//
	// Memory info.
	//
	
	memoryShowMemoryInfo();
	
	//Espec�fico para intel.
	//Talves isso n�o deva ficar aqui.
	//show_cpu_intel_parameters();
	
	//More?!
	
//Done
done:
	if(VideoBlock.useGui == 1){
	    //N�o precisa disso se foi chamado pelo procesimento do sistema.
		refresh_screen();
	};
	
	//SetFocus(hWindow);	
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

