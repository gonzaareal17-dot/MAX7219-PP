#include <LedControl.h>
#include <TM1637Display.h>
#include <TimeLib.h>

#define CLK 6
#define DIO 7

TM1637Display reloj(CLK, DIO);

const int minutos = 45;
const int segundos = 0;
time_t finalperiodo;
bool cronometro = true;

LedControl lc = LedControl(13, 11, 12, 1);

int periodos = 1;

const int MASLOCAL = 2;
const int MENOSLOCAL = 3;
const int MASVIS = 4;
const int MENOSVIS = 5;
const int MAS10 = A0;
const int MAS5 = A1;
const int inicio = A2;
const int reinicio = A3;

int local = 0;
int visitante = 0;

bool MLANT = HIGH;
bool MELANT = HIGH;
bool MVANT = HIGH;
bool MEVANT = HIGH;

void MARCADOR()
{
  lc.setDigit(0, 1, local / 10, false);
  lc.setDigit(0, 0, local % 10, false);

  lc.setDigit(0, 3, visitante / 10, false);
  lc.setDigit(0, 2, visitante % 10, false);

  lc.setDigit(0, 4, periodos, false);
}
void setup()
{
  pinMode(MASLOCAL, INPUT_PULLUP);
  pinMode(MENOSLOCAL, INPUT_PULLUP);
  pinMode(MASVIS, INPUT_PULLUP);
  pinMode(MENOSVIS, INPUT_PULLUP);

  lc.shutdown(0, false);
  lc.setScanLimit(0, 4);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);

  reloj.setBrightness(5); 
  setTime(0, 0, 0, 1, 1, 2026);
  time_t tiempototal= (minutos * 60) + segundos;
  finalperiodo = now() + tiempototal;

  MARCADOR();
}
void loop(){
  bool ML = digitalRead(MASLOCAL);
  bool MEL = digitalRead(MENOSLOCAL);
  bool MV = digitalRead(MASVIS);
  bool MEV = digitalRead(MENOSVIS);

    if (ML == LOW && MLANT == HIGH){
      if (local<99){
        local++;
      }
      MARCADOR();
    }
    if (MEL == LOW && MELANT == HIGH){
      if (local>0){
        local--;
      }
      MARCADOR();
    }
    if (MV == LOW && MVANT == HIGH){
      if (visitante<99){
        visitante++;
      }
      MARCADOR();
    }
    if (MEV == LOW && MEVANT == HIGH){
      if (visitante>0){
        visitante--;
      }
      MARCADOR();
    }
    MLANT = ML;
    MELANT = MEL;
    MVANT = MV;
    MEVANT = MEV;

    delay(25);
    if (cronometro){
      time_t tiemporeal = now();
      if (tiemporeal < finalperiodo){
        time_t tiemporestante = finalperiodo - tiemporeal;
        int Minutos = tiemporestante / 60;
        int Segundos = tiemporestante % 60;
        int mostrar = (Minutos * 100) + Segundos;
        reloj.showNumberDecEx(mostrar, 0b01000000, true);
      }
    else{
      cronometro = false;
      periodos = 1;
      reloj.showNumberDec(0, true);
      periodos++;
      if(periodos > 9) { 
      }
      MARCADOR();
    }
  }
}
