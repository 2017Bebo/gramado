/*
 * File: memory.c
 *
 * Descri��o:
 *     Arquivo principal do m�dulo /mm do executive, Memory Manager. 
 *     MB - M�dulos inclu�dos no Kernel Base.
 *
 * Atribui��es:
 *     + Alocar Heap do Kernel.
 *     + Liberar Heap do Kernel.
 *     + Inicializar Heap e Stack do Kernel.
 *     + Gerenciar Page Directory, Page Table ...
 *     ...
 *
 * Obs:
 *     Uma regi�o � uma �rea de 4MB alocada. S�o todas as p�ginas
 * que cabem em uma tabela, 2014 p�ginas de 4KB cada. Isso tamb�m pode
 * ser chamado de pool e ser alocado todo de uma vez. At� mesmo
 * compartilhado entre processos.
 *
 * Sobre o heap de processo:
 *    Uma vari�vel global indica qual � o Heap do processo atual. 
 *    A estrutura de um processo cont�m informa��es sobre o seu Heap.
 *    ... 
 *
 * @todo: Criar: 
 * Criar uma fun��o que aloca mem�ria no heap de um processo. Deve-se usar 
 * o heap do desktop ao qual o processo pertence ou o heap do processo.
 * 
 * Obs: Poss�veis organiza��es de Heap: 
 *     + Heap Size Modifier, (HSM).
 *     + Heap Size Checker, (HSC). 
 *     + Desktop Heap Size Manager, (DHSM). 
 *       Gerencia o Heap alocado para cada desktop. Os programas usam o Heap
 * do seu pr�prio desktop. Alguns desktops podem ter Heaps pequenos.
 * @todo: Criar o arquivo heap.c para as rotinas de ger�ncia de heap.
 * Continua...
 *
 * Obs: Um processo pode criar um heap privado, que ele usar� para aloca��o 
 * din�mica.
 *      
 *
 * In this file:
 * =============
 *     +get_process_heap_pointer
 *     +SetKernelHeap
 *     +AllocateHeap
 *     +FreeHeap
 *     +AllocateHeapEx
 *     +show_memory_structs
 *     +init_heap
 *     +init_stack
 *     +init_mm
 *
 *
 * @todo: Criar: heapGetPointer, heapSePointer.
 *
 * Hist�rico:
 *     Vers�o 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *     Vers�o 1.0, 2016 - Aprimoramento geral das rotinas b�sicas.
 *     ...
 */

 
#include <kernel.h>
 
 
//Vari�veis internas. 

//int mmStatus;
unsigned long last_valid;         //�ltimo heap pointer v�lido. 
unsigned long last_size;          //�ltimo tamanho alocado.
unsigned long mm_prev_pointer;    //Endere�o da �ntima estrutura alocada.



/*
 * memsize: 
 *     Testando manualmente o tamanho da mem�ria.
 *     ## Adaptado de SANOS - Michael Ringgaard.
 *     @todo: Corrigir o asm inline. usar padr�o gcc.
 *
 */

/* 
unsigned long memsize();  
unsigned long memsize() 
{
    volatile unsigned long *mem;
  unsigned long addr;
  unsigned long value;
  unsigned long cr0save;
  unsigned long cr0new;

  // Start at 1MB
  addr = 1024 * 1024;

  // Save a copy of CR0
  __asm { mov eax, cr0 };
  __asm { mov [cr0save], eax };

  // Invalidate the cache (write-back and invalidate the cache)
  __asm { wbinvd };

  // Plug cr0 with just PE/CD/NW (cache disable(486+), no-writeback(486+), 32bit mode(386+))
  cr0new = cr0save | 0x00000001 | 0x40000000 | 0x20000000;
  __asm { mov eax, [cr0new] };
  __asm { mov cr0, eax };

  //Probe for each megabyte
  
    while(addr < 0xFFF00000){
		
        addr += 1024 * 1024;
        mem = (unsigned long *) addr;

        value = *mem;
        *mem = 0x55AA55AA;

        if(*mem != 0x55AA55AA) break;

        *mem = 0xAA55AA55;
        if(*mem != 0xAA55AA55) break;

        *mem = value;  //corrige.
    };

  //Restore 
  
  __asm { mov eax, [cr0save] };
  __asm { mov cr0, eax };

  return addr;
}
*/

