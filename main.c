#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "listaE_Cliente.h"
#include "Turno.h"
#include "listaD_Turno.h"
#include "Cliente.h"
void CargaDeUnTurno(List_of_Turno *ListaDeTurno, List_of_Cliente *ListaDeCliente);
void CargarTurnoClienteExistente(List_of_Turno *ListaDeTurno , int VerificacionDocumento, char NombreMain[]);
float ganancia (List_of_Turno *ListaDeTurno, int mescalculo, int i);
void PrepararTurno(TDA_Turno *NuevoTurno, int VerificacionDocumento, int CantidadTratamientoMain);
void CargarTurnoClienteYaEncontrado(List_of_Turno *ListaDeTurno,List_of_Cliente listaDeCliente, int VerificacionDocumento,  char NombreMain[]);
float descuento (TDA_Turno *t, TDA_Cliente c, float total);
void carga_de_un_cliente_porDni(List_of_Cliente *ListaCliente, List_of_Turno *ListaDeTurno ,int DNI);
void Buscar_si_cargarTurno(List_of_Turno *ListaDeTurno, List_of_Cliente *ListaDeCliente, int id);
int busca_turno_idcliente (List_of_Turno *l,int id);
void MostrarTodosLosClienteNombre(List_of_Cliente *ListaDeCliente, char NombreBuscar[]);
void MostrarTodosLosClientesDeLaLista(List_of_Cliente *ListaDeCliente);
void MostrarTodosLosTurnosFecha(List_of_Turno listaD_Turno , int Mes);
void ModificarRalizadoTurno(List_of_Turno *ListaTurno,List_of_Cliente ListaCliente, int idClienteModificar);
void mostrar_turno_cliente(List_of_Turno t, List_of_Cliente c, char clbuscar[]);
void ModificarLaCantidadTratamiento(List_of_Cliente *ListaDeCliente, int idClienteModificar);
void busca_turnos (List_of_Turno ListaDeTurno,List_of_Cliente listaDeCliente, int idbuscar);
void mostrar_todos_los_turnos (List_of_Turno l);
void modificar_pago (List_of_Turno *l,List_of_Cliente c,int id);
void muestraTurnoDeNorealizados(List_of_Turno listaDeTurno);
void Eliminar_Cliente_sm_Turno (List_of_Cliente *listaCliente, int idCLienteEliminar);
void mostrar_turno_por_tratamiento (List_of_Turno *l,int tipo);
void precargarClientesDesdeArchivo(List_of_Cliente *ListaDeCliente);
void carga_de_un_cliente(List_of_Cliente *listaDeClientes) ;
void GuardarTurnoCancelado(TDA_Turno TurnoAcancelar);
void cancelarTurnoPorIdCliente (List_of_Turno *ListaDeTurno,int idbuscar);
int main (){

    int opcion,Mes,IdCliente,Tipo,mescalculo;
    char NombreClienteMB[21];
    int idbuscar;
    List_of_Turno ListaDeTurno;
    List_of_Cliente ListaDeCliente;
    init_l(&ListaDeTurno);
    init_lC(&ListaDeCliente);

    do{
        printf("#### Bienvenidos al menu ####\n");
        printf("Ya puede operar esta app, ingrese la operacion a realizar\n");
        printf("<1>. Cargar un Turno.\n");
        printf("<2>. Buscar Turno por ID de Cliente.\n");
        printf("<3>. Mostrar todos los turnos de una fecha determinada.\n");
        printf("<4>. Buscar y mostrar los turnos por nombre de cliente.\n");
        printf("<5>. Mostrar los turnos solicitados por un cliente mediante ID.\n");
        printf("<6>. Calcular la ganancia mensual mediante el mes.\n");
        printf("<7>. Mostrar Todos los turnos almacenados en la lista.\n");
        printf("<8>. Modificar la cantidad de tratamientos del cliente.\n");
        printf("<9>. Modificar la forma de pago de un turno mediante su ID Cliente.\n");
        printf("<10>. Cancelar turno por ID y guardar una lista de eliminados.\n");
        printf("<11>. Almacenar en un archivo los datos de los turnos mediante cualquier forma de pago.\n");
        printf("<12>. Registrar un cliente.\n");
        printf("<13>. Mostrar turnos con un tratamiento determinado.\n");
        printf("<14>. Precarga automatica.\n");
        printf("<15>. Mostrar todos los clientes de la lista.\n");
        printf("<16>. Eliminar cliente segun su ID. No modifica el turno.\n");
        printf("<17>. Modificar el turno a Confirmado por ID Cliente.\n");
        printf("<18>. Mostrar los turnos no realizados.\n");
        printf("<19>.Salir\n");
        scanf ("%d",&opcion);
        switch (opcion) {
            case 1:
                resetC(&ListaDeCliente);
                resert(&ListaDeTurno);
                CargaDeUnTurno(&ListaDeTurno, &ListaDeCliente);
                forwardsC(&ListaDeCliente);
            break;
            case 2:
                printf ("ingrese un DNI para averiguar su estado del turno\n");
                scanf ("%d",&idbuscar);
                int valor = busca_turno_idcliente(&ListaDeTurno,idbuscar );
                if (valor == 1){
                    printf("Cliente encontrado con turno\n");
                }else {
                    printf ("Cliente sin Turno\n");
                }
            break;
            case 3:
                printf ("Para mostrarle todos los turnos mediante una fecha, el MES a ingresar: ");
                scanf ("%d",&Mes);
                MostrarTodosLosTurnosFecha(ListaDeTurno , Mes);
            break;
            case 4:
                printf ("ingrese el nombre que quiere encontrar su tratamiento\n");
                scanf ("%s", NombreClienteMB);
                mostrar_turno_cliente(ListaDeTurno ,ListaDeCliente, NombreClienteMB);
            break;
            case 5:
                printf("ingrese id del cliente a buscar: \n");
                scanf("%d", &idbuscar);
                busca_turnos (ListaDeTurno, ListaDeCliente ,idbuscar);
            break;
            case 6:
                printf ("ingrese mes al que quiera sacarle la ganancia \n");
                scanf ("%d",&mescalculo);
                float gananxia = ganancia (&ListaDeTurno,mescalculo,0);
                printf ("La ganancia mensual del mes %d es de : %f \n",mescalculo,gananxia);
            break;
            case 7:
                printf ("Mostrando los turnos: \n");
                mostrar_todos_los_turnos(ListaDeTurno);
            break;
            case 8:
                if (isemptyC(ListaDeCliente)){
                    printf ("la lista de cliente esta vacia\n");
                    return 0;
                }
                resetC(&ListaDeCliente);
                printf ("ingrese el DNI del cliente a modificar\n");
                scanf ("%d", &idbuscar);
                //ModificarLaCantidadTratamiento(&ListaDeCliente, idbuscar);
            break;
            case 9:
                printf ("Ingrese porfavor el DNI para buscar para la modificacion de pago");
                scanf ("%d", &idbuscar);
                modificar_pago (&ListaDeTurno,ListaDeCliente ,idbuscar);
            break;
            case 10:
                printf ("Ingrese por favol el DNI para eliminarlo: ");
                scanf ("%d",&idbuscar);
                cancelarTurnoPorIdCliente (&ListaDeTurno,idbuscar);
            break;
            case 11:

            break;
            case 12:
                carga_de_un_cliente(&ListaDeCliente);
            break;
            case 13:
                printf ("ingrese el Tipo de tratamiento que quiere buscar en la lista\n");
                scanf ("%d",&Tipo);
                mostrar_turno_por_tratamiento(&ListaDeTurno,Tipo);
            break;
            case 14:
                precargarClientesDesdeArchivo(&ListaDeCliente);
            break;
            case 15:
                resetC(&ListaDeCliente);
                MostrarTodosLosClientesDeLaLista(&ListaDeCliente);
            break;
            case 16:
                resetC(&ListaDeCliente);
                printf ("ingrese el DNI del cliente que quiere eliminar\n");
                scanf ("%d",&idbuscar);
                Eliminar_Cliente_sm_Turno (&ListaDeCliente , idbuscar);
            break;
            case 17:
                printf ("ingrese el DNI: ");
                scanf ("%d",&IdCliente);
                ModificarRalizadoTurno(&ListaDeTurno, ListaDeCliente,IdCliente);
            break;
            case 18:
                muestraTurnoDeNorealizados(ListaDeTurno);
            break;
            case 19:
                printf("Saliendo del programa...\n");
            break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
            break;
        }
    }while (opcion != 19);
    return 0;
}
/*void SeteoNombre(List_of_Cliente *ListaDeCliente, List_of_Turno *ListaDeTurno ,int VerificacionDocumento){
    TDA_Cliente SetnombreCLiente;
    TDA_Turno SetnombreTUrno;
    char nombrefuncion[31];
    while (!isOosC(*ListaDeCliente)){
        if (get_IdCliente(ListaDeCliente) == VerificacionDocumento){
            printf("Ingrese el Nombre: ");
            scanf ("%s", nombrefuncion);
            set_Nombre(ListaDeCliente, nombrefuncion);
            set_Nombres(ListaDeTurno, nombrefuncion);
        }
    }
}*/
void CargaDeUnTurno(List_of_Turno *ListaDeTurno, List_of_Cliente *ListaDeCliente) {
    int VerificacionDocumento;
    char NombreMain[31];
    char ApellidoMain[31];
    int CantidadTratamientoMain = 0;
    int clienteEncontrado = 0;
    TDA_Cliente NuevoCliente;
    TDA_Turno NuevoTurno;
    if (isfullC(*ListaDeCliente)) {
        printf("La lista de clientes está llena.\n");
        return;
    }

    printf("Ingrese por favor su Numero de documento para verificar si es o no Cliente: ");
    scanf("%d", &VerificacionDocumento);
    resetC(ListaDeCliente);

    while(!isOosC(*ListaDeCliente)){
        if (get_IdClientes(&NuevoCliente)== VerificacionDocumento){
            clienteEncontrado = 1;
            break;
        }
        forwardsC(ListaDeCliente);
    }

    if (!clienteEncontrado) {
        printf("Usted no es cliente, vamos a proceder a la carga de cliente.\n");
        printf("__________________________________________________\n");

        set_IdCliente(&NuevoCliente, VerificacionDocumento);

        printf("Ingrese el Nombre: ");
        scanf("%s", NombreMain);
        set_Nombres(&NuevoCliente, NombreMain);

        printf("Ingrese el Apellido: ");
        scanf("%s", ApellidoMain);
        set_Apellido(&NuevoCliente, ApellidoMain);

        printf("Ingrese la cantidad de tratamientos: ");
        do {
            scanf("%d", &CantidadTratamientoMain);
            if (CantidadTratamientoMain > 4) {
                printf("Error: No se pueden realizar mas de 4 tratamientos en un turno.\nIngrese una cantidad valida (1-4): ");
            }
        } while (CantidadTratamientoMain < 1 || CantidadTratamientoMain > 4);
        set_CantidadTratamientoss(&NuevoCliente, CantidadTratamientoMain);
        set_Nivel(&NuevoCliente);

        inserteC(ListaDeCliente, NuevoCliente);
        printf("Cliente agregado con exito.\n");
    float total = 0;
    char confirmacion;
    int FormaDePagoTurno;
    int DiaTurno, MesTurno, AnioTurno, HoraTurno;

    set_IdClientes(&NuevoTurno, VerificacionDocumento);
    set_Nombre(&NuevoTurno, NombreMain);

    // Cargar tratamientos y precios
    int TipoDeTratamiento;
    float precios[] = {7500.0, 15000.0, 7000.0, 24500.0, 12500.0, 8000.0, 11000.0, 9000.0, 9000.0, 20000.0};

    for (int i = 0; i < 10; i++) {
        NuevoTurno.Tratamientos.Precio_Tratamiento[i] = precios[i];
       NuevoTurno.Tratamientos.TipoTratamiento [i]= 0;
    }
    for (int i=0 ; i<=4; i++){
        NuevoTurno.Pago_of_Turno.FormaDePago[i] = 0;
    }
    for (int i = 0; i < CantidadTratamientoMain; i++) {
    do {
        printf("Ingrese el tipo de tratamiento (1-10): \n");
            printf("Tratamiento 1: Depilación Facial: $7.500. (incluye en cejas y labio superior).\n");
            printf("Tratamiento 2: Limpieza Facial Profunda: $15.000.\n");
            printf("Tratamiento 3: Perfilado de cejas: $7.000.\n");
            printf("Tratamiento 4: Tratamiento Antiarrugas: $24.500.\n");
            printf("Tratamiento 5: Tratamiento Antiacné: $12.500.\n");
            printf("Tratamiento 6: Manicura con esmaltado permanente: $8.000.\n");
            printf("Tratamiento 7: Pedicura Spa para pies: $11.000.\n");
            printf("Tratamiento 8: Tratamiento de hidratación para pies: $9.000.\n");
            printf("Tratamiento 9: Corte de pelo común: $9.000.\n");
            printf("Tratamiento 10: Corte de pelo completo (incluye lavado y bomba de keratina): $20.000.\n");
        if (scanf("%d", &TipoDeTratamiento) != 1) {
            printf("Entrada inválida. Debe ingresar un número.\n");
            while(getchar() != '\n');
            continue;
        }

        if (TipoDeTratamiento < 1 || TipoDeTratamiento > 10) {
            printf("El tipo de tratamiento debe estar entre 1 y 10.\n");
            continue;  // Volver a pedir la entrada
        }
        set_Tratamiento(&NuevoTurno, TipoDeTratamiento);
        set_PrecioTratamiento(&NuevoTurno, i, precios[TipoDeTratamiento - 1]);

    } while (TipoDeTratamiento < 1 || TipoDeTratamiento > 10);
}


    do {
        printf("Ingrese la forma de pago que necesita: \n");
        printf("<1>. Qr.\n<2>. Debito.\n<3>. Credito.\n<4>. Efectivo.\n");
        scanf("%d", &FormaDePagoTurno);
    } while (FormaDePagoTurno < 1 || FormaDePagoTurno > 4);

    do {
        printf("Ingrese la fecha del turno (01/11/2024 - 31/12/2024 entre 9:00 y 20:00):\n");
        printf("Dia: ");
        scanf("%d", &DiaTurno);
        printf("Mes: ");
        scanf("%d", &MesTurno);
        printf("Anio: ");
        scanf("%d", &AnioTurno);
        printf("Hora: ");
        scanf("%d", &HoraTurno);
    } while ((MesTurno < 11 || MesTurno > 12) || AnioTurno != 2024 ||
             (MesTurno == 11 && DiaTurno < 1) || (MesTurno == 12 && DiaTurno > 31) ||
             HoraTurno < 9 || HoraTurno > 20);

    total = 0;
    for (int i = 0; i < CantidadTratamientoMain; i++) {
        total += get_precioTratamiento(&NuevoTurno, i);
    }

    set_FormaDePago(&NuevoTurno, FormaDePagoTurno );

    set_FechaTurno(&NuevoTurno, DiaTurno, MesTurno, AnioTurno, HoraTurno);
    set_Realizado(&NuevoTurno, 0);
    set_TotalDepago(&NuevoTurno, total);

    switch (get_FormaDepago(&NuevoTurno, FormaDePagoTurno - 1)) {
        case 1: printf ("La forma de pago es: Qr\n"); break;
        case 2: printf ("La forma de pago es: Debito\n"); break;
        case 3: printf ("La forma de pago es: Credito\n"); break;
        case 4: printf ("La forma de pago es: Efectivo\n"); break;
    }
    printf("La fecha del turno es: %d/%d/%d a las %d hs\n", NuevoTurno.Fechas_of_Turno.Dia, NuevoTurno.Fechas_of_Turno.Mes, NuevoTurno.Fechas_of_Turno.Anio, NuevoTurno.Fechas_of_Turno.Hora);
    printf("============================\n");
    printf("El total SIN Descuento es: %.2f\n", get_Total(&NuevoTurno));
    switch (get_Nivel(&NuevoCliente)){
    case 0:
        printf("============================\n");
        printf("el cliente no tiene descuentos por ser nivel 0 \n\n");
        printf("============================\n");
        break;
    case 1:
        printf("============================\n");
        printf("El total con Descuento por nivel %d de 5 porciento : %.2f\n", get_Nivel(&NuevoCliente),descuento(&NuevoTurno,NuevoCliente,total));
        printf("============================\n");
        break;
    case 2:
        printf("============================\n");
        printf("El total con Descuento por nivel %d de 10 porciento : %.2f\n", get_Nivel(&NuevoCliente),descuento(&NuevoTurno,NuevoCliente,total));
        printf("============================\n");
        break;
    case 3:
        printf("============================\n ");
        printf("El total con Descuento por nivel %d de 15 porciento : %.2f\n", get_Nivel(&NuevoCliente),descuento(&NuevoTurno,NuevoCliente,total));
        printf("============================\n");
        break;
    }
    do {
        printf("Para la confirmacion: (S/n) ");
        scanf(" %c", &confirmacion);
    } while (confirmacion != 'S' && confirmacion != 's' && confirmacion != 'N' && confirmacion != 'n');

    if (confirmacion == 'S' || confirmacion == 's') {
        inserte(ListaDeTurno, NuevoTurno);
        printf("Guardado exitoso\n");
    } else {
        printf("Turno Cancelado\n");
    }
    }else if (clienteEncontrado == 1){
        CargarTurnoClienteYaEncontrado(ListaDeTurno, *ListaDeCliente , VerificacionDocumento, NombreMain);
    }

}
void CargarTurnoClienteYaEncontrado(List_of_Turno *ListaDeTurno,List_of_Cliente listaCliente, int VerificacionDocumento, char NombreMain[]) {
    TDA_Turno NuevoTurno;
    TDA_Cliente NuevoCliente;
    int CantidadTratamientoMain;
    int TipoDeTratamiento;
    float precios[] = {7500.0, 15000.0, 7000.0, 24500.0, 12500.0, 8000.0, 11000.0, 9000.0, 9000.0, 20000.0};
    float total = 0;
    int FormaDePagoTurno;
    int DiaTurno, MesTurno, AnioTurno, HoraTurno;
    char confirmacion;

    printf("Cliente encontrado: %s\n", NombreMain);

    // Inicializar el turno para el cliente encontrado
    set_IdClientes(&NuevoTurno, VerificacionDocumento);
    set_Nombre(&NuevoTurno, NombreMain);

    printf("Ingrese la cantidad de tratamientos: ");
    do {
        scanf("%d", &CantidadTratamientoMain);
        if (CantidadTratamientoMain > 4) {
            printf("Error: No se pueden realizar más de 4 tratamientos en un turno.\nIngrese una cantidad válida (1-4): ");
        }
    } while (CantidadTratamientoMain < 1 || CantidadTratamientoMain > 4);

    for (int i = 0; i < 10; i++) {
        NuevoTurno.Tratamientos.Precio_Tratamiento[i] = precios[i];
        NuevoTurno.Tratamientos.TipoTratamiento[i] = 0;
    }

    for (int i = 0; i < CantidadTratamientoMain; i++) {
        do {
            printf("Ingrese el tipo de tratamiento (1-10): ");
            printf("Tratamiento 1: Depilación Facial: $7.500. (incluye en cejas y labio superior).\n");
            printf("Tratamiento 2: Limpieza Facial Profunda: $15.000.\n");
            printf("Tratamiento 3: Perfilado de cejas: $7.000.\n");
            printf("Tratamiento 4: Tratamiento Antiarrugas: $24.500.\n");
            printf("Tratamiento 5: Tratamiento Antiacné: $12.500.\n");
            printf("Tratamiento 6: Manicura con esmaltado permanente: $8.000.\n");
            printf("Tratamiento 7: Pedicura Spa para pies: $11.000.\n");
            printf("Tratamiento 8: Tratamiento de hidratación para pies: $9.000.\n");
            printf("Tratamiento 9: Corte de pelo común: $9.000.\n");
            printf("Tratamiento 10: Corte de pelo completo (incluye lavado y bomba de keratina): $20.000.\n");

            if (scanf("%d", &TipoDeTratamiento) != 1) {
                printf("Entrada inválida. Debe ingresar un número.\n");
                while(getchar() != '\n');  // Limpiar el buffer de entrada
                continue;
            }

            if (TipoDeTratamiento < 1 || TipoDeTratamiento > 10) {
                printf("El tipo de tratamiento debe estar entre 1 y 10.\n");
                continue;
            }

            set_Tratamiento(&NuevoTurno, TipoDeTratamiento);
            set_PrecioTratamiento(&NuevoTurno, i, precios[TipoDeTratamiento - 1]);

        } while (TipoDeTratamiento < 1 || TipoDeTratamiento > 10);
    }

    do {
        printf("Ingrese la forma de pago:\n<1>. QR\n<2>. Débito\n<3>. Crédito\n<4>. Efectivo\n");
        scanf("%d", &FormaDePagoTurno);
    } while (FormaDePagoTurno < 1 || FormaDePagoTurno > 4);

    do {
        printf("Ingrese la fecha del turno (01/11/2024 - 31/12/2024 entre 9:00 y 20:00):\n");
        printf("Día: ");
        scanf("%d", &DiaTurno);
        printf("Mes: ");
        scanf("%d", &MesTurno);
        printf("Año: ");
        scanf("%d", &AnioTurno);
        printf("Hora: ");
        scanf("%d", &HoraTurno);
    } while ((MesTurno < 11 || MesTurno > 12) || AnioTurno != 2024 ||
             (MesTurno == 11 && DiaTurno < 1) || (MesTurno == 12 && DiaTurno > 31) ||
             HoraTurno < 9 || HoraTurno > 20);

    for (int i = 0; i < CantidadTratamientoMain; i++) {
        total += get_precioTratamiento(&NuevoTurno, i);
    }

    set_FormaDePago(&NuevoTurno, FormaDePagoTurno - 1);
    set_FechaTurno(&NuevoTurno, DiaTurno, MesTurno, AnioTurno, HoraTurno);
    set_Realizado(&NuevoTurno, 0);
    set_TotalDepago(&NuevoTurno, total);

    printf("============================\n");
    printf("El total sin descuento es: %.2f\n", get_Total(&NuevoTurno));
    switch (get_Nivel(&NuevoCliente)){
    case 0:
        printf("============================\n");
        printf("el cliente no tiene descuentos por ser nivel 0 \n\n");
        printf("============================\n");
        break;
    case 1:
        printf("============================\n");
        printf("El total con Descuento por nivel %d de 5 porciento : %.2f\n", get_Nivel(&NuevoCliente),descuento(&NuevoTurno,NuevoCliente,total));
        printf("============================\n");
        break;
    case 2:
        printf("============================\n");
        printf("El total con Descuento por nivel %d de 10 porciento : %.2f\n", get_Nivel(&NuevoCliente),descuento(&NuevoTurno,NuevoCliente,total));
        printf("============================\n");
        break;
    case 3:
        printf("============================\n");
        printf("El total con Descuento por nivel %d de 15 porciento : %.2f\n", get_Nivel(&NuevoCliente),descuento(&NuevoTurno,NuevoCliente,total));
        printf("============================\n");
        break;
    }
    do {
        printf("Para la confirmación: (S/n) ");
        scanf(" %c", &confirmacion);
    } while (confirmacion != 'S' && confirmacion != 's' && confirmacion != 'N' && confirmacion != 'n');

    if (confirmacion == 'S' || confirmacion == 's') {
        inserte(ListaDeTurno, NuevoTurno);
        printf("Guardado exitoso\n");
    } else {
        printf("Turno cancelado\n");
    }
}

