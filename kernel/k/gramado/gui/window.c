/*
 * File: window.c 
 *
 * Descri��o:
 *     Arquivo principal do Window Manager.
 *     Window Manager.
 *     MB - M�dulos inclu�dos no Kernel Base.
 *     Rotinas envolvendo a feitura de janelas.     
 *     Parte da interface gr�fica oferecida em Kernel Mode.
 *     A interface gr�fica oferecida pelo Kernel Base deve ser leve e veloz.
 *
 * Obs: Muitas funcionalidades devem ser iplementadas em user mode e n�o aqui.
 *      aqui devem ficar as fun��es mais primitivas. e outras pra ganhar desempenho
 *      mas n�o tudo. 
 *
 * @todo: Criar uma fun��o que copie o conte�do de um buffer dedicado de janela para
 * o LFB,(FrontBuffer).
 *       
 * In this file:
 * ============
 * +
 * +
 * +
 *
 *
 *
 * Hist�rico:
 *     Vers�o: 1.0, 2013 - Esse arquivo foi criado por Fred Nora.
 *     Vers�o: 1.0, 2014 - Aprimoramento geral das rotinas b�sicas. 
 *     Vers�o: 1.0, 2015 - Revis�o. 
 *     Vers�o: 1.0, 2016 - Revis�o.
 *     ...
 */

 
#include <kernel.h>
 
 
 
// 
// Argumentos passados pelo Boot Loader em head.s. 
//

extern unsigned long kArg1;    //Video Mode.	
extern unsigned long kArg2;	   //LFB - Linear Frame Buffer.
extern unsigned long kArg3;	   //??.
extern unsigned long kArg4;	   //??.	



/*
int windowShowWindow(struct window_s *window);
int windowShowWindow(struct window_s *window)
{
	int Status;
	
	if( (void*) window == NULL ){
		return (int) 1;
	};
	
	//@todo: Copiar o conteudo do buffer dedicado para o frontbuffer.
	
	//na estrutura de janela:
	//a vari�vel dedicatedbuffer precisa estar correta.
	//a vari�vel frontbuffer precisa estar correta.
	
	return (int) Status;
}
*/



/*
 * windowSetParent:
 * Atribui uma nova janela mae � uma dada janela filha.
 */
/*
void *windowSetParent(struct window_t *clild, struct window_d *new_parent);
void *windowSetParent(struct window_t *clild, struct window_d *new_parent)
{
	//@implementar.
	//Obs: Se o par�metro new_parent for NULL ent�o a janela principal (main ou desktop) 
	//ser� a nova janela mae.
	return NULL;
}
*/

/*
 * windowIsWindow:
 *     Testa atrav�s do handle passado, se � uma janela ou n�o.
 *     0 = Yes; 1 = Not; 
 */
/* 
int windowIsWindow(struct window_d *window);
int windowIsWindow(struct window_d *window)
{
	//@todo:Implementar.
	return 0;
};
*/

/*
void* windowGetWindowWithFocus();
void* windowGetWindowWithFocus()
{
	return (void*) WindowWithFocus;
}
*/


//isso configura o esquema de cores a ser utilizado pelo sistema.
//o esquema de cores a ser utilizado deve estar salvo no perfil
//do usu�rio que fez o logon.

void windowSetUpColorScheme()
{
	//Por enquanto, estamos fazendo o b�sico.
	
	
    struct color_scheme_d *humility;
    struct color_scheme_d *pride;	
	
    //Criando o esquema de cores humility. (cinza)
    humility = (void*) malloc( sizeof(struct color_scheme_d) );
    if( (void*) humility == NULL ){
		printf("windowSetUpColorScheme: humility");
		refresh_screen();
		while(1){}
	}else{
		
		//Object.
		humility->objectType = ObjectTypeColorScheme;
		humility->objectClass = ObjectClassGuiObjects;
		

		humility->used = 1;
		humility->magic = 1234;
		
		humility->name = "Humility";
		
		humility->elements[csiNull] = 0;
        humility->elements[csiDesktop] = COLOR_BACKGROUND;		
		humility->elements[csiWindow] = COLOR_WINDOW;
        humility->elements[csiWindowBackground] = COLOR_WINDOW;		
		humility->elements[csiActiveWindowBorder] = 0x00FFFF00;
        humility->elements[csiInactiveWindowBorder] = 0x00FFFF00;		
		humility->elements[csiActiveWindowTitleBar] = COLOR_BLACK;
        humility->elements[csiInactiveWindowTitleBar] = COLOR_GRAY;		
		humility->elements[csiMenuBar] = COLOR_MENUBAR;
        humility->elements[csiScrollBar] = COLOR_GRAY;		
		humility->elements[csiStatusBar] = COLOR_STATUSBAR;
        humility->elements[csiMessageBox] = COLOR_GRAY;		
		//...
		
		HumilityColorScheme = (void*) humility;
	};	
	
	
    //Criando o esquema de cores PRIDE. (colorido)
    pride = (void*) malloc( sizeof(struct color_scheme_d) );
    if( (void*) pride == NULL ){
		printf("windowSetUpColorScheme: pride");
		refresh_screen();
		while(1){}
	}else{
		
		//Object.
		pride->objectType = ObjectTypeColorScheme;
		pride->objectClass = ObjectClassGuiObjects;
		

		pride->used = 1;
		pride->magic = 1234;
		
		pride->name = "Pride";
		
		pride->elements[csiNull] = 0;
        pride->elements[csiDesktop] = COLOR_TEST_0;		
		pride->elements[csiWindow] = COLOR_TEST_2;
        pride->elements[csiWindowBackground] = COLOR_WINDOW;		
		pride->elements[csiActiveWindowBorder] = 0x00FFFF00;
        pride->elements[csiInactiveWindowBorder] = 0x00FFFF00;		
		pride->elements[csiActiveWindowTitleBar] = COLOR_TEST_9;
        pride->elements[csiInactiveWindowTitleBar] = COLOR_TEST_10;		
		pride->elements[csiMenuBar] = COLOR_TEST_4;
        pride->elements[csiScrollBar] = COLOR_TEST_12;		
		pride->elements[csiStatusBar] = COLOR_STATUSBAR;
        pride->elements[csiMessageBox] = COLOR_GRAY;		
		//...
		
		PrideColorScheme = (void*) pride;
	};	
		
	
	// Set current.
	CurrentColorScheme = (void*) humility; 
	
done:	
	return;
}

