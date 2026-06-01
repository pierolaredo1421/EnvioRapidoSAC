// ============================================================
//  colaAtencion.cpp  —  OBJ. ESPECÍFICO 2
//  Sistema de atención al cliente en agencias (Cola FIFO)
//  Proyecto: EnvíoRápido Perú S.A.C.
// ============================================================

#include "../include/Colaatencion.h"
#include <iostream>
using namespace std;

// Agrega un cliente al final de la cola
void encolar(ColaAtencion& cola, const char* nombre,
             const char* servicio) {

    NodoCola* nuevo = new NodoCola;
    nuevo->dato.numero = ++cola.contadorTickets;
    copiarStr(nuevo->dato.nombreCliente, nombre);
    copiarStr(nuevo->dato.tipoServicio,  servicio);
    nuevo->siguiente = nullptr;

    if (cola.frente == nullptr) {
        // Cola vacía: frente y fin apuntan al único nodo
        cola.frente = nuevo;
    } else {
        cola.fin->siguiente = nuevo;
    }
    cola.fin = nuevo;
    cola.total++;

    cout << "  [TURNO " << nuevo->dato.numero << "] "
         << nombre << " - Servicio: " << servicio << "\n";
}

// Atiende al primer cliente de la cola (FIFO)
bool atender(ColaAtencion& cola) {
    if (colaVacia(cola)) {
        cout << "  [!] No hay clientes en espera.\n";
        return false;
    }

    NodoCola* atendido = cola.frente;
    cout << "  [ATENDIENDO] Turno " << atendido->dato.numero
         << " - " << atendido->dato.nombreCliente
         << " (" << atendido->dato.tipoServicio << ")\n";

    // El frente avanza al siguiente nodo
    cola.frente = cola.frente->siguiente;
    if (cola.frente == nullptr)
        cola.fin = nullptr; // la cola quedó vacía

    delete atendido;
    cola.total--;
    return true;
}

// Muestra quién será atendido a continuación sin desencolar
void verSiguiente(const ColaAtencion& cola) {
    if (colaVacia(cola)) {
        cout << "  [!] La cola está vacía.\n";
        return;
    }
    cout << "  [PRÓXIMO] Turno " << cola.frente->dato.numero
         << " - " << cola.frente->dato.nombreCliente << "\n";
}

// Lista todos los clientes en espera
void listarCola(const ColaAtencion& cola) {
    if (colaVacia(cola)) {
        cout << "  No hay clientes en espera.\n";
        return;
    }
    cout << "  Clientes en espera: " << cola.total << "\n";
    cout << "  " << string(50, '-') << "\n";
    NodoCola* aux = cola.frente;
    while (aux != nullptr) {
        cout << "  Turno " << aux->dato.numero
             << " | " << aux->dato.nombreCliente
             << " | " << aux->dato.tipoServicio << "\n";
        aux = aux->siguiente;
    }
    cout << "  " << string(50, '-') << "\n";
}

// Retorna verdadero si la cola no tiene elementos
bool colaVacia(const ColaAtencion& cola) {
    return cola.frente == nullptr;
}

// Libera toda la memoria de la cola
void liberarCola(ColaAtencion& cola) {
    while (!colaVacia(cola))
        atender(cola);
}