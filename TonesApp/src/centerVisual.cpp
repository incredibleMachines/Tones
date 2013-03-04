//
//  centerVisual.cpp
//  Tones
//
//  Created by Francisco Zamorano on 2/28/13.
//
//

#include "centerVisual.h"


// comparison routine for sort...
bool comparisonFunction(  particle * a, particle * b ) {
	return a->pos.x < b->pos.x;
}

//------------------------------------------------------------
centerVisual::centerVisual(){
    
    
}
//------------------------------------------------------------
void centerVisual::setup(vector<ofPoint>shape, ofPoint ctr){
    center = ctr;
    mainShape.addVertices(shape);
    mainShape.setClosed(true);
    
    //particles
    int nParticles = 1300;
    for (int i = 0; i < nParticles; i++){
        particle * p = new particle();
        myParticles.push_back(p);
        myParticles[i]->setInitialCondition(mainShape.getCentroid2D().x + ofRandom(-100,100), mainShape.getCentroid2D().x + ofRandom(-200), 1, 0);
        myParticles[i]->vel.set(0,0);
    }
    
    
    for (int i = 0; i < 6; i++){
        ofVec2f tempPoint;
        tempPoint.set(center);
        repulsionPoints.push_back(tempPoint);
    }
}

//------------------------------------------------------------
void centerVisual::update(){
    ///UPDATE PARTICLES
    //	// sort all the particle
	sort( myParticles.begin(), myParticles.end(), comparisonFunction);               // sort them!
	
    for (int i = 0; i < myParticles.size(); i++){
        myParticles[i]->resetForce();
    }
	
	for (int i = 0; i < myParticles.size(); i++){
		for (int j = i-1; j >= 0; j--){
			if ( fabs(myParticles[j]->pos.x - myParticles[i]->pos.x) >  10) break;
			myParticles[i]->addRepulsionForce(*myParticles[j], 12, 0.2f);
            
		}
    }

    for (int i = 0; i < myParticles.size(); i++){
        float attraction = 0.01;
        
        myParticles[i]->addAttractionForce(center.x,center.y, 400, 0.01);
        myParticles[i]->addAttractionForce(center.x,center.y, 500, 0.001);
        
        for (int j=0; j<repulsionPoints.size(); j++) {
            myParticles[i]->addRepulsionForce(repulsionPoints[j].x,repulsionPoints[j].y, 50, 0.5);
            myParticles[i]->addAttractionForce(repulsionPoints[j].x,repulsionPoints[j].y, 20, 0.7);
        }
        
		myParticles[i]->addDampingForce();
//        myParticles[i]->bounceOffWalls(mainShape.getVertices());
        myParticles[i]->update();
	}
    
    
}

//------------------------------------------------------------
void centerVisual::draw(){
    //    mainShape.draw();
    ofCircle(center, 2);
    
    ofSetColor(150,255,230,100);
    ofFill();
//    ofBeginShape();
//    for(int i=0; i<mainShape.getVertices().size();i++){
//        ofVertex(mainShape.getVertices()[i]);
//    }
//    ofEndShape();
    
    for(int i=0; i<40;i++){
        ofSetCircleResolution(60);
        ofSetColor(150,255,230, 5);
        ofCircle(center, 5*i);
    }
    
    //DRAW PARTICLES
    for (int i = 0; i < myParticles.size(); i++){
        myParticles[i]->draw();
    }
    
    
}

