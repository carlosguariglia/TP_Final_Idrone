#include "application/DroneController.hpp"

#include <iomanip>
#include <iostream>
#include <sstream>

#include "domain/Drone.hpp"

DroneController::DroneController(Drone* drone) : drone_(drone) {}

void DroneController::printSuccess(const std::string& operation) {
    std::cout << "✓ " << operation << " exitoso" << std::endl;
}

void DroneController::printError(const std::string& operation, const std::string& reason) {
    std::cerr << "✗ Error en " << operation;
    if (!reason.empty()) {
        std::cerr << ": " << reason;
    }
    std::cerr << std::endl;
}

std::string DroneController::formatDouble(double value, int precision) const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << value;
    return oss.str();
}

void DroneController::takeOff() {
    if (drone_->takeOff()) {
        printSuccess("Despegue");
    } else {
        if (drone_->isFlying()) {
            printError("Despegue", "el dron ya está volando");
        } else {
            printError("Despegue", "condiciones no permitidas");
        }
    }
}

void DroneController::land() {
    if (drone_->land()) {
        printSuccess("Aterrizaje");
    } else {
        if (!drone_->isFlying()) {
            printError("Aterrizaje", "el dron no está volando");
        } else if (drone_->getSpeed() != 0.0) {
            printError("Aterrizaje", "debe frenar primero (velocidad actual: " + 
                      formatDouble(drone_->getSpeed()) + " m/s)");
        } else {
            printError("Aterrizaje", "condiciones no permitidas");
        }
    }
}

void DroneController::elevate(double meters) {
    if (drone_->elevate(meters)) {
        printSuccess("Elevación de " + formatDouble(meters) + "m");
    } else {
        if (!drone_->isFlying()) {
            printError("Elevación", "el dron debe estar volando");
        } else if (meters < 0) {
            printError("Elevación", "use 'bajar' para descender (valor negativo no permitido)");
        } else {
            printError("Elevación", "operación no permitida");
        }
    }
}

void DroneController::descend(double meters) {
    if (drone_->descend(meters)) {
        printSuccess("Descenso de " + formatDouble(meters) + "m");
    } else {
        if (!drone_->isFlying()) {
            printError("Descenso", "el dron debe estar volando");
        } else if (meters < 0) {
            printError("Descenso", "use 'subir' para elevar (valor negativo no permitido)");
        } else {
            printError("Descenso", "altitud mínima es 1.0m cuando está volando");
        }
    }
}

void DroneController::turnRight(double degrees) {
    if (drone_->turnRight(degrees)) {
        printSuccess("Giro a la derecha de " + formatDouble(degrees, 0) + "°");
    } else {
        if (!drone_->isFlying()) {
            printError("Giro", "el dron debe estar volando");
        } else if (degrees < 0 || degrees > 360) {
            printError("Giro", "grados deben estar entre 0 y 360");
        } else {
            printError("Giro", "operación no permitida");
        }
    }
}

void DroneController::turnLeft(double degrees) {
    if (drone_->turnLeft(degrees)) {
        printSuccess("Giro a la izquierda de " + formatDouble(degrees, 0) + "°");
    } else {
        if (!drone_->isFlying()) {
            printError("Giro", "el dron debe estar volando");
        } else if (degrees < 0 || degrees > 360) {
            printError("Giro", "grados deben estar entre 0 y 360");
        } else {
            printError("Giro", "operación no permitida");
        }
    }
}

void DroneController::accelerate(double speed) {
    if (drone_->accelerate(speed)) {
        printSuccess("Aceleración a " + formatDouble(speed) + " m/s");
    } else {
        if (!drone_->isFlying()) {
            printError("Aceleración", "el dron debe estar volando");
        } else {
            printError("Aceleración", "operación no permitida");
        }
    }
}

void DroneController::brake() {
    if (drone_->brake()) {
        printSuccess("Frenado");
    } else {
        printError("Frenado", "el dron no está en movimiento o no está volando");
    }
}

void DroneController::releasePackage() {
    if (drone_->releasePackage()) {
        printSuccess("Paquete liberado");
    } else {
        if (!drone_->isFlying()) {
            printError("Liberar paquete", "el dron debe estar volando");
        } else if (!drone_->hasPackage()) {
            printError("Liberar paquete", "no hay paquete cargado (ya fue entregado)");
        } else if (drone_->getSpeed() != 0.0) {
            printError("Liberar paquete", "debe frenar primero (velocidad actual: " + 
                      formatDouble(drone_->getSpeed()) + " m/s)");
        } else {
            printError("Liberar paquete", "operación no permitida");
        }
    }
}

void DroneController::takePhoto() {
    if (drone_->takePhoto()) {
        printSuccess("Foto tomada");
    } else {
        if (drone_->getSpeed() != 0.0) {
            printError("Tomar foto", "debe frenar primero (velocidad actual: " + 
                      formatDouble(drone_->getSpeed()) + " m/s)");
        } else {
            printError("Tomar foto", "operación no permitida");
        }
    }
}

void DroneController::notifyDelivery() {
    if (drone_->notifyDelivery()) {
        printSuccess("Notificación de entrega enviada");
    } else {
        if (drone_->hasPackage()) {
            printError("Notificar entrega", "debe entregar el paquete primero");
        } else {
            printError("Notificar entrega", "operación no permitida");
        }
    }
}

void DroneController::showStatus() {
    std::cout << "\n╔════════════════════════════════════╗" << std::endl;
    std::cout << "║     ESTADO DEL DRON IBag151        ║" << std::endl;
    std::cout << "╚════════════════════════════════════╝" << std::endl;
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "  Altitud:     " << drone_->getAltitude() << " m" << std::endl;
    std::cout << "  Velocidad:   " << drone_->getSpeed() << " m/s" << std::endl;
    std::cout << "  Volando:     " << (drone_->isFlying() ? "SÍ" : "NO") << std::endl;
    std::cout << "  Paquete:     " << (drone_->hasPackage() ? "CARGADO" : "ENTREGADO") << std::endl;
    std::cout << "  Batería:     " << drone_->getBatteryLevel() << " %" << std::endl;
    std::cout << "════════════════════════════════════\n" << std::endl;
}
