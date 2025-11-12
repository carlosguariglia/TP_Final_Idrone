#ifndef INCLUDE_APPLICATION_DRONECONTROLLER_HPP_
#define INCLUDE_APPLICATION_DRONECONTROLLER_HPP_

#include <string>

#include "domain/Drone.hpp"

/**
 * Coordina las operaciones del dron y proporciona retroalimentación al usuario.
 */
class DroneController {
public:
    DroneController(Drone* drone);

    void takeOff();
    void land();
    void elevate(double meters);
    void descend(double meters);
    void turnRight(double degrees);
    void turnLeft(double degrees);
    void accelerate(double speed);
    void brake();
    void releasePackage();
    void takePhoto();
    void notifyDelivery();
    void showStatus();

private:
    void printSuccess(const std::string& operation);
    void printError(const std::string& operation, const std::string& reason = "");
    // funcion auxiliar para formatear doubles con 2 decimales
    std::string formatDouble(double value, int precision = 2) const;

    Drone* drone_;
};

#endif  // INCLUDE_APPLICATION_DRONECONTROLLER_HPP_
