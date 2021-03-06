/*
 * File: fs/fs.c 
 *
 * Descri��o:
 *    Arquivo principal do file system manager.
 *    M�dulo em kernel mode, incluido no kernel base. 
 *    
 *    *IMPORTANTE: A id�ia principal � que esse m�dulo de o suporte ao acesso 
 * a qualquer sistema de arquivo suportado, esteja ele em user mode ou em 
 * kernel mode.
 *
 *    Arquivo principal do m�dulo fs do executive do kernel..
 *    Gerenciador de arquivos do kernel.
 *    Na verdade o Kernel n�o tem atribui��es de carregar arquivos. Mas
 * ele ofere�e servi�os b�sicos que podem ser chamados pelos aplicativos.
 *
 * Objetivo:
 *    Ofere�er opera��es nos sistemas de arquivos suportados pelo kernel.
 *    Esse gerenciador chama as fun��es em kernel mode do sistema de arquivos
 * interno e chama as servi�os oferecidos pelos drivers em user mode.
 *
 *    Os drivers em user mode podem oferecer acesso � sistemas de arquivos
 * variados.
 *
 *   Ao kernel, compete as fun��es b�sicas de opera��es com hardware.
 *   O sistema de arquivos suportado pelo kernel � fat16.
 *   Continua ...
 *
 * Observa��o: 
 *    Os valores das estruturas do sistema de arquivos podem ser salvos 
 * em um registro.
 *    No registro pode ter um registro das opera��es efetuadas 
 * no sistema de arquivo.
 *   Continua ...
 *   
 * History: 
 *    2015 - Created by Fred Nora.
 *    2016 - Revision.
 *    ...
 */
 

#include <kernel.h>




//Vari�veis internas.
//int fsStatus;
//int fsError;
//...


int fsCheckELFFile ( unsigned long address ){
	
	unsigned char *buffer = (unsigned char *) address;
	
	//.ELF
	if ( buffer[0] != 0x7F ||
		 buffer[1] != 0x45 ||
		 buffer[2] != 0x4C ||
		 buffer[3] != 0x46 )
	{
		printf("fsCheckELFFile: Sig \n");
		//goto fail;
	    return 1;
	}
	
	//Continua...
	
	//
	// # OK #

	return (int) 0;
}




// Checando a validade de arquivos bin�rios no formato PE.
// #bugbug: Isso n�o deve ficar no kernel, pois PE � propriet�rio.
// Nem usaremos PE no futuro.

int fsCheckPEFile ( unsigned long address ){
	
	unsigned char *buffer = (unsigned char *) address;
	
	//i386
	if ( buffer[0] != 0x4C || buffer[1] != 0x01 )
	{
		printf("fsCheckPEFile: Sig \n");
		//goto fail;
		return 1;
	}
	
	//i486
	
	//Continua...
	
	//
	// # OK #
	//
	
	return (int) 0;
}


/*
 * fsListFiles:
 *     Lista os arquivos em um diret�rio, dados os �ndices de disco, 
 * volume e diret�rio.
 * #test isso funciona.
 */				  
void 
fsListFiles( int disk_id, 
             int volume_id, 
			 int directory_id )
{
	printf("fsListFiles: disk={%d} vol={%d} dir={%d}\n", 
	    disk_id, volume_id, directory_id );

	// @todo: Checar mais limites.
	
	if ( disk_id == -1 || 
	     volume_id == -1 || 
		 directory_id == -1 )
	{
		goto fail;	
	}
	
	// Show!
	// Se o diret�rio selecionado � o diret�rio raiz do VFS.
	
	if ( current_disk == 0 && 
	     current_volume == 0 &&
		 current_directory == 0 )
	{
	    vfsListFiles();
        goto done;		
	};
	
	// @todo: Suportar outros diret�rios.
	// ...
	
	goto done;
	
fail:
    printf("fail\n");
done:	
	refresh_screen();
	return;
};


/*
 * fsCreateVFS:
 * 
 * #bugbug : Isso est� errado:
 * agora temos rotinas de vfs em vfs.c
 *
  @todo
//  
// ** CRIANDO O DIRET�RIO RAIZ DO VFS BASEADO EM STREAMS **
//

//criando o diret�rio '/vfs'

**/

void fsCreateVFS (){
	
/*	
    FILE *vfs;
    char *vfs_root;
  
    //inicializa a estrutura ...
    vfs = ( void* ) malloc( sizeof(struct _iobuf) );
	if( (void*) vfs == NULL  ){
		//die();
	}	
	
	//aloca mem�ria para o diret�rio raiz do vfs.
    vfs_root = (char *) malloc(512*16);
	
	if( (char *) vfs_root == (char *) 0 )
	{
		//die();
	}else{
		
		//O in�cio da �rea de mem�ria reservado para o diret�rio 
		//ser� salvo na estrutura de stream.
		vfs->_base = (char *) vfs_root;
        //...
	};
*/
};


