#ifndef SURFACE_H
#define SURFACE_H
#include "QAbstractVideoSurface"
#include "ledbar.h"
#include "qlabel.h"

class MyVideoSurface : public QAbstractVideoSurface
{
public:
    MyVideoSurface(LedBar *ledbarparam, int numledbar);

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const;
    void onQuit();
    void setShowFullPrev(bool b);

private slots:
    bool present(const QVideoFrame &frame);

private:
    LedBar *ledmodules;
    int numberOfModules=0;
    bool showFullPrev=0;
    bool strobing=0;
    QLabel fullprev;
};

#endif // SURFACE_H
