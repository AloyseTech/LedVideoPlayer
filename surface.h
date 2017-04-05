#ifndef SURFACE_H
#define SURFACE_H
#include "QAbstractVideoSurface"
#include "ledbar.h"
#include "qlabel.h"
#include "qpainter.h"

#define LED_MODULE_PREV_WIDTH       600
#define LED_MODULE_PREV_HEIGTH      8


class MyVideoSurface : public QAbstractVideoSurface
{
public:

    MyVideoSurface(LedBar *ledbarparam, int numledbar)
    {
        numberOfModules=numledbar;
        ledmodules=ledbarparam;
        lineprev = new QLabel[numberOfModules];

        fullprev.move(LED_MODULE_PREV_WIDTH+4,22);
        fullprev.resize(300,300);
        fullprev.setWindowTitle("Full Preview");
        fullprev.setWindowFlags(Qt::Tool);

        modulesprev.move(0,0);
        modulesprev.resize(LED_MODULE_PREV_WIDTH,4+numberOfModules*(LED_MODULE_PREV_HEIGTH+4));
        modulesprev.setWindowTitle("Modules Preview");
        modulesprev.setWindowFlags(Qt::Tool);

        surfaceTimeElapsed=new QElapsedTimer();
        surfaceTimeElapsed->start();
    }
    LedBar *ledmodules;
    int numberOfModules=0;

    QLabel fullprev, modulesprev;
    QLabel *lineprev;
    QPainter paint;
    QImage buffer;

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const
    {
        Q_UNUSED(handleType);

        // Return the formats you will support
        return QList<QVideoFrame::PixelFormat>() << QVideoFrame::Format_BGR24<< QVideoFrame::Format_ARGB32;
    }

private slots:
    bool present(const QVideoFrame &frame)
    {
        //Q_UNUSED(frame);
        // Handle the frame and do your processing
        QVideoFrame cloneFrame(frame);
        cloneFrame.map(QAbstractVideoBuffer::ReadOnly);
        const QImage img(cloneFrame.bits(),cloneFrame.width(),cloneFrame.height(),QImage::Format_ARGB32);

        if(strobePeriod>0 && (surfaceTimeElapsed->elapsed()-lastStrobe)>strobePeriod)
        {
            strobing=1-strobing;
            lastStrobe=surfaceTimeElapsed->elapsed();
        }
        else if (strobePeriod==0)
            strobing=false;

        if(showModulesPrev)
        {
            buffer = QImage(QSize(LED_MODULE_PREV_WIDTH,4+numberOfModules*(LED_MODULE_PREV_HEIGTH+4)),QImage::Format_RGB888);
            buffer.fill(Qt::gray);
            paint.begin(&buffer);
        }

        for(int Y = 0; Y < img.height(); Y++)
        {
            if(Y<numberOfModules)
            {
                const uint8_t* pPixel = img.scanLine(Y);

                for(int X = 0; X < img.width(); X++)
                {
                    const int Blue = *pPixel++;
                    const int Green = *pPixel++;
                    const int Red = *pPixel++;
                    const int AA = *pPixel++;

                    int redValue = Red;
                    int greenValue = Green;
                    int blueValue = Blue;

                    if(redMod>0)
                        redValue=redMod;
                    if(greenMod>0)
                        greenValue=greenMod;
                    if(blueMod>0)
                        blueValue=blueMod;

                    if(strobing)
                    {
                        redValue=0;
                        greenValue=0;
                        blueValue=0;
                    }

                    if(X<LED_PER_MODULE)
                    {
                        ledmodules[Y].pixelBuffer[3*X]=redValue;
                        ledmodules[Y].pixelBuffer[3*X+1]=greenValue;
                        ledmodules[Y].pixelBuffer[3*X+2]=blueValue;

                        if(showModulesPrev)
                        {
                            paint.fillRect(4+X*LED_MODULE_PREV_WIDTH/LED_PER_MODULE,4+Y*(LED_MODULE_PREV_HEIGTH+4),LED_MODULE_PREV_WIDTH/LED_PER_MODULE,
                                           LED_MODULE_PREV_HEIGTH,QColor((uint8_t)redValue,(uint8_t)greenValue,(uint8_t)blueValue));
                        }
                    }
                }
                //lineprev[Y].setPixmap(QPixmap::fromImage(buffer));
                //lineprev[Y].show();
            }
        }

        if(showModulesPrev)
        {
            paint.end();
            modulesprev.setPixmap(QPixmap::fromImage(buffer));
            modulesprev.update();
        }
        if(showFullPrev)
        {
            fullprev.setPixmap(QPixmap::fromImage(img.scaled(300,300,Qt::IgnoreAspectRatio,Qt::FastTransformation)));
            fullprev.update();
        }

        cloneFrame.unmap();
        return true;
    }

public:
    void onQuit()
    {
        fullprev.close();
        modulesprev.close();
        for(int i =0; i<numberOfModules; i++)
            lineprev[i].close();
    }

    void setShowFullPrev(bool b)
    {
        showFullPrev=b;
        if(showFullPrev)
            fullprev.show();
        else
            fullprev.close();
    }

    void setShowModulesPrev(bool b)
    {
        showModulesPrev=b;
        if(showModulesPrev)
            modulesprev.show();
        else
            modulesprev.close();
    }

    void setStrobePeriod(uint64_t p)
    {
        strobePeriod=p;
    }

    uint64_t getStrobePeriod()
    {
        return strobePeriod;
    }

    void setRed(uint8_t v)
    {
        redMod=v;
    }
    void setGreen(uint8_t v)
    {
        greenMod=v;
    }
    void setBlue(uint8_t v)
    {
        blueMod=v;
    }


private:
    bool showFullPrev=0,showModulesPrev=0;
    //effects
    bool strobing=0;
    uint8_t redMod=0,greenMod=0,blueMod=0;
    uint64_t strobePeriod=0,lastStrobe=0;
    QElapsedTimer *surfaceTimeElapsed;


};

#endif // SURFACE_H
