#ifndef RUTAS_H
#define RUTAS_H

// ============================================================
//  rutas.h  —  OBJ. ESPECÍFICO 4
//  Red de distribución nacional como grafo ponderado
//  Algoritmo de Dijkstra para ruta de menor costo
//  Proyecto: EnvíoRápido Perú S.A.C.
// ============================================================

#include "Tipos.h"

// ── Nodo de lista de adyacencia (vecinos de una ciudad) ──────
struct NodoAdyacente {
    int            destino;   // índice de la ciudad destino
    int            costo;     // distancia en km
    NodoAdyacente* siguiente;
};

// ── Grafo no dirigido con lista de adyacencia ────────────────
struct Grafo {
    char           ciudades[MAX_NODOS][MAX_STR]; // nombres
    NodoAdyacente* adyacencia[MAX_NODOS];        // listas de vecinos
    int            numCiudades;

    Grafo() : numCiudades(0) {
        for (int i = 0; i < MAX_NODOS; i++)
            adyacencia[i] = nullptr;
    }
};

// ── Resultado de Dijkstra ────────────────────────────────────
struct ResultadoRuta {
    int dist[MAX_NODOS];    // distancia mínima desde el origen
    int prev[MAX_NODOS];    // nodo previo en el camino óptimo
};

// ── Prototipos ───────────────────────────────────────────────
int  agregarCiudad(Grafo& g, const char* nombre);
int  indiceCiudad(const Grafo& g, const char* nombre);
void agregarRuta(Grafo& g, const char* origen,
                 const char* destino, int costo);
void mostrarGrafo(const Grafo& g);

ResultadoRuta dijkstra(const Grafo& g, int origen);
void mostrarRutaOptima(const Grafo& g, const ResultadoRuta& res,
                       int origen, int destino);
void liberarGrafo(Grafo& g);

#endif // RUTAS_H