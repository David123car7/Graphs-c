/*****************************************************************//**
 * @file   Header.h
 * @brief  
 * 
 * @author David Carvalho
 * @date   April 2024
 *********************************************************************/

#pragma once
#include <stdbool.h>
#define INFINITO 9999

/// <summary>
/// Estrutura do grafo
/// </summary>
typedef struct Grafo {
	struct Vertice* vertInicio;
	int vertices;
}Grafo;

/// <summary>
/// Estrutura do vertice
/// </summary>
typedef struct Vertice {
	int id;
	bool visitado;
	struct Vertice* proxVertice;
	struct Adjacente* proxAdjacente;
}Vertice;

/// <summary>
/// Estrutura dos vertices adjacentes
/// </summary>
typedef struct Adjacente {
	int id;
	int peso;
	struct Adjacente* proxAdjacente;
}Adjacente;

/// <summary>
/// Estrutura da lista de inteiros
/// </summary>
typedef struct ListaInteiros {
	int num;
	struct ListaInteiros* proxInteiro;
}ListaInteiros;

/// <summary>
/// Estrutura dos vertices distancia
/// </summary>
typedef struct VerticeDistancia {
	int id;
	int distancia;
	struct VerticeDistancia* proxVerDist;
	struct VerticeDistancia* antVerDist;
}VerticeDistancia;

#pragma region Vertices
Vertice* CriarVertice();

#pragma region Adicionar/Alterar
Vertice* AdicionarDadosVertice(Vertice* vertice, int id, bool visitado, int* res);
Vertice* AdicionarVertice(Vertice* vertices, Vertice* vertice, int* res);
Vertice* AdicionarAdjacenciaVertices(Vertice* vertices, int origem, Adjacente* adjacente, int verificar, int* res);
Vertice* AlterarEstadoVerticeVisitado(Vertice* vertice, bool estado, int* res);
Vertice* AlterarEstadoVerticeVisitadoVertices(Vertice* vertices, int id, bool estado, int* res);
Vertice* AlterarEstadoVisitadoTodosVertices(Vertice* vertices, bool estado, int* res);
#pragma endregion

#pragma region Remover
Vertice* RemoverVertice(Vertice* vertices, int id, int* res);
Vertice* RemoveAdjacenteVertices(Vertice* vertices, int vertice, int adjacente, int* res);
Vertice* RemoverAdjacenteTodosVertices(Vertice* vertices, int id, int* res);
Vertice* RemoverTodosAdjacentesVertice(Vertice* vertices, int id, int* res);
#pragma endregion

#pragma region Verificacoes
int VerificarVertice(Vertice* vertices, int id);
int VerificarVerticeGrafo(Grafo* grafo, int id);
int VerificarAdjacencia(Adjacente* adjacentes, int id);
int VerificarAdjacenciaVertice(Vertice* vertices, int id);
int VerificarAdjacenciaVerticeGrafo(Grafo* grafo, int vertice, int adjacente);
int VerificarVerticeVisitado(Vertice* vertices, int id);
#pragma endregion

#pragma region Outro
Vertice* EncontrarVerticeGrafo(Grafo* grafo, int id, int* res);
Vertice* EncontrarVertice(Vertice* vertices, int id, int* res);
int ProcessarVertice(Vertice* vertice);
#pragma endregion
#pragma endregion

#pragma region VerticesAdjacentes

Adjacente* CriarAdjacente();

#pragma region Adicionar
Adjacente* AdicionarDadosAdjacente(Adjacente* adjacente, int id, int peso, int* res);
Adjacente* AdicionarAdjacencia(Adjacente* adjacentes, Adjacente* adjacente, int* res);
#pragma endregion

#pragma region Remover
Adjacente* RemoverAdjacente(Adjacente* adjacentes, int id, int* res);
int RemoverTodosAdjacentes(Adjacente* adjacentes);
#pragma endregion

#pragma region Verificar
int VerificarVerticesAdjacentesVisitados(Vertice* vertices, Adjacente* adjacentes);
int VerificarAdjacencia(Adjacente* adjacentes, int id);
#pragma endregion

#pragma region Operacoes
int CompararPesosAdjacente(Adjacente* adjacente, int valor);
#pragma endregion

#pragma region Outro
 int EncontrarIdMenorAdjacente(Adjacente* adjacentes);
int EncontrarIdMenorAdjacenteNaoVisitado(Vertice* vertices, Adjacente* adjacentes, int* res);
#pragma endregion

#pragma endregion

#pragma region Grafo

Grafo* CriarGrafo();

#pragma region Adicionar
Grafo* AdicionarVerticeGrafo(Grafo* grafo, Vertice* vertice, int* res);
Grafo* AdicionarAdjacenciaGrafo(Grafo* grafo, int origem, Adjacente* adjacente, int verificar, int* res);
#pragma endregion

#pragma region Remover
Grafo* RemoverTodosAdjacentesGrafo(Grafo* grafo, int id, int* res);
Grafo* RemoverAdjacenteTodosVerticesGrafo(Grafo* grafo, int id, int* res);
Grafo* RemoverAdjacenteGrafo(Grafo* grafo, int vertice, int adjacente, int* res);
Grafo* RemoverVerticeGrafo(Grafo* grafo, int id, int* res);
#pragma endregion

#pragma region Algoritmos
int DepthFirstTraversal(Grafo* grafo, int inicioId);
int BreadthFirstTraversal(Grafo* grafo, int inicioId);
int DeterminarMaiorCaminhoGrafo(Grafo* grafo, int inicioId, int destinoId, int* res);
#pragma endregion

#pragma region Outro
int MostrarGrafo(Grafo* grafo);
#pragma endregion
#pragma endregion

