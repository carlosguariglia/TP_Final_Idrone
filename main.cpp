#include "application/DroneController.hpp"
#include "domain/Drone.hpp"
#include "infrastructure/MockDroneAPI.hpp"
#include "presentation/ConsoleUI.hpp"
#include <memory>

// Configuración para Windows: habilitar UTF-8 en la consola
#ifdef _WIN32
    #include <windows.h>
#endif

int main() {
    // Configurar consola para UTF-8 en Windows (permite mostrar ✓ ✗ ╔ ║ ═ ╚)
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif

    // Capa de Infraestructura: API simulada del dron
    auto api = std::make_unique<MockDroneAPI>();

    // Capa de Dominio: El dron con su estado y lógica
    Drone drone(api.get());

    // Capa de Aplicación: Coordinador de operaciones del dron
    DroneController controller(&drone);

    // Capa de Presentación: Interfaz de usuario en consola
    ConsoleUI ui(&controller);

    // Iniciar la aplicación
    ui.run();

    return 0;
}
