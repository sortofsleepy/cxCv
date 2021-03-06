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
typedef std::shared_ptr<class VideoGrabber>VidGrabber;
    class VideoGrabber{
        //our main video grabber
        ci::CaptureRef grabber;
        
        //width and height of image
        int32_t width,height;
        
        //if we have more devices.
        std::vector<ci::Capture::DeviceRef> devices;
        
        //texture used to display
        ci::gl::TextureRef video_t;
        
        //used to store coordinates for where ot place texture
        ci::Vec3f loc;
        
        ci::Surface video_s;
        
        //should we mirror the video? Default = true
        bool shouldMirror;
    public:
        VideoGrabber();
        bool mirror();
        static VidGrabber create(){
            return VidGrabber(new VideoGrabber());
        }
        void toggleMirror();
        int32_t getWidth();
        int32_t getHeight();
        
        ci::Vec2i getDimensions();
        void setup();
        bool update();
        void draw();
        
        ci::gl::TextureRef getTexture;
        ci::Surface getSurface();
        ci::CaptureRef getGrabber();
        
    };
};
#endif
