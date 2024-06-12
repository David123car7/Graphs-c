/*****************************************************************//**
 * @file   Adjacentes.c
 * @brief  Ficheiro C com as funcoes relacionadas com os vertices adjacentes
 * 
 * @author David Carvalho
 * @date   May 2024
 *********************************************************************/

#pragma warning (disable:4996)
#include <stdio.h>
#include <malloc.h>
#include "Header.h"

/// <summary>
/// Cria um vertice adjacente
/// </summary>
/// <returns>Retorna vertice adjacente criado</returns>
Adjacente* CriarAdjacente() {
	Adjacente* aux = (Adjacente*)malloc(sizeof(Adjacente));

	if (aux != NULL) {
		aux->id = NULL;
		aux->peso = NULL;
		aux->proxAdjacente = NULL;
	}

	return aux;
}

#pragma region Adicionar
/// <summary>
/// Cria um vertice adjacente
/// </summary>
/// <returns>Retorna vertice adjacente criado</returns>
Adjacente* AdicionarDadosAdjacente(Adjacente* adjacente, int id, int peso, int* res) {
	if (adjacente == NULL) { res = 0; return NULL; }
	if (peso < 0) { res = 0; return adjacente; }

	adjacente->id = id;
	adjacente->peso = peso;
	adjacente->proxAdjacente = NULL;

	*res = 1;
	return adjacente;
}

/// <summary>
/// Adiciona uma adjacencia dentro de uma lista de adjacentes
/// </summary>
/// <param name="adjacentes">Lista de adjacentes</param>
/// <param name="adjacente">Adjacente</param>
/// <param name="res"Retorna 0 se o adjacente nao for adicionado, retorna 1 se o adjacente for adicionado ou se a adjacencia ja existe</param>
/// <returns>Retorna nulo se se a lista de adjacentes for nula, retorna a lista de adjacentes sem o adjacente adicionado se o mesmo for nulo, e retorna 
/// a lista de adjacentes com o adjacente adicionado se o mesmo for adicionado</returns>
Adjacente* AdicionarAdjacencia(Adjacente* adjacentes, Adjacente* adjacente, int* res) {
	if (adjacentes == NULL && adjacente != NULL) { *res = 1; return adjacentes = adjacente; }
	if (adjacentes == NULL) { *res = 0; return NULL; }
	if (adjacente == NULL) { *res = 0; return adjacentes; }
	if (VerificarAdjacencia(adjacentes, adjacente->id) == 1) { *res = 1; return adjacentes; }

	Adjacente* aux = adjacentes;
	while (aux->proxAdjacente != NULL)
		aux = aux->proxAdjacente;

	aux->proxAdjacente = adjacente;

	*res = 1;
	return adjacentes;
}
#pragma endregion

#pragma region Remover
/// <summary>
/// Remove um adjacente de uma lista de adjacentes
/// </summary>
/// <param name="adjacentes">Lista de adjacentes</param>
/// <param name="id">Id do vertice</param>
/// <param name="res">Retorna 0 se a adjacencia nao for removida, retorna 1 se a ajdacencia foi removida ou se a adjacencia nao existe</param>
/// <returns>Retorna nulo se a lista de adjacentes for nula, retorna a lista de adjacentes sem o adjacente removido se o mesmo nao existir
/// , retorna a lista de adjacencias com o adjacente removido se o mesmo for removido.</returns>
Adjacente* RemoverAdjacente(Adjacente* adjacentes, int id, int* res) {
	if (adjacentes == NULL) { *res = 0; return NULL; }

	if (VerificarAdjacencia(adjacentes, id) != 1) { *res = 1; return adjacentes; }

	Adjacente* aux = adjacentes;
	Adjacente* aux2 = aux;
	if (aux->id == id) {
		adjacentes = aux->proxAdjacente;
		free(aux);
	}
	else {
		aux = aux->proxAdjacente;
		while (aux != NULL) {
			if (aux->id == id) {
				if (aux->proxAdjacente == NULL) {
					free(aux);
					aux2->proxAdjacente = NULL;
					break;
				}
				else {
					aux2->proxAdjacente = aux->proxAdjacente;
					free(aux);
					break;
				}
			}
			aux = aux->proxAdjacente;
			aux2 = aux2->proxAdjacente;
		}
	}

	*res = 1;
	return adjacentes;
}