/*
void fsClearRootdirBuffer();
void fsClearRootdirBuffer()
{
    limpa_root();
	return;
}
*/


/*
void fsClearFatBuffer();
void fsClearFatBuffer()
{
    limpa_fat();
	return;
}
*/


/*
int fsIsFAT12();
int fsIsFAT12()
{
   //testa o tipo de fat.
    return 0;
};
*/


/*
int fsIsFAT16();
int fsIsFAT16()
{
    //testa o tipo de fat.
    return 0;
};
*/


/*
int fsIsFAT32();
int fsIsFAT32()
{
    //testa o tipo de fat.
    return 0;
};
*/


/*
int fs_open()
int fs_open()
{
  
    if( fs_channel == NULL)
	{
	    return 1;
	}
	else
	{
        fs_channel->opened = 1;		
	};
	
done:
    return;	
};
*/


//comando 'dir'
//Listando arquivos em um diret�rio dado o nome.

int fsList ( const char *dir_name ){
	
	
	printf("fsList:\n");
	
	
	//#importante:
	//temos que consultar a estrutura storage.
	//L� saberemos qual � o disco e volume atuais.
	//Se o nome passado n�o indicar em qual disco devemos atuar,
	//isso significa que devemos continuar no mesmo disco.
	
	//com base no nome temos que encontrar as outras informa��es sobre 
	//o diret�rio.
	
	//se apenas o nome do diret�rio for indicado 
	//ent�o devemos procurar no diret�rio atual.
	
	//#bugbug 
	//POR ENQUANTO S� PROCURAMOS NO ROOT DIR.
	
	//# improvisando os valores.
	fsFAT16ListFiles ( (const char *) dir_name,         // name 
		    (unsigned short *) VOLUME1_ROOTDIR_ADDRESS, // address
			256 );				                        // number of entries
			
	
	//...
	
	return (int) 0;
};


/*
 * fsFAT16ListFiles:
 *     Mostra os nomes dos arquivos de um diret�rio.
 *     Sistema de arquivos fat16.
 *
 * IN:
 *     dir_address = Ponteiro para um endere�o de mem�ria 
 *                   onde foi carregado o diret�rio.
 *
 */
 
void 
fsFAT16ListFiles( const char *dir_name, 
                  unsigned short *dir_address, 
				  int number_of_entries )
{
	//@todo: O n�mero de entradas � maior no diret�rio raiz.(512 ?)
	
    int i = 0;
	int max = number_of_entries;         // N�mero m�ximo de entradas.
    
	unsigned long j = 0;  // Deslocamento
	
	unsigned short *DirBaseAddress = (unsigned short *) dir_address;
	
	
	if ( number_of_entries <= 0 ){
		return;
	}
	
	printf("\n");
	printf("fsFAT16ListFiles: Listing names in [%s]\n\n", dir_name );
	
    
	// Mostra.
	i=0; 
	while (i < max)
	{
		// Diferente de vazio.
		if ( DirBaseAddress[j] != 0 ){
			
			//O problema � a termina��o da string '\0'
			printf ("%s\n", &DirBaseAddress[j] );
        } 
		
		//(32/2) pr�xima entrada! (16 words) 512 vezes!
        j += 16;    
        ++i;        
    }; 
	
	//...
	
	//printf ("Done\n");	
	refresh_screen();
};



/*
 * KeLoadFile:
 *     Carraga um arquivo na mem�ria.
 *     @todo: Ke_ n�o � o certo, pois ke � chamadas 
 *            � rotinas externas. 
 *
 * #bugbug a estrutura de canal ser� usada para troca 
 * de mensagens S|----|S
 */
int 
KeLoadFile( struct channel_d *channel, 
            unsigned char *file_name, 
			unsigned long file_address )
{

	/*
	
    int Status;
	
	if ( (void *) channel == NULL )
	{
	    return (int) 1;
	}else{
	    
		//Aberto?
	    if(channel->State != 1){
		    return (int) 1;
		};
		
		//esta em uso.
		channel->InUse = 1;
	
	};	
	
	//confere se o canal passado por argumento est� aberto.
	
    //Status = (int) fsLoadFile ( file_name, file_address );
	
	Status = (int) fsLoadFile ( VOLUME1_ROOTDIR_ADDRESS, 
	                file_name, 
					file_address );
		
	if ( Status != 0 )
	{
		// Aqui tem que ter uma mensagem @todo.
	    channel->InUse = 0;
		channel->State = 0;
	    return (int) 1;
	};
	
	//N�o est� mais em uso.
	channel->InUse = 0;
	
	//Close channel.
	channel->State = 0;

    return (int) 0;	
	*/
	return -1;
};



