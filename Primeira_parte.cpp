//bibliotecas utilizadas
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

//estrutura de cada m�sica
typedef struct musica {
	int id;
	char titulo[200];
	char artista[200];
	char album[200];
	int duracao; //segundos
}musica;

//estrutura da lista duplamente encadeada onde cada n� aponta para uma struct m�sica
typedef struct musica_no {
	musica *musica; //campo valor - ponteiro chamado 'musica' para uma struct do tipo 'musica'
	struct musica_no *ant;
	struct musica_no *prox;
} musica_no;

//estrutura da playlist - ser� uma lista circular
typedef struct playlist_no {
	musica *musica;
	struct playlist_no *prox;
} playlist_no;

typedef struct lplaylists_no{
	int id;
	char nome[200];
	playlist_no *musicas;
	struct lplaylists_no *prox;
}lplaylists_no;


//vari�veis globais
int qtd_musica = 0; //armazena o n�mero de m�sicas registradas na lista de m�sicas
int qtd_playlists = 0;
playlist_no* enderecos_play[100]; //vetor que armazena endere�o do cabe�a das playlists criadas

//declara��o das fun��es
void cadastra_musica(musica_no*); //cadastrar m�sica
void imprimi_todas(musica_no*); //imprimitodas as m�sicas
void format_duracao(int); //formata dura��o da m�sica se acordo com o requisito
playlist_no* criar_playlist(musica_no*); //cria a playlist de m�sicas
bool insere_playlist(musica_no*, playlist_no*, int);
void cria_lista_playlist(lplaylists_no*, playlist_no*);
void imprimi_playlist(lplaylists_no*, int);
void remove_musica(musica_no*, lplaylists_no*);

int main(void){
	//cria��o do cabe�a para a lista duplamente encadeada
	musica_no *cabeca_Nod;
	cabeca_Nod = (musica_no*)malloc(sizeof(musica_no));
	cabeca_Nod->prox = NULL;
	cabeca_Nod->ant = NULL;
	cabeca_Nod->musica = NULL;
	
	//cria cabe�a para lista simplesmente encadeada de playlists
	lplaylists_no* cabeca_lplay;
	cabeca_lplay = (lplaylists_no*)malloc(sizeof(lplaylists_no));
	cabeca_lplay->musicas = NULL;
	cabeca_lplay->prox = NULL;
	
	//vari�vel de controle do primeiro la�o
	int opcao=0;
	
	//menu principal
	while(opcao!=7){
		printf("-------CADASTRO DE MUSICAS E PLAYLISTS------- \n");
		printf("1 - Cadastro Musica \n");
		printf("2 - Imprimir todos as Musicas cadastradas \n");
		printf("3 - Criar Playlist\n");
		printf("4 - Alterar a ordem das Musicas aleatoriamente em uma Playlist - SHUFFLE \n");
		printf("5 - Imprimir Playlist \n");
		printf("6 - Remover Musica do cadastro \n");
		printf("7 - Sair \n");
		
		//seleciona a entrada
		printf("Escolha a opcao desejada: ");
		scanf("%d", &opcao);
		printf("\n");
		
		//Cadastra m�sica(s)
		if (opcao == 1){
			cadastra_musica(cabeca_Nod);
		}
		
		//imprimi todas as m�sicas (que est�o na lista duplamente encadeada)
		else if (opcao == 2){
			//analisa se existem m�sicas cadastradas
			if(qtd_musica == 0){
				printf("Nao ha musicas cadastradas! \n");
			}else{
				imprimi_todas(cabeca_Nod->prox);
			}
		}
		
		//cria playlist
		else if (opcao == 3){
			//vari�veis
			int escolha;
			
			//recebe o endere�o do cabe�a da playlist criada
			playlist_no* endereco;
			endereco = criar_playlist(cabeca_Nod);
			
			if(endereco != NULL){
				printf("Deseja salvar a Playlist criada? Se nao quiser ela sera excluida \n 1-SIM \n 2-NAO\n");
				fflush(stdin);
				scanf("%d", &escolha);
			
				while(escolha != 1 && escolha !=2){
					printf("Valor digitado incorreto, digite novamente:");
					scanf("%d", &escolha);
				}
			
				//insere ou descarta a playlist criada na lista de playlists
				if(escolha == 1){
					cria_lista_playlist(cabeca_lplay, endereco);
					printf("Playlist adicionada com sucesso! \n\n");
				}else{
					printf("Playlist descartada com sucesso! \n\n");
				}
			}
			
			
		}
		
		//shuffle - altera aleatoriamente a ordem das m�sicas dentro de uma playlist
		else if (opcao == 4){
			printf("Ok 4\n");
		}
		
		//imprimir playlist
		else if (opcao == 5){
			//vari�veis
			int numero_id;
			
			if(qtd_playlists != 0){
				printf("Digite o ID da playlist que deseja imprimir:");
				fflush(stdin);
				scanf("%d", &numero_id);
			
				imprimi_playlist(cabeca_lplay->prox, numero_id);
			}else{
				printf("Nao ha Playlist cadastrada\n");
			}
			
		}
		
		//ordena struct de alunos de acordo com o m�todo escolhido
		else if (opcao == 6){
			if(qtd_musica != 0){
				remove_musica(cabeca_Nod->prox, cabeca_lplay->prox);
			}else{
				printf("Nao ha musicas cadastradas!\n");
			}
		}
		
		//remove m�sica(s) do cadastro
		else if (opcao == 7){
			printf("Obrigado, fim do programa! \n");
		}
		
		else{
			printf("OPCAO INVALIDA, TENTE NOVAMENTE! \n");
		}
	}
}

