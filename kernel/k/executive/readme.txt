Executive: (Internal Servers) 

   Sobre o diret�rio /executive:
   ============================

   O diret�rio /executive � dividido em tr�s partes:
   /sm, /uitm e uigm.  


 
   Ambiente= ring0

   S�o os m�dulos servidores incluidos no Kernel Base.
   
   Os processos em user mode podem chamar esses servi�os
   via interrup��o, atraves do kernel


   Client --> Kernel --> Server


   pode haver algum tipo de encapsulamento de vari�veis e estruturas
   desses m�dulos.
   o que permite alguma portabilidade desses m�dulos.



   *** Boa parte do codigo desses porcessos ser�o aproveitados 
   para drivers e servidores em user mode. por exemplo a GUI.


   @todo: Talvez criar a pasta posix para dar suporte em kernel mode � biblioteca.





