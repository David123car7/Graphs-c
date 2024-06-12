/*****************************************************************//**
 * @file   Grafo.c
 * @brief  Ficheiro C com as funcoes relacionadas com o grafo
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
/// Cria um grafo
/// </summary>
/// <returns>Retorna o grafo criado</returns>
Grafo* CriarGrafo() {
	Grafo* aux = (Grafo*)malloc(sizeof(Grafo));
	if (aux != NULL) {
		aux->vertInicio = NULL;
		aux->vertices = NULL;
	}
	return aux;
}

#pragma region Adicionar
/// <summary>
/// Adiciona um vertice no grafo no fim do grafo
/// </summary>
/// <param name="grafo">Grafo</param>
/// <param name="vertice">Vertice a ser adicionado</param>
/// <param name="res">Retorna 0 se o vertice nao for adicionado, retorna 1 se o vertice foi adicionado</param>
/// <returns>Retorna null se nao for adicionado o vertice ao grafo e retorna o grafo se o vertice foi adicionado com exito</returns>
Grafo* AdicionarVerticeGrafo(Grafo* grafo, Vertice* vertice, int* res) {
	if (grafo == NULL) { *res = 0; return NULL; }
	grafo->vertInicio = AdicionarVertice(grafo->vertInicio, vertice, res);
	grafo->vertices++;
	return grafo;
}

/// <summary>
/// Cria uma adjacencia entre um vertice origem e destino
/// </summary>
/// <param name="grafo">Grafo</param>
/// <param name="origem">Id do vertice origem</param>
/// <param name="adjacente">Adjacente</param>
/// <param name="verificar">Colocar 0 para nao verificar vertice, colocar 1 para verificar vertice</param>
/// <param name="res">Retorna 0 se a adjacencia nao for adicionada, retorna 1 se a adjacencia for adicionada</param>
/// <returns>Retorna nulo se o grafo é nulo, se nao retorna o grafo com a aresta criada</returns>
Grafo* AdicionarAdjacenciaGrafo(Grafo* grafo, int origem, Adjacente* adjacente, int verificar, int* res) {
	if (grafo == NULL) { *res = 0; return NULL; }
	grafo->vertInicio = AdicionarAdjacenciaVertices(grafo->vertInicio, origem, adjacente, verificar, res);
	return grafo;
}

#pragma endregion

#pragma region Remover
/// <summary>
/// Remove todos os vertices adjacentes de um vertice dentro de um grafo
/// </summary>
/// <param name="grafo">Grafo</param>
/// <param name="id">Id do vertice a remover os adjacentes</param>
/// <param name="res">Retorna 0 se os adjacentes nao forem removidos, retorna 1 se os adjacentes forem removidos</param>
/// <returns>Retorna nulo se o grafo for nulo, retorna o grafo sem os adjacentes serem removidos se o grafo nao tiver vertices, retorna o grafo
/// com os adjacentes removidos se os mesmos forem removidos</returns>
Grafo* RemoverTodosAdjacentesGrafo(Grafo* grafo, int id, int* res) {
	if (grafo == NULL) { *res = 0; return NULL; }
	grafo->vertInicio = RemoverTodosAdjacentesVertice(grafo->vertInicio, id, res);
	return grafo;
}

/// <summary>
/// Remove o vertice adjacente de todas adjacencias presentes no grafo
/// </summary>
/// <param name="grafo">Grafo</param>
/// <param name="id">Id do adjacente</param>
/// <param name="res">Retorna 0 se nao for removido o adjacente, retorna 1 se for removido o adjacente</param>
/// <returns>Retorna nulo se o adjacente nao for removido do grafo, retorna o grafo se for removido o adjacente do mesmo</returns>
Grafo* RemoverAdjacenteTodosVerticesGrafo(Grafo* grafo, int id, int* res) {
	if (grafo == NULL) { *res = 0; return NULL; }
	grafo->vertInicio = RemoverAdjacenteTodosVertices(grafo->vertInicio, id, res);
	return grafo;
}

/// <summary>
/// Remove o vertice adjacente de um vertice presente no grafo
/// </summary>
/// <param name="grafo">Grafo</param>
/// <param name="vertice">Id do vertice</param>
/// <param name="adjacente">Id do adjacente</param>
/// <param name="res">Retorna 0 se o adjacente nao for removido do grafo, retorna 1 se o adjacente for removido do grafo.</param>
/// <returns>Retorna nulo se o grafo for nulo, retorna o grafo se o adjacente for removido</returns>
Grafo* RemoverAdjacenteGrafo(Grafo* grafo, int vertice, int adjacente, int* res) {
	if (grafo == NULL) { *res = 0; return NULL; }
	grafo->vertInicio = RemoveAdjacenteVertices(grafo->vertInicio, vertice, adjacente, res);
	return grafo;
}

/// <summary>
/// Remove um vertice de um grafo
/// </summary>
/// <param name="grafo">Grafo</param>
/// <param name="id">Id do vertice</param>
/// <param name="res">Retorna 0 se o vertice nao for removido, retorna 1 se o vertice for removido</param>
/// <returns>Retorna nulo se o grafo for nulo, retorna o grafo sem o vertice se o mesmo for eliminado</returns>
Grafo* RemoverVerticeGrafo(Grafo* grafo, int id, int* res) {
	if (grafo == NULL) { *res = 0; return grafo; }
	grafo->vertInicio = RemoverVertice(grafo->vertInicio, id, res);
	return grafo;
}
#pragma endregion

#pragma region Algoritmos
/// <summary>
/// DepthFirstTraversal: Percorre todo o grafo em profundidade
/// </summary>
/// <param name="grafo">Grafo</param>
/// <param name="inicioId">Id do vertice inicio</param>
/// <returns>Retorna 0 se o grafo nao for percorrido, retorna 1 se o grafo for percorrido</returns>
int DepthFirstTraversal(Grafo* grafo, int inicioId) {
	if (grafo == NULL) return 0;

	int v;
	int res = 1;
	Vertice* aux = EncontrarVertice(grafo->vertInicio, inicioId, &res);

	ListaInteiros* stack = NULL;
	int top = -1;

	if (aux->visitado == true) return 1;

	stack = CriarAdicionarNumeroListaInteirosFim(stack, aux->id, &top, &res);
	aux = AlterarEstadoVerticeVisitado(aux, true, &res);

	while (VerificarListaInteirosVazia(stack) != 0) {
		ProcessarVertice(aux);
		v = VerificarVerticesAdjacentesVisitados(grafo->vertInicio, aux->proxAdjacente);
		if (v == 1) {
			stack = RemoverNumeroListaInteirosComTop(stack, top, &top, &res);
			aux = EncontrarVertice(grafo->vertInicio, top, &res);
		}
		else {
			aux = EncontrarVertice(grafo->vertInicio, v, &res);
			aux = AlterarEstadoVerticeVisitado(aux, true, &res);
			stack = CriarAdicionarNumeroListaInteirosFim(stack, v, &top, &res);
		}
	}

	grafo->vertInicio = AlterarEstadoVisitadoTodosVertices(grafo->vertInicio, false, &res);

	return 1;
}

/// <summary>
/// Breadth First Search
/// </summary>
/// <param name="grafo">Grafo</param>
/// <param name="inicioId">Id do vertice inicio</param>
/// <returns>Retorna 0 se o grafo nao for percorrido, retorna 1 se o grafo for percorrido</returns>
int BreadthFirstTraversal(Grafo* grafo, int inicioId) {
	if (grafo == NULL) return 0;

	int res = 1;
	Vertice* aux = EncontrarVertice(grafo->vertInicio, inicioId, &res);

	ListaInteiros* queue = NULL;
	int top = -1;
	int v;
	if (aux->visitado == true) return 1;

	queue = CriarAdicionarNumeroListaInteirosInicio(queue, aux->id, &res);
	aux = AlterarEstadoVerticeVisitado(aux, true, &res);
	ProcessarVertice(aux);
	top = queue->num;

	while (VerificarListaInteirosVazia(queue) != 0) {
		v = VerificarVerticesAdjacentesVisitados(grafo->vertInicio, aux->proxAdjacente);
		if (v == 1) {
			queue = RemoverNumeroListaInteirosComTop(queue, top, &top, &res);
			aux = EncontrarVertice(grafo->vertInicio, top, &res);
		}
		else {
			aux = EncontrarVertice(grafo->vertInicio, v, &res);
			ProcessarVertice(aux);
			aux = AlterarEstadoVerticeVisitado(aux, true, &res);
			queue = CriarAdicionarNumeroListaInteirosInicio(queue, v, &res);
			aux = EncontrarVertice(grafo->vertInicio, top, &res);
		}
	}

	grafo->vertInicio = AlterarEstadoVisitadoTodosVertices(grafo->vertInicio, false, &res);

	return 1;
}

/// <summary>
/// Determina o maior caminho
/// </summary>
/// <param name="grafo">Grafo</param>
/// <param name="inicioId">Inicio</param>
/// <param name="destinoId">Destino</param>
/// <param name="res">Retorna -1 se o grafo for nulo, se o inicio ou o destino nao pertencerem ao grafo, retorna a soma do maior caminho</param>
/// <returns>Retorna a soma do caminho maximo</returns>
int DeterminarMaiorCaminhoGrafo(Grafo* grafo, int inicioId, int destinoId,int* res) {
	if (grafo == NULL) return -1;

	if (VerificarVerticeGrafo(grafo, inicioId) != 1) { *res = 0; return -1;}
	if (VerificarVerticeGrafo(grafo, destinoId) != 1) { *res = 0; return -1; }

	Vertice* aux = EncontrarVertice(grafo->vertInicio, inicioId, res);

	//Cria lista de vertices nao visitados
	ListaInteiros* vertNaoVisitados = CriarListasInteiros(grafo->vertices, res);
	vertNaoVisitados = AdicionarVerticeIdListaInteiros(vertNaoVisitados, grafo->vertInicio, res);

	//Cria lista das distancias dos vertices
	VerticeDistancia* vertDist = CriarVerticesDistancia(grafo->vertices, res);
	vertDist = AdicionarTodosVerticesIdVerticesDistancia(vertDist, grafo->vertInicio, res);
	vertDist = AdicionarTodosDistanciaVerticesDistancia(vertDist, -1, res);
	vertDist = AdicionarDistanciaListaVerticeDistancia(vertDist, inicioId, 0, res);

	while (VerificarListaInteirosVazia(vertNaoVisitados) != 0) {
		//Somar Adjacencias
		Adjacente* adj = aux->proxAdjacente;
		VerticeDistancia* temp = EncontrarVerticeDistancia(vertDist, aux->id, res);
		while (adj != NULL) {
			if (VerificarVerticeVisitado(grafo->vertInicio, adj->id) == 0) {
				int distAnt = EncontrarIdAnteriorVerticeDistancia(vertDist, adj->id); 
				vertDist = AtribuirListaVerticeDistanciaAnterior(vertDist, temp, adj->id, res); //Atribui anterior
				int dist = SomarDistanciaListaVerticeDistancia2(vertDist, adj->id, adj->peso, res);

				int c = ComparaDistanciaListaVerticeDistancia(vertDist, adj->id, dist);
				if (c == 0) {
					vertDist = AdicionarDistanciaListaVerticeDistancia(vertDist, adj->id, dist, res);
					printf("%d ", adj->id);
				}
				else {
					VerticeDistancia* temp = EncontrarVerticeDistancia(vertDist, distAnt, res);
					vertDist = AtribuirListaVerticeDistanciaAnterior(vertDist, temp, adj->id, res);
				}
			}
			adj = adj->proxAdjacente;
		}
		
		aux = AlterarEstadoVerticeVisitado(aux, true, res);
		vertNaoVisitados = RemoverNumeroListaInteiros(vertNaoVisitados, aux->id, res);
		int menorAdj = EncontrarIdMenorAdjacenteNaoVisitado(grafo->vertInicio, aux->proxAdjacente, res);
		if (menorAdj == -1) {
			int tmpId = EncontrarIdAnteriorVerticeDistancia(vertDist, aux->id);
			aux = EncontrarVertice(grafo->vertInicio, tmpId, res);
		}
		else
			aux = EncontrarVertice(grafo->vertInicio, menorAdj, res);
	}

	int p = ProcessarCaminho(vertDist, destinoId);

	return EncontrarVerticeDistancia(vertDist, destinoId, res)->distancia;
}
#pragma endregion

#pragma region Outro
/// <summary>
/// Mostra o grafo no terminal
/// </summary>
/// <param name="grafo">Grafo</param>
/// <returns>Retorna 0 se o grafo for nulo, retorna 1 se o grafo for mostrado no terminal</returns>
int MostrarGrafo(Grafo* grafo) {
	if (grafo == NULL) return 0;
	Vertice* aux = grafo->vertInicio;
	while (aux != NULL) {
		printf("Vertice: %d\n", aux->id);
		Adjacente* aux2 = aux->proxAdjacente;
		if (aux2 != NULL) {
			printf("Adj: ");
			while (aux2 != NULL) {
				printf("ID: %d PESO: %d\n", aux2->id, aux2->peso);
				aux2 = aux2->proxAdjacente;
			}
		}
		printf("\n");
		aux = aux->proxVertice;
	}

	return 1;
}
#pragma endregion







