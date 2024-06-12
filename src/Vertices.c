/*****************************************************************//**
 * @file   Vertices.c
 * @brief  Ficheiro C com as funcoes relacionadas com os vertices
 * 
 * @author David Carvalho
 * @date   May 2024
 *********************************************************************/

#pragma warning (disable:4996)
#include <stdio.h>
#include <malloc.h>
#include "Header.h"

/// <summary>
/// Cria um vertice
/// </summary>
/// <returns>Retorna o vertice criado</returns>
Vertice* CriarVertice() {
	Vertice* aux = (Vertice*)malloc(sizeof(Vertice));

	if (aux != NULL) {
		aux->id = NULL;
		aux->visitado = NULL;
		aux->proxVertice = NULL;
		aux->proxAdjacente = NULL;
	}

	return aux;
}

#pragma region Adicionar/Alterar
/// <summary>
/// Adiciona um vertice a uma lista de vertices
/// </summary>
/// <param name="vertices">Lista de vertices</param>
/// <param name="vertice">Vertice a ser adicionado</param>
/// <param name="res">Retorna 0 se o vertice nao for adicionado, retorna 1 se o vertice foi adicionado</param>
/// <returns>Retorna nulo se a lista de vertices for nula, retorna a lista de vertices sem o vertice adicionado se o mesmo for nulo
/// e retorna a lista de vertices se o vertice for adicionado</returns>
Vertice* AdicionarVertice(Vertice* vertices, Vertice* vertice, int* res) {
	if (vertices == NULL && vertice != NULL) { *res = 1; return vertices = vertice; }
	if (vertices == NULL) { *res = 0; return NULL; }
	if (vertice == NULL) { *res = 0; return vertices; }

	if (VerificarVertice(vertices, vertice->id) == 1) { *res = 0; return vertices; }

	Vertice* aux = vertices;
	Vertice* ant = NULL;
	while (aux != NULL && aux->id < vertice->id) {
		ant = aux;
		aux = aux->proxVertice;
	}
	if (ant == NULL) {
		vertices = vertice;
		vertice->proxVertice = aux;
	}
	else {
		ant->proxVertice = vertice;
		vertice->proxVertice = aux;
	}

	*res = 1;
	return vertices;
}

/// <summary>
/// Adiciona uma adjacencia dentro de uma lista de adjacentes
/// </summary>
/// <param name="adjacentes">Lista de adjacentes</param>
/// <param name="adjacente">Adjacente</param>
/// <param name="verificar">Colocar 0 para nao verificar vertice, colocar 1 para verificar vertice</param>
/// <param name="res">Retorna 0 se o adjacente nao for adicionado, retorna 1 se o adjacente for adicionado</param>
/// <returns>Retorna nulo se a lista de vertices for nula, retorna a lista de vertices sem o adjacente adicionado se o mesmo for nulo, e retorna 
/// a lista de vertices com o adjacente adicionado se o mesmo for adicionado</returns>
Vertice* AdicionarAdjacenciaVertices(Vertice* vertices, int origem, Adjacente* adjacente, int verificar, int* res) {
	if (vertices == NULL) { *res = 0; return NULL; }

	if (verificar == 1)
		if (VerificarVertice(vertices, origem) != 1 || VerificarVertice(vertices, adjacente->id) != 1) { *res = 0; return vertices; }

	Vertice* aux = vertices;
	while (aux != NULL) {
		if (aux->id == origem) {
			aux->proxAdjacente = AdicionarAdjacencia(aux->proxAdjacente, adjacente, res);
			*res = 1;
			return vertices;
		}
		aux = aux->proxVertice;
	}
}

/// <summary>
/// Altera o estado da variabel boleana visitado de um vertice
/// </summary>
/// <param name="vertice">Vertice</param>
/// <param name="estado">Estado da variavel boleana</param>
/// <param name="res">Retorna 0 se o vertice for nulo, retorna o vertice com a variavel alterada</param>
/// <returns>Retorna nulo se o vertice for nulo, retorna o vertice com a variavel alterada</returns>
Vertice* AlterarEstadoVerticeVisitado(Vertice* vertice, bool estado, int* res) {
	if (vertice == NULL) { *res = 0; return NULL; }
	vertice->visitado = estado;
	*res = 1;
	return vertice;
}


