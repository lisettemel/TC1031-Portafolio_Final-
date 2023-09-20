#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <set>

using namespace std;


class Bitacora {
protected:
    string fecha;
    string hora;
    string IP_Origen;
    int p_Origen;
    string nombreOrigen;
    string IP_Destino;
    int p_Destino;
    string nombreDestino;

public:
    Bitacora() {}

   Bitacora(std::string fecha_, std::string hora_, std::string IP_Origen_,
             int p_Origen_, std::string nombreOrigen_, std::string IP_Destino_,
             int p_Destino_, std::string nombreDestino_)
        : fecha(fecha_), hora(hora_), IP_Origen(IP_Origen_), p_Origen(p_Origen_),
          nombreOrigen(nombreOrigen_), IP_Destino(IP_Destino_),
          p_Destino(p_Destino_),
          nombreDestino(nombreDestino_) {
    }

    // Métodos para obtener los campos de la línea de bitácora
    string getFecha() const { return fecha; }
    string getHora() const { return hora; }
    string getIPOrigen() const { return IP_Origen; }
    int getPuertoOrigen() const { return p_Origen; }
    string getNombreOrigen() const { return nombreOrigen; }
    string getIPDestino() const { return IP_Destino; }
    int getPuertoDestino() const { return p_Destino; }
    string getNombreDestino() const { return nombreDestino; }

    bool compara(const Bitacora& other) const {
        return fecha < other.fecha;
    }

};



vector<Bitacora> readbitacora(const string& filename) {
    vector<Bitacora> bitacora; 
    ifstream file(filename);

    
    if (!file.is_open()) {
        throw runtime_error("No se puede abrir el archivo");
    }

    string linea;

    while (getline(file, linea)) {
        stringstream ss(linea);
        string fecha, hora, IP_Origen, nombreOrigen, IP_Destino, nombreDestino;
        int p_Origen, p_Destino;

        getline(ss, fecha, ',');
        getline(ss, hora, ',');
        getline(ss, IP_Origen, ',');
        ss >> p_Origen;
        ss.ignore(); 
        getline(ss, nombreOrigen, ',');
        getline(ss, IP_Destino, ',');
        ss >> p_Destino;
        ss.ignore(); 
        getline(ss, nombreDestino, ',');

        
        bitacora.emplace_back(fecha, hora, IP_Origen, p_Origen, nombreOrigen,
        IP_Destino, p_Destino, nombreDestino);
    }

   
    file.close();

    return bitacora;
}




// Función para realizar el merge de dos subarrays ordenados
template <typename T>
void merge(vector<T>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<T> leftArr(n1);
    vector<T> rightArr(n2);

    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }

    for (int i = 0; i < n2; i++) {
        rightArr[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i].compara(rightArr[j])) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Función recursiva para realizar el Merge Sort
