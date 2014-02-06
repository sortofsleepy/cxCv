//
//  Helpers.h
//  TypeMotion
//
//  Created by Joseph Chow on 2/1/14.
//
//

#ifndef TypeMotion_Helpers_h
#define TypeMotion_Helpers_h

#include "cxCv.h"

namespace cxCv {
    
    class Helpers{
    public:
        /**
         Loads a image into a Surface.
         Note : images should be in assets
         */
        static ci::Surface loadImage(std::string path){
            ci::Surface image(cinder::loadImage(::cinder::app::loadAsset(path)));
            
            return image;
        };
        
        /**
         Converts a cv::Mat to a gl::Texture
         */
        ci::gl::Texture toTexture(cv::Mat from){
            ci::gl::Texture image(ci::fromOcv(from));
            return image;
        }
        
        
        
        /*============= OPENCV SPECIFIC ============= */
        /**
         Runs a OpenCV threshold algorithim on a Surface
         */
        static cv::Mat thresholdImage(ci::Surface32f inputs,float thresholdLevel){
            
        };
        
        
        
        
        
        
        
        
        /**
         Turns input into grayscale image
         */
        static cv::Mat toGray(cv::Mat input){
            cv::Mat gray;
            cv::cvtColor(input,gray,CV_RGB2GRAY);
            
            return gray;
        }
        

    };
    
    
};//end namespace

#endif
