#include <iostream>
#include <cmath>

struct points { int x; int y; int r; };

typedef struct Node {
	int num; //número do vértice
	int dist; // peso da aresta
	struct Node* prox; // próximo nó
}NODE;

typedef struct Grafo {
	int v; // número de vertices do grafo
	int a; // número de arcos do grafo
	points* p;
	NODE** n;   
}GRAFO;

/*
* Função de inicialização do grafo, passando o número de vertices como parâmetro
*/
GRAFO* GrafoInit(int v) {
	GRAFO* g = new GRAFO;
	g->n = new NODE*[v]; // aloca o vetor de lista ligada
	g->p = new points[v];
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
NODE* NEWnode(int v, int d, NODE* prox) {
	NODE* a = new NODE;
	a->num = v;
	a->dist = d;
	a->prox = prox;
	return a;
}

/*
* Procedimento que remove um nó da lista ligada;
*/
void RemoveNode(GRAFO* g, int v, int w) {
	NODE** rmv = &g->n[v];
	while (*rmv != nullptr && (*rmv)->num != w) {
		rmv = &(*rmv)->prox;
	}
	if (*rmv != nullptr) {
		NODE* aux = (*rmv);
		*rmv = aux->prox;
		delete aux;
	}
	g->a--;
}

/*
* Procedimento de inserção de aresta
*/
void GrafoInsertLink(GRAFO* g, int v, int w, int d) {
	for (NODE* a = g->n[v]; a != nullptr; a = a->prox)
		if (a->num == w) return;
	g->n[v] = NEWnode(w, d, g->n[v]);
	g->a++;
}

/*
* Procedimento de inserção de aresta bidirecionalmente
*/
void GrafoBiLink(GRAFO* g, int v, int w, int d) {
	GrafoInsertLink(g, v, w, d);
	GrafoInsertLink(g, w, v, d);
}

/*
* Procedimento de remoção de aresta
*/
void GrafoRemoveLink(GRAFO* g, int v, int w) {
	RemoveNode(g, v, w);
	RemoveNode(g, w, v);
}

/*
* Procedimento para desalocar o espaço de memória do grafo
*/
void DestroyGrafo(GRAFO* g) {
	NODE* aux;
	for(int i = 0; i < g->v; i++){
		while (g->n[i] != nullptr) {
			aux = g->n[i];
			g->n[i] = aux->prox;
			delete aux;
		}
	}
	delete[] g->n;
	delete[] g->p;
	delete g;
}

void GrafoShow(GRAFO* g) {
	for (int i = 0; i < g->v; i++) {
		std::cout << i << ": ";
		for (NODE* a = g->n[i]; a != nullptr; a = a->prox) {
			std::cout << a->num << " ";
		}
		std::cout << std::endl;
	}
}

int GrafoOutDeg(GRAFO* g, int v) {
	int o = 0;
	for (NODE* a = g->n[v]; a != nullptr; a = a->prox)
		o++;
	return o;
}

int dist(points a1, points a2) {
	double d = sqrt(pow(a1.x - a2.x, 2) + pow(a1.y - a2.y, 2));
	return floor(d);
}

void IsReachable(GRAFO *g, int idx1, int idx2) {
	int d = dist(g->p[idx1], g->p[idx2]);
	if (d > g->p[idx1].r)
		std::cout << "output: " << -1 << std::endl;
	else {
		std::cout << "output: " << d << std::endl;
		GrafoInsertLink(g, idx1, idx2, d);
	}
}

int main(int argc, char **argv) {
	int n, c, idx1, idx2;
	int x, y, r;
	GRAFO* g; 
	while (true) {
		std::cin >> n;
		if (!n) return -1;

		g = GrafoInit(n);
		//loop para inserir as coordenadas das antenas
		for (int i = 0; i < n; i++) {
			std::cin >> x >> y >> r;
			g->p[i].x = x;
			g->p[i].y = y;
			g->p[i].r = r;
		}
		//loop para verificar a menor distância entre as antenas; 
		std::cin >> c;
		for (int i = 0; i < c; i++) {
			std::cin >> idx1 >> idx2;
			IsReachable(g, idx1-1, idx2-1);
		}
		DestroyGrafo(g);
	}

	return 0;
}