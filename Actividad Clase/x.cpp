// x.cpp

#include <iostream>
#include <string>
#include "Criptografo.h"

using namespace std;

int main() {
    // Simulamos obtener las llaves de una base de datos o archivo de configuración
    string llavePublicaX = "llave_publica_x";
    string llavePrivadaX = "llave_privada_x";
    string llavePublicaY = "llave_publica_y";

    // Creamos una instancia de Criptografo para X
    Criptografo criptografoX(llavePublicaX, llavePrivadaX);

    // Solicitamos el mensaje a enviar
    string mensaje;
    cout << "Ingrese el mensaje a enviar: ";
    getline(cin, mensaje);

    // Generamos el criptograma
    string criptograma = criptografoX.enviar(llavePublicaY, mensaje);

    // Mostramos el criptograma generado
    cout << "Criptograma generado: " << criptograma << endl;

    return 0;
}