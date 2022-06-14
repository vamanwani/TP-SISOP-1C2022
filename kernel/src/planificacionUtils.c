#include "planificacionUtils.h"

// CONFIG_ALGORITMO

//algoritmo obtener_algoritmo(){
//
// 	 algoritmo switcher;
// 	 char* algoritmo = obtener_de_config(config_valores_kernel, "ALGORITMO_PLANIFICACION");
//
// 	    //FIFO
// 	 if (strcmp(algoritmo,"FIFO") == 0)
// 	 {
// 		 switcher = FIFO;
// 	     log_info(logger, "El algoritmo de planificacion elegido es FIFO.");
// 	 }
//
// 	    //SFJ SIN DESALOJO
// 	 if (strcmp(algoritmo,"SRT") == 0)
// 	 {
// 		 switcher = SRT;
// 	     log_info(logger, "El algoritmo de planificacion elegido es SRT.");
// 	 }
// 	 return switcher;
//}

// AVISOS A MEMORIA - CONSOLA

// void avisarAModulo(int socket_fd,op_code codigo){
	// enviar_datos(socket_fd, &codigo, sizeof(op_code));

// }

// void enviar_pcb_a_memoria(pcb *pcb, int socket_memoria) {
// enviar_pcb(pcb,socket_memoria);
// }


//uint32_t obtener_entrada_tabla_de_pagina(int socket_fd) {
//	uint32_t numero;
//	t_paquete *paquete = crear_paquete_con_codigo_de_operacion(INICIALIZAR_ESTRUCTURAS);
//	enviar_paquete(paquete, socket_fd);
//	eliminar_paquete(paquete);
//
//	recibir_datos(socket_fd, &numero, sizeof(uint32_t));
//
//	return numero;
//}


// }


//void eliminar_pcb(pcb *pcb) {
//	list_destroy_and_destroy_elements(pcb->instrucciones, free);
//	free(pcb);
//}


// LISTAS

// void inicializar_listas(void){

// 	colaNew =list_create();
// 	colaReady = list_create();
// 	colaExec = list_create();
// 	colaBlocked = list_create();
//  colaSuspendedBlocked = list_create();
//  colaReadySuspended=list_create();
// 	colaExit = list_create();
// }


// SEMAFOROS

// void inicializar_semaforos(void){

// 	pthread_mutex_init(&mutexBlockSuspended, NULL);
// 	pthread_mutex_init(&mutexReadySuspended, NULL);
// 	pthread_mutex_init(&mutexNew, NULL);
// 	pthread_mutex_init(&mutexReady, NULL);
// 	pthread_mutex_init(&mutexBlocked, NULL);
// 	pthread_mutex_init(&mutexExec, NULL);
// 	pthread_mutex_init(&mutexExit, NULL);

// 	sem_init(&analizarSuspension, 0, 0);
// 	sem_init(&suspensionFinalizada, 0, 0);
// 	sem_init(&contadorNew, 0, 0); // Estado New
// 	sem_init(&contadorReady, 0, 0); // Estado Ready
// 	sem_init(&contadorExec, 0, 0); // Estado Exec
// 	sem_init(&contadorProcesosEnMemoria, 0, 0);	
// 	sem_init(&multiprogramacion, 0, gradoMultiprogramacion); // Memoria
// 	sem_init(&contadorBlocked, 0, 0);
// 	sem_init(&largoPlazo, 0, 1);
// 	sem_init(&contadorReadySuspended, 0, 0);
// 	sem_init(&medianoPlazo, 0, 1);
// }


//..................................... DESTRUCCIONES............................................................................ 



// SEMAFOROS

// void destruir_semaforos(void){

// 	pthread_mutex_destroy(&mutexNew);
// 	pthread_mutex_destroy(&mutexReady);
// 	pthread_mutex_destroy(&mutexBlocked);
// 	pthread_mutex_destroy(&mutexExec);
// 	pthread_mutex_destroy(&mutexExit);
// 	pthread_mutex_destroy(&mutexBlockSuspended);
// 	pthread_mutex_destroy(&mutexReadySuspended);

