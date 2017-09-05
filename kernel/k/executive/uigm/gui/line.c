/*
 * File: line.c
 *
 * Descri��o:
 *     Rotinas de pintura de linha.
 *     Faz parte do m�dulo Window Manager do tipo MB.
 *
 * Vers�o 1.0, 2015.
 */


#include <kernel.h>



/*
 * lineDrawHorizontalLineWindowBuffer:
 *     Pinta uma linha horizontal no buffer da janela.
 *     Serve para pintar janelas que ir�o direto do seu buffer para o LFB da 
 * mem�ria de v�deo, sem passar pelo back buffer. (OVERLAPPED)
 *
 */
/* 
void lineDrawHorizontalLineWindowBuffer(struct window_d *window,
                                        unsigned long x1,
										unsigned long y,
										unsigned long x2,
										unsigned long color );
										
void lineDrawHorizontalLineWindowBuffer(struct window_d *window,
                                        unsigned long x1,
										unsigned long y,
										unsigned long x2,
										unsigned long color )
{
    return;	
}
*/


/*
 * my_buffer_horizontal_line:
 *     Pinta uma linha horinzontal no backbuffer.
 *
 */
void my_buffer_horizontal_line( unsigned long x1,
                                unsigned long y, 
								unsigned long x2,  
								unsigned long color )
{
	while(x1 < x2){
        my_buffer_put_pixel( color, x1, y, 0);
        x1++;  
    };

	return;
};


//
//fim.
//
