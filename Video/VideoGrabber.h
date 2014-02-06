//
//  VideoGrabber.h
//  TypeMotion
//
//  Created by Joseph Chow on 2/2/14.
//
//

#ifndef TypeMotion_VideoGrabber_h
#define TypeMotion_VideoGrabber_h
#include "cxCv.h"
#include <vector>

/**
 A wrapper around the Cinder::Capture 
 class
*/

namespace cxCv {
    class VideoGrabber{
        //our main video grabber
        ci::CaptureRef grabber;
        
        //width and height of image
        int32_t width,height;
        
        //if we have more devices.
        std::vector<ci::Capture::DeviceRef> devices;
        
        //texture used to display
        ci::gl::Texture video_t;
        
        
        
        //need to make a surface so we can manipulate pixels
        ci::Surface32f video_s;
        
        //used to store coordinates for where ot place texture
        ci::Vec3f loc;
    public:
        VideoGrabber();
        
        void update();
        void draw();
        
        ci::CaptureRef getGrabber();
        
    };
};
#endif
