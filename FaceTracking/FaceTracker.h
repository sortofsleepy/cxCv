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


namespace cxCv{
    typedef std::shared_ptr<class FaceTracker>FaceTrackerRef;

class FaceTracker{
    
    cv::CascadeClassifier	mFaceCascade, mEyeCascade;
	vector<Rectf>			mFaces, mEyes;
    
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
    void update(Surface image);
    virtual void draw();
};
    
} // end namespace

#endif
