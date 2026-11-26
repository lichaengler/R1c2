#include "Giroscopio.h"
#include <Wire.h>
#include <math.h>

void Giroscopio::begin() {
  Wire.begin();
  Wire.setClock(100000);
  Wire.setWireTimeout(3000, true);

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(REG_PWR_MGMT_1);
  Wire.write(0);
  Wire.endTransmission();
  delay(100);
}

// Lee el giro vertical (eje Y del MPU) y horizontal (eje Z).
bool Giroscopio::leerCrudo(int &h, int &v) const {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(REG_GYRO_Y);
  if (Wire.endTransmission(false) != 0) return false;
  if (Wire.requestFrom(MPU_ADDR, 4) < 4) return false;

  byte yAlto = Wire.read();
  byte yBajo = Wire.read();
  byte zAlto = Wire.read();
  byte zBajo = Wire.read();
  v = (int16_t)(yAlto << 8 | yBajo);
  h = (int16_t)(zAlto << 8 | zBajo);
  return true;
}

void Giroscopio::calibrar() {
  long sumaH = 0, sumaV = 0;
  int n = 0;
  for (int i = 0; i < MUESTRAS_CAL; i++) {
    int h, v;
    if (leerCrudo(h, v)) {
      sumaH += h;
      sumaV += v;
      n++;
    }
    delay(RETARDO_CAL_MS);
  }
  if (n > 0) {
    offH_ = sumaH / n;
    offV_ = sumaV / n;
  }
  giroH_ = 0;
  giroV_ = 0;
  restoX_ = 0;
  restoY_ = 0;
}

bool Giroscopio::leer() {
  int h, v;
  if (!leerCrudo(h, v)) return false;
  giroH_ = giroH_ * (1 - SUAVIZADO) + (h - offH_) * SUAVIZADO;
  giroV_ = giroV_ * (1 - SUAVIZADO) + (v - offV_) * SUAVIZADO;
  return true;
}

Vector Giroscopio::deltaMouse(bool lenta) {
  float s = lenta ? SENS / 2 : SENS;
  if (fabs(giroH_) > ZONA_MUERTA) restoX_ -= giroH_ * s;
  if (fabs(giroV_) > ZONA_MUERTA) restoY_ += giroV_ * s;

  int x = constrain((int)restoX_, -127, 127);
  int y = constrain((int)restoY_, -127, 127);
  restoX_ -= (int)restoX_;
  restoY_ -= (int)restoY_;
  return {x, y};
}
