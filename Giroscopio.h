#pragma once
#include <Arduino.h>
#include "config.h"

// Delta de mouse ya convertido a pasos (máximo ±127 por eje).
struct Vector {
  int x;
  int y;
};

// MPU6050 acostado en el cañón, con la flecha X hacia la punta.
// Lee los ejes Y (vertical) y Z (horizontal) del giroscopio.
class Giroscopio {
public:
  void begin();                 // despierta el sensor por I2C
  void calibrar();              // promedia 100 lecturas con la pistola quieta
  bool leer();                  // actualiza el giro suavizado; false si falla I2C
  Vector deltaMouse(bool lenta);// aplica deadzone, sensibilidad y acumulador

private:
  bool leerCrudo(int &h, int &v) const;

  long offH_ = 0, offV_ = 0;          // "cero" del giroscopio
  float giroH_ = 0, giroV_ = 0;       // giro suavizado
  float restoX_ = 0, restoY_ = 0;     // decimales que quedan para la vuelta siguiente
};
