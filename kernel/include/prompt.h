/*
 * File: prompt.h
 * 
 * Descri��o:
 *     Header para gerenciamento de prompt.
 *     Pode ser usado por qualquer m�dulo do kernel base
 * ou aplica��o.
 *
 * Vers�o 1.0, 2016 - Esse arquivo foi criado por Fred Nora.
 */



/*
 * Prompt:
 *    O prompt do shell. 
 *    Se os caracteres do prompt do shell
 * ser�o pintados no terminal, ent�o precisamos de mais espa�o.
 * o terminal pode ser a janela que � a tela toda (gui->screen) ou
 * outra janela qualquer.
 *
 */

//@todo: O tamanho deveria ser apenas uma linha. 
#define PROMPT_SIZE 256 
 
char prompt[PROMPT_SIZE];
unsigned long prompt_pos; 
unsigned long prompt_status;

//@todo: Testando strings.
static char prompt_cursor[] = "$";
static char prompt_string[] = "Prompt:";

//
// Fim.
//


