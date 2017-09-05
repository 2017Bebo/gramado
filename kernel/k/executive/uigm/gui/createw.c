/*
 * File: createw.c
 *
 * Descri��o: 
 *     Gerencia os m�todos de cria��o de molduras de janelas e de janelas simples.
 *     Rotina principal de cria��o de janelas.
 *     Faz parte do m�dulo Window Manager do tipo MB.
 *
 * Obs: Os m�todos de cria��o de moldura de janelas podem coexistirem e ser�o
 *      gerenciados por esse m�dulo.
 *
 * *Importante:
 * Um dos m�todos inclui v�rias chamadas ao sistema, sendo que a promeira 
 * chamada ser� uma uma inicializa��o da rotina de constru��o da moldura. Essa
 * inicializa��o deve garantir exclusividade � um processo, para que outro processo
 * n�o interrompa a cria��o da moldura enquanto a rotina em user mode estiver
 * enviando par�metros para o kernel.
 *
 *
 * @todo: 
 * Toda vez que criarmos uma estrutura de janela devemos alocar mem�ria para 
 * o seu buffer dedicado de acordo com as dimens�es da janela e registrar o 
 * ponteiro para o buffer na estrutura de janela.
 * Uma das primeiras coisa a fazer � criar o buffer dedicado, que ser�
 * passado para as rotinas de pintura, para a pintura ser feita no buffer
 * dedicado. 
 *
 * IMPORTANTE: De toda forma, se a rotina de pintura, n�o pintar a janela no 
 * seu buffer dedicado, ela pintar� no buffer default, que � o backbuffer e
 * perceberemos o erro facilmente, para corrigi-lo. Ent�o, na hora de passar o 
 * conte�do dos buffers para o LFB deve-se seguir a ordem de uma lista linkada 
 * cujo primeiro ponteiro � o Backbuffer. Por observa��o poderemos ver se
 * ela � flutuante ou n�o. Se � flutuante, � porque foi pintada em buffer dedicado,
 * se n�o � flutuante � porque foi pintada no buffer default, que � o Backbuffer.
 *
 *
 * Hist�rico:
 *     Vers�o 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *     Vers�o 1.0, 2016 - Aprimoramento geral das rotinas b�sicas.
 *     ...
 */

 
/*
 What is the Difference between a window and a Frame?
 ====================================================
 A window is an undecorated Frame. That is it doesn�t have title bar, border 
 and any close button. It is just a container, which holds children components 
 on it like button, label, text field, etc. Simple we can say it is an 
 imaginary rectangle. The default layout to place these children is Border 
 Layout.
 A Frame is derived from window but it has title bar, border, close button, 
 minimize button, resizable and movable options. By default it also has Border 
 Layout. 
 Note: A frame is a part of a window, but a window is not a part of window.
*/
 
/*
   M$:
 Most programs should use standard window frames. Immersive applications can 
 have a full screen mode that hides the window frame.
 * With a window frame, users can manipulate a window and view the title and 
 icon to identify its contents.
 Hidden frames:
 Sometimes the best window frame is no frame at all. This is often the case for 
 the primary window of immersive full screen applications that aren't used in 
 conjunction with other programs, such as media players, games, and kiosk 
 applications.
 Custom frames: ...
 
 
*/ 


/*
    *Importante:
	 Poder� haver mais de um m�todo de cria��o de uma frame window.   
 */
 
#include <kernel.h>

//
// Identifica��o do processo chamador e da janela a ser criada.
//

/*
struct process_d *xxxCallerProcess;
struct window_d *xxxNewWindow;

//
// Status: Qual � o status? se estiver aberto � porque algum processo est�
//         utilizando a rotina de cria��o de frame.
//

int createw_in_use;  //@todo: Essa vari�vel precisa ser inicializada.

int createwInitialize();
int createwInitialize()
{
	int pid;
	
	//Ocupado.
	if(createw_in_use == 1){
		goto fail;
	}
	
	//desocupado.
	if(createw_in_use == 0)
	{
		createw_in_use = 1;
	    pid = (int) current_process; //@todo: Criar rotina para pegar o id.
		xxxCallerProcess = (void*) processList[pid];
		return (int) 0;
	}
	//Nothing.
fail:
    return (int) 1;	
};

void *createwNewWindow();
void *createwNewWindow()
{
	xxxNewWindow = (void*) malloc(...);
	if( (void*) xxxNewWindow == NULL  ){
		return NULL;
	}
	
	return (void*) xxxNewWindow;
}

 ... @todo: criar mais rotinas primitivas.

*/

