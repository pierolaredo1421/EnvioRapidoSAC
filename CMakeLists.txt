cmake_minimum_required(VERSION 4.2)
project(EnvioRapidoSAC)

set(CMAKE_CXX_STANDARD 20)

add_executable(EnvioRapidoSAC
        main.cpp
        enviorapido/include/Tipos.h
        enviorapido/include/Clientes.h
        enviorapido/include/Colaatencion.h
        enviorapido/include/Seguimiento.h
        enviorapido/include/Rutas.h
        enviorapido/src/Clientes.cpp
        enviorapido/src/Colaatencion.cpp
        enviorapido/src/Seguimiento.cpp
        enviorapido/src/Rutas.cpp
)