/*
 Traduz um endere�o virtual em um endere�o f�sico.
unsigned long memoryGetPhysicalAddress( unsigned long virtual_address);
unsigned long memoryGetPhysicalAddress( unsigned long virtual_address){
	//return (unsigned long) ;
}
*/

/*
unsigned long heap_set_new_handler( unsigned long address );
unsigned long heap_set_new_handler( unsigned long address )
{
    unsigned long Old;

    Old = kernel_heap_start;
    
    kernel_heap_start = address;

    return (Old);
};
*/


/*
 * get_process_heap_pointer:
 *     Pega o heap pointer do heap de um processo.
 *     Pega o endere�o do in�cio do header da pr�xima aloca��o.
 */
unsigned long get_process_heap_pointer(int pid)
{
	unsigned long heapLimit;
	struct process_d *P;
	
	
	if(pid < 0){
		return 0;
	};
	
	P = (void*) processList[pid];
	
	if((void*) P == NULL ){
	    return 0;	
	};
	
	
	//
	// Limits:
	//     Cada processo tem uma �rea onde ele pode alocar mem�ria, os 
    // processos usam seu pr�prio heap ou o heap do desktop ao qual pertencem.
    // Os limites devem ser respeitados.	
	//
	
	heapLimit = (unsigned long) (P->Heap + P->HeapSize);
	
	//Se for menor que o in�cio ou maior que o limite.
	if( P->HeapPointer < P->Heap || P->HeapPointer >= heapLimit ){
		return 0;
	};
	
done:
    //Retorna o heap pointer do processo. 
	return (unsigned long) P->HeapPointer;
};



/*
 * SetKernelHeap:
 *    Configura o heap do kernel.
 *    Reconfigura��o total do heao do kernel.
 *    @todo: Salvar em estrutura de processo. O kernel tem seu processo.
 */
void SetKernelHeap( unsigned long HeapStart, unsigned long HeapSize)
{
	struct heap_d *h;    //Kernel Heap struct.    
	
	
	//
	// Check limits.
	//
	
	//if(HeapStart == 0){}
	//if(HeapSize == 0){}	
	
	//start, end, pointer, available.    
	
	kernel_heap_start = (unsigned long) HeapStart;                 
	kernel_heap_end   = (unsigned long) (HeapStart + HeapSize);
	g_heap_pointer    = (unsigned long) kernel_heap_start;            
	g_available_heap  = (unsigned long) (kernel_heap_end - kernel_heap_start); 
	
	//A estrutura fica no in�cio do heap.??!!
	h = (void*) kernel_heap_start;
	
	//Configurando a estrutura.
	h->HeapStart     = (unsigned long) kernel_heap_start;             
	h->HeapEnd       = (unsigned long) kernel_heap_end;
	h->HeapPointer   = (unsigned long) g_heap_pointer;            
	h->AvailableHeap = (unsigned long) g_available_heap; 	
	
	
	//
	// Configura a estrutura global que guarda informa��es sobre o heap do kernel.
	//
	
	KernelHeap = (void*) h;
	
	//
	// Lista de heaps.
	//
	
	//Configura��o inicial da lista de heaps. S� temos 'um' ainda.
	heapList[0] = (unsigned long) KernelHeap; //Configura o heap do kernel.
	heapList[1] = (unsigned long) 0;
	heapList[2] = (unsigned long) 0;
	//...
	
	//Contagem? ainda em zero.?!
	
done:	
	return;
};



