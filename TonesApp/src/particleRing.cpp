//
//  particleRing.cpp
//  Tones
//
//  Created by Francisco Zamorano on 2/25/13.
//
//

#include "particleRing.h"
#include "ofMain.h"

//------------------------------------------------------------
particle::particle(){
	setInitialCondition(0,0,0,0);
	damping = 0.02f;
    bRedraw = false;
    
    color.setHsb(130, 150, 255);
    moveToCenter.set(ofGetWidth()/2, ofGetHeight()/2);
}

//------------------------------------------------------------
void particle::resetForce(){
    // we reset the forces every frame
    frc.set(0,0);
}

//------------------------------------------------------------
void particle::addForce(float x, float y){
    // add in a force in X and Y for this frame.
    frc.x = frc.x + x;
    frc.y = frc.y + y;
}

//------------------------------------------------------------
void particle::addRepulsionForce(float x, float y, float radius, float scale){
    
	// ----------- (1) make a vector of where this position is:
	
	ofVec2f posOfForce;
	posOfForce.set(x,y);
	
	// ----------- (2) calculate the difference & length
	
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
        diff.normalize();
		frc.x = frc.x + diff.x * scale * pct;
        frc.y = frc.y + diff.y * scale * pct;
    }
}

//------------------------------------------------------------
void particle::addAttractionForce(float x, float y, float radius, float scale){
    
	// ----------- (1) make a vector of where this position is:
	
	ofVec2f posOfForce;
	posOfForce.set(x,y);
	
	// ----------- (2) calculate the difference & length
	
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		frc.x = frc.x - diff.x * scale * pct;
        frc.y = frc.y - diff.y * scale * pct;
    }
}

//------------------------------------------------------------
void particle::addRepulsionForce(particle &p, float radius, float scale){
	
	// ----------- (1) make a vector of where this particle p is:
	ofVec2f posOfForce;
	posOfForce.set(p.pos.x,p.pos.y);
	
	// ----------- (2) calculate the difference & length
	
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		frc.x = frc.x + diff.x * scale * pct;
        frc.y = frc.y + diff.y * scale * pct;
		p.frc.x = p.frc.x - diff.x * scale * pct;
        p.frc.y = p.frc.y - diff.y * scale * pct;
    }
}

//------------------------------------------------------------
void particle::addAttractionForce(particle & p, float radius, float scale){
	
	// ----------- (1) make a vector of where this particle p is:
	ofVec2f posOfForce;
	posOfForce.set(p.pos.x,p.pos.y);
	
	// ----------- (2) calculate the difference & length
	
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		frc.x = frc.x - diff.x * scale * pct;
        frc.y = frc.y - diff.y * scale * pct;
		p.frc.x = p.frc.x + diff.x * scale * pct;
        p.frc.y = p.frc.y + diff.y * scale * pct;
    }
	
}


//------------------------------------------------------------
void particle::addDampingForce(){
	
	// the usual way to write this is  vel *= 0.99
	// basically, subtract some part of the velocity
	// damping is a force operating in the oposite direction of the
	// velocity vector
	
    frc.x = frc.x - vel.x * damping;
    frc.y = frc.y - vel.y * damping;
}

//------------------------------------------------------------
void particle::setInitialCondition(float px, float py, float vx, float vy){
    pos.set(px,py);
	vel.set(vx,vy);
    
    color.setHsb(100, 100, 100);
}

//------------------------------------------------------------
void particle::update(){
	vel = vel + frc;
	pos = pos + vel;
    
    innerPos = pos - moveToCenter*0.02;
    
    if (!outRing.inside(pos)) {
        bInsideMyRing = false;
    }
    
    else if (inRing.inside(pos)) {
        bInsideMyRing = true;
    }
}

//------------------------------------------------------------
void particle::draw(){
    
   	if (vel.x + vel.y >1){
   		ofSetColor(80- 30 *(vel.x*vel.y), 200 - 30 *(vel.x*vel.y), 255 - 10 * (vel.x*vel.y) );
   		ofCircle(pos, 5+vel.x*vel.y*0.5);
        ofCircle(innerPos , 5+vel.x*vel.y*0.5);
   	}
   
   	else if (vel.x < 1 || vel.y <1) {
   		ofSetColor(100 - 30 *(vel.x*vel.y), 200 - 30 *(vel.x*vel.y), 220 - 5 * (vel.x*vel.y) );
   		ofCircle(pos, 1 + vel.x*vel.x*0.5);
        
//        ofCircle(innerPos , 1+vel.x*vel.y*0.5);
   	}
}


//------------------------------------------------------------
void particle::bounceOffWalls(ofPolyline outerRing){
    
    outRing = outerRing;
    centroid = outerRing.getCentroid2D();
    
    
    // sometimes it makes sense to damped, when we hit
	bool bDampedOnCollision = true;
	bool bDidICollide = false;

    
    if (!outerRing.inside(pos)) {               
        ofPoint goBack = centroid-pos;
        pos = pos + goBack * 0.001;
        vel.x *= -1;
        vel.y *= -1;
        bDidICollide = true;
    }

	
	if (bDidICollide == true && bDampedOnCollision == true){
		vel *= 0.3;
	}
	
}


//------------------------------------------------------------

ofPoint particle::posinsideHex(ofPolyline outerRing, ofPolyline innerRing){
    
    ofPoint _pos;
    
    float left = outerRing.getVertices()[1].x;
    float right = outerRing.getVertices()[4].x;
    float up = outerRing.getVertices()[1].y;
    float down = outerRing.getVertices()[4].y;
    
    float height = down-up;
    float width = right-left;
    
    
//    cout<<left<<" "<<right<<" "<<up<<" "<<down<<" "<<width<<" "<<height<<endl;
    
    
    for (int i=left; i<width; i++) {
        for (int j=up; j<height;j++) {

            
            if(outRing.inside(_pos)&&!innerRing.inside(_pos)){
                _pos.x=i;
                _pos.y=j;
                return _pos;
//                bRedraw = false;
            }
        }
    }
    


}