/*
 * windowShowWWFMessageBuffers:
 *     Mostra o buffer de mensagens da janela com foco de entrada.
 *     #Rotinas de teste. @todo: Enviar para a pasta /test.
 *     Esse rotina funcionou e se mostrou bem �til.
 */
void windowShowWWFMessageBuffers()
{
	struct window_d *wFocus;
    wFocus = (void *) WindowWithFocus;

	int i;
	//Obs: Tipo.
	for( i=0; i<32; i++){
	    printf("%d ", wFocus->msgList[i]);
    };
    return;	
}

/*
 * windowSendMessage:
 *    Uma mensagem deve ser enviada para a estrutura da janela com o foco de entrada.
 *    A classe system.devices.unblocked. pois essa rotina � um m�todo dela.
 *
 * Sobre a fila de mensagem da janela com o foco de entrada:
 * ========================================================
 *  *IMPORTANTE: 
 *      O que importa � qual janela est� com o foco de entrada.
 *      Quando sabemos qual janela est� com o foco de entrada, ent�o
 * sabemos qual � a janela que � a �rea de cliente, sabemos e provavelmente
 * a sua janela m�e � a janela ativa, se ela mesma n�o for a janela ativa.
 *      Uma mensagem pode ser enviada para a janela com o foco de entrada,
 * e a mensagem afetar� apenas a janela com o foco de entrada.
 *      Se a janela que receber a mensagem for a janela ativa, ela n�o
 * ter� janela m�e, nessa caso uma mensagem para fechar uma janela ativa
 * implica em fechar o processo ao qual ela est� vinculada.
 *      (N�o importa qual processo foi interrompido pela interrup��o de 
 * teclado. A mensagem deve ir para a fila de mensagens da janela com o foco
 * de entrada.)
 * @todo: Criar uma rotina semelhante, mas exclusivamente para a janela com foco de entrada.
 * Ex: void windowSendMessageWWW(unsigned long arg1, unsigned long arg2, unsigned long arg3, unsigned long arg4)
 */	
void windowSendMessage(unsigned long arg1, unsigned long arg2, unsigned long arg3, unsigned long arg4)
{    
	struct window_d *wFocus;
		
	
    //
	// lembrando: O arg1 por enquanto ser� ignorado ;;; ele deveria 
	//conter a janela que devemos enviar a mensagem...
	// pegaremos por conta pr�pria o penteiro pra janela com o foco de entrada.
	//
	
	//
    // N�o estamos falando de fila de mensagens na estrutura da janela,
	// portando se uma mensagem for enviada para uma estrutura de janela
	// ela ir� sobrepor a mensagem antiga caso a mensagem antiga ainda n�o 
	// tenha sido consumida.
    //	
		
	//
	// @todo: 
	// Na verdade, aqui tem que mandar a mensagem para a janela com o foco 
	// de entrada, mesmo que seja uma janela filha.
	//
		
	//lenbrando que esse � um endere�o f�sico, o m�nimo que uma rotina em user mode deve fazer 
    //com essa informa��o � converte-la em endere�o l�gico.
    //Ou devemos enviar um endere�o l�gico ??	
	wFocus = (void *) WindowWithFocus;
	
	// Aqui estamos apenas enviando para a janela com foco de entrada.
	// N�o fazer nada caso n�o haja uma janela com o foco de entrada, 
	// pois quem decide que janela tem o foco de entrada � o usu�rio.
		
	if( (void*) wFocus == NULL )
	{
		printf("windowSendMessage: wFocus fail\n");
		refresh_screen();
	    return;
	}else{
		
		//Valida a estrutura da janela com o foco de entrada.
		if( wFocus->used == 1 && wFocus->magic == 1234 )
		{
            //nesse momento podemos mostrar o nome da janela com o foco de entrada.
			//printf("windowSendMessage: focus={%s}\n",wFocus->name);
              			
            
			wFocus->sendOffset = 0; 
			
			//Trata o deslocamento atual para as filas.
			//wFocus->sendOffset++;
			//if(wFocus->sendOffset >= 32){ 
			//    wFocus->sendOffset = 0; 
			//};
	        
			//Envia cada mensagem pra sua fila apropriada.
			wFocus->hwndList[wFocus->sendOffset]  = (unsigned long) 0;//WindowWithFocus; //arg1;
			wFocus->msgList[wFocus->sendOffset]   = (unsigned long) arg2;  //msg.
			wFocus->long1List[wFocus->sendOffset] = (unsigned long) arg3;  //long1
			wFocus->long2List[wFocus->sendOffset] = (unsigned long) arg4;  //long2
			
			
			//isso � um teste.
			//Para facilitar vamos colocar a mensagem num lugar mais acessivel.
			gNextKeyboardMessage = (int) 0;
			
		}else{
			//fail.
		};
          		
	};
	
	return;
}


/*
 * windowGetMessage:
 *     Pega uma mensagem na estrutura da janela com o foco de entrada.
 *
 * Obs: 
 *     Esse mecanismo deve ser reproduzido para os parametros hwnd, long1 e long2.
 *     As fun��es precisam ser criadas ainda. semelhantes a essa.
 *     Mas o que nos importa agora � somente o par�metro 'msg'.
 * @todo: Quem chamou essa rotina, deseja pegar a mensagem de qualquer janela 
 *ou somente a da janela com o foco de entreada.???
 * @todo: Criar uma rotina semelhante, mas exclusivamente para a janela com foco de entrada.
 * Ex: void *windowGetMessageWWF()
 */
