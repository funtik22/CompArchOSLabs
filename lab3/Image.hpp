#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_

#include <opencv2/opencv.hpp> 
#include <string>

class Image{
    cv::Mat image;
    std::string pathToImage;
    std::string pathToNewImage;

    public:
        Image():image(), pathToImage(), pathToNewImage(){}
        Image(std::string pathToImage_, std::string pathToNewImage_):
            pathToImage(pathToImage_), pathToNewImage(pathToNewImage_), image(){}

        std::string getPathToImage() const;
        std::string getPathToNewImage() const;
        void setImage(cv::Mat image_);
        cv::Mat geImage() const;
};

#endif