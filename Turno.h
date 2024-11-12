#ifndef TURNO_H_INCLUDED
#define TURNO_H_INCLUDED
#include <string.h>
#include <stdlib.h>

typedef struct {
    int FormaDePago[4];
    float Total;
} Turno_Pago;

typedef struct {
    int TipoTratamiento[10];
    float Precio_Tratamiento[10];
} Turno_Tratamiento;

typedef struct {
    int Dia;
    int Mes;
    int Anio;
    int Hora;
} Fecha_Turno;

typedef struct {
    int Idturno;
    char Nombre[21];
    int IdCliente;
    int Realizado;
    Turno_Tratamiento Tratamientos;
    Fecha_Turno Fechas_of_Turno;
    Turno_Pago Pago_of_Turno;
} TDA_Turno;

void set_Idturno(TDA_Turno *t, int IdTurnoNuevo) {
    (*t).Idturno = IdTurnoNuevo;
}

void set_Nombre(TDA_Turno *t, const char NombreNuevo[]) {
    strncpy(t->Nombre, NombreNuevo, 20);
    t->Nombre[20] = '\0'; // Asegura que siempre haya terminador nulo
}

void set_IdClientes(TDA_Turno *t, int IdClienteNuevos) {
    (*t).IdCliente = IdClienteNuevos;
}

void set_Tratamiento(TDA_Turno *t,int tratamientosSeleccionados) {
    for (int i = 0; i <= 10; i++) {
        if (tratamientosSeleccionados == i) {
            t->Tratamientos.TipoTratamiento[tratamientosSeleccionados - 1] = tratamientosSeleccionados;
        }
    }
}
void set_PrecioTratamiento(TDA_Turno *t, int index, float PrecioTratamientoNuevo) {
    if (index >= 0 && index <= 10) {
        (*t).Tratamientos.Precio_Tratamiento[index] = PrecioTratamientoNuevo;
    }
}

void set_FormaDePago(TDA_Turno *t, int TipoDepagoNuevo) {
    for (int i=0; i<=4; i++){
        if (TipoDepagoNuevo == i){
            t->Pago_of_Turno.FormaDePago[TipoDepagoNuevo -1] = TipoDepagoNuevo;
        }
    }
}

void set_TotalDepago(TDA_Turno *t,float TotalNuevo) {
    (*t).Pago_of_Turno.Total = TotalNuevo;
}

void set_FechaTurno(TDA_Turno *t, int DiaNuevo, int MesNuevo, int AnioNuevo, int HoraNuevo) {
    (*t).Fechas_of_Turno.Dia = DiaNuevo;
    (*t).Fechas_of_Turno.Mes = MesNuevo;
    (*t).Fechas_of_Turno.Anio = AnioNuevo;
    (*t).Fechas_of_Turno.Hora = HoraNuevo;
}

void set_Realizado(TDA_Turno *t, int RealizadoNuevo) {
    (*t).Realizado = RealizadoNuevo;
}

char *get_Nombre(TDA_Turno t) {
    char *p = malloc(strlen(t.Nombre) + 1);

    if (!p) {
        exit(1);
    }

    strcpy(p, t.Nombre);
    return p;
}

int get_IdTurno(TDA_Turno *t) {
    return (*t).Idturno;
}

int get_IdCliente(TDA_Turno *t) {
    return (*t).IdCliente;
}

int get_Tratamiento(TDA_Turno *t, int index) {
    if (index >= 0 && index < 10){
        return (*t).Tratamientos.TipoTratamiento[index];
    }else {
        return 0;
    }
}
float get_precioTratamiento(TDA_Turno *t, int index) {
    if (index >= 0 && index < 10){
        return (*t).Tratamientos.Precio_Tratamiento[index];
    }else{
        return 0;
    }
}

int get_FormaDepago(TDA_Turno *t, int index) {
    if (index >= 0 && index < 4){
        return (*t).Pago_of_Turno.FormaDePago[index];
    }else{
        return 0;
    }
}

float get_Total(TDA_Turno *t) {
    return (*t).Pago_of_Turno.Total;
}
int get_realizado(TDA_Turno *t){
    return (*t).Realizado;
}
Fecha_Turno get_Fecha(TDA_Turno *t) {
    return (*t).Fechas_of_Turno;
}

#endif // TURNO_H_INCLUDED