/*
 * get_file:
 *     Obt�m o ponteiro da estrutura do arquivo, dado seu id.
 *     Com um �ndice da lista de arquivos, a fun��o retorna o ponteiro da
 *     estrutura do arquivo.
 */
 
// void *get_stream (int Index)
void *get_file (int Index){
	
	//Limits.	
	//@todo: max.
	if(Index < 0){
	    return NULL;
	};
	
    return (void *) Streams[Index];
};


/*
 * set_file:
 *     Coloca na lista de arquivos o ponteiro de estrutura,
 * dado seu id.
 * 
 */
 
//void set_stream ( void *stream, int Index ){ 
void set_file ( void *file, int Index ){
	
	//Limits.	
	if(Index < 0){
	    return;
	};
	
	//
	// @todo: Limite m�ximo da lista.
	//
	
    // Structure.
	if( (void *) file == NULL ){
		return;
	}	
	
	// Include pointer in the list.
	Streams[Index] = (unsigned long) file;
	//return;
};


void fs_test_fat_vector (){
	//Ainda n�o implementada.
};


unsigned long fs_get_fat_entry (unsigned long n){
	
    //Ainda n�o implementada.	
    return 0; 
};
											 

void fs_set_fat_entry ( unsigned long n, unsigned long value ){
	
    //Ainda n�o implementada.	
};


void fs_put_list_on_fat (){
	
	//Ainda n�o implementada.
};


void fs_set_structures (){
	
	//Ainda n�o implementada.
};


void fs_set_entry ( unsigned long id, unsigned long eid ){
	//suspensa
};


void fs_get_entry ( unsigned long id, unsigned long eid ){
	//suspensa
};


void fs_show_dir_entry ( unsigned long id, unsigned long eid ){
	
    //Ainda n�o implementada.	
	//return; 
};



void fs_show_dir (unsigned long id){
	
	//Ainda n�o implementada.
};


//confere clusers de um diretorio.
unsigned long fs_check_cluster (unsigned long id){
	
	//Ainda n�o implementada.
	return 0; 
};



/*
 * fs_check_fat:
 *     Check FAT.
 */
unsigned long fs_check_fat (){
	
	//Ainda n�o implementada.
	return 0; 
};



void fs_show_entry ( unsigned long id, unsigned long eid ){
	
	//Ainda n�o implementada.
	//return; 
};


unsigned long 
fs_get_entry_status( unsigned long id, 
                     unsigned long eid )
{
	//Ainda n�o implementada.
	return 0; 
};


void 
fs_set_entry_status( unsigned long id, 
                     unsigned long eid, 
					 unsigned long status )
{
	//Ainda n�o implementada.
    //return; 
};


/*
 *************
 * fsCheckMbrFile: (Essa rotina pode ser usada pra checar se o volume � fat.)
 *     Checamos um mbr carregado em algum endere�o de mem�ria.
 *
 *     Checa o registro do disco. (MBR). (disco do sistema).
 *
 *     Obs: O MBR desse sistema n�o tem o bpb no inicio do primeiro setor e 
 * sim no final do primeiro setor, antes da tabela de parti��es.
 *
 * Endere�o da mem�ria onde o MBR � carregado na inicializa��o. 0x00020000.   
 *
 * @todo: Talvez essa rotina pudesse fornecer o endere�o do buffer como 
 * argumento.
 * @todo: O mbr do sisco do sistema precisa de uma estruura que 
 * coordene o acesso a ele.
 *
 * #todo: precisa colocar tudo na estrutura que est� em fs.h
 */

//void fsCheckMBR(unsigned char* buffer)  //@todo

