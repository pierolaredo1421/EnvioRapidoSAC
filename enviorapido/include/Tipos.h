#ifndef TIPOS_H
#define TIPOS_H

// ============================================================
//  tipos.h  —  Constantes y tipos compartidos del sistema
//  Proyecto: EnvíoRápido Perú S.A.C.
// ============================================================

#include <iostream>
#include <cstring>
using namespace std;

// ── Constantes globales ─────────────────────────────────────
const int MAX_STR    = 100;
const int INF_DIST   = 999999;   // distancia "infinita" para Dijkstra
const int MAX_NODOS  = 20;       // máximo de ciudades en el grafo

// ── Estados posibles de una encomienda ──────────────────────
enum EstadoEnvio {
    REGISTRADO,
    EN_AGENCIA,
    EN_TRANSITO,
    EN_REPARTO,
    ENTREGADO,
    REZAGADO
};

// Convierte el enum a texto legible
inline const char* estadoTexto(EstadoEnvio e) {
    switch (e) {
        case REGISTRADO:  return "Registrado";
        case EN_AGENCIA:  return "En agencia";
        case EN_TRANSITO: return "En tránsito";
        case EN_REPARTO:  return "En reparto";
        case ENTREGADO:   return "Entregado";
        case REZAGADO:    return "Rezagado";
        default:          return "Desconocido";
    }
}

// ── Utilidad: copiar string seguro ──────────────────────────
inline void copiarStr(char* dest, const char* src, int maxLen = MAX_STR) {
    strncpy(dest, src, maxLen - 1);
    dest[maxLen - 1] = '\0';
}

#endif // TIPOS_H