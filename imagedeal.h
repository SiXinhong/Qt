#ifndef IMAGEDEAL_H
#define IMAGEDEAL_H

class ImageDeal
{
public:
    ImageDeal();
    QImage Img;
    QImage AdjustBrightness(QImage Img, int iBrightValue);//������
};

#endif // IMAGEDEAL_H
