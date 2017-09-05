
executive/uigm

    UIGM - User Interface Graphic Mode.
    Recursos de suporte a interface gr�fica de usu�rio.
    O pro�sito � oferecer recursos gr�ficos de forma r�pida e direta.
Esse � o meio mais direto de um processo acessar recursos gr�ficos.
Muitas rotinas primitivas de recursos gr�ficos ser�o oferecidas dentro do
pr�prio kernel base para efeito de maior desempenho. Por�m haver�o bibliotecas em servidores de recursos gr�ficos em um user mode e em kernel mode. Cada servidor
de recurso gr�ficos ter� um desempenho e um privil�gio diferente. Os servidores de recursos gr�ficos poder�o utiizar das primitivas oferecidas pelo kernel base.

    Um servidor que ofere�a recursos gr�ficos de forma mais direta e com maior desempenho der� seu nome relacionado com a palavra DIRECT ou FAST.
Ex: DIRECTMEDIA, DIRECTVIDEO, FASTVIDEO ... ETC...



Sobre o modulo /gui:
===================
    O prop�sito do m�dulo /gui � oferecer recursos para a interface gr�fica de usu�rio. para que o usu�rio possa interagir com o sistema atrav�s de uma interface gr�fica, usando janelas e menus...


Outros m�dulos:
==============  
    Outro m�dulos de suporte a recursos gr�ficos poder�o ser criados aqui.
modulos que gerenciem o suporte aos recurso necess�rios para se ter uma boa interface de usu�rio em modo gr�fico. Ex: Podem gerenciar os recursos de hardware como acelera��o 2d e 3d entre outras funcionalidades. Como configra��es de propriedades f�sicas do video. Ex: Retra�o vertical...etc...Lembrando que quem acessar� o hardware ser� o m�dulo hal, aquia ficar�o alguns gerenciadores em camada mais alta.


 @todo:
 +Graphic Mode configuration.
 +Temas.
 +O diret�rio de imagens usadas pelo modo gr�fico
 +o arquivo que salva as configura��es de modo gr�fico.



  @todo:
  Sobre o processo de cria��o de janelas quando a rotina de cria��o de janelas � chamada por um processo em user mode:
  ====================================================================================================================
  
  *iMPORTANTE: Pode haver mais de um m�todo de cria��o de janela. Tanto eles podem coexistirem, quando podemos
               selecionar o melhor com o passar do tempo.

   + Uma op��o seria uma rotina em usermode de cria��o de janela realiza varias chamadas ao kernel soliciatando primitivas de rotinas
     gr�ficas. Ex: Uma chamda estabelece as dimens�es da janela e outra as cores, epor fim uma rotina monta o window frame todo
     com os elementos previamente passados. 

     *importante:
     Obs: Uma rotina de inicializa��o do procedimento de pintura garante exclusividade para
     o processo, assim nenhum outro processo poder� realizar essa rotina de pintura enquanto o processo n�o tiver acabado.