/*
//@todo: Criar essa rotina.
//Aloca mem�ria dentro de um heap determinado.
//Esse rotina deve ser oferecida como servi�o. e chamada via system call.
void* HeapAlloc(struct heap_d * heap, unsigned long size);
void* HeapAlloc(struct heap_d * heap, unsigned long size)
{
	return (void*) ...;
}
*/

/*
 @todo:
 Retorna um ponteiro para o heap de um processo.
 oferecer como servi�o do sistema.
void *GetProcessHeap(struct process_d *process);
void *GetProcessHeap(struct process_d *process)
{
	return NULL;
}
*/

/*
 @todo:
 Retorna um ponteiro para o heap do processo atual.
 oferecer como servi�o do sistema.
void *GetHeap();
void *GetHeap()
{
	return NULL;
}
*/



/*
 * AllocateHeap:
 *     Aloca mem�ria no heap do kernel.
 *
 * *IMPORTANTE: Aloca BLOCOS de mem�ria dentro do heap do processo Kernel.
 *
 * Obs: A estrutura usada aqui � salva onde ??
 *
 * @todo: 
 *     Ao fim dessa rotina, os valores da estrutura devem ser armazenas no 
 * header, l� onde foi alocado espa�o para o header, assim tem-se informa��es 
 * sobre o header alocado.
 *  A estrutura header do heap, � uma estrutura e deve ficar antes da 
 *  �rea desejada. partes={header,client,footer}.
 *
 * @todo: Essa rotina poderia se chamar KernelHeapAlloc(unsigned long size)
 *
 * 2015 - Created.
 * sep 2016 - Revision.
 * ...
 */
