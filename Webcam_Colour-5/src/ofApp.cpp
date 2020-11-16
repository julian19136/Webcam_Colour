#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // load shader
    julianShader.load("julian");
    
    // Variable to adjust focus of image
    move = 8;
    
    // Set capture dimensions of 640x400, a common video size
    w = 640;
    h = 400;
    
    // Open an ofVideoGrabber for the default camera (Webcam)
    videoGrabber.initGrabber (w,h);
    
    // Set size of outImage
    outImage = new unsigned char [w * h * 3];
    
    Texture.allocate(w, h, GL_RGB);

    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    videoGrabber.update();
    
    if (videoGrabber.isFrameNew()){
        unsigned char *input = videoGrabber.getPixels().getData();
        // Looping through them
        for (int y = 0; y <h; y ++) {
            for (int x = 0; x <w; x ++) {
                // Input pixel (x, y):
                int r = input [6 * (x + w * (y*2)) + 0];
                int g = input [6 * (x + w * (y*2)) + 1];
                int b = input [6 * (x + w * (y*2)) + 2];
                // Threshold via Red
                int result = (r > b + 100 && r > g + 100)? 255: 0;
                // Write output image will be black or white:
                outImage[3 * (x + w * y) + 0] = result;
                outImage[3 * (x + w * y) + 1] = result;
                outImage[3 * (x + w * y) + 2] = result;}}
        // Write to a texture for the subsequent withdrawal of its on-screen
        Texture.loadData(outImage, w, h, GL_RGB);
    };
    
    pos = ofPoint(0, 0);
    int n = 0; //Number of pixels found
    for (int y = 0; y <h; y ++) {
        for (int x = 0; x <w; x ++) {
            int r = outImage[3 * (x + w * y) + 2]; // Look processed image
            if (r == 255) { // We have previously labeled as red dots
                pos.x += x; pos.y += y;n ++;}}}// Display average
    if (n> 0) {pos.x/= n;pos.y/= n;}
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // Output frame
    videoGrabber.draw(0,0, w, h);
    
    // Output the processing result
    Texture.draw(0, 0, w*2, h*2);
    
    // Iniation of fragment shader's uniform vectors
    julianShader.begin();
    // Setting the pixel data collected to moveMent variable within the fragment shader
    // This initiates moveMent based on red objects
    julianShader.setUniform2f("moveMent", vec2(pos.x, pos.y));
    julianShader.setUniform2f("windowSize", vec2(ofGetWidth(), ofGetHeight()));
    julianShader.setUniform1f("complexRange", move);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    julianShader.end();
    
    
   

    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == 'a'){
        move += 0.5; // do something
    } else if (key == 's'){
        move -= 0.5; // do something else
    }

}
