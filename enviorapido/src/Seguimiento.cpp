// ============================================================
//  seguimiento.cpp  —  OBJ. ESPECÍFICO 3
//  Seguimiento de encomiendas mediante Pila (LIFO)
//  Proyecto: EnvíoRápido Perú S.A.C.
// ============================================================

#include "../include/Seguimiento.h"
#include <iostream>
using namespace std;

// Registra un nuevo estado en el tope de la pila
void pushEstado(PilaHistorial& pila, int codigo,
                EstadoEnvio estado, const char* fecha,
                const char* obs) {

    NodoPila* nuevo = new NodoPila;
    nuevo->dato.codigoEnvio = codigo;
    nuevo->dato.estado      = estado;
    copiarStr(nuevo->dato.fecha,       fecha, 20);
    copiarStr(nuevo->dato.observacion, obs);

    // El nuevo nodo apunta al tope anterior y se convierte en el nuevo tope
    nuevo->siguiente = pila.tope;
    pila.tope = nuevo;
    pila.total++;

    cout << "  [HISTORIAL] Envío " << codigo
         << " -> " << estadoTexto(estado)
         << " (" << fecha << ")\n";
}

// Retira el estado más reciente de la pila
bool popEstado(PilaHistorial& pila) {
    if (pilaVacia(pila)) {
        cout << "  [!] El historial está vacío.\n";
        return false;
    }
    NodoPila* tmp = pila.tope;
    pila.tope = pila.tope->siguiente;
    delete tmp;
    pila.total--;
    return true;
}

// Muestra solo el estado más reciente (tope) sin eliminar
void verUltimoEstado(const PilaHistorial& pila) {
    if (pilaVacia(pila)) {
        cout << "  [!] Sin historial de estados.\n";
        return;
    }
    const EventoEstado& e = pila.tope->dato;
    cout << "  [ESTADO ACTUAL] Envío " << e.codigoEnvio
         << ": " << estadoTexto(e.estado)
         << " | " << e.fecha
         << " | " << e.observacion << "\n";
}

// Recorre y muestra todos los estados del historial (del más reciente al más antiguo)
void mostrarHistorial(const PilaHistorial& pila) {
    if (pilaVacia(pila)) {
        cout << "  No hay historial registrado.\n";
        return;
    }
    cout << "  Historial de estados (" << pila.total << " registro(s)):\n";
    cout << "  " << string(65, '-') << "\n";

    NodoPila* aux = pila.tope;
    int pos = 1;
    while (aux != nullptr) {
        cout << "  #" << pos++
             << " | " << estadoTexto(aux->dato.estado)
             << " | " << aux->dato.fecha
             << " | " << aux->dato.observacion << "\n";
        aux = aux->siguiente;
    }
    cout << "  " << string(65, '-') << "\n";
}

// Retorna verdadero si la pila está vacía
bool pilaVacia(const PilaHistorial& pila) {
    return pila.tope == nullptr;
}

// Libera toda la memoria de la pila
void liberarPila(PilaHistorial& pila) {
    while (!pilaVacia(pila))
        popEstado(pila);
}