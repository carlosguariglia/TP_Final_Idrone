# Drone IBag151 - Sistema de Control

**Trabajo Práctico Final Integrador**  
**Materia:** Algoritmos 2  
**Institución:** ISFT 151  
**Versión:** 0.0.1

---

## 📋 Descripción

Sistema de control para el drone de reparto **IBag151**, desarrollado en **C++17** con arquitectura limpia (Clean Architecture) aplicando principios SOLID y GRASP.

La aplicación permite controlar un dron mediante una interfaz de consola con **comandos de texto bilingües** (español/inglés), enviando instrucciones a una API externa (simulada con MockDroneAPI para desarrollo).

### Operaciones soportadas:
- ✈️ Despegar / Aterrizar
- ⬆️ Subir / Bajar
- ↩️ Girar derecha / izquierda
- 🚀 Acelerar / Frenar
- 📦 Entregar paquete
- 📸 Tomar foto de recepción
- 📢 Notificar entrega
- 📊 Ver estado del dron (altitud, velocidad, batería, etc.)

---

## 🏗️ Arquitectura

### Capas (Clean Architecture)

```
┌─────────────────────────────────────────┐
│  Presentation Layer (ConsoleUI)         │
├─────────────────────────────────────────┤
│  Application Layer (DroneController)    │
├─────────────────────────────────────────┤
│  Domain Layer (Drone - modelo)          │
├─────────────────────────────────────────┤
│  Infrastructure Layer (IDroneAPI)       │
└─────────────────────────────────────────┘
```

### Flujo de datos

```
Usuario → ConsoleUI → DroneController → Drone → IDroneAPI → Hardware
                           ↓              ↓
                    Imprime resultado  Estado + Validaciones
```

### Principios aplicados

✅ **SOLID:**
- Single Responsibility Principle (SRP)
- Dependency Inversion Principle (DIP)

✅ **GRASP:**
- Information Expert (Drone)
- Controller (DroneController)
- Low Coupling
- High Cohesion

