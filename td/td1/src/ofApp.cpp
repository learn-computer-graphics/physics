#include "ofApp.h"

#include <vector>

#include "link.h"
#include "mass.h"

static int      Fe = 100; // frequency
static double   h = 1. / Fe;
static double   m = 1.;
static double   k = 0.100 * m * std::sqrt(Fe);
static double   z = 0.005 * m * Fe;

std::vector<Mass> masses = {
	Mass(MassType::Constant, 500., 500., 0.),
	Mass(MassType::Movable, 500., 550., m),
};

std::vector<Link> links = {
	SpringBreakLink(k, z)
};

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(255, 255, 255);
	ofSetWindowTitle("Physics TD1");
	ofEnableAntiAliasing();
	ofSetFrameRate(60);

	gui.setup(); // most of the time you don't need a name
	gui.add(radius.setup("radius", 140, 10, 300));

	ofSetColor(255, 130, 0);

	links[0].connect(&masses[0], &masses[1]);
	reset();
}

//--------------------------------------------------------------
void ofApp::update(){
	for (auto& link : links)
		link.update();

	for (auto& mass : masses)
		mass.update(h);
}

//--------------------------------------------------------------
void ofApp::draw(){
	gui.draw();

	for (auto& link : links)
		link.draw();

	for (auto& mass : masses)
		mass.draw();
}

void ofApp::reset()
{
	masses[0].addToFriction(1. * std::sqrt(Fe));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	reset();
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