//cadastra nova m�sica
void cadastra_musica(musica_no *ini){ //a inser��o ser� sempre depois do cabe�a
	//aloca um espa�o na mem�ria para uma struct do tipo musica
	musica *musica_nova = (musica*)malloc(sizeof(musica));
	
	//ID
	qtd_musica++;
	musica_nova->id = qtd_musica;
	
	//T�TULO
	fflush(stdin);
	printf("Digite o titulo da musica : ");
	gets(musica_nova->titulo);
		
	//ARTISTA
	fflush(stdin);
	printf("Digite o nome do artista : ");
	gets(musica_nova->artista);
		
	//�LBUM
	fflush(stdin);
	printf("Digite o nome do album : ");
	gets(musica_nova->album);
	
	//DURA��O
	fflush(stdin);
	printf("Digite a duracao da musica em segundos: ");
	scanf("%d", &musica_nova->duracao);
		
	printf("\n");
	
	//PARTE DA INSER��O DA M�SICA NA LISTA DUPLAMENTE ENCADEADA//
	musica_no *novo;
	novo = (musica_no*)malloc(sizeof(musica_no));
	novo->musica = musica_nova;
	novo->prox = ini->prox;
	novo->ant = ini;
	//analisa se j� existia alguma m�sica cadastrada
	if(ini->prox){
		ini->prox->ant = novo;
		ini->prox = novo;
	}else{
		ini->prox = novo;
	}

}

//imprimi todas as m�sicas cadastradas
void imprimi_todas(musica_no *ini){
	
	while(ini){
		printf("**MUSICA %d**\n", ini->musica->id);
		printf("Titulo: %s\n", ini->musica->titulo);
		printf("Artista: %s\n", ini->musica->artista);
		printf("Album: %s\n", ini->musica->album);
		format_duracao(ini->musica->duracao);
		
		ini = ini->prox;
	}
	
}