/// <summary>
/// Adiciona dados a um vertice
/// </summary>
/// <param name="vertice">Vertice a serem adicionados os dados</param>
/// <param name="id">Id do vertice</param>
/// <param name="num">Numero do vertice</param>
/// <param name="visitado">Bool visitado ou nao</param>
/// <param name="res">retorna 0 se nao forem adicionados os dados ao vertice, 
/// retorna 1 se forem adicionados os dados ao vertice</param>
/// <returns>Retorna nulo se o vertice for nulo, retorna o vertice se os dados forem adicionados ao vertice</returns>
Vertice* AdicionarDadosVertice(Vertice* vertice, int id, bool visitado, int* res) {
	if (vertice == NULL) { *res = 0; return NULL; }
	vertice->id = id;
	vertice->visitado = visitado;
	*res = 1;
	return vertice;
}


/// <summary>
/// Altera o estado da variavel boleana visitado de um vertice dentro de uma lista de vertices
/// </summary>
/// <param name="vertices">Lista de vertices</param>
/// <param name="id">Id do vertice</param>
/// <param name="estado">Estado da variavel</param>
/// <param name="res">Retorna 0 se o estado nao for modificado, retorna 1 se o estado for modificado</param>
/// <returns>Retorna nulo se a lista de vertices for nula, retorna a lista de vertices sem ser feita a alteracao se o vertice nao existir
/// retorna a lista de vertices com a alteracao feita se a mesma for feita</returns>
Vertice* AlterarEstadoVerticeVisitadoVertices(Vertice* vertices, int id, bool estado, int* res) {
	if (vertices == NULL) { *res = 0; return NULL; }
	if (VerificarVertice(vertices, id) != 1) { *res = 0; return vertices; }

	Vertice* aux = vertices;
	while (aux != NULL) {
		if (aux->id == id) {
			aux = AlterarEstadoVerticeVisitado(aux, estado, res);
			break;
		}
		aux = aux->proxVertice;
	}

	return vertices;
}

/// <summary>
/// Altera o estado da variabel boleana visitado de todos os vertices dentro de uma lista de vertices
/// </summary>
/// <param name="vertices">Lista de vertices</param>
/// <param name="estado">Estado</param>
/// <param name="res">Retorna 0 se a alteracao nao for feita, retorna 1 se a alteracao for feita</param>
/// <returns>Retorna nulo se a lista de vertices for nula, retorna a lista de vertices com a alteracao feita se a mesma for feita</returns>
Vertice* AlterarEstadoVisitadoTodosVertices(Vertice* vertices, bool estado, int* res) {
	if (vertices == NULL) { *res = 0; return NULL; }

	Vertice* aux = vertices;
	while (aux != NULL) {
		aux = AlterarEstadoVerticeVisitado(aux, estado, res);
		aux = aux->proxVertice;
	}

	return vertices;
}
#pragma endregion

#pragma region Remover
/// <summary>
/// Remove um vertice de uma lista de vertices
/// </summary>
/// <param name="vertices">Lista de vertices</param>+
/// <param name="id">Id do vertice</param>
/// <param name="res">Retorna 0 se o vertice nao for removido, retorna 1 se o vertice for removido ou se o vertice nao existir</param>
/// <returns>Retorna nulo se a lista de vertices for nula, retorna a lista de vertices sem fazer nada se o vertice nao exisitr, 
/// retorna a lista de vertices com o vertice removido se o mesmo for removido.</returns>
Vertice* RemoverVertice(Vertice* vertices, int id, int* res) {
	if (vertices == NULL) { *res = 0; return NULL; }

	if (VerificarVertice(vertices, id) != 1) { *res = 1; return vertices; }

	Vertice* aux = vertices;
	Vertice* ant = NULL;

	while (aux->id != id) {
		ant = aux;
		aux = aux->proxVertice;
	}
	if (ant == NULL) {
		vertices = aux->proxVertice;
		aux->proxAdjacente = RemoverTodosAdjacentes(aux->proxAdjacente);
		free(aux);
	}
	else {
		if (aux->proxVertice == NULL) {
			ant->proxVertice = NULL;
			aux->proxAdjacente = RemoverTodosAdjacentes(aux->proxAdjacente);
			free(aux);
		}
		else {
			ant->proxVertice = aux->proxVertice;
			aux->proxAdjacente = RemoverTodosAdjacentes(aux->proxAdjacente);
			free(aux);
		}
	}
	*res = 1;
	return vertices;
}

