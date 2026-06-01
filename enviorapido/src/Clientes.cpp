// ============================================================
//  clientes.cpp  —  OBJ. ESPECÍFICO 1
//  Gestión de clientes y encomiendas con lista enlazada
//  Proyecto: EnvíoRápido Perú S.A.C.
// ============================================================

#include "../include/Clientes.h"

#include <iostream>
using namespace std;

// ── CLIENTES ─────────────────────────────────────────────────

// Registra un nuevo cliente al final de la lista
void registrarCliente(ListaClientes& lista, int id,
                      const char* nombre, const char* tel,
                      const char* ciudad) {

    // Verificar que el ID no esté duplicado
    if (buscarCliente(lista, id) != nullptr) {
        cout << "  [!] Ya existe un cliente con ID " << id << "\n";
        return;
    }

    NodoCliente* nuevo = new NodoCliente;
    nuevo->dato.id = id;
    copiarStr(nuevo->dato.nombre,   nombre);
    copiarStr(nuevo->dato.telefono, tel, 20);
    copiarStr(nuevo->dato.ciudad,   ciudad);
    nuevo->siguiente = nullptr;

    // Insertar al final (orden de registro)
    if (lista.cabeza == nullptr) {
        lista.cabeza = nuevo;
    } else {
        NodoCliente* aux = lista.cabeza;
        while (aux->siguiente != nullptr)
            aux = aux->siguiente;
        aux->siguiente = nuevo;
    }
    lista.total++;
    cout << "  [OK] Cliente '" << nombre << "' registrado.\n";
}

// Búsqueda por ID — retorna puntero o nullptr
Cliente* buscarCliente(ListaClientes& lista, int id) {
    NodoCliente* aux = lista.cabeza;
    while (aux != nullptr) {
        if (aux->dato.id == id)
            return &aux->dato;
        aux = aux->siguiente;
    }
    return nullptr;
}

// Muestra todos los clientes registrados
void listarClientes(const ListaClientes& lista) {
    if (lista.cabeza == nullptr) {
        cout << "  No hay clientes registrados.\n";
        return;
    }
    cout << "  Total: " << lista.total << " cliente(s)\n";
    cout << "  " << string(60, '-') << "\n";
    NodoCliente* aux = lista.cabeza;
    while (aux != nullptr) {
        cout << "  ID: "       << aux->dato.id
             << "  Nombre: "   << aux->dato.nombre
             << "  Tel: "      << aux->dato.telefono
             << "  Ciudad: "   << aux->dato.ciudad << "\n";
        aux = aux->siguiente;
    }
    cout << "  " << string(60, '-') << "\n";
}

// Libera toda la memoria de la lista de clientes
void liberarClientes(ListaClientes& lista) {
    NodoCliente* aux = lista.cabeza;
    while (aux != nullptr) {
        NodoCliente* tmp = aux;
        aux = aux->siguiente;
        delete tmp;
    }
    lista.cabeza = nullptr;
    lista.total  = 0;
}

// ── ENCOMIENDAS ───────────────────────────────────────────────

// Registra una nueva encomienda al final de la lista
void registrarEncomienda(ListaEncomiendas& lista, int codigo,
                         int idCliente, const char* dest,
                         const char* origen, const char* destino,
                         float peso) {

    if (buscarEncomienda(lista, codigo) != nullptr) {
        cout << "  [!] Ya existe una encomienda con código " << codigo << "\n";
        return;
    }

    NodoEncomienda* nuevo = new NodoEncomienda;
    nuevo->dato.codigo    = codigo;
    nuevo->dato.idCliente = idCliente;
    nuevo->dato.peso      = peso;
    nuevo->dato.estado    = REGISTRADO;
    copiarStr(nuevo->dato.destinatario,  dest);
    copiarStr(nuevo->dato.ciudadOrigen,  origen);
    copiarStr(nuevo->dato.ciudadDestino, destino);
    nuevo->siguiente = nullptr;

    if (lista.cabeza == nullptr) {
        lista.cabeza = nuevo;
    } else {
        NodoEncomienda* aux = lista.cabeza;
        while (aux->siguiente != nullptr)
            aux = aux->siguiente;
        aux->siguiente = nuevo;
    }
    lista.total++;
    cout << "  [OK] Encomienda " << codigo << " registrada ("
         << origen << " -> " << destino << ").\n";
}

// Búsqueda por código — retorna puntero o nullptr
Encomienda* buscarEncomienda(ListaEncomiendas& lista, int codigo) {
    NodoEncomienda* aux = lista.cabeza;
    while (aux != nullptr) {
        if (aux->dato.codigo == codigo)
            return &aux->dato;
        aux = aux->siguiente;
    }
    return nullptr;
}

// Actualiza el estado de una encomienda
bool actualizarEstado(ListaEncomiendas& lista, int codigo,
                      EstadoEnvio nuevoEstado) {
    Encomienda* e = buscarEncomienda(lista, codigo);
    if (e == nullptr) return false;
    e->estado = nuevoEstado;
    return true;
}

// Muestra todas las encomiendas registradas
void listarEncomiendas(const ListaEncomiendas& lista) {
    if (lista.cabeza == nullptr) {
        cout << "  No hay encomiendas registradas.\n";
        return;
    }
    cout << "  Total: " << lista.total << " encomienda(s)\n";
    cout << "  " << string(65, '-') << "\n";
    NodoEncomienda* aux = lista.cabeza;
    while (aux != nullptr) {
        const Encomienda& e = aux->dato;
        cout << "  Cod: "    << e.codigo
             << "  Dest: "   << e.destinatario
             << "  Ruta: "   << e.ciudadOrigen << "->" << e.ciudadDestino
             << "  Peso: "   << e.peso << "kg"
             << "  Estado: " << estadoTexto(e.estado) << "\n";
        aux = aux->siguiente;
    }
    cout << "  " << string(65, '-') << "\n";
}

// Libera toda la memoria de la lista de encomiendas
void liberarEncomiendas(ListaEncomiendas& lista) {
    NodoEncomienda* aux = lista.cabeza;
    while (aux != nullptr) {
        NodoEncomienda* tmp = aux;
        aux = aux->siguiente;
        delete tmp;
    }
    lista.cabeza = nullptr;
    lista.total  = 0;
}