unsigned long AllocateHeap(unsigned long size)
{
	struct mmblock_d *Current;	
	//struct mmblock_d *Prev;		
	
	//
	// Se n�o h� heap dispon�vel, n�o h� muito o que fazer.
	//
	
	// Available heap.
	if(g_available_heap == 0)
	{
	    //
		// @todo: Tentar crescer o heap para atender o size requisitado.
		//
		
		//try_grow_heap() ...
		
		//
		// @todo: Aqui poderia parar o sistema e mostrar essa mensagem.
		//
		
	    printf("AllocateHeap fail: g_available_heap={0}\n");
        refresh_screen();		
        return (unsigned long) 0;
		//while(1){};
	};
	
	//
    // Size limits. (Min, max).
    //
 	
	//Se o tamanho desejado � igual a zero.
    if(size == 0){
	    printf("AllocateHeap error: size={0}\n");
		refresh_screen();
		return (unsigned long) g_heap_pointer;
	};
	
	//Se o tamanho desejado � maior ou igual ao espa�o dispon�vel.
	if(size >= g_available_heap)
	{
	    //
		// @todo: Tentar crescer o heap para atender o size requisitado.
		//

		//try_grow_heap() ...

		printf("AllocateHeap error: size >= g_available_heap\n");
		refresh_screen();
		return (unsigned long) 0;
	};
    
	//Salvando o tamanho desejado.
	last_size = (unsigned long) size;
	
	//
	// Contador de blocos.
	//
	
try_again:	

    mmblockCount++;  
    
	if( mmblockCount >= MMBLOCK_COUNT_MAX ){
        printf("AllocateHeap Error: mmblockCount limits!");
		refresh_screen();
		while(1){};
    };
	
    //Identificadores.	
	
	//
	// O Header do header do bloco � o inicio da estrutura que o define. (h�???)
	//

	//
	// Pointer Limits. 
	// (N�o vamos querer um heap pointer fora dos limites do heap do kernel)
	//
	
	//
	// Se o 'g_heap_pointer' atual esta fora dos limites do heap, ent�o 
	// devemos usar o �ltimo v�lido que provavelmente est� nos limites.
	//
	
	if( g_heap_pointer < KERNEL_HEAP_START || 
	    g_heap_pointer >= KERNEL_HEAP_END )
	{
	    //Checa os limites o �ltimo last heap pointer v�lido.
	    if( last_valid < KERNEL_HEAP_START || 
		    last_valid >= KERNEL_HEAP_END )
		{
            printf("AllocateHeap Error: last valid heap pointer limits");
		    refresh_screen();
		    while(1){}		
	    };
		//Havendo um last heap pointer v�lido.
		//?? isso n�o faz sentido.
		g_heap_pointer = (unsigned long) last_valid + last_size;
		goto try_again;
	};
	

    //
	// Agora temos um 'g_heap_pointer' v�lido, salvaremos ele.
	// 'last_valid' N�O � global. Fica nesse arquivo.
	//
	
	last_valid = (unsigned long) g_heap_pointer;
	
	//
	// Criando um bloco.
	//
	
	//
	// Estrutura mmblock_d interna.
	// Configurando a estrutura para o bloco atual.
	//
	
    //	
	// Obs: A estutura dever� ficar l� no espa�o reservado para o header. 
	// (antes da area alocada).
	// Current = (void*) g_heap_pointer;
    //		
	
	//O endere�o do ponteiro da estrutura ser� o pointer do heap.
	Current = (void*) g_heap_pointer;    
	
	if( (void*) Current != NULL )
	{
	    Current->Header = (unsigned long) g_heap_pointer;  //Endere�o onde come�a o header.
	    Current->headerSize = MMBLOCK_HEADER_SIZE;         //Tamanho do header. TAMANHO DA STRUCT.  
        Current->Id = mmblockCount;                        //Id do mmblock.
	    Current->Used = 1;                //Flag, 'sendo Usado' ou 'livre'.
	    Current->Magic = 1234;            //Magic number. Ver se n�o est� corrompido.
        Current->Free = 0;                //not free.
	    //Continua...		
	
	    //
	    // Mensuradores. (tamanhos) (@todo:)
	    //
	
	    //
	    // @todo:
	    // Tamanho da �rea reservada para o cliente.
	    // userareaSize = (request size + unused bytes)
	    // Zera unused bytes, j� que n�o foi calculado.
	    //	

        //
	    // User Area base:
	    // Onde come�a a �rea solicitada. Isso fica logo depois do header.
	    //
	
	    Current->userArea = (unsigned long) Current->Header + Current->headerSize;    

	    //
	    // Footer:
        // O footer come�a no 'endere�o do in�cio da �rea de cliente' + 'o tamanho dela'.
	    // O footer � o fim dessa aloca��o e in�cio da pr�xima.
	    //
	
	    Current->Footer = (unsigned long) Current->userArea + size;
	
	    //
	    // Heap pointer. 
	    //     Atualiza o endere�o onde vai ser a pr�xima aloca��o.
	    //
	
	    //if ( Current->Footer < KERNEL_HEAP_START){
	    //    Current->Used = 0;                //Flag, 'sendo Usado' ou 'livre'.
	    //    Current->Magic = 0;            //Magic number. Ver se n�o est� corrompido.	    
	    //	goto try_again;	
	    //}
	
        
		//
		// Obs: O limite da contagem de blocos foi checado acima.
		//
		
	    //
	    // Coloca o ponteiro na lista de blocos.
	    //
	
	    mmblockList[mmblockCount] = (unsigned long) Current;
	
	    //
		// Salva o ponteiro do bloco usado como 'pr�vio'.
	    // Obs: 'mm_prev_pointer' n�o � global, fica nesse arquivo.
	    //
		
		mm_prev_pointer  = (unsigned long) g_heap_pointer; 
	
	    //
		// *IMPORTANTE.
	    // Atualiza o ponteiro. Deve ser onde termina o �ltimo bloco 
		// configurado.
	    //
		
		g_heap_pointer = (unsigned long) Current->Footer;	

	
	    //
	    // Available heap:
	    // Calcula o valor de heap dispon�vel para as pr�ximas aloca��es.
	    //
	
	    g_available_heap = (unsigned long) g_available_heap - (Current->Footer - Current->Header);		
	
	    //
	    // Retorna o ponteiro para o in�cio da �rea alocada.
		// Obs: Esse � o valor que ser� usado pela fun��o malloc.
		//
		
		return (unsigned long) Current->userArea;
		//Nothing.
		
	}else{
		
	    //Se o ponteiro da estrutura de mmblock for inv�lido.
		
		printf("AllocateHeap fail: struct.\n");
		//@todo: Deveria retornar.
		//goto fail;
		return (unsigned long) 0;
	};
	

	//
	// @todo: 
	// Checar novamente aqui o heap dispon�vel. Se esgotou, tentar crescer.
	//
	

    /*
	 * *IMPORTANTE
	 *
	 * @todo:
	 * Colocar o conte�do da estrutura no lugar alocado para o header.
	 * O header conter� informa��es sobre o heap.
	 *
	 */
	
	
	
	/* errado #bugbug.
	Prev = (void*) mm_prev_pointer;
	
	if( (void*) Prev != NULL)
	{
	    if( Prev->Used == 1 && 
		    Prev->Magic == 1234 && 
			Prev->Free == 0)
		{
		    Current->Prev = (void*) Prev;
            Prev->Next = (void*) Current;			
		};		
	};
	*/
	
	
//
// Fail.
//	
fail:
    //Se falhamos, retorna 0. Que equivaler� � NULL.
    return (unsigned long) 0;	
};



