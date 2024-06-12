/*****************************************************************//**
 * @file   ListaInteiros.c
 * @brief  Ficheiro C com as funcoes relacionadas com a lista de inteiros
 * 
 * @author David Carvalho
 * @date   May 2024
 *********************************************************************/

#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Header.h"

/// <summary>
/// Cria uma lista de inteiros
/// </summary>
/// <returns>Retorna a lista de caracteres</returns>
ListaInteiros* CriarListaInteiros() {
	ListaInteiros* aux = (ListaInteiros*)malloc(sizeof(ListaInteiros));

	if (aux != NULL) {
		aux->num = NULL;
		aux->proxInteiro = NULL;
	}

	return aux;
}

/// <summary>
///  Cria uma lista de inteiros de um determinado tamanho
/// </summary>
/// <param name="tam">Tamanho da lista</param>
/// <param name="res">Retorna 0 se a lista nao for criada, retorna 1 se a lista for criada</param>
/// <returns>Retorna nulo se o tamanho for 0, retorna a lista de a mesma for criada</returns>
ListaInteiros* CriarListasInteiros(int tam, int* res) {
	if (tam == 0) { *res = 0; return NULL; }
	ListaInteiros* lista = NULL;
	for (int i = 0; i < tam; i++) {
		ListaInteiros* aux = CriarListaInteiros();
		lista = AdicionarNumeroListaInteirosFim(lista, aux, res);
	}
	return lista;
}

#pragma region Adicionar
/// <summary>
///  Adiciona dados a uma lista de inteiros
/// </summary>
/// <param name="lista">Lista</param>
/// <param name="num">Numero</param>
/// <param name="res">Retorna 0 se os dados nao forem adicionados, retorna 1 se os dados forem adicionados</param>
/// <returns>Retorna nulo se a lista for nula, retorna a lista com os dados adicionados se os mesmos forem adicionados</returns>
ListaInteiros* AdiconarDadosListaInteiros(ListaInteiros* lista, int num, int* res) {
	if (lista == NULL) { *res = 0; return NULL; }
	lista->num = num;
	*res = 1;
	return lista;
}

/// <summary>
/// Adicona um numero a uma lista de inteiros no inicio da lista de inteiros
/// </summary>
/// <param name="lista">Lista de inteiros</param>
/// <param name="numero">Numero do tipo lista de inteiros</param>
/// <param name="res">Retorna 0 se nao for adicionado, retorna 1 se for adicionado</param>
/// <returns>Retorna nulo se a lista for nula, retorna a lista sem o numero adicionado se o numero for nulo, retorna a lista com o numero adicionado se for adicionado</returns>
ListaInteiros* AdicionarNumeroListaInteirosInicio(ListaInteiros* lista, ListaInteiros* numero, int* res) {
	if (lista == NULL && numero != NULL) { *res = 1;  return lista = numero; }
	if (lista == NULL) { *res = 0; return NULL; }
	numero->proxInteiro = lista;
	lista = numero;
	return lista;
}

/// <summary>
/// Adicona um numero a uma lista de inteiros no final da lista de inteiros
/// </summary>
/// <param name="lista">Lista de inteiros</param>
/// <param name="numero">Numero do tipo lista de inteiros</param>
/// <param name="res">Retorna 0 se nao for adicionado, retorna 1 se for adicionado</param>
/// <returns>Retorna nulo se a lista for nula, retorna a lista sem o numero adicionado se o numero for nulo, retorna a lista com o numero adicionado se for adicionado</returns>
ListaInteiros* AdicionarNumeroListaInteirosFim(ListaInteiros* lista, ListaInteiros* numero, int* res) {
	if (lista == NULL && numero != NULL) { *res = 1;  return lista = numero; }
	if (lista == NULL) { *res = 0; return NULL; }

	ListaInteiros* aux = lista;
	while (aux->proxInteiro != NULL)
		aux = aux->proxInteiro;

	aux->proxInteiro = numero;

	return lista;
}

