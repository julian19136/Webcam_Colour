#pragma once

#include "ofMain.h"

using namespace glm;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void keyPressed(int key);
    
        ofVideoGrabber videoGrabber;
        ofShader julianShader;
        ofTexture Texture;
    
        // Coordinates of object
        ofPoint pos;
    
        float move;
    
        // Process bytes of image
        // Texture to display the processed image
        unsigned char * outImage;
        unsigned char * input;
    
        // Width and Height
        int w;
        int h;
    
    

		
};