void fsCheckMbrFile ( unsigned char *buffer ){
	
	
	//#todo
	//mudar os argumentos para chamarmos as portas ide.
	
	int i;
	unsigned char *mbr = (unsigned char *) buffer; 
	

	//setor 0.
	my_read_hd_sector( (unsigned long) &mbr[0] , 0, 0 , 0 );  
	
	// read test (buffer, lba, rw flag, port number )
    //pio_rw_sector ( (unsigned long) ax, (unsigned long) bx, (int) 0x20, (int) 0 );		
	
	
	//message:
	printf("\n");
	printf("fsCheckMbrFile: testing MBR ...\n");
	
	// @todo:
	// Checar uma estrutura do mbr do disco do sistema,
	// para validar o acesso � ele.	
	
	// Check signature.
	if ( mbr[0x1FE] != 0x55 || mbr[0x1FF] != 0xAA )
	{	
	    printf("fsCheckMbrFile: Sig FAIL \n" );
        goto fail;		
	}
	
	//jmp
	printf("JMP: [ %x ", mbr[ BS_JmpBoot + 0 ] );
	printf("%x ", mbr[ BS_JmpBoot + 1 ] );
	printf("%x ]\n", mbr[ BS_JmpBoot + 2 ] );
	
	
	//name

	
	printf("OS name: [ ");
	for ( i=0; i<8; i++ )
	{
	    printf("%c", mbr[ BS_OEMName + i ] );
	};
	printf(" ]\n");
	
	//...
	
	
	printf("Signature: [ %x %x ] \n" , mbr[0x1FE], mbr[0x1FF] );
	
	// Continua ...
    goto done;

	
fail:	
    printf("fail\n");	
done:
    printf("Done\n");
	refresh_screen();
	return;
};


/*
 * fsCheckVbr:
 *     Checa o registro de boot de um volume.
 *     Vai no endere�o onde est� armazenado o VBR do volume atual
 *     e confere as informa��es sobre o volume.
 */
void fsCheckVbrFile( unsigned char *buffer ){
	
	unsigned char *vbr = (unsigned char *) buffer; 

    //
	// @todo:
	// Checar uma estrutura do mbr do disco do sistema,
	// para validar o acesso � ele.
	//
	
	
	// Check signature.
	if( vbr[0x1FE] != 0x55 || vbr[0x1FF] != 0xAA )
	{
	    printf("fsCheckVbrFile: Sig. Fail\n");
        goto fail;		
	};
	
	//
	// Continua ...
	//

    goto done;

	
fail:	
    printf("fsCheckVbrFile: fail\n");	
done:
    printf("Done\n");
	refresh_screen();
	return;
};



/*
 * fs_check_disk:
 *    Checa elementos do disco.
 *    Disco, Volume.
 *    Mbr. Vbr.
 * @todo: Mudar para fsCheckDisk().
 */

void fs_check_disk (){
	
    //printf("fs_check_disk: Initializing..\n");	
	//fsCheckMbrFile();
	//fsCheckVbrFile();
    //...	
    //printf("Done\n");
	//refresh_screen();	
}


/*
 **************************************************
 * MountShortFileName:
 *     This function parses a directory entry name 
 * which is in the form of "FILE   EXT" and puts it in Buffer 
 * in the form of "FILE.TXT".
 *
 * @todo fsMountShortFileName(...)
 */
 
void 
MountShortFileName ( char *buffer, 
                     struct dir_entry_d *entry )
{
    int i = 0;
    
    // Get the file name.
    while (i < 8)
    {
        if ( entry->FileName[i] == ' '){
            break;
        }

        buffer[i] = entry->FileName[i];
        i++;
    }
 
    // Get extension.
    if ( (entry->FileName[8] != ' ') )
    {
        buffer[i++] = '.';
        buffer[i++] = (entry->FileName[ 8] == ' ') ? '\0' : entry->FileName[ 8];
        buffer[i++] = (entry->FileName[ 9] == ' ') ? '\0' : entry->FileName[ 9];
        buffer[i++] = (entry->FileName[10] == ' ') ? '\0' : entry->FileName[10];
    }
}


/*
 * set_spc:
 *     Configura spc, 'Sector Per Cluster' em vari�vel global.
 *     ?? #bugbug: De qual disco ??
 */
 
void set_spc (int spc){
	
    g_spc = (int) spc;
};


/*
 * get_spc:
 *     Pega spc, Sector Per Cluster.
 *     ?? #bugbug: De qual disco ??
 */
int get_spc (){
	
    return (int) g_spc;
};


/*
 * get_filesystem_type:
 *     Pega o tipo de sistema de arquivos.
 *     ?? #bugbug: De qual volume ?? 
 */
int get_filesystem_type (){
	
    return (int) g_filesystem_type;
};


/*
 * set_filesystem_type:
 *     Configura o tipo de sistema de arquivo.
 *     ?? #bugbug: De qual volume ??  
 */
void set_filesystem_type (int type){
		
    g_filesystem_type = (int) type;
};


/*
 ***********************************************
 * fs_init_fat:
 *     Inicializa a estrutura usada no sistema de arquivos.
 *     fsInitFat()
 *     ?? #bugbug: De qual volume ?? 
 */

