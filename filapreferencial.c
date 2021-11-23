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
				// if(atual->id == novo->id)
				// 	break;
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
		}
	}

	return true;
}

bool atenderPrimeiraDaFila(PFILA f, int* id){

	/* COMPLETE */


	return false;
}


bool desistirDaFila(PFILA f, int id){

	/* COMPLETE */


	return false;
}
/*
int main() {
	PFILA f = criarFila();
	int id;
	bool ehPreferencial;
	bool res;

	res = inserirPessoaNaFila(f, 1, false);
	if(res) printf("Insercao retornou true (0). [OK]\n");
	else printf("Insercao retornou false (0).\n");
	res = inserirPessoaNaFila(f, 2, false);
	if(res) printf("Insercao retornou true (0).\n");
	else printf("Insercao retornou false (0). [OK]\n");
	res = inserirPessoaNaFila(f, 0, true);
	exibirLog(f);

	return 0;
}
*/