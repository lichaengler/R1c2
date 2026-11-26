// PISTOLA COMO MOUSE Y TECLADO
// Placa en el IDE: "Arduino Leonardo".
// Arranca en pausa. START: toque corto = activa o pausa el control.
//                         mantener 1 segundo = recalibra (pistola apoyada y quieta).
//   Mover la pistola = mouse     Joystick = W A S D     Click del joystick = Shift
//   RB = click izquierdo         LB = click derecho y mira más lenta
//   Y = R (recargar)             B = C (agacharse)
//
// Estructura: config.h (ajustes) · Giroscopio (sensor) · Entrada (botones)
//             Salida (HID) · este archivo (flujo principal).

#include "config.h"
#include "Giroscopio.h"
#include "Entrada.h"
#include "Salida.h"

Giroscopio giro;
Entrada entrada;
Salida salida;

void setup() {
  giro.begin();
  entrada.begin();
  salida.begin();
  giro.calibrar();
}

void loop() {
  EstadoEntrada ev = entrada.actualizar();
  if (ev.recalibrar) giro.calibrar();

  giro.leer();
  if (ev.activo) {
    Vector d = giro.deltaMouse(ev.lenta);
    salida.mover(d.x, d.y);
  }
  salida.aplicar(ev);

  delay(LOOP_MS);
}
