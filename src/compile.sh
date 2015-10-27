#!/bin/bash

gcc -o server server.c headers/tabuleiro.h headers/tabuleiro.c

gcc -o client client.c headers/tabuleiro.h headers/tabuleiro.c


