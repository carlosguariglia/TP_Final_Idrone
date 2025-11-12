#include "domain/Drone.hpp"

Drone::Drone(IDroneAPI* api)
    : api_(api), altitude_(0.0), speed_(0.0), flying_(false), hasPackageLoaded_(true), batteryLevel_(100.0) {}

bool Drone::takeOff() {
    // Solo validar que no esté volando
    if (flying_) {
        return false;
    }

    if (api_ && api_->sendTakeOff()) {
        flying_ = true;
        altitude_ = 1.0;  // Altitud inicial al despegar
        return true;
    }
    return false;
}

bool Drone::land() {
    // No se puede aterrizar si no está volando o si tiene velocidad
    if (!flying_ || speed_ != 0.0) {
        return false;
    }

    if (api_ && api_->sendLand()) {
        flying_ = false;
        altitude_ = 0.0;
        return true;
    }
    return false;
}

bool Drone::elevate(double meters) {
    // No puede elevar si no está volando o si usa valor negativo
    if (!flying_ || meters < 0) {
        return false;
    }

    if (api_ && api_->sendElevate(meters)) {
        altitude_ += meters;
        return true;
    }
    return false;
}

bool Drone::descend(double meters) {
    // No puede descender si no está volando o si usa valor negativo
    if (!flying_ || meters < 0) {
        return false;
    }
    
    // La altitud mínima cuando está volando es 1.0
    // Si intenta bajar más de lo permitido, baja hasta 1.0
    double newAltitude = altitude_ - meters;
    if (newAltitude < 1.0) {
        newAltitude = 1.0;
    }
    
    if (api_ && api_->sendDescend(meters)) {
        altitude_ = newAltitude;
        return true;
    }
    return false;
}

bool Drone::turnRight(double degrees) {
    // No puede girar si no está volando, solo acepta grados entre 0 y 360
    if (!flying_ || degrees < 0 || degrees > 360) {
        return false;
    }
    return api_ ? api_->sendTurnRight(degrees) : false;
}

bool Drone::turnLeft(double degrees) {
    // No puede girar si no está volando, solo acepta grados entre 0 y 360
    if (!flying_ || degrees < 0 || degrees > 360) {
        return false;
    }
    return api_ ? api_->sendTurnLeft(degrees) : false;
}

bool Drone::accelerate(double speed) {
    // Puede acelerar en positivo o negativo (reversa)
    if (!flying_) {
        return false;
    }

    if (api_ && api_->sendAccelerate(speed)) {
        speed_ = speed;
        return true;
    }
    return false;
}

bool Drone::brake() {
    if (!flying_ || speed_ == 0.0) {
        return false;
    }
    if (api_ && api_->sendBrake()) {
        speed_ = 0.0;
        return true;
    }
    return false;
}

bool Drone::releasePackage() {
    // No se puede entregar paquete si no está volando, no tiene paquete, o tiene velocidad
    if (!flying_ || !hasPackageLoaded_ || speed_ != 0.0) {
        return false;
    }

    if (api_ && api_->sendReleasePackage()) {
        hasPackageLoaded_ = false;
        return true;
    }
    return false;
}

bool Drone::takePhoto() {
    // No se puede sacar foto si tiene velocidad
    if (speed_ != 0.0) {
        return false;
    }
    return api_ ? api_->sendTakePhoto() : false;
}

bool Drone::notifyDelivery() {
    // Solo requiere que el paquete haya sido entregado (no importa si está volando o en movimiento)
    if (hasPackageLoaded_) {
        return false;  // No puede notificar si todavía tiene el paquete
    }
    return api_ ? api_->sendNotifyDelivery() : false;
}

double Drone::getAltitude() const { return altitude_; }

double Drone::getSpeed() const { return speed_; }

bool Drone::isFlying() const { return flying_; }

bool Drone::hasPackage() const { return hasPackageLoaded_; }

double Drone::getBatteryLevel() const { return batteryLevel_; }
