//
//  VideoGrabber.cpp
//  TypeMotion
//
//  Created by Joseph Chow on 2/2/14.
//
//

#include "VideoGrabber.h"
using namespace ci;
using namespace std;
namespace cxCv{
    VideoGrabber::VideoGrabber(){
        
        //default width and height
        width = 640;
        height = 480;
        
        //zero out the position
        loc = Vec3f::zero();
        
        //get all available devices
        devices = Capture::getDevices();
        
        //we default to first one, which should be a webcam in most cases.
        //bail out if one doesn't exist
        for( vector<Capture::DeviceRef>::const_iterator deviceIt = devices.begin(); deviceIt != devices.end(); ++deviceIt ) {
            Capture::DeviceRef device = *deviceIt;
            
            try{
                if(device->checkAvailable()){
                    grabber = Capture::create(width, height,device);
                }
            }catch(CaptureExc &){
                app::console() << "Unable to initialize device: " << device->getName() << endl;
            }
        }
    }
    
    void VideoGrabber::update(){
        if(grabber->checkNewFrame()){
            video_t = gl::Texture(grabber->getSurface());
        }
        
    }
    
    void VideoGrabber::draw(){
        gl::draw(video_t, Rectf(loc.x,loc.y,width,height));
    }
    CaptureRef VideoGrabber::getGrabber(){
        return grabber;
    }
    
    
};//end namespace