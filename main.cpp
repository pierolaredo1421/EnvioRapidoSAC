// ============================================================
//  main.cpp  —  OBJ. ESPECÍFICO 5
//  Punto de entrada: integración de todos los módulos
//  Sistema de Gestión Logística — EnvíoRápido Perú S.A.C.
//
//  Módulos integrados:
//    1. Clientes y encomiendas  (lista enlazada)
//    2. Atención en agencias    (cola FIFO)
//    3. Seguimiento de envíos   (pila LIFO)
//    4. Rutas de distribución   (grafo + Dijkstra)
// ============================================================

#include <iostream>
#include <limits>
#include "enviorapido/include/Tipos.h"
#include "enviorapido/include/Clientes.h"
#include "enviorapido/include/Colaatencion.h"
#include "enviorapido/include/Seguimiento.h"
#include "enviorapido/include/Rutas.h"

using namespace std;

// ── Prototipos de menús ──────────────────────────────────────
void menuPrincipal();
void menuClientes(ListaClientes& clientes);
void menuEncomiendas(ListaEncomiendas& encomiendas,
                     ListaClientes& clientes);
void menuAgencia(ColaAtencion& cola);
void menuSeguimiento(PilaHistorial& historial,
                     ListaEncomiendas& encomiendas);
void menuRutas(Grafo& grafo);

// ── Utilidad: limpiar buffer de entrada ─────────────────────
void limpiarBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ── Separador visual ─────────────────────────────────────────
void separador(const char* titulo) {
    cout << "\n  " << string(60, '=') << "\n";
    cout << "   " << titulo << "\n";
    cout << "  " << string(60, '=') << "\n";
}

// ── Inicialización con datos de prueba ───────────────────────
void cargarDatosDemostracion(ListaClientes& clientes,
                              ListaEncomiendas& encomiendas,
                              ColaAtencion& cola,
                              PilaHistorial& historial,
                              Grafo& grafo) {

    cout << "\n  Cargando datos de demostración...\n";

    // OBJ 1 — Clientes
    registrarCliente(clientes, 1001, "Carlos Quispe",  "987001001", "Lima");
    registrarCliente(clientes, 1002, "María Huanca",   "987002002", "Arequipa");
    registrarCliente(clientes, 1003, "Juan Mamani",    "987003003", "Cusco");
    registrarCliente(clientes, 1004, "Rosa Flores",    "987004004", "Trujillo");

    // OBJ 1 — Encomiendas
    registrarEncomienda(encomiendas, 5001, 1001,
                        "Pedro Salas",  "Lima",     "Arequipa", 2.5f);
    registrarEncomienda(encomiendas, 5002, 1002,
                        "Ana Torres",   "Arequipa", "Cusco",    1.2f);
    registrarEncomienda(encomiendas, 5003, 1003,
                        "Luis Vargas",  "Cusco",    "Lima",     3.0f);
    registrarEncomienda(encomiendas, 5004, 1004,
                        "Carmen Diaz",  "Trujillo", "Piura",    0.8f);

    // OBJ 2 — Cola de atención
    encolar(cola, "Carlos Quispe", "Envio");
    encolar(cola, "Maria Huanca",  "Recojo");
    encolar(cola, "Pedro Salas",   "Reclamo");

    // OBJ 3 — Historial de envío 5001
    pushEstado(historial, 5001, REGISTRADO,
               "10/01/2025 08:00", "Recibido en agencia Lima");
    pushEstado(historial, 5001, EN_AGENCIA,
               "10/01/2025 09:30", "Clasificado para despacho");
    pushEstado(historial, 5001, EN_TRANSITO,
               "10/01/2025 14:00", "Salida a Arequipa");
    pushEstado(historial, 5001, EN_REPARTO,
               "11/01/2025 10:00", "Repartidor asignado");

    // OBJ 4 — Grafo de rutas nacionales (distancias en km)
    agregarRuta(grafo, "Lima",      "Trujillo",  557);
    agregarRuta(grafo, "Lima",      "Ica",       306);
    agregarRuta(grafo, "Lima",      "Huancayo",  298);
    agregarRuta(grafo, "Trujillo",  "Chiclayo",  209);
    agregarRuta(grafo, "Trujillo",  "Cajamarca", 296);
    agregarRuta(grafo, "Chiclayo",  "Piura",     209);
    agregarRuta(grafo, "Chiclayo",  "Cajamarca", 260);
    agregarRuta(grafo, "Ica",       "Arequipa",  660);
    agregarRuta(grafo, "Arequipa",  "Cusco",     521);
    agregarRuta(grafo, "Arequipa",  "Puno",      297);
    agregarRuta(grafo, "Cusco",     "Puno",      388);
    agregarRuta(grafo, "Huancayo",  "Arequipa",  888);

    cout << "  Datos cargados correctamente.\n";
}