/*
 * FreeHeap:
 * @todo: Implementar essa fun��o.
 * Objetivo: Liberar o bloco de mem�ria, configurando a sua estrutura.
 * Libera mem�ria.
 * O argumento � a diferen�a entra o ponteiro antigo e o novo ponteiro 
 * desejado. 
 * Ponteiros do in�cio da �rea do cliente.
 * ??
 */
unsigned long FreeHeap(unsigned long size){  		
	return (unsigned long) g_heap_pointer;    //#cancelada!
};


/*
 * AllocateHeapEx:
 *     Aloca heap.
 *     @todo: Fun��o imcompleta.
 *     Poderia chamar a fun��o AllocateHeap.
 */
void *AllocateHeapEx(unsigned long size){
	return (void *) AllocateHeap(size);  //suspensa.
};


/*
 * show_memory_structs:
 *     Mostra as informa��es das estruturas de mem�ria. 
 * @todo: 
 *     Mostrar a mem�ria usada pelos processos.
 *     Mostrar o quanto de mem�ria o processo usa.
 *
 */
void show_memory_structs()
{
	int i = 0;
    struct mmblock_d *B;	
	
	// Title.
	printf("Memory Block Information:\n\n");
	//printf("=========================\n");
	
	//Mostra os heap da lista.		
	while(i < MMBLOCK_COUNT_MAX) 
	{
        B = (void*) mmblockList[i];
		++i;
		
		if( (void*) B != NULL )
		{
			//Validade.
		    if( B->Used == 1 && B->Magic == 1234){
		        printf("Id={%d} Header={%x} userA={%x} Footer{%x}\n",B->Id
		                                                            ,B->Header
				                                                    ,B->userArea
				                                                    ,B->Footer );
			};
			//Nothing.
		};
		//Nothing.
    };
	
	//More?!
	
//
// Done.
//	
done:
    printf("Done\n");
	return;
};




/*
 * init_heap:
 *     Iniciar a ger�ncia de Heap do kernel. 
 *     @todo: Usar heapInit() ou heapHeap().
 */