#pragma region Ficheiros
ListaInteiros* GrafoParaListaInteiros(Grafo* grafo, ListaInteiros* lista, int* res);
Grafo* CarregarGrafo(ListaInteiros* lista, int* vertices, int* res);
ListaInteiros* LerGrafoTxt(char ficheiro[], int* numVertices, int* res);
ListaInteiros* LerGrafoBin(ListaInteiros* lista, char ficheiro[], int* vertices, int* res);
int GuardarGrafoBin(ListaInteiros* lista, char ficheiro[]);
Grafo* ArrancarPrograma(char ficheiroTxt[], char ficheiroBin[], int* res);
#pragma endregion

#pragma region ListaInteiros
ListaInteiros* CriarListaInteiros();
ListaInteiros* CriarListasInteiros(int tam, int* res);

#pragma region Adicionar
ListaInteiros* AdiconarDadosListaInteiros(ListaInteiros* lista, int num, int* res);
ListaInteiros* AdicionarNumeroListaInteirosInicio(ListaInteiros* lista, ListaInteiros* numero, int* res);
ListaInteiros* AdicionarNumeroListaInteirosFim(ListaInteiros* lista, ListaInteiros* numero, int* res);
ListaInteiros* AdicionarVerticeIdListaInteiros(ListaInteiros* lista, Vertice* vertices, int* res);
ListaInteiros* CriarAdicionarNumeroListaInteirosInicio(ListaInteiros* lista, int num, int* res);
ListaInteiros* CriarAdicionarNumeroListaInteirosFim(ListaInteiros* lista, int num, int* top, int* res);
ListaInteiros* CriarAdicionarNumeroListaInteirosFim2(ListaInteiros* lista, int num, int* res);
#pragma endregion

#pragma region Operacoes
int CompararDistanciaVerticeDistancia(VerticeDistancia* verticeDistancia, int valor);
int ComparaDistanciaListaVerticeDistancia(VerticeDistancia* verticeDistancia, int id, int valor);
#pragma endregion

#pragma region Remover
ListaInteiros* RemoverNumeroListaInteiros(ListaInteiros* lista, int num, int* res);
ListaInteiros* RemoverNumeroListaInteirosComTop(ListaInteiros* lista, int num, int* top, int* res);
#pragma endregion

#pragma region Verificar
int VerificarListaInteirosVazia(ListaInteiros* lista);
int VerificarNumeroListaInteiros(ListaInteiros* lista, int num);
#pragma endregion

#pragma region Outro
int EncontrarUltimoNumeroListaInteiros(ListaInteiros* lista);
ListaInteiros* EncontrarNumeroListaInteiros(ListaInteiros* lista, int num, int* res);
#pragma endregion

#pragma endregion

#pragma region VerticeDistancias
VerticeDistancia* CriarVerticeDistancia();
VerticeDistancia* CriarVerticesDistancia(int tamanho, int* res);

#pragma region Adicionar
VerticeDistancia* AdicionarDadosVerticeDistancia(VerticeDistancia* verticeDistancia, int id, int distancia, int* res);
VerticeDistancia* AdicionarIdVerticeDistancia(VerticeDistancia* verticeDistancia, int id, int* res);
VerticeDistancia* AdicionarDistanciaVerticeDistancia(VerticeDistancia* verticeDistancia, int distancia, int* res);
VerticeDistancia* AdicionarDistanciaListaVerticeDistancia(VerticeDistancia* verticeDistancia, int id, int distancia, int* res);
VerticeDistancia* AdicionarTodosIdVerticesDistancia(VerticeDistancia* verticeDistancias, int id, int* res);
VerticeDistancia* AdicionarTodosVerticesIdVerticesDistancia(VerticeDistancia* verticeDistancias, Vertice* vertices, int* res);
VerticeDistancia* AdicionarTodosDistanciaVerticesDistancia(VerticeDistancia* verticeDistancias, int distancia, int* res);
VerticeDistancia* AdicionarVerticeDistancia(VerticeDistancia* verticeDistancias, VerticeDistancia* verticeDist, int* res);

VerticeDistancia* AtribuirVerticeDistanciaAnterior(VerticeDistancia* verticeDistancia, VerticeDistancia* anterior, int* res);
VerticeDistancia* AtribuirListaVerticeDistanciaAnterior(VerticeDistancia* verticeDistancias, VerticeDistancia* anterior, int id, int* res);
#pragma endregion

#pragma region Remover
VerticeDistancia* RemoverVerticeDistacia(VerticeDistancia* verticeDistancias, int id, int* res);
#pragma endregion

#pragma region Operacoes
VerticeDistancia* SomarDistanciasVerticeDistancia(VerticeDistancia* verticeDistancia, int valor, int* res);
VerticeDistancia* SomarDistanciaListaVerticeDistancia(VerticeDistancia* verticeDistancias, int id, int valor, int* res);
int SomarDistanciasVerticeDistancia2(VerticeDistancia* verticeDistancia, int valor, int* res);
int SomarDistanciaListaVerticeDistancia2(VerticeDistancia* verticeDistancias, int id, int valor, int* res);
int SomarTodasDistanciasListaVerticeDistancia(Vertice* verticeDistancias);
#pragma endregion

#pragma region Verificar
int VerificarVerticeDistancia(VerticeDistancia* verticeDistancias, int id);
#pragma endregion

#pragma region Outro
VerticeDistancia* EncontrarVerticeDistancia(VerticeDistancia* verticeDistancias, int id, int* res);
int EncontrarIdAnteriorVerticeDistancia(VerticeDistancia* verticeDistancias, int id);
int ProcessarCaminho(VerticeDistancia* verticeDistancas, int destino);
#pragma endregion

#pragma endregion
