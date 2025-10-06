#ifndef VAL_H
#define VAL_H

#include <fstream>
#include <limits>
#include "graphics.h"

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

string clavesita();
string leerLinea(const string&);
bool validarDNI(int);
int leerEntero(const string&, int, int, int, int);
void guardarGrupo(ofstream &, paciente*, int);
void guardarPacientes();
void ingresoMedico();
void ingresoPaciente();
void cargarPacientes();
void mostrarPaciente();
bool borrarDe(paciente*, int&, int);
void borrarPaciente();

string clavesita(){
  string contra;
  char caractersito;
  while(true){
         caractersito=getch();
         if(caractersito==13){
    break;
         }       
         else if(caractersito==8){
    if(!contra.empty()){//evalua si la cadena esta vacia
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

string leerLinea(const string& mensaje) {
    string texto;
    cout << mensaje;
    getline(cin >> ws, texto); // limpia espacios, luego lee la línea
    return texto;
}

bool validarDNI(int dni){
    
    for(int i=0;i<contGeneral;i++){
        if(dni==camaGeneral[i].DNI){
            gotoxy(35,6);cout<<"Este DNI ya ha sido registrado";
            getch();
            return false;
        }
    }
    for(int i=0;i<contUCIN;i++){
        if(dni==camaUCIN[i].DNI){
            gotoxy(35,6);cout<<"Este DNI ya ha sido registrado";
            getch();
            return false;
        }
    } 
    for(int i=0;i<contUCI;i++){
        if(dni==camaUCI[i].DNI){
            gotoxy(35,6);cout<<"Este DNI ya ha sido registrado";
            getch();
            return false;
        }
    } 
    return true;

}

int leerEntero(const string& mensaje, int min, int max, int colu, int fila) {
    int valor;
    while (true) {
        gotoxy(colu,fila); cout << mensaje;
        if (cin >> valor) {
            if (valor >= min && valor <= max) return valor;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        gotoxy(colu,fila);cout<<"                                                    ";//se necesita antes y despues
        gotoxy(colu,fila);cout << "Valor invalido. Intenta de nuevo.\n";
        getch();
        gotoxy(colu,fila);cout<<"                                                    ";//esto es para limpiar la linea
    }
}

void guardarGrupo(ofstream &arch, paciente *arr, int cantidad) {
    for (int i = 0; i < cantidad; ++i)
        arch << arr[i].nombre << "\n" << arr[i].DNI << "\n"
             << arr[i].edad << "\n" << arr[i].sexo << "\n"
             << arr[i].gravedad << "\n";
}

// Guarda todos los pacientes en un archivo de texto
void guardarPacientes() {
    ofstream archivo("pacientes.txt");
    if (!archivo) {
        cout << "Error al abrir el archivo para guardar." << endl;
        return;
    }

    archivo << contGeneral << " " << contUCIN << " " << contUCI << "\n";

    guardarGrupo(archivo, camaGeneral, contGeneral);
    guardarGrupo(archivo, camaUCIN, contUCIN);
    guardarGrupo(archivo, camaUCI, contUCI);
    
    archivo.close();
}

void ingresoMedico(){
    int contador=0;
    string codigo="1", contra="2";
    string ingreso_codigo, ingreso_contra;

    do{
        gotoxy(35,5);cout<<"INGRESE CODIGO MEDICO: "; 
		getline(cin, ingreso_codigo);
		
        gotoxy(35,7);cout<<"INGRESE CONTRASENA: "; 
            ingreso_contra=clavesita();
        
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
    int dni;

	for(int i=30; i<=90; i++){   
        gotoxy(i,2); cout << char(205);
         gotoxy(i,15); cout << char(205); }
         
    for(int j=2; j<=15; j++){   
        gotoxy(30,j); cout << char(186);
        gotoxy(90,j); cout << char(186);  }
	
        gotoxy(30,2); cout << char(201);  
        gotoxy(90,2); cout << char(187);  
        gotoxy(30,15); cout << char(200); 
        gotoxy(90,15); cout << char(188); 
	

    gotoxy(35,3);cout << "INGRESO DEL PACIENTE";
    //NOMBRE
    gotoxy(35,5);nuevo.nombre = leerLinea("Ingrese su nombre: ");

    //DNI
    do{ 
        gotoxy(35,6);cout<<"                                        ";//esto es para limpiar la linea
        dni=leerEntero("DNI: ", 10000000, 99999999,35,6);//los 2 ultimos numeros son columna y fila respectivamente
        
    }while(validarDNI(dni)==false);//false.. hay un dni igual
    nuevo.DNI =dni;

    //EDAD
    nuevo.edad = leerEntero("Edad: ", 1, 120,35,7);

    //SEXO

    do{ 
        gotoxy(35,8);cout<<"                                        ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        gotoxy(35,8);cout <<"Sexo(M/F): "; cin >> nuevo.sexo;

    }while (cin.fail() || 
        (nuevo.sexo != "M" && nuevo.sexo != "F" && 
         nuevo.sexo != "m" && nuevo.sexo != "f"));
    

    //GRAVEDAD
	nuevo.gravedad = leerEntero("Nivel de gravedad [1-General | 2-UCIN | 3-UCI]: ", 1, 3,35,9);

    
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
    guardarPacientes(); // Guarda automáticamente después de agregar
    getch();
}

//Carga los pacientes desde el archivo de texto
void cargarPacientes() {
    ifstream archivo("pacientes.txt");
    if (!archivo) return; // Si no existe, no hay nada que cargar

    archivo >> contGeneral >> contUCIN >> contUCI;
    archivo.ignore(); // para evitar que quede un salto de línea pendiente

    for (int i = 0; i < contGeneral; i++) {
        getline(archivo, camaGeneral[i].nombre);
        archivo >> camaGeneral[i].DNI;
        archivo >> camaGeneral[i].edad;
        archivo >> camaGeneral[i].sexo;
        archivo >> camaGeneral[i].gravedad;
        archivo.ignore();
    }

    for (int i = 0; i < contUCIN; i++) {
        getline(archivo, camaUCIN[i].nombre);
        archivo >> camaUCIN[i].DNI;
        archivo >> camaUCIN[i].edad;
        archivo >> camaUCIN[i].sexo;
        archivo >> camaUCIN[i].gravedad;
        archivo.ignore();
    }

    for (int i = 0; i < contUCI; i++) {
        getline(archivo, camaUCI[i].nombre);
        archivo >> camaUCI[i].DNI;
        archivo >> camaUCI[i].edad;
        archivo >> camaUCI[i].sexo;
        archivo >> camaUCI[i].gravedad;
        archivo.ignore();
    }

    archivo.close();
}

void mostrarPacientes() {
    int grupo = 0; // 0 = General, 1 = UCIN, 2 = UCI
    int inicio = 0; // índice de inicio para mostrar
    const int porPagina = 10;
    char tecla;

    while (true) {
        system("cls");
        string nombreGrupo;
        paciente* arr;
        int cantidad;

        // Seleccionar grupo según el valor de 'grupo'
        switch (grupo) {
            case 0: arr = camaGeneral; cantidad = contGeneral; nombreGrupo = "CAMA GENERAL"; break;
            case 1: arr = camaUCIN; cantidad = contUCIN; nombreGrupo = "UCIN"; break;
            case 2: arr = camaUCI; cantidad = contUCI; nombreGrupo = "UCI"; break;
        }

        gotoxy(5,2); cout << "LISTA DE PACIENTES - " << nombreGrupo;
        gotoxy(5,3); cout << "--------------------------------------------------------------";
        gotoxy(5,4); cout << "NOMBRE";
        gotoxy(37,4);cout << "DNI";
        gotoxy(49,4);cout << "EDAD";
        gotoxy(56,4);cout << "SEXO";
        gotoxy(5,5); cout << "--------------------------------------------------------------";

        if (cantidad == 0) {
            gotoxy(5,7); cout << "No hay pacientes en este grupo.";
        } else {
            int fin = min(inicio + porPagina, cantidad);
            int fila = 6;
            for (int i = inicio; i < fin; i++) {
                gotoxy(5, fila + (i - inicio));  cout << arr[i].nombre;
                gotoxy(35, fila + (i - inicio)); cout << arr[i].DNI;
                gotoxy(50, fila + (i - inicio)); cout << arr[i].edad;
                gotoxy(58, fila + (i - inicio)); cout << arr[i].sexo;
            }
        }

        gotoxy(5,20);
        cout << "[?/?] Desplazar  [?/?] Cambiar grupo  [B] Volver";

        tecla = getch();

        // Navegación dentro del grupo
        if (tecla == 72 && inicio > 0) { // ?
            inicio--;
        } 
        else if (tecla == 80 && inicio + porPagina < cantidad) { // ?
            inicio++;
        } 
        // Cambiar grupo
        else if (tecla == 75) { // ?
            grupo = (grupo - 1 + 3) % 3;
            inicio = 0;
        } 
        else if (tecla == 77) { // ?
            grupo = (grupo + 1) % 3;
            inicio = 0;
        } 
        // Salir
        else if (tolower(tecla) == 'b') {
            break;
        }
    }
}

bool borrarDe(paciente* arr, int &cont, int dni) {
    for (int i = 0; i < cont; i++) {
        if (arr[i].DNI == dni) {
            for (int j = i; j < cont - 1; j++)
                arr[j] = arr[j + 1];
            cont--;
            return true;
        }
    }
    return false;
}

// Eliminar un paciente por su DNI 
void borrarPaciente() {
    system("cls");
    gotoxy(35,5); cout << "Ingrese el DNI del paciente a eliminar: ";
    int dni;
    cin >> dni;

    bool eliminado = borrarDe(camaGeneral, contGeneral, dni)
              || borrarDe(camaUCIN, contUCIN, dni)
              || borrarDe(camaUCI, contUCI, dni);

    if (eliminado) {
        gotoxy(35,7); cout << "Paciente eliminado correctamente.";
        guardarPacientes(); // actualiza el archivo
    } else {
        gotoxy(35,7); cout << "No se encontro ningun paciente con ese DNI.";
    }

    getch();
}

#endif
