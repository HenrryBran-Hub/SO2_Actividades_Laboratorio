// Criptografo.h

#ifndef CRIPTOGRAFO_H
#define CRIPTOGRAFO_H

#include <string>

using namespace std;

class Criptografo {
public:
    Criptografo(string llvPub, string llvPriv);
    
    /** genera el criptograma para enviar un mensaje certificado usando las
    llaves propias y la llave del destinatario llvDestinatario */
    string enviar(string llvDestinatario, string mensaje);
    
    /** Recibe un criptograma certificado usando las llaves propias y la llave
    del remitente llvRemitente y genera el mensaje recibido*/
    string recibir(string llvRemitente, string criptograma);

private:
    string llvPublica, llvPrivada;

    /** devuelve el criptograma correspondiente a la encripción RSA del mensaje
    con la llave llv pública o privada */
    string encriptaRSA(string llv, const char *mensaje);

    /** devuelve el mensaje correspondiente a la desencripción RSA del
    criptograma con la llave llv pública o privada */
    string desencriptaRSA(string llv, string criptograma);

    /** devuelve el criptograma correspondiente a la encripción AES del mensaje
    con la llave llv pública o privada */
    string encriptaAES(string llv, const char *mensaje);

    /** devuelve el mensaje correspondiente a la desencripción AES del
    criptograma con la llave llv pública o privada */
    string desencriptaAES(string llv, string criptograma);

    /** genera una llave de sesión aleatoria */
    string sesion();
};

#endif // CRIPTOGRAFO_H