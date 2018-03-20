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

/**
 * Function for read file names of images from given path
 * 
 * @param path as folder contains images
 * @return vector of file names
 * **/
std::vector<String> read_sample_images_names(std::string path);

/**
 * Function for load images to cv::Mat objects from given path
 * 
 * @param path as folder contains images
 * @return vector of loaded images as cv::Mat objects
 * **/
std::vector<Mat> load_images(std::string path);

/**
 * Function for creation of sharp image and depth image from given sequence
 * 
 * @param images as vector of images as cv::Mat objects
 * @return pair of cv:Mat objects, where first is sharp image and second is depth map
 * **/
std::pair<Mat, Mat> create_sharp_image_and_depth_map(std::vector<Mat> images);

/**
 * Function for smart finding maximum values from given pair of views in gray scale. One view is a pair of color and grey image. Grey image is
 * image of edges. 
 * 
 * @param first_image as first pair of color and edges
 * @param second_image as second pair of color and edges
 * @param depth_map as created depth_map
 * @param color_modificator as parameter for creating depth_map pixels
 * @return pair of images with winning color and edges values (criterium is a maximum value in edge_map)
 * **/
std::pair<Mat, Mat> smart_max_mat(std::pair<Mat, Mat> first_image, std::pair<Mat, Mat> second_image, Mat depth_map, double color_modificator);

/**
 * Function for process image and create edge map in gray scale
 * 
 * @param img as image to process
 * @return edge map in gray scale
 * **/
Mat create_edge_map(Mat img);

#endif