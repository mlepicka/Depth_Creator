#include "../include/functions.hpp"



std::vector<String> read_sample_images_names(std::string path){
  std::vector<String> images_filenames;

  cv::glob(path, images_filenames, false);  
  std::cout << "Number of files in directory " << images_filenames.size() << std::endl;

  return images_filenames;
}

std::vector<Mat> load_images(std::string path){
  std::vector<Mat> images;
  std::vector<String> images_filenames;
  Mat src;

  images_filenames = read_sample_images_names(path);
  
  for(int iter= 0; iter < images_filenames.size()  ; ++iter){
    src = imread(images_filenames[iter], IMREAD_COLOR ); // Load an image
    images.push_back(src);
  }

  return images;
}

std::pair<Mat, Mat> create_sharp_image_and_depth_map(std::vector<Mat> images){
  std::vector<Mat> edge_maps;
  std::vector<double> weights;
  std::pair<Mat,Mat> result;

  double weight_diff = 255.00/(double) images.size();

  for(int iter= 0; iter < images.size()  ; ++iter){
      Mat edge_map = create_edge_map(images[iter]);
      edge_maps.push_back(edge_map);
      weights.push_back((double)iter*weight_diff);
  }

  Mat depth_map = edge_maps[0].clone();
  depth_map = 0;

  for(int iter= 1; iter < images.size()  ; ++iter){
    result = smart_max_mat(iter == 1 ? std::pair<Mat, Mat>(images[iter-1], edge_maps[iter-1]) : result,
                           std::pair<Mat, Mat>(images[iter], edge_maps[iter]), 
                           depth_map, weights[iter]);
  }
  medianBlur(depth_map, depth_map, 3);

  //second was just image with edges, we need depth map
  result.second = depth_map;

  return result;
}

std::pair<Mat, Mat> smart_max_mat(std::pair<Mat, Mat> firstImage, std::pair<Mat, Mat> secondImage, Mat depth_map, double color_modificator){
  Mat color  = firstImage.first.clone();
  Mat grey  = firstImage.second.clone();

  for(int j=0; j< grey.rows; j++){
    for (int i=0; i< grey.cols; i++){  
      if((uchar)firstImage.second.at<uchar>(j,i) <= (uchar)secondImage.second.at<uchar>(j,i)){ 
        //second mat grey value is bigger - more edgy -> sharper part of image
        color.at<Vec3b>(j,i) = secondImage.first.at<Vec3b>(j,i);
        grey.at<uchar>(j,i) = secondImage.second.at<uchar>(j,i);
        depth_map.at<uchar>(j,i) = (int)(255.00-color_modificator);
      }
    }
  }
  return std::pair<Mat, Mat>(color, grey);
}

Mat create_edge_map(Mat img) {
  int scale = 1;
  int delta = 0;
  int ddepth = CV_16S;

  Mat src_gray, edge_map;
  cvtColor( img, src_gray, COLOR_BGR2GRAY );

  Mat grad_x, grad_y;
  Mat abs_grad_x, abs_grad_y;

  Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
  Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );

  convertScaleAbs( grad_x, abs_grad_x );
  convertScaleAbs( grad_y, abs_grad_y );
  addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, edge_map);

  GaussianBlur(edge_map, edge_map, Size(5,5), 0, 0, BORDER_DEFAULT );

  return edge_map;
}