int init_heap()
{
	//Internas.
	int i = 0;

    //Globals.	
	kernel_heap_start  = (unsigned long) KERNEL_HEAP_START;  
    kernel_heap_end    = (unsigned long) KERNEL_HEAP_END;  
	g_heap_pointer     = (unsigned long) kernel_heap_start;    //Heap Pointer.	
    g_available_heap   = (unsigned long) (kernel_heap_end - kernel_heap_start);    	// Available heap.
	heapCount = 0;      // Contador.
	
	//�ltimo heap pointer v�lido. (*IMPORTANTE)
	last_valid = (unsigned long) g_heap_pointer;
	last_size = 0;
	
	
	//Check Heap Pointer.
	if(g_heap_pointer == 0){
	    printf("init_heap fail: Heap pointer!\n");
		goto fail;
	};
	
	//Check Heap Pointer overflow.
	if(g_heap_pointer > kernel_heap_end){
        printf("init_heap fail: Heap Pointer Overflow!\n");
		goto fail;
    };	
	
    //Heap Start.
	if(kernel_heap_start == 0){
	    printf("init_heap fail: HeapStart={%x}\n" ,kernel_heap_start);
	    goto fail;
	};
	
	//Heap End.
	if(kernel_heap_end == 0){
	    printf("init_heap fail: HeapEnd={%x}\n" ,kernel_heap_end);
	    goto fail;
	};
	
	//Check available heap.
	if(g_available_heap == 0)
	{
	    //@todo: Tentar crescer o heap.
		
		printf("init_heap fail: Available heap!\n");
		goto fail;
	};
	
	// Heap list ~ Inicializa a lista de heaps.
	while(i < HEAP_COUNT_MAX){
        heapList[i] = (unsigned long) 0;
		++i;
    };
	
	
	//KernelHeap = (void*) x??;
	
	//More?!
	
// Done.
done:
    printf("Done.\n");	
	return (int) 0;
// Fail. Falha ao iniciar o heap do kernel.
fail:
    printf("init_heap: Fail!\n");
	
	/*
	printf("* Debug: %x %x %x %x \n", kernel_heap_start, 
	                                  kernel_heap_end,
									  kernel_stack_start,
									  kernel_stack_end);	
	refresh_screen();	 
    while(1){}		
	*/
    
	return (int) 1;
};


/*
 * init_stack:
 *     Iniciar a ger�ncia de Stack do kernel. 
 *     @todo Usar stackInit(). 
 *
 */
int init_stack()
{
    //Globals.
	kernel_stack_end   = (unsigned long) KERNEL_STACK_END; 
	kernel_stack_start = (unsigned long) KERNEL_STACK_START; 
	
    //End.
	if(kernel_stack_end == 0){
	    printf("init_stack fail: StackEnd={%x}\n" ,kernel_stack_end);
	    goto fail;
	};
	
	//Start.
	if(kernel_stack_start == 0){
	    printf("init_stack fail: StackStart={%x}\n" ,kernel_stack_start);
	    goto fail;
	};
	//Nothing.
done:
    return (int) 0;
fail:
    return (int) 1;
};


/*
 * init_mm:
 *   Inicializa o memory manager.
 *    @todo: Usar mmInit().
 */
int init_mm()
{	
    int Status = 0;
	int i = 0;	
	
	//
	// @todo: 
	// Inicializar algumas vari�veis globais.
	// Chamar os construtores para inicializar o b�sico.
	//
	
	//
	// @todo: 
	// Clear BSS.
	// Criar mmClearBSS()
	//
	//
	
	//Heap.
	Status = (int) init_heap();
	if(Status != 0){
	    printf("init_mm fail: Heap.\n");
	    return (int) 1;
	};	
	
	//Stack.
	Status = (int) init_stack();
	if(Status != 0){
	    printf("init_mm fail: Stack.\n");
	    return (int) 1;
	};		
	
	//Lista de blocos de mem�ria dentro do heap do kernel.
	while(i < MMBLOCK_COUNT_MAX){
        mmblockList[i] = (unsigned long) 0;
		++i;
    };
	
	//Primeiro Bloco.
    //current_mmblock = (void *) NULL;
	
	//
	// Continua...
	//
	
done:	
    return (int) Status;	
}; 


/*
int mmInit()
{
    //...	
}
*/

//
//fim.
//
