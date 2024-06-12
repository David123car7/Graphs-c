/*****************************************************************//**
 * @file   Dijkstra.c
 * @brief  Ficheiro C com as funcoes relacionadas com a estrutura VerticeDistancias
 * 
 * @author David Carvalho
 * @date   May 2024
 *********************************************************************/

#pragma warning (disable:4996)
#include <stdio.h>
#include <malloc.h>
#include "Header.h"

/// <summary>
/// Cria uma variavel do tipo verticeDistancias
/// </summary>
/// <returns>Retorna o Dijkstra</returns>
VerticeDistancia* CriarVerticeDistancia() {
	VerticeDistancia* aux = (VerticeDistancia*)malloc(sizeof(VerticeDistancia));
	if (aux != NULL) {
		aux->distancia = NULL;
		aux->id = NULL;
		aux->proxVerDist = NULL;
		aux->antVerDist = NULL;
	}
	return aux;
}

/// <summary>
/// Cria uma lista de vertices distancia com um determinado tamanho
/// </summary>
/// <param name="num">Tamanho da lista de vertices distancias</param>
/// <param name="res">Retorna 0 se nao for criado a lista, retorna a lista se a mesma for criada</param>
/// <returns>Retorna nulo se o tamanho for igual a 0, retorna  lista se a mesma for criada</returns>
VerticeDistancia* CriarVerticesDistancia(int tamanho, int *res) {
	if (tamanho == 0) return NULL;
	VerticeDistancia* lista = NULL;
	for (int i = 0; i < tamanho; i++) {
		VerticeDistancia* aux = CriarVerticeDistancia();
		lista = AdicionarVerticeDistancia(lista, aux, res);
	}

	return lista;
}

#pragma region Adicionar
/// <summary>
/// Adiciona dados a uma variavel do tipo verticeDistancias
/// </summary>
/// <param name="verticeDistancias">Vertice distancia</param>
/// <param name="id">Id do vertice</param>
/// <param name="distancia">Distancia</param>
/// <param name="res">Retorna 0 e nao for adicionado os dados, retorna 1 se for adicionado os dados</param>
/// <returns>Retorna nulo se o vertice distancia for nulo, retorna o vertice distancia se os dados forem adicionados</returns>
VerticeDistancia* AdicionarDadosVerticeDistancia(VerticeDistancia* verticeDistancia, int id, int distancia, int* res) {
	if (verticeDistancia == NULL) { *res = 0; return NULL; }
	verticeDistancia->id = id;
	verticeDistancia->distancia = distancia;
	*res = 1;
	return verticeDistancia;
}

/// <summary>
/// Adiciona um id a uma variavel do tipo verticeDistancias
/// </summary>
/// <param name="verticeDistancias">Vertice distancia</param>
/// <param name="id">Id do vertice</param>
/// <param name="res">Retorna 0 e nao for adicionado o id, retorna 1 se for adicionado o id</param>
/// <returns>Retorna nulo se o vertice distancia for nulo, retorna o vertice distancia se o id for adicionado</returns>
VerticeDistancia* AdicionarIdVerticeDistancia(VerticeDistancia* verticeDistancia, int id, int* res) {
	if (verticeDistancia == NULL) { *res = 0; return NULL; }
	verticeDistancia->id = id;
	*res = 1;
	return verticeDistancia;
}

/// <summary>
/// Adiciona uma distancia a uma variavel do tipo verticeDistancias
/// </summary>
/// <param name="verticeDistancias">Vertice distancia</param>
/// <param name="distancia">Distancia</param>
/// <param name="res">Retorna 0 e nao for adicionado a distancia, retorna 1 se for adicionado a distancia</param>
/// <returns>Retorna nulo se o vertice distancia for nulo, retorna o vertice distancia se o id for adicionado</returns>
VerticeDistancia* AdicionarDistanciaVerticeDistancia(VerticeDistancia* verticeDistancia, int distancia, int* res) {
	if (verticeDistancia == NULL) { *res = 0; return NULL; }
	verticeDistancia->distancia = distancia;
	*res = 1;
	return verticeDistancia;
}

