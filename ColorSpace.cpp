#include "ColorSpace.hpp"
#include <iostream>
using namespace std;

#define MAX2(a, b) ( (a) > (b) ) ?  (a) : (b)
#define MAX3(a,b,c) ( ( (a) > (b) ) ?  MAX2( a, c) : MAX2( b, c ) )

#define MIN2(a, b)  ( (a) < (b) ) ?  (a) : (b)
#define MIN3(a,b,c) ( ( (a) < (b) ) ?  MIN2( a, c ) : MIN2( b, c ) )


#define SWAP(a, b, t)  do { t = a; a = b; b = t; } while(0)
#define CLIP_RANGE(value, min, max)  ( (value) > (max) ? (max) : (((value) < (min)) ? (min) : (value)) )
#define COLOR_RANGE(value)  CLIP_RANGE(value, 0, 255)


namespace cv {
/**
 * Convert RGB to HSB
 *
 * @param bgr [in] pointer to pixel data in Blue-Green-Red format, each channel's value range [0, 255]
 * @param hsb [out] pointer to pixel data in Hue-Saturation-Brightness format
 *         hue,  value range [0, 360]
 *         saturation,  value range [0, 1]
 *         brightness,   value range [0, 1]
 */
void BGR2HSB(const uchar *bgr, float *hsb)
{
	uchar sorted[3], temp;
	memcpy(sorted, bgr,3);
	if (sorted[1] > sorted[0]) SWAP(sorted[0], sorted[1], temp);
	if (sorted[2] > sorted[1]) SWAP(sorted[1], sorted[2], temp);
	if (sorted[1] > sorted[0]) SWAP(sorted[0], sorted[1], temp);

	uchar max = sorted[0];
	uchar min = sorted[2];

	hsb[2] = max / 255.0;
	hsb[1] = max == 0 ? 0 : (max - min) / (float) max;

	hsb[0] = 0;
	if (max == bgr[2] && bgr[1] >= bgr[0]) {
		hsb[0] = ( bgr[1] - bgr[0] ) * 60.0 / (max - min) + 0;
	} else if (max == bgr[2] && bgr[1] < bgr[0]) {
		hsb[0] = (bgr[1] - bgr[0]) * 60.0 / (max - min) + 360;
	} else if (max == bgr[1]) {
		hsb[0] = (bgr[0] - bgr[2]) * 60.0 / (max - min) + 120;
	} else if (max == bgr[0]) {
		hsb[0] = (bgr[2] - bgr[1]) * 60.0 / (max - min) + 240;
	}
}


/**
 *  Convert HSB to BGR
 *
 * @param hsb [in] pointer to pixel data in Hue-Saturation-Brightness format
 *         hue,  value range [0, 360]
 *         saturation,  value range [0, 1]
 *         brightness,   value range [0, 1]
 *
 * @param bgr [out] pointer to pixel data in Blue-Green-Red format, each channel's value range [0, 255]
 */
void HSB2BGR(const float *hsb, uchar *bgr)
{
	float r = 0, g = 0, b = 0;
	int i = (int) (int(hsb[0] / 60) % 6);
	float f = (hsb[0] / 60.0) - i;
	float p = hsb[2] * (1 - hsb[1]);
	float q = hsb[2] * (1 - f * hsb[1]);
	float t = hsb[2] * (1 - (1 - f) * hsb[1]);
	switch (i) {
	case 0:
		r = hsb[2];
		g = t;
		b = p;
		break;
	case 1:
		r = q;
		g = hsb[2];
		b = p;
		break;
	case 2:
		r = p;
		g = hsb[2];
		b = t;
		break;
	case 3:
		r = p;
		g = q;
		b = hsb[2];
		break;
	case 4:
		r = t;
		g = p;
		b = hsb[2];
		break;
	case 5:
		r = hsb[2];
		g = p;
		b = q;
		break;
	default:
		break;
	}

	bgr[0] = int(b * 255);
	bgr[1] = int(g * 255);
	bgr[2] = int(r * 255);
}
} /* namespace cv */