template <typename T>
void mergeSort(vector<T>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int contarRegistrosPorDia(const vector<Bitacora>& bitacora) {
    int count = 0;
    string fechaPrimerDia = bitacora[0].getFecha();
    string fechaSegundoDia = "";

    for (const Bitacora& linea : bitacora) {
        if (linea.getFecha() != fechaPrimerDia) {
            fechaSegundoDia = linea.getFecha();
            break;
        } else {
            count++;
        }
    }

    // Imprimir el número de registros del primer día
    cout << "Número de registros del primer día: " << count << endl;

    // Imprimir la fecha del segundo día, si existe
    if (!fechaSegundoDia.empty()) {
        cout << "Fecha del segundo día: " << fechaSegundoDia << endl;
    } else {
        cout << "No se encontró un segundo día en la bitácora." << endl;
    }

    return count;
}

//Contar registros del segundo dia 
int contarRegistrosDelSegundoDia(const vector<Bitacora>& bitacora) {
    int count = 0;
    string fechaPrimerDia = bitacora[0].getFecha();
    string fechaSegundoDia = "";

    bool segundoDiaEncontrado = false;

    for (const Bitacora& linea : bitacora) {
        if (!segundoDiaEncontrado && linea.getFecha() != fechaPrimerDia) {
            fechaSegundoDia = linea.getFecha();
            segundoDiaEncontrado = true;  // Marcar que se encontró el segundo día
        }

        if (segundoDiaEncontrado && linea.getFecha() == fechaSegundoDia) {
            count++;
        }
    }

    // Imprimir el número de registros del segundo día
    cout << "Número de registros del segundo día: " << count << endl;

    if (!segundoDiaEncontrado) {
        cout << "No se encontró un segundo día en la bitácora." << endl;
    }

    return count;
}

vector<string> findComputadorasPorPersona(const vector<Bitacora>& bitacora, const string& nombrePersona) {
    vector<string> computadoras;

    for (const Bitacora& linea : bitacora) {
        // Obtener el nombre de origen sin el dominio
        size_t pos = linea.getNombreOrigen().find('.');
        if (pos != string::npos) {
            string nombreOrigenSinDominio = linea.getNombreOrigen().substr(0,pos);
            
            if (nombreOrigenSinDominio == nombrePersona) {
                // Agregar la IP de origen de esta línea (computadora) a la lista
                computadoras.push_back(linea.getIPOrigen());
            }
        }
    }

    return computadoras;
}

//Funcion para obtener la IP_Interna

string IP_Interna(const vector<Bitacora>& bitacora) {
    if (bitacora.empty()) {
        throw runtime_error("El vector de bitácora está vacío");
    }

    string ipOrigen = bitacora[0].getIPOrigen();
    size_t lastDotPos = ipOrigen.find_last_of('.');  // Buscar la última posición del punto
    if (lastDotPos != string::npos) {
        string IP = ipOrigen.substr(0, lastDotPos);  // Obtener la parte antes del último punto
        return IP;
    } else {
        throw runtime_error("No se encontró un punto en la dirección IP de origen");
    }
}
//Buscar nombre de server.reto.com
void buscarNombreOrigen(const vector<Bitacora>& bitacora) {
  bool Verificador=false;
    for (const Bitacora& linea : bitacora) {
        if (linea.getNombreOrigen() == "server.reto.com") {
           Verificador=true;// Se encontró un elemento con nombreOrigen igual a "server.reto.com"
        }
    }

      if (Verificador) {
            cout << "Se encontró al menos un elemento con nombreOrigen igual a 'server.reto.com'" << endl;
        } else {
            cout << "No se encontró ningún elemento con nombreOrigen igual a 'server.reto.com'" << endl;
        }
  
    
}

//Funcion para encontrar correos
vector<string> obtenerCorreos(const vector<Bitacora>& bitacora) {
    vector<string> Correos;
    set<string> CorreosUnicos; // Usamos un set para almacenar correos únicos

    for (const Bitacora& linea : bitacora) {
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


// //Funcionamiento busqueda de correos basado en el nombreDestino
// int main() {
//     string registro = "equipo6.csv";

   
//         vector<Bitacora> bitacora = readbitacora(registro);

//         vector<string> Correos = obtenerCorreos(bitacora);

//         if (!Correos.empty()) {
//             cout << "Correos encontrados:" << endl;
//             for (const string& correo : Correos) {
//                 cout << correo << endl;
//             }
//         } else {
//             cout << "No se encontraron correos en la bitácora." << endl;
//         }

    
//     return 0;
// }

//Funcionamiento de la busqueda de la IP de la red
// int main() {
//   string registro = "equipo6.csv"; 
    
//       vector<Bitacora> bitacora = readbitacora(registro);
//        // Ordenar la bitácora por fecha utilizando Merge Sort
//        mergeSort(bitacora, 0, bitacora.size() - 1);

//         string IP = IP_Interna(bitacora);
//         cout << "IP interna: " << IP << endl;

//     return 0;
// }





// int main() {
//   string registro = "equipo6.csv"; 
//     try {
//       vector<Bitacora> bitacora = readbitacora(registro);
//        // Ordenar la bitácora por fecha utilizando Merge Sort
//        mergeSort(bitacora, 0, bitacora.size() - 1);
      
//       int count = contarRegistrosPorDia(bitacora);

//       string nombrePersonaABuscar = "amy"; // Cambia esto al nombre que desees buscar
//       vector<string> computadoras = findComputadorasPorPersona(bitacora, nombrePersonaABuscar);
//        if (!computadoras.empty()) {
//             cout << "Las computadoras pertenecientes a " << nombrePersonaABuscar << " son:" << endl;
//             for (const string& computadora : computadoras) {
//                 cout << computadora << endl;
//             }
//         } else {
//             cout << "No se encontraron registros para " << nombrePersonaABuscar << "." << endl;
//         }

      
    
//     } 
//     catch (const exception& e) {
//     cerr << "Error: " << e.what() << endl;
//     }

//     return 0;
// }

