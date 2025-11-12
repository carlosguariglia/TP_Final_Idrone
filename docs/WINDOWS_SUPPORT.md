# Soporte Multiplataforma - Windows

Este documento explica cómo el proyecto soporta **Windows** además de Linux/macOS.

---

## ✅ Cambios Implementados

### 1. **UTF-8 en Windows** (`main.cpp`)

**Problema:**
Windows CMD/PowerShell usa por defecto la codificación **CP-1252** (o la página de códigos regional), lo que hace que los caracteres Unicode se vean mal:
- `✓` se muestra como `ÔîÜ`
- `╔═╗` se muestran como `Ôòá`

**Solución:**
```cpp
// main.cpp - Configuración automática para Windows
#ifdef _WIN32
    #include <windows.h>
#endif

int main() {
    // Habilitar UTF-8 en la consola de Windows
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);  // Salida UTF-8
        SetConsoleCP(CP_UTF8);         // Entrada UTF-8
    #endif
    
    // ... resto del código
}
```

**Funcionamiento:**
- `#ifdef _WIN32`: Solo se compila en Windows (MSVC, MinGW detectan automáticamente)
- `SetConsoleOutputCP(CP_UTF8)`: Configura la salida de la consola a UTF-8
- `SetConsoleCP(CP_UTF8)`: Configura la entrada de la consola a UTF-8
- En Linux/macOS: El código dentro del `#ifdef` se ignora (ya usan UTF-8 por defecto)

---

### 2. **CMakeLists.txt Multiplataforma**

**Cambios:**
```cmake
# Compiler flags (específicos por plataforma)
if(MSVC)
    # Visual Studio (Windows)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    add_compile_options(/utf-8)  # Habilitar UTF-8 en archivos fuente
elseif(MINGW)
    # MinGW (Windows)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
else()
    # GCC/Clang (Linux/macOS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
endif()
```

**Beneficios:**
- ✅ Usa flags apropiados para cada compilador
- ✅ `/utf-8` en MSVC asegura que los archivos fuente se lean como UTF-8
- ✅ Mantiene warnings estrictos en todas las plataformas

---

## 🪟 Compilación en Windows

### **Opción 1: Visual Studio (MSVC)**

**Requisitos:**
- Visual Studio 2019 o superior
- CMake (incluido en Visual Studio o standalone)

**Pasos:**
```cmd
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release
```

**Ejecutar:**
```cmd
.\Release\drone_app.exe
```

---

### **Opción 2: MinGW**

**Requisitos:**
- MinGW-w64: https://www.mingw-w64.org/downloads/
- CMake: https://cmake.org/download/

**Pasos:**
```cmd
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
```

**Ejecutar:**
```cmd
.\drone_app.exe
```

---

### **Opción 3: MSYS2 (Recomendado para desarrolladores)**

**Requisitos:**
- MSYS2: https://www.msys2.org/

**Instalación de herramientas:**
```bash
pacman -S mingw-w64-x86_64-gcc
pacman -S mingw-w64-x86_64-cmake
pacman -S make
```

**Pasos:**
```bash
mkdir build
cd build
cmake .. -G "MSYS Makefiles"
make
```

**Ejecutar:**
```bash
./drone_app.exe
```

---

## 🔍 Verificación

### **Linux:**
```bash
$ ./drone_app
╔═══════════════════════════════════════╗
║     DRONE IBag151 - Panel de Control  ║
╚═══════════════════════════════════════╝
> despegar
✓ Despegue exitoso
```

### **Windows:**
```cmd
> drone_app.exe
╔═══════════════════════════════════════╗
║     DRONE IBag151 - Panel de Control  ║
╚═══════════════════════════════════════╝
> despegar
✓ Despegue exitoso
```

**Los caracteres se ven idénticos en ambas plataformas!** ✅

---

## 📝 Notas Técnicas

### **¿Por qué `#ifdef _WIN32` y no `#ifdef WIN32`?**
- `_WIN32`: Definido tanto en Windows 32-bit como 64-bit (nombre confuso pero estándar)
- `WIN32`: Solo en 32-bit (obsoleto)
- MSVC y MinGW definen `_WIN32` automáticamente

### **¿Por qué no usar `#ifdef _MSC_VER`?**
- `_MSC_VER`: Solo Visual Studio (Microsoft Compiler)
- `_WIN32`: Funciona con MSVC, MinGW, Clang para Windows

### **¿Y si uso Windows Terminal o PowerShell 7?**
- Windows Terminal soporta UTF-8 mejor que CMD clásico
- El código sigue siendo necesario para compatibilidad con CMD antiguo

### **¿Qué pasa si no configuro UTF-8?**
```
> despegar
Ôèå Despegue exitoso  // ❌ Caracteres mal
```

---

## 🎯 Conclusión

El proyecto es **100% multiplataforma** con estos cambios mínimos:
- ✅ Compila en Linux, macOS, Windows
- ✅ Los caracteres UTF-8 se ven correctamente en todas las plataformas
- ✅ Sin cambios en la lógica de negocio
- ✅ CMake detecta automáticamente la plataforma

**Total de líneas agregadas: ~15 líneas**  
**Impacto: Soporte completo para Windows** 🎉

---

**Autor:** Carlos Guariglia - ISFT 151  
**Fecha:** Noviembre 2025
