#!/bin/bash

gcc -o server server.c headers/error.h headers/error.c

gcc -o client client.c headers/error.h headers/error.c