/// <summary>
/// Adiciona uma distancia a uma variavel do tipo verticeDistancias dentro de uma lista de vertice distancias
/// </summary>
/// <param name="verticeDistancia">Lista de vertice distancias</param>
/// <param name="id">Id do vertice</param>
/// <param name="distancia">Distancia</param>
/// <param name="res">Retorna 0 sea distancia nao for adicionada, retorna 1 se a distancia for adicionada</param>
/// <returns>Retorna nulo se o vertice distancia for nulo, retorna a lista de vertices distancia sem a distancia 
/// adicionada se o vertice nao existir, retorna a lista de vertices distancia com a distancia adicionada ao vertice</returns>
VerticeDistancia* AdicionarDistanciaListaVerticeDistancia(VerticeDistancia* verticeDistancia, int id, int distancia, int* res) {
	if (verticeDistancia == NULL) { *res = 0; return NULL; }

	if (VerificarAdjacencia(verticeDistancia, id) != 1) { *res = 0; return verticeDistancia; }

	VerticeDistancia* aux = verticeDistancia;
	while (aux->id != id)
		aux = aux->proxVerDist;
	aux = AdicionarDistanciaVerticeDistancia(aux, distancia, res);
	return verticeDistancia;
}

/// <summary>
/// Adiciona a todos os vertices presentes na lista vertices distancia um id
/// </summary>
/// <param name="verticeDistancias">Lista vertices distancia</param>
/// <param name="id">Id</param>
/// <param name="res">Retorna 0 se nao for adicionado os ids aos vertices, retorna 1 se for adicionado os ids aos vertices</param>
/// <returns>Retorna nulo se a lista de vertices distancias for nula, retorna a lista de vertice distancias com os ids dos vertices adicionados</returns>
VerticeDistancia* AdicionarTodosIdVerticesDistancia(VerticeDistancia* verticeDistancias, int id, int* res) {
	if (verticeDistancias == NULL) { *res = 0; return NULL; }
	VerticeDistancia* aux = verticeDistancias;
	while (aux != NULL) {
		aux = AdicionarIdVerticeDistancia(aux, id, res);
		aux = aux->proxVerDist;
	}
	*res = 1;
	return verticeDistancias;
}

/// <summary>
/// Adiciona a todos os vertices presentes na lista vertices distancia uma distancia
/// </summary>
/// <param name="verticeDistancias">Lista vertices distancia</param>
/// <param name="distancia">distancia</param>
/// <param name="res">Retorna 0 se nao for adicionado a distancia aos vertices, retorna 1 se for adicionado a distancia aos vertices</param>
/// <returns>Retorna nulo se a lista de vertices distancias for nula, retorna a lista de vertice distancias com a distancia dos vertices adicionados</returns>
VerticeDistancia* AdicionarTodosDistanciaVerticesDistancia(VerticeDistancia* verticeDistancias, int distancia, int* res) {
	if (verticeDistancias == NULL) { *res = 0; return NULL; }
	VerticeDistancia* aux = verticeDistancias;
	while (aux != NULL) {
		aux = AdicionarDistanciaVerticeDistancia(aux, distancia, res);
		aux = aux->proxVerDist;
	}
	*res = 1;
	return verticeDistancias;
}

/// <summary>
/// Adiciona a cada vertice presente na lista vertices distancia o id do vertice correspondente a lista de vertices
/// </summary>
/// <param name="verticeDistancias">Lista vertices distancia</param>
/// <param name="vertices">Lista de vertices</param>
/// <param name="res">Retorna 0 se nao for adicionado os ids aos vertices, retorna 1 se for adicionado os ids aos vertices</param>
/// <returns>Retorna nulo se a lista de vertice distancias ou vertices for nulo, retorna a lista de vertices distancias com os ids adicionados</returns>
VerticeDistancia* AdicionarTodosVerticesIdVerticesDistancia(VerticeDistancia* verticeDistancias, Vertice* vertices, int* res) {
	if (verticeDistancias == NULL) { *res = 0; return NULL; }
	if (vertices == NULL) { *res = 0; return NULL; }
	Vertice* aux = vertices;
	VerticeDistancia* auxDist = verticeDistancias;
	while (aux != NULL) {
		auxDist = AdicionarIdVerticeDistancia(auxDist, aux->id, res);
		aux = aux->proxVertice;
		auxDist = auxDist->proxVerDist;
	}

	return verticeDistancias;
}