void *windowGetMessage(struct window_d *window)
{
	void *kMSG;
	
	struct window_d *wFocus;
	
	
	//
	// teste
	//
	//isso n�o ficar� assim, � s� para testar se um app em user mode 
	//consegue pegar alguma mensagem atravez dessa rotina.
	
	//int tmp;
	//if( gNextKeyboardMessage != 0)
	//{
	//	tmp = gNextKeyboardMessage;
    //    gNextKeyboardMessage = (int) 0;  		
	//	return (void *) tmp; 
	//};
	
	//Pega o ponteiro da janela com o foco de entrada.
	wFocus = (void *) WindowWithFocus;
	
	//Desejamos usar a janela com o foco de entrada.
	if(  (void*) window != (void*) wFocus  )
	{
		printf("windowGetMessage: window != wFocus \n");
		refresh_screen();		
		window = (void*) wFocus;
	};
	
	
	//Testando a validade.
	if((void*) window == NULL)
	{ 
		printf("windowGetMessage: window fail \n");
		refresh_screen();		
	    return NULL; 
	}else{	

			//isso exibiria muitas mensagens por causa do while.
			//printf("windowGetMessage: focus={%s}\n",wFocus->name);	
		
		//
		// @todo: Quando pegar a mensagem no buffer, tem que colocar 
		// zero no lugar, pra n�o pegar novamente.
		//
		
		window->receiveOffset = 0;
				
		// N�o mudaremos o offset do receive ante de tentarmos pegar.
		//Circula.
		//if(window->receiveOffset >= 32){
		//	window->receiveOffset = 0;
		//};
				
		//Pega mensagem.
		kMSG = (void*) window->msgList[window->receiveOffset]; 
				
		//Apaga a mensagem que foi consumida.
		window->msgList[window->receiveOffset] = 0; 
		
        //Incrementamos o offset para a pr�xima vez.
		//window->receiveOffset++;  		
		
		//Retorna.
		return (void*) kMSG; 
	};
	//Nothing.
fail:	
	return NULL;
};


void *windowGetLong1(struct window_d *window)
{
	void *kLONG1;
	
	struct window_d *wFocus;
	
	
	//
	// teste
	//
	//isso n�o ficar� assim, � s� para testar se um app em user mode 
	//consegue pegar alguma mensagem atravez dessa rotina.
	
	//int tmp;
	//if( gNextKeyboardMessage != 0)
	//{
	//	tmp = gNextKeyboardMessage;
    //    gNextKeyboardMessage = (int) 0;  		
	//	return (void *) tmp; 
	//};
	
	//Pega o ponteiro da janela com o foco de entrada.
	wFocus = (void *) WindowWithFocus;
	
	//Desejamos usar a janela com o foco de entrada.
	if(  (void*) window != (void*) wFocus  )
	{
		printf("windowGetLong1: window != wFocus \n");
		refresh_screen();		
		window = (void*) wFocus;
	};
	
	
	//Testando a validade.
	if((void*) window == NULL)
	{ 
		printf("windowGetLong1: window fail \n");
		refresh_screen();		
	    return NULL; 
	}else{	

			//isso exibiria muitas mensagens por causa do while.
			//printf("windowGetMessage: focus={%s}\n",wFocus->name);	
		
		//
		// @todo: Quando pegar a mensagem no buffer, tem que colocar 
		// zero no lugar, pra n�o pegar novamente.
		//
		
		window->receiveOffset = 0;
				
		// N�o mudaremos o offset do receive ante de tentarmos pegar.
		//Circula.
		//if(window->receiveOffset >= 32){
		//	window->receiveOffset = 0;
		//};
				
		//Pega mensagem.
		kLONG1 = (void*) window->long1List[window->receiveOffset]; 
				
		//Apaga a mensagem que foi consumida.
		window->long1List[window->receiveOffset] = 0; 
		
        //Incrementamos o offset para a pr�xima vez.
		//window->receiveOffset++;  		
		
		//Retorna.
		return (void*) kLONG1; 
	};
	//Nothing.
fail:	
	return NULL;
};



void *windowGetLong2(struct window_d *window)
{
	void *kLONG2;
	
	struct window_d *wFocus;
	
	
	//
	// teste
	//
	//isso n�o ficar� assim, � s� para testar se um app em user mode 
	//consegue pegar alguma mensagem atravez dessa rotina.
	
	//int tmp;
	//if( gNextKeyboardMessage != 0)
	//{
	//	tmp = gNextKeyboardMessage;
    //    gNextKeyboardMessage = (int) 0;  		
	//	return (void *) tmp; 
	//};
	
	//Pega o ponteiro da janela com o foco de entrada.
	wFocus = (void *) WindowWithFocus;
	
	//Desejamos usar a janela com o foco de entrada.
	if(  (void*) window != (void*) wFocus  )
	{
		printf("windowGetLong2: window != wFocus \n");
		refresh_screen();		
		window = (void*) wFocus;
	};
	
	
	//Testando a validade.
	if((void*) window == NULL)
	{ 
		printf("windowGetLong2: window fail \n");
		refresh_screen();		
	    return NULL; 
	}else{	

			//isso exibiria muitas mensagens por causa do while.
			//printf("windowGetMessage: focus={%s}\n",wFocus->name);	
		
		//
		// @todo: Quando pegar a mensagem no buffer, tem que colocar 
		// zero no lugar, pra n�o pegar novamente.
		//
		
		window->receiveOffset = 0;
				
		// N�o mudaremos o offset do receive ante de tentarmos pegar.
		//Circula.
		//if(window->receiveOffset >= 32){
		//	window->receiveOffset = 0;
		//};
				
		//Pega mensagem.
		kLONG2 = (void*) window->long2List[window->receiveOffset]; 
				
		//Apaga a mensagem que foi consumida.
		window->long2List[window->receiveOffset] = 0; 
		
        //Incrementamos o offset para a pr�xima vez.
		//window->receiveOffset++;  		
		
		//Retorna.
		return (void*) kLONG2; 
	};
	//Nothing.
fail:	
	return NULL;
};



/*
 * windowCreateDedicatedBuffer: 
 * Cria um buffer dedicado de acordo com as dimens�es da janela.
 */
