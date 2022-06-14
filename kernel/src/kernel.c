#include "kernel.h"

//........................................INICIO_KERNEL.......................................................................

int main(void){

//	Logging kernel

	logger = log_create("kernel.log", "Kernel", 1, LOG_LEVEL_INFO);

//	Configuracion

//	cargar_configuracion("cfg/kernel.config");

//	Iniciar Cliente/Servidor

	int server_fd = iniciar_servidor(IP_KERNEL, PUERTO_KERNEL);
	log_info(logger, "Kernel listo para recibir al cliente.\n");

	while(1){
		int cliente_fd = esperar_cliente(logger,"kernel",server_fd); //Si espera el cliente adentro del while, puede recibir varias consolas sin romper
		int cod_op = recibir_operacion(cliente_fd);

		switch(cod_op){
		case PAQUETE_CONSOLA:
			log_info(logger, "Recibi un paquete de consola.\n");
			break;
		case HANDSHAKE:
			log_info(logger, "Hola consola.\n");
			break;
		case -1:
			log_error(logger, "Fallo la comunicacion.\n");
			return EXIT_FAILURE;
		default:
			log_warning(logger, "Operacion desconocida.\n");
		}
	}

	return EXIT_SUCCESS;

}

//-.................................DESERIALIZAR INSTRUCCIONES.................................................................

//.......................................CONFIGURACIONES.......................................................................

  void cargar_configuracion(char* path) {

  	t_config* config = config_create(path); //Leo el archivo de configuracion

  	if (config == NULL) {
  		perror("Archivo de configuracion de kernel no encontrado");
  		return;
  	}

  	config_valores_kernel.ip_memoria = config_get_string_value(config, "IP_MEMORIA");
  	config_valores_kernel.ip_cpu = config_get_string_value(config, "IP_CPU");
  	config_valores_kernel.algoritmo_planificacion = config_get_string_value(config, "ALGORITMO_PLANIFICACION");
  	config_valores_kernel.puerto_memoria =	config_get_int_value(config, "PUERTO_MEMORIA");
  	config_valores_kernel.puerto_cpu_dispatch = config_get_int_value(config, "PUERTO_CPU_DISPATCH");
  	config_valores_kernel.puerto_cpu_interrupt = config_get_int_value(config, "PUERTO_CPU_INTERRUPT");
  	config_valores_kernel.puerto_escucha = config_get_int_value(config, "PUERTO_ESCUCHA");
  	config_valores_kernel.estimacion_inicial = config_get_int_value(config, "GRADO_MULTIPROGRAMACION");
  	config_valores_kernel.grado_multiprogramacion = config_get_int_value(config, "ESTIMACION_INICIAL");
  	config_valores_kernel.tiempo_maximo_bloqueado = config_get_int_value(config, "TIEMPO_MAXIMO_BLOQUEADO");
    config_valores_kernel.alfa = config_get_double_value(config, "ALFA");
  	config_destroy(config);

  }

//......................................INICIALIZACIONES.......................................................................

//.........................................CONEXIONES..........................................................................

//...........................................HILOS.............................................................................

//........................................DESTRUCCIONES........................................................................

