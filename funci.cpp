#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <cctype>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::min;
void ingresoMedico();
void ingresoPaciente();
void menu();
void mostrarPacientes();
void gotoxy(int,int) ;
void cambio_color(int);
void mostrarCursor(bool );

void gotoxy(int x,int y) {
    HANDLE hcon;  
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
    COORD dwPos;  
    dwPos.X = x;  
    dwPos.Y= y;  
    SetConsoleCursorPosition(hcon,dwPos);
}

struct paciente{
    string nombre;
    int DNI;
    int edad;
    string sexo;
    int gravedad;
};

paciente camaGeneral[50];
paciente camaUCIN[30];
paciente camaUCI[20];

int contGeneral=0,contUCIN=0,contUCI=0;

int main(){
    ingresoMedico();
    menu();
    
    return 0;
}

string clavesita(int x, int y){
              string contra;
              char caractersito;
              while(true){
                     caractersito=getch();
                     if(caractersito==13){
                            break;
                     }       
                     else if(caractersito==8){
                            if(contra.empty()==false){//evalua si la cadena esta vacia
                                          contra.pop_back();//elimina el ultimo caracter
                                          cout << "\b \b";//retrocede
                            }
                     }
                     else{
                            contra.push_back(caractersito);
                            cout << "*";
                     }
              }
              return contra;
}
void ingresoMedico(){
    int contador=0;
    string codigo="1", contra="2";
    string ingreso_codigo, ingreso_contra;
    do{
        gotoxy(35,5);cout<<"INGRESE CODIGO MEDICO: "; 
		getline(cin, ingreso_codigo);
		
        gotoxy(35,7);cout<<"INGRESE CONTRASENA: "; 
                            ingreso_contra=clavesita(57,7);
        
        if(ingreso_codigo==codigo && ingreso_contra==contra){
        	return; 
        }
        else{
            contador++;
            gotoxy(35,9); cout<<"CREDENCIALES INCORRECTAS. Intentos: "<<contador<<"/3";
            getch();
            system("cls");
        } 
    }while(contador<3);

    gotoxy(35,11); cout << "ACCESO DENEGADO. Cerrando programa...";
    Sleep(1000);
    system("cls");
    exit(1);
}

void ingresoPaciente(){
    system("cls");
	paciente nuevo;

	for(int i=30; i<=90; i++){   
        gotoxy(i,2); cout << char(205);
         gotoxy(i,15); cout << char(205); }
         
    for(int j=2; j<=15; j++){   
        gotoxy(30,j); cout << char(186);
        gotoxy(90,j); cout << char(186);   }
	
           gotoxy(30,2); cout << char(201);  
            gotoxy(90,2); cout << char(187);  
        gotoxy(30,15); cout << char(200); 
        gotoxy(90,15); cout << char(188); 
	
    gotoxy(35,3);cout << "INGRESO DEL PACIENTE";
    gotoxy(35,5);cout << "Nombre: ";
    cin.ignore();
    getline(cin, nuevo.nombre);
    gotoxy(35,6);cout <<"DNI: "; cin >> nuevo.DNI;
    gotoxy(35,7);cout <<"Edad: "; cin >> nuevo.edad;
    gotoxy(35,8);cout <<"Sexo: "; cin >> nuevo.sexo;

    // PARA validad entre 1 a 3
    do {
        gotoxy(35,9);cout <<"Nivel de gravedad [1-General | 2-UCIN | 3-UCI]: ";
        cin >> nuevo.gravedad;
        if(nuevo.gravedad < 1 || nuevo.gravedad > 3){
			gotoxy(35+42,9); cout << "   ";
            gotoxy(35,11);cout << "Error: nivel de gravedad invalido. Intente de nuevo.";
        }
    } while(nuevo.gravedad < 1 || nuevo.gravedad > 3);

    switch(nuevo.gravedad){
        case 1:
            if(contGeneral < 50) {   
            camaGeneral[contGeneral] = nuevo;
            contGeneral++;
            gotoxy(35,13);cout << "Paciente guardado en cama General.";
            } else {
            gotoxy(35,13);cout << "No hay espacio en cama General.";
               }
        break;
        case 2:
            if (contUCIN < 30){
            camaUCIN[contUCIN] = nuevo;
            contUCIN++;
            gotoxy(35,13);cout << "Paciente guardado en cama UCIN.";
            }
		    else{
            gotoxy(35,13);cout <<"No hay espacio en cama UCIN.";
             }
        break;
        case 3:
            if(contUCI < 20) {
            camaUCI[contUCI] = nuevo;
            contUCI++;
            gotoxy(35,13);cout << "Paciente guardado en cama UCI.";
            } else{
            gotoxy(35,13);cout << "No hay espacio en cama UCI.";
              }
        break;
    }
}

