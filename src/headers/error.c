#include <stdlib.h>
#include "error.h"

	void socket_error(){
		perror("Erro ao criar um socket");
		exit(1);
	}

	void connect_error(){
		perror("Erro ao solicitar uma conexão");
		exit(1);
	}

	void recv_error(){
		perror("Erro ao receber uma mensagem");
		exit(1);
	}

	void send_error(){
		perror("Erro ao enviar uma mensagem");
		exit(1);
	}

	void bind_error(){
		perror("Erro ao associar uma porta ao socket (bind)");
		exit(1);
	}

	void listen_error(){
		perror("Erro ao abrir a escuta");
		exit(1);
	}

	void gethostbyname_error(){
		herror("gethostbyname");
        	exit(1);
	}
