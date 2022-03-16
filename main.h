#ifndef _POKETCH_H_
#define _POKETCH_H_
#include <M5Core2.h>
#include <LovyanGFX.hpp>
static LGFX lcd;

#include "src/lib/printNumber.h"
#include "src/lib/printButton.h"
static PrintNumber prn(&lcd);

#define POK_WHITE 0x75AE
#define POK_GRAY lcd.color565(82, 132, 82)
#define POK_DARK_GRAY lcd.color565(57, 82, 49)
#define POK_BLACK lcd.color565(5, 22, 2)

#define WATCH_MODE_NUM 4 // モードの総数
#define WATCH_CLOCK 0
#define WATCH_DRAW 1
#define WATCH_PEDOMETER 2
#define WATCH_COINTOSS 3

// バイブレーション
void buttonVib(int duration)
{
    M5.Axp.SetLDOEnable(3, true);
    delay(duration);
    M5.Axp.SetLDOEnable(3, false);
}

#endif