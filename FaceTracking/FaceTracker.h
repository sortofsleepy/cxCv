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
#include "VideoGrabber.h"
using namespace ci;
using namespace ci::app;
using namespace std;


namespace cxCv{
    typedef std::shared_ptr<class FaceTracker>FaceTrackerRef;

class FaceTracker{
    
    cv::CascadeClassifier	mFaceCascade, mEyeCascade;
	vector<Rectf>			mFaces, mEyes;
    
    //Refrence to the VideoGrabber thats providing the feed
    VidGrabber * grabber;
    bool debug;
public:
    FaceTracker();
    
    /**
     Instantiates a instance using a shader_ptr
     */
    static FaceTrackerRef create(){
        return FaceTrackerRef(new FaceTracker());
    }
    void toggleDebug();
    void setup();
    void setup(std::string facepath, std::string eyepath);
    void update(VidGrabber &capture);
    virtual void draw();
    
    /**
     Checks to see if anything has interacted with our face.
     */
    void checkHit(Vec2f position);
};
    
} // end namespace

#endif
