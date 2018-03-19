#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

using namespace cv;

Mat process_image(Mat img);
std::pair<Mat, Mat> smart_max_mat(std::pair<Mat, Mat> ftImgs, std::pair<Mat, Mat> sImgs, Mat winner_map, double iter);

#endif