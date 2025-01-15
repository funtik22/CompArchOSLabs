#include "Image.hpp"

std::string Image::getPathToImage() const{
    return pathToImage;
}

std::string Image::getPathToNewImage() const{
    return pathToNewImage;
}

void Image::setImage(cv::Mat image_){
    image = image_;
}

cv::Mat Image::geImage() const{
    return image;
}