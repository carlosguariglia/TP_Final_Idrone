#ifndef INCLUDE_INFRASTRUCTURE_IDRONEAPI_HPP_
#define INCLUDE_INFRASTRUCTURE_IDRONEAPI_HPP_

/**
 * Interfaz que abstrae la capa de comunicación con el hardware del dron.
 * Las implementaciones deben ser sin estado y simplemente reenviar comandos
 * al transporte subyacente (hardware real o simulado).
 */
class IDroneAPI {
public:
    virtual ~IDroneAPI() = default;

    virtual bool sendTakeOff() = 0;
    virtual bool sendLand() = 0;
    virtual bool sendElevate(double meters) = 0;
    virtual bool sendDescend(double meters) = 0;
    virtual bool sendTurnRight(double degrees) = 0;
    virtual bool sendTurnLeft(double degrees) = 0;
    virtual bool sendAccelerate(double speed) = 0;
    virtual bool sendBrake() = 0;
    virtual bool sendReleasePackage() = 0;
    virtual bool sendTakePhoto() = 0;
    virtual bool sendNotifyDelivery() = 0;
};

#endif  // INCLUDE_INFRASTRUCTURE_IDRONEAPI_HPP_