// 	sem_destroy(&contadorNew);
// 	sem_destroy(&contadorReady);
// 	sem_destroy(&contadorExec);
// 	sem_destroy(&multiprogramacion);
// 	sem_destroy(&contadorBlocked);
// 	sem_destroy(&analizarSuspension);
// 	sem_destroy(&suspensionFinalizada);
// 	sem_destroy(&largoPlazo);
// 	sem_destroy(&contadorReadySuspended);
// 	sem_destroy(&medianoPlazo);

// }


// LISTAS

// void destruir_listas(void){

// 	destruirListaYElementos(colaNew);
// 	destruirListaYElementos(colaReady);
// 	destruirListaYElementos(colaExec);
// 	destruirListaYElementos(colaBlocked);
// 	destruirListaYElementos(colaExit);
	
// }

// void destruirListaYElementos(t_list* unaLista){
//     list_clean_and_destroy_elements(unaLista, free);
//     list_destroy(unaLista);
// }


// --------------------------------------------------- FUNCIONES CORTO PLAZO ----------------------------------------------------------
//pcb* obtenerSiguienteReady(){
//	pcb* procesoSeleccionado;
//
//	int tamanioReady;
// 	tamanioReady = list_size(colaReady);
// 	int gradoMultiprogramacion;
// 	algoritmo algoritmo = obtener_algoritmo();
// 	int ejecutando = list_size(colaExec);
//
//
// 	if (tamanioReady > 0 && ejecutando < gradoMultiprogramacion){
// 		switch(algoritmo){
// 		case FIFO:
// 			procesoSeleccionado = obtenerSiguienteFIFO();
// 			break;
// 		case SRT:
// 			procesoSeleccionado = obtenerSiguienteSRT();
// 			break;
// 		}
// 	}
// 	return procesoSeleccionado;
// }
//
// pcb* obtenerSiguienteFIFO(){
// 	log_info(logger,"Inicio la planificacion FIFO");
// 	pcb* procesoSeleccionado = list_remove(colaReady,0);
//	return procesoSeleccionado;
//
//}
//
//pcb* obtenerSiguienteSRT(){
// 	log_info(logger,"Inicio la planificacion SRT");
// 	asignarEstimacionesAProcesos();
// 	pcb* procesoElegido = elegirElDeMenorEstimacion();
// 	return procesoElegido;
// }
//
//pcb* elegirElDeMenorEstimacion(){
//	int tamanioReady = list_size(colaReady);
//	pcb* procesoSeleccionado;
//	pcb* procesoAux;
//	int indiceElegido = 0;
//	float procesoMasCorto;
//	procesoMasCorto = procesoAux->estimacion_rafaga;
//	for(int i = 0; i < tamanioReady; i++){
//		pcb* procesoAux = list_get(colaReady,i);
//		if(procesoMasCorto > procesoAux->estimacion_rafaga){
//			procesoMasCorto = procesoAux->estimacion_rafaga;
//			indiceElegido = i;
//		}
//	}
//
//	procesoSeleccionado = list_remove(colaReady,indiceElegido);
//
//	return procesoSeleccionado;
//}
//
//void asignarEstimacionesAProcesos(){
// 	int tamanioReady = list_size(colaReady);
//	for(int i = 0; i < tamanioReady; i++){
//		pcb* proceso = list_get(colaReady,i);
//		float realAnterior;
//		proceso->estimacion_rafaga = calculoEstimacionProceso(realAnterior); // le paso a calculoEstimacionProceso la rafaga real anterior
//	};
//}  //revisar bien esta funcion
//
//float calculoEstimacionProceso(float realAnterior){
//	float alfa;
//	float estimacionInicial;
//	float estimacion_rafaga = alfa * realAnterior + (1 - alfa) * estimacionInicial;
//	return estimacion_rafaga;
//}

//void interrumpir_cpu(){
//	t_paquete *paqueteAEnviar = crear_paquete_con_codigo_de_operacion(INTERRUPCION);
//	enviar_paquete(paqueteAEnviar, socket_interrupt);
//	eliminar_paquete(paquete);

//}

//probando