/// <summary>
/// Adiciona a uma lista de inteiros todos os ids dos vertices presentes numa lista de vertices.
/// </summary>
/// <param name="lista">Lista de inteiros</param>
/// <param name="vertices">Lista de vertices</param>
/// <param name="res">Retorna 0 se nao for adicionado, retorna 1 se for adicionado</param>
/// <returns>Retorna nulo se a lista de inteiros ou a lista de vertices for nula, retorna a lista de inteiros com os ids dos vertices</returns>
ListaInteiros* AdicionarVerticeIdListaInteiros(ListaInteiros* lista, Vertice* vertices, int* res) {
	if (vertices == NULL) { *res = 0; return NULL; }
	Vertice* aux = vertices;
	ListaInteiros* auxLista = lista;
	while (aux != NULL) {
		auxLista = AdiconarDadosListaInteiros(auxLista, aux->id, res);
		aux = aux->proxVertice;
		auxLista = auxLista->proxInteiro;
	}
	return lista;
}

/// <summary>
/// Cria e adiciona um numero a uma lista de inteiros no inicio, retornando como parametro o numero na posicao mais alta da lista
/// </summary>
/// <param name="lista">Lista de inteiros</param>
/// <param name="num">Numero</param>
/// <param name="res">Retorna 0 se nao for adicionado, retorna 1 se for adicionado</param>
/// <returns>Retorna o numero que esta na ultima posicao da lista de inteiros se o numero for adicionado, se nao for adicionado retorna o rear</returns>
ListaInteiros* CriarAdicionarNumeroListaInteirosInicio(ListaInteiros* lista, int num, int* res) {
	ListaInteiros* numero = CriarListaInteiros();
	numero = AdiconarDadosListaInteiros(numero, num, res);
	lista = AdicionarNumeroListaInteirosInicio(lista, numero, res);
	return lista;
}

/// <summary>
/// Cria e adiciona um numero a uma lista de inteiros no fim, retornando como parametro o numero na posicao mais alta da lista
/// </summary>
/// <param name="lista">Lista de inteiros</param>
/// <param name="num">Numero</param>
/// <param name="top">Posicao do ultimo numero da lista</param>
/// <param name="res">Retorna 0 se nao for adicionado, retorna 1 se for adicionado</param>
/// <returns>Retorna o numero que esta na ultima posicao da lista de inteiros se o numero for adicionado, se nao for adicionado retorna o top</returns>
ListaInteiros* CriarAdicionarNumeroListaInteirosFim(ListaInteiros* lista, int num, int* top, int* res) {
	ListaInteiros* numero = CriarListaInteiros();
	numero = AdiconarDadosListaInteiros(numero, num, res);
	lista = AdicionarNumeroListaInteirosFim(lista, numero, res);
	if (*res == 1)
		*top = numero->num;
	return lista;
}

/// <summary>
/// Cria e adiciona um numero a uma lista de inteiros no fim
/// </summary>
/// <param name="lista">Lista de inteiros</param>
/// <param name="num">Numero</param>
/// <param name="res">Retorna 0 se nao for adicionado, retorna 1 se for adicionado</param>
/// <returns>Retorna o numero que esta na ultima posicao da lista de inteiros se o numero for adicionado, se nao for adicionado retorna o top</returns>
ListaInteiros* CriarAdicionarNumeroListaInteirosFim2(ListaInteiros* lista, int num, int* res) {
	ListaInteiros* numero = CriarListaInteiros();
	numero = AdiconarDadosListaInteiros(numero, num, res);
	lista = AdicionarNumeroListaInteirosFim(lista, numero, res);
	return lista;
}
#pragma endregion

#pragma region Remover
/// <summary>
/// Remove um numero de uma lista de inteiros, retornando com um parametro o numero que esta a cima da lista
/// </summary>
/// <param name="lista">Lista de inteiros</param>
/// <param name="num">Numero a remover da lista de inteiros</param>
/// <param name="top">Posicao do ultimo numero da lista</param>
/// <param name="res">Retorna 0 se nao for removido, retorna 1 se for removido</param>
/// <returns></returns>
ListaInteiros* RemoverNumeroListaInteirosComTop(ListaInteiros* lista, int num, int* top, int* res) {
	if (lista == NULL) { *res = 0; return NULL; }

	if (VerificarNumeroListaInteiros(lista, num) != 1) { *res = 1; return lista; }

	ListaInteiros* aux = lista;
	ListaInteiros* ant = NULL;

	//Caso so exista um numero na lista
	if (lista->proxInteiro == NULL) {
		*top = -1;
	}

	while (aux->num != num) {
		ant = aux;
		aux = aux->proxInteiro;
	}
	if (ant == NULL) {
		lista = aux->proxInteiro;
		free(aux);
	}
	else {
		if (aux->proxInteiro == NULL) {
			ant->proxInteiro = NULL;
			*top = ant->num;
			free(aux);
		}
		else {
			ant->proxInteiro = aux->proxInteiro;
			*top = aux->proxInteiro;
			free(aux);
		}
	}
	*res = 1;
	return lista;
}

