/*
 * Arquivo: grid.h
 *
 * Descri��o:
 *     Header para grid da �rea de trabalho.
 *     Os grids de aplicativos ser�o resolvidos fora do kernel.
 *
 *     @todo: Esses grids devem ser m�nimos em kernel mode.
 *
 * Vers�o 1.0, 2015.
 */
 
 
// 
// Armazena ponteiros de estrutura.
//

unsigned long screenGrid[128];   //@todo: Esses grids devem ser m�nimos em kernel mode.


int initScreenGrid();
int drawScreenGrid();


//
//fim.
//
