// ============================================================
//  rutas.cpp  —  OBJ. ESPECÍFICO 4
//  Red de distribución nacional como grafo ponderado
//  Algoritmo de Dijkstra para ruta de menor costo
//  Proyecto: EnvíoRápido Perú S.A.C.
// ============================================================

#include "../include/Rutas.h"
#include <iostream>
using namespace std;

// ── Gestión del grafo ─────────────────────────────────────────

// Agrega una ciudad y retorna su índice
int agregarCiudad(Grafo& g, const char* nombre) {
    // Verificar si ya existe
    int idx = indiceCiudad(g, nombre);
    if (idx != -1) return idx;

    if (g.numCiudades >= MAX_NODOS) {
        cout << "  [!] Grafo lleno, no se puede agregar más ciudades.\n";
        return -1;
    }
    copiarStr(g.ciudades[g.numCiudades], nombre);
    g.adyacencia[g.numCiudades] = nullptr;
    return g.numCiudades++;
}

// Retorna el índice de una ciudad, o -1 si no existe
int indiceCiudad(const Grafo& g, const char* nombre) {
    for (int i = 0; i < g.numCiudades; i++)
        if (strcmp(g.ciudades[i], nombre) == 0)
            return i;
    return -1;
}

// Agrega una arista bidireccional (ruta de ida y vuelta)
void agregarRuta(Grafo& g, const char* origen,
                 const char* destino, int costo) {

    int u = agregarCiudad(g, origen);
    int v = agregarCiudad(g, destino);
    if (u == -1 || v == -1) return;

    // Insertar u -> v
    NodoAdyacente* nUV  = new NodoAdyacente;
    nUV->destino         = v;
    nUV->costo           = costo;
    nUV->siguiente       = g.adyacencia[u];
    g.adyacencia[u]      = nUV;

    // Insertar v -> u (grafo no dirigido)
    NodoAdyacente* nVU  = new NodoAdyacente;
    nVU->destino         = u;
    nVU->costo           = costo;
    nVU->siguiente       = g.adyacencia[v];
    g.adyacencia[v]      = nVU;
}

// Muestra las conexiones del grafo
void mostrarGrafo(const Grafo& g) {
    cout << "  Red de rutas (" << g.numCiudades << " ciudades):\n";
    cout << "  " << string(55, '-') << "\n";
    for (int i = 0; i < g.numCiudades; i++) {
        cout << "  " << g.ciudades[i] << " -> ";
        NodoAdyacente* aux = g.adyacencia[i];
        if (aux == nullptr) {
            cout << "(sin conexiones)";
        } else {
            while (aux != nullptr) {
                cout << g.ciudades[aux->destino]
                     << "(" << aux->costo << "km)";
                if (aux->siguiente) cout << ", ";
                aux = aux->siguiente;
            }
        }
        cout << "\n";
    }
    cout << "  " << string(55, '-') << "\n";
}

// ── Algoritmo de Dijkstra ─────────────────────────────────────
// Calcula las distancias mínimas desde el nodo origen
// Implementación con arreglo simple (sin STL priority_queue)
ResultadoRuta dijkstra(const Grafo& g, int origen) {
    ResultadoRuta res;
    bool visitado[MAX_NODOS] = {false};

    // Inicializar distancias en infinito y previos en -1
    for (int i = 0; i < g.numCiudades; i++) {
        res.dist[i] = INF_DIST;
        res.prev[i] = -1;
    }
    res.dist[origen] = 0;

    // Iterar numCiudades veces
    for (int iter = 0; iter < g.numCiudades; iter++) {

        // Seleccionar el nodo no visitado con menor distancia
        int u = -1;
        for (int i = 0; i < g.numCiudades; i++) {
            if (!visitado[i] &&
                (u == -1 || res.dist[i] < res.dist[u]))
                u = i;
        }
        if (u == -1 || res.dist[u] == INF_DIST) break;

        visitado[u] = true;

        // Relajar aristas de los vecinos de u
        NodoAdyacente* aux = g.adyacencia[u];
        while (aux != nullptr) {
            int v    = aux->destino;
            int peso = aux->costo;
            if (!visitado[v] && res.dist[u] + peso < res.dist[v]) {
                res.dist[v] = res.dist[u] + peso;
                res.prev[v] = u;
            }
            aux = aux->siguiente;
        }
    }
    return res;
}

// Muestra la ruta óptima entre dos ciudades reconstruyendo el camino
void mostrarRutaOptima(const Grafo& g, const ResultadoRuta& res,
                       int origen, int destino) {

    if (res.dist[destino] == INF_DIST) {
        cout << "  [!] No existe ruta entre "
             << g.ciudades[origen] << " y "
             << g.ciudades[destino] << "\n";
        return;
    }

    // Reconstruir el camino de atrás hacia adelante con pila auxiliar
    int camino[MAX_NODOS];
    int longitud = 0;
    int actual   = destino;
    while (actual != -1) {
        camino[longitud++] = actual;
        actual = res.prev[actual];
    }

    cout << "  Ruta optima: ";
    for (int i = longitud - 1; i >= 0; i--) {
        cout << g.ciudades[camino[i]];
        if (i > 0) cout << " -> ";
    }
    cout << "\n  Distancia total: " << res.dist[destino] << " km\n";
}

// Libera toda la memoria del grafo
void liberarGrafo(Grafo& g) {
    for (int i = 0; i < g.numCiudades; i++) {
        NodoAdyacente* aux = g.adyacencia[i];
        while (aux != nullptr) {
            NodoAdyacente* tmp = aux;
            aux = aux->siguiente;
            delete tmp;
        }
        g.adyacencia[i] = nullptr;
    }
    g.numCiudades = 0;
}