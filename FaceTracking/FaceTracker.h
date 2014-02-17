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
    
    void update(){}
    
    void draw(){}
};

#endif