int windowCreateDedicatedBuffer(struct window_d *window) 
{
	size_t bufferSize;
	
	//Check;
	if((void*) window == NULL ){ 
	    return (int) 1;  //Fail. 
	};
	
    //
    // Buffer size.
    //
	
	//@todo: Usar vari�vel para quantidade de bytes por pixel.
	bufferSize = (size_t) (window->width * 3) + (window->height * 3);
	
	//
	// Alocando mem�ria no Heap do kernel.
	//
	
	if(bufferSize == 0){
	    return (int) 1;    //Fail.	
	}
	else
	{
	    window->DedicatedBuffer = (void*) malloc(bufferSize);	
	    if( (void*) window->DedicatedBuffer == NULL ){
		    return (int) 1;    //Fail.	
		}
		goto done;
	};
	//Nothing
done:
	return (int) 0;  //Success.
};

/*
 * windowLock:
 *     Bloqueia uma janela.
 *     @todo: Quem pode realizar essa opera��o??
 */
void windowLock(struct window_d *window)
{
    //Check.
	if( (void*) window == NULL ){
	    return;
    };  
    window->locked = (int) WINDOW_LOCKED;  //1.
    return;
};

/*
 * windowUnlock:
 *     Desbloqueia uma janela.
 *     @todo: Quem pode realizar essa opera��o??
 */
void windowUnlock(struct window_d *window)
{
    //Check.
	if( (void*) window == NULL ){
	    return;
    };  
    window->locked = (int) WINDOW_UNLOCKED;  //0.
    return;
};


/*
 * set_current_window:
 *     @todo: Mudar para windowSetCurrentWindow
 */
void set_current_window(struct window_d *window)
{
    //Check.
	if( (void*) window == NULL ){ return; };  
    
	CurrentWindow = (void*) window;
	current_window = (int) window->id;
    return;
};


/*
 * get_current_window: Get current window pointer.
 */
void *get_current_window(){
	return (void *) CurrentWindow;
};


/*
 * RegisterWindow: 
 *     Registrando uma janela numa lista de janelas.
 */
int RegisterWindow(struct window_d *window)
{
	int Offset = 0; 
    struct window_d *Empty; 
	
    if( (void*) window == NULL ){
        return (int) 1;    //Erro, estrutura inv�lida.
    };
   
	//
	// Contagem de janelas e limites.
	// (� diferente de id, pois id representa a posi��o
	// da janela na lista de janelas).
	//
	
	windows_count++;
	
	if(windows_count >= WINDOW_COUNT_MAX){
	    printf("RegisterWindow: Limits.");
		refresh_screen();
		while(1){}
	};
    
	// Create empty.	
	
//Loop.	
get_next:

	Offset++;
	
	//Limite da lista, volta ao in�cio da lista.
	if(Offset >= WINDOW_COUNT_MAX){
	   Offset = 0;
	};	
    
	//Get empty.
 	Empty = (void*) windowList[Offset]; 	
    if( (void*) Empty != NULL ){
        goto get_next;
    }else{
	    
		//coloca na lista.
		//Onde est� vazio, registra o ponteiro.
	    windowList[Offset] = (unsigned long) window; 	
		
		//configura o id.
		window->id = (int) Offset;
		
		//...
	};  		
	
done:
    return (int) 0;
};


/*
 * windowShowWindowList:
 *     Show Window List
 *     Mostra a lista de janelas registradas. 
 */
void windowShowWindowList()
{
	int i = 0;
	struct window_d *hWnd;
	struct window_d *hWindow;
	
	
	//Se n�o estivermos em modo gr�fico, n�o h� o que mostrar.	
    if(VideoBlock.useGui != 1){
	    return;	
	};
		
	//@todo: Chamar m�todo.	
	//Cursor.
	g_cursor_x = 0;
	g_cursor_y = 10; 
	//set_up_cursor(0,10);
	
	//
	// Se estamos no modo gr�fico.
	//
	
	if(VideoBlock.useGui == 1)
	{
		//Parent window.
	    if( (void*) gui->main == NULL){
	        return;
	    };
			
	    //Create.
	    hWindow = (void*) CreateWindow( 3, 0, VIEW_MAXIMIZED, "Window List:", 
	                                    (800 -320 -2), (600 -240 -2), 320, 240, 
			     				         gui->main, 0, COLOR_BLACK, COLOR_TEST_1 ); 

	    if( (void*) hWindow == NULL){
	        printf("show_window_list:\n");
		    return;
        }else{
		    RegisterWindow(hWindow);
			set_active_window(hWindow);
			SetFocus(hWindow);
	    };										
		
		
		// Auterando as margens.
		// Essas margens s�o usadas pela fun��o printf.
		// Obs: As medidas s�o feitas em n�meros de caracteres.
		// Obs: @todo: Devemos usar aqui o ret�ngulo da �rea de cliente,
		// e n�o as margens da janela.
		// A estrutura de janela deve nos oferecer os valores para a m�trica do 
		// ret�ngulo da �rea de cliente.
		
		g_cursor_left   = (hWindow->left/8);
		g_cursor_top    = (hWindow->top/8) + 4;   //Queremos o in�cio da �rea de clente.
		g_cursor_right  = g_cursor_left + (320/8);
		g_cursor_bottom = g_cursor_top  + (240/8);
		
		//cursor (0, mas com margem nova).
		g_cursor_x = g_cursor_left; 
		g_cursor_y = g_cursor_top; 
		
        //Mostrando as informa��es de todas as janelas registradas.		
        while(i < WINDOW_COUNT_MAX)
        {	
	        hWnd = (void*) windowList[i];
		
		    //
		    // @todo: BUGBUG.
		    // O valor de hWnd tem que estar num limite v�lido, n�o adianta apenas ser
		    // diferente de NULL.
		    //
		
		    if( (void*) hWnd != NULL )
			{
	            printf("i={%d} h={%x} dBuf={%x} Name={%s}\n", i, hWnd, hWnd->DedicatedBuffer, hWnd->name);
				//draw_text( hWindow, 8,  1*(400/16), COLOR_WINDOWTEXT, "F1 Help.");
	        };
		    ++i;
	    };
		
		show_active_window();
        show_window_with_focus();
        SetFocus(hWindow);
	
		
		//voltando a margem normal a margem
		g_cursor_left = 0;
		g_cursor_top =  0;
		g_cursor_right = 256;
		g_cursor_bottom = 256;
		
		//cursor (0, mas com margem nova)
		g_cursor_x = g_cursor_left; 
		g_cursor_y = g_cursor_top;
        //set_up_cursor(g_cursor_left,g_cursor_top); 		


		StatusBar(hWindow,"Esc=EXIT","Enter=?");		
	    //refresh_screen();    	
	    
		//Nothing.
		
		//return;
	};	
	    

    // Continua ...
	
done:
    //SetFocus(hWindow);
    return;
};



