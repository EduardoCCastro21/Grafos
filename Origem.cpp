#include <iostream>

typedef struct Node {
	int num; //número do vértice
	struct Node* prox; // próximo nó
}NODE;

typedef struct Grafo {
	int v; // número de vertices do grafo
	int a; // número de arcos do grafo
	NODE** n;   
}GRAFO;

/*
* Função de inicialização do grafo, passando o número de vertices como parâmetro
*/
GRAFO* GrafoInit(int v) {
	GRAFO* g = new GRAFO;
	g->n = new NODE*[v]; // aloca o vetor de lista ligada
	g->v = v;
	g->a = 0;
	for (int i = 0; i < v; i++) {
		g->n[i] = nullptr;
	}
	return g;
}

/*
* função que insere um novo nó a lista 
*/
NODE* NEWnode(int v, NODE* prox) {
	NODE* a = new NODE;
	a->num = v;
	a->prox = prox;
	return a;
}

/*
* Procedimento de inserção de arestas
*/
void GrafoInsertLink(GRAFO* g, int v, int w) {
	for (NODE* a = g->n[v]; a != nullptr; a = a->prox)
		if (a->num == v) return;
	g->n[v] = NEWnode(w, g->n[v]);
	g->a++;
}

int main(int argc, char **argv) {
	GRAFO* g = GrafoInit(5);
	GrafoInsertLink(g, 0, 5);
	std::cout << "no 0 está ligado ao no " << g->n[0]->num << std::endl;

	return 0;
}