// ════════════════════════════════════════════════════════════
//  MENÚ 1 — Gestión de clientes
// ════════════════════════════════════════════════════════════
void menuClientes(ListaClientes& clientes) {
    int opcion;
    do {
        separador("OBJ.1 — Gestion de Clientes (Lista Enlazada)");
        cout << "  1. Registrar cliente\n";
        cout << "  2. Buscar cliente por ID\n";
        cout << "  3. Listar todos los clientes\n";
        cout << "  0. Volver\n";
        cout << "  Opcion: ";
        cin >> opcion; limpiarBuffer();

        if (opcion == 1) {
            int id; char nom[MAX_STR], tel[20], ciu[MAX_STR];
            cout << "  ID: "; cin >> id; limpiarBuffer();
            cout << "  Nombre: "; cin.getline(nom, MAX_STR);
            cout << "  Telefono: "; cin.getline(tel, 20);
            cout << "  Ciudad: "; cin.getline(ciu, MAX_STR);
            registrarCliente(clientes, id, nom, tel, ciu);

        } else if (opcion == 2) {
            int id;
            cout << "  ID a buscar: "; cin >> id; limpiarBuffer();
            Cliente* c = buscarCliente(clientes, id);
            if (c)
                cout << "  Encontrado: " << c->nombre
                     << " | " << c->telefono
                     << " | " << c->ciudad << "\n";
            else
                cout << "  Cliente no encontrado.\n";

        } else if (opcion == 3) {
            listarClientes(clientes);
        }
    } while (opcion != 0);
}

// ════════════════════════════════════════════════════════════
//  MENÚ 1b — Gestión de encomiendas
// ════════════════════════════════════════════════════════════
void menuEncomiendas(ListaEncomiendas& encomiendas,
                     ListaClientes& clientes) {
    int opcion;
    do {
        separador("OBJ.1 — Gestion de Encomiendas (Lista Enlazada)");
        cout << "  1. Registrar encomienda\n";
        cout << "  2. Buscar encomienda por codigo\n";
        cout << "  3. Actualizar estado\n";
        cout << "  4. Listar todas las encomiendas\n";
        cout << "  0. Volver\n";
        cout << "  Opcion: ";
        cin >> opcion; limpiarBuffer();

        if (opcion == 1) {
            int cod, idCli; float peso;
            char dest[MAX_STR], orig[MAX_STR], desti[MAX_STR];
            cout << "  Codigo: ";       cin >> cod;    limpiarBuffer();
            cout << "  ID cliente: ";   cin >> idCli;  limpiarBuffer();
            if (!buscarCliente(clientes, idCli)) {
                cout << "  [!] Cliente no existe.\n"; continue;
            }
            cout << "  Destinatario: "; cin.getline(dest,  MAX_STR);
            cout << "  Ciudad origen: ";cin.getline(orig,  MAX_STR);
            cout << "  Ciudad destino:";cin.getline(desti, MAX_STR);
            cout << "  Peso (kg): ";    cin >> peso;   limpiarBuffer();
            registrarEncomienda(encomiendas, cod, idCli,
                                dest, orig, desti, peso);

        } else if (opcion == 2) {
            int cod;
            cout << "  Codigo: "; cin >> cod; limpiarBuffer();
            Encomienda* e = buscarEncomienda(encomiendas, cod);
            if (e)
                cout << "  Encontrada: " << e->destinatario
                     << " | " << e->ciudadOrigen << "->" << e->ciudadDestino
                     << " | " << estadoTexto(e->estado) << "\n";
            else
                cout << "  Encomienda no encontrada.\n";

        } else if (opcion == 3) {
            int cod, est;
            cout << "  Codigo: "; cin >> cod; limpiarBuffer();
            cout << "  Estado (0=Reg 1=Agencia 2=Transito 3=Reparto "
                    "4=Entregado 5=Rezagado): ";
            cin >> est; limpiarBuffer();
            if (est < 0 || est > 5) {
                cout << "  [!] Estado invalido.\n"; continue;
            }
            if (actualizarEstado(encomiendas, cod, (EstadoEnvio)est))
                cout << "  Estado actualizado.\n";
            else
                cout << "  Encomienda no encontrada.\n";

        } else if (opcion == 4) {
            listarEncomiendas(encomiendas);
        }
    } while (opcion != 0);
}

