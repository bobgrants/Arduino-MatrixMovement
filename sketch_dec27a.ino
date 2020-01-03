//www.elegoo.com
//2016.12.9

//We always have to include the library
#include "LedControl.h"


LedControl lc = LedControl(12, 10, 11, 1);

int PinX = 0;
int PinY = 1;
int currentCol, currentRow;
bool Up, Down, Left, Right;

void setup() 
{
  currentCol = 0;
  currentRow = 1;

  lc.shutdown(0, false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0, 0);
  /* and clear the display */
  lc.clearDisplay(0);

  lc.setColumn(0, currentCol, currentRow);

  Serial.begin(9600);
}

void loop()
{
  JoystickControlX();
  JoystickControlY();
  MovePoint();
}

void JoystickControlX() 
{
  if (analogRead(PinX) < 450) {
    Left = true;
    Right = false;
    //    Serial.print("Left: ");
    //    Serial.print(Left);
    //    Serial.print("\n");
  }
  else if (analogRead(PinX) > 550) {
    Right = true;
    Left = false;
  }
  else {
    Right = false;
    Left = false;
    return;
  }
}

void JoystickControlY() 
{
  if (analogRead(PinY) < 450) {
    Down = false;
    Up = true;
  }
  else if (analogRead(PinY) > 550) {
    Up = false;
    Down = true;
  }
  else {
    Up = false;
    Down = false;
    return;
  }
}


void MovePoint()
{
  if (Left == true)
  {
    currentCol--;
    if (currentCol < 0) {
      currentCol = 0;
    }
  }

  if (Right == true)
  {
    currentCol++;
    if (currentCol > 7) {
      currentCol = 7;
    }
  }

  if (Up == true)
  {
    currentRow = currentRow * 2;
    if (currentRow > 128) {
      currentRow = 128;
    }
  }

  if (Down == true) {
    currentRow = currentRow / 2;
    if (currentRow < 1) {
      currentRow = 1;
    }
  }

  lc.clearDisplay(0);
  lc.setColumn(0, currentCol, currentRow);

  delay(100);
}
