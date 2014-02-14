//
//  Contours.cpp
//  TypeMotion
//
//  Created by Joseph Chow on 2/1/14.
//
//

#include "Contours.h"

using namespace ci;
using namespace ci::app;
using namespace std;
namespace cxCv{
    
    Contours::Contours(){
        threshold = 70.0f;
        blobMin = 20.0f;
        blobMax = 80.0f;
        
        
        
        debug = false;
    }
    
    void Contours::debugMode(){
        if(!debug){
            debug = true;
        }else{
            debug = false;
        }
    }
    
    void Contours::setupDebug(){
        mParams = params::InterfaceGl( "Contour Parameters", Vec2i( 220, 170 ) );
       
        mParams.addParam( "Threshold level", &threshold, "min=1 max=2000 keyIncr== keyDecr=-" );
        mParams.addParam( "Min blob size", &blobMin);
        mParams.addParam( "Max Blob", &blobMax );

    }

    /**
     Returns a vector of points within a ContourSet
    */
    Vec2f Contours::findTarget( float minRadius,float maxRadius){
        
        Vec2f target;
      
        // loop the stored contours
        for (vector<vector<cv::Point> >::iterator it=points.begin() ; it < points.end(); it++ ){
            // center abd radius for current blob
            cv::Point2f center;
            float radius;
            // convert the cuntour point to a matrix
            vector<cv::Point> pts = *it;
            cv::Mat pointsMatrix = cv::Mat(pts);
            // pass to min enclosing circle to make the blob
            cv::minEnclosingCircle(pointsMatrix, center, radius);
            
            cv::Scalar color( 0, 255, 0 );
            
            if (radius > blobMin && radius < blobMax) {
                target.x = 640 - center.x;
                target.y = center.y;
            }
            
            
        }
        
        return target;
    }
    

    Vec2f Contours::findTarget(){
        
        Vec2f target;
        
        // loop the stored contours
        for (vector<vector<cv::Point> >::iterator it=points.begin() ; it < points.end(); it++ ){
            // center abd radius for current blob
            cv::Point2f center;
            float radius;
            // convert the cuntour point to a matrix
            vector<cv::Point> pts = *it;
            cv::Mat pointsMatrix = cv::Mat(pts);
            // pass to min enclosing circle to make the blob
            cv::minEnclosingCircle(pointsMatrix, center, radius);
            
            cv::Scalar color( 0, 255, 0 );
            
            if (radius > blobMin && radius < blobMax) {
                target.x = 640 - center.x;
                target.y = center.y;
            }
            
            
        }
        
        return target;
    }
    

    /**
     Finds the contours in a image.
     */
    std::vector<ci::Vec2f> Contours::findContours(ci::Surface image,bool draw){
        cv::Mat img(ci::toOcv(image));
        thresh = cxCv::toGray(img);
        vector<Vec4i> hierarchy;
        vector<Vec2f> returnpoints;
        
        //using edge detection at the same time gives us slightly better results.
        cv::Mat canny_output;
        cv::Canny(thresh, canny_output, threshold, threshold *2,3);
        
        //run contour finding algorithim.
        cv::findContours( canny_output, allcontours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

        
        
        if(draw){
            vector<vector<cv::Point> >::iterator it;
            gl::pushMatrices();
            
            for(it = allcontours.begin();it != allcontours.end();++it){
                vector<cv::Point> pt = *it;
                vector<cv::Point>::iterator pts;
                for(pts = pt.begin();pts != pt.end();++pts){
              
                    gl::color(Color(1,1,0));
                    glPointSize(2.0f);
                    glBegin(GL_POINTS);
                    gl::vertex(ci::fromOcv(*pts));
                    glEnd();
              
                }
            }
            gl::popMatrices();

        }else{
            vector<vector<cv::Point> >::iterator it;
           
            for(it = allcontours.begin();it != allcontours.end();++it){
                vector<cv::Point> pt = *it;
                vector<cv::Point>::iterator pts;
                for(pts = pt.begin();pts != pt.end();++pts){
                    
                    
                    returnpoints.push_back(ci::fromOcv(*pts));
                }
            }

        }
        
        
        if(debug){
            try{
                mParams.draw();
            }catch(...){
                app::console()<<"There was trouble drawing the params panel";
            }
        }
        
        return returnpoints;
    }
    
    
    void Contours::drawContours(){
        vector<vector<cv::Point> >::iterator it;
        gl::pushMatrices();
        glPointSize(2.0f);
        glBegin(GL_POINTS);
        gl::color(cxCv::debugColor);
        for(int i = 0;i<allcontours.size();i+=10){
            vector<cv::Point> pt = allcontours.at(i);
            vector<cv::Point>::iterator pts;
            for(pts = pt.begin();pts != pt.end();++pts){
                
                
                gl::vertex(ci::fromOcv(*pts));
              
            }
        }
          glEnd();
        if(debug){
            try{
                mParams.draw();
            }catch(...){
                app::console()<<"There was trouble drawing the params panel";
            }
        }
        

        gl::popMatrices();

    }


    
}; //end namespace