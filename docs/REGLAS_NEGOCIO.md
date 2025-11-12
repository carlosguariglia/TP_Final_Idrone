# Reglas de Negocio - Drone IBag151

Este documento detalla todas las reglas de validación implementadas en el modelo de dominio (`Drone`).

---

## 📋 Índice

1. [Reglas por Operación](#reglas-por-operación)
2. [Límites y Restricciones](#límites-y-restricciones)
3. [Estados del Dron](#estados-del-dron)
4. [Matriz de Validaciones](#matriz-de-validaciones)

---

## 🔍 Reglas por Operación

### 1. Despegar (`takeOff`)

**Precondiciones:**
- ✅ El dron NO debe estar volando

**Postcondiciones:**
- El dron pasa a estado `flying = true`
- La altitud se establece en `1.0m` (inicial)
- Se envía comando `sendTakeOff()` a la API

**Mensajes de error:**
- `"el dron ya está volando"` - Si intenta despegar estando en vuelo

---

### 2. Aterrizar (`land`)

**Precondiciones:**
- ✅ El dron DEBE estar volando
- ✅ La velocidad DEBE ser `0.0 m/s`

**Postcondiciones:**
- El dron pasa a estado `flying = false`
- La altitud se establece en `0.0m`
- Se envía comando `sendLand()` a la API

**Mensajes de error:**
- `"el dron no está volando"` - Si intenta aterrizar sin estar en vuelo
- `"debe frenar primero (velocidad actual: X m/s)"` - Si tiene velocidad

---

### 3. Elevar (`elevate`)

**Precondiciones:**
- ✅ El dron DEBE estar volando
- ✅ Los metros DEBEN ser `>= 0`

**Postcondiciones:**
- La altitud aumenta en `metros` especificados
- Se envía comando `sendElevate(metros)` a la API

**Mensajes de error:**
- `"el dron debe estar volando"` - Si no está en vuelo
- `"use 'bajar' para descender (valor negativo no permitido)"` - Si metros < 0

**Notas:**
- No hay límite máximo de altitud (simplificación)

---

### 4. Descender (`descend`)

**Precondiciones:**
- ✅ El dron DEBE estar volando
- ✅ Los metros DEBEN ser `>= 0`
- ✅ La altitud resultante DEBE ser `>= 1.0m`

**Postcondiciones:**
- La altitud disminuye en `metros` especificados
- Se envía comando `sendDescend(metros)` a la API

**Mensajes de error:**
- `"el dron debe estar volando"` - Si no está en vuelo
- `"use 'subir' para elevar (valor negativo no permitido)"` - Si metros < 0
- `"altitud mínima es 1.0m cuando está volando"` - Si el descenso viola el mínimo

**Notas:**
- Cuando está volando, NO puede bajar a menos de 1.0m
- Debe aterrizar explícitamente para llegar a 0.0m

---

### 5. Girar a la Derecha (`turnRight`)

**Precondiciones:**
- ✅ El dron DEBE estar volando
- ✅ Los grados DEBEN estar entre `0` y `360`

**Postcondiciones:**
- Se envía comando `sendTurnRight(grados)` a la API

**Mensajes de error:**
- `"el dron debe estar volando"` - Si no está en vuelo
- `"grados deben estar entre 0 y 360"` - Si grados fuera de rango

**Notas:**
- No modifica estado interno (orientación no se persiste)

---

### 6. Girar a la Izquierda (`turnLeft`)

**Precondiciones:**
- ✅ El dron DEBE estar volando
- ✅ Los grados DEBEN estar entre `0` y `360`

**Postcondiciones:**
- Se envía comando `sendTurnLeft(grados)` a la API

**Mensajes de error:**
- `"el dron debe estar volando"` - Si no está en vuelo
- `"grados deben estar entre 0 y 360"` - Si grados fuera de rango

**Notas:**
- No modifica estado interno (orientación no se persiste)

---

### 7. Acelerar (`accelerate`)

**Precondiciones:**
- ✅ El dron DEBE estar volando

**Postcondiciones:**
- La velocidad se establece en `speed` especificado
- Se envía comando `sendAccelerate(speed)` a la API

**Mensajes de error:**
- `"el dron debe estar volando"` - Si no está en vuelo

**Notas:**
- ✅ Permite valores NEGATIVOS (reversa)
- ✅ NO hay límite máximo de velocidad (simplificación)
- La velocidad se establece directamente (no es incremental)

---

### 8. Frenar (`brake`)

**Precondiciones:**
- ✅ El dron DEBE tener velocidad (`speed != 0`)

**Postcondiciones:**
- La velocidad se establece en `0.0 m/s`
- Se envía comando `sendBrake()` a la API

**Mensajes de error:**
- `"el dron ya está detenido"` - Si la velocidad ya es 0

**Notas:**
- Puede frenar estando en tierra o volando

---

### 9. Liberar Paquete (`releasePackage`)

**Precondiciones:**
- ✅ El dron DEBE estar volando
- ✅ DEBE tener paquete cargado (`hasPackageLoaded = true`)
- ✅ La velocidad DEBE ser `0.0 m/s`

**Postcondiciones:**
- El paquete se marca como entregado (`hasPackageLoaded = false`)
- Se envía comando `sendReleasePackage()` a la API

**Mensajes de error:**
- `"el dron debe estar volando"` - Si no está en vuelo
- `"no hay paquete cargado (ya fue entregado)"` - Si no tiene paquete
- `"debe frenar primero (velocidad actual: X m/s)"` - Si tiene velocidad

**Notas:**
- Requiere estar completamente detenido para entregar con seguridad

---

### 10. Tomar Foto (`takePhoto`)

**Precondiciones:**
- ✅ La velocidad DEBE ser `0.0 m/s`

**Postcondiciones:**
- Se envía comando `sendTakePhoto()` a la API

**Mensajes de error:**
- `"debe frenar primero (velocidad actual: X m/s)"` - Si tiene velocidad

**Notas:**
- Puede tomar foto en tierra o volando
- Requiere estar detenido para evitar fotos borrosas

---

### 11. Notificar Entrega (`notifyDelivery`)

**Precondiciones:**
- ✅ El paquete DEBE haber sido entregado (`hasPackageLoaded = false`)

**Postcondiciones:**
- Se envía comando `sendNotifyDelivery()` a la API

**Mensajes de error:**
- `"debe entregar el paquete primero"` - Si aún tiene el paquete cargado

**Notas:**
- Solo se puede notificar DESPUÉS de liberar el paquete

---

## 📊 Límites y Restricciones

### Altitud
- **Mínimo volando:** `1.0 m`
- **Mínimo en tierra:** `0.0 m`
- **Máximo:** Sin límite (simplificación)

### Velocidad
- **Mínimo:** Sin límite (permite valores negativos = reversa)
- **Máximo:** Sin límite (simplificación)
- **Requiere 0 para:** Aterrizar, liberar paquete, tomar foto

### Giros
- **Rango válido:** `0° - 360°`
- **Solo volando:** Sí

### Batería
- **Rango:** `0.0% - 100.0%`
- **No hay validación:** La batería no bloquea operaciones (simplificación)

---

## 🎯 Estados del Dron

### Estado: `flying = false` (En tierra)

| Operación | ¿Permitida? |
|-----------|-------------|
| Despegar | ✅ Sí |
| Aterrizar | ❌ No |
| Elevar | ❌ No |
| Descender | ❌ No |
| Girar | ❌ No |
| Acelerar | ❌ No |
| Frenar | ✅ Sí (si tiene velocidad) |
| Liberar paquete | ❌ No |
| Tomar foto | ✅ Sí (sin velocidad) |
| Notificar | ✅ Sí (si paquete entregado) |

### Estado: `flying = true` (Volando)

| Operación | ¿Permitida? |
|-----------|-------------|
| Despegar | ❌ No |
| Aterrizar | ✅ Sí (sin velocidad) |
| Elevar | ✅ Sí (metros >= 0) |
| Descender | ✅ Sí (altitud >= 1.0) |
| Girar | ✅ Sí (0-360°) |
| Acelerar | ✅ Sí (cualquier valor) |
| Frenar | ✅ Sí (si tiene velocidad) |
| Liberar paquete | ✅ Sí (sin velocidad + con paquete) |
| Tomar foto | ✅ Sí (sin velocidad) |
| Notificar | ✅ Sí (si paquete entregado) |

---

## 📋 Matriz de Validaciones

| Operación | Volando | Velocidad = 0 | Altitud >= 1.0 | Grados 0-360 | Tiene Paquete | Paquete Entregado |
|-----------|---------|---------------|----------------|--------------|---------------|-------------------|
| `takeOff` | ❌ No | - | - | - | - | - |
| `land` | ✅ Sí | ✅ Sí | - | - | - | - |
| `elevate` | ✅ Sí | - | - | - | - | - |
| `descend` | ✅ Sí | - | ✅ Sí | - | - | - |
| `turnRight` | ✅ Sí | - | - | ✅ Sí | - | - |
| `turnLeft` | ✅ Sí | - | - | ✅ Sí | - | - |
| `accelerate` | ✅ Sí | - | - | - | - | - |
| `brake` | - | ❌ No | - | - | - | - |
| `releasePackage` | ✅ Sí | ✅ Sí | - | - | ✅ Sí | - |
| `takePhoto` | - | ✅ Sí | - | - | - | - |
| `notifyDelivery` | - | - | - | - | - | ✅ Sí |

**Leyenda:**
- ✅ = Debe cumplirse
- ❌ = NO debe cumplirse
- `-` = No aplica

---

## 🔄 Flujo Típico de Entrega

```
1. despegar          → flying=true, altitude=1.0, speed=0
2. subir 50          → altitude=51.0
3. acelerar 20       → speed=20.0
4. derecha 90        → giro a la derecha
5. frenar            → speed=0.0
6. foto              → toma evidencia
7. entregar          → hasPackageLoaded=false
8. notificar         → envía confirmación
9. bajar 50          → altitude=1.0
10. aterrizar        → flying=false, altitude=0.0
```

---

## 🛡️ Decisiones de Diseño

### ¿Por qué NO hay límite máximo de velocidad/altitud?
- Simplificación del modelo académico
- Permite probar el sistema sin restricciones artificiales
- En producción se agregarían límites de seguridad

### ¿Por qué permite velocidad negativa?
- Permite simular "reversa" o movimiento hacia atrás
- Mayor flexibilidad para maniobras

### ¿Por qué la altitud mínima volando es 1.0m?
- Previene que el dron "toque el suelo" sin aterrizar formalmente
- Fuerza el uso explícito de `land()` para completar el aterrizaje

### ¿Por qué foto y notificar NO requieren estar volando?
- `takePhoto`: Puede documentar antes de despegar o después de aterrizar
- `notifyDelivery`: La notificación es una acción administrativa, no física

### ¿Por qué NO se valida batería?
- Simplificación del modelo
- La batería es informativa (estado observable)
- En producción bloquearía operaciones con batería < 20%

---

## 📚 Implementación

Todas estas reglas están implementadas en:
- **Archivo:** `src/domain/Drone.cpp`
- **Clase:** `Drone`
- **Patrón:** Information Expert (GRASP)

Los mensajes de error específicos se manejan en:
- **Archivo:** `src/application/DroneController.cpp`
- **Clase:** `DroneController`
- **Patrón:** Controller (GRASP)

---

**Última actualización:** Noviembre 2025  
**Autor:** Carlos Guariglia - ISFT 151
