#ifndef GRAPHICS_H
#define GRAPHICS_H

/*
Valores para parametro de cambio_color:
0 = Negro         8 = Gris oscuro
1 = Azul          9 = Azul claro  
2 = Verde         10 = Verde claro
3 = Aguamarina    11 = Aguamarina claro
4 = Rojo          12 = Rojo claro
5 = Púrpura       13 = Púrpura claro
6 = Amarillo      14 = Amarillo claro
7 = Blanco        15 = Blanco brillante
*/

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>

using namespace std;

void gotoxy(int,int) ;
void mostrarCursor(bool);
void bannerInicio();
void cambio_color(int);

void gotoxy(int x,int y) {
    HANDLE hcon;  
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
    COORD dwPos;  
    dwPos.X = x;  
    dwPos.Y= y;  
    SetConsoleCursorPosition(hcon,dwPos);
}   

void mostrarCursor(bool visible) {
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE); 
    CONSOLE_CURSOR_INFO cci;                        
    GetConsoleCursorInfo(hCon, &cci);              
    cci.bVisible = visible;                         
    SetConsoleCursorInfo(hCon, &cci);              
}

void cambio_color(int x){
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
}

void bannerInicio() {
    system("cls");
    string titulo = "SISTEMA DE GESTION HOSPITALARIA";
    string subtitulo = "    Hospital Nacional";
    
    cambio_color(11);
    gotoxy(25, 5);
    cout << char(201);
    for (int i = 0; i < 40; i++) cout << char(205);
    cout << char(187);

    for (int i = 6; i <= 11; i++) {
        gotoxy(25, i); cout << char(186);
        gotoxy(66, i); cout << char(186);
    }

    gotoxy(25, 12);
    cout << char(200);
    for (int i = 0; i < 40; i++) cout << char(205);
    cout << char(188);

    // Animación tipo máquina de escribir
    cambio_color(14);
    gotoxy(30, 7);
    for (char c : titulo) {
        cout << c;
        Sleep(80);
    }

    cambio_color(14);
    gotoxy(33, 9);
    for (char c : subtitulo) {
        cout << c;
        Sleep(50);
    }

    cambio_color(7);
    gotoxy(35, 11);
    cout << "Cargando sistema";
    for (int i = 0; i < 3; i++) {
        cout << ".";
        Sleep(700);
    }
    Sleep(600);

    system("cls");
    cambio_color(15);
}

#endif
