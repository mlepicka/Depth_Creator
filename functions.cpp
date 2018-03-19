#include "functions.hpp"

int scale = 1;
int delta = 0;
int ddepth = CV_16S;

Mat process_image(Mat img) {
  Mat src_gray, grad, g;
  cvtColor( img, src_gray, COLOR_BGR2GRAY );

  Mat grad_x, grad_y;
  Mat abs_grad_x, abs_grad_y;

  Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
  Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );

  convertScaleAbs( grad_x, abs_grad_x );
  convertScaleAbs( grad_y, abs_grad_y );
  addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

  GaussianBlur(grad, grad, Size(5,5), 0, 0, BORDER_DEFAULT );

  return grad;
}

std::pair<Mat, Mat> smart_max_mat(std::pair<Mat, Mat> fImgs, std::pair<Mat, Mat> sImgs, Mat winner_map, double iter){
  Mat color  = fImgs.first.clone();
  Mat grey  = fImgs.second.clone();
  int mask_size = 1;
  for(int j=0;j< grey.rows-mask_size+1;j++){
    for (int i=0;i< grey.cols-mask_size+1;i++){  
      if((uchar)fImgs.second.at<uchar>(j,i) > (uchar)sImgs.second.at<uchar>(j,i)){ //first mat grey value is bigger
        color.at<Vec3b>(j,i) = fImgs.first.at<Vec3b>(j,i);
        grey.at<uchar>(j,i) = fImgs.second.at<uchar>(j,i);
      }else{  //second mat grey value is bigger
        color.at<Vec3b>(j,i) = sImgs.first.at<Vec3b>(j,i);
        grey.at<uchar>(j,i) = sImgs.second.at<uchar>(j,i);
        winner_map.at<uchar>(j,i) = 255-(int)(iter*(255.00));
      }
    }
  }
  return std::pair<Mat, Mat>(color, grey);
}