/// <summary>
/// Adiciona um vertice distancia no fim da lista de vertice distancias
/// </summary>
/// <param name="verticeDistancias">Lista de vertice distancias</param>
/// <param name="verticeDist">Vertice distancia</param>
/// <param name="res">Retorna 0 se nao for adicionado, retorna 1 se for adicionado</param>
/// <returns>Retorna nulo se a lista de vertice distancias for nulo, retorna a lista de vertice distancias se for adicionado o vertice distancia a lista</returns>
VerticeDistancia* AdicionarVerticeDistancia(VerticeDistancia* verticeDistancias, VerticeDistancia* verticeDist, int* res) {
	if (verticeDistancias == NULL && verticeDist != NULL) { *res = 1; return verticeDistancias = verticeDist; }
	if (verticeDistancias == NULL) { *res = 0; return NULL; }

	VerticeDistancia* aux = verticeDistancias;
	while (aux->proxVerDist != NULL)
		aux = aux->proxVerDist;
	aux->proxVerDist = verticeDist;

	*res = 1;
	return verticeDistancias;
}

/// <summary>
/// Atribuir a um vertice distancia o seu anterior
/// </summary>
/// <param name="verticeDistancia">Vertice distancia</param>
/// <param name="anterior">Vertice distancia anterior</param>
/// <param name="res">Retorna 0 se o anterior nao for adicionado, retorna 1 se o seu anterior for adicionado</param>
/// <returns>Retorna nulo se o vertice distancia for nulo, retorna o vertice distancia com o seu anterior atribuido</returns>
VerticeDistancia* AtribuirVerticeDistanciaAnterior(VerticeDistancia* verticeDistancia, VerticeDistancia* anterior, int* res) {
	if (verticeDistancia == NULL) { *res = 0; return NULL; }
	return verticeDistancia->antVerDist = anterior;
}

/// <summary>
/// Atribuir a um vertice distancia presente numa lista de vertices distancias o seu anterior
/// </summary>
/// <param name="verticeDistancias">Lista de vertices distacias</param>
/// <param name="anterior">Anterior</param>
/// <param name="id">Id do vertice</param>
/// <param name="res">Retorna 0 se o anterior nao for adicionado, retorna 1 se o seu anterior for adicionado</param>
/// <returns>Retorna nulo se a lista de vertice distancia for nulo, retorna a lista de vertice distancia com o vertice distancia com o seu anterior atribuido</returns>
VerticeDistancia* AtribuirListaVerticeDistanciaAnterior(VerticeDistancia* verticeDistancias, VerticeDistancia* anterior, int id, int* res) {
	if (verticeDistancias == NULL) { *res = 0; return NULL; }
	if (VerificarVerticeDistancia(verticeDistancias, id) != 1) { *res = 0; return verticeDistancias; }
	VerticeDistancia* aux = verticeDistancias;
	while (aux->id != id)
		aux = aux->proxVerDist;
	aux = AtribuirVerticeDistanciaAnterior(aux, anterior, res);
	return verticeDistancias;
}
#pragma endregion

#pragma region Remover
/// <summary>
/// Remove um vertice dentro de uma lista de vertice distancias
/// </summary>
/// <param name="verticeDistancias">Lista de vertice distancias</param>
/// <param name="id">Id do vertice</param>
/// <param name="res">Retorna 0 se nao for removido, retorna 1 se for removido</param>
/// <returns>Retorna nulo se a lista de vertice distancias for nula, retorna a lista de vertice distancias sem o vertice removido se o mesmo nao existir e retorn lista de vertices distancias com o vertice removido</returns>
VerticeDistancia* RemoverVerticeDistacia(VerticeDistancia* verticeDistancias, int id, int* res) {
	if (verticeDistancias == NULL) { *res = 0; return NULL; }

	if (VerificarVerticeDistancia(verticeDistancias, id) != 1) { *res = 1; return verticeDistancias; }

	VerticeDistancia* aux = verticeDistancias;
	VerticeDistancia* ant = NULL;

	while (aux->id != id) {
		ant = aux;
		aux = aux->proxVerDist;
	}
	if (ant == NULL) {
		verticeDistancias = aux->proxVerDist;
		free(aux);
	}
	else {
		if (aux->proxVerDist == NULL) {
			ant->proxVerDist = NULL;
			free(aux);
		}
		else {
			ant->proxVerDist = aux->proxVerDist;
			free(aux);
		}
	}
	*res = 1;
	return verticeDistancias;
}
#pragma endregion