///Funcion "2" b).

int busca_turno_idcliente (List_of_Turno *l,int id){

if (isempty(*l)){
  printf ("la lista de cliente esta vacia\n ");
  return 0;
}

  resert(l);
  while (!isOos(*l)){
        TDA_Turno TurnoActual = Copyy(*l);
    if (TurnoActual.IdCliente == id && TurnoActual.Realizado == 0){
      return 1;
    }
    forwards (l);
  }
  return 0;
}
///Funci�n "3").
void MostrarTodosLosTurnosFecha(List_of_Turno ListaDeTurno, int Mes) {
    if (isempty(ListaDeTurno)) {
        printf("La lista está vacía.\n");
        return;
    }

    resert(&ListaDeTurno);
    int encontrado = 0;

    while (!isOos(ListaDeTurno)) {
        TDA_Turno TurnoActual = Copyy(ListaDeTurno);

        if (Mes == TurnoActual.Fechas_of_Turno.Mes) {
            encontrado = 1;
            printf("=======================================\n");
            printf("        Detalles del Turno Cliente      \n");
            printf("=======================================\n");

            printf("Nombre: %s\n", get_Nombre(TurnoActual));
            printf("DNI: %d\n", get_IdCliente(&TurnoActual));
            printf("Fecha del turno: %02d/%02d/%d a las %02d hs\n",
                   get_Fecha(&TurnoActual).Dia,get_Fecha(&TurnoActual).Mes, get_Fecha(&TurnoActual).Anio, get_Fecha(&TurnoActual).Hora);

            printf("=======================================\n");
            printf("         Detalles sobre el Turno        \n");
            printf("=======================================\n");

            // Imprimir tratamientos seleccionados
                int tratamientoEncontrado = 0;

                for (int i = 0; i < 10; i++) { 
                    int tratamiento = get_Tratamiento(&TurnoActual, i);
                    if (tratamiento != 0) {
                        tratamientoEncontrado = 1;
                        switch (tratamiento) {
                            case 1: 
                                printf("Tratamiento 1: Depilación Facial: $7.500. (incluye en cejas y labio superior).\n");
                                break;
                            case 2: 
                                printf("Tratamiento 2: Limpieza Facial Profunda: $15.000.\n");
                                break;
                            case 3: 
                                printf("Tratamiento 3: Perfilado de cejas: $7.000.\n");
                                break;
                            case 4: 
                                printf("Tratamiento 4: Tratamiento Antiarrugas: $24.500.\n");
                                break;
                            case 5: 
                                printf("Tratamiento 5: Tratamiento Antiacné: $12.500.\n");
                                break;
                            case 6: 
                                printf("Tratamiento 6: Manicura con esmaltado permanente: $8.000.\n");
                                break;
                            case 7: 
                                printf("Tratamiento 7: Pedicura Spa para pies: $11.000.\n");
                                break;
                            case 8: 
                                printf("Tratamiento 8: Tratamiento de hidratación para pies: $9.000.\n");
                                break;
                            case 9: 
                                printf("Tratamiento 9: Corte de pelo común: $9.000.\n");
                                break;
                            case 10: 
                                printf("Tratamiento 10: Corte de pelo completo (incluye lavado y bomba de keratina): $20.000.\n");
                                break;
                            default: 
                                printf("Tratamiento desconocido.\n");
                                break;
                        }
                    }
                }

                if (!tratamientoEncontrado) {
                    printf("No se han seleccionado tratamientos.\n");
                }

            // Imprimir forma de pago
            printf("Forma de pago:\n");
            int formaPagoEncontrada = 0;
            for (int i = 0; i <= 4; i++) {
                if (get_FormaDepago(&TurnoActual, i) != 0) {
                    formaPagoEncontrada = 1;
                    switch (get_FormaDepago(&TurnoActual, i)) {
                        case 1: printf("-Forma de pago: Qr\n"); break;
                        case 2: printf ("-Forma de pago: Debito\n"); break;
                        case 3: printf ("-Forma de pago: Credito\n"); break;
                        case 4: printf ("-Forma de pago: Efectivo\n"); break;
                    };
                }
            }
            if (!formaPagoEncontrada) {
                printf("No se ha seleccionado forma de pago.\n");
            }

            printf("Estado del Turno: %d\n", get_realizado(&TurnoActual));
            printf("=======================================\n");
        }
        forwards(&ListaDeTurno);
    }

    if (!encontrado) {
        printf("No se encontraron turnos para el mes especificado.\n");
    }
}
///Funci�n "4").
void mostrar_turno_cliente(List_of_Turno t, List_of_Cliente c, char clbuscar[]) {
    int cpagina = 3;
    int count = 0;

    if (isemptyC(c)) {
        printf("La lista de clientes está vacía\n");
        return;
    }

    resetC(&c);
    TDA_Cliente buscarCliente;
    int encontrado = 0;

    while (!isOosC(c)) {
        buscarCliente = copyyC(c);


        if (strcmp(get_Nombres(&buscarCliente), clbuscar) == 0) {
            encontrado = 1;
            int idcliente = get_IdClientes(&buscarCliente);


            resert(&t);
            while (!isOos(t)) {
                TDA_Turno buscaymuestra = Copyy(t);


                if (buscaymuestra.IdCliente == idcliente) {
                    printf("Cliente: %s\n", get_Nombres(&buscarCliente));
                    printf("IDCliente: %d\n", get_IdClientes(&buscarCliente));
                    printf("IDTurno: %d\n", get_IdTurno(&buscaymuestra));
                    printf("¿Está realizado?: %d\n", get_realizado(&buscaymuestra));
                    printf("\n");

                    count++;

                    if (count % cpagina == 0) {
                        printf("Presione Enter para continuar a la siguiente página...");
                        getchar();
                    }
                }
                forwards(&t);
            }
            break;
        }

        forwardsC(&c);
    }

    if (!encontrado) {
        printf("No se encontró el cliente con el nombre '%s'.\n", clbuscar);
    } else if (count == 0) {
        printf("No se encontraron turnos para el cliente '%s'.\n", clbuscar);
    }
}
///Funci�n "5").
void busca_turnos(List_of_Turno t,List_of_Cliente c ,int idbuscar){
 if (isemptyC(c)){
        printf ("No hay cliente cargados\n");
    return ;
 }
       TDA_Turno TurnoR = Copyy(t);
    if(TurnoR.IdCliente == idbuscar){
        printf("Cliente :%s \n",get_Nombre(TurnoR));
        /// Falta poner mas cosas del campo "Turno".
        printf ("total: %f\n",get_Total(&TurnoR));
            for (int i = 0; i < 4; i++) {
                int formaDePago = get_FormaDepago(&TurnoR, i);
                if (formaDePago != 0) {
                    printf("- Forma de pago %d\n", formaDePago);
                }
            }
   }else{
        forwards(&t);
        busca_turnos (t, c,idbuscar);
   }
}
/// Función "6"f).
float ganancia(List_of_Turno *l, int mesbuscado, int i) {
    if (isOos(*l)) {
        return 0;
    } else {
        TDA_Turno turnoAbuscar = Copyy(*l); // Revisar nombre correcto de Copy
        if (get_realizado(&turnoAbuscar) == 1 && get_Fecha(&turnoAbuscar).Mes == mesbuscado) {
            forwards(l);  // Mover el puntero hacia adelante
            return get_precioTratamiento(&turnoAbuscar, i) + ganancia(l, mesbuscado, i);
        } else {
            forwards(l);  // Mover el puntero hacia adelante
            return ganancia(l, mesbuscado, i);
        }
    }
}


