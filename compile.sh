mkdir -p bin

cd src

gcc -o ../bin/server server.c headers/jogador.h headers/jogador.c

gcc -o ../bin/client client.c headers/jogador.h headers/jogador.c
