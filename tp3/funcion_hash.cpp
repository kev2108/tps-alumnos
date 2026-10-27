#include "funcion_hash.h"

size_t funcion_hash(const std::string& clave) {
    //usamos la funcion hash polinomial
    size_t suma = 0;
    for (char c: clave){
        suma = suma * 31 + c; 
    }
    return suma;
}

size_t funcion_hash(int clave) {
    return (size_t)clave;
}
