
#include "../include/functions.hpp"

using namespace cv;

int main( int, char** argv )
{
  const char* window_name = "It's a feature, not a bug!";

  std::vector<Mat> images;
  std::pair<Mat, Mat> result;

  images = load_images("./sample/*");

  result = create_sharp_image_and_depth_map(images);

  imshow(window_name, result.first );
  waitKey(0);
  imshow(window_name, result.second);
  waitKey(0);

  imwrite( "result_images/color_sharp_image.jpg", result.first);
  imwrite( "result_images/depth_image.jpg", result.second);

  std::cout << "FINSIHED" << std::endl;

  images.clear();
  
  return 0;
}