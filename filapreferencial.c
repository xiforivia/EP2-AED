/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2021                           **/
/**   <turma> - Prof. Luciano Antonio Digiampietri                  **/
/**                                                                 **/
/**   EP 2 - Fila Preferencial                                      **/
/**                                                                 **/
/**   <nome do(a) aluno(a)>                   <numero USP>          **/
/**                                                                 **/
/*********************************************************************/

#include "filapreferencial.h"

PFILA criarFila(){
    PFILA res = (PFILA) malloc(sizeof(FILAPREFERENCIAL));
    res->cabeca = (PONT) malloc(sizeof(ELEMENTO));
    res->inicioNaoPref = res->cabeca;
    res->cabeca->id = -1;
    res->cabeca->ehPreferencial = false;
    res->cabeca->ant = res->cabeca;
    res->cabeca->prox = res->cabeca;
    return res;
}

int tamanho(PFILA f){
	PONT atual = f->cabeca->prox;
	int tam = 0;
	while (atual != f->cabeca) {
		atual = atual->prox;
		tam++;
	}
	return tam;
}

PONT buscarID(PFILA f, int id){
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		if (atual->id == id) return atual;
		atual = atual->prox;
	}
	return NULL;
}

void exibirLog(PFILA f){
	int numElementos = tamanho(f);
	printf("\nLog fila [elementos: %i]\t- Inicio:", numElementos);
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		printf(" [%i;%i]", atual->id, atual->ehPreferencial);
		atual = atual->prox;
	}
	printf("\n                       \t-    Fim:");
	atual = f->cabeca->ant;
	while (atual != f->cabeca) {
		printf(" [%i;%i]", atual->id, atual->ehPreferencial);
		atual = atual->ant;
	}
	printf("\n\n");
}


bool consultarPreferencial(PFILA f, int id){
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		if (atual->id == id) return atual->ehPreferencial;
		atual = atual->prox;
	}
	return -1;
}


bool inserirPessoaNaFila(PFILA f, int id, bool ehPreferencial)
{
	if(id < 0 || buscarID(f, id) != NULL)
		return false;
	
	PONT novo;
  	novo = (PONT) malloc(sizeof(ELEMENTO));
	
	novo->id = id;
	novo->ehPreferencial = ehPreferencial;

	if(f->cabeca->prox == f->cabeca && f->cabeca->ant == f->cabeca) //se a fila estiver vazia
	{
		f->cabeca->prox = novo;
		f->cabeca->ant = novo;
		novo->prox = f->cabeca; //ou novo->prox = f->cabeca->prox
		novo->ant = f->cabeca;
		if(ehPreferencial == false)
			f->inicioNaoPref = novo;
	}
	else //se a fila não está vazia
	{
		if(ehPreferencial == true)
		{
			PONT atual = f->cabeca->ant;
			while (atual != f->cabeca)
			{
				if(atual->ehPreferencial == true) //pega o ultimo preferencial
				{
					novo->prox = atual->prox;
					novo->ant = atual;
					atual->prox = novo;
					f->inicioNaoPref->ant = novo;
					return true;
				}
				atual = atual->ant;
			}
			//se não achou nenhum preferencial, então será o primeiro preferencial
			novo->prox = f->inicioNaoPref;
			novo->ant = f->cabeca;
			f->cabeca->prox = novo;
			f->inicioNaoPref->ant = novo;
		}
		else //não é preferencial = insere no fim
		{
			novo->prox = f->cabeca;
			novo->ant = f->cabeca->ant;
			f->cabeca->ant = novo;
			novo->ant->prox = novo;

			PONT atual = f->cabeca->prox;
			bool inicio = true;
			while (atual != novo) //vai até um antes do elemento novo
			{
				if(atual->ehPreferencial == false) //se existir qualquer um não preferencial além do novo
					inicio = false;
				
				atual = atual->prox;
			}
			if(inicio == true) //se o novo é o primeiro não preferencial
				f->inicioNaoPref = novo;
		}
	}
	return true;
}

bool atenderPrimeiraDaFila(PFILA f, int* id)
{
	if(f->cabeca->prox == f->cabeca && f->cabeca->ant == f->cabeca) //se não tem ninguém na fila
		return false;

	*id = f->cabeca->prox->id;

	PONT atender;
	atender = buscarID(f, f->cabeca->prox->id);

	if(atender->ehPreferencial == false) //se a pessoa atendida não for preferencial
		f->inicioNaoPref = atender->prox; //o primeiro não preferencial passa a ser o próximo
	
	f->cabeca->prox = atender->prox; //o segundo passa a ser o primeiro
	atender->prox->ant = f->cabeca; //ele passa a ser o nó cabeça
	free(atender);

	return true;	
}

bool desistirDaFila(PFILA f, int id)
{
	PONT remover;
	remover = buscarID(f, id);

	if(remover == NULL) //se a pessoa não está na fila
	return false;
	
	if(f->inicioNaoPref->id == id)
		f->inicioNaoPref = remover->prox;

	remover->ant->prox = remover->prox; //o anterior vai ter como proximo quem era o proximo do desistente
	remover->prox->ant = remover->ant; //o proximo vai ter como anterior quem era o anterior do disistente
	
	free(remover);

	return true;
}

// int main() {
// 	PFILA f = criarFila();
// 	int id;
// 	bool ehPreferencial;
// 	bool res;

// 	exibirLog(f);
// 	res = inserirPessoaNaFila(f, 7, true);
// 	if(res) printf("Insercao retornou true (14). [OK]\n");
// 	else printf("Insercao retornou false (14).\n");
// 	exibirLog(f);
// 	res = inserirPessoaNaFila(f, 8, false);
// 	if(res) printf("Insercao retornou true (15). [OK]\n");
// 	else printf("Insercao retornou false (15).\n");
// 	exibirLog(f);
// 	res = inserirPessoaNaFila(f, 9, true);
// 	if(res) printf("Insercao retornou true (16). [OK]\n");
// 	else printf("Insercao retornou false (16).\n");
// 	exibirLog(f);

// 	return 0;
// }
