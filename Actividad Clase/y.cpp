// y.cpp

#include <iostream>
#include <string>
#include "Criptografo.h"

using namespace std;

int main() {
    // Simulamos obtener las llaves de una base de datos o archivo de configuración
    string llavePublicaY = "llave_publica_y";
    string llavePrivadaY = "llave_privada_y";
    string llavePublicaX = "llave_publica_x";

    // Creamos una instancia de Criptografo para Y
    Criptografo criptografoY(llavePublicaY, llavePrivadaY);

    // Solicitamos el criptograma recibido
    string criptograma;
    cout << "Ingrese el criptograma recibido: ";
    getline(cin, criptograma);

    // Desciframos el mensaje
    string mensajeDescifrado = criptografoY.recibir(llavePublicaX, criptograma);

    // Mostramos el mensaje descifrado
    cout << "Mensaje descifrado: " << mensajeDescifrado << endl;

    return 0;
}