#ifdef ERROR_H
#define ERROR_H

	//Erro ao criar um socket
	void socket_error();
	//Erro ao solicitar uma conexão
	void connect_error();
	//Erro ao receber uma mensagem
	void recv_error();
	//Erro ao enviar uma mensagem
	void send_error();
	//Erro ao associar uma porta ao socket
	void bind_error();
	//Erro ao iniciar uma escuta
	void listen_error();
	//Erro no gethostbyname
	void gethostbyname_error();

#endif
