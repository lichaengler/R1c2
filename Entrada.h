#pragma once
#include <Arduino.h>
#include "config.h"

// Todo lo que el loop necesita saber de los controles en una sola vuelta.
struct EstadoEntrada {
  bool activo;        // START corto: activa o pausa
  bool recalibrar;    // START mantenido 1 segundo
  bool lenta;         // LB apretado: mira más lenta
  int adelante;       // joystick X: positivo = adelante
  int derecha;        // joystick Y: positivo = derecha
  bool shift;         // click del joystick
  bool r;             // botón Y
  bool c;             // botón B
  bool clickIzq;      // RB
  bool clickDer;      // LB
};

// Botones, joystick y la máquina de estados de START.
class Entrada {
public:
  void begin();
  EstadoEntrada actualizar();

private:
  bool apretado(int pin) const;   // con INPUT_PULLUP, apretado = LOW

  bool activo_ = false;
  bool startAntes_ = false;
  unsigned long startDesde_ = 0;
  bool recalibrado_ = false;
};
