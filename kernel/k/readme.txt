
Sobre o kernel base:
====================
    O kernel base tem 2 gerenciadores, process.c e modules.c
	O resto s�o m�dulos do tipo MB e processos do tipo PB.


Lista de diret�rios:
===================

/hal          - Hardware abstraction layer
/microkernel  - Kernel m�nimo e fundamental. (tasks)
/executive    - Drivers VIPs, que ficam em kernel mode.



Sobre o executive:
    S�o modulos incluidos ao 'kernel base' na hora da compila��o
    pois s�o modulos e drivers sistemicamente importantes.
    os m�dulos do kernel que ser�o ligados dinamicamente ser�o
 m�dulos de menor importancia para o funcionamento do sistema, como o kd.
   por exermplo: n�o se deve fazer um modulo para o timer.

...
 

Obs:
    A outra parte do controle do hardware fica em user mode. 
    (servers, drivers)

     *@todo:
     * No futuro ser�o esses 3 diret�rios, so que com outros nomes.
       pois a estrutura hal,microkernel e executive pertencem a M$. 
       ex: /hardware /microkernel /system
;
; fim.
;