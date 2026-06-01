#ifndef SEGUIMIENTO_H
#define SEGUIMIENTO_H

// ============================================================
//  seguimiento.h  —  OBJ. ESPECÍFICO 3
//  Seguimiento de encomiendas mediante Pila (LIFO)
//  Proyecto: EnvíoRápido Perú S.A.C.
// ============================================================

#include "Tipos.h"

// ── Estructura: evento de estado de un envío ─────────────────
struct EventoEstado {
    int         codigoEnvio;
    EstadoEnvio estado;
    char        fecha[20];      // formato "DD/MM/YYYY HH:MM"
    char        observacion[MAX_STR];
};

// ── Nodo de la pila ──────────────────────────────────────────
struct NodoPila {
    EventoEstado dato;
    NodoPila*    siguiente;
};

// ── Pila de historial de un envío ────────────────────────────
struct PilaHistorial {
    NodoPila* tope;
    int       total;
    PilaHistorial() : tope(nullptr), total(0) {}
};

// ── Prototipos ───────────────────────────────────────────────
void   pushEstado(PilaHistorial& pila, int codigo,
                  EstadoEnvio estado, const char* fecha,
                  const char* obs);
bool   popEstado(PilaHistorial& pila);           // retira el último estado
void   verUltimoEstado(const PilaHistorial& pila);
void   mostrarHistorial(const PilaHistorial& pila);
bool   pilaVacia(const PilaHistorial& pila);
void   liberarPila(PilaHistorial& pila);

#endif // SEGUIMIENTO_H