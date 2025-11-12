#ifndef INCLUDE_INFRASTRUCTURE_MOCKDRONEAPI_HPP_
#define INCLUDE_INFRASTRUCTURE_MOCKDRONEAPI_HPP_

#include "infrastructure/IDroneAPI.hpp"

/**
 * Implementación simulada de IDroneAPI para desarrollo y demostración.
 * Todos los comandos retornan éxito (true) simulando un dron que responde correctamente.
 */
class MockDroneAPI : public IDroneAPI {
public:
    MockDroneAPI() = default;

    bool sendTakeOff() override { return true; }
    bool sendLand() override { return true; }
    // Al forzar a devolver true, los parámetros no se usan
    // para evitar warnings, se nombran con /*nombre*/
    // El compilador se queja si ponemos variables sin usar
    bool sendElevate(double /*meters*/) override { return true; }
    bool sendDescend(double /*meters*/) override { return true; }
    bool sendTurnRight(double /*degrees*/) override { return true; }
    bool sendTurnLeft(double /*degrees*/) override { return true; }
    bool sendAccelerate(double /*speed*/) override { return true; }
    bool sendBrake() override { return true; }
    bool sendReleasePackage() override { return true; }
    bool sendTakePhoto() override { return true; }
    bool sendNotifyDelivery() override { return true; }
};

#endif  // INCLUDE_INFRASTRUCTURE_MOCKDRONEAPI_HPP_
