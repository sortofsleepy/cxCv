//
//  FaceTracker.h
//  BlobTracking
//
//  Created by Joseph Chow on 2/17/14.
//
//

#ifndef BlobTracking_FaceTracker_h
#define BlobTracking_FaceTracker_h


#include "cxCv.h"

using namespace ci;
using namespace ci::app;
using namespace std;

typedef std::shared_ptr<class FaceTracker>FaceTrackerRef;

class FaceTracker{
    
    cv::CascadeClassifier	mFaceCascade, mEyeCascade;
	vector<Rectf>			mFaces, mEyes;
public:
    FaceTracker(){}
    static FaceTrackerRef create(){
        return FaceTrackerRef(new FaceTracker());
    }
    void setup(){
    	mFaceCascade.load( getAssetPath( "../cxCv/assets/haarcascade_frontalface_alt.xml" ).string() );
        mEyeCascade.load( getAssetPath( "../cxCv/assets/haarcascade_eye.xml" ).string() );

    }
    
    void update(Surface image){
    	const int calcScale = 6; // calculate the image at half scale
        cv::Mat img(ci::toOcv(Channel(image)));
     
        
        // create a grayscale copy of the input image
        cv::Mat grayCameraImage( cxCv::toGray(img) );
        
        // scale it to half size, as dictated by the calcScale constant
        int scaledWidth = image.getWidth() / calcScale;
        int scaledHeight = image.getHeight() / calcScale;
        cv::Mat smallImg( scaledHeight, scaledWidth, CV_8UC1 );
        cv::resize( grayCameraImage, smallImg, smallImg.size(), 0, 0, cv::INTER_LINEAR );
        
        // equalize the histogram
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
    
    void draw(){
    	// draw the faces as transparent yellow rectangles
        gl::color( ColorA( 1, 1, 0, 0.45f ) );
        for( vector<Rectf>::const_iterator faceIter = mFaces.begin(); faceIter != mFaces.end(); ++faceIter )
		gl::drawSolidRect( *faceIter );
    }
};

#endif