#pragma region Operacoes
/// <summary>
/// Soma a uma distancia do "vertice distania" um valor
/// </summary>
/// <param name="verticeDistancia">Vertice distancia</param>
/// <param name="valor">Valor</param>
/// <param name="res">Retorna 0 se nao for somado, retorna 1 se for somado</param>
/// <returns>Retorna nulo e o vertice distancia for nulo, retorna o vertice distancia se for feita a soma</returns>
VerticeDistancia* SomarDistanciasVerticeDistancia(VerticeDistancia* verticeDistancia, int valor, int* res) {
	if (verticeDistancia == NULL) { *res = 0; return NULL;}
	//if (verticeDistancia->distancia == INFINITO)
	//	verticeDistancia->distancia = 0;
	verticeDistancia->distancia = verticeDistancia->antVerDist->distancia + valor;
	return verticeDistancia;
}

/// <summary>
/// Soma a uma distancia de um id presente numa lista de vertices distania um valor
/// </summary>
/// <param name="verticeDistancia">Lista de Vertice distancia</param>
/// <param name="id">Id</param>
/// <param name="valor">Valor</param>
/// <param name="res">Retorna 0 se nao for somado, retorna 1 se for somado</param>
/// <returns>Retorna nulo e o vertice distancia for nulo, retorna o vertice distancia se for feita a soma</returns>
VerticeDistancia* SomarDistanciaListaVerticeDistancia(VerticeDistancia* verticeDistancias, int id, int valor, int* res) {
	if (verticeDistancias == NULL) { *res = 0; return NULL; }
	if (VerificarVerticeDistancia(verticeDistancias, id) != 1) { *res = 0; return verticeDistancias; }
	VerticeDistancia* aux = verticeDistancias;
	while (aux->id != id)
		aux = aux->proxVerDist;
	aux = SomarDistanciasVerticeDistancia(aux, valor, res);
	return verticeDistancias;
}

/// <summary>
/// Retorna a soma de uma distancia do "vertice distania" um valor
/// </summary>
/// <param name="verticeDistancia">Vertice distancia</param>
/// <param name="valor">Valor</param>
/// <param name="res">Retorna 0 se nao for somado, retorna 1 se for somado</param>
/// <returns>Retorna nulo e o vertice distancia for nulo, retorna o vertice distancia se for feita a soma</returns>
int SomarDistanciasVerticeDistancia2(VerticeDistancia* verticeDistancia, int valor, int* res) {
	if (verticeDistancia == NULL) { *res = 0; return NULL; }
	//if (verticeDistancia->distancia == INFINITO)
	//	verticeDistancia->distancia = 0;
	if (verticeDistancia->antVerDist == NULL) return valor;
	
	return verticeDistancia->antVerDist->distancia + valor;
}

/// <summary>
/// Retorna uma soma de uma distancia de um id presente numa lista de vertices distancia um valor
/// </summary>
/// <param name="verticeDistancia">Lista de Vertice distancia</param>
/// <param name="id">Id</param>
/// <param name="valor">Valor</param>
/// <param name="res">Retorna 0 se nao for somado, retorna 1 se for somado</param>
/// <returns>Retorna nulo e o vertice distancia for nulo, retorna o vertice distancia se for feita a soma</returns>
int SomarDistanciaListaVerticeDistancia2(VerticeDistancia* verticeDistancias, int id, int valor, int* res) {
	if (verticeDistancias == NULL) { *res = 0; return NULL; }
	if (VerificarVerticeDistancia(verticeDistancias, id) != 1) { *res = 0; return verticeDistancias; }
	VerticeDistancia* aux = verticeDistancias;
	while (aux->id != id)
		aux = aux->proxVerDist;
	return SomarDistanciasVerticeDistancia2(aux, valor, res);
}

/// <summary>
/// Soma todas as distancias presentes na lista de vertices (caminho) 
/// </summary>
/// <param name="verticeDistancias">Lista de vertice distancias</param>
/// <returns>Retorna -1 se a lista for nula, retorna a soma</returns>
int SomarTodasDistanciasListaVerticeDistancia(Vertice* verticeDistancias) {
	if (verticeDistancias == NULL) return -1;
	VerticeDistancia* aux = verticeDistancias;
	int soma = 0;
	while (aux != NULL) {
		soma += aux->distancia;
		aux = aux->proxVerDist;
	}
	return soma;
}

/// <summary>
/// Compara as distancias de um vertice distancia e um valor
/// </summary>
/// <param name="verticeDistancia">Vertice distancia</param>
/// <param name="valor">Valor</param>
/// <returns>Retorna -1 se o vertice distancia for nulo, retorna 0 se a distacia do vertice distancia for menor que o valor, 
/// retorna 1 se a distancia do vertice distancia for maior, retorna 2 se as distancias forem iguais</returns>
int CompararDistanciaVerticeDistancia(VerticeDistancia* verticeDistancia, int valor) {
	if (verticeDistancia == NULL) return -1;

	if (verticeDistancia->distancia == valor) return 2;
	else if (verticeDistancia->distancia > valor) return 1;
	else return 0;
}

