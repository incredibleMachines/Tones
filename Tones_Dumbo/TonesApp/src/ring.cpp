//
//  ring.cpp
//  Lunarlon_v3
//
//  Created by Francisco Zamorano on 8/31/13.
//
//

#include "ring.h"
//------------------------------------------------------------
void Ring::setup(int _nParticles, ofPoint _ctr, float _radius, float _springiness, float _distance){
    ctr = _ctr;
    radius = _radius;
    touchAmt = 0;
    
    //Particles
    nParticles = _nParticles;
    for (int i = 0; i < _nParticles; i++){
        
        float mod = sin((TWO_PI/4)*i) * 30;
 
        particle myParticle;
        float ang = (TWO_PI/nParticles) * i ;
        float x = _ctr.x + cos(ang) * (_radius + mod);
        float y = _ctr.y + sin(ang) * (_radius + mod);
        
        myParticle.setInitialCondition(x,y,0,0,0.3);
        myParticle.color.setHsb(78, 50 , 200, 200);

        particles.push_back(myParticle);
        originalParticlePos.push_back(myParticle);
        
    }
    
    //Springs
    for (int i = 0; i < particles.size(); i++){
		Spring mySpring;
		mySpring.distance		= _distance;
		mySpring.springiness	= _springiness;
		mySpring.particleA = & (particles[i]);
		mySpring.particleB = & (particles[(i+1) % particles.size()]);
        mySpring.color.setHsb(78, 50 , 200, 100);
		springs.push_back(mySpring);
        
        
//        //bFix some points
//        particles[i].bFixed = true;

//        particles[0].bFixed = true;
//        particles[particles.size()-1].bFixed = true;
        
//        particles[1].bFixed = true;
//        for (int j=0; j<7; j++) {
//            particles[int(particles.size()/2)*i].bFixed = true;
//        }
        
	}
    
    // Mesh Mode (For Spring Fills)
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
}

//------------------------------------------------------------
void Ring::updateForces(vector<ofPoint>_blobs){
    
    blobs = _blobs;
    
    /// -- Reset Particles
    for (int i=0; i<particles.size(); i++) {
        particles[i].resetForce();
    }

    /// -- Update Particle forces
    for (int i=0; i<particles.size(); i++) {

        //Incoming forces from blobs
        if (blobs.size()>0) {
            for (int n=0; n<blobs.size(); n++) {
                particles[i].addRepulsionForce(blobs[n].x, blobs[n].y,  50, 8.5f);
                particles[i].addAttractionForce(ofGetWidth()/2, ofGetHeight()/2,  400, 0.01f);
                particles[i].changeColor(blobs[n],100);
//                particles[i].bounceOffWalls();
            }
        }
        
        //Particle-to-particle forces
        for (int j=0; j<i; j++) {
            particles[i].addRepulsionForce(particles[j],p2pForceRadius,p2pForceStrength);
        }
    }
    
    /// -- Clear Mesh
    for (int i=0; i<particles.size(); i++) {
        mesh.clear();
    }
    
    /// --  Create Meshes from Rings
    ofColor tempColor;
    for (int i=0; i<particles.size(); i++) {
        
        tempColor.setHsb(20 - 0.4*i , 255-i/2, 255- 0.1*i,80);
        mesh.addColor(baseColor);
        mesh.addVertex(particles[i].pos);
        
        if (i==particles.size()-1) {
            mesh.addColor(baseColor);
            mesh.addVertex(particles[0].pos);
        }
    }
    
    /// -- Radial color highlight around the blobs
    for (int i=0; i<particles.size(); i++) {
        for (int j=0; j<blobs.size(); j++) {
            ofVec2f diff = particles[i].pos - blobs[j];
            float distance = diff.length();
            
            if (distance<80) {
                float pct = 1 - (distance / 80);
                mesh.setColor(i, ofColor(255,255,255,50 + 80*pct));
            }
        }
    }
         
    /// -- Springs update
    for (int i=0; i<springs.size(); i++) {
        springs[i].update();
     }
    
    for (int i=0; i<particles.size(); i++) {
        particles[i].pos.interpolate(originalParticlePos[i].pos,0.05);
    }
    
    // Particle update. This should go at the end--Important!!
    for (int i=0; i<particles.size(); i++) {
        particles[i].addDampingForce();
        particles[i].update();
    }
}

//------------------------------------------------------------
void Ring::setColor(ofColor _color){
    baseColor = _color;
}

//------------------------------------------------------------
void Ring::draw(){
    mesh.draw();
    
//    for (int i=0; i<springs.size(); i++) {
//        springs[i].draw();
//    }
//    for (int i=0; i<particles.size(); i++) {
//        particles[i].draw();
//    }
    
    mesh.drawWireframe();
    
}





