#include "presentation/ConsoleUI.hpp"

#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "application/DroneController.hpp"

ConsoleUI::ConsoleUI(DroneController* controller) : controller_(controller) {}

void ConsoleUI::run() {
    if (!controller_) {
        std::cerr << "Error: ConsoleUI iniciada con un controlador nulo." << std::endl;
        return;
    }

    std::cout << "\n╔═══════════════════════════════════════╗\n";
    std::cout << "║     DRONE IBag151 - Panel de Control  ║\n";
    std::cout << "╚═══════════════════════════════════════╝\n";
    
    displayMenu();
    
    std::string input;
    while (true) {
        std::cout << "\n> ";
        std::getline(std::cin, input);
        
        if (input.empty()) continue;
        
        std::string command = toLowerCase(input);
        if (command == "salir" || command == "exit") {
            std::cout << "Saliendo del panel de control.\n";
            std::cout << "Copyright © 2025 GuarigliaTech una division de ISFT151 Corps.\n";
            std::cout << "Contrataciones: jose.oemig@isft151corps.ceo.ar\n";
            break;
        }
        
        processCommand(input);
    }
}

void ConsoleUI::displayMenu() const {
    std::cout << "\nComandos disponibles (español/inglés):\n";
    std::cout << "  despegar / takeoff                    - Despegar el dron\n";
    std::cout << "  aterrizar / land                      - Aterrizar el dron\n";
    std::cout << "  subir [metros] / elevate [meters]     - Elevar altura (default: 5m)\n";
    std::cout << "  bajar [metros] / descend [meters]     - Bajar altura (default: 5m)\n";
    std::cout << "  derecha [grados] / turn-right [degrees] - Girar derecha (default: 45°)\n";
    std::cout << "  izquierda [grados] / turn-left [degrees] - Girar izquierda (default: 45°)\n";
    std::cout << "  acelerar [velocidad] / accelerate [speed]     - Acelerar (default: 5 m/s)\n";
    std::cout << "  frenar / brake                        - Frenar completamente\n";
    std::cout << "  entregar / release-package            - Soltar el paquete\n";
    std::cout << "  foto / take-photo                     - Tomar una fotografía\n";
    std::cout << "  notificar / notify-delivery           - Notificar entrega completada\n";
    std::cout << "  estado / status                       - Ver estado del dron\n";
    std::cout << "  ayuda / help                          - Mostrar este menú\n";
    std::cout << "  salir / exit                          - Salir del programa\n";
    std::cout << "\nEjemplos:\n";
    std::cout << "  > subir            (sube 5 metros)\n";
    std::cout << "  > subir 10         (sube 10 metros)\n";
    std::cout << "  > acelerar -5      (reversa a -5 m/s)\n";
}

std::vector<std::string> ConsoleUI::parseInput(const std::string& input) const {
    std::vector<std::string> tokens;
    std::istringstream stream(input);
    std::string token;
    
    while (stream >> token) {
        tokens.push_back(token);
    }
    
    return tokens;
}
// funcion para convertir a minusculas y permitir que 
// el usuario ingrese comandos en mayusculas, minusculas o mixtas
// usa std::tolower de <cctype> Ej: "DeSpEgAr" -> "despegar"
std::string ConsoleUI::toLowerCase(const std::string& str) const {
    std::string result = str;
    for (char& c : result) {
        c = std::tolower(static_cast<unsigned char>(c));
    }
    return result;
}

// Procesa el comando ingresado por el usuario
// y llama al método correspondiente del DroneController
// Esta capa permite comandos en español e inglés
// aunque la API solo acepte comandos en Inglés
void ConsoleUI::processCommand(const std::string& input) {
    std::vector<std::string> tokens = parseInput(input);
    if (tokens.empty()) return;
    
    std::string command = toLowerCase(tokens[0]);
    
    // Comandos sin parámetros
    if (command == "despegar" || command == "takeoff") {
        controller_->takeOff();
    }
    else if (command == "aterrizar" || command == "land") {
        controller_->land();
    }
    else if (command == "frenar" || command == "brake") {
        controller_->brake();
    }
    else if (command == "entregar" || command == "release-package") {
        controller_->releasePackage();
    }
    else if (command == "foto" || command == "take-photo") {
        controller_->takePhoto();
    }
    else if (command == "notificar" || command == "notify-delivery") {
        controller_->notifyDelivery();
    }
    else if (command == "estado" || command == "status") {
        controller_->showStatus();
    }
    else if (command == "ayuda" || command == "help") {
        displayMenu();
    }
    // Comandos con parámetros opcionales
    else if (command == "subir" || command == "elevate") {
        double meters = 5.0;  // Default
        if (tokens.size() > 1) {
            try {
                meters = std::stod(tokens[1]);
            } catch (...) {
                std::cout << "✗ Valor inválido, usando default: 5 metros\n";
            }
        }
        controller_->elevate(meters);
    }
    else if (command == "bajar" || command == "descend") {
        double meters = 5.0;  // Default
        if (tokens.size() > 1) {
            try {
                meters = std::stod(tokens[1]);
            } catch (...) {
                std::cout << "✗ Valor inválido, usando default: 5 metros\n";
            }
        }
        controller_->descend(meters);
    }
    else if (command == "derecha" || command == "turn-right") {
        double degrees = 45.0;  // Default
        if (tokens.size() > 1) {
            try {
                degrees = std::stod(tokens[1]);
            } catch (...) {
                std::cout << "✗ Valor inválido, usando default: 45 grados\n";
            }
        }
        controller_->turnRight(degrees);
    }
    else if (command == "izquierda" || command == "turn-left") {
        double degrees = 45.0;  // Default
        if (tokens.size() > 1) {
            try {
                degrees = std::stod(tokens[1]);
            } catch (...) {
                std::cout << "✗ Valor inválido, usando default: 45 grados\n";
            }
        }
        controller_->turnLeft(degrees);
    }
    else if (command == "acelerar" || command == "accelerate") {
        double speed = 5.0;  // Default
        if (tokens.size() > 1) {
            try {
                speed = std::stod(tokens[1]);
            } catch (...) {
                std::cout << "✗ Valor inválido, usando default: 5 m/s\n";
            }
        }
        controller_->accelerate(speed);
    }
    else {
        std::cout << "✗ Comando no reconocido: '" << command << "'\n";
        std::cout << "  Escribe 'ayuda' o 'help' para ver los comandos disponibles.\n";
    }
}

