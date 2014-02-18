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
        
        shouldMirror = true;
        
    }
    
    int32_t VideoGrabber::getWidth(){
        return width;
    }
    
    int32_t VideoGrabber::getHeight(){
        return height;
    }
    
    Vec2i VideoGrabber::getDimensions(){
        return Vec2i(width,height);
    }
    
    void VideoGrabber::setup(){
        //get all available devices
        devices = Capture::getDevices();
        
        //we default to first one, which should be a webcam in most cases.
        //bail out if one doesn't exist
        for( vector<Capture::DeviceRef>::const_iterator deviceIt = devices.begin(); deviceIt != devices.end(); ++deviceIt ) {
            Capture::DeviceRef device = *deviceIt;
            
            try{
                if(device->checkAvailable()){
                    
                    //init capture system
                    grabber = Capture::create(width, height,device);
                    
                    //start getting video
                    grabber->start();
                    
                    //write to the texture;
                    video_t = gl::Texture::create(width,height);
                }
            }catch(CaptureExc &){
                app::console() << "Unable to initialize device: " << device->getName() << endl;
            }
        }

    }
    void VideoGrabber::toggleMirror(){
        if(shouldMirror){
            shouldMirror = false;
        }else if(!shouldMirror){
            shouldMirror = true;
        }
    }
    bool VideoGrabber::update(){
        if(grabber->checkNewFrame()){
            
            video_s = grabber->getSurface();
            
            cv::Mat frame(ci::toOcv(grabber->getSurface()));
            
            if(shouldMirror){
                cv::flip(frame, frame, 1);
            }
            
            video_t = gl::Texture::create(ci::fromOcv(frame));
            return true;
        }else{
            return false;
        }
        
    }
    bool VideoGrabber::mirror(){
        if(shouldMirror){
            return true;
        }else{
            return false;
        }
    }
    void VideoGrabber::draw(){
        gl::pushMatrices();
        gl::setMatricesWindow(app::getWindowSize());
        gl::draw(video_t, Rectf(loc.x,loc.y,loc.x + width,loc.y+ height));
        gl::popMatrices();
    }

    Surface VideoGrabber::getSurface(){
        
        return video_s;
    }
    
    CaptureRef VideoGrabber::getGrabber(){
        return grabber;
    }
    
    
};//end namespace