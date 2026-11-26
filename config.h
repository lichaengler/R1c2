#pragma once
#include <Arduino.h>

// Pines (placa Arduino Leonardo)
constexpr int PIN_RB = 5;
constexpr int PIN_LB = 9;
constexpr int PIN_Y = 8;
constexpr int PIN_B = 7;
constexpr int PIN_START = 6;
constexpr int PIN_CLICK = A1;
constexpr int PIN_JOY_X = A3;
constexpr int PIN_JOY_Y = A2;

// Ajustes de la mira y del joystick
constexpr float SENS = 0.002f;   // velocidad de la mira (con LB va a la mitad)
constexpr int ZONA_MUERTA = 250; // giros más chicos se ignoran (evita temblor)
constexpr int UMBRAL = 200;      // cuánto empujar el joystick para caminar
constexpr float SUAVIZADO = 0.3f;// cuánto del giro nuevo se mezcla en cada vuelta

// Tiempos
constexpr unsigned long START_MS = 1000;    // START mantenido = recalibrar
constexpr unsigned long DEBOUNCE_MS = 30;   // rebote del botón START
constexpr unsigned long LOOP_MS = 5;        // retardo al final de cada vuelta

// MPU6050
constexpr byte MPU_ADDR = 0x68;
constexpr byte REG_GYRO_Y = 0x45;           // Y y Z seguidos (salteamos X)
constexpr byte REG_PWR_MGMT_1 = 0x6B;        // despertar el sensor
constexpr int MUESTRAS_CAL = 100;
constexpr unsigned long RETARDO_CAL_MS = 5;
