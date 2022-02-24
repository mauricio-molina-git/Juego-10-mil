#include <iostream>

using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

const char *nombreTirada[] = {
    "Juego de 1",       // 0
    "Juego de 5",       // 1
    "Trio 1",           // 2
    "Trio X",           // 3
    "Trio X ampliado",  // 4
    "Trio 1 ampliado",  // 5
    "Tres pares",       // 6
    "Escalera mediana", // 7
    "Escalera larga",   // 8
    "Sexteto"           // 9
};

void gotoxy(int x, int y){
  COORD pos;
  pos.X = x;
  pos.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void tirarDadosManual(int dado[], int y) {
    int i;
    int x = 1;
    int num;

    /* obtiene la tirada de 6 dados en forma manual */
    for(i = 0; i < 6; i++) {
        gotoxy(x, y);
        cout << "[" << i+1 << "]: ";
        cin >> num;

        while(num < 1 || num > 6) {
           //cout<<"DADO INCORRECTO."<<endl<<endl;
            gotoxy(x, y);
            cout << "[" << i+1 << "]: ";
            cin >> num;
        }
        dado[i] = num;
        x += 8;
    }
}

void tirarDados(int dado[]) {
    int i;
    /* obtiene la tirada de 6 dados en forma aleatoria */
    for(i = 0; i < 6; i++) {
        dado[i] = rand() % 6 + 1;
    }
}

void puntajeFinal(int dado[]) {
    int i, cambio;
    /* obtiene la tirada de 6 dados en forma aleatoria */
    //tirarDados(dado);
     tirarDadosManual(dado, 7);
    /* los ordena de menor a mayor (método de la burbuja) */
    do {
        cambio = 0;
        for(i = 1; i < 6; i++) {
            if(dado[i] < dado[i-1]) {
                int x = dado[i];
                dado[i] = dado[i-1];
                dado[i-1] = x;
                cambio = 1;
            }
        }
    } while(cambio);
}

/*
    Cuenta la cantidad de apariciones de cada dado.
*/

void contarDados(int dado[], int cuenta[]) {
    int i;

    /* inicia todos los contadores en 0 */
    for(i = 0; i < 6; cuenta[i++] = 0);

    for(i = 0; i < 6; i++) {
        /* incrementa el contador correspondiente al valor de cada dado */
        int d = dado[i] - 1;
        cuenta[d]++;
    }
}
/*
    Determina las tres cantidades máximas de apariciones y los valores correspondientes.
*/
void maximos(int cuenta[], int maximo[], int valor[]) {
    int i;

    for(i = 0; i < 3; i++) {
        maximo[i] = valor[i] = 0;
    }

    for(i = 0; i < 6; i++) {
        int c = cuenta[i];

        if(c > maximo[2]) {
            if(c > maximo[1]) {
                maximo[2] = maximo[1];
                valor[2] = valor[1];
                if(c > maximo[0]) {
                    maximo[1] = maximo[0];
                    valor[1] = valor[0];
                    maximo[0] = c;
                    valor[0] = i+1;
                } else {
                    maximo[1] = c;
                    valor[1] = i+1;
                }
            } else {
                maximo[2] = c;
                valor[2] = i+1;
            }
        }
    }
}

int evaluar1y5(int cuenta[], char resultado[]) {
    int puntos;

    if(cuenta[0] == 2) {
        puntos = 100 * 2;
        strcpy(resultado, "Dos unos");
    } else if(cuenta[4] == 2) {
        puntos = 50 * 2;
        strcpy(resultado, "Dos cincos");
    } else if(cuenta[0] == 1) {
        puntos = 100 * 1;
        strcpy(resultado, "Un uno");
    } else if(cuenta[4] == 1) {
        puntos = 50 * 1;
        strcpy(resultado, "Un cinco");
    } else {
        puntos = 0;
        strcpy(resultado, "Nada");
    }

    return puntos;
}

/*
    maximo[3] tiene las tres cantidades máximas que aparecieron
    valor[3] tiene los números de los dados correspondientes (1..6)
*/
int evaluar(int cuenta[], int maximo[], int valor[], char resultado[]) {
    int puntos;

    switch(maximo[0]) {
    case 1:
        puntos = 1500;
        strcpy(resultado, "Escalera completa");
        break;
    case 2:
        if(maximo[1] == 2) {
            if(maximo[2] == 2) {
                puntos = 1500;
                strcpy(resultado, "Tres pares");
            } else {
                puntos = evaluar1y5(cuenta, resultado);
            }
        } else {
            if(cuenta[0] == 0 || cuenta[5] == 0) {
                puntos = 500;
                strcpy(resultado, "Escalera mediana");
            }else {
                puntos = evaluar1y5(cuenta, resultado);
            }
        }
        break;
    case 3:
        if(valor[0] == 1) {
            puntos = 1000;
            strcpy(resultado, "Trio de 1");
        } else {
            puntos = 100 * valor[0];
            sprintf(resultado, "Trio de %d", valor[0]);
        }
        break;
    case 4:
    case 5:
        if(maximo[1] == 2) {
            puntos = 1500;
            strcpy(resultado, "Tres pares");
        } else if(valor[0] == 1) {
            puntos = 2000;
            strcpy(resultado, "Trio de 1 ampliado");
        } else {
            puntos = 100 * 2 * valor[0];
            sprintf(resultado, "Trio de %d ampliado", valor[0]);
        }
        break;
    case 6:
        if(valor[0] == 1) {
            puntos = 10000;
            strcpy(resultado, "Sexteto");
        } else {
            puntos = 1500;
            strcpy(resultado, "Tres pares");
        }
    }

    return puntos;
}

int tirar(int dado[], char resultado[]) {
    int cuenta[6];
    int maximo[3];
    int valor[3];

    puntajeFinal(dado);
    contarDados(dado, cuenta);
    maximos(cuenta, maximo, valor);
    return evaluar(cuenta, maximo, valor, resultado);
}

void pantalla(int puntajeInicial, int numero, char *nombre, int esteTurno, int tiradas) {
    system("cls");

    cout << "TURNO DE " << nombre << " | RONDA N° " << numero << " | PUNTAJE TOTAL " << puntajeInicial << endl;
    cout << "----------------------------------------------------------------------" << endl;
    cout << "PUNTAJE DE LA RONDA " << esteTurno << endl;
    cout << "LANZAMIENTO N° " << tiradas << endl;
    cout << "----------------------------------------------------------------------" << endl;

}

void cambioRonda(int numero, char *nombre1, char *nombre2, int puntaje1, int puntaje2) {
    system("cls");

    cout << "RONDA N° " << numero << endl;
    cout << "PRÓXIMO TURNO " << nombre1 << endl;
    cout << "PUNTAJE " << nombre1 << ": " << puntaje1 << endl;
    cout << "PUNTAJE " << nombre2 << ": " << puntaje2 << endl;
    system("pause");
}

void dibujar(int dado, int x, int y) {
    gotoxy(x+1, y);
    cout << "-------";
    gotoxy(x, y+1);
    cout << "|       |";
    gotoxy(x, y+2);
    cout << "|       |";
    gotoxy(x, y+3);
    cout << "|       |";
    gotoxy(x+1, y+4);
    cout << "-------";

    x+=2;
    y++;

    switch(dado) {
    case 1:
        gotoxy(x+2, y+1);
        cout << "O";
        gotoxy(x+2, y+2);
        break;
    case 2:
        gotoxy(x+2, y);
        cout << "O";
        gotoxy(x+2, y+2);
        cout << "O";
        break;
    case 3:
        gotoxy(x, y);
        cout << "O";
        gotoxy(x+2, y+1);
        cout << "O";
        gotoxy(x+4, y+2);
        cout << "O";
        break;
    case 4:
        gotoxy(x, y);
        cout << "O   O";
        gotoxy(x, y+2);
        cout << "O   O";
        break;
    case 5:
        gotoxy(x, y);
        cout << "O   O";
        gotoxy(x+2,y+1);
        cout << "O";
        gotoxy(x,y+2);
        cout << "O   O";
        break;
    case 6:
        gotoxy(x, y);
        cout << "O   O";
        gotoxy(x, y+1);
        cout << "O   O";
        gotoxy(x, y+2);
        cout << "O   O";
        break;
    }
}

void dibujarTodos(int dados[], int x, int y) {
    int i;
    int h = x;

    for(i = 0; i < 6; i++) {
        dibujar(dados[i], h, y);
        h += 12;
    }
}

int turno(int puntajeInicial, int numero, char *nombre) {
    int dados[6];
    int esteTurno = 0;
    int puntos;
    int puntajeFinal;
    int sigue = 1;
    int tiradas = 0;
    char resultado[30];

    char resp;

    do {
        tiradas ++;

        pantalla(puntajeInicial, numero, nombre, esteTurno, tiradas);

        puntos = tirar(dados, resultado);
        esteTurno += puntos;

        dibujarTodos(dados, 1, 9);

        cout << endl << endl << "\tOBTUVISTE " << resultado << " +" << puntos << endl;

        if(puntos == 10000) {
            puntajeFinal = 10000;
            sigue = 0;
        } else {
            if(puntos == 0 || puntajeInicial + esteTurno > 10000) {
                puntajeFinal = puntajeInicial;
                sigue = 0;
            } else if(puntajeInicial + esteTurno == 10000) {
                puntajeFinal = 10000;
                sigue = 0;
            } else {
                cout << "CONTINUAR LANZANDO (S/N)? ";
                cin >> resp;
                sigue = resp == 'S' || resp == 's';
                if(!sigue) {
                    puntajeFinal = puntajeInicial + esteTurno;
                }
            }
        }
    } while(sigue);

    cout << "\nFin del turno " << numero << " de " << nombre << endl;
    cout << "Puntaje final " << puntajeFinal << endl;
    system("pause");

    return puntajeFinal;
}