/// <summary>
/// Remove todas as adjacencias de uma lista de adjacencias
/// </summary>
/// <param name="adjacentes">Lista de adjacentes</param>
/// <param name="res">Retorna -1 se a lista de adjacentes for nula, </param>
/// <returns>Retorna 0 se a lista de adjacencias nao for removida, retorna 1 se a lista de adjacencias for removida</returns>
int RemoverTodosAdjacentes(Adjacente* adjacentes) {
	if (adjacentes == NULL) return -1;

	Adjacente* aux = adjacentes;
	Adjacente* aux2 = aux;
	while (aux != NULL) {
		aux2 = aux2->proxAdjacente;
		free(aux);
		aux = aux2;
	}
	return 1;
}
#pragma endregion

#pragma region Verificacoes
/// <summary>
/// Verifica se os vertices adjacentes de uma lista de adjacentes foram visitados
/// </summary>
/// <param name="vertices">Lista de vertices</param>
/// <param name="adjacentes">Lista de adjacentes</param>
/// <returns>Retorna o id do vertice adjacente for visitar, retorna 1 se todos os vertices adjacentes forem visitados </returns>
int VerificarVerticesAdjacentesVisitados(Vertice* vertices, Adjacente* adjacentes) {
	if (adjacentes == NULL) return 1;
	if (vertices == NULL) return 0;

	Adjacente* auxAdj = adjacentes;
	Vertice* auxVer = vertices;

	while (auxAdj != NULL) {
		if (VerificarVerticeVisitado(vertices, auxAdj->id) == 0)
			return auxAdj->id;
		auxAdj = auxAdj->proxAdjacente;
	}

	return 1;
}

/// <summary>
/// Verifica se existe o adjacente dentro de uma lista de adjacencias
/// </summary>
/// <param name="adjacentes">Lista de adjacente</param>
/// <param name="id">Id do adjacente</param>
/// <returns>Retorna 0 se nao existir adjacente e retorna 1 se existir</returns>
int VerificarAdjacencia(Adjacente* adjacentes, int id) {
	if (adjacentes == NULL) { return 0; }

	Adjacente* aux = adjacentes;
	while (aux != NULL) {
		if (aux->id == id)
			return 1;
		aux = aux->proxAdjacente;
	}

	return 0;
}
#pragma endregion

#pragma region Operacoes
/// <summary>
/// Compara o peso de um adjacente e um valor
/// </summary>
/// <param name="adjacente"></param>
/// <param name="valor"></param>
/// <returns>Retorna -1 se o adjacente for nulo, retorna 0 se o peso for maior que o valor, retorna 1 se o peso for menor que o falor, retorna 2 se for igual</returns>
int CompararPesosAdjacente(Adjacente* adjacente, int valor) {
	if (adjacente == NULL) return -1;
	if (adjacente->peso > valor) return 0;
	else if (adjacente->peso < valor) return 1;
	else return 2;
}
#pragma endregion

#pragma region Outro
/// <summary>
/// Encontra o id do adjacente que possui o menor peso
/// </summary>
/// <param name="adjacentes">Lista de adjacentes</param>
/// <returns>Retorna -1 se a lista de adjacentes for nula, retorna o menor adjacente</returns>
int EncontrarIdMenorAdjacente(Adjacente* adjacentes) {
	if (adjacentes == NULL) return -1;
	Adjacente* adj = adjacentes->proxAdjacente;
	Adjacente* menor = adjacentes;
	while (adj != NULL) {
		if (menor->peso > adj->peso)
			menor = adj;
		adj = adj->proxAdjacente;
	}

	return menor->id;
}

/// <summary>
/// Encontra o id do adjacente que possui o menor peso e nao foi visitado
/// </summary>
/// <param name="adjacentes">Lista de adjacentes</param>
/// <returns>Retorna -1 se a lista de adjacentes for nula, retorna o menor adjacente ou retorna -2 se nao exitir nenhum adjacente sem estar por visitar</returns>
int EncontrarIdMenorAdjacenteNaoVisitado(Vertice* vertices, Adjacente* adjacentes, int* res) {
	if (adjacentes == NULL) return -1;
	Vertice* aux = NULL;
	Adjacente* adj = adjacentes;
	Adjacente* menor = NULL;
	while (adj != NULL) {
		aux = EncontrarVertice(vertices, adj->id, res);
		if (aux->visitado == false) {
			if (menor == NULL)
				menor = adj;

			if (menor->peso > adj->peso)
				menor = adj;
		}
		adj = adj->proxAdjacente;
	}

	if (menor != NULL)
		return menor->id;
	else
		return -2;
}
#pragma endregion
