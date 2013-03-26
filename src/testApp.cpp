#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    //init grabber and party hat images
    grabber.initGrabber(640, 480);
    partyHat.allocate(partyHat.width, partyHat.height, OF_IMAGE_COLOR_ALPHA);
    partyHat.loadImage("partyHat.png");
    partyHat.setImageType(OF_IMAGE_COLOR_ALPHA);
    
    //Load and setup music
    loop.loadSound("frontLoop.mp3");
    loop.setLoop(true);
    loop.setVolume(0.1f);
    music.loadSound("foundLoveBoom.mp3");
    music.setVolume(0.8f);
    
    
    //allocate mem for image, setup Haar Finder
    camImage.allocate(grabber.width, grabber.height);
    finder.setup("haarcascade_frontalface_default.xml");
    
    // Number of particles
    nParts = 100;
    
    // Create array of pointers to particles
    p = new Particle*[nParts];
    
    for (int i = 0; i < nParts; i++){
        p[i] = new Particle();
    }
    
    // Start the loop music playing
    loop.play();
    
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    grabber.update();
    
    // If the grabber has a new frame, grab the video and perform Haar Finder, looking for face
    if (grabber.isFrameNew()){
        
        camImage.setFromPixels(grabber.getPixelsRef());
        greyImage = camImage;
        finder.findHaarObjects(greyImage, 150,150);
    }
    
    // DEBUGGING
    numFaces = finder.blobs.size();
    
    //ofLogNotice() << numFaces;

    // Rotation step for confetti particles
    rotY+=2;
    
    
    // Delete the confetti after a bit, create new ones
    if (numFaces){
        for (int i = 0; i < nParts; i++){
            p[i]->update();
            if (p[i]->isDead()){
                delete p[i];
                p[i] = new Particle();
            }
        }
    }
    
    

    

}

//--------------------------------------------------------------
void testApp::draw(){
    ofEnableAlphaBlending();

    camImage.draw(0, 0);
    
    ofNoFill();
    
    // Draw party hat on the first face found
	for(int i = 0; i < finder.blobs.size(); i++) {
        if (i == 0){
            ofRectangle current = finder.blobs[i].boundingRect;
            partyHat.draw(current.x, current.y-(current.height/1.8), current.width*.8,current.height*.8);
        }
	}
    
    // If a face is seen, stop the loop and drop the beat
    if (numFaces){
        if (!music.getIsPlaying()){
            loop.stop();
            music.play();
        }
        for (int i = 0; i < nParts; i++){
            p[i]->draw();
            ofNoFill();
        }
    } else {
        
        //Show the Private Party string with black background if no faces
        ofSetColor(0, 0, 0);
        ofFill();
        ofRect(0, 0, 640, 480);
        ofSetColor(255, 255, 255);
        ofFill();
        ofDrawBitmapString("RESERVED FOR", 280, 480/2);
        ofDrawBitmapString("PRIVATE PARTY", 280, 480/2 + 20);
        
        
        music.stop();
        if (!loop.getIsPlaying()){
            loop.play();
        }
    }
    

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}