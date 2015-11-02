#!/bin/bash

gcc -o server server.c headers/error.h headers/error.c headers/message.h headers/message.c headers/jogador.h headers/jogador.c headers/tabuleiro.h headers/tabuleiro.c

gcc -o client client.c headers/error.h headers/error.c headers/message.h headers/message.c headers/jogador.h headers/jogador.c headers/tabuleiro.h headers/tabuleiro.c 
