#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;



class Bitacora{
public:
    string fecha;
    string hora;
    string IP_Orgen;
    int p_Origen;
    string nombreOrigen;
    string IP_Destino;
    int p_Destino;
    string nombreDestino;
};

template <class T>
void quicksort(T a[], int primero, int ultimo) {
    int izquierdo = primero;
    int derecho = ultimo;

    // Se selecciona pivote
    T pivote = a[primero];

    if (primero < ultimo) // paso base
    {
        // partición
        while (izquierdo < derecho) {
            while ((izquierdo < derecho) && compararPorFecha(a[izquierdo], pivote)) izquierdo++;
            while (compararPorFecha(pivote, a[derecho])) derecho--;
            if (izquierdo < derecho) // se intercambian los contenidos
            {
                std::swap(a[izquierdo], a[derecho]);
            }
        }
        // Se intercambia el pivote con el elemento de la posición derecha
        std::swap(a[primero], a[derecho]);

        // Paso recursivo
        quicksort(a, primero, derecho - 1);
        quicksort(a, izquierdo, ultimo);
    }
}

int main(){
    ifstream arch("equipo6.csv");
    char delimitador = ',';
    string linea;
    int contadorRegistros=0;

    vector<Bitacora> registros; // Vector para almacenar los registros

    while (getline(arch, linea)) {
        Bitacora registro;
        stringstream ss(linea);
        //string token;

        // Lee y asigna cada columna al objeto Bitacora
        getline(ss, registro.fecha, delimitador);
        getline(ss, registro.hora, delimitador);
        getline(ss, registro.IP_Orgen, delimitador);
        ss >> registro.p_Origen;
        ss.ignore(); // Ignora la coma
        getline(ss, registro.nombreOrigen, delimitador);
        getline(ss, registro.IP_Destino, delimitador);
        ss >> registro.p_Destino;
        ss.ignore(); // Ignora la coma
        getline(ss, registro.nombreDestino);

        registros.push_back(registro);

        contadorRegistros++;
    }
    
    cout<<contadorRegistros;

    return 0;

}