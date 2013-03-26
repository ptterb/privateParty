//
//  Particle.cpp
//  privateParty
//
//  Created by Brett Peterson on 2/25/13.
//
//

#include "Particle.h"


Particle::Particle()
{
    
    // Start at a common location
    location.set(-200, 480/2);
    
    // Give each confetti flake a random - but directed - velocity
    velocity.set(ofRandom(0, 7.0),ofRandom(-10, 0));
    
    //gravity
    accel.set(0,0.1);
    
    //prettymuch arbitrary lifespan
    lifespan = 255;
    
    //random color and rotation direction
    color.set(ofRandom(255), ofRandom(255), ofRandom(255));
    rotSeed = ofRandom(-1, 1);
    
    

}
void Particle::update()
{

    // Move the confetti flake with velocity and gravity
    velocity = velocity + accel;
    location = location + velocity;
    
    // Kill it a little bit
    lifespan -= 2.0;
    
    // add some rotation (should be other axes as well, only Y for now)
    rotY+=rotSeed;
    
}


void Particle::draw()
{
    ofSetColor(color);
    ofFill();
    
    ofPushMatrix();
    ofTranslate(location.x, location.y);
    ofRotateY(rotY);
    ofRect(0, 0, 10, 10);
    ofPopMatrix();
    ofSetColor(255, 255, 255);
    ofNoFill();
    
    
}

//Check if dead
bool Particle::isDead()
{
    if (lifespan < 0.0){
        return true;
    } else {
        return false;
    }
}

void Particle::run()
{
    update();
    draw();
    
}