//
//  cxCv.h
//  TypeMotion
//
//  Created by Joseph Chow on 2/1/14.
//
//

#ifndef TypeMotion_cxCv_h
#define TypeMotion_cxCv_h

/**
 All our includes go here.
*/

#include "cinder/ImageIo.h"
#include "CinderOpenCV.h"
#include "cinder/Surface.h"
#include "cinder/gl/Texture.h"
#include "Helpers.h"
#include "cinder/Color.h"
#include "cinder/Capture.h"

/**
 Common functionality that could be used 
 across all classes ought to go here.
 */

namespace cxCv{
    /**
        Color used for debugging stuff.
        Default is red
     */
    static ci::Color debugColor = ci::Color(1,1,0);
    
    static cv::Mat toGray(cv::Mat img){
        cv::Mat thresh;
        if(img.channels() == 1) {
            thresh = img.clone();
        } else if(img.channels() == 3) {
            cv::cvtColor(img, thresh, CV_RGB2GRAY);
        } else if(img.channels() == 4) {
            cv::cvtColor(img, thresh, CV_RGBA2GRAY);
        }
        
        return thresh;
    }
};
#endif
