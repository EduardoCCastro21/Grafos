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

/*
* Função para auxiliar função de circuitos
*/
static bool AuxCircuito( GRAFO* G, int v, int *pre, int *pa) { 
   int cnt = 0;
   pre[v] = cnt++;
   for (NODE* a = G->n[v]; a != NULL; a = a->prox) {
      int num = a->num;
      if (pre[num] == -1) {
         pa[num] = v; 
         if (AuxCircuito( G, num, pre, pa)) return true;
      } else { // pre[w] < pre[v]
         if (num != pa[v]) return true; 
      }
   }
   return false;
}

/*
* Função de Circuitos
*/
bool All_Circuito( GRAFO* G) {
   int *pre = (int *) malloc( G->v * sizeof (int));
   int *pa = (int *) malloc( G->v * sizeof (int));
   int cnt = 0;
   for (int x = 0; x < G->v; ++x)
      pre[x] = -1;
   for (int x = 0; x < G->v; ++x) {
      if (pre[x] == -1) {
         pa[x] = x;
         if (AuxCircuito( G, x, pre, pa)) {
            free( pre); free( pa);
            return true;
         }
      }
   }
   free( pre); free( pa);
   return false;
}
/*
* Função Auxiliar de DFS
*/
static void AuxDFS( GRAFO* G, int v, int *pre, int *post, int *pa) { 
   int cnt = 0;
   int cntt = 0;
   pre[v] = cnt++; 
   for (NODE* a = G->n[v]; a != NULL; a = a->prox)
      if (pre[a->num] == -1) {
         pa[a->num] = v; 
         DFS( G, a->num, pre, post, pa); 
      } 
   post[v] = cntt++;
}
 
/*
* Função DFS (Depth-first search)
*/

void DFS( GRAFO* G, int *pre, int *post, int *pa) { 
   int cnt = 0;
   int cntt = 0; 
   for (int x = 0; x < G->v; ++x) 
      pre[x] = post[x] = -1; // A
   for (int x = 0; x < G->v; ++x)
      if (pre[x] == -1) {
         pa[x] = x;
         DFS( G, x, pre, post, pa); // nova etapa
      }
}

/*
* Função BFS (Breadth-first search)
*/

static void GrafoBFS( GRAFO* G, int s, int num[], int pa[]) { 
   for (int x = 0; x < G->v; ++x) 
      num[x] = -1;
   int c = 0;
   num[s] = c++;
   pa[s] = s;
   QUEUEinit( G->v);
   QUEUEput( s); 
   while (!QUEUEempty( )) {
      int x = QUEUEget( ); 
      for (NODE* a = G->n[x]; a != NULL; a = a->prox)
         if (num[a->num] == -1) {
            num[a->num] = c++; 
            pa[a->num] = x;
            QUEUEput( a->num); 
         }
   }
   QUEUEfree( ); 
}

/*
* Função de Dijkstra
*/

void Dijkstra( GRAFO* G, int s, int *pa, int *dist) { 
   for (int x = 0; x < G->v; ++x) 
      pa[x] = -1, dist[x] = INT_MAX;
   pa[s] = s, dist[s] = 0; 
   while (true) {
      int minc = INT_MAX;
      int z = 0; 
      int y = 0;
      for (int x = 0; x < G->v; ++x) {
         if (pa[x] == -1) continue;
         for (NODE* a = G->n[x]; a != NULL; a = a->prox) {
            if (pa[a->num] != -1) continue;
            if (dist[x] + a->dist < minc) {
               minc = dist[x] + a->dist;
               z = x, y = a->num;
            }
         }
      }
      if (minc == INT_MAX) break; 
      pa[y] = z, dist[y] = minc;
   }
}

/*
* Função de Bellman-Ford
*/

int BellmanFord( GRAFO* G, int s, int *pa, int *dist) { 
   QUEUEinit( G->a);
   bool *onqueue = (bool *) malloc( G->v * sizeof (bool));
   for (int u = 0; u < G->v; ++u)
      pa[u] = -1, dist[u] = INT_MAX, onqueue[u] = false;
   pa[s] = s, dist[s] = 0;
   QUEUEput( s);
   onqueue[s] = true;
   int j = G->v; 
   QUEUEput( j); // sentinela
   int k = 0;
   while (true) {
      int z = QUEUEget( );
      if (z < j) {
         for (NODE* a = G->n[z]; a != NULL; a = a->prox) {
            if (dist[z] + a->dist < dist[a->num]) {
               dist[a->num] = dist[z] + a->dist; 
               pa[a->num] = z;
               if (onqueue[a->num] == false) {
                  QUEUEput( a->num);
                  onqueue[a->num] = true;
               }
            }
         }
      } else { 
         if (QUEUEempty( )) {
            QUEUEfree( );
            free( onqueue);
            return -1; 
         }
         if (++k >= G->v) break;  
         QUEUEput( j); // sentinela na fila
         for (int u = 0; u < G->v; ++u) onqueue[u] = false;
      }
   }
   free( onqueue);
   // procura ciclo negativo:
   while (true) {
      int z = QUEUEget( ); 
      for (NODE* a = G->n[z]; a != NULL; a = a->prox) {
         if (dist[z] + a->dist < dist[a->num]) { 
            QUEUEfree( );
            bool *visited = (bool *) malloc( G->v * sizeof (bool));
            for (int u = 0; u < G->v; ++u) visited[u] = false;
            while (!visited[z]) {
               visited[z] = true;
               z = pa[z];
            } 
            free( visited);
            return z;
         }
      }
   }
}

/*
* Função de Prim
*/

int Prim( GRAFO* G, int pa[]) { 
   for (int w = 0; w < G->v; ++w) pa[w] = -1; 
   int s = 0;
   pa[s] = s; 
   int mstcost = 0;
   while (true) {
      int minc = INT_MAX;
      int x = 0, y = 0;
      for (int k = 0; k < G->v; ++k) {
         if (pa[k] == -1) continue; 
         for (NODE* a = G->n[k]; a != NULL; a = a->prox) 
            if (pa[a->num] == -1 && a->dist < minc) {
               minc = a->dist;
               x = k, y = a->num;
            }
      }   
      if (minc == INT_MAX) break; 
      pa[y] = x;
      mstcost += minc;
   }
   return mstcost;
}

/*
* Criação de um vértice auxiliar para Kruskal
*/

typedef struct { 
    int v; 
    int w; 
    int c; 
} edge;
static edge EDGE( int v, int w, int c) {
   edge e;
   e.v = v, e.w = w; e.c = c;
   return e;
}

/*
* Função de Kruskal
*/


int Kruskal( GRAFO* G, edge mst[]) { 
   int *chefe =(int *) malloc(G->v * sizeof (int));
   for (int x = 0; x < G->v; ++x) 
      chefe[x] = x;
   int k = 0;
   int mstcost = 0;
   while (true) {
      // a floresta tem arestas mst[0..k-1]
      int minc = INT_MAX;
     int x; 
     int y;
      for (int j = 0; j < G->v; ++j) {
         for (NODE* a = G->n[j]; a != NULL; a = a->prox) {
            int num = a->num; int dist = a->dist;
            if (j < num && chefe[j] != chefe[num] && dist < minc) {
               minc = dist;
               x = j, y = num;
            }
         }
      }
      if (minc == INT_MAX) return mstcost;
      edge e; e.v = x, e.w = y, e.c = minc; 
      mstcost += e.c;
      mst[k++] = e;
      int v0 = chefe[x], w0 = chefe[y];
      for (int n = 0; n < G->v; ++n)
         if (chefe[n] == w0)
            chefe[n] = v0;
   }
   free( chefe);
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
