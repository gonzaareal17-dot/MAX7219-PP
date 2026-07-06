#include <LedControl.h>

LedControl lc = LedControl(13, 11, 12, 1);

const int MASLOCAL = 2;
const int MENOSLOCAL = 3;
const int MASVIS = 4;
const int MENOSVIS = 5;

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
}
void setup()
{
  pinMode(MASLOCAL, INPUT_PULLUP);
  pinMode(MENOSLOCAL, INPUT_PULLUP);
  pinMode(MASVIS, INPUT_PULLUP);
  pinMode(MENOSVIS, INPUT_PULLUP);

  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);

  MARCADOR();
}
void loop()
{
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
}