void fs_init_fat (){
	
	// File system structure.
	
	if ( (void *) filesystem == NULL )
	{
	    printf("fs_init_fat error: filesystem\n");
	    return;
	}

	// FAT structure.
	
	fat = (void *) malloc ( sizeof(struct fat_d) );
	
	if ((void *) fat == NULL )
	{
	    printf("fs_init_fat error: fat\n");
	    return;
		
	}else{
		
	    // Info.
	    
		fat->address = filesystem->fat_address; 
	    fat->type = filesystem->type;
	    
		//Continua ...
	};
	
	// #bugbug
	// N�o fizemos nada com a estrutura 'fat'
	// tem que passar esse ponteiro para algum lugar.
	
	// Continua a inicializa��o da fat.
};	
	

/*
 ******************************************************
 * fs_init_structures:
 *     Inicializa a estrutura do sistema de arquivos.
 *     fsInitStructures
 */
 
void fs_init_structures (){
	
    int Type;
	
	//====================
	
     //antiga. deletar,	
    filesystem = (void *) malloc ( sizeof(struct filesystem_d) );
	
	if ( (void *) filesystem == NULL )
	{
	    panic ("fs_init_structures: filesystem");
	}else{
		
	    storage->fs = filesystem;	
	};
	
	
	
	//Type.
	//#bugbug: 
    //Em qual dico e volume pegamos o tipo de sistema de arquivos.


	
	Type = (int) get_filesystem_type ();   
	
	if ( Type == 0 )
	{
	    printf("fs_init_structures error: Type");
        die();
	}else{
		
	    filesystem->type = (int) Type;	
	};
	
	
	
    switch (Type)
	{
	    case FS_TYPE_FAT16:
	        
			//Rootdir.
			filesystem->rootdir_address = VOLUME1_ROOTDIR_ADDRESS;
	        filesystem->rootdir_lba = VOLUME1_ROOTDIR_LBA;
	        
			//Fat.
			filesystem->fat_address = VOLUME1_FAT_ADDRESS;
	        filesystem->fat_lba = VOLUME1_FAT_LBA;
	        
			//Dataarea.
			//filesystem->dataarea_address = ??;
	        filesystem->dataarea_lba = VOLUME1_DATAAREA_LBA;
	        
			//sectors per cluster.
			filesystem->spc = (int) get_spc(); //vari�vel
	        filesystem->rootdir_entries = FAT16_ROOT_ENTRIES;
	        filesystem->entry_size = FAT16_ENTRY_SIZE;
			
		    break;
			
	    case FS_TYPE_EXT2:
		    //nothing for now.
		break;
		
		//case FS_TYPE_EXT3: break;
		
        default:
		    //nothing for now.
            break;		
	};
};


/*
 ********************************************************
 * fsInit:
 *     Inicializa o file system manager.
 */
 
