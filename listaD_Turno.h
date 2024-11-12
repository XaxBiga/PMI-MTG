#ifndef LISTAD_TURNO_H_INCLUDED
#define LISTAD_TURNO_H_INCLUDED

#include "Turno.h"

typedef struct Nodo{
    TDA_Turno data ;
    struct Nodo *next;
} Nodo;

typedef struct{
    Nodo *acc;
    Nodo *aux;
    Nodo *cur;
} List_of_Turno;

void init_l (List_of_Turno *l){
    (*l).acc = NULL;
    (*l).aux = NULL;
    (*l).cur = NULL;
}

int isempty (List_of_Turno l){
   return (l.acc == NULL);
}
int isfull (List_of_Turno l){
    Nodo *nuevonodo = (Nodo *)malloc(sizeof(Nodo));
    if (nuevonodo == NULL) return 1;
    free(nuevonodo);
    return 0;
}
TDA_Turno Copyy(List_of_Turno l){
    return l.cur->data;
}

void forwards (List_of_Turno *l){
    (*l).aux=(*l).cur;
    (*l).cur=(*l).cur -> next;
}
void resert (List_of_Turno *l){
    l->aux = l->cur = l->acc;
}
void inserte (List_of_Turno *l, TDA_Turno NuevoEstudiante){
    Nodo *NuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    NuevoNodo ->data = NuevoEstudiante;
    if (l->acc == l->cur){
        NuevoNodo->next = l->acc;
        l->acc = l->aux=l->cur = NuevoNodo;
    }else{
        NuevoNodo->next = l->cur;
        l->aux->next=l->cur=NuevoNodo;
    }
}
void supress(List_of_Turno *l){
    if (l->acc == l->cur){
        l->acc = l->cur = l->cur->next;
        free((void*)l->cur);
        l->aux=l->cur= l->acc;
    }else{
        Nodo *eliminarr =l->cur;
        l->cur = l->cur->next;
        free(eliminarr);
        l->aux->next=l->cur;
    }
}
int isOos(List_of_Turno l) {
    return l.cur == NULL;
}

#endif // LISTAD_TURNO_H_INCLUDED
