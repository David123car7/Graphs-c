/*****************************************************************//**
 * @file   Ficheiros.c
 * @brief  Ficheiro C com as funcoes relacionadas com os ficheiros
 * 
 * @author David Carvalho
 * @date   May 2024
 *********************************************************************/

#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "Header.h"

/// <summary>
/// Arranca o programa 
/// </summary>
/// <param name="ficheiroTxt"></param>
/// <param name="ficheiroBin"></param>
/// <param name="res"></param>
/// <returns></returns>
Grafo* ArrancarPrograma(char ficheiroTxt[], char ficheiroBin[], int* res) {
	Grafo* grafo = CriarGrafo();
	ListaInteiros* lista = CriarListaInteiros();
	int vertices = 0;

	lista = LerGrafoBin(lista, ficheiroBin, &vertices, res);
	if (*res == 0) {
		lista = LerGrafoTxt(ficheiroTxt, &vertices, res);
		int a = GuardarGrafoBin(lista, ficheiroBin);
	}
	//lista = LerGrafoTxt(ficheiroTxt, &vertices, res); //TEMP
	return grafo = CarregarGrafo(lista, &vertices, res);
}

/// <summary>
/// Carrega um grafo para o programa a partir de uma lista de inteiros
/// </summary>
/// <param name="ficheiro">Nome do ficheiro</param>
/// <param name="res">Retorna 0 se o grafo for carregado, retorna 1 o</param>
/// <returns>Retorna nulo se a lista de inteiros for nula ou se nao existir vertices, retorna o grafo se o mesmo for carregado para o programa</returns>
Grafo* CarregarGrafo(ListaInteiros* listaChar, int* vertices, int* res) {
	if (listaChar == NULL) { *res = 0; return NULL; }
	if (*vertices == 0) { *res = 0; return NULL; }

	ListaInteiros* listaAux = listaChar;
	Grafo* grafo = CriarGrafo();
	Vertice* aux = NULL;
	Adjacente* adj = NULL;
	aux = CriarVertice();
	int id = 1;
	int adjId = 1;
	while (listaAux != NULL) {
		aux = AdicionarDadosVertice(aux, id, false,res);
		grafo = AdicionarVerticeGrafo(grafo, aux, res);
		for (int i = 0; i < *vertices; i++) {
			if (listaAux->num != 0) {
				adj = CriarAdjacente();
				adj = AdicionarDadosAdjacente(adj, adjId, listaAux->num, res);
				grafo = AdicionarAdjacenciaGrafo(grafo, id, adj, 0, res);
			}
			adjId++;
			listaAux = listaAux->proxInteiro;
		}
		aux = CriarVertice();
		id++;
		adjId = 1;
	}

	*res = 1;
	return grafo;
}

/// <summary>
/// Lê um grafo (matriz de adjacencias) presente num ficheiro.txt para uma lista de inteiros.
/// </summary>
/// <param name="ficheiro">Nome do ficheiro</param>
/// <param name="numVertices">Retorna o numero de vertices no grafo</param>
/// <param name="res">Retorna 0 se o grafo nao for lido, retorna 1 se o grafo for lido</param>
/// <returns>Retorna nulo se o nome do ficheiro for invalido ou se o ficheiro nao for aberto e retorna a lista de inteiros com os dados do grafo se o mesmo for lido</returns>
ListaInteiros* LerGrafoTxt(char ficheiro[], int* numVertices, int* res) {
	if (strlen(ficheiro) == 0) { *res = 0; return NULL; }
	FILE* fp = fopen(ficheiro, "r");
	if (fp == NULL) { *res = 0; return NULL; }

	ListaInteiros* lista = CriarListaInteiros();
	ListaInteiros* aux = lista;
	ListaInteiros* remover = NULL;
	int ch = getc(fp);
	int a = 0;
	*numVertices = 0;
	while (ch != EOF) {
		if (ch == 59) {
			aux->num = a;
			aux->proxInteiro = CriarListaInteiros();
			remover = aux;
			aux = aux->proxInteiro;
			a = 0;
		}
		else if (ch == 10) {
			aux->num = a;
			aux->proxInteiro = CriarListaInteiros();
			remover = aux;
			aux = aux->proxInteiro;
			a = 0;
			*numVertices = *numVertices + 1;
		}
		else
			a = a * 10 + (ch - '0'); //Converte o char par inteiro
		ch = getc(fp);
	}
	fclose(fp);
	free(aux);
	if (remover != NULL)
		remover->proxInteiro = NULL;

	*res = 1;
	return lista;
}

