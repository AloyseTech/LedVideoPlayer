#include "surface.h"


MyVideoSurface::MyVideoSurface(LedBar *ledbarparam, int numledbar)
{
    numberOfModules=numledbar;
    ledmodules=ledbarparam;

    fullprev.move(600+10,22);
    fullprev.resize(300,300);
    fullprev.setWindowTitle("Full Preview");
    fullprev.setWindowFlags(Qt::Tool);
}

QList<QVideoFrame::PixelFormat> MyVideoSurface::supportedPixelFormats(
        QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const
{
    Q_UNUSED(handleType);

    // Return the formats you will support
    return QList<QVideoFrame::PixelFormat>() << QVideoFrame::Format_BGR24<< QVideoFrame::Format_ARGB32;
}

bool MyVideoSurface::present(const QVideoFrame &frame)
{
    //Q_UNUSED(frame);
    QVideoFrame cloneFrame(frame);
    cloneFrame.map(QAbstractVideoBuffer::ReadOnly);
    const QImage img(cloneFrame.bits(),cloneFrame.width(),cloneFrame.height(),QImage::Format_ARGB32);

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

                /*
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
                */

                if(X<LED_PER_MODULE)
                {
                    ledmodules[Y].pixelBuffer[3*X]=redValue;
                    ledmodules[Y].pixelBuffer[3*X+1]=greenValue;
                    ledmodules[Y].pixelBuffer[3*X+2]=blueValue;
                }
            }
            //lineprev[Y].setPixmap(QPixmap::fromImage(buffer));
            //lineprev[Y].show();
        }
    }

    /*
    if(showModulesPrev)
    {
        paint.end();
        modulesprev.setPixmap(QPixmap::fromImage(buffer));
        modulesprev.update();
    }
    */
    if(showFullPrev)
    {
        fullprev.setPixmap(QPixmap::fromImage(img.scaled(300,300,Qt::IgnoreAspectRatio,Qt::FastTransformation)));
        fullprev.update();
    }

    cloneFrame.unmap();
    return true;
}

void MyVideoSurface::onQuit()
{
    fullprev.close();
}

void MyVideoSurface::setShowFullPrev(bool b)
{
    showFullPrev=b;
    if(showFullPrev)
        fullprev.show();
    else
        fullprev.close();
}