void menu(){
    mostrarCursor(false);
    system("cls");
    string opciones[3] = {"INGRESAR PACIENTE", "MOSTRAR PACIENTES", "SALIR"};
    int posX = 40, posY = 5, seleccion=0, cant_opciones=3;
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
    cambio_color(14);
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
                    case 2 : return;
                }

                menu();//para que vuelva al menu luego de mostrar lo q sea
            }

            // Restaurar color de la opción anterior
            gotoxy(posX, posY + (anterior*2));
            cambio_color(15);
            cout << opciones[anterior];

            // Pintar color de la nueva opción seleccionada
            gotoxy(posX, posY + (seleccion*2));
            cambio_color(14);
            cout << opciones[seleccion];


        }

    }
}


void mostrarCursor(bool visible) {
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE); 
    CONSOLE_CURSOR_INFO cci;                        
    GetConsoleCursorInfo(hCon, &cci);              
    cci.bVisible = visible;                         
    SetConsoleCursorInfo(hCon, &cci);              
}

//AQUI FALTA LAS PAGINAS 1 , 2, 3 ,4
//FALTA ARREGLAR
void mostrarPacientes(){
   system("cls");
   vector<paciente> todos;//es un arreglo pero me siento comodo usando vector, tons lo uso normal dx
   for(int i=0; i<contGeneral;i++){
    todos.push_back(camaGeneral[i]);
   }
   for(int i=0; i<contUCIN;i++){
    todos.push_back(camaUCIN[i]);
   }
   for(int i=0; i<contUCI;i++){
    todos.push_back(camaUCI[i]);
   }
    if(todos.empty()){// empty para ver si esta vacia
        gotoxy(5,5); cout << "No hay pacientes registrados por el momento.";
        getch();
        return;
    }
    const int cantpag=10; //cantidad de pacientes por pagina
    int tot=todos.size();
    int paginita=0;
    int totpag= (tot+cantpag-1)/cantpag;//es un redondeo para que se generen paginas dependiendo de cuantos internados hay
    char opcion;
    do{
        system("cls");
        gotoxy(5,2); cout << "LISTA DE PACIENTES - PAGINA " << (paginita+1) << " de " << totpag;
         gotoxy(5,3); cout << "--------------------------------------------------------------";
        gotoxy(5,4); cout << "Nombre\t\tDNI\tEdad\tSexo";
        gotoxy(5,5); cout << "--------------------------------------------------------------";

        int fila = 6;
        int inicio = paginita * cantpag;
        int fin = min(inicio + cantpag, tot);

        for(int i=inicio; i<fin; i++){
            gotoxy(5,fila+(i-inicio));  cout << todos[i].nombre;
            gotoxy(25,fila+(i-inicio)); cout << todos[i].DNI;
            gotoxy(40,fila+(i-inicio)); cout << todos[i].edad;
            gotoxy(50,fila+(i-inicio)); cout << todos[i].sexo;
        }

        gotoxy(5,20); cout << "[S] Siguiente - [A] Anterior - [B] Salir";
        opcion = tolower(getch());

        if(opcion=='s' && paginita < totpag-1) paginita++;
        else if(opcion=='a' && paginita > 0) paginita--;

    }while(opcion!='b');
    }








