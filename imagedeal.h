#ifndef IMAGEDEAL_H
#define IMAGEDEAL_H

class ImageDeal
{
public:
    ImageDeal();
    QImage Img;
    QImage AdjustBrightness(QImage Img, int iBrightValue);//调亮度
};

#endif // IMAGEDEAL_H
