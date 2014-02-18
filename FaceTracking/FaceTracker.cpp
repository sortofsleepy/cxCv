//
//  FaceTracker.cpp
//  BlobTracking
//
//  Created by Joseph Chow on 2/17/14.
//
//

#include "FaceTracker.h"
using namespace ci;

namespace cxCv{
    
    FaceTracker::FaceTracker(){
        debug = false;
    }
    
    void FaceTracker::toggleDebug(){
        if(debug){
            debug = false;
        }else if (!debug){
            debug = true;
        }
    }
    
    /**
     Setup. Loads xml files from 
     within the cxCv folder.
     */
    void FaceTracker::setup(){
        mFaceCascade.load( getAssetPath( "../cxCv/assets/haarcascade_frontalface_alt.xml" ).string() );
        mEyeCascade.load( getAssetPath( "../cxCv/assets/haarcascade_eye.xml" ).string() );

    }
    /**
     Another setup. Pass in path to 
     necessary xml files.
     */
    void FaceTracker::setup(std::string facepath, std::string eyepath){
        mFaceCascade.load( getAssetPath(facepath).string() );
        mEyeCascade.load( getAssetPath( eyepath ).string() );
    }
    
    /**
     Update the tracker with new data.
     */
    void FaceTracker::update(VidGrabber &capture){
        grabber = &capture;
        Surface image = capture->getSurface();
        
        //might work better on a newer computer but on a older one like
        //mine, the scale needs to be > 4 and < 10
    	const int calcScale = 6;
        
        //get image into a cv::Mat
        cv::Mat img(ci::toOcv(Channel(image)));
        
        
        // create a grayscale copy of the input image
        cv::Mat grayCameraImage( cxCv::toGray(img) );
        
        // scale it to half size, as dictated by the calcScale constant
        int scaledWidth = image.getWidth() / calcScale;
        int scaledHeight = image.getHeight() / calcScale;
        
        /**
         Make a smaller copy of the image to do the face
         detection on.
         TODO : figure out why this is necessary instead
         of just using the image you receive.
         */
        cv::Mat smallImg( scaledHeight, scaledWidth, CV_8UC1 );
        cv::resize( grayCameraImage, smallImg, smallImg.size(), 0, 0, cv::INTER_LINEAR );
        
        /**
         Need to equalize the histogram.
         It'll still work if you don't, but it'll
         make other things much easier to mistake
         as faces than if you do.
         */
        cv::equalizeHist( smallImg, smallImg );
        
        // clear out the previously deteced faces & eyes
        mFaces.clear();
        
        
        // detect the faces and iterate them, appending them to mFaces
        vector<cv::Rect> faces;
        mFaceCascade.detectMultiScale( smallImg, faces );
        for( vector<cv::Rect>::const_iterator faceIter = faces.begin(); faceIter != faces.end(); ++faceIter ) {
            Rectf faceRect( fromOcv( *faceIter ) );
            faceRect *= calcScale;
            mFaces.push_back( faceRect );
            
        }

    }
    /**
     Draw what the tracker finds.
     */
    void FaceTracker::draw(){
        gl::pushMatrices();
        
        /**
         If we are in debug mode
         */
        if(debug){
            // draw the faces as transparent yellow rectangles
            gl::color( ColorA( 1, 1, 0, 0.45f ) );
        }
        for( vector<Rectf>::const_iterator faceIter = mFaces.begin(); faceIter != mFaces.end(); ++faceIter ){
            
            if(grabber->get()->mirror()){
                //since the video is flipped to mirror viewer,
                //need to do some additional math to re-calculate face position.
                Vec2f flipped = (faceIter->getCenter());
                flipped.x  = (grabber->get()->getWidth()) - flipped.x;
                gl::drawSolidCircle(flipped, 100.0f);
            }else{
                gl::drawSolidCircle(faceIter->getCenter(), 100.0f);
            }
           // gl::drawSolidRect( *faceIter );
        }
        
        gl::popMatrices();

    }
    
    
    void FaceTracker::checkHit(Vec2f position){
        
    }
}; // end namespace