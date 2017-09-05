/*
 * Arquivo: grid.c
 *
 * Descri��o:
 *     Grid da �rea de trabalho. (bandeja) (tray)
 *     A tray principal do desktop.
 *     O grid que fica na janela principal. Main window.
 *     Faz parte do m�dulo Window Manager do tipo MB.
 *
 *    @todo: Suspender qualquer opera��o com grid dentro do kernel base.
 *
 *  Fase de desnvolvimento: grid de 4 �tens no topo, centralizado.
 *
 *
 * Vers�o 1.0, 2015.
 */


#include <kernel.h>





/*
 * drawScreenGrid:
 *     Desenha o grid da janela principal. (�rea de trabalho)
 *
 */
int drawScreenGrid()
{
    
	/*
	
	struct window_d *gridWindow; 
	struct window_d *griditemWindow;
	
    int i = 0;
	int j = 0;
	unsigned long x, y, cx, cy;
	
	//
	// Background do grid da janela principal.
	//
	 
	//o grid pertence a janela principal. 
	
	gridWindow = (void*) CreateWindow( 1, 0, 0, "Grid Bg", 
	                                   0, 0, 640, 480-(480/16), 
							           gui->main, 0, COLOR_BACKGROUND, 0 ); //popup						
    if( (void*) gridWindow == NULL)
	{
	    printf("drawScreenGrid fail: bg.\n");
		refresh_screen();
	    while(1){};
	}
	else
	{
		RegisterWindow(gridWindow);
	};	
	
	// Setup.
	x = 0;
	y = 0;
	cx = (unsigned long) (640/8);      //largura do �tem.
	cy = (unsigned long) 480-(480/16); //altura total do bg do grid.
	cy = (unsigned long) (cy/7);       //altura do �tem.
	
	
	// Pintando os �tens.
	
    while(i < 4)
    {		
		//grid item(popup)
	    griditemWindow = (void*) CreateWindow( 1, 0, 0, "Grid Item", 
		                                       x, y, cx, cy, 
								               gridWindow, 0, COLOR_WINDOW, 0 ); 						
        if((void*) griditemWindow == NULL)
	    {
	        printf("drawScreenGrid fail: �tem.\n");
		    refresh_screen();
			while(1){};		    
	    }
	    else
	    {
			RegisterWindow(griditemWindow);
	    };		
		
		y = (unsigned long) y + cy;    
		i++;			
	};
		
		
	*/
	
done:
    return (int) 0;
};


/*
 * initScreenGrid:
 *     Inicializa a estrutura do grid da janela principal. 
 * �rea de trabalho.
 *
 */
int initScreenGrid()
{
	
/*	
	
	struct window_d *hWindow;
	int i = 0;	
	
    //
	// Check ~ Checar se o grid ser� usado na GUI ou n�o. 
	//
	
	
	//if ( gui->gridStatus != 1 )
	//{
	//    return 1; //nao usa.  
	//};
	
	

	//Inicializa lista.
	
    while(i < 32){
	    screenGrid[i] = 0;
	    ++i;
	};
	

	//Set up.
	int z = 0;
	int Count = 2;
	
	unsigned long x = (unsigned long) (800/8);
	unsigned long y = (unsigned long) (600/8);
	unsigned long width  = (unsigned long) (800/6);
	unsigned long height = (unsigned long) (600/8); 
	
	while(Count < 6)
	{
	    //A navigation bar perence a janela principal.
	    hWindow = (void*) CreateWindow( 1, 0, 0, "Title", 
	                                    Count*(800/8), (600/8), (width-2), (height-2), 
							            gui->screen, 0, 0, COLOR_WINDOW); 
	    if( (void*) hWindow == NULL)
	    {
	        printf("initScreenGrid error: Struct.\n");
		    refresh_screen();
	        //while(1){};
			 return (int) 1;
	    }
	    else
	    {
		    //load_bitmap_16x16(0x004F0000, hWindow->left+8, hWindow->top+8, 0);
		    draw_text( hWindow, 24, 0, COLOR_WINDOWTEXT, "Item");
		    
		    //if(root[z] == 0)
			//{
			//    draw_text( hWindow, 8, 8, COLOR_WINDOWTEXT, "Empty");
			//}
			//else
			//{
			//    memcpy( name_x, &root[z], 11);
			//	name_x[11] = 0;
		    //    draw_text( hWindow, 8, 8, COLOR_WINDOWTEXT, &name_x);
			//};
			
			
		    //@todo registrar item de menu
	        RegisterWindow(hWindow);
		    
			x = (unsigned long) ( x + (width));
		
	        if( x > 600 ){
		        x = 0;
			    y = (unsigned long) (y + (height) );
		    };
        };
	    
        //z += 16; 		
	    Count++;
	};
	
	*/
done:
    return (int) 0;
};


//
//fim.
//
