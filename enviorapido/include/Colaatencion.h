#ifndef COLA_ATENCION_H
#define COLA_ATENCION_H

// ============================================================
//  colaAtencion.h  —  OBJ. ESPECÍFICO 2
//  Sistema de atención al cliente en agencias (Cola FIFO)
//  Proyecto: EnvíoRápido Perú S.A.C.
// ============================================================

#include "Tipos.h"

// ── Estructura: ticket de un cliente en cola ─────────────────
struct Ticket {
    int  numero;               // número de turno
    char nombreCliente[MAX_STR];
    char tipoServicio[MAX_STR]; // "envío", "recojo", "reclamo"
};

// ── Nodo de la cola ──────────────────────────────────────────
struct NodoCola {
    Ticket    dato;
    NodoCola* siguiente;
};

// ── Cola FIFO de atención ────────────────────────────────────
struct ColaAtencion {
    NodoCola* frente;
    NodoCola* fin;
    int       total;
    int       contadorTickets; // auto-incremental

    ColaAtencion() : frente(nullptr), fin(nullptr),
                     total(0), contadorTickets(0) {}
};

// ── Prototipos ───────────────────────────────────────────────
void   encolar(ColaAtencion& cola, const char* nombre,
               const char* servicio);
bool   atender(ColaAtencion& cola);          // desencola y atiende
void   verSiguiente(const ColaAtencion& cola);
void   listarCola(const ColaAtencion& cola);
bool   colaVacia(const ColaAtencion& cola);
void   liberarCola(ColaAtencion& cola);

#endif // COLA_ATENCION_H