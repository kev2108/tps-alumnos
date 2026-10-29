#include "goleadores.h"

#include <iostream>

Goleadores::Goleadores() {
    // COMPLETAR (si hace falta)
}

void Goleadores::anotar_gol(const std::string& jugador) {
    // COMPLETAR
    if (goles_por_jugador.pertenece(jugador)) {
        int nuevos_goles = goles_por_jugador.obtener(jugador) + 1;
        goles_por_jugador.insertar(jugador, nuevos_goles);    
    }
    else{
        goles_por_jugador.insertar(jugador,1);
    }

    if(maximo.empty() || goles_por_jugador.obtener(jugador) > goles_por_jugador.obtener(maximo)){
        maximo = jugador;
    }
}

int Goleadores::goles(const std::string& jugador) {
    // COMPLETAR
    if (goles_por_jugador.pertenece(jugador)) {
        return goles_por_jugador.obtener(jugador);
    }
    return 0;
}

size_t Goleadores::cantidad_de_jugadores() {
    // COMPLETAR
    return goles_por_jugador.cantidad();
}

std::string Goleadores::maximo_goleador() {
    // COMPLETAR
    return maximo;
}

void Goleadores::imprimir_por_nombre() {
    // OPTATIVO
}

void Goleadores::imprimir_por_goles() {
    // OPTATIVO
}
