#include "Entrada.h"

void Entrada::begin() {
  pinMode(PIN_RB, INPUT_PULLUP);
  pinMode(PIN_LB, INPUT_PULLUP);
  pinMode(PIN_Y, INPUT_PULLUP);
  pinMode(PIN_B, INPUT_PULLUP);
  pinMode(PIN_START, INPUT_PULLUP);
  pinMode(PIN_CLICK, INPUT_PULLUP);
}

bool Entrada::apretado(int pin) const {
  return digitalRead(pin) == LOW;
}

EstadoEntrada Entrada::actualizar() {
  // START: toque corto = activar/pausar; mantener 1 segundo = recalibrar.
  bool start = apretado(PIN_START);
  bool recalibrar = false;
  if (start && !startAntes_) {
    startDesde_ = millis();
    recalibrado_ = false;
  }
  if (start && !recalibrado_ && millis() - startDesde_ >= START_MS) {
    recalibrar = true;
    recalibrado_ = true;
  }
  if (!start && startAntes_ && !recalibrado_ &&
      millis() - startDesde_ > DEBOUNCE_MS) {
    activo_ = !activo_;
  }
  startAntes_ = start;

  EstadoEntrada e;
  e.activo = activo_;
  e.recalibrar = recalibrar;
  e.lenta = apretado(PIN_LB);
  e.adelante = analogRead(PIN_JOY_X) - 512;
  e.derecha = analogRead(PIN_JOY_Y) - 512;
  e.shift = activo_ && apretado(PIN_CLICK);
  e.r = activo_ && apretado(PIN_Y);
  e.c = activo_ && apretado(PIN_B);
  e.clickIzq = activo_ && apretado(PIN_RB);
  e.clickDer = activo_ && apretado(PIN_LB);
  return e;
}
