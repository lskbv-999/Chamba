#ifndef MENU_H
#define MENU_H

#include "val.h"

void menu(){
    mostrarCursor(false);
    system("cls");
    string opciones[4] = {"INGRESAR PACIENTE", "MOSTRAR PACIENTES","BORRAR PACIENTE", "SALIR"};
    int posX = 40, posY = 5, seleccion=0, cant_opciones=4;
    int anterior;//guarda la pos de seleccion
    bool bandera = true;

    // Dibujo el menu principal, todas en blanco
    for(int i=0;i<cant_opciones;i++){
        gotoxy(posX, posY + (i*2));
        cambio_color(15);
        cout << opciones[i];
    }

    // Voy a pintar la primera, osea por defecto estará selecionada
    gotoxy(posX, posY);
    cambio_color(9);
    cout << opciones[0];

    while(bandera){

        if(kbhit()){
            
            char tecla = getch();//es para que no se muestre la tecla
            anterior = seleccion;

            if(tecla == 72) //Flecha arriba
                seleccion = (seleccion - 1 + cant_opciones)% cant_opciones;
            if(tecla == 80) //Flecha abajo
                seleccion = (seleccion + 1)% cant_opciones;
            
            if(tecla ==13){
                system("cls");
                bandera=false;
                cambio_color(15);
                mostrarCursor(true);

                switch(seleccion){

                    case 0 : ingresoPaciente();break;
                    case 1 : mostrarPacientes(); break;
                    case 2: borrarPaciente(); break;
                    case 3: exit(1);
                }

                menu();//para que vuelva al menu luego de mostrar lo q sea
            }

            // Restaurar color de la opción anterior
            gotoxy(posX, posY + (anterior*2));
            cambio_color(15);
            cout << opciones[anterior];

            // Pintar color de la nueva opción seleccionada
            gotoxy(posX, posY + (seleccion*2));
            cambio_color(9);
            cout << opciones[seleccion];
        }
    }
}

#endif
