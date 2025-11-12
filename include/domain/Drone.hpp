#ifndef INCLUDE_DOMAIN_DRONE_HPP_
#define INCLUDE_DOMAIN_DRONE_HPP_

#include "infrastructure/IDroneAPI.hpp"

/**
 * Modelo de dominio del dron. Gestiona el estado del dron y valida las
 * reglas de negocio: altitud máxima, velocidad máxima, nivel mínimo de batería.
 */
class Drone {
public:
    Drone(IDroneAPI* api);

    // Operaciones de vuelo
    bool takeOff();
    bool land();
    bool elevate(double meters);
    bool descend(double meters);
    bool turnRight(double degrees);
    bool turnLeft(double degrees);
    bool accelerate(double speed);
    bool brake();
    bool releasePackage();
    bool takePhoto();
    bool notifyDelivery();

    // Consultas de estado
    double getAltitude() const;
    double getSpeed() const;
    bool isFlying() const;
    bool hasPackage() const;
    double getBatteryLevel() const;

private:
    IDroneAPI* api_;

    // Estado interno
    double altitude_;
    double speed_;
    bool flying_;
    bool hasPackageLoaded_;
    double batteryLevel_;
};

#endif  // INCLUDE_DOMAIN_DRONE_HPP_