/*
 * redraw_window:
 *     #bugbug: Essa rotina est� errada !!!
 *     O OBJETICO DESSA ROTINA DEVE SER APENAS REPINTAR UM RET�NGULO
 * QUE FOI PINTADO DENTRO DA �REA DE CLIENTE DA JANELA QUE FOI PASSADA 
 * VIA ARGUMENTO. PORTANTO UM ARGUMENTO DE RET�NGULO TAMBEM DEVE SER OFERECIDO @TODO 
 * Obs: Esse ret�ngulo deve pertencer a janela que foi passada por argumento.
 * na estrutura de ret�ngulo deve haver um ponteiro para  ajanela � qual ele pertence.
 *
 *
 *
 *     Repinta uma janela de acordo com os par�metros na estrutura.
 *     Repinta uma janela v�lida. Tem que estar registrada. 
 *     @todo: Mudar para windowRedrawWindow(.)
 * Obs: Esse � o tipo de rotina que exige o recurso de buffer dedicado.
 * Pois podemos redezenhar a janela em seu buffer dedicado e depois copiar
 * o conte�do do buffer dedicado para o backbuffer... na hora de atualizar a tela
 * � so copiar o backbuffer no frontbuffer(LFB).
 * *** Na verdade eu n�o fa�o a menor ideia de como redezenhar uma janela...
 * Talvez essa fun��o deva ser igual a fun��o create, mas as caracter�sticas da 
 * janela s�o pegadas da estrutura de janela passada via argumento.
 * pois bem, essa janela vai ter muitos elementos para incluir isso leva muito tempo.
 * Devemos registrar na estrutura da janela todos os bot�es que ela tem.?? 
 * todos os textos gravados nela?? ... todas as cores??
 */
//int windowRedrawWindow(struct window_d *window) 
//int redraw_window(struct window_d *window, struct rect_d *rect)
int redraw_window(struct window_d *window)
{
	int Status;
 
 
	//Checar se a estrutura � v�lida.
	
	//handle
	if((void*) window == NULL){
		return (int) 1;
	};
	
	//used
	if( window->used != 1 ){
		return (int) 1;
	}
	
	//magic
	if( window->magic != 1234 ){
		return (int) 1;
	}
	
	//@todo: Pra que serva a flag redraw ??
	// � para indicar que repecisamos repintar. ??
	//if( window->redraw != 1 ){ return (int) 0;}
	
	//
	// Ok, pelo jeito temos uma estrutura v�lida.
	//
	
	// Minimized? Se tiver minimizada, n�o precisa repintar.
	Status = (int) is_window_minimized(window);
    if(Status == 1){
	    return (int) 1;
	};	
	
	//E se ela estiver travada ??
	// ?? travada pra quem ??
	//if(window->locked == 1){}

	
	//Pintar ?? Onde ?? backbuffer ?? dedicated buffer ??
//drawWindow:	
	
	//
	// Devo lembrar que as caracter�sticas da janela est�o salvas na estrutura
	// e s�o muitas caracter�sticas. N�o exige c�lculos, toda a m�trica j� est� pronta.
	//
	
	
	//Buffers ??
	//window->DedicatedBuffer
	//window->BackBuffer
	//window->FrontBuffer
	
	
 
	
	//
	// Agora na hora de efetivamente redezenhar. podemos ver na estrutura
	// Qual os elementos preseentes nela, lembrando que esses elementos 
	// podem ter sido modificados, ent�o o melhor lugar para pegar essas
	//informa��es � na estrutura mesmo, pois l� ser�o salvos as prefer�ncias
	//atuais do usu�rio em rela��o a janela que deve ser repintada.
	// por ex: o usu�rio pode ter redimencionado ou arrastado elementos da janela,
	//ou ocultado apenas. afinal feito escolhas ... usuarisses.
	//
	
	
RedrawBegin:		



    //Sombra.	
	if(window->shadowUsed == 1)
	{
        drawDataRectangle( window->left +1, 
		                   window->top  +1, 
						   window->width, 
						   window->height, 
						   COLOR_BLACK );  //@criar padr�o de cor para sombra.      
	};


    //Background.
	if(window->backgroundUsed == 1)
	{		
	    drawDataRectangle( window->left, 
		                   window->top, 
						   window->width, 
						   window->height, 
						   window->color_bg );   	
	};
	
	
	
	
    //T�tulo + borda.	
	if(window->titlebarUsed == 1)
	{ 
        //
		// #bugbug: Aqui temos um problema, nahora de repintar, n�o temos 
		// definido a cor que precisamos....esse if focus n�o deveria existir na rotina de redraw.
		//
		
		//Focus.
		if(window->focus == 1){
		    window->color_bg = COLOR_BLACK;  // Com foco de entrada.
		}else{
			window->color_bg = COLOR_GRAY;   // Sem foco de entrada.
		};
		
		//@todo: String color.
		
		//@todo: String size.
		
		//Rectangle and string.
		
        drawDataRectangle( window->left, 
		                   window->top, 
						   window->width, 
						   window->height, 
						   window->color_bg );
						   
						   
		//#bugbug n�o temos salvo o posicionamento da string.
        //deveria estar na estrutura da janela.		
		draw_string( window->left +8 +16 +8, 
		             window->top +8, 
					 COLOR_WHITE, 
					 window->name );   //?? name 
					 
		//...			 
	};		
	
	

   // Client Area. 	
	if(window->clientAreaUsed == 1)
	{
		//
		// Obs: A Client Area � apenas um ret�ngulo.
		//

		//@todo: Passar a estrutura de janela.
		
		
		//
		// #BUGBUG :: N�O PODEMOS REALOCAR NOVAMENTE ... TEMOS QUE CHECAR 
		// SE A ESTRUTURA � V�LIDA...
		// SE TRATA APENAS DE UMA ESTRUTTURA DE RET�NGULO, N�O ESPERAMOS MUITOS PROBLEMAS.
		//
		
		 
		if( (void*) window->rcClient == NULL )
		{
			printf("redraw window: a estrtutura de client falhou");
			refresh_screen();
            while(1){}			
		     
		}else{
		
		    //@todo: a cor deveria vir de outra estrutura: window->rcClient->color_bg.
            drawDataRectangle( (unsigned long) window->rcClient->x, 
		                       (unsigned long) window->rcClient->y, 
						       (unsigned long) window->rcClient->cx, 
						       (unsigned long) window->rcClient->cy, 
						       (unsigned long) window->clientrect_color_bg );         
							    
		};
		//Nothing.
	};




	//
	// Outros elementos inda n� implementados ...
	//


	//
	// A rotina de repintura deve estar em sintonia com a rotina de pintura, elas 
	// devem ser semelhantes, porem a rotina de repintura deve levar em considera��o 
	// os elementos inclu�dos depois da cria��o da janela e que ficam gravados na 
	// estrutura. como por exemplo: arquivos abertos.
	//

	//Continua ...
	
done:
    return (int) 0; 
};


