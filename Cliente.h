#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED
#include "Turno.h"
#include <string.h>
#include <stdlib.h>


// Definición de la estructura del cliente
typedef struct {
    int IdClienteDNI;
    char Nombre[31];
    char Apellido[31];
    int CantidadTratamiento;
    int Nivel;
} TDA_Cliente;

void set_Nombres(TDA_Cliente *c,char NombreElegido[]) {
     strcpy((*c).Nombre, NombreElegido);
}

void set_Apellido(TDA_Cliente *c, char ApellidoElegido[]) {
    strcpy((*c).Apellido, ApellidoElegido);
}

void set_IdCliente(TDA_Cliente *c, int IdClienteNuevo) {
    c->IdClienteDNI = IdClienteNuevo;
}

void set_CantidadTratamientoss(TDA_Cliente *c, int CantidadDeTratamientosNuevos) {
    c->CantidadTratamiento = CantidadDeTratamientosNuevos;
}

void set_Nivel(TDA_Cliente *c) {
    int totalTratamientos = c->CantidadTratamiento;

    if (totalTratamientos == 0) {
        c->Nivel = 0;
    } else if (totalTratamientos >= 1 && totalTratamientos <= 4) {
        c->Nivel = 1;
    } else if (totalTratamientos >= 5 && totalTratamientos <= 10) {
        c->Nivel = 2;
    } else if (totalTratamientos > 10) {
        c->Nivel = 3;
    }
}
char *get_Nombres(TDA_Cliente *c) {
    return c->Nombre;
}

char *get_Apellidos(TDA_Cliente *c) {
    return c->Apellido;
}

int get_IdClientes(TDA_Cliente *c) {
    return c->IdClienteDNI;
}

int get_CantidadTratamientoss(TDA_Cliente *c) {
    return c->CantidadTratamiento;
}

int get_Nivel(TDA_Cliente *c) {
    return c->Nivel;
}


#endif // CLIENTE_H_INCLUDED
