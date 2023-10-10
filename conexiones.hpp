#ifndef conexiones_hpp
#define conexiones_hpp
#include <iostream>
#include "Stack.hpp"
#include "node.hpp"
#include "bitacora.hpp"
#include "registros.hpp"
#include"LinkedList.hpp"
using namespace std;


#include <string>


template <class T>
class ConexionesComputadora{
private:
    string ip = "";
    string Nombre="";
    string direccionIP= "";
    Stack<Bitacora> * conexionesEntrantes = new Stack<Bitacora>();
    LinkedList<Bitacora> * conexionesSalientes = new LinkedList<Bitacora>();



public:
    ConexionesComputadora() {}
     ConexionesComputadora(const string& _IP, const string& _Nombre, const vector<Bitacora>& registros)
        : ip(_IP), Nombre(_Nombre) {llenarConexiones(registros, direccionIP);}

    Stack<Bitacora> * getConexionesEntrantes();
    LinkedList<Bitacora> * getConexionesSalientes();

    
    void llenarConexiones(const vector<Bitacora>& registros, string direccionIP);  

    int totalConexionesEntrantes();
    int totalConexionesSalientes();
    T ultimaConexion(const vector<Bitacora>& registros);
    bool tresConexiones(const vector<Bitacora>& registros, const string& sitioWebEvaluado);

    string IP_web(const vector<Bitacora>& registros);

    string IP(const vector<Bitacora>& registros, int numero); 


    // Destructor
    ~ConexionesComputadora() {
        delete conexionesEntrantes;
        delete conexionesSalientes;
    }



};

template <class T>
void ConexionesComputadora<T>::llenarConexiones(const vector<Bitacora>& registros, string direccionIP) {
    for (const Bitacora& registro : registros) {
        if (registro.getIP_Origen() == direccionIP) {
            conexionesEntrantes->push(registro); // Registrar conexiones entrantes en la pila
            cout << "Added an incoming connection: " << registro.getIP_Origen() << endl; // Imprimir la conexión agregada
        } else if (registro.getIP_Destino() == direccionIP) {
            conexionesSalientes->insert_back(registro); // Registrar conexiones salientes en la lista enlazada
            cout << "Added an outgoing connection: " << registro.getIP_Destino() << endl; // Imprimir la conexión agregada
        }
    }
}

template <class T>
T ConexionesComputadora<T>::ultimaConexion(const vector<Bitacora>& registros) {
    T ultimaIP; // Esta variable almacenará la última dirección IP encontrada

    for (const Bitacora& registro : registros) {
        if (registro.getIP_Destino() == ip) {
            ultimaIP = registro.getIP_Origen();
        }
    }

    return ultimaIP;
}



template <class T>
int ConexionesComputadora<T>::totalConexionesSalientes() {
    return conexionesSalientes->size();
    }


template <class T>
int ConexionesComputadora<T>::totalConexionesEntrantes() {
    return conexionesEntrantes->size();
}


template <class T>
bool ConexionesComputadora<T>::tresConexiones(const vector<Bitacora>& registros, const string& redEvaluada) {
    int conexionesSeguidas = 0;

    for (const Bitacora& registro : registros) {
        // Obtener la dirección IP de destino
        string ipDestino = registro.getIP_Destino();

        // Separar la dirección IP en componentes (a.b.c)
        size_t puntoUno = ipDestino.find('.');
        string a = ipDestino.substr(0, puntoUno);
        size_t puntoDos = ipDestino.find('.', puntoUno + 1);
        string b = ipDestino.substr(puntoUno + 1, puntoDos - puntoUno - 1);
        size_t puntoTres = ipDestino.find('.', puntoDos + 1);
        string c = ipDestino.substr(puntoDos + 1, puntoTres - puntoDos - 1);

        // Comprobar si la dirección IP de destino coincide con la red evaluada (a.b.c)
        if (a + "." + b + "." + c == redEvaluada) {
            conexionesSeguidas++;
            if (conexionesSeguidas == 3) {
                return true; // Se encontraron 3 conexiones seguidas a la misma red.
            }
        } else {
            conexionesSeguidas = 0; // Restablecer el contador si la dirección IP de destino no coincide.
        }
    }

    return false; // No se encontraron 3 conexiones seguidas a la misma red (a.b.c).
}



string IP(const vector<Bitacora>& registros, int numero) {
    if (numero < 1 || numero > 150) {
        cout << "El número debe estar en el rango de 1 a 150." << endl;
        return ""; // número inválido
    }

    string direccionRed = IP_Interna(registros);
    
    // Dividir la dirección de red en sus componentes
    size_t puntoUno = direccionRed.find('.');
    string octUno = direccionRed.substr(0, puntoUno);
    size_t puntoDos = direccionRed.find('.', puntoUno + 1);
    string octDos = direccionRed.substr(puntoUno + 1, puntoDos - puntoUno - 1);
    size_t puntoTres = direccionRed.find('.', puntoDos + 1);
    string octTres = direccionRed.substr(puntoDos + 1, puntoTres - puntoDos - 1);

    // Construir la dirección IP con el formato deseado
    string ipInterna = octUno + "." + octDos + "." + octTres + "." + to_string(numero);
    return ipInterna;
}




int numero;


int run(const vector<Bitacora>& registros) {
    ConexionesComputadora<string> conexiones;

    cout << "Ingresa un número entre 1 y 150: ";
    cin >> numero;

    if (numero >= 1 && numero <= 150) {
        string direccionRed = IP_Interna(registros);
        string direccionIP = IP(registros, numero);
        cout << "Dirección IP interna con número " << numero << ": " << direccionIP << endl;
        conexiones.llenarConexiones(registros, direccionIP); // Utiliza la direcciónIP calculada aquí
    } else {
        cout << "El número debe estar en el rango de 1 a 150." << endl;
    }

    int option;

    cout << "1. Obtener la dirección IP actual y sus conexiones." << endl;
    cout << "Ingresa una opcion:";
    cin >> option;

    switch (option) {
        case 1: {
            // ¿Cuál fue la dirección IP de la última conexión que recibió esta computadora?
            string ultimaDireccionIP = conexiones.ultimaConexion(registros);
            if (!ultimaDireccionIP.empty()) {
                cout << "La dirección IP de la última conexión entrante fue: " << ultimaDireccionIP << endl;
            } else {
                cout << "No se encontraron conexiones entrantes." << endl;
            }
            break;
        }
        case 2: {
            int totalEntrantes = conexiones.totalConexionesEntrantes(); // Debes usar la instancia de conexiones
            cout << "La computadora tiene " << totalEntrantes << " conexiones entrantes." << endl;
            break;
        }
        case 3: {
            // ¿Cuántas conexiones salientes tiene esta computadora?
            int totalSalientes = conexiones.totalConexionesSalientes();
            cout << "La computadora tiene " << totalSalientes << " conexiones salientes." << endl;
            break;
        }
        case 4: {
            // ¿Tiene esta computadora 3 conexiones seguidas a un mismo sitio web?
            string redEvaluada;
            redEvaluada = IP_Interna(registros);
            if (conexiones.tresConexiones(registros, redEvaluada)) {
                cout << "Esta computadora tiene 3 conexiones seguidas a la red " << redEvaluada << endl;
            } else {
                cout << "No se encontraron 3 conexiones seguidas a la red " << redEvaluada << endl;
            }
            break;
        }
        default: {
            cout << "Opción no válida." << endl;
            break;
        }
    }

    return 0;
}


#endif
