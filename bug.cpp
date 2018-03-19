
#include "functions.hpp"

using namespace cv;

int main( int, char** argv )
{
  Mat src, src_gray;
  Mat grad;
  const char* window_name = "It's a feature, not a bug!";
  int counter = 0; 

  //Create List of images
  std::vector<Mat> images;
  std::vector<Mat> grey_image;
  std::vector<Mat> depth_image;
  std::vector<Mat> masks;
  std::vector<Mat> filtered_images;
  std::vector<double> weights;
  std::vector<String> images_filenames;
  
  std::string path = "./sample/*";
  cv::glob(path,images_filenames,false);  
  std::cout << "Number of files in directory " << images_filenames.size() << std::endl;
  
  double weight_diff = 1.00/(double) images_filenames.size();

  for(int iter= 0; iter < images_filenames.size()  ; ++iter){
    weights.push_back((double)iter*weight_diff);

    src = imread( images_filenames[iter], IMREAD_COLOR ); // Load an image
    images.push_back(src);
    if( !src.empty() ){ 
      ++counter; 
    }
    
    Mat grey = process_image(src);
    grey_image.push_back(grey);
  }

  std::pair<Mat,Mat> result;
  
  Mat grey = process_image(src);
  Mat winner_map = grey.clone();
  winner_map = 0;
  for(int iter= 1; iter < images.size()  ; ++iter){
    result = smart_max_mat( iter == 1 ? std::pair<Mat, Mat>( images[iter-1], grey_image[iter-1]) : result,
                           std::pair<Mat, Mat>( images[iter], grey_image[iter]), winner_map, weights[iter-1]);
  }

  medianBlur(winner_map, winner_map, 3);

  while(1){
    imshow( window_name, winner_map);
      waitKey(0);
    for(int iter= 0; iter < grey_image.size()  ; ++iter){     
      imshow( window_name, grey_image[iter]);
      waitKey(0);
    }
    imshow( window_name, result.second );
    waitKey(0);
    imshow( window_name, result.first );
    waitKey(0);

    imwrite( "depth_image.jpg", winner_map);
    imwrite( "color_sharp_image.jpg", result.first );
  }
  std::cout << "FINSIHED" << std::endl;

  return 0;
}