/// <summary>
/// Remove um numero de uma lista de inteiros
/// </summary>
/// <param name="lista">Lista de inteiros</param>
/// <param name="num">Numero a remover da lista de inteiros</param>
/// <param name="top">Posicao do ultimo numero da lista</param>
/// <param name="res">Retorna 0 se nao for removido, retorna 1 se for removido</param>
/// <returns></returns>
ListaInteiros* RemoverNumeroListaInteiros(ListaInteiros* lista, int num, int* res) {
	if (lista == NULL) { *res = 0; return NULL; }

	if (VerificarNumeroListaInteiros(lista, num) != 1) { *res = 1; return lista; }

	ListaInteiros* aux = lista;
	ListaInteiros* ant = NULL;

	while (aux->num != num) {
		ant = aux;
		aux = aux->proxInteiro;
	}
	if (ant == NULL) {
		lista = aux->proxInteiro;
		free(aux);
	}
	else {
		if (aux->proxInteiro == NULL) {
			ant->proxInteiro = NULL;
			free(aux);
		}
		else {
			ant->proxInteiro = aux->proxInteiro;
			free(aux);
		}
	}
	*res = 1;
	return lista;
}

#pragma endregion

#pragma region Verificacoes
/// <summary>
/// Vertifica se existe algum numero dentro da lista de numeros
/// </summary>
/// <param name="lista">Lista de numeros</param>
/// <returns>Retorna 0 nao existe nenhum numero, retorna 1 se existe algum numero</returns>
int VerificarListaInteirosVazia(ListaInteiros* lista) {
	if (lista == NULL) return 0;
	else return 1;
}

/// <summary>
/// Verifica se existe o numero na lista de inteiros
/// </summary>
/// <param name="lista">Lista de inteiros</param>
/// <param name="num">Numero</param>
/// <returns>Retorna 0 se a lista for nula ou se nao existir o numero, retorna 1 se existir o numero</returns>
int VerificarNumeroListaInteiros(ListaInteiros* lista, int num) {
	if (lista == NULL) return 0;

	ListaInteiros* aux = lista;
	while (aux != NULL) {
		if (aux->num == num)
			return 1;
		aux = aux->proxInteiro;
	}
	return 0;
}
#pragma endregion

#pragma region Outro
/// <summary>
/// Encontra um numero dentro de uma lista de inteiros e retorna esse mesmo numero da lista de inteiros
/// </summary>
/// <param name="lista">Lista de inteiros</param>
/// <param name="num">Numero</param>
/// <param name="res">Retorna 0 se nao o encontrar, retorna 1 se o encontrars</param>
/// <returns>Retorna nulo se a lista for nula, retorna o numero do tipo listaInteiros se o numero for encontrado</returns>
ListaInteiros* EncontrarNumeroListaInteiros(ListaInteiros* lista, int num, int* res) {
	if (lista == NULL) { *res = 0; return NULL; }
	ListaInteiros* aux = lista;
	while (aux != NULL) {
		if (aux->num == num) {
			*res = 1;
			return aux;
		}
		aux = aux->proxInteiro;
	}

	*res = 0;
	return lista;
}

/// <summary>
/// Encontra o ultimo numero (Encontrar o top da stack)
/// </summary>
/// <param name="stack">Stack lista de inteiros</param>
/// <returns>Retorna 0 se a lista de inteiros for nula, retorna o ultimo numero da lista</returns>
int EncontrarUltimoNumeroListaInteiros(ListaInteiros* lista) {
	if (lista == NULL) return 0;
	ListaInteiros* aux = lista;
	while (aux->proxInteiro != NULL) {
		aux = aux->proxInteiro;
	}
	return aux->num;
}
#pragma endregion