///Funcion "7" g).
void mostrar_todos_los_turnos (List_of_Turno l){

  if (isempty(l) == 1){
   printf ("no hay ningun turno cargado \n");
  return;
  }

  resert(&l);
  while (!isOos(l)){
    TDA_Turno TurnoActual = Copyy(l);

            printf("=======================================\n");
            printf("       Detalles del Turno Cliente:      \n");
            printf("=======================================\n");
            printf("Nombre: %s\n", get_Nombre(TurnoActual));
            printf("DNI: %d\n", get_IdCliente(&TurnoActual));
            printf("Fecha del turno: %d/%d/%d a las %d hs\n",
                   get_Fecha(&TurnoActual).Dia,get_Fecha(&TurnoActual).Mes, get_Fecha(&TurnoActual).Anio, get_Fecha(&TurnoActual).Hora);

            printf("=======================================\n");
            printf("         Detalles sobre el Turno        \n");
            printf("=======================================\n");

            for (int i = 0; i <= 10; i++) {
                if ( get_Tratamiento(&TurnoActual, i) != 0) {
                    switch (get_Tratamiento(&TurnoActual, i)) {
                        case 1: 
                            printf("Tratamiento 1: Depilación Facial: $7.500. (incluye en cejas y labio superior).\n");
                            break;
                        case 2: 
                            printf("Tratamiento 2: Limpieza Facial Profunda: $15.000.\n");
                            break;
                        case 3: 
                            printf("Tratamiento 3: Perfilado de cejas: $7.000.\n");
                            break;
                        case 4: 
                            printf("Tratamiento 4: Tratamiento Antiarrugas: $24.500.\n");
                            break;
                        case 5: 
                            printf("Tratamiento 5: Tratamiento Antiacné: $12.500.\n");
                            break;
                        case 6: 
                            printf("Tratamiento 6: Manicura con esmaltado permanente: $8.000.\n");
                            break;
                        case 7: 
                            printf("Tratamiento 7: Pedicura Spa para pies: $11.000.\n");
                            break;
                        case 8: 
                            printf("Tratamiento 8: Tratamiento de hidratación para pies: $9.000.\n");
                            break;
                        case 9: 
                            printf("Tratamiento 9: Corte de pelo común: $9.000.\n");
                            break;
                        case 10: 
                            printf("Tratamiento 10: Corte de pelo completo (incluye lavado y bomba de keratina): $20.000.\n");
                            break;
                    };
                }
            }

            for (int i = 0; i <= 4; i++) {
                if (get_FormaDepago(&TurnoActual , i) != 0) {
                    switch (get_FormaDepago(&TurnoActual, i)) {
                        case 1: printf("-Forma de pago: Qr\n"); break;
                        case 2: printf ("-Forma de pago: Debito\n"); break;
                        case 3: printf ("-Forma de pago: Credito\n"); break;
                        case 4: printf ("-Forma de pago: Efectivo\n"); break;
                    };
                }
            }

            printf("Estado del Turno: ");
            if (get_realizado(&TurnoActual) == 1) {
                printf("Realizado\n");
            } else {
                printf("No Realizado\n");
            }
            printf ("El total es: %2.f\n",get_Total(&TurnoActual));

        printf ("---------------------------------\n");
        forwards(&l);
           }


      }
