cmake_minimum_required(VERSION 3.14)
project(DroneIBag151 VERSION 0.0.1 LANGUAGES CXX)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags (específicos por plataforma)
if(MSVC)
    # Flags para Visual Studio (Windows)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    # Habilitar UTF-8 en MSVC
    add_compile_options(/utf-8)
elseif(MINGW)
    # Flags para MinGW (Windows)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
else()
    # Flags para GCC/Clang (Linux/macOS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(INFRASTRUCTURE_SOURCES
    src/infrastructure/MockDroneAPI.cpp
)

set(DOMAIN_SOURCES
    src/domain/Drone.cpp
)

set(APPLICATION_SOURCES
    src/application/DroneController.cpp
)

set(PRESENTATION_SOURCES
    src/presentation/ConsoleUI.cpp
)

set(ALL_SOURCES
    ${INFRASTRUCTURE_SOURCES}
    ${DOMAIN_SOURCES}
    ${APPLICATION_SOURCES}
    ${PRESENTATION_SOURCES}
)

# Main executable
add_executable(drone_app
    ${ALL_SOURCES}
    main.cpp
)



# Print configuration
message(STATUS "=== Drone IBag151 Configuration ===")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Platform: ${CMAKE_SYSTEM_NAME}")
if(WIN32)
    message(STATUS "Windows UTF-8 Support: Enabled")
endif()
message(STATUS "===================================")
