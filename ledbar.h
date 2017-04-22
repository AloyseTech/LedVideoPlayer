#ifndef LEDBAR_H
#define LEDBAR_H
#include <QtNetwork>

#define LED_PER_MODULE (150)

class LedBar
{
public:
    LedBar();

    uint8_t pixelBuffer[3*LED_PER_MODULE];

    uint8_t status=0,ID=255;

    uint8_t fps=0;

    int32_t motorApos,motorBpos,motorAtarget,motorBtarget;

    QHostAddress IP;
    bool valid=false;

};


#endif // LEDBAR_H