/*
 * CreateWindow: 
 *     Cria uma janela com base em uma struct. Retorna o endere�o da estrutura 
 * da janela criada, para que possa ser registrada na lista windowList[].
 * Obs: A contagem � feita quando registra a janela.
 *
 * @todo: � necess�rio definir claramente os conceitos de window e window frame...
 *        A constru��o dos elementos gr�ficos precisam de organiza��o e hierarquia.
 *
 * Obs: Essa rotian pode criar tanto uma janela, quanto um frame ou um bot�o.
 *
 * Cria a janela dependendo do tipo:                              
 * =================================
 * 1 - POP-UP.
 * 2 - EDIT-BOX.
 * 3 - NORMAL ( bg + client area ).
 * 4 - NORMAL_EDIT ( bg + editbox).
 * 5 - MENUBAR.
 * 6 - TOOLBAR.
 * 7 - STATUSBAR.
 * 8 - TASKBAR.
 * 9 - ? 
 * CONTINUA ...
 */
void *CreateWindow( unsigned long type, //1  - Tipo de janela (popup,normal,...)
unsigned long status,     //2  - Estado da janela (ativa ou nao)
unsigned long view,       //3  - (min, max ...)
char *windowname,         //4  - T�tulo.                          
unsigned long x,          //5  - Deslocamento em rela��o �s margens do Desktop.                           
unsigned long y,          //6  - Deslocamento em rela��o �s margens do Desktop.
unsigned long width,      //7  - Largura da janela.
unsigned long height,     //8  - Altura da janela.
struct window_d *pWindow, //9  - Endere�o da estrutura da janela m�e.
unsigned long onde,       //10 - Ambiente. (poderia ser struct desktop_d)
unsigned long arg11,      //11 - ??
unsigned long color       //12 - color (bg) (para janela simples)
)
{
	int View;	//(min, max ...).

	//Bars.
	int TitleBar = 0;
	int MenuBar = 0;
	int ToolBar = 0;
	int StatusBar = 0;
	int ScrollBar = 0;
	//...
	
	//Items.
	int Background = 0;
	int ClientArea = 0;
	int Shadow = 0;
	int ButtonDown = 0; //??
	int ButtonUp = 0;   //??
	int ButtonSysMenu = 0;  //system menu na barra de t�tulos.	

	//Desktop support.
    int ParentWindowDesktopId;    //Id do desktop da parent window.
	int WindowDesktopId;          //Id do desktop da janela a ser criada.
	

    //Structs.	
	struct window_d *window;
	struct window_d *Parent;
	struct desktop_d *Desktop;
    struct rect_d *rcClient;  //rect

	//
	// Desktop:
	// @todo: Configurar desktop antes de tudo. 
	// @todo: Quando criamos uma janela temos de definir que ela
	// pertence ao desktop atual se n�o for enviado por argumento 
	// o desktop que desejamos que a janela perten�a.
	//

	
	//
	// O argumento onde:
	// Indica onde devemos pintar a janela. Serve para indicar as
	// janelas principais. Ex: Se o valor do argumento for 0,
	// indica que devemos pintar na tela screen(background) etc...
	//
	
	//
	// Parent window.
	//
	
    //Usaremos a janela screen como parent window, se a parent window
	//enviada por argumento for inv�lida.
	if( (void*) pWindow == NULL ){
		Parent = (void*) gui->screen;	
	}else{
		Parent = (void*) pWindow;
	};
	
	//
    // New window.
    //	
	
//CreateStruct:
	
	//Alocando mem�ria para a estrutura da janela.
	window = (void*) malloc( sizeof(struct window_d) );	           
	if( (void*) window == NULL )
	{
        //
        // @todo: 
		// Onde o Kernel colocar� essa mensagem de erro ?
		// Por enquanto no backbuffer.
        //
		
		printf("CreateWindow:\n");
		refresh_screen();	
		return NULL; //erro.
		
    }else{
        
		//
		// Obs: 
		// Conseguimos alocar mem�ria para a estrutura da janela. Agora 
		// vamos inicializar os elementos da estrutura de acordo com os 
		// par�metros passados via argumento.
		//
		
		//Object.
		window->objectType = ObjectTypeWindow;
		window->objectClass = ObjectClassGuiObjects;

		//Id. A janela recebe um id somente na hora de registrar.
		//window->id = ??.

	    //Name.
		window->name = windowname;
		
		//Seguran�a.
		window->used = 1;
		window->magic = 1234;
		
		
	    //Window type.	
	    window->type = (unsigned long) type;

		//Procedure support.
		//@todo: Devemos receber esses par�metros e configurar aqui.
		//window->procedure = (unsigned long) &system_procedure;
		//window->wProcedure = NULL;  //Estrutura.
		
		//icon, cursor, cursor x, cursor y, bg etc...
		
		//Caracter�sticas.
		
		//window->active = 0;
		//window->focus = 0;
		
		//Modo de exibi��o.
		//Se n�o estivermos no modo gr�fico, n�o h� o que pintar.
		window->view = (int) view;
		if(g_useGUI == 0){ window->view = (int) VIEW_MINIMIZED; };		
		
		//window->status = 0;
		
		//
		// @todo:
		// Se for uma janela filha o posicionamento deve ser somado �s margens 
		// da �rea de cliente da janela que ser� a janela m�e.
		//


		//Dimens�es e margens.
		window->x = x;
        window->y = y;
        window->width  = width;
        window->height = height;  
		window->left   = window->x;    
        window->top    = window->y;
        window->right  = (unsigned long) window->left + window->width;
        window->bottom = (unsigned long) window->top  + window->height;       
		
		window->color_bg = (unsigned long) color; 
		
		//O ret�ngulo da janela.
		//window->rcWindow = NULL;
		
		//Barras.
		//As flags que representam a presen�a de cada uma das barras
		//ser�o acionadas mais tarde, na hora da pintuda, de acordo com
		//o tipo de janela � ser pintada.
		
		//Msg support.
		window->msg_window = (void *) window;
		window->msg = 0;
		window->long1 = 0;
		window->long2 = 0;
		
		//Offsets
		window->sendOffset = 0;
		window->receiveOffset = 0;
		
		//Arrays.
		//window->hwndList[0] = 0;
		window->msgList[0] = 0;
		//window->long1List[0] = 0;
		//window->long2List[0] = 0;
		
		//Buffers support.
		
		//Dedicated buffer: Cria um buffer dedicado de acordo com as dimens�es da janela.		
		window->DedicatedBuffer = (void*) windowCreateDedicatedBuffer(window);
		
		//O backbuffer � a janela do desktop ao qual a janela pertence.
		//window->BackBuffer = (void*) windowGetBackbufferAddress(); //@todo: Criar fun��o.
		window->BackBuffer = (void*) g_backbuffer_address;
		
		//o frontbuffer � o endere�o da mem�ria de v�deo para o monitor
		//que se deseja mostrar a janela. (LFB, cr3)
		//window->FrontBuffer = (void*) windowGetFrontbufferAddress(); //@todo: Criar fun��o.
		window->FrontBuffer = (void*) g_frontbuffer_buffer_address;
		
	    //@todo:
	    //Se n�o for uma Child, deve-se resetar todas as informa��es relativas
	    //� parent window.
		
		//Parent support
		window->parent = (void*) Parent;
		window->parentid = (unsigned long) Parent->id;
		
		//Child window linked list.
		window->childListHead = NULL;
		
		//Client window support.
		window->client_window = NULL; //window.
		window->rcClient = NULL; //rect.
		
		//Desktop support.
		//window->desktop = (void*) Desktop; //configurado anteriormente.
		//window->desktop_id = Desktop->id;  //@todo: verificar elemento.
		
	    //Menu window. Qual janela o menu usar�.
	    window->menu_window = NULL;    //gui->menu_window ???
		
		//Menus.
		window->sysMenu = NULL;  //gui->menu ???
		window->barMenu = NULL;  //gui->menu ???
		window->defaultMenu = NULL; //gui->menu ???
		
		//menu and button support.
		window->isMenu = 0;
		window->isButton = 0;
		window->selected = 0;  //Caso a janela seja um �tem de menu.
		//window->text = NULL; //Texto, caso a janela seja um �tem de menu

		//Draw support.
		window->draw = 0;      //@todo: Cuidado com isso.
		window->redraw = 0;
	    window->show = 1; //Inicialmente presumimos que precisamos mostrar essa janela.
	    //Continua ...
	
        //Abaixo, elementos referenciados com menor frequ�ncia.
	    
		//Trava.
		window->locked = 0;
		
		//Linked list.
		//window->linkedlist = NULL;
		
		//Prev e next.
		window->prev = (void*) Parent;
		window->next = NULL;
			
		//Debug:
		//printf("config1 %s %d %d %d %d \n",window->name,window->left, window->top, window->width, window->height);
	};
	
    //Exemplos de tipos de janelas, segundo MS.	
    //Overlapped Windows
    //Pop-up Windows
    //Child Windows
    //Layered Windows
    //Message-Only Windows	
	
	//
	// Preparando os parametros da pintura de acordo com o tipo.
	//	

	//
	// Minimized ? 
	// Se tiver minimizada, n�o precisa mostrar a janela, por�m
	// � necess�rio pintar a janela no buffer dedicado.
	//
	View = 0;
	View = (int) is_window_minimized(window);
    if(View == 1)
	{
		//window->draw = 1; //Devemos pint�la no buffer dedicado.
		window->show = 0;
		window->redraw = 0;
		//...
		
		//@todo: N�o retornar. 
		//como teste estamos retornando.
		//goto done;
	    return (void*) window;
	};
	
	//
	// @todo: Maximized ?
	// Para maximizar devemos considerar as dimens�es da �rea de cliente
	// da janela m�e.
	// Se a jenela estiver maximizada, ent�o deve ter 
	// o tamanho da �rea do cliente, caso ela seja uma janela filha.
	// Essa �rea de cliente poder� ser a �rea de trabalho, caso a
	// janela m�e seja a janela principal.
	// 
	
	//View = 0;
	//View = (int) is_window_maximized(window);
    //if(View == 1){
	//	//...
	//}	
	
	//
	// Configurando os elementos de acordo com o tipo.
	// @todo: Salvar as flags para os elementos presentes
	// na estrutura da janela.
	//
	
    switch(type)
    {
		//0) Null.
		case WT_NULL:
		    return NULL;  //Ainda n�o implementada.
		break;
		
		//    **** WINDOW ****
		// A window is an undecorated Frame.
		//1) Simple rect, (Sem barra de t�tulos).
		case WT_SIMPLE:
	    Background = 1;    //bg.
	    window->backgroundUsed = 1;
		break;

		//
		//2) Edit box, (Simples + borda preta).
		case WT_EDITBOX:
	    Shadow = 1;        //sombra.
	    Background = 1;    //bg.
		window->shadowUsed = 1;
		window->backgroundUsed = 1;
		break;

		//   **** FRAME ****
		//3) Overlapped, (completa, para aplicativos).
		case WT_OVERLAPPED:
	    Shadow = 1;        //Sombra.
	    Background = 1;    //bg.
	    TitleBar = 1;      //T�tulo + Borda.
		//MenuBar       = 1;  //Barra de menu. 
	    ButtonSysMenu = 1;    //System menu button. ??
		ClientArea = 1;
		
		window->shadowUsed = 1;
		window->backgroundUsed = 1;
		window->titlebarUsed = 1;
		window->clientAreaUsed = 1;
		
		//@todo:
		//Se for do tipo overlapped pode ser ou n�o a janela ativa.
		//set_active_window(window);
		break;

		//4) Popup (um tipo de overlapped mais simples).
		case WT_POPUP:
	    Shadow = 1;        //sombra.
	    Background = 1;    //bg.
		window->shadowUsed = 1;
		window->backgroundUsed = 1;		
		
	    //if(titulo){} TitleBar = 1;    //titulo + borda
		break;

		//5) Button down.
		case WT_BUTTON_DOWN:
	    ButtonDown = 1;
		window->isButton = 1;
		window->selected = 1;
		break;

		//6) Button up.
		case WT_BUTTON_UP:
	    ButtonUp = 1;
		window->isButton = 1;
		window->selected = 0;
		break;

        //Continua ...
		
        default:
            return NULL;  //Ainda n�o implementada.		
		    break;
	};	
	
	// Continua...
	
	
    //
	// Draw !
	//
	
	//
	// Hora de pintar. Os elementos ser�o inclu�dos se foram 
	// selecionados anteriormente.
	//
	
DrawBegin:	

    //
	// Obs: Se for uma janela, pintaremos apenas a janela.
	//      Se for um frame, pintaremos todos os elementos
	//      presentes nesse frame de acordo com as flags.
	//

    //
	// Obs:
	// A janela precisa ser pintada em seu buffer dedicado.
	// Nesse momento o buffer dedicado da janela j� est� na estutura
	// da janela. Rotinas de pintura que tenham acesso � estrutura da
	// janela devem utilizar o buffer dedicado que for indicado na estrutura.
	// Para que seja poss�vel pintar uma janela em seu buffer dedicado,
	// devemos passar um ponteiro para a estrutura da janela em todas
	// as rotinas de pintura chamadas daqui pra baixo.
	//
	// @todo: Passar estrutura de janela via argumento, para a rotina
	// de pintura ter acesso ao buffer dedicado.
	//
	
	//if(DedicatedBuffer == 1){};


    //
	// Color:
	// Obs: @todo: Isso foi definido acima, foi passado por argumento e
	// colocado na estrutura. Fiacr� assim somente por teste,
	// depois deletaremos essa defini��o aqui.
	//
	
	window->color_bg = COLOR_WINDOW;

    //Sombra.	
	if(Shadow == 1)
	{
		//@todo: Passar a estrutura de janela.
        drawDataRectangle( window->left +1, 
		                   window->top  +1, 
						   window->width, 
						   window->height, 
						   COLOR_BLACK );        
	};	
	
    //Background.
	if(Background == 1)
	{
	    if( (unsigned long) type == WT_SIMPLE){
		    window->color_bg = color;
		};
		
        //@todo: Passar a estrutura de janela.
		drawDataRectangle( window->left, 
		                   window->top, 
						   window->width, 
						   window->height, 
						   window->color_bg );   	
	};
	
    //T�tulo + borda.	
	if(TitleBar == 1)
	{ 
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
						   
		draw_string( window->left +8 +16 +8, 
		             window->top +8, 
					 COLOR_WHITE, 
					 windowname ); 
					 
		//...			 
	};	
	
	
    // Client Area. 	
	if(ClientArea == 1)
	{

		//@todo: Passar a estrutura de janela.
		
		rcClient = (void*) malloc( sizeof(struct rect_d) ); 
		if( (void*) rcClient == NULL )
		{
			//free(rcClient);
		    window->rcClient = NULL;	
		}else{
			
			//@todo: Criar fun��o rectSetup(....)
			// Testando, isso pode falhar.
		    
			window->rcClient->objectType = ObjectTypeRectangle;
			window->rcClient->objectClass = ObjectClassGuiObjects;
			window->rcClient->x  = (unsigned long)(window->left +1);
            window->rcClient->y  = (unsigned long)(window->top +24);
            window->rcClient->cx = (unsigned long)(window->width -2);
            window->rcClient->cy = (unsigned long)(window->height -25);			
		
	        window->color_bg = COLOR_WINDOW;
            drawDataRectangle( (unsigned long) window->rcClient->x, 
		                       (unsigned long) window->rcClient->y, 
						       (unsigned long) window->rcClient->cx, 
						       (unsigned long) window->rcClient->cy, 
						       (unsigned long) window->color_bg );
		};
		//Nothing.
	};

	//MenuBar (teste)
    /*   
    if(MenuBar == 1)
	{
	    create_menubar(window);
        initmenuArray( window->barMenu, 2);    //Quantidade.
        create_menubar_item(window->barMenu,"Item1",1);    /Selected
        create_menubar_item(window->barMenu,"Item2",0); 		
	};
	*/

    // Button Down.
	if(ButtonDown == 1)
    {
        //@todo: Passar a estrutura de janela.		
		window->color_bg = COLOR_BUTTONFACE;
		draw_button( window->parent, window->name, BN_DOWN,  
		             window->left, window->top, window->width, window->height, 
					 window->color_bg);	
	};
	
    // Button Up.
	if(ButtonUp == 1)
    {	
        //@todo: Passar a estrutura de janela.  
		window->color_bg = COLOR_BUTTONFACE;
		draw_button( window->parent, window->name, BN_UP,  
		             window->left, window->top, window->width, window->height, 
					 window->color_bg);	
	};
	
	//
	// Continua ... ( Pinta detalhes da janela, caso ouver )
	//
	
	//Barras de rolagem ...
	//efeitos ...
	//itens de menus...
	//itens de barras ...
	//carrega �cones ...
	//Continua ...
	
	
	//
	// Message: 
	// @todo: Enviar uma mensagem de CREATE pra janela.
	//        Assim o procedimento cria os elementos
	//        restantes.
	//
		
	
	
	//
	// @todo: Atualizar a linkedlist da parent window.
	//
	
	
	//
	// @todo: ShowWindow.
	//
	
	
// done.		
done:
    //SetFocus(window);
	return (void*) window;
};

//
// End.
//