/*
 * resize_window:
 *     Muda as dimens�es da janela.
 */				  
int resize_window(struct window_d *window, unsigned long cx, unsigned long cy)
{
    if( (void*) window == NULL ){
	    return (int) 1;    //Erro, estrutura inv�lida.
	}else{	
	    
		//@todo: Checar limites.
	
        window->width  = (unsigned long) cx;
        window->height = (unsigned long) cy;	
	};

done:
    return (int) 0;
};


/*
 * replace_window:
 *     Muda os valores do posicionamento da janela.
 */				  
int replace_window(struct window_d *window, unsigned long x, unsigned long y)
{
    if( (void*) window == NULL ){
	    return (int) 1;
	}else{
		
        //@todo: Checar limites.
	
        window->left = (unsigned long) x;
        window->top  = (unsigned long) y;
	};

done:
    return (int) 0;
};


/*
 * is_window_full:
 *     Checar se est� no modo tela cheia.
 *
 *     retorno 1, modo tela cheia.
 * @todo: Rever o retorno.
 */
int is_window_full(struct window_d *window)
{
    //Checa estrutura.
    if( (void*) window == NULL ){
	    return (int) 0;    //FALSE.
	};

	//Checa modo tela cheia.
    if(window->view == VIEW_FULL){
	    return (int) 1;    //TRUE.
	};
	
fail:
	return (int) 0;
};


/*
 * is_window_maximized:
 *     Checar se est� no modo maximizado.
 *
 *     retorno 1, modo maximizada.
 * @todo: Rever o retorno.
 */
int is_window_maximized(struct window_d *window)
{
    //Checa estrutura.
    if( (void*) window == NULL){
	    return (int) 0;    //FALSE.
	};

	//Checa se est� maximizada.
    if( window->view == VIEW_MAXIMIZED){
	    return (int) 1;    //TRUE.
	};
	
fail:
	return (int) 0;    //FALSE.
};

//todo: rever o retorno
int is_window_minimized(struct window_d *window)
{
    //Checa estrutura.
	if( (void*) window == NULL){
	    return (int) 0;    //FALSE.
	};

	//Checa se est� minimizada.
    if( window->view == VIEW_MINIMIZED){
	    return (int) 1;    //TRUE.
	};
	
fail:
	return (int) 0;    //FALSE.
};


/*
 * CloseWindow:
 *     Fecha uma janela. (Destr�i).
 *
 *     OBS: O ato de fechar uma janela est� associado
 *          ao ato de encerrar um processo. Mas nem sempre.
 *
 */
void CloseWindow(struct window_d *window)
{
	int Offset;
	
	//Check.
	if( (void*) window == NULL ){ return; };

	// Focus.
	KillFocus(window);
	
	// Parent.
	if( (void*) window->parent == NULL)
	{
		//@todo: Usar a linked list de janelas ativas.
	    set_current_window(gui->screen);
	    set_active_window(gui->screen);    
		SetFocus(gui->screen);
	}else{
        set_current_window(window->parent); 
	    set_active_window(window->parent);
        SetFocus(window->parent);  		
    };
	
	//Tira da lista.
    Offset = (int) window->id;		
	windowList[Offset] = (unsigned long) 0;  
	
	//Destr�i a estrutura..
	window = NULL;
	
	
	//
	// @todo: 
	//     Liberar mem�ria. 
	//     (bug bug) problemas para novo ponteiro de heap.
	//
	
	// Counter.
	if( windows_count > 0){
	    windows_count--;
	};
	
	
	//
	// Next window procedure. (@todo: usar lista linkada.)
	//
	//g_next_proc = (unsigned long) &system_procedure;
	SetProcedure( (unsigned long) &system_procedure );
	
// Done
done:
    return;
};


/*
 * DestroyWindow:
 *     Destr�i uma janela.
 *
 *     Obs: Quando a janela � do tipo Overlapped,
 *          destruir janela significa tamb�m fechar 
 *          o processo e as threads associados � ela.
 *
 *          Pois Overlapped � o tipo de janela usado
 *          como janela principal de um processo.
 *
 */