/// <summary>
/// Carrega os dados do grafo para uma lista de inteiros
/// </summary>
/// <param name="grafo">Grafo</param>
/// <param name="lista">Lista de inteiros</param>
/// <param name="res">Retorna 0 se os dados nao forem carregados para lista de inteiros, retorna 1 se os dados forem carregados para lista de inteiros</param>
/// <returns>Retorna nulo se o grafo ou lista de inteiros for nula, retorna a lista de inteiros com os dados do grafo se o carregamento for bem sucedido</returns>
ListaInteiros* GrafoParaListaInteiros(Grafo* grafo, ListaInteiros* lista, int* res) {
	if (grafo == NULL) { *res = 0; return NULL; }
	if (lista == NULL) { *res = 0; return NULL; }

	Vertice* aux = grafo->vertInicio;
	Adjacente* adj = NULL;
	ListaInteiros* auxLista = lista;
	ListaInteiros* remover = NULL;
	int numVertices = grafo->vertices;
	while (aux != NULL) {
		if (aux->proxAdjacente == NULL) {
			for (int i = 0; i < numVertices; i++) {
				auxLista->num = 0;
				auxLista->proxInteiro = CriarListaInteiros();
				remover = auxLista;
				auxLista = auxLista->proxInteiro;
			}
		}
		else {
			adj = aux->proxAdjacente;
			for (int j = 1; j <= numVertices; j++) {
				if (adj != NULL && adj->id == j) {
					auxLista->num = adj->peso;
					adj = adj->proxAdjacente;
				}
				else {
					auxLista->num = 0;
				}

				auxLista->proxInteiro = CriarListaInteiros();
				remover = auxLista;
				auxLista = auxLista->proxInteiro;
			}
		}
		aux = aux->proxVertice;
	}
	free(aux);
	if(remover != NULL)
		remover->proxInteiro = NULL;

	*res = 1;
	return lista;
}

/// <summary>
/// Guarda os dados do grafo carregados na lista de inteiros
/// </summary>
/// <param name="lista">Lista de inteiros</param>
/// <param name="ficheiro">Nome do ficheiro binario</param>
/// <returns>Retorna 0 se o ficheiro nao for guardado, retorna 1 se o ficheiro nao for guardado</returns>
int GuardarGrafoBin(ListaInteiros* lista, char ficheiro[]) {
	if (lista == NULL) return 0;
	if (strlen(ficheiro) == 0) return 0;

	FILE* fp = fopen(ficheiro, "wb");
	if (fp == NULL) return 0;

	while (lista != NULL) {
		fwrite(&lista->num, 1, sizeof(int), fp);
		lista = lista->proxInteiro;
	}

	fclose(fp);

	return 1;
}

/// <summary>
/// Carrega os dados de um grafo presentes num ficheiro binario para uma lista de inteiros
/// </summary>
/// <param name="lista">Lista de inteiros</param>
/// <param name="ficheiro">Nome do ficheiro binario</param>
/// <param name="res">Retorna 0 se os dados do grafo nao forem carregados e retorna 1 se forem carregados</param>
/// <returns>Retorna nulo se a lista for nula ou o nome do ficheiro for invalido, retorna a lista de inteiros com os dados do grafo se o carregamento for bem sucedido</returns>
ListaInteiros* LerGrafoBin(ListaInteiros* lista, char ficheiro[], int* vertices ,int* res) {
	if (lista == NULL) { return NULL; *res = 0; }
	if (strlen(ficheiro) == 0) { return lista; *res = 0;}

	FILE* fp = fopen(ficheiro, "r");
	if (fp == NULL) { *res = 0; return lista; };

	ListaInteiros* aux = lista;
	ListaInteiros* remover = NULL;
	int v = 0;
	while (fread(&aux->num, sizeof(int), 1, fp)) {
		aux->proxInteiro = CriarListaInteiros();
		remover = aux;
		aux = aux->proxInteiro;
		v++;
	}
	fclose(fp);
	*vertices = sqrt(v);

	free(aux);
	if(remover != NULL)
		remover->proxInteiro = NULL;

	return lista;
}