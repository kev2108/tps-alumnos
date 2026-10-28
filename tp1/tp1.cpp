#include "tp1.h"

/* ---------------------------------------------------------------
 * Parte 1: funciones libres (no operan sobre un arreglo).
 * --------------------------------------------------------------- */

bool is_prime(int x) {
    // TODO: determinar si x es primo.
    if (x < 2) {
        return false;
    }
    for (int i = x-1; i > 1; i--) {
        if (x%i==0) {
            return false;
        }
    }
    return true;
}

int storage_capacity(float d, float v) {
    // TODO: calcular cuántos productos de volumen v entran en el depósito d.
    return int(d/v);
}

void swap(int *x, int *y) {
    // TODO: intercambiar los valores de x e y.
    int actual = *x;
    *x = *y;
    *y = actual;
}

/* ---------------------------------------------------------------
 * Parte 2: CustomVector. Administra su propia memoria con
 * new/delete. Recordá la regla de los tres: destructor,
 * constructor de copia y operator=.
 * --------------------------------------------------------------- */

CustomVector::CustomVector(int length) {
    // TODO: reservar memoria para 'length' enteros y setear capacity.
    this->length = length;
    this->capacity = length;
    this->data = new int[length];
}

CustomVector::CustomVector(const int *array, int length) {
    // TODO: reservar memoria, copiar 'length' enteros desde 'array' y
    // setear capacity.
    this->length = length;
    this->capacity = length;
    this->data = new int[length];
    for (int i=0; i<length; i++) {
        this->data[i] = array[i];
    }
}

CustomVector::CustomVector(const CustomVector &other) {
    // TODO: copia profunda del contenido de 'other' (incluida capacity).
    this->length = other.length;
    this->capacity = other.capacity;
    this->data = new int[other.capacity];
    for (int i=0; i < this->length; i++) {
        this->data[i] = other.data[i];
    }
}

CustomVector &CustomVector::operator=(const CustomVector &other) {
    // TODO: liberar lo anterior y hacer una copia profunda de 'other'
    // (incluida capacity).
    delete[] this->data;
    this->length = other.length;
    this->capacity = other.capacity;
    this->data = new int[other.capacity];
    for (int i=0; i < this->length; i++) {
        this->data[i] = other.data[i];
    }
    return *this;
}

CustomVector::~CustomVector() {
    // TODO: liberar la memoria del vector.
    delete[] this->data;
}

int CustomVector::get_length() const {
    return this->length;
}

int &CustomVector::operator[](int i) {
    // TODO: devolver el elemento en la posición i.
    return this->data[i];
}

const int &CustomVector::operator[](int i) const {
    // TODO: devolver el elemento en la posición i.
    return this->data[i];
}

int CustomVector::max() const {
    // TODO: devolver el máximo del vector.
    int maximo = data[0];
    for(int i=0; i<this->length; i++){
        if(data[i] > maximo) {
            maximo = data[i];
        }
    }
    return maximo;
}

void CustomVector::map(int (*f)(int)) {
    // TODO: aplicar f a cada elemento. Si f es NULL, no hacer nada.
    if (f==nullptr) {
        return;
    }
    for (int i=0; i<this->length; i++) {
        data[i]=f(data[i]);
    }
}

void CustomVector::bubble_sort() {
    // TODO: ordenar el vector ascendentemente con bubble sort.
    for (int i=0; i<this->length - 1; i++) {
        for (int k=0; k<this->length - 1 - i ;k++) {
            if (data[k+1] < data[k]) {
                swap(&data[k+1], &data[k]);
            }
        }
    }
}

bool CustomVector::equal(const CustomVector &other) const {
    // TODO: determinar si los dos vectores son idénticamente iguales.
    if(this->length != other.length) {
        return false;
    }
    
    for (int i=0; i<this->length; i++){
        if(this->data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}

bool CustomVector::is_anagram(const CustomVector &other) const {
    // TODO: determinar si los dos vectores son anagramas.
    if (this->length != other.length) {
        return false;
    }

    bool *usado = new bool[other.length];
    for (int j = 0; j < other.length; j++) {
        usado[j] = false;
    }

    for (int i = 0; i < this->length; i++) {
        bool encontrado = false;
        for (int j = 0; j < other.length; j++) {
            if (!usado[j] && this->data[i] == other.data[j]) {
                usado[j] = true;
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            delete[] usado;
            return false;
        }
    }

    delete[] usado;
    return true;
}

int CustomVector::get_capacity() const {
    return this->capacity;
}

void CustomVector::push_back(int value) {
    // TODO: agregar 'value' al final del vector, creciendo la capacity
    // si hace falta.
    if (this->capacity > this->length){
        data[length] = value;
        this->length++;
    }
    else {
        int nueva_capacity = this->capacity + 1;
        int *nuevo_data = new int[nueva_capacity];

        for (int i = 0; i < this->length; i++) {
            nuevo_data[i] = this->data[i];
        }

        delete[] this->data;

        this->data = nuevo_data;
        this->capacity = nueva_capacity;

        this->data[this->length] = value;
        this->length++;
    }
}

void CustomVector::remove() {
    // TODO: quitar el último elemento del vector. Si está vacío, no
    // hacer nada.
    if(this->length == 0) {
        return;
    }
    this->length --;
}

/* ---------------------------------------------------------------
 * Parte 3: reserva de UN solo objeto (new / delete escalar).
 * --------------------------------------------------------------- */

CustomVector *war_winner(const CustomVector &a, const CustomVector &b) {
    // TODO: devolver un CustomVector nuevo con el ganador de cada
    // ronda (el máximo entre a[i] y b[i]).
    int rounds;
    if (a.get_length() < b.get_length()) {
        rounds = a.get_length();
    }  
    else {
        rounds = b.get_length();
    }    
    CustomVector* resultado = new CustomVector(rounds);
    for(int i=0; i<rounds; i++){
        if(a[i]>b[i]){
            (*resultado)[i] = a[i];
        }
        else{
            (*resultado)[i] = b[i];
        }
    }
    return resultado;
}

void destroy_vector(CustomVector *vector) {
    // TODO: liberar vector con delete (versión escalar, sin []).
    delete vector;
}

CustomVector *tournament_champion(CustomVector **decks, int num_decks) {
    // TODO: enfrentar decks[0] contra cada mazo siguiente con
    // war_winner, liberando el campeón anterior y el mazo que
    // perdió en cada pelea, y devolver el campeón final.
    CustomVector* campeon = decks[0];
    for(int i=1; i<num_decks; i++){
        CustomVector *nuevo_campeon = war_winner(*campeon, *decks[i]);
        delete campeon;
        delete decks[i];
        campeon = nuevo_campeon;
    }
    delete[] decks;
    return campeon;
}
