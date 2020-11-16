#pragma once

#include "ofMain.h"

using namespace glm;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
    
        ofShader juliaShader;
    
        float move;
    
        ofVideoGrabber videoGrabber;
    
        //Process bytes of image
        unsigned char * outImage;//Texture to display the processed image
        unsigned char * input;
        ofTexture Texture;
    
        int w;
        int h;
    
        ofPoint pos; //Coordinates of object

		
};
