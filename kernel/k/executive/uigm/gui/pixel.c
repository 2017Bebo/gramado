/*
 * File: pixel.c
 *
 * Descri��o:
 *     Rotinas de pintura de pixel.
 *     Faz parte do m�dulo Window Manager do tipo MB.
 *
 * *IMPORTANTE
 * Obs: Se uma estrutura de janela for passada como argumento
 *      na hora de colocar um pixel ent�o usaremos o buffer dedicado
 * indicado nessa estutura. Caso contr�rio, se n�o for passado
 * um ponteiro pra estrutura de janela, ou se estrutura n�o tem um 
 * ponteiro para buffer dedicado, ent�o usaremos um buffer padr�o,
 * que sempre ser� o buffer dedicado da janela principal, gui->main.
 * que podemos chamar de 'desktop', mas n�o � a estrutura de desktop
 * como a conhecemos. 
 *
 * Uma solu��o elegante seria ter ponteiros para buffers na 
 * estrutura da gui->, assim podemos alocar mem�ria para um buffer
 * gen�rico, e seu ponteiro ser passado para a janela que se interessar 
 * por ela. As estruturas de user session, windos station, e desktop
 * tambem podem ter ponteiros para buffers gen�ricos. Podemos tamb�m
 * ter uma vari�vel global para isso e tamb�m estrututra de buffer.
 *
 *
 * A solu��o mais simples � passar para a rotina de pintura o buffer desejado,
 * n�o a estrutura de buffer e sim apenas o ponteiro para o buffer. se bem que 
 * se fosse passado um ponteiro para um estrutura de buffer seria bem mais seguro.
 *
 * Vers�o 1.0, 2015.
 */

 
#include <kernel.h>


//
// Vari�veis importadas. 
//


//Herdadas do Boot Loader.
extern unsigned long SavedBootBlock;
extern unsigned long SavedLFB;
extern unsigned long SavedX;
extern unsigned long SavedY;
extern unsigned long SavedBPP; 

//Outras.
extern void gui_buffer_putpixel();

/*
//Pinta um pixel diretamente na mem�ria de v�deo.
//Obs: A sincroniza��o vertical deve ser feita na hora de pintar
//um caractere, e n�o a cada pixel pintado.
//Por�m se um aplicativo em user mode desejar pintar apenas um pixel,
//� necess�rio fazer a sincrniza��o vertical.
void pixelDirectPutPixel( void* FrontBuffer, unsigned long x, unsigned long y, unsigned long color );
void pixelDirectPutPixel( void* FrontBuffer, unsigned long x, unsigned long y, unsigned long color )
{
    return; //ainda n�o implementada.							  
}
*/


										 
//Pinta um pixel em um buffer de janela.
void pixelPutPixelWindowBuffer( void* buffer, 
                          unsigned long x, 
						  unsigned long y, 
						  unsigned long color )
{
	return; //@todo: Ainda n�o implementada.					  
};
										 
/*
 * *IMPORTANTE
 * Obs: Se uma estrutura de janela for passada como argumento
 *      na hora de colocar um pixel ent�o usaremos o buffer dedicado
 * indicado nessa estutura. Caso contr�rio, se n�o for passado
 * um ponteiro pra estrutura de janela, ou se estrutura n�o tem um 
 * ponteiro para buffer dedicado, ent�o usaremos um buffer padr�o,
 * que sempre ser� o buffer dedicado da janela principal, gui->main.
 * que podemos chamar de 'desktop', mas n�o � a estrutura de desktop
 * como a conhecemos.
*/										 
void pixelPutPixelDedicatedWindowBuffer( struct window_d *window, 
                                         unsigned long x, 
										 unsigned long y, 
										 unsigned long color )
{
	//O buffer ser� selecionado por essa rotina ficar� aqui
	//
	void *buff;
	
	//Se temos uma estrutura de janela, essa estrutura pode
	//conter um ponteiro para um buffer dedicado de janela.
	if((void*) window == NULL )
	{
		buff = NULL;
		goto useDefaultBuffer;
	}else{
		
		//Se o ponteiro para buffer dedicado indicado na estrutura
		//for inv�lido.
		if( (void*) window->DedicatedBuffer == NULL ){
			goto useDefaultBuffer;
		}
		
		//Ok.
		//O ponteiro para o buffer dedicado parece v�lido.
		//@todo: A rotina de cria��o de estrutura de janela
		//tem que alocar din�micamente mem�ria para o buffer corretamente.
		//e n�o pode admitir falha nesse requesito.
		
		
		buff = (void*) window->DedicatedBuffer;
		goto useDedicatedBuffer;
		//
		//
	}
	//Nothing.
	
// Somos obrigados a usar o buffer dedicado da janela principal.	
//@por enquanto isso n�o ser� considerado uma falha.
useDefaultBuffer:
	//@todo: pegar o buffer default.
	buff = (void*) gui->defaultWindowDedicatedBuffer1;
	if( (void*) buff == NULL ){
		//@todo: Alocamos mem�ria par a o buffer
		
		//buff = (void*) malloc(SIZE??);
		
		printf("pixelPutPixelDedicatedWindowBuffer:");
		refresh_screen();
		while(1){}
	}
	//...pinta asm_putpixel()
//Aqui conseguimos encontrar o buffer dedicado da janela em quest�o.	
//O buffer selecionad foi o buffer dedicado da janela. temos que checar.
useDedicatedBuffer:	
	if( (void*) buff == NULL ){
		//@todo: Alocamos mem�ria par a o buffer
		
		//buff = (void*) malloc(SIZE??);
		
		printf("pixelPutPixelDedicatedWindowBuffer:");
		refresh_screen();
		while(1){}
	}
	//pinta. asm_putpixel()
    return;	
}


/*
 * my_buffer_put_pixel:
 *     Coloca um pixel o buffer backbuffer. 
 *     Obs: O backbuffer dever� ser o buffer dedicado da janela principal gui->main.     
 *
 * a = cor
 * b = x
 * c = y
 * d = null
 *
 */
void my_buffer_put_pixel( unsigned long ax, 
                          unsigned long bx, 
						  unsigned long cx, 
						  unsigned long dx )
{
	asm volatile(" \n " : : "a"(ax), "b"(bx), "c"(cx), "d"(dx) );
		
	/*
	 * Chama a rotina em assembly depois de enviar os valores para os 
	 * registradores.
	 */
	 
	//Coloca um pixel no backbuffer. 
	gui_buffer_putpixel(); 	
	return;
};

//
// End.
//