//formata��o da dura��o da m�sica
void format_duracao(int duracao){
	//vari�veis
	int vetor[5];
	int hora, min, seg;
	int res_divisao_hora;
	int res_divisao_min;
	
	if(duracao >= 3600){ //analisa se existe pelo menos 1 hora
		hora = duracao / 3600;
		res_divisao_hora = duracao % 3600;
		
		if(res_divisao_hora >= 60){ //analisa se existe pelo menos 1 minuto
			min = res_divisao_hora / 60;
			seg = res_divisao_hora % 60;
			
			vetor[0] = hora;
			vetor[1] = min;
			vetor[2] = seg;
		}else{ //caso a dura��o seja menos de um minuto
			min = 0;
			seg = res_divisao_hora;
			
			vetor[0] = hora;
			vetor[1] = min;
			vetor[2] = seg;
		}
		
	} else if(duracao >= 60){ //analisa se existe pelo menos um minuto
		hora = 0;
		min = duracao / 60;
		seg = duracao % 60;
		
		vetor[0] = hora;
		vetor[1] = min;
		vetor[2] = seg;
		
	}else{
		hora = 0;
		min = 0;
		seg = duracao;
		
		vetor[0] = hora;
		vetor[1] = min;
		vetor[2] = seg;
		
	}
	
	//exibe hor�rio formatado na tela
	printf("Duracao: %d:%d:%d", vetor[0], vetor[1], vetor[2]);
	printf("\n \n");
}

//cria��o de playlist
playlist_no* criar_playlist(musica_no* cabeca_Nod){
	//vari�veis
	char ids[100];
	char string_temp[10]; //vari�vei auxiliar para armazenar cada n�mero em forma de string
	int aux_temp = 0; //�ndice auxiliar de temp			
	int valor_inteiro; //armazena o valor inteiro da string convertida
	bool verifica_id, verifica_geral = false; //vai verificar se alguma m�sica das passadas como par�metro foi adicionada
	
	//verifica se existe alguma m�sica cadastrada
	if(qtd_musica == 0){
		printf("Nao ha musicas cadastradas! \n");
	}else{
		fflush(stdin);
		printf("Digite os valores de ID das musicas da playlist: ");
		gets(ids);
	
		//cria��o do cabe�a para a lista circular - cada lista circular tem um cabe�a
		playlist_no *cabeca_Circ;
		cabeca_Circ = (playlist_no*)malloc(sizeof(playlist_no));
		cabeca_Circ->musica = NULL;
		cabeca_Circ->prox = cabeca_Circ;
		
		//percorre a string inteira
		for(int i=0; strlen(ids); i++){ 
			if(ids[i] == ' '|| ids[i] == '\0'){
				string_temp[aux_temp] = '\0'; //finalizo meu auxiliar
				valor_inteiro = atoi(string_temp); 
				verifica_id = insere_playlist(cabeca_Nod, cabeca_Circ, valor_inteiro); //procura o valor do id na lista de m�sicas - se n�o encontrar nenhum valor retorna 'false'
				
				//verifica se j� foi retornado 'true' alguma vez
				if(verifica_id == true){
					verifica_geral = true;
				}
				
				//verifica se a ids j� chegou no �ltimo digito
				if(ids[i] == '\0'){ 
					break;
				}else{
					aux_temp = 0;
				}
				
			}
			else{
				string_temp[aux_temp] = ids[i]; 
				aux_temp++;
			}
		}
		//analisa se algum id foi encontrado
		if(verifica_geral == false){
			printf("Nenhuma musica das requisitadas estao cadastradas! \n\n");
			free(cabeca_Circ);
			return NULL;
		}else{
			printf("Playlist criada com sucesso! \n\n");
			return cabeca_Circ;
		}
	}
}

//insere uma m�sica na playist de m�sicas
bool insere_playlist(musica_no* ini_dup, playlist_no* ini_circ, int valor_id){
	//vari�veis
	playlist_no* novo_circ;
	bool verifica_id = false;
	
	ini_dup = ini_dup->prox; //a busca inicia no prox do cabe�a
	
	//percorre a lista duplamente encadeada procurando pelo valor do id
	while(ini_dup && ini_dup->musica->id != valor_id){
		ini_dup = ini_dup->prox;
	}
	if(ini_dup){
		verifica_id = true;	//m�sica com o id passado foi encontrada
		
		novo_circ = (playlist_no*)malloc(sizeof(playlist_no));
		novo_circ->prox = ini_circ->prox;
		ini_circ->prox = novo_circ;
		novo_circ->musica = ini_dup->musica;

	}else{
		printf("Musica %d nao existe!\n", valor_id);
	}
	
	return verifica_id;
}

