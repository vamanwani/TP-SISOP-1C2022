#include "consola.h"


int main(int argc, char **argv){

	if(argc < 2){
		return EXIT_FAILURE;
	}

//	Inicializacion

	int tamanio_proceso = atoi(argv[1]);

//	Logging consola

	logger = iniciar_logger("consola.log", "Consola", 1, LOG_LEVEL_INFO);
	log_info(logger,"Iniciando consola\n");

//	Configuracion

	t_config* config = cargar_configuracion("cfg/consola.config");

//	Parseo

	t_list *instrucciones = parsear_instrucciones(argv[2]);
	log_info(logger, "Instrucciones parseadas correctamente\n");

//	Serializacion y agregar a paquete

	t_paquete *paquete_instrucciones = crear_paquete_con_codigo_de_operacion(PAQUETE_CONSOLA);
	serializar_instrucciones(instrucciones, paquete_instrucciones);
//	agregar_entero_a_paquete(paquete_instrucciones, tamanio_proceso);


//	Conexion servidor

	int server_fd = crear_conexion(config_valores_consola.ip_kernel, config_valores_consola.puerto_kernel);
	log_info(logger, "Conexion exitosa con kernel.\n");

//	Enviar paquete

	enviar_paquete(paquete_instrucciones, server_fd);
	log_info(logger, "Paquete enviado correctamente.\n");

//	Terminar programa

	log_info(logger, "Terminando programa.\n");
	terminar_programa(server_fd, logger, config);


	return 0;
}

t_config* cargar_configuracion(char* path) {

	t_config* config = config_create(path); //Leo el archivo de configuracion

	if (config == NULL) {
	  	perror("Archivo de configuracion de consola no encontrado");
	  	abort();
	}

	config_valores_consola.ip_kernel = config_get_string_value(config, "IP_KERNEL");
	config_valores_consola.puerto_kernel = config_get_string_value(config, "PUERTO_KERNEL");

	return config;
}

t_list *parsear_instrucciones(char* path) {
	t_list *instrucciones = list_create();
	uint32_t parametro1;
	uint32_t parametro2;
	char *pseudo_codigo_leido = leer_archivo(path);
	char **split_instrucciones = string_split(pseudo_codigo_leido, "\n");
	int indice_split = 0;
	while(split_instrucciones[indice_split] != NULL) {
		char **palabras = string_split(split_instrucciones[indice_split], " ");
		if(string_equals_ignore_case(palabras[0], "NO_OP")){
			parametro1 = atoi(palabras[1]);
			for(int i=0; i<parametro1; i++){
				list_add(instrucciones, armar_estructura_instruccion(NO_OP, 0, 0));
			}
		}
		else if(string_equals_ignore_case(palabras[0], "I/O")){
			parametro1 = atoi(palabras[1]);
			list_add(instrucciones, armar_estructura_instruccion(IO, parametro1, 0));
		}
		else if(string_equals_ignore_case(palabras[0], "READ")){
			parametro1 = atoi(palabras[1]);
			list_add(instrucciones, armar_estructura_instruccion(READ, parametro1, 0));
		}
		else if(string_equals_ignore_case(palabras[0], "WRITE")){
			parametro1 = atoi(palabras[1]);
			parametro2 = atoi(palabras[2]);
			list_add(instrucciones, armar_estructura_instruccion(WRITE, parametro1, parametro2));
		}
		else if(string_equals_ignore_case(palabras[0], "COPY")){
			parametro1 = atoi(palabras[1]);
			parametro2 = atoi(palabras[2]);
			list_add(instrucciones, armar_estructura_instruccion(COPY, parametro1, parametro2));
		}
		else if(string_equals_ignore_case(palabras[0], "EXIT")){
			list_add(instrucciones, armar_estructura_instruccion(EXIT, 0, 0));
		}
		indice_split++;
		free(palabras);
	}
	return instrucciones;
}

instruccion *armar_estructura_instruccion(codigo_instrucciones id, uint32_t parametro1, uint32_t parametro2) {
	instruccion *estructura = malloc(sizeof(instruccion));
	estructura->codigo = id;
	estructura->parametro1 = parametro1;
	estructura->parametro2 = parametro2;
	return estructura;
}

void serializar_instrucciones(t_list *instrucciones, t_paquete *paquete){

	for(int i=0; i<list_size(instrucciones); i++) {
		instruccion *instr = list_get(instrucciones, i);
		agregar_a_paquete(paquete, &(instr->codigo), sizeof(codigo_instrucciones));
		agregar_a_paquete(paquete, &(instr->parametro1), sizeof(uint32_t));
		agregar_a_paquete(paquete, &(instr->parametro2), sizeof(uint32_t));
	}
	unsigned char *stream = (unsigned char *)paquete->buffer->stream; //Para debuggear
    for(int i=0 ; i<paquete->buffer->stream_size;i++){
    	printf("%02X ",stream[i]);
    }

}

char *leer_archivo(char *unPath)
{

    char instrucciones[100];
    strcpy(instrucciones, unPath);

    FILE *archivo = fopen(instrucciones, "r");

    if (archivo == NULL)
    {
        perror("Error al abrir el archivo.\n");
    }

    fseek(archivo, 0, SEEK_END);         // mover el archivo al final
    int cant_elementos = ftell(archivo); // cantidad total de elementos que tiene el archivo
    rewind(archivo);                        //mover archivo al inicio del txt

    char *cadena = calloc(sizeof(char) + 1, cant_elementos); //arreglo dinamico de caracteres para almacenar en cadena el contenido del archivo
    if (cadena == NULL)
    {
        perror("Error en la reserva de memoria") ;
    }
    int cant_elementos_leidos = fread(cadena, sizeof(char), cant_elementos, archivo);
    if (cant_elementos_leidos != cant_elementos)
    {
        perror("Error leyendo el archivo.\n") ;
    }

    printf("\n%s", cadena);
    fclose(archivo);
    printf("\nSe ha leido el archivo de pseudocodigo correctamente.\n");
    return cadena;
}
