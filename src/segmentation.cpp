#include "segmentation.h"

namespace segmentation {

  /*
   * Segmentation of logarithmic chromatic image
   */
  cv::Mat seg_log_chromatic(cv::Mat log_image) {

    // Segment the image using the pre-defined threshold in the header of this file

    // Allocation of the original image
    cv::Mat log_image_seg = cv::Mat::zeros(log_image.rows, log_image.cols, CV_8UC1);
    
    // Make the segmentation by simple threholding
    for (int i = 0 ; i < log_image_seg.rows ; i++) {
      for (int j = 0 ; j < log_image_seg.cols ; j++) {
	bool condR = (log_image[0].at<double>(i, j) > MINLOGRG)&&(log_image[0].at<double>(i, j) < MAXLOGRG);
	bool condB = (logImage[1].at<double>(i, j) > MINLOGBG)&&(log_image[1].at<double>(i, j) < MAXLOGBG);
	/*----------- Red detection ----------*/
	log_image_seg.at<uchar>(i, j) = (condR&&condB) ? 255 : 0;
	/*----------- Have to be done for blue too ------------*/
      }
    }

    return logSegmentedImage;
  }

  /*
   * Segmentation of IHLS image
   */
  cv::Mat convert_ihls_to_nhs(cv::Mat ihls_image, int colour, int hue_max, int hue_min, int sat_min) {
    
    // Define the different thresholds
    if (colour == 2) {
      if (hue_max > 255 || hue_max < 0 || hue_min > 255 || hue_min < 0 || sat_min > 255 || sat_min < 0) {
	hue_min = R_HUE_MIN;
	hue_max = R_HUE_MAX;
	sat_min = R_SAT_MIN;
      }
    }
    else if (colour == 1) {
      hue_min = B_HUE_MIN;
      hue_max = B_HUE_MAX;
      sat_min = B_SAT_MIN;
    }
    else {
      hue_min = R_HUE_MIN;
      hue_max = R_HUE_MAX;
      sat_min = R_SAT_MIN;
    }

    // Check that the image has three channels
    cv::assert(ihls_image.channels() == 3);

    // Create the ouput the image
    cv::Mat nhs_image(ihls_image.rows, ihls_image.cols, CV_8UC1);

    // I put the if before for loops, to make the process faster.
    // Otherwise for each pixel it had to check this condition.
    // Nicer implementation could be to separate these two for loops in
    // two different functions, one for red and one for blue.
    if (colour == 1) {
      for (int i = 0; i < ihls_image.rows; ++i) {
	const uchar *ihls_data = ihls_image.ptr<uchar> (i);
	uchar *nhs_data = nhs_image.ptr<uchar> (i);
	for (int j = 0; j < ihls_image.cols; ++j) {
	  uchar s = *ihls_data++;
	  // Although l is not being used and we could have
	  // replaced the next line with ihls_data++
	  // but for the sake of readability, we left it as it it.
	  uchar l = *ihls_data++;
	  uchar h = *ihls_data++;
	  *nhs_data++ = (B_CONDITION) ? 255 : 0;
	}
      }
    }
    else {
      for (int i = 0; i < ihls_image.rows; ++i) {
	const uchar *ihls_data = ihls_image.ptr<uchar> (i);
	uchar *nhs_data = nhs_image.ptr<uchar> (i);
	for (int j = 0; j < ihls_image.cols; ++j) {
	  uchar s = *ihls_data++;
	  // Although l is not being used and we could have
	  // replaced the next line with ihls_data++
	  // but for the sake of readability, we left it as it it.
	  uchar l = *ihls_data++;
	  uchar h = *ihls_data++;
	  *nhs_data++ = (R_CONDITION) ? 255 : 0;
	}
      }
    }

    return nhs_image;
  }

}