int fsInit (){
	
#ifdef EXECVE_VERBOSE
    printf("fsInit: Initializing..\n");
#endif 
 
	// Type - Configura o tipo de sistema de arquivos usado. 
	// No caso, (fat16).
	//
	// @todo: Deve-se checar o volume ativo e ver qual sistema de arquivos est�
	//        sendo usado, ent�o depois definir configurar o tipo.
	//        O sistema operacional pode salvar o tipo usado. Nesse caso 
	//        apenas checar se ouve altera��es nas configura��es de sistema de arquivos.
	//        O registro de configura��es de disco pode ser armazenado em arquivos de metadados.
	
	set_filesystem_type (FS_TYPE_FAT16);
	
	
	// SPC 
	// Configura o n�mero de setores por cluster.
	// Nesse caso, s�o (512 bytes por setor, um setor por cluster).
	
	set_spc(1);
	
   
    // ## initialize currents ##
	
	
	//selecionando disco, volume e diret�rio.
	//estamos resetando tudo e selecionando o diret�rio raiz 
	//do vfs ... mas na verdade o diret�rio selecionado 
	//deveria ser o diret�rio onde ficam a maioria dos aplicativos.
	//para que o usu�rio possa chamar o maior n�mero de apps usando 
	//apenas comandos simples.
    //#bugbug: isso deveria se passado pelo boot ??	
	
	
	//#bugbug: 
	//Deixaremos cada m�dulo inicializar sua vari�vel.
	//Mas aqui podemos zerar esses valores.
	
	//current_disk = 0;
	//current_volume = 0;   
	//current_directory = 0;

	// Structures and fat.
    
#ifdef EXECVE_VERBOSE
	printf("fsInit: Structures..\n");
#endif
	
	fs_init_structures();
	

#ifdef EXECVE_VERBOSE
	printf("fsInit: FAT..\n");
#endif
	
	fs_init_fat();
	
	//
	// ==================== ## Streams ## =========================
	//

	// Agora inicialzamos as stream 4 e 5.
	// As anteriores foram inicializadas em stdio,
	// pois s�o o fluxo padr�o.	
	
	
	//
    //  ## volume 1 root dir  ##
	//
	
	
	//foi definido em stdio.h
	//FILE *volume1_rootdir;
	
	volume1_rootdir = (FILE *) malloc ( sizeof(FILE) );
	
	if ( (void *) volume1_rootdir == NULL )
	{
		printf("fsInit: volume1_rootdir");
		die ();
		
	} else {
		
	    volume1_rootdir->_base = (char *) VOLUME1_ROOTDIR_ADDRESS;
	    volume1_rootdir->_ptr = (char *) VOLUME1_ROOTDIR_ADDRESS;
	    volume1_rootdir->_cnt = (32 * 512) ;
	    volume1_rootdir->_file = 0; //?
	    volume1_rootdir->_tmpfname = "volume1-stream";
	
	    Streams[4] = (unsigned long) volume1_rootdir;

        storage->stream = volume1_rootdir; 		
	};
	
	

	
	
	//
    //  ## volume 2 root dir  ##
	//
	
	
	//foi definido em stdio.h
	//FILE *volume2_rootdir;
	
	volume2_rootdir = (FILE *) malloc ( sizeof(FILE) );
	
	if ( (void *) volume2_rootdir == NULL )
	{
		printf("fsInit: volume2_rootdir");
		die ();
	} else {
		
	    volume2_rootdir->_base = (char *) VOLUME2_ROOTDIR_ADDRESS;
	    volume2_rootdir->_ptr = (char *) VOLUME2_ROOTDIR_ADDRESS;
	    volume2_rootdir->_cnt = (32 * 512) ;
	    volume2_rootdir->_file = 0; //?
	    volume2_rootdir->_tmpfname = "volume2-stream";
	
	    Streams[5] = (unsigned long) volume2_rootdir;
	};
	
	
    //
	// ## Inicializando os pipes usados em execve ## 
	//
	
	
	//gramado core init execve 
	
	//aloca mem�ria para a estrutura.
	pipe_gramadocore_init_execve = (FILE *) malloc ( sizeof(FILE) );
	
	if ( (void *) pipe_gramadocore_init_execve == NULL )
	{
		printf("fsInit: pipe_gramadocore_init_execve");
		die ();
	}else{
		
	
    	//aloca mem�ria para o buffer.
	    unsigned long pipe0base = (unsigned long) malloc(512);
	    
		if ( (void *) pipe0base == NULL )
	    {
		    printf("fsInit: pipe0base");
		    die ();
	    }
	
	    pipe_gramadocore_init_execve->_base = (char *) pipe0base;
	    pipe_gramadocore_init_execve->_ptr  = (char *) pipe0base;
	    pipe_gramadocore_init_execve->_cnt  = 512;
	    pipe_gramadocore_init_execve->_file = 0; //??
	    pipe_gramadocore_init_execve->_tmpfname = "pipe0";
	
	    //0
	    Pipes[0] = (unsigned long) pipe_gramadocore_init_execve;			
	};	
	
	
	//
	// ## PWD ##
	//
	
	//inicializa p pwd support.
	fsInitializeWorkingDiretoryString ();
	
	//
	// @todo: Continua ...
	//
	
//done:

#ifdef EXECVE_VERBOSE
    printf("Done\n");
#endif 

    return (int) 0;    	
};


/*
 *****************************************
 * fsInitializeWorkingDiretoryString:
 *     Atualiza a string do diret�rio de trabalho.
 * Essa � a string que ser� mostrada antes do prompt.
 * 'pwd'> 
 * ?? isso deve sser todo o pathname do pwd ?? 
 * ex: root:/volume0>
 */
 