/// <summary>
/// Remove o vertice adjacente de todos vertices presentes na lista de vertices
/// </summary>
/// <param name="vertices">Lista de vertices</param>
/// <param name="id">Id do vertice</param>
/// <param name="res">Retorna 0 se o vertice nao for removido, retorna 1 se o vertice for removido ou se o vertice nao existe.</param>
/// <returns>Retorna nulo se a lista de vertices for nula, retorna </returns>
Vertice* RemoverAdjacenteTodosVertices(Vertice* vertices, int id, int* res) {
	if (vertices == NULL) { *res = 0; return NULL; }

	if (VerificarAdjacenciaVertice(vertices, id) != 1) { *res = 1; return vertices; }

	Vertice* aux = vertices;
	while (aux != NULL) {
		if (aux->proxAdjacente != NULL) {
			aux->proxAdjacente = RemoverAdjacente(aux->proxAdjacente, id, res);
		}
		aux = aux->proxVertice;
	}

	*res = 1;
	return vertices;
}

/// <summary>
/// Remove o vertice adjacente de um vertice presente na lista de vertices
/// </summary>
/// <param name="vertices">Lista de vertice</param>
/// <param name="vertice">Id do Vertice</param>
/// <param name="adjacente">Id do adjacente</param>
/// <param name="res">Retorna 0 se a adjacencia nao for removida dos vertices, retorna 1 se a adjacencia foi removida dos vertices</param>
/// <returns>Retorna nulo se a lista de vertices for nula, retorna a lista de vertices sem o adjacente removido se o vertice nao existir, retorna a lista de vertices com o adjacente
/// removido se o mesmo for removido</returns>
Vertice* RemoveAdjacenteVertices(Vertice* vertices, int vertice, int adjacente, int* res) {
	if (vertices == NULL) { *res = 0; return NULL; }

	if (VerificarVertice(vertices, vertice) != 1) { *res = 0; return vertices; }
	if (VerificarAdjacenciaVertice(vertices, adjacente) != 1) { *res = 1; return vertices; }

	Vertice* aux = vertices;
	while (aux->id != vertice)
		aux = aux->proxVertice;
	aux->proxAdjacente = RemoverAdjacente(aux->proxAdjacente, adjacente, res);

	*res = 1;
	return vertices;
}

/// <summary>
/// Remove todos os vertices adjacentes de um vertice dentro de uma lista de vertice
/// </summary>
/// <param name="Vertice">Vertice</param>
/// <param name="id">Id do vertice a remover os adjacentes</param>
/// <param name="res">Retorna 0 se os adjacentes nao forem removidos, retorna 1 se os adjacentes forem removidos, ou se o vertice nao existe</param>
/// <returns>Retorna nulo se a lista for for nula, retorna a lista de vertices sem os adjacentes serem removidos se a lista de vertices nao tiver vertices, retorna a
/// lista de vertices com os adjacentes removidos se os mesmos forem removidos</returns>
Vertice* RemoverTodosAdjacentesVertice(Vertice* vertices, int id, int* res) {
	if (vertices == NULL) { *res = 0; return NULL; }

	if (VerificarVertice(vertices, id) != 1) { *res = 1; return vertices; }

	Vertice* aux = vertices;
	while (aux->id != id)
		aux = aux->proxVertice;
	aux->proxAdjacente = RemoverTodosAdjacentes(aux->proxAdjacente);

	*res = 1;
	return vertices;
}
#pragma endregion

#pragma region Verificacoes
/// <summary>
/// Verifica se o vertice foi visitado
/// </summary>
/// <param name="vertices">Lista de vertices</param>
/// <returns>Retorna 0 se o vertice nao foi visitado, retorna 1 se o vertice foi visitado</returns>
int VerificarVerticeVisitado(Vertice* vertices, int id) {
	if (vertices == NULL) return 0;

	Vertice* aux = vertices;
	while (aux != NULL) {
		if (aux->id == id && aux->visitado == false)
			return 0;
		aux = aux->proxVertice;
	}

	return 1;
}