/// Funcion "8"H).
void ModificarLaCantidadTratamiento(List_of_Cliente *ListaDeCliente,int ModCantTratamiento){
    if (isemptyC(*ListaDeCliente)){
         printf ("la lista de cliente esta vacia\n");
       return ;
    }
    char confirmacion;
    int CantidadTratamientoNuevo;
            TDA_Cliente ClienteAux;
            while (!isOosC(*ListaDeCliente)) {
                ClienteAux = copyyC(*ListaDeCliente);

                if (get_IdClientes(&ClienteAux) == ModCantTratamiento) {

                    do {
                        printf("¿Esta seguro que quiere realizar la modificacion de cantidad de tratamientos? (S/n): ");
                        scanf(" %c", &confirmacion);
                    } while (confirmacion != 'S' && confirmacion != 's' &&
                            confirmacion != 'N' && confirmacion != 'n');

                    if (confirmacion == 'S' || confirmacion == 's') {
                        printf("Ingrese la cantidad de tratamientos que quiere modificar: ");
                        scanf("%d", &CantidadTratamientoNuevo);
                        set_CantidadTratamientoss(&ClienteAux, CantidadTratamientoNuevo);
                        set_Nivel(&ClienteAux);

                        supressC(ListaDeCliente);
                        inserteC(ListaDeCliente, ClienteAux);
                        printf("Modificacion exitosa\n");
                        break;
                    } else {
                        printf("Se nego la realizacion de la modificacion\n");
                        break;
                    }
                }

                forwardsC(ListaDeCliente);
            }
    }