void fsInitializeWorkingDiretoryString (){
	
	struct volume_d *v;
	
	//'root:'
    //  ## volume list ##
    //primeiro colocamos a string que indica a lista de volumes. 
    sprintf ( current_workingdiretory_string, FS_VOLUMELIST_STRING ); 
	
	
	//'/'
	// ## separador ##
	strcat ( current_workingdiretory_string, FS_PATHNAME_SEPARATOR );


	//
	//  ## volume root dir ##	
	//
	
	v = (struct volume_d *) volumeList[current_volume];
	
	if ( (void *) v == NULL )
	{
		//fail.
		printf("fsInitializeWorkingDiretoryString: v\n");
		die();
		
	}else{
		
		if ( v->used != 1 || v->magic != 1234 )
		{
		    //fail.
		    printf("fsInitializeWorkingDiretoryString: validation\n");
		    die();
		}

	    switch (v->id)
		{
			case 0:
		        //global usada para string do nome do volume.
	            current_volume_string = (char *) FS_VOLUME0_STRING;
		 	    break;
				
			case 1:
		        //global usada para string do nome do volume.
	            current_volume_string = (char *) FS_VOLUME1_STRING;
		 	    break;
			
			default:
		        //fail.
		        printf("fsInitializeWorkingDiretoryString: default volume #todo\n");
		        die();			    
			    break;
		}
		
		
		//path string na estrutura do volume.
        sprintf ( v->path_string, current_volume_string ); 	

	    //'volumeX'
	    strcat ( current_workingdiretory_string, v->path_string );
	    //strcat ( current_workingdiretory_string, current_volume_string );		
	}
	

	// ## separador ##
	strcat ( current_workingdiretory_string, FS_PATHNAME_SEPARATOR );	

	//More ?...
    pwd_initialized = 1;
}


int fs_initialize_process_pwd ( int pid, char *string ){
	
	int i;	
	struct process_d *p;
	
	
	if ( pwd_initialized == 0 )
	{
		printf("fs_initialize_process_pwd: pwd not initialized\n"); 
		die();
	} 
	
	if (pid<0)
		return 1;	
		
    if ( (void *) string == NULL )
	    return 1;    
			

    //#importante
	//Vamos copiar a string para a estrutura do processo atual.
	
	p = (struct process_d *) processList[pid];
	
	if ( (void *) p == NULL )
	{
	    printf("fs_initialize_process_pwd: p\n");
	    die ();
		
	}else{
		
	    if ( p->used != 1 || p->magic != 1234 )
	    {
	        printf("fs_initialize_process_pwd: validation\n");
	        die ();
	    }
		
	    for ( i=0; i<32; i++ )
	    {
	        p->pwd_string[i] = string[i];	
	    }
	};
	
    return 0;
}



/*
 * fs_print_process_pwd
 *     Cada processo tem seu pr�prio pwd.
 *     Essa rotina mostra o pathname usado pelo processo.
 */

int fs_print_process_pwd ( int pid ){
	
	struct process_d *p;
	
	if ( pwd_initialized == 0 )
	{
		printf("fs_print_process_pwd: pwd not initialized\n"); 
		die();
	} 	

	if (pid<0)
		return 1;	
	
	p = (struct process_d *) processList[pid];
	
	if ( (void *) p == NULL )
	{
	    printf("fs_print_process_pwd: p\n");
	    die ();
		
	}else{
		
	    if ( p->used != 1 || p->magic != 1234 )
	    {
	        printf("fs_print_process_pwd: validation\n");
	        die ();
	    }
		
 		printf("\n PID=%d %s \n\n", p->pid, p->pwd_string );
		
		refresh_screen();
		return (int) 0;
	};
	
    //fail.
    return -1;	
};


/*
 *****************************************
 * fsUpdateWorkingDiretoryString:
 *     +Atualiza o pathname na estrutura do processo atual.
 *     +Atualiza o pathname na string global.
 */ 
 
void fsUpdateWorkingDiretoryString ( char *string ){
	
	int i;    
	struct process_d *p;

	
	if ( pwd_initialized == 0 )
	{
		printf("fsUpdateWorkingDiretoryString: pwd not initialized\n"); 
		return;
	}  	
	
    if ( (void *) string == NULL )
	    return;  
	
	p = (struct process_d *) processList[current_process];
	
	if ( (void *) p == NULL )
	{
	    printf ("fsUpdateWorkingDiretoryString: p\n");
	    die ();
		
	}else{
		
	    if ( p->used != 1 || p->magic != 1234 )
	    {
	        printf("fsUpdateWorkingDiretoryString: validation\n");
	        die ();
	    }
		
        if ( (void *) string == NULL )
	    {
			printf ("fsUpdateWorkingDiretoryString: string\n");
		    return;
	    
		} else {
			
			//atualiza a string do processo atual.
			
		    strcat ( p->pwd_string, string );	

	        // ## separador ##
		    strcat ( p->pwd_string, FS_PATHNAME_SEPARATOR );				
		
	        //atualiza a string global.
			//usando a string do processo atual.
			
			for ( i=0; i<32; i++ )
			{
	            current_workingdiretory_string[i] = p->pwd_string[i];	
	        }
		}		
	}	
}