// ════════════════════════════════════════════════════════════
//  MENÚ 2 — Atención en agencia (Cola)
// ════════════════════════════════════════════════════════════
void menuAgencia(ColaAtencion& cola) {
    int opcion;
    do {
        separador("OBJ.2 — Atencion en Agencia (Cola FIFO)");
        cout << "  1. Tomar turno\n";
        cout << "  2. Atender siguiente cliente\n";
        cout << "  3. Ver proximo en cola\n";
        cout << "  4. Listar cola de espera\n";
        cout << "  0. Volver\n";
        cout << "  Opcion: ";
        cin >> opcion; limpiarBuffer();

        if (opcion == 1) {
            char nom[MAX_STR], srv[MAX_STR];
            cout << "  Nombre: ";   cin.getline(nom, MAX_STR);
            cout << "  Servicio (envio/recojo/reclamo): ";
            cin.getline(srv, MAX_STR);
            encolar(cola, nom, srv);
        } else if (opcion == 2) {
            atender(cola);
        } else if (opcion == 3) {
            verSiguiente(cola);
        } else if (opcion == 4) {
            listarCola(cola);
        }
    } while (opcion != 0);
}

// ════════════════════════════════════════════════════════════
//  MENÚ 3 — Seguimiento de envío (Pila)
// ════════════════════════════════════════════════════════════
void menuSeguimiento(PilaHistorial& historial,
                     ListaEncomiendas& encomiendas) {
    int opcion;
    do {
        separador("OBJ.3 — Seguimiento de Envio (Pila LIFO)");
        cout << "  1. Registrar nuevo estado de envio\n";
        cout << "  2. Ver estado actual (tope)\n";
        cout << "  3. Ver historial completo\n";
        cout << "  0. Volver\n";
        cout << "  Opcion: ";
        cin >> opcion; limpiarBuffer();

        if (opcion == 1) {
            int cod, est;
            char fecha[20], obs[MAX_STR];
            cout << "  Codigo envio: "; cin >> cod; limpiarBuffer();
            if (!buscarEncomienda(encomiendas, cod)) {
                cout << "  [!] Encomienda no encontrada.\n"; continue;
            }
            cout << "  Estado (0-5): "; cin >> est; limpiarBuffer();
            if (est < 0 || est > 5) {
                cout << "  [!] Estado invalido.\n"; continue;
            }
            cout << "  Fecha (DD/MM/YYYY HH:MM): ";
            cin.getline(fecha, 20);
            cout << "  Observacion: ";
            cin.getline(obs, MAX_STR);
            pushEstado(historial, cod, (EstadoEnvio)est, fecha, obs);
            actualizarEstado(encomiendas, cod, (EstadoEnvio)est);

        } else if (opcion == 2) {
            verUltimoEstado(historial);
        } else if (opcion == 3) {
            mostrarHistorial(historial);
        }
    } while (opcion != 0);
}