/// <summary>
/// Compara as distancias de um vertice presente numa lista de vertices distancia e um valor
/// </summary>
/// <param name="verticeDistancia">Vertice distancia</param>
/// <param name="id">Id</param>
/// <param name="valor">Valor</param>
/// <returns>Retorna -1 se o vertice distancia for nulo, retorna 0 se a distacia do vertice distancia for menor que o valor, 
/// retorna 1 se a distancia do vertice distancia for maior, retorna 2 se as distancias forem iguais</returns>
int ComparaDistanciaListaVerticeDistancia(VerticeDistancia* verticeDistancia, int id, int valor) {
	if (verticeDistancia == NULL) return -1;
	if (VerificarVerticeDistancia(verticeDistancia, id) != 1) return -1;
	VerticeDistancia* aux = verticeDistancia;
	while (aux->id != id)
		aux = aux->proxVerDist;
	return CompararDistanciaVerticeDistancia(aux, valor);
}
#pragma endregion

#pragma region Verificar
/// <summary>
/// Verificam se existe um vertice dentro de uma lista de vertice distancias
/// </summary>
/// <param name="verticeDistancias">Lista de vertice distancias</param>
/// <param name="id">Id do vertice</param>
/// <returns>Retorna 0 se nao existir, retorna 1 se existir</returns>
int VerificarVerticeDistancia(VerticeDistancia* verticeDistancias, int id) {
	if (verticeDistancias == NULL) return 0;
	VerticeDistancia* aux = verticeDistancias;
	while (aux != NULL) {
		if (aux->id == id)
			return 1;
		aux = aux->proxVerDist;
	}
	return 0;
}
#pragma endregion

#pragma region Outro
/// <summary>
/// Encontra um vertice distancias a partir do seu ID e retorna o mesmo
/// </summary>
/// <param name="verticeDistancias">Lista de vertice distancias</param>
/// <param name="id">Id</param>
/// <param name="res">Retorna 0 se nao for encontrado, retorna 1 se for encontrado</param>
/// <returns>Retorna nulo se a lista de vertice distancias for nulo, retorna o vertice distancia se o mesmo existir</returns>
VerticeDistancia* EncontrarVerticeDistancia(VerticeDistancia* verticeDistancias, int id, int* res){
	if (verticeDistancias == NULL) { *res = 0; return NULL; }
	if (VerificarVerticeDistancia(verticeDistancias, id) != 1) { *res = 0; return verticeDistancias; }
	VerticeDistancia* aux = verticeDistancias;
	while (aux->id != id)
		aux = aux->proxVerDist;
	return aux;
}

/// <summary>
/// Encontra o id do vertice distancia anterior ao vertice distancia
/// </summary>
/// <param name="verticeDistancias">Lista de vertice distancia</param>
/// <param name="id">Id</param>
/// <returns>Retorna -1 se a lista de verticeDistancias for nulo ou se o vertice lista nao existir, retorna o id do vertice distancia anterior </returns>
int EncontrarIdAnteriorVerticeDistancia(VerticeDistancia* verticeDistancias, int id) {
	if (verticeDistancias == NULL) return -1;
	if (VerificarVerticeDistancia(verticeDistancias, id) != 1) return -1;
	VerticeDistancia* aux = verticeDistancias;
	while (aux->id != id)
		aux = aux->proxVerDist;
	if (aux->antVerDist != NULL)
		return aux->antVerDist->id;
	else
		return NULL;
}

/// <summary>
/// Mostra o caminho no terminal
/// </summary>
/// <param name="verticeDistancas">Lista de vertice distancas</param>
/// <param name="destino">ID do destino</param>
/// <returns></returns>
int ProcessarCaminho(VerticeDistancia* verticeDistancas,int destino) {
	if (verticeDistancas == NULL) return -1;
	if (VerificarVerticeDistancia(verticeDistancas, destino) != 1) return -1;
	int res = 0;
	VerticeDistancia* aux = EncontrarVerticeDistancia(verticeDistancas, destino, &res);
	printf("\nCaminho: %d ", aux->id);
	while (aux->antVerDist != NULL) {
		printf("%d ", aux->antVerDist->id);
		aux = aux->antVerDist;
	}

	return res;
}
#pragma endregion

