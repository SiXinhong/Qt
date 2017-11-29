#include "imagedeal.h"

ImageDeal::ImageDeal()
{
}
ImageDeal::ImageDeal(QImage Img)
{
    this->Img = Img;
}
QImage ImageDeal::AdjustBrightness(QImage Img, int iBrightValue)
{
    int red, green, blue;
    int pixels = Img.width() * Img.height();
    unsigned int *data = (unsigned int *)Img.bits();

    for (int i = 0; i < pixels; ++i)
    {
        red= qRed(data[i])+ iBrightValue;
        red = (red < 0x00) ? 0x00 : (red > 0xff) ? 0xff : red;
        green= qGreen(data[i]) + iBrightValue;
        green = (green < 0x00) ? 0x00 : (green > 0xff) ? 0xff : green;
        blue= qBlue(data[i]) + iBrightValue;
        blue =  (blue  < 0x00) ? 0x00 : (blue  > 0xff) ? 0xff : blue ;
        data[i] = qRgba(red, green, blue, qAlpha(data[i]));
    }

    return Img;
}