/// Función "9"I).
void modificar_pago(List_of_Turno *l,List_of_Cliente c, int id) {
    int nuevopago;
    resert(l);
    if (isemptyC(c)){
        printf ("No hay cliente registrado\n");
    }
    if (isempty(*l)){
        printf ("La lista de turno esta vacia\n");
    }
        TDA_Turno TurnoAux;

    while (!isOos(*l)) {
        TurnoAux = Copyy(*l);
        //Inicializar el TDA turno (inicializar con 0 menos la forma de pago que a elegido el usuario ).
        for (int i=0;i<=4;i++){
            TurnoAux.Pago_of_Turno.FormaDePago[i] = 0;
        }
        if (busca_turno_idcliente(l,id) == 1) {
            do {
                printf("¿De que forma quiere pagar?\n");
                printf("<1>. Qr\n");
                printf("<2>. Débito\n");
                printf("<3>. Crédito\n");
                printf("<4>. Efectivo\n");
                scanf("%d", &nuevopago);
            } while (nuevopago < 1 || nuevopago > 4);
            set_FormaDePago(&TurnoAux, nuevopago-1);
            supress(l);
            inserte(l, TurnoAux);
            printf("Forma de pago modificada con exito.\n");
            break;
        }
        forwards(l);
    }
}
///Funcion "10"J).
void cancelarTurnoPorIdCliente (List_of_Turno *ListaTurno, int idClienteCancelar){
    if (isOos(*ListaTurno)){
        printf ("La lista con ese turno esta vacia\n");
        return;
    }
    resert (ListaTurno);
    while(!isOos(*ListaTurno)){
        TDA_Turno TurnoAcancelar = Copyy(*ListaTurno);
        if (get_IdCliente(&TurnoAcancelar) == idClienteCancelar){
            GuardarTurnoCancelado(TurnoAcancelar);
            supress(ListaTurno);
            printf("Turno del cliente con ID %d ha sido cancelado y eliminado.\n", idClienteCancelar);
            return;
        }
        forwards(ListaTurno);
    }
printf("No se encontró ningún turno para el cliente con ID %d.\n", idClienteCancelar);
}
//case 102b).
void GuardarTurnoCancelado(TDA_Turno TurnoAcancelar){
    FILE *Archivo = fopen ("Turno_Cancelado.txt", "a");
    if(Archivo == NULL){
        printf ("no se encontro cliente con ese Id\n");
        return;
    }
    fprintf (Archivo, "Turno Cancelado\n");
    fprintf (Archivo, "Nombre del cliente: %s\n",get_Nombre(TurnoAcancelar));
    fprintf (Archivo, "El DNI del Cliente: %d\n",get_IdCliente(&TurnoAcancelar));
    fprintf (Archivo, "El id Turno es: %d\n", get_IdTurno(&TurnoAcancelar));
    fprintf (Archivo, "El Total de los tratamientos: %f\n",get_Total(&TurnoAcancelar));


    fclose(Archivo);

}
/// Funcion "11"k).

