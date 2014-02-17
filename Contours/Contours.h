//
//  Contours.h
//  TypeMotion
//
//  Created by Joseph Chow on 2/1/14.
//
//

#ifndef TypeMotion_Contours_h
#define TypeMotion_Contours_h

#include "cxCv.h"
#include "cinder/params/Params.h"
using namespace ci;
/**
 Typedef contours to make things
 easier to work with.
 */
typedef struct{
    std::vector<std::vector<cv::Point> > contourlist;
}ContourSet;

typedef struct{
    std::vector<ci::Vec2f> points;
}VecSet;

typedef struct{
    std::vector<cv::Point> cvpoints;
}PointSet;

namespace cxCv {
    typedef std::shared_ptr<class Contours> ContourRef;
    class Contours{
        float threshold;
        float blobMin,blobMax;
        
        bool debug;
        params::InterfaceGl	mParams;
        
        //raw points fround from the findCountours operation
        std::vector<std::vector<cv::Point> > points;
        
        //stores the contours found at each request.
        std::vector<std::vector<cv::Point> > allcontours;
        
        std::vector<cv::Point> contours;
        
        cv::Mat thresh;
    public:
        Contours();
        static ContourRef create(){
            return ContourRef(new Contours);
        }
        
        /**
         Turns on/off debug mode
         */
        void debugMode();
        
        /**
         if we want debug mode to work,
         need to run this function
         */
        void setupDebug();
        /**
         Finds the contours of a image.
         */
        void findContours(ci::Surface image,bool draw=false);
        
        //void findContours(ci::Surface image,bool draw=false);
        void drawContours();
        
        /**
         Returns a vector of targets within a specified set of contours points.
         */
        ci::Vec2f findTarget(float minRadius,float maxRadius);
        
        /**
         Same thing but based on current minBlob and maxBlob
         */
        ci::Vec2f findTarget();
        
        
        
        
        ci::Vec3f mTargetPosition;
        ci::gl::Texture mCvTexture;
        
        VecSet getVectorFromContours(ContourSet set);
        
    };
    
};//end namespace


#endif