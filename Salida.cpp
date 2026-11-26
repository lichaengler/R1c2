#include "Salida.h"
#include <Mouse.h>
#include <Keyboard.h>

void Salida::begin() {
  Mouse.begin();
  Keyboard.begin();
}

void Salida::mover(int x, int y) {
  if (x != 0 || y != 0) Mouse.move(x, y);
}

void Salida::tecla(uint8_t k, bool ahora, bool &antes) {
  if (ahora && !antes) Keyboard.press(k);
  if (!ahora && antes) Keyboard.release(k);
  antes = ahora;
}

void Salida::click(uint8_t b, bool ahora, bool &antes) {
  if (ahora && !antes) Mouse.press(b);
  if (!ahora && antes) Mouse.release(b);
  antes = ahora;
}

void Salida::aplicar(const EstadoEntrada &e) {
  // Joystick -> W A S D (el módulo va girado: X es adelante/atrás).
  tecla('w', e.activo && e.adelante > UMBRAL, teclaW_);
  tecla('s', e.activo && e.adelante < -UMBRAL, teclaS_);
  tecla('d', e.activo && e.derecha > UMBRAL, teclaD_);
  tecla('a', e.activo && e.derecha < -UMBRAL, teclaA_);

  tecla(KEY_LEFT_SHIFT, e.shift, teclaShift_);
  tecla('r', e.r, teclaR_);
  tecla('c', e.c, teclaC_);
  click(MOUSE_LEFT, e.clickIzq, clickIzq_);
  click(MOUSE_RIGHT, e.clickDer, clickDer_);
}
