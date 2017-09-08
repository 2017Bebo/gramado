;
; Gramado Idle - This is a 32bit, user mode, system application.
; It's the idle process to run when the system is with few activity.
; (c) Copyright 2015-2016 Fred Nora.
;
; File: head.s 
;
; Descri��o:
;     � o entry point do programa IDLE.BIN. 
;     Faz a vez do crt0.s por enquanto.
;
;
; Alguns par�metros: (@todo: rever)
; ================== 
;  4MB � partir de 400000.
;  f�sico = virtual      
;  400000 = 400000
;
;  + O kernel carrega o programa em 0x00400000 com o entry point em 0x0041000.
;  + Quem configurou a pagina��o foi o Boot Loader, mas o kernel refez.
;
;   Stack: (rever)
;   ss  = 0x23
;   esp = 0x00709fff0  ???
;
; Hist�rico:
;     2015 - Created by fred Nora.
;     2016 - Revision.
;

;;
;; codename db 'angola'
;;


segment .head_x86


 
[bits 32]


 
;
; Fun��o importadas.
;

extern _appMain           ;Roda o Idle como uma aplica��o normal.
extern _driverInitialize  ;Envia um sinal pro kernel inicializar esse driver.
extern _driverUninitialize
;extern _exit



;extern _slSystemRam
;extern _slSystemIoCpu
;extern _slSystemIoDma
;extern _slSystemDevicesUnblocked
;extern _slSystemDevicesBlocked
;extern _slSystemThings


;--------------------------------------------
; _idle_entry_point:
;     Entry point
;
global _idle_entry_point              
_idle_entry_point:

;;
;; Normal initialization.
;;

;jmp RealStart

;;
;; System Lib Support. 
;; Obs: Apenas os jmps.
;; Obs: 4 argumentos devem estar na pilha.
;;

;jmp _slSystemRam
;jmp _slSystemIoCpu
;jmp _slSystemIoDma
;jmp _slSystemDevicesUnblocked
;jmp _slSystemDevicesBlocked
;jmp _slSystemThings


RealStart:
	
	;
	; Atuando como driver:
	; ====================
	; Para o Kernel utilizar esse processo como driver, ele precisa linkar 
	; esse processo ao processo Kernel. Vamos fazer isso de forma simples 
	; agora como um teste, depois melhoraremos a maneira de fazer. 
	; O que faremos aqui � atender a solicita��o do Kernel de inicializar o 
	; driver. Logo ap�s inicializarmos o driver, enviaremos uma mensagem para 
	; o Kernel na forma de system call, ent�o o Kernel linkar� ao sistema o 
	; driver inicializado.
	;

	;
	; Testar se devemos ou n�o inicializar o driver:
	; ==============================================
	; O Kernel envia uma flag no registrado edx, se a flag for encontrada,
	; significa que devemos inicializar o driver, caso contr�rio, n�o.
	;
	; Status do teste: Ok, funcionou. Podemos usar outros argumentos para 
	; efetuarmos outras opera��es no driver. Como uninitilization.
	;

	
	push edx
	
    ;Initialize driver.
	cmp edx, dword 1234
    je .InitializeDriver	
	
	;Uninitialize driver.
	cmp edx, dword 4321
	je .UninitializeDriver
	
    ;Default, Initialize normal application.  	
	jmp .InitializeApplication 
	
	;
	; ...
	;
	
; Esse processo ser� inicializado como um driver.   
.InitializeDriver:
    ;envia ao kernel um sinal pra ele inicializar esse processo
	;como uum driver do sistema.
    call _driverInitialize	
    jmp $ ;;Hang.
	
.UninitializeDriver:
    call _driverUninitialize
	jmp $

;
; ...
;
	
; Esse processo n�o est� ser� inicializado como driver.	
.InitializeApplication:	
    pop edx

    ;
    ; Para transformar o processo Idle em um tipo de servidor, esse c�digo 
    ; precisa ser reentrante. Todos servidores receber�o quatro argumentos 
    ; na pilha que ser�o enviados pra uma rotina. 
    ; Esse � um m�todo diferente do tradicional. Isso � um teste.
    ;
    ; @todo:  
    ; Obs: Os argumentos j� est�o na pilha, se fizermos um call para a 
    ; rotina principal, talvez novos argumentos sejam colocados na pilha
    ; talvez n�o. (Testado: Novos valores n�o foram inclu�dos na pilha e
    ; tudo funcionou como esperado ).
    ; Precisamos salvar os argumentos recebidos e coloc�-los na pilha antes 
    ; de chamar a rotina principal. Obs: Salvar argumentos passados nunca 
    ; fez mal.
    ; Obs: N�o desejamos realizar esses salvamentos. N�o salvaremos a pilha se 
    ; saltarmos diretamente para rotinas de servi�os de classes do sistema.
    ;
   
    ;Salvando.
    pop eax
    mov dword [.save1], eax
    pop eax
    mov dword [.save2], eax   
    pop eax
    mov dword [.save3], eax   
    pop eax
    mov dword [.save4], eax   
	

    ;Debug:
    ;Isso � um teste antigo. @todo: Deletar.
    ;NOP
    ;NOP
    ;NOP
    ;NOP
    ;mov ax, word 0x1 
    ;mov ax, word 0x2 
    ;mov ax, word 0x3 
    ;mov ax, word 0x4 
	;mov byte [0x800000], byte "i"	
    ;mov byte [0x800001], byte 0x0f	
    ;mov byte [0x800002], byte "d"	
    ;mov byte [0x800003], byte 0x0f	
    ;mov byte [0x800004], byte "l"	
    ;mov byte [0x800005], byte 0x0f	
    ;mov byte [0x800006], byte "e"	
    ;mov byte [0x800007], byte 0x0f	
	
	
	;Passando os argumentos atrav�s da pilha.
	mov eax, dword [.save4]
	push eax
	mov eax, dword [.save3]
	push eax
	mov eax, dword [.save2]
	push eax
	mov eax, dword [.save1]
	push eax
	
	;Chamando a fun��o principal.
    call _appMain
	
	;Tratando o retorno.
	cmp eax, 0
	je .retOk
	
    ;Nothing.
.die:	
    ;mov eax, dword [_error_code]
    ;call _exit
	jmp $
	;...
.retOk:
    ;mov eax, dword [_error_code]
    ;call _exit
    jmp $

;salvar pilha aqui.	
.save1: dd 0
.save2: dd 0
.save3: dd 0
.save4: dd 0	
	
;
;End.
;
