#ifndef PLANIFICION_H
#define PLANIFICACION_H


#include "kernel.h"
#include <commons/collections/list.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <commons/log.h>
#include <commons/config.h>
#include <pthread.h>
#include <unistd.h>
#include "comunicacion.h"
#include "log_config.h"
#include "sockets.h"

// STRUCTS/ENUMS

typedef enum{
	FIFO,
	SRT
}t_algoritmo_planificacion;

//typedef struct {
//    uint32_t id_proceso ;
//    uint32_t tamanio_proceso ;
//    uint32_t valor_tabla_paginas ;
//    uint32_t program_counter;
//    float estimacion_rafaga ;
//    double tiempo_bloqueado ;
//    uint8_t suspendido;
//    char* estado ;
//    t_list* instrucciones ;
//}pcb ;


// SEMAFOROS

// sem_t planificacion;
// sem_t operacionesProcesos;
// sem_t planificacionPausada;
// sem_t sincroProcesPlanif;
// sem_t sincroProcesPlanif2;
// sem_t contadorNew;
// sem_t contadorReady;
// sem_t contadorExe;
// sem_t contadorProcesosEnMemoria;
// sem_t multiprogramacion;
// sem_t multiprocesamiento;
// sem_t contadorBlock;
// sem_t analizarSuspension;
// sem_t suspensionFinalizada;
// sem_t largoPlazo;
// sem_t contadorReadySuspended;
// sem_t medianoPlazo;
// pthread_mutex_t mutexNew;
// pthread_mutex_t mutexReady;
// pthread_mutex_t mutexBlock;
// pthread_mutex_t mutexExe;
// pthread_mutex_t mutexExit;
// pthread_mutex_t mutexBlockSuspended;
// pthread_mutex_t mutexReadySuspended;



// FUNCIONES

//void planificador_crearProcesos(int  ,char*,int  );
//void planificacionFIFO();
//void planificacionSRT();
//void agregarAReady(pcb* proceso);
//void agregarABlocked(pcb* proceso);
//void sacarDeBlocked(pcb* proceso);
//void hiloNew_Ready() ;
//pcb sacarDeNew();
//void agregarANewProceso(pcb proceso);
//void avisarAMemoria(pcb proceso)

pcb* obtenerSiguienteFIFO();
pcb* obtenerSiguienteSRT();
pcb* elegirElDeMenorEstimacion();
void asignarEstimacionesAProcesos();
float calculoEstimacionProceso(float);
t_algoritmo_planificacion obtener_algoritmo();



// LISTAS/COLAS

//t_lista* colaNew;
t_list* colaReady;
t_list* listaExec;
//t_list* listaBlocked;
//t_list* listaExit;
//t_list* listaBlockedSuspended;
//t_lista* colaReadySuspended;

#endif