/* 
 ************************************************
 * fs_pathname_backup:
 *     Remove n nomes de diret�rio do pathname do processo indicado no argumento.
 *     Copia o nome para a string global.
 *
 *     Remove the last N directories from PATH.  
 *     Do not leave a blank path.
 *     PATH must contain enough space for MAXPATHLEN characters. 
 *     #obs: O PID costuma ser do processo atual mesmo. 
 *
 * Credits: bash 1.05
 */
 
void fs_pathname_backup ( int pid, int n ){
	
	int i;
	struct process_d *p;
		
	if ( pwd_initialized == 0 )
	{
		printf("fs_pathname_backup: pwd not initialized\n"); 
		return;
	}  

	if ( pid<0 ){
		printf("fs_pathname_backup: PID\n"); 
		return;
	}
	
	p = (struct process_d *) processList[pid];
	
	if ( (void *) p == NULL )
	{
	    printf("fsUpdateWorkingDiretoryString: p\n");
	    die ();
		
	}else{
		
	    if ( p->used != 1 || p->magic != 1234 )
	    {
	        printf("fsUpdateWorkingDiretoryString: validation\n");
	        die ();
	    }
		
 
        char *path = (char *) p->pwd_string;
	
        register char *s = path + strlen( path );

 
        if (*path)
            s--;

        while (n--)
        {
            while (*s == '/')
	            s--;

            while (*s != '/')
	            s--;

            *++s = '\0';
        };	
		
		//atualizando a string global.
		for ( i=0; i<32; i++ )
		{
	        current_workingdiretory_string[i] = p->pwd_string[i];	
	    }
	}
}


//interface para carregar arquivo ou diret�rio.
//essa rotina � chamada por services em services.c
int 
sys_read_file ( unsigned long name, 
                unsigned long address )
{ 
	//fail
    int Ret = -1;	
	
	//#debug
	//Essa rotina funciona apenas parcialmente.
	//Por enquanto s� podemos carregar o arquivo.
	goto do_loadfile;

	/*
	
    //#importante 
	//Aqui devemos ler qual � o tipo de arquivo 
	//que se deseja carregar, e falharmos caso o 
	//o tipo deja inv�lido.
	//continuamos apenas se o tipo for um dos 
	//atendidos pelo switch abaixo.
	
	//ainda n�o sabemos.
	int file_type = -1;
	
	//pegando o tipo de arquivo nas informa��es sobre o aquivo
	file_type = fs_get_file_type (name);
	
	//aqui temos os tipos de arquivo atendidos por essa rotina.
	switch (file_type)
	{
		//load file.
		case 1000:
		    goto do_loadfile;
			break;
			
		case 1001:
            goto do_loaddir;
			break;
			
		//continua	
		//...	
			
		//Isso ficar� aqui por compatibilidade,
		//tem rotinas antigas que n�o usavam esse argumento.
		//#todo: podemos colocar um hang aqui e falharmos o sistema 
		//caso o argumento option seja inv�lido.
		default:
		    goto do_loadfile;
		    break;
	};
	
	*/
	//
	// ## LOAD FILE ##
	//
	
do_loadfile:	
	
    taskswitch_lock();
    scheduler_lock();			
    
	Ret = (int) fsLoadFile ( VOLUME1_FAT_ADDRESS,  
				    VOLUME1_ROOTDIR_ADDRESS, 
	                (unsigned char *) name, 
					(unsigned long) address );    		
	
	scheduler_unlock();
    taskswitch_unlock();
	return (int) Ret;
			
fail:			
    return 1;	
};


//interface para salvar arquivo ou diret�rio.
//isso pode ser usado para criar um diret�rio
//ou copiar um diret�rio. 
int
sys_write_file ( char *file_name, 
                 unsigned long file_size,
                 unsigned long size_in_bytes,			
                 char *file_address,
                 char flag )  
{
	
	//#todo:
	//vamos fazer igual ao sys_read_file 
	//e criarmos op��es ... se poss�vel.
	
	int Ret = -1;
    
	taskswitch_lock();
	scheduler_lock();	
		    
	Ret = (int) fsSaveFile ( (char *) file_name,    //name
	                (unsigned long) file_size,      //3, //@todo: size in sectors 
				    (unsigned long) size_in_bytes,  //255, //@todo: size in bytes
				    (char *) file_address,          //arg3,//address
				    (char) flag );                  //,arg4 ); //flag
						
	scheduler_unlock();
	taskswitch_unlock();

    return Ret;	
}



//
// End.
//

