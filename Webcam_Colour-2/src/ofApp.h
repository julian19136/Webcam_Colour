// Example 7: Background Subtraction
// This is ofApp.h

#pragma once
#include "ofMain.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    ofVideoGrabber videoGrabber;
    
    //Process bytes of image
    unsigned char * outImage;//Texture to display the processed image
    unsigned char * input;
    ofTexture Texture;
    
    int w;
    int h;
    
    ofPoint pos; //Coordinates of object
    
};