///Funcion "12"L).
void carga_de_un_cliente(List_of_Cliente *listaDeClientes) {
    if (isfullC(*listaDeClientes)) {
        printf("La lista de clientes esta llena.\n");
        return;
    }

    int id_C;
    char nom[31];
    char ape[31];
    int cant_tra;
    printf("Ingrese su Numero de DNI para verificar si es cliente: ");
    scanf("%d", &id_C);

    int clienteEncontrado = 0;
    for (int i = 0; i < listaDeClientes->ultimo; i++) {
        if (listaDeClientes->data[i].IdClienteDNI == id_C) {
            clienteEncontrado = 1;
            break;
        }
    }

    if (clienteEncontrado) {
        printf("El cliente con DNI %d ya esta registrado.\n", id_C);
        return;
    }
    printf ("No se encontro como Clinete , cargando como cliente\n");
    TDA_Cliente nuevoCliente;
    set_IdCliente(&nuevoCliente, id_C);

    printf("Ingrese el Nombre: ");
    scanf("%s", nom);
    set_Nombres(&nuevoCliente, nom);

    printf("Ingrese el Apellido: ");
    scanf("%s", ape);
    set_Apellido(&nuevoCliente, ape);

    printf("Ingrese la cantidad de tratamientos: ");
    scanf("%d", &cant_tra);
    set_CantidadTratamientoss(&nuevoCliente, cant_tra);

    inserteC(listaDeClientes, nuevoCliente);
    printf("Cliente agregado correctamente.\n");
    forwardsC(listaDeClientes);
}
///Funcion "13" m).
void mostrar_turno_por_tratamiento (List_of_Turno *l,int tipo){
  resert (l);
  int cont = 0;

  if (isempty(*l) == 1){
   printf ("no hay ningun turno cargado \n");
  return;
  }


  while (!isOos(*l)){
    TDA_Turno t = Copyy(*l);
    for(int i=0;i<4;i++){
        int TipoTratamiento = get_Tratamiento(&t, i);
    if (TipoTratamiento != 0 && TipoTratamiento == tipo){
            cont++;
            printf("=======================================\n");
            printf("       Detalles del Turno :      \n");
            printf("=======================================\n");
            printf("Nombre: %s\n", get_Nombre(t));
            printf("DNI: %d\n", get_IdCliente(&t));
            printf("Fecha del turno: %d/%d/%d a las %d hs\n",
                   get_Fecha(&t).Dia,get_Fecha(&t).Mes, get_Fecha(&t).Anio, get_Fecha(&t).Hora);

            printf("=======================================\n");
            printf("         Detalles sobre el Turno        \n");
            printf("=======================================\n");

            printf("Tratamientos:\n");
            for (int i = 0; i < 10; i++) {
                int tratamiento = get_Tratamiento(&t, i);
                if (tratamiento != 0) {
                    printf("- Tratamiento %d\n", tratamiento);
                }
            }

            printf("Formas de Pago:\n");
            for (int i = 0; i < 4; i++) {
                int formaDePago = get_FormaDepago(&t, i);
                if (formaDePago != 0) {
                    printf("- Forma de pago %d\n", formaDePago);
                }
            }

            printf("Estado del Turno: ");
            if (get_realizado(&t) == 1) {
                printf("Realizado\n");
            } else {
                printf("No Realizado\n");
            }
            printf ("===========================================\n");
    }
    }
     forwards (l);
  }
  if (cont == 0){
    printf ("No hay turnos con este tratamiento \n\n");
  }


}
///Funcion "14"n).
void precargarClientesDesdeArchivo(List_of_Cliente *c) {
    int dni, cantTratamientos, nivel;
    char nom[31], ape[31];

    FILE *fp = fopen("Cliente.txt", "r");
    if (fp == NULL) {
        printf("Error al abrir el archivo.\n");
        exit(1);
    }

    TDA_Cliente cliente;

    // Bucle para leer cada cliente hasta el fin del archivo
    rewind(fp);
    while (fscanf(fp, "%d %s %s %d %d", &dni, nom, ape, &cantTratamientos, &nivel) == 5) {
        // Asignar valores al cliente usando setters
        set_IdCliente(&cliente, dni);
        set_Nombres(&cliente, nom);
        set_Apellido(&cliente, ape);
        set_CantidadTratamientoss(&cliente, cantTratamientos);
        set_Nivel(&cliente);

        if (!isfullC(*c)) {
            inserteC(c, cliente);
            forwardsC(c);
        } else {
            printf("La lista de clientes está llena. No se pueden agregar más clientes.\n");
            break;
        }
    }

    fclose(fp);
    printf("Clientes precargados desde el archivo 'Cliente.txt' exitosamente.\n");
}
///Funci�n "15").
void MostrarTodosLosClientesDeLaLista(List_of_Cliente *ListaDeCliente) {
    if (isemptyC(*ListaDeCliente)){
        printf ("La lista de cliente esta vacia\n");
    }
    TDA_Cliente clienteActual;

    while (!isOosC(*ListaDeCliente)) {
        clienteActual = copyyC(*ListaDeCliente);

        printf("DNI: %d\n", get_IdClientes(&clienteActual));
        printf("Nombre: %s\n", get_Nombres(&clienteActual));
        printf("Apellido: %s\n", get_Apellidos(&clienteActual));
        printf("Cantidad tratamientos: %d\n", get_CantidadTratamientoss(&clienteActual));
        printf("El Nivel es: %d\n", get_Nivel(&clienteActual));
        printf("__________________________________________________\n");

        forwardsC(ListaDeCliente);
    }
}
///Funcion "16" o).
void Eliminar_Cliente_sm_Turno (List_of_Cliente *listaCliente, int idClienteEliminar){
    if (isemptyC(*listaCliente)) {
        printf("La lista de clientes está vacía.\n");
        return;
    }
    resetC(listaCliente);
    while (!isOosC(*listaCliente)) {
        TDA_Cliente ClienteActual = copyyC(*listaCliente);
        if (ClienteActual.IdClienteDNI == idClienteEliminar) {
            supressC(listaCliente);
            break;
        } else {
            forwardsC(listaCliente);
        }
    }
}
/// 17)p)
void ModificarRalizadoTurno(List_of_Turno *ListaTurno, List_of_Cliente ListaCliente, int idClienteModificar) {
    char Confirmacion;
    if (isempty(*ListaTurno) == 1) {
        printf("La lista esta vacia\n");
        return;
    }
    if (isemptyC(ListaCliente)){
        printf ("no hay cliente registrado \n");
        return ;
    }
    resert(ListaTurno);

    while (!isOos(*ListaTurno)) {
        TDA_Turno TurnoModificar = Copyy(*ListaTurno);

        if (TurnoModificar.IdCliente == idClienteModificar) {
            do {
                printf("Esta seguro de confirmar la realizacion? S/n \n");
                scanf(" %c", &Confirmacion);
            } while (Confirmacion != 'S' && Confirmacion != 's' && Confirmacion != 'N' && Confirmacion != 'n');

            if (Confirmacion == 'S' || Confirmacion == 's') {
                TDA_Turno ModiRealizado = TurnoModificar;
                set_Realizado(&ModiRealizado, 1);
                supress (ListaTurno);
                inserte(ListaTurno, ModiRealizado);
                printf("Opcion cancelada y guardado con exito\n");
            }


        }
        forwards(ListaTurno);
    }
}