/// <summary>
/// Verifica a existencia de um vertice numa lista de vertices
/// </summary>
/// <param name="vertices">Lista de vertices</param>
/// <param name="id">Id do vertice</param>
/// <returns>Retorna -1 se o vertice for nulo,retorna 0 se o vertice nao 
/// existir retorna 1 se o vertice existir </returns>
int VerificarVertice(Vertice* vertices, int id) {
	if (vertices == NULL) return -1;

	Vertice* aux = vertices;
	while (aux != NULL) {
		if (aux->id == id)
			return 1;
		aux = aux->proxVertice;
	}

	return 0;
}

/// <summary>
/// Verifica a existencia de um vertice num grafo
/// </summary>
/// <param name="grafo">Grafo</param>
/// <param name="id">Id do vertice</param>
/// <returns>Retorna -2 se o grafo for nulo, retorna -1 se nao existir vertices no grafo, 
/// retorna 0 se o vertice nao existir, retorna 1 se o vertice existir</returns>
int VerificarVerticeGrafo(Grafo* grafo, int id) {
	if (grafo == NULL) return 0;

	return(VerificarVertice(grafo->vertInicio, id));
}

/// <summary>
/// Verifica se existe alguem vertice adjacente dentro de uma lista de vertices
/// </summary>
/// <param name="vertices">Lista de vertices</param>
/// <param name="vertice">Id do vertice</param>
/// <param name="adjacente">Id do vertice adjacente</param>
/// <returns>Retorna 0 se nao existir e retorna 1 se existir</returns>
int VerificarAdjacenciaVertice(Vertice* vertices, int id) {
	if (vertices == NULL) return 0;

	Vertice* aux = vertices;
	while (aux != NULL) {
		int a = VerificarAdjacencia(aux->proxAdjacente, id);
		if (a == 1)
			return 1;
		aux = aux->proxVertice;
	}

	return 0;
}

/// <summary>
/// Verifica se existe alguem vertice adjacente a um vertice dentro de um grafo
/// </summary>
/// <param name="grafo">Grafo</param>
/// <param name="vertice">Id do vertice</param>
/// <param name="adjacente">Id do vertice adjacente</param>
/// <returns>Retorna 0 se nao existir e retorna 1 se existir</returns>
int VerificarAdjacenciaVerticeGrafo(Grafo* grafo, int vertice, int adjacente) {
	if (grafo == NULL) return 0;
	return(VerificarAdjacenciaVertice(grafo->vertInicio, vertice, adjacente));
}
#pragma endregion

#pragma region Outro
/// <summary>
/// Encontra um vertice dentro de uma lista de vertices e retorna o mesmo
/// </summary>
/// <param name="vertices">Lista de vertices</param>
/// <param name="id">Id do vertice</param>
/// <param name="res">Retorna -1 se a lista de vertices for nula, retorna 0 se nao encontrar o vertice, retorna 1 se encontrar e retornar o vertice</param>
/// <returns>Retorna nulo se nao encontrar o vertice ou se a lista de vertices for nula, retorna o vertice se o mesmo for encontrado</returns>
Vertice* EncontrarVertice(Vertice* vertices, int id, int* res) {
	if (vertices == NULL) { *res = -1; return NULL; }

	Vertice* aux = vertices;
	while (aux != NULL) {
		if (aux->id == id) {
			*res = 1;
			return aux;
		}
		aux = aux->proxVertice;
	}

	*res = 0;
	return NULL;
}

/// <summary>
/// Encontra um vertice dentro de um grafo e retorna o mesmo.
/// </summary>
/// <param name="grafo">Grafo</param>
/// <param name="id">Id do vertice</param>
/// <param name="res">Retorna -2 se o grafo for nulo, retorna -1 se nao exitir vertices no grafo,retorna 0 se nao encontrar o vertice, 
/// retorna 1 se encontrar e retornar o vertice</param>
/// <returns>Retorna nulo se nao encontrar o vertice, se o encontrar retorna o vertice.</returns>
Vertice* EncontrarVerticeGrafo(Grafo* grafo, int id, int* res) {
	if (grafo == NULL) { *res = -2; return NULL; }

	return(EncontrarVertice(grafo->vertInicio, id, res));
}

/// <summary>
/// Processa o vertice mostrando o no terminal
/// </summary>
/// <param name="vertice">Vertice</param>
/// <returns>Retorna 0 se nao for mostrado no terminal, retorna 1 se for mostrado no terminal</returns>
int ProcessarVertice(Vertice* vertice) {
	if (vertice == NULL) return 0;
	printf("%d ", vertice->id);
	return 1;
}
#pragma endregion