void DestroyWindow(struct window_d *window)
{
	//Check.
	if( (void*) window == NULL ){ return; };
	
	// Kill Threads and Process.
	if(window->type == WT_OVERLAPPED)
    {
	    //kill threads ...
	    //kill process ...
		
		//destroy as threads e o processo associado � janela.
	};
		
	//
	// Close child. (todas do array de estrutura cujo ponteiro esta na estrutura da janela)
	//
	
done:
    //Do Close.
    CloseWindow(window);
    return;
};


/*
 * get_active_window:
 *     Obtem o id da janela ativa.
 *     @todo: Mudar para windowGetActiveWindowId().
 */
int get_active_window(){
    return (int) active_window;  
};


/*
 * set_active_window:
 *     Seleciona qual ser� a janela ativa.
 *     Ativa uma janela.
 */
void set_active_window(struct window_d *window)
{
    //Checa procedimento de janela.	
	if( (void*) WindowProcedure == NULL){
	    return;
	};
	
	//Check window.
	if((void*) window == NULL ){ 
	    return; 
	}else{

	    window->active = (int) 1;	
        WindowProcedure->active_window = (int) window->id;			

	    //Vari�vel global
        active_window = (int) window->id;	
	
	    //Estrutura global
	    ActiveWindow = (void *) window;	
	
	    //Essa fun��o deveria fazer o que manualmente foi feito acima.
	    SetFocus(window);		
	};
	//Nothing.
done:
    return;
};


/*
 * change_active_window:
 *     @todo: Trocar a janela ativa usando uma linked list.
 */
void change_active_window(int Id)
{
	// @todo: Limits. Max.
    if(Id < 0){
	    return;
	};
	
    // Procedure Struct.	
    if( (void*) WindowProcedure == NULL){
	    return;
	};
    
	//
	// @todo: Usar a linked list pra trocar o id.
	//
	
	// Id.
	WindowProcedure->active_window = (int) Id;
	
done:
    return;
};


/*
 * show_active_window:
 *     Mostra o id da janela ativa.
 *     @todo: Mudar o nome para windowShowActiveWindowId() 
 */
void show_active_window(){
	printf("ActiveWindowId={%d}\n", (int) active_window);
    return;
};

/*
 * show_window_with_focus:
 *     Mostra o id da janela com o foco de entrada..
 */
void show_window_with_focus(){
	printf("WindowWithFocusId={%d}\n", (int) window_with_focus);
    return;
};

/*
 * CloseActiveWindow:
 *     Fecha a janela ativa.
 */
void CloseActiveWindow()
{
	int Offset;
    struct window_d *Window;
	
    Offset = (int) get_active_window();	
	if(Offset < 0){
       return;	
	};
	
	//struct.
	Window = (void*) windowList[Offset];
	
	//Nothing to do.
	if( (void*) Window == NULL ){
        return;
    }else{
	    
		//Torna ativa a pr�xima janela.
	    if( (void*) Window->next != NULL ){
	        set_active_window(Window->next);
	    }else{
	        //Torna ativa a janela m�e.
	        if( (void*) Window->parent != NULL ){
	            set_active_window(Window->parent);
	        };
		};
	};	
	
// Done.
done:
    DestroyWindow(Window);
    return;
};


//
// @todo: windowSetFocus(.) e windowGetFocus() windowSwitchFocus()
//



void windowBlockfocus(){
	gFocusBlocked = (int) 1;
	return;
};

void windowUnblockFocus(){
	gFocusBlocked = (int) 0;
	return;
};

/*
 * SetFocus:
 *     Atribui o foco � uma janela e poss�vel.
 *     //Por enquanto estamos implementando a possibilidade
 * de travar a obten��o de foco, somente para teste... porem 
 * isso pode ser �til depois.
 */
void SetFocus(struct window_d *window)
{
	//Imposs�vel mudar o focus.
	//Isso manter� o foco na janela do desenvolvedor
	//durante a fase de cria��o da interface gr�fica.
	if( _lockfocus == 1){
		return;
	};
	
	
	
    if( (void *) window == NULL )
	{
		
		//Isso pe recursivo, pode dar problema.
		//SetFocus(gui->screen);    
		return;
	}else{
		
		//Focus.
	    window->focus = (int) 1;
	    window_with_focus = (int) window->id;		
		WindowWithFocus = (void *) window;
		
		//cursor
		//WindowWithFocus->cursor_x = 0;
		//WindowWithFocus->cursor_y = 0;
		
		//Procedure.
		//?? N�o sei se � o ideal.
		SetProcedure((unsigned long) window->procedure);	
	};
	//Nothing.
	return;
};


/*
 * GetFocus: Pega o id da janela com o foco de entrada.
 */
int GetFocus(){
    return (int) window_with_focus;	
};

/*
 muda qual sra a janela ativa.
 Obs: Quando mudamos qual ser� a janela ativa
 temos que atualizar qum ser� a janela com o foco de entrada.
 ... e as janes com o foco de entrada devem ficar numa lista.
 .. que provavelmente � a lista de janelas filhas.
void windowSwitchActiveWindow();
void windowSwitchActiveWindow()
{}
*/

/*
 * windowSwitchFocus:
 *     Muda a janela que est� com foco de entrada.
 *     @todo: Selecionar a janela indicada como next na estrutura.
 *     Em cada momento o foco est� em uma lista de janelas
 * e quando trocamos o foco, percorremos a lista atual.
 * mas a lista muda dependendo do ambeinte gr�fico que estamos.
 * muda quando trocamos a janela ativa, muda quando trocamos o desktop.
 * 
 */
