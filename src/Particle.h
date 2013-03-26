//
//  Particle.h
//  privateParty
//
//  Created by Brett Peterson on 2/25/13.
//
//

#include "ofMain.h";
class Particle{
    
    
    public:
        
        void update();
        void draw();
        bool isDead();
        void run();
    
        
        Particle();
        
        ofVec2f location;
        ofVec2f velocity;
        ofVec2f accel;
        float lifespan;
        float rotY;
        float rotSeed;
        ofColor color;

};
