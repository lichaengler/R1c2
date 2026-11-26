#pragma once
#include <Arduino.h>
#include "Entrada.h"

// Único lugar que habla con la PC por HID (mouse y teclado).
// Avisa del estado sólo cuando cambia, no en cada vuelta.
class Salida {
public:
  void begin();
  void mover(int x, int y);
  void aplicar(const EstadoEntrada &e);

private:
  void tecla(uint8_t k, bool ahora, bool &antes);
  void click(uint8_t b, bool ahora, bool &antes);

  bool teclaW_ = false, teclaA_ = false, teclaS_ = false, teclaD_ = false;
  bool teclaShift_ = false, teclaR_ = false, teclaC_ = false;
  bool clickIzq_ = false, clickDer_ = false;
};