// ════════════════════════════════════════════════════════════
//  MENÚ 4 — Rutas de distribución (Grafo + Dijkstra)
// ════════════════════════════════════════════════════════════
void menuRutas(Grafo& grafo) {
    int opcion;
    do {
        separador("OBJ.4 — Rutas de Distribucion (Grafo + Dijkstra)");
        cout << "  1. Calcular ruta optima entre dos ciudades\n";
        cout << "  2. Ver todas las rutas desde una ciudad\n";
        cout << "  3. Mostrar red de rutas\n";
        cout << "  0. Volver\n";
        cout << "  Opcion: ";
        cin >> opcion; limpiarBuffer();

        if (opcion == 1) {
            char orig[MAX_STR], dest[MAX_STR];
            cout << "  Ciudad origen: ";  cin.getline(orig, MAX_STR);
            cout << "  Ciudad destino: "; cin.getline(dest, MAX_STR);
            int u = indiceCiudad(grafo, orig);
            int v = indiceCiudad(grafo, dest);
            if (u == -1 || v == -1) {
                cout << "  [!] Ciudad no encontrada en la red.\n";
                continue;
            }
            ResultadoRuta res = dijkstra(grafo, u);
            mostrarRutaOptima(grafo, res, u, v);

        } else if (opcion == 2) {
            char orig[MAX_STR];
            cout << "  Ciudad origen: "; cin.getline(orig, MAX_STR);
            int u = indiceCiudad(grafo, orig);
            if (u == -1) {
                cout << "  [!] Ciudad no encontrada.\n"; continue;
            }
            ResultadoRuta res = dijkstra(grafo, u);
            cout << "  Distancias minimas desde " << orig << ":\n";
            cout << "  " << string(45, '-') << "\n";
            for (int i = 0; i < grafo.numCiudades; i++) {
                cout << "  " << grafo.ciudades[i] << ": ";
                if (res.dist[i] == INF_DIST)
                    cout << "no alcanzable\n";
                else
                    cout << res.dist[i] << " km\n";
            }
        } else if (opcion == 3) {
            mostrarGrafo(grafo);
        }
    } while (opcion != 0);
}

// ════════════════════════════════════════════════════════════
//  MENÚ PRINCIPAL
// ════════════════════════════════════════════════════════════
int main() {

    // Instanciar las estructuras de datos de cada módulo
    ListaClientes    clientes;
    ListaEncomiendas encomiendas;
    ColaAtencion     colaAgencia;
    PilaHistorial    historialEnvios;
    Grafo            redRutas;

    cout << "\n  *** Sistema de Gestion Logistica ***\n";
    cout << "  *** EnvioRapido Peru S.A.C.       ***\n";

    cargarDatosDemostracion(clientes, encomiendas,
                            colaAgencia, historialEnvios, redRutas);

    int opcion;
    do {
        separador("Menu Principal");
        cout << "  1. Gestion de clientes        (Lista enlazada)\n";
        cout << "  2. Gestion de encomiendas     (Lista enlazada)\n";
        cout << "  3. Atencion en agencia        (Cola FIFO)\n";
        cout << "  4. Seguimiento de envios      (Pila LIFO)\n";
        cout << "  5. Rutas de distribucion      (Grafo + Dijkstra)\n";
        cout << "  0. Salir\n";
        cout << "  Opcion: ";
        cin >> opcion; limpiarBuffer();

        switch (opcion) {
            case 1: menuClientes(clientes);                         break;
            case 2: menuEncomiendas(encomiendas, clientes);         break;
            case 3: menuAgencia(colaAgencia);                       break;
            case 4: menuSeguimiento(historialEnvios, encomiendas);  break;
            case 5: menuRutas(redRutas);                            break;
            case 0: cout << "  Cerrando sistema...\n";              break;
            default: cout << "  [!] Opcion invalida.\n";            break;
        }
    } while (opcion != 0);

    // ── Liberar toda la memoria dinámica ────────────────────
    liberarClientes(clientes);
    liberarEncomiendas(encomiendas);
    liberarCola(colaAgencia);
    liberarPila(historialEnvios);
    liberarGrafo(redRutas);

    cout << "  Memoria liberada. Hasta luego.\n\n";
    return 0;
}