void windowSwitchFocus()
{
	int Max;
	int Current;

    struct window_d *window;
	struct window_d *next;
	struct window_d *Saved;    //Caso tudo ter errado, use essa.	
	//...
	
	//Max e Current.
	Max     = (int) windows_count;
	Current = (int) window_with_focus;	
	
	//
	// @todo: 
	// Essa rotina precisa ser refeita. Seguindo uma lista linkada de janelas.
	//
	
	window = (void*) windowList[window_with_focus];	
	
	if( (void*) window == NULL ){
	    return;    
	}else{
		
	    //Se n�o h� uma pr�xima, n�o tem como mudar.
	    if( (void*) window->next == NULL ){
		    return;
		};		
		
	    KillFocus(window);  //Kill.
		
	    next = (void*) window->next;  //Get next.

		//Focus.	    
		Current = (int) next->id;     //Current id.
	    
		//Se estiver fora dos limites, use o antigo.
		if(Current < 0 || Current >= Max){
		    Current = (int) window->id;
	    };	

		//@todo: Usar o m�todo.
		window_with_focus = (int) Current;
		window = (void*) windowList[Current];
        SetFocus(window);		
	};
	//Nothing.
done:

    //Debug message:  
	//@todo: Criar mecanismo melhor pra mostrar a janela com o foco.
    printf("Focus={%d}\n", (int) window_with_focus);
	refresh_screen();
	
	return;
};


/*
 * KillFocus:
 *     Uma janela perde o foco.
 */
void KillFocus(struct window_d *window)
{
    //Check.
	if( (void *) window == NULL ){ return; };
	
	//Focus.
	window->focus = (int) 0;

	//
	// Pra onde vai o foco ??
	//
	
	//set next window
	if( (void*) window->parent == NULL){
	    SetFocus(gui->screen); //@todo: Usar a linked list de janelas ativas.
	}else{
	    SetFocus(window->parent); 
    };	
	
	//Set procedure.
    //g_next_proc =  (unsigned long) &system_procedure;
	
done:
	//window_with_focus = ??
	return;
};


/*
 * MinimizeWindow:
 *     Minimiza uma janela.
 *     @todo windowMinimize()
 */
void MinimizeWindow(struct window_d *window)
{
	int Status;
	
    if( (void *) window == NULL){
		return;
	};
	
	Status = (int) is_window_minimized(window);
    if(Status == 1){
	    return;
	};	
	
	//
	//@todo: Redraw ?!
	//
	
done:
	window->view = (int) VIEW_MINIMIZED;
    return;	
};


/*
 * MaximizeWindow:
 *     Maximiza uma janela.
 *     @todo: windowMazimize()
 */
void MaximizeWindow(struct window_d *window)
{
	int Status;
	
    if( (void *) window == NULL){
	    return;
	};
	
	Status = (int) is_window_maximized(window);
    if(Status == 1){
	    return;
	};


    //redimensionar.
	if(gui->main != NULL){
        window->left   = gui->main->left;             
        window->top    = gui->main->top;                   
	    window->width  = gui->main->width;             
        window->height = gui->main->height;
	}; 	

	//
	//@todo: Redraw ?!
	//
	
done:
	window->view = (int) VIEW_MAXIMIZED;
    return;	
};


/*
 * init_window_manager:
 *     Inicializa o gerenciamento de janelas.
 *     @todo windowmanagerInit()
 */
int init_window_manager()
{
	//
    // Aloca mem�ria para a estrutura do procedimento 
	// de janela da thread atual.
	//
	
	WindowProcedure = (void*) malloc( sizeof( struct window_procedure_d ) );
	if( (void*) WindowProcedure == NULL ){
	    printf("init_window_manager fail: Structure.");
		refresh_screen();
		while(1){}
	};  

	//
	// Configura a janela ativa. 
	// Configura a janela com o foco de entrada. 
	// Se a janela com o foco de entrada for uma janela filha,
	// ent�o a janela m�e ser� a janela ativa.
	//
	
	WindowProcedure->active_window = (int) 0;
	WindowProcedure->window_with_focus = (int) 0;

	//
	// @todo:  
	//     Continua fazendo inicializa��es de procedimento de janela.
	//
	
done:
    printf("done!\n");
    return (int) 0;
};


/*
 * init_windows:
 *     Inicializa a lista de janelas.
 *     Inicializa globais relativas � janelas.
 */
int init_windows()
{
	int Offset = 0;
	
	windows_count = 0;
	
	// Inicializa a lista de janelas.
	//printf("init_windows:\n");  	
	
	while(Offset < WINDOW_COUNT_MAX){
	    windowList[Offset] = (unsigned long) 0;
        ++Offset;
	};
	
	// Set current.
	set_current_window(NULL);
	
	//
	// Inicializando a estrutura do ret�ngulo da �rea de cliente.
	//
	
	rectClientArea = (void*) malloc( sizeof(struct rect_d) );
    if((void*) rectClientArea == NULL){	
	    printf("init_windows:");
		refresh_screen();
		while(1){}
	}else{
	    setClientAreaRect( 0, 0, 0, 0);	
	};
	
	
	//
    // Set fonts. @todo: Criar uma estrutura para caracter�sticas do char.
	//
		
	// 8x8 
	g8x8fontAddress  = (unsigned long) 0x000FFA6E;    //ROM. @todo usar defini��o de constante.
	//g8x16fontAddress = (unsigned long) 0x000FFA6E;  //@todo.
	//...
	
	//@todo: create SetFontAddress(.)
	gfontAddress = (unsigned long) g8x8fontAddress;
	
	//
	// Char parameters.
	//
	
	//@todo: Create SetCharParam(.,.)
	gcharWidth = (int) 8;
	gcharHeight = (int) 8;	
	
	//...	
	
	//
	// @todo:
	// Pega o video mode passado pelo Boot Loader e 
	// registra na global e na estrutura.
	//
	
	/*
	
	//video mode
	if( kArg1 > 0)
	{
	    printf("init_windows: Configurando modo de video.");
	    SetVideoMode(kArg1);
	};
	
	//LFB
	if( kArg2 != LFB_BASE)
    {
        printf("init_windows: LFB error");
		//@todo hang
    };	
	
	*/
	
	//Inicializando vari�veis.
	current_windowstation = 0;
	current_desktop = 0;
	current_window = 0;
	windows_count = 0;
	window_with_focus = 0;
	current_menu = 0;
    //Continua...		

	
	//inicializando os esquemas de cores.
	windowSetUpColorScheme();	
	
	//
	// Continua ...
	//
	
done:	
    //printf("Done.\n");
	return (int) 0;
};


//
// End.
//

