#ifndef INCLUDE_PRESENTATION_CONSOLEUI_HPP_
#define INCLUDE_PRESENTATION_CONSOLEUI_HPP_

#include <string>
#include <vector>

class DroneController;

/**
 * Proporciona una interfaz de usuario interactiva basada en consola
 * para controlar el dron mediante comandos de texto.
 */
class ConsoleUI {
public:
    ConsoleUI(DroneController* controller);

    /** Inicia el bucle principal de la aplicación, mostrando el menú y manejando la entrada del usuario. */
    void run();

private:
    void displayMenu() const;
    void processCommand(const std::string& input);
    std::vector<std::string> parseInput(const std::string& input) const;
    std::string toLowerCase(const std::string& str) const;

    DroneController* controller_;
};

#endif  // INCLUDE_PRESENTATION_CONSOLEUI_HPP_
