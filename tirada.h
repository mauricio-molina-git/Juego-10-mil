#ifndef TIRADA_H_INCLUDED
#define TIRADA_H_INCLUDED

int tirar(int dado[]);
void puntajeFinal(int dado[]);
void contarDados(int dado[], int cuenta[]);
void maximos(int cuenta[], int maximo[], int valor[]);
int evaluar(int cuenta[], int maximo[], int valor[]);
void mostrar(int dado[]);
int turno(int puntajeInicial, int numero, char *nombre);
void cambioRonda(int numero, char *nombre1, char *nombre2, int puntaje1, int puntaje2);

#endif // TIRADA_H_INCLUDED
