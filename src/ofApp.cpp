#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //ofEnableNormalizedTexCoords() ...
    
    //Set the number of particles in the system
    numParticles = 1000000;
    
    //Calculate the texture resolution
    int textureDim = (int)sqrt(numParticles);
    cout << ofToString(numParticles) << " particles, texture size " << ofToString(textureDim) << endl;
    
    
    
    
    //----POSITION
    currentPos.allocate(textureDim, textureDim, GL_RGB32F, 4);
    currentPos.begin();
    ofClear(255, 255, 255, 0);
    currentPos.end();
    
    nextPos.allocate(textureDim, textureDim, GL_RGB32F, 4);
    nextPos.begin();
    ofClear(255, 255, 255, 0);
    nextPos.end();
    
    float *positionData = new float[numParticles*3];
    for(int i = 0; i < numParticles; i++) {
        positionData[i*3 + 0] = ofRandom(1.0);
        positionData[i*3 + 1] = ofRandom(1.0);
        positionData[i*3 + 2] = 0.0;
    }
    currentPos.getTextureReference().loadData(positionData, textureDim, textureDim, GL_RGB);
    nextPos.getTextureReference().loadData(positionData, textureDim, textureDim, GL_RGB);
    delete [] positionData;
    

    
    
    //----VELOCITY
    currentVel.allocate(textureDim, textureDim, GL_RGB32F, 4);
    currentVel.begin();
    ofClear(255, 255, 255, 0);
    currentVel.end();
    
    nextVel.allocate(textureDim, textureDim, GL_RGB32F, 4);
    nextVel.begin();
    ofClear(255, 255, 255, 0);
    nextVel.end();
    
    float *velocityData = new float[numParticles*3];
    for(int i = 0; i < numParticles; i++) {
        velocityData[i*3 + 0] = ofRandom(1.0);//ofRandom(-1.0, 1.0);
        velocityData[i*3 + 1] = ofRandom(1.0);//ofRandom(-1.0, 1.0);
        velocityData[i*3 + 2] = 1.0;
    }
    currentVel.getTextureReference().loadData(velocityData, textureDim, textureDim, GL_RGB);
    nextVel.getTextureReference().loadData(velocityData, textureDim, textureDim, GL_RGB);
    delete [] velocityData;
    
    
    
    
    //----RENDER
    render.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGB32F, 4);
    render.begin();
    ofClear(255, 255, 255, 0);
    render.end();
    
    
    
    
    //----SHADERS
    updatePos.load("updatePos.vert", "updatePos.frag");
    updateVel.load("updateVel.vert", "updateVel.frag");
    renderShader.load("render.vert", "render.frag");
    
    
    
    
    //----MESH
    particleMesh.setMode(OF_PRIMITIVE_POINTS);
    for (int x = 0; x < textureDim; x++) {
        for (int y = 0; y < textureDim; y++) {
            particleMesh.addVertex(ofVec3f(x, y));
            particleMesh.addTexCoord(ofVec2f(x, y));
        }
    }

}

//--------------------------------------------------------------
void ofApp::update(){
    //--------------------------------------------------------------UPDATE PARTICLE VELOCITIES
    nextVel.begin();
    ofClear(0);
    updateVel.begin();
    
    updatePos.setUniformTexture("currentPos", currentPos.getTextureReference(), 0);
    updatePos.setUniformTexture("currentVel", currentVel.getTextureReference(), 1);
    currentVel.draw(0, 0);
    
    updateVel.end();
    nextVel.end();
    
    
    
    //Swap velocity textures
    currentVel = nextVel;
    
    
    
    
    //--------------------------------------------------------------UPDATE PARTICLE POSITIONS
    nextPos.begin();
    ofClear(0);
    updatePos.begin();
    
    updatePos.setUniformTexture("currentPos", currentPos.getTextureReference(), 0);
    updatePos.setUniformTexture("currentVel", currentVel.getTextureReference(), 1);
    currentPos.draw(0, 0);
    
    updatePos.end();
    nextPos.end();
    
    
    
    //Swap position textures
    currentPos = nextPos;
    
    
    
    
    //--------------------------------------------------------------UPDATE RENDER FBO
    render.begin();
    ofClear(0);
    renderShader.begin();
    
    renderShader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
    renderShader.setUniformTexture("currentPos", currentPos.getTextureReference(), 0);
    particleMesh.draw();
    
    renderShader.end();
    render.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    render.draw(0, 0);
    
    ofDrawBitmapString("FPS " + ofToString(ofGetFrameRate()), 15, 15);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
