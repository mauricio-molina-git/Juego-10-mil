#include  "tirada.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

int menu() {
    int opcion;

    cout << endl;
    cout << "------------------------------" << endl;
    cout << "           Diez Mil" << endl;
    cout << "------------------------------" << endl;
    cout << "1. Juego nuevo para un jugador" << endl;
    cout << "2. Juego nuevo para dos jugadores" << endl;
    cout << "3. Mostrar puntaje máximo" << endl;
    cout << "0. Salir" << endl;
    cout << "------------------------------" << endl;
    cout << "Su opcion: ";
    cin >> opcion;

    while(opcion < 0 || opcion > 3) {
        cout << "Opcion incorrecta. Ingrese nuevamente ";
        cin >> opcion;
    }

    return opcion;
}

int main()
{
    int dado[6];
    int opcion;
    int puntaje1, puntaje2;
    int ronda1, ronda2;
    char nombre1[20];
    char nombre2[20];
    int jugadores = 0;

    setlocale(LC_ALL, "Spanish");

    opcion = menu();
    while(opcion != 0) {
        switch(opcion) {
        case 1:
            jugadores = 1;


            system("cls") ;
            cout << "NOMBRE DEL JUGADOR: ";
            cin >> nombre1;

            puntaje1 = 0;
            ronda1 = 0;
            do {
                puntaje1 += turno(puntaje1, ++ronda1, nombre1);
            } while(puntaje1 < 10000);

            system("cls");
            cout<<"--------------------"<<endl;
            cout << "JUGADOR " << nombre1 << endl;
            cout << "PUNTOS " << puntaje1 << endl;
            cout << "RONDAS " << ronda1 << endl;
            cout<<"--------------------"<<endl;
            system("pause") ;
            system("cls");
            break;


        case 2:
            jugadores = 2;
            system("cls");
            cout << "NOMBRE JUGADOR 1: ";
            cin >> nombre1;
            cout << "NOMBRE JUGADOR 2: ";
            cin >> nombre2;

            puntaje1 = 0;
            puntaje2 = 0;
            ronda1 = 0;
            ronda2 = 0;

            do {
                puntaje1 = turno(puntaje1, ++ronda1, nombre1);
                cambioRonda(ronda2, nombre2, nombre1, puntaje2, puntaje1);
                puntaje2 = turno(puntaje2, ++ronda2, nombre2);
                cambioRonda(ronda1, nombre1, nombre2, puntaje1, puntaje2);
            } while(puntaje1 < 10000 && puntaje2 < 10000);

            system("cls");

            if(puntaje1 > puntaje2) {
                cout<<"------------------------"<<endl;
                cout << "EL GANADOR ES:" << endl;
                cout << "JUGADOR " << nombre1 << endl;
                cout << "PUNTOS " << puntaje1 << endl;
                cout << "RONDAS " << ronda1 << endl;
                cout<<"------------------------"<<endl;
                 system("pause") ;
                 system("cls") ;
            } else if(puntaje2 > puntaje1) {
                cout<<"------------------------"<<endl;
                cout <<"EL GANADOR ES:" << endl;
                cout << "JUGADOR " << nombre2 << endl;
                cout << "PUNTOS " << puntaje2 << endl;
                cout << "RONDAS " << ronda2 << endl;
                cout<<"------------------------"<<endl;
                 system("pause") ;
                 system("cls") ;
            } else {
                cout<<"------------------------"<<endl;
                cout << "EMPATE:" << endl;
                cout << "JUGADOR " << nombre1 << endl;
                cout << "JUGADOR " << nombre2 << endl;
                cout << "PUNTOS " << puntaje2 << endl;
                cout << "RONDAS " << ronda2 << endl;
                cout<<"------------------------"<<endl;
                 system("pause") ;
                 system("cls") ;

            }

            break;
        case 3:
            if(jugadores == 0) {
                system("cls");
                cout<<"-------------------------------"<<endl;
                cout << "NO SE HA COMENZADO A JUGAR." << endl;
                cout<<"-------------------------------"<<endl;
                system("pause");
                system("cls");
            } else {
                system("cls");
                //cout << endl << "EL GANADOR ES:" << endl;

                if(jugadores == 2 && puntaje2 > puntaje1) {
                    cout<<"-------------------------------"<<endl;
                    cout << "JUGADOR " << nombre2 << endl;
                    cout << "PUNTOS " << puntaje2 << endl;
                    cout << "RONDAS " << ronda2 << endl;
                    cout<<"-------------------------------"<<endl;
                } else {
                    cout<<"-------------------------------"<<endl;
                    cout << "JUGADOR " << nombre1 << endl;
                    cout << "PUNTOS " << puntaje1 << endl;
                    cout << "RONDAS " << ronda1 << endl;
                    cout<<"-------------------------------"<<endl;
                }
                system("pause");
                system("cls");
            }

            break;
        }

        opcion = menu();
    }

    return 0;
}