///Funcion 18 "q").
void muestraTurnoDeNorealizados(List_of_Turno listaDeTurno) {
    if (isempty(listaDeTurno)){
        printf ("la lista esta vacia");
        return ;
    }
    resert(&listaDeTurno);

    while (!isOos(listaDeTurno)){
        TDA_Turno TurnoMostrar = Copyy(listaDeTurno);
        if (get_realizado(&TurnoMostrar) == 0){
             printf ("El DNI: %d",get_IdCliente(&TurnoMostrar));
             printf("El nombre es: %s\n", get_Nombre(TurnoMostrar));
             for (int i=0;i<4;i++){
                    if (get_FormaDepago(&TurnoMostrar, i) !=0){
                        printf ("La forma de tratamiento es: %d\n",(get_FormaDepago(&TurnoMostrar, i) !=0));
                    }
             }
             printf ("El total del tratamiento es: %0.2f\n",get_Total(&TurnoMostrar));
             printf ("La fecha del turno es: %d/%d/%d a las: %d\n",get_Fecha(&TurnoMostrar).Dia, get_Fecha(&TurnoMostrar).Mes, get_Fecha(&TurnoMostrar).Anio, get_Fecha(&TurnoMostrar).Hora);
            printf ("==========================\n");
        }
        forwards(&listaDeTurno);
    }
}
float descuento (TDA_Turno *t, TDA_Cliente c, float total) {
    switch (c.Nivel) {
        case 1:
            total *= 0.95;
            set_TotalDepago(t, total);
            break;
        case 2:
            total *= 0.90;
            set_TotalDepago(t, total);
            break;
        case 3:
            total *= 0.85;
            set_TotalDepago(t, total);
            break;
        default: // Nivel 0, sin descuento
            set_TotalDepago(t, total);
            break;
    }
    return get_Total(t);
}
