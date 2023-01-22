#include <iostream>
#include <cmath>

struct points { int x; int y; int r; };

typedef struct Node {
	int num; //número do vértice
	int dist;
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

/*
* Função que remove um nó da lista ligada;
*/
NODE* RemoveNode(NODE* rmv) {
	NODE* aux = rmv->prox;
	delete rmv;
	return aux;
}

/*
* Função para desalocar o espaço de memória do grafo
*/
void DestroyGrafo(GRAFO* g) {
	delete[] g->p;
	for(int i = 0; i < g->v; i++){
		for (NODE* a = g->n[i]; a != nullptr;) {
			g->n[i] = RemoveNode(a);
			a = g->n[i];
		}
	}
	delete[] g->n;
	delete g;
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
		GrafoInsertLink(g, idx1, idx2);
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