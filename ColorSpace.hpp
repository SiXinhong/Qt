#ifndef OPENCV2_PS_COLORSPACE_HPP_
#define OPENCV2_PS_COLORSPACE_HPP_
#include <opencv2/core/core.hpp>

namespace cv {
	/**
	 * Convert BGR to HSB
	 *
	 * @param bgr [in] pointer to pixel data in Blue-Green-Red format, each channel's value range [0, 255]
	 * @param hsb [out] pointer to pixel data in Hue-Saturation-Brightness format
	 *         hue,  value range [0, 360]
	 *         saturation,  value range [0, 1]
	 *         brightness,   value range [0, 1]
	 */
	void BGR2HSB(const uchar *bgr, float *hsb);
	/**
	 * Convert HSB to BGR
	 *
	 * @param hsb [in] pointer to pixel data in Hue-Saturation-Brightness format
	 *         hue,  value range [0, 360]
	 *         saturation,  value range [0, 1]
	 *         brightness,   value range [0, 1]
	 *
	 * @param bgr [out] pointer to pixel data in Blue-Green-Red format, each channel's value range [0, 255]
	 */
	void HSB2BGR(const float *hsb, uchar *bgr);


	/**
	 * Convert RGB to HSB
	 *
	 * @param R [in] red,   value range [0, 255]
	 * @param G [in] green, value range [0, 255]
	 * @param B [in] blue,  value range [0, 255]
	 * @param h [out] hue,  value range [0, 360]
	 * @param s [out] saturation,  value range [0, 1]
	 * @param b [out] brightness,   value range [0, 1]
	 */
}
#endif /* OPENCV2_PS_COLORSPACE_HPP_ */
