#ifndef BITACORA_HPP
#define BITACORA_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class Bitacora {
private:
    std::string fecha;
    std::string hora;
    std::string IP_Origen;
    int p_Origen;
    std::string nombreOrigen;
    std::string IP_Destino;
    int p_Destino;
    std::string nombreDestino;

public:
    // Constructor de Bitacora
    Bitacora(const std::string& _fecha, const std::string& _hora, const std::string& _IP_Origen, int _p_Origen,
             const std::string& _nombreOrigen, const std::string& _IP_Destino, int _p_Destino, const std::string& _nombreDestino)
        : fecha(_fecha), hora(_hora), IP_Origen(_IP_Origen), p_Origen(_p_Origen),
          nombreOrigen(_nombreOrigen), IP_Destino(_IP_Destino), p_Destino(_p_Destino), nombreDestino(_nombreDestino) {}

    std::string getFecha() const { return fecha; }
    std::string getHora() const { return hora; }
    std::string getIP_Origen() const { return IP_Origen; }
    int getP_Origen() const { return p_Origen; }
    std::string getNombreOrigen() const { return nombreOrigen; }
    std::string getIP_Destino() const { return IP_Destino; }
    int getP_Destino() const { return p_Destino; }
    std::string getNombreDestino() const { return nombreDestino; }
    bool operator!=(const Bitacora& other) const;
    bool operator==(const Bitacora& other) const;



};

bool Bitacora::operator!=(const Bitacora& other) const {
    return (nombreOrigen != other.nombreOrigen || fecha != other.fecha);
}

bool Bitacora::operator==(const Bitacora& other) const {
    return (nombreOrigen == other.nombreOrigen && fecha == other.fecha);
}


// Función para leer la bitácora desde un archivo CSV y almacenarla en un vector
std::vector<Bitacora> leerBitacora() {
    std::ifstream arch("equipo6.csv");
    if (!arch.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo equipo6.csv" << std::endl;
        // Puedes manejar el error de otra manera, como lanzar una excepción o retornar un valor apropiado.
        exit(1);
    }

    char delimitador = ',';
    std::string linea;
    std::vector<Bitacora> registros; // Vector para almacenar los registros

    while (getline(arch, linea)) {
        std::stringstream ss(linea);
        std::string fecha, hora, ipOrigen, nombreOrigen, ipDestino, nombreDestino;
        int puertoOrigen, puertoDestino;

        getline(ss, fecha, delimitador);
        getline(ss, hora, delimitador);
        getline(ss, ipOrigen, delimitador);
        ss >> puertoOrigen;
        ss.ignore(); 
        getline(ss, nombreOrigen, delimitador);
        getline(ss, ipDestino, delimitador);
        ss >> puertoDestino;
        ss.ignore(); 
        getline(ss, nombreDestino, delimitador);

        registros.emplace_back(fecha, hora, ipOrigen, puertoOrigen, nombreOrigen, ipDestino, puertoDestino, nombreDestino);
    }

    arch.close();
    return registros;
}

#endif
