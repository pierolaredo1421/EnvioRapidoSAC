#ifndef CLIENTES_H
#define CLIENTES_H

// ============================================================
//  clientes.h  —  OBJ. ESPECÍFICO 1
//  Gestión de clientes y encomiendas con lista enlazada
//  Proyecto: EnvíoRápido Perú S.A.C.
// ============================================================

#include "Tipos.h"

// ── Estructura: datos de un cliente ─────────────────────────
struct Cliente {
    int  id;
    char nombre[MAX_STR];
    char telefono[20];
    char ciudad[MAX_STR];
};

// ── Estructura: datos de una encomienda ─────────────────────
struct Encomienda {
    int     codigo;
    int     idCliente;           // cliente remitente
    char    destinatario[MAX_STR];
    char    ciudadOrigen[MAX_STR];
    char    ciudadDestino[MAX_STR];
    float   peso;                // en kilogramos
    EstadoEnvio estado;
};

// ── Nodo de la lista enlazada de clientes ───────────────────
struct NodoCliente {
    Cliente      dato;
    NodoCliente* siguiente;
};

// ── Nodo de la lista enlazada de encomiendas ────────────────
struct NodoEncomienda {
    Encomienda      dato;
    NodoEncomienda* siguiente;
};

// ── Lista de Clientes ───────────────────────────────────────
struct ListaClientes {
    NodoCliente* cabeza;
    int          total;
    ListaClientes() : cabeza(nullptr), total(0) {}
};

// ── Lista de Encomiendas ─────────────────────────────────────
struct ListaEncomiendas {
    NodoEncomienda* cabeza;
    int             total;
    ListaEncomiendas() : cabeza(nullptr), total(0) {}
};

// ── Prototipos: clientes ─────────────────────────────────────
void   registrarCliente(ListaClientes& lista, int id,
                        const char* nombre, const char* tel,
                        const char* ciudad);
Cliente* buscarCliente(ListaClientes& lista, int id);
void   listarClientes(const ListaClientes& lista);
void   liberarClientes(ListaClientes& lista);

// ── Prototipos: encomiendas ──────────────────────────────────
void   registrarEncomienda(ListaEncomiendas& lista, int codigo,
                           int idCliente, const char* dest,
                           const char* origen, const char* destino,
                           float peso);
Encomienda* buscarEncomienda(ListaEncomiendas& lista, int codigo);
bool   actualizarEstado(ListaEncomiendas& lista, int codigo,
                        EstadoEnvio nuevoEstado);
void   listarEncomiendas(const ListaEncomiendas& lista);
void   liberarEncomiendas(ListaEncomiendas& lista);

#endif // CLIENTES_H