#ifndef registros_hpp
#define registros_hpp
#include <iostream>
#include <string>
#include <vector>
#include "bitacora.hpp"
#include <vector>
#include <set>

using namespace std;

int contarIndices(const vector<Bitacora>& registros) {
    // Contar los índices del vector
    int n = registros.size();
    return n;
}

int contarRegistrosPorDia(const vector<Bitacora>& bitacora) {
    int countSegundoDia = 0;
    string fechaPrimerDia = bitacora[0].getFecha();
    string fechaSegundoDia = "";

    bool segundoDiaEncontrado = false;

    for (const Bitacora& linea : bitacora) {
        if (linea.getFecha() == fechaPrimerDia) {
        } 
        else {
            if (!segundoDiaEncontrado) {
                fechaSegundoDia = linea.getFecha();
                segundoDiaEncontrado = true;
            }
            if (segundoDiaEncontrado && linea.getFecha() != fechaSegundoDia) {
                // Detener el contador si se ha agotado el segundo día
                break;
            }
            countSegundoDia++;
        }
    }

    // Imprimir la fecha del segundo día, si existe
    if (segundoDiaEncontrado) {
        cout << "Fecha del segundo día: " << fechaSegundoDia << endl;
        cout << "Número de registros del segundo día: " << countSegundoDia << endl;
    } else {
        cout << "No se encontró un segundo día en la bitácora." << endl;
    }

    return countSegundoDia;
}
Bitacora buscarRegistroPorNombre(const vector<Bitacora>& registros, const string& nombreABuscar) {
    Bitacora buscada("", "", "", 0, "", "", 0, ""); // Proporciona valores por defecto

    for (const Bitacora& registro : registros) {
        if (registro.getNombreOrigen() == nombreABuscar && registro.getIP_Origen() != "-") {
            buscada = registro;
            break; // Break out of the loop as soon as the target is found
        }
    }

    if (buscada.getNombreOrigen() != nombreABuscar) {
        cout << "No se encontró el nombre en el registro." << endl;
    }

    return buscada;
}

string IP_Interna(const vector<Bitacora>& registros) {
    string adress;
    string a;
    a="-";
    for (const Bitacora& linea : registros) {
        size_t puntoUno = linea.getIP_Origen().find('.');
        string octUno = linea.getIP_Origen().substr(0, puntoUno);
        size_t puntoDos = linea.getIP_Origen().find('.', puntoUno + 1);
        string octDos = linea.getIP_Origen().substr(puntoUno + 1, puntoDos - puntoUno - 1);
        size_t puntoTres = linea.getIP_Origen().find('.', puntoDos + 1);
        string octTres = linea.getIP_Origen().substr(puntoDos + 1, puntoTres - puntoDos - 1);
        adress = linea.getIP_Origen().substr(0, puntoTres); // Actualizar el valor de 'adress'

      if (adress!="-"||a!=adress){
        break;
      }
      else{
        a=adress;
      }
    }

    return adress; // Puedes devolver 'adress' aquí si es necesario
}

vector<int> puertos(const vector<Bitacora>& registros) {
    vector<int> Puerto;
    for (const Bitacora& linea : registros) {
        if (linea.getP_Destino() < 1000) {
            Puerto.push_back(linea.getP_Destino()); // Almacena el puerto en el vector
        }
    }
    int numElementos = Puerto.size();
    cout<<"El numero de puertos debajo de 1000 es: "<<numElementos<<endl;

    return Puerto;
}

vector<string> obtenerCorreos(const vector<Bitacora>& registros) {
    vector<string> Correos;
    set<string> CorreosUnicos; // Usamos un set para almacenar correos únicos

    for (const Bitacora& linea : registros) {
        string nombreDestino = linea.getNombreDestino();
        size_t lastDotPos = nombreDestino.find_last_of('.'); // Buscar el último punto
        if (lastDotPos != string::npos) {
            string correo = nombreDestino.substr(0, lastDotPos); // Obtener la parte antes del último punto
            if (CorreosUnicos.find(correo) == CorreosUnicos.end()) {
                Correos.push_back(correo);
                CorreosUnicos.insert(correo);
            }
        }
    }

    return Correos;
}

void buscarNombreOrigen(const vector<Bitacora>& bitacora) {
    bool Verificador = false;
    for (const Bitacora& linea : bitacora) {
        if (linea.getNombreDestino() == "server.reto.com") {
            Verificador = true; // Se encontró un elemento con nombreOrigen igual a "server.reto.com"
        }
    }

    if (Verificador) {
        cout << "Se encontró al menos un elemento con nombreOrigen igual a 'server.reto.com'" << endl;
    } else {
        cout << "No se encontró ningún elemento con nombreOrigen igual a 'server.reto.com'" << endl;
    }
}

int inicio(const std::vector<Bitacora>& registros) {
    
    cout << "\t-----Menu de opciones-----" << endl;
    cout << "1. Número total de registros\n2. Récords que hay del segundo día registrado\n3. IP de personas\n4. Dirección de la red interna de la compañía\n5. Computadoras llamadas server.reto.com\n6. Servicios de correo electrónico utilizados\n7. Puertos abajo del 1000" << endl;
    cout<<"Numero: ";
    int option;
    cin >> option;

    switch (option) {
        case 1: {
            cout << "El vector tiene " << contarIndices(registros) << " registros." << endl;
            break;
        }
        case 2: {
            int count = contarRegistrosPorDia(registros);
            break;
        }
        case 3: {
            string nom;
            cout << "Nombre: ";
            cin >> nom;
            string nombreABuscar = nom + ".reto.com";

            Bitacora registroEncontrado = buscarRegistroPorNombre(registros, nombreABuscar);

            if (!registroEncontrado.getNombreOrigen().empty()) {
                cout << "Registro encontrado: " << registroEncontrado.getNombreOrigen() << endl;
                cout << "IP: " << registroEncontrado.getIP_Origen() << endl;
            } else {
                cout << "Registro no encontrado." << endl;
            }
            break;
        }
        case 4: {
            string IP = IP_Interna(registros);
            cout << "Dirección de la red interna de la compañía: " << IP << endl;
            break;
        }
        case 5: {
            buscarNombreOrigen(registros);
            break;
        }
        case 6: {
            vector<string> Correos = obtenerCorreos(registros);

            if (!Correos.empty()) {
                cout << "Correos encontrados:" << endl;
                for (const string& correo : Correos) {
                    cout << correo << endl;
                }
            } else {
                cout << "No se encontraron correos en la bitácora." << endl;
            }

            break;
        }
        case 7: {
            vector<int> puertosEncontrados = puertos(registros);

            if (!puertosEncontrados.empty()) {
                cout << "Puertos encontrados:" << endl;
                for (int puerto : puertosEncontrados) {
                    cout << puerto << endl;
                }
            } else {
                cout << "No se encontraron puertos que cumplan con la condición." << endl;
            }
            break;
        }
        default:
            cout << "Opción no válida." << endl;
            break;
    }

    return 0;
}



#endif