//insere uma playist na lista de playlists
void cria_lista_playlist(lplaylists_no* cabeca_lplay, playlist_no* endereco){
	//cria novo n� na lista de playlist
	lplaylists_no* novo_lplay;
	novo_lplay = (lplaylists_no*)malloc(sizeof(lplaylists_no));
	
	//incrementa a quantidade de playlists adicionadas
	qtd_playlists++;
	
	//adiciona ID
	novo_lplay->id = qtd_playlists;
	
	//adiciona nome
	fflush(stdin);
	printf("Digite o Nome da Playlist: ");
	gets(novo_lplay->nome);
	
	//adiciona playlist no n�
	novo_lplay->musicas = endereco;
	
	//adiciona o n� novo na lista
	novo_lplay->prox = cabeca_lplay->prox;
	cabeca_lplay->prox = novo_lplay;
}

void imprimi_playlist(lplaylists_no* ini, int numero_id){
	//variaveis
	playlist_no* aux;
	
	//percorre a lista de playlists procurando pelo n�mero de ID que foi passado
	while(ini && ini->id != numero_id){
		ini = ini->prox;
	}
	
	//verifica se achou a playlist passada
	if(ini){
		aux = ini->musicas->prox; //aux recebe o 'prox' do cabe�a da playlist
		while(aux != ini->musicas){
			printf("### Playlist de ID %d ###\n", numero_id);
			printf("**MUSICA %d**\n", aux->musica->id);
			printf("Titulo: %s\n", aux->musica->titulo);
			printf("Artista: %s\n", aux->musica->artista);
			printf("Album: %s\n", aux->musica->album);
			format_duracao(aux->musica->duracao);
			
			aux = aux->prox;
		}
	}else{
		printf("O ID informado nao pertence a nenhuma Playlist! \n");
	}
}

void remove_musica(musica_no *ini_dup, lplaylists_no *ini_list){ //prox do cabe�a da duplamente encadeada e da lista de playlists
	//vari�veis
	int id;
	musica_no* aux_dup;
	playlist_no* aux_p; 
	playlist_no* aux_q; 
			
	printf("Digite o ID da musica que deseja remover: ");
	fflush(stdin);
	scanf("%d", &id);
	
	//REMO��O DA M�SICA DA LISTA CIRCULAR - PLAYLIST
	while(ini_list){
		aux_p = ini_list->musicas; //aponta para o cabe�a da playlist em quest�o
		aux_q = ini_list->musicas->prox; //aponta para o pr�ximo do cabe�a na playlist em quest�o
		
		while(aux_q != ini_list->musicas && aux_q->musica->id != id){
			aux_q = aux_q->prox;
			aux_p = aux_p->prox;
		}
		//verifica se o n� a ser exclu�do aponta para a cabe�a
		if(aux_q != ini_list->musicas){
			aux_p->prox = aux_q->prox;
			free(aux_q);
		}
		ini_list = ini_list->prox;
	}
	
	//REMO��O DA M�SICA NA LISTA DUPLAMENTE ENCADEADA - LISTA DE M�SICAS
	while(ini_dup && ini_dup->musica->id != id){
			ini_dup = ini_dup->prox;
		}
	if(ini_dup){
		aux_dup = ini_dup->ant;
		aux_dup->prox = ini_dup->prox;
		//analisa se tem algum n� depois do passado
		if(ini_dup->prox){
			printf("encontrou a musica no meio das musicas \n");
			ini_dup->prox->ant = aux_dup;
		}
		//remove n� que aponta para essa lista
		free(ini_dup);
		qtd_musica--;//decrementa a quantidade total de m�sicas cadastradas
	}else{
		printf("Musica nao cadastrada!\n");
	}	
}


