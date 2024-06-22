#include "Criptografo.h"
#include <iostream>
#include <algorithm>

Criptografo::Criptografo(std::string llvPub, std::string llvPriv) : llvPublica(llvPub), llvPrivada(llvPriv) {}

std::string Criptografo::enviar(std::string llvDestinatario, std::string mensaje) {
    // Generar una llave de sesión aleatoria
    std::string llaveSesion = sesion();
    
    // Encriptar el mensaje con la llave de sesión usando AES
    std::string mensajeEncriptado = encriptaAES(llaveSesion, mensaje.c_str());
    
    // Encriptar la llave de sesión con la llave pública del destinatario usando RSA
    std::string llaveSesionEncriptada = encriptaRSA(llvDestinatario, llaveSesion.c_str());
    
    // Firmar el mensaje encriptado con la llave privada propia usando RSA
    std::string firma = encriptaRSA(llvPrivada, mensajeEncriptado.c_str());
    
    // Combinar todos los elementos en un solo criptograma
    return llaveSesionEncriptada + "|" + mensajeEncriptado + "|" + firma;
}

std::string Criptografo::recibir(std::string llvRemitente, std::string criptograma) {
    // Separar los componentes del criptograma
    size_t pos1 = criptograma.find("|");
    size_t pos2 = criptograma.find("|", pos1 + 1);
    
    std::string llaveSesionEncriptada = criptograma.substr(0, pos1);
    std::string mensajeEncriptado = criptograma.substr(pos1 + 1, pos2 - pos1 - 1);
    std::string firma = criptograma.substr(pos2 + 1);
    
    // Desencriptar la llave de sesión con la llave privada propia
    std::string llaveSesion = desencriptaRSA(llvPrivada, llaveSesionEncriptada);
    
    // Verificar la firma con la llave pública del remitente
    std::string mensajeVerificado = desencriptaRSA(llvRemitente, firma);
    
    if (mensajeVerificado != mensajeEncriptado) {
        return "Error: La firma no es válida.";
    }
    
    // Desencriptar el mensaje con la llave de sesión
    return desencriptaAES(llaveSesion, mensajeEncriptado);
}

// Funciones auxiliares para cifrado por desplazamiento
std::string cifradoDesplazamiento(const std::string &texto, int desplazamiento) {
    std::string resultado = texto;
    std::transform(resultado.begin(), resultado.end(), resultado.begin(), [desplazamiento](unsigned char c) -> unsigned char {
        if (std::isalnum(c)) {
            if (std::isupper(c)) {
                return 'A' + (c - 'A' + desplazamiento + 26) % 26;
            } else if (std::islower(c)) {
                return 'a' + (c - 'a' + desplazamiento + 26) % 26;
            } else if (std::isdigit(c)) {
                return '0' + (c - '0' + desplazamiento + 10) % 10;
            }
        }
        return c;
    });
    return resultado;
}

std::string descifradoDesplazamiento(const std::string &texto, int desplazamiento) {
    return cifradoDesplazamiento(texto, -desplazamiento);
}

// Implementaciones para los métodos de encriptación y desencriptación
std::string Criptografo::encriptaRSA(std::string llv, const char *mensaje) {
    // Implementación simple usando cifrado por desplazamiento
    return cifradoDesplazamiento(std::string(mensaje) + "_RSA_" + llv, 3);
}

std::string Criptografo::desencriptaRSA(std::string llv, std::string criptograma) {
    // Implementación simple usando cifrado por desplazamiento
    std::string descifrado = descifradoDesplazamiento(criptograma, 3);
    return descifrado.substr(0, descifrado.find("_RSA_"));
}

std::string Criptografo::encriptaAES(std::string llv, const char *mensaje) {
    // Implementación simple usando cifrado por desplazamiento
    return cifradoDesplazamiento(std::string(mensaje) + "_AES_" + llv, 3);
}

std::string Criptografo::desencriptaAES(std::string llv, std::string criptograma) {
    // Implementación simple usando cifrado por desplazamiento
    std::string descifrado = descifradoDesplazamiento(criptograma, 3);
    return descifrado.substr(0, descifrado.find("_AES_"));
}

std::string Criptografo::sesion() {
    // Implementación de prueba simple
    return "llave_sesion_aleatoria";
}
