#include <thread>
#include <iostream>
#include <opencv2/opencv.hpp> 
#include "Buffer.hpp"
#include "Image.hpp"
#include <dirent.h>
#include <atomic>
#include "Time.cpp"

#define NUM_PRODUCERS 5
#define NUM_CONSUMERS 5
#define PRODUCER_DELAY_TO_PRODUCE 1
#define CONSUMER_DELAY_TO_CONSUME 3


std::atomic<int> num_producers_working(0);

void consumeImage(Buffer<Image> &buffer);
void produceImage(Buffer<Image> &buffer, std::vector<Image> &images, int start, int end);
std::vector<Image> getImagesList(const char * initialDir, const char * resultDir);


int main(int argc, const char * argv[]){
    LogDuration ld("1");


    if (argc != 3) { 
        printf("usage: buffer.out <Initial_Directory_Images_Path> <Result_Directory_Images_Path>\n"); 
        return -1; 
    }
 

    std::cout << "Executing code in main...\n";
    
    srand (time(NULL));
    
    Buffer<Image> buffer;
    
    std::vector<std::thread> producers_and_consumers;
    
    std::vector<Image> images = getImagesList(argv[1], argv[2]);
    if(images.empty()){
        perror("invalid path to directories or empty folders");
        return -1;
    }
    int step = (images.size()/NUM_PRODUCERS);
        // Create producers
    for(int i = 0; i < NUM_PRODUCERS; ++i)
            producers_and_consumers.push_back(std::thread(produceImage, 
            std::ref(buffer), std::ref(images), step*i, step*(i+1)));
 
        // Create consumers
    for(int i = 0; i < NUM_CONSUMERS; ++i)
            producers_and_consumers.push_back(std::thread(consumeImage, std::ref(buffer)));
 
        // Wait for consumers and producers to finish
    for(auto& t : producers_and_consumers)
            t.join();

    
    std::cout << "Done!\n";
}


void consumeImage(Buffer<Image> &buffer) {

    while(num_producers_working == 0) std::this_thread::yield();

    while(num_producers_working != 0 || buffer.getSize() > 0){
        Image img = buffer.consume(1);
        cv::Mat newImage;
        bitwise_not(img.geImage(), newImage);
        cv::imwrite(img.getPathToNewImage(), newImage);
        std::this_thread::sleep_for(std::chrono::nanoseconds(CONSUMER_DELAY_TO_CONSUME));
    }
}

void produceImage(Buffer<Image> &buffer, std::vector<Image> &images, int start, int end) {
    ++num_producers_working;
    for (int i = start; i < end; i++) {
        images[i].setImage(cv::imread(images[i].getPathToImage(), 1));
        buffer.produce(i, images[i]);
        std::this_thread::sleep_for(std::chrono::nanoseconds(PRODUCER_DELAY_TO_PRODUCE));
    }
    --num_producers_working;
}

std::vector<Image> getImagesList(const char * initialDirName, const char * resultDirName){
    DIR *initialDir = opendir(initialDirName), *resultDir = opendir(resultDirName);
    std::vector<Image> images;
    if(initialDir == NULL || resultDir == NULL){
        perror("Invalid path to directories");
        return images;
    }

    struct dirent *ent;
    while ((ent = readdir (initialDir)) != NULL) {
        std::string pathToImage = "", pathToNewImage = "";
        pathToImage.append(std::string(initialDirName).append("/").append(std::string(ent->d_name)));
        pathToNewImage.append(std::string(resultDirName).append("/").append(std::string(ent->d_name)));
        std::string extension = pathToImage.substr(pathToImage.find_last_of(".") + 1);
        if(extension == "png" || extension == "jpg"){
            images.push_back(Image(pathToImage, pathToNewImage));
        }
    }
    return images;
}