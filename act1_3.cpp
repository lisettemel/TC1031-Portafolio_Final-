
#include <iostream>
#include <string>
#include "bitacora.hpp" 
#include "conexiones.hpp"
#include "registros.hpp"
#include "LinkedList.hpp"
#include "node.hpp"
#include "stack.hpp"

using namespace std;



int main(){
    vector<Bitacora> registros = leerBitacora();
    int option;
    cout<<"------Menu Principal------"<<endl;
    cout<<"1. Informacion de Registros\n2. Informacion de Conexion "<<endl;
    cout<<"Elige una opcion: ";
    cin>>option;



    switch (option)
    {
    case 1:
         inicio(registros);
        break;

    case 2:
        main(registros);
        break;
    
    default:
        break;
    }
   
}