✅ **Buenas prácticas:**
- Clean Architecture
- Validaciones basadas en estado
- Include guards tradicionales (#ifndef)

---

## 📂 Estructura del proyecto

```
TP_FINAL_0.0.1/
├── CMakeLists.txt              # Configuración CMake (C++17)
├── README.md                   # Este archivo
├── main.cpp                    # Punto de entrada
├── docs/           
│   └── DroneIBag151_UML.drawio # Diagrama UML
├── include/
│   ├── infrastructure/
│   │   ├── IDroneAPI.hpp      # Interfaz abstracta de API
│   │   └── MockDroneAPI.hpp   # Simulador de API
│   ├── domain/
│   │   └── Drone.hpp          # Modelo de dominio
│   ├── application/
│   │   └── DroneController.hpp # Controlador
│   └── presentation/
│       └── ConsoleUI.hpp       # Interfaz de usuario
├── src/
│   ├── infrastructure/
│   │   └── MockDroneAPI.cpp   
│   ├── domain/
│   │   └── Drone.cpp          # Lógica de validaciones
│   ├── application/
│   │   └── DroneController.cpp # Orquestación
│   └── presentation/
│       └── ConsoleUI.cpp       # Parser de comandos
└── build/                      # Directorio de compilación
```

---

## 🔧 Requisitos

- **C++17** o superior
- **CMake** 3.14 o superior
- **Compilador compatible:**
  - Linux/macOS: g++, clang++
  - Windows: MSVC (Visual Studio), MinGW, MSYS2

---

## 🚀 Compilación y ejecución

### Linux / macOS

#### 1. Configurar el proyecto

```bash
mkdir build
cd build
cmake ..
```

#### 2. Compilar

```bash
make
```

#### 3. Ejecutar la aplicación

```bash
./drone_app
```

### Windows

#### Opción A - Visual Studio (MSVC)

```cmd
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release
.\Release\drone_app.exe
```

#### Opción B - MinGW

```cmd
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
.\drone_app.exe
```

#### Opción C - MSYS2

```bash
mkdir build
cd build
cmake .. -G "MSYS Makefiles"
make
./drone_app.exe
```

### Soporte UTF-8

El proyecto incluye **soporte automático para UTF-8** en Windows para mostrar correctamente los caracteres especiales (✓, ✗, ╔, ║, ═, ╚) en la consola.

---

## 📖 Uso

### Sistema de Comandos por Texto (Bilingüe)

El sistema acepta comandos en **español** o **inglés** con parámetros opcionales.

#### Comandos disponibles:

| Comando (ES) | Comando (EN) | Parámetro | Default | Descripción |
|--------------|--------------|-----------|---------|-------------|
| `despegar` | `takeoff` | - | - | Despegar el dron |
| `aterrizar` | `land` | - | - | Aterrizar (requiere velocidad 0) |
| `subir` | `elevate` | metros | 5.0 | Elevar altitud |
| `bajar` | `descend` | metros | 5.0 | Descender (mín. 1.0m volando) |
| `derecha` | `right` | grados | 45 | Girar a la derecha (0-360°) |
| `izquierda` | `left` | grados | 45 | Girar a la izquierda (0-360°) |
| `acelerar` | `accelerate` | m/s | 5.0 | Acelerar (permite negativo=reversa) |
| `frenar` | `brake` | - | - | Frenar por completo |
| `entregar` | `release` | - | - | Liberar paquete (requiere velocidad 0) |
| `foto` | `photo` | - | - | Tomar fotografía (requiere velocidad 0) |
| `notificar` | `notify` | - | - | Notificar entrega (paquete entregado) |
| `estado` | `status` | - | - | Mostrar estado del dron |
| `salir` | `exit` | - | - | Salir del sistema |

#### Ejemplo de sesión:

```
Ingrese comando: despegar
✓ Despegue exitoso

Ingrese comando: subir 10
✓ Elevación de 10m exitosa

Ingrese comando: derecha
✓ Giro a la derecha de 45° exitoso

Ingrese comando: acelerar 15
✓ Aceleración a 15 m/s exitosa

Ingrese comando: estado
╔════════════════════════════════════╗
║     ESTADO DEL DRON IBag151        ║
╚════════════════════════════════════╝
  Altitud:     11.0 m
  Velocidad:   15.0 m/s
  Volando:     SÍ
  Paquete:     CARGADO
  Batería:     90.0 %
════════════════════════════════════

Ingrese comando: frenar
✓ Frenado exitoso

Ingrese comando: foto
✓ Foto tomada exitosamente

Ingrese comando: entregar
✓ Paquete liberado exitosamente

Ingrese comando: notificar
✓ Notificación de entrega enviada exitosamente

Ingrese comando: aterrizar
✓ Aterrizaje exitoso

Ingrese comando: salir
```

---

## 🔍 Reglas de Validación

El sistema implementa validaciones **basadas en el estado** del dron:

### Estado: Volando
- ❌ **Despegar**: No puede despegar si ya está volando
- ✅ **Aterrizar**: Requiere velocidad = 0
- ✅ **Elevar/Descender**: Solo cuando está volando
- ✅ **Girar**: Solo cuando está volando

### Límites físicos
- 📏 **Altitud mínima**: 1.0m cuando está volando
- 🔄 **Grados**: Entre 0 y 360
- ⚡ **Velocidad**: Permite valores negativos (reversa)

### Operaciones con paquete
- 📦 **Liberar paquete**: 
  - Debe estar volando
  - Velocidad = 0
  - Debe tener paquete cargado
- 📸 **Tomar foto**: Velocidad = 0
- 📢 **Notificar entrega**: El paquete debe haber sido entregado

### Mensajes de error específicos

El sistema proporciona **mensajes de error descriptivos** que indican exactamente qué validación falló:

```
✗ Error en Aterrizaje: debe frenar primero (velocidad actual: 15.0 m/s)
✗ Error en Descenso: altitud mínima es 1.0m cuando está volando
✗ Error en Giro: grados deben estar entre 0 y 360
✗ Error en Liberar paquete: debe frenar primero (velocidad actual: 10.0 m/s)
```

---

## 🔍 Diagrama UML

El diagrama de clases completo está disponible en:
- `docs/DroneIBag151_UML.drawio`

Abrirlo con:
- **Draw.io Desktop**: https://github.com/jgraph/drawio-desktop/releases
- **Draw.io Web**: https://app.diagrams.net/
- **VS Code Extension**: "Draw.io Integration"

---

## 📝 Notas de diseño

### ¿Por qué MockDroneAPI?

`MockDroneAPI` simula una API externa que controlaría hardware real. Permite:
- Desarrollar sin hardware físico
- Verificar que los comandos se envían correctamente
- **Solo se encarga de comunicación** (no mantiene estado)

### ¿Por qué la clase Drone?

`Drone` es el **modelo de dominio** que:
- Mantiene el estado del dron (altitud, velocidad, batería, etc.)
- Implementa **validaciones de negocio** basadas en estado
- Aplica el principio **Information Expert** de GRASP
- Separa **lógica de negocio** de **infraestructura**

En un escenario real, se implementaría `DroneAPIReal` con:
- Comunicación serial (UART/USB)
- Protocolos como MAVLink (PX4/ArduPilot)
- SDK del fabricante (DJI, Parrot, etc.)

### Responsabilidades por capa

| Clase | Responsabilidad |
|-------|----------------|
| `IDroneAPI` | Contrato abstracto para comunicación con hardware |
| `MockDroneAPI` | Simulación simple de comunicación (sin estado) |
| `Drone` | **Modelo de dominio** (estado + validaciones) |
| `DroneController` | Orquestación + mensajes de éxito/error |
| `ConsoleUI` | Parseo de comandos + interacción con usuario |

---

## 🛠️ Características técnicas

- ✅ **C++17** con `std::make_unique`
- ✅ **Multiplataforma** (Linux, macOS, Windows)
- ✅ **UTF-8** automático en Windows para caracteres especiales
- ✅ **Include guards** tradicionales (`#ifndef`/`#define`/`#endif`)
- ✅ **Comentarios en español**
- ✅ **Interfaz bilingüe** (español/inglés)
- ✅ **Sin dependencias externas** (solo STL)
- ✅ **Compilación limpia** (sin warnings)
- ✅ **CMake multiplataforma** (MSVC, MinGW, GCC, Clang)

---

## 📄 Licencia

Proyecto académico - ISFT 151

---

## ✨ Autor

**Carlos Guariglia**  
Algoritmos 2 - 2do Año ISFT

---

## 🔗 Referencias

- [Clean Architecture - Robert C. Martin](https://blog.cleancoder.com/uncle-bob/2012/08/13/the-clean-architecture.html)
- [SOLID Principles](https://en.wikipedia.org/wiki/SOLID)
- [GRASP Patterns](https://en.wikipedia.org/wiki/GRASP_(object-oriented_design))
- [C++17 Standard](https://en.cppreference.com/w/cpp/17)
