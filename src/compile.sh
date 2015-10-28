#!/bin/bash

gcc -o server server.c headers/tabuleiro.h headers/tabuleiro.c headers/jogador.c headers/jogador.h

gcc -o client client.c headers/tabuleiro.h headers/tabuleiro.c headers/jogador.c headers/jogador.h
