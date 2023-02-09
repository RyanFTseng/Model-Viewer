#include "ofApp.h"
#include <glm/gtx/intersect.hpp>



//--------------------------------------------------------------
void ofApp::setup(){
	// initialization
	//
	ofSetBackgroundColor(ofColor::black);
	theCam = &easyCam;
	easyCam.setDistance(10);
	easyCam.setNearClip(.1);

	m.cube();

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	
	// called every frame
	//
	theCam->begin();

	// draw our 3D object
	//
	ofSetColor(ofColor::green);
	ofNoFill();
	m.draw();

	if (bIntersect) {
		
		m.highlightSphere();
		m.highlightTri();
	}

	theCam->end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	
	case ' ':
		bIntersect = false;
		m.cube();
		break;
	}
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
	glm::vec3 screen3DPt = theCam->screenToWorld(glm::vec3(x, y, 0));
	glm::vec3 rayOrigin = theCam->getPosition();
	glm::vec3 rayDir = glm::normalize(screen3DPt - rayOrigin);
	glm::vec3 intersectNormal;
	
	
	for (int i = 0; i < m.verts.size(); i++) {
			bIntersect = glm::intersectRaySphere(rayOrigin, rayDir, m.verts[i].position, 0.1,
				intersectPt, intersectNormal);
			if (bIntersect){
				m.selectedVert = m.verts[i];
				m.selectVertInd = i;
				break;
			}

	}
	
	if (bIntersect) {
		cout << "hit" << endl;
		//cout << "selected vertex position: " << m.selectedVert.position << endl;
		//cout << m.selectVertInd << endl;
		
		selected = true;
	}
	else {
		cout << "miss" << endl;
		selected = false;
	}


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
	//
	//
	m.tris.clear();
	m.verts.clear();
	bIntersect = false;
	objFile = ofFile(dragInfo.files[0]);
	readObjFile(dragInfo.files[0]);
}

void ofApp::readObjFile(string name) {
	string line;
	ofFile file;
	file = objFile;


	// Open file, return if error
	//
	if (!file.open(name)) {
		cout << "can't open file: " << name << endl;
		return;
	}
	// read each line in file and process 
	//
	while (getline(file, line)) {
		// "line" is a string that contains the current line in the file
		//  suggest printing it out first to make sure you are reading it properly
		//  then parse the string "line" to create vertices and faces in mesh (refer to wavefront .obj wiki for format) 
		//cout << line << endl;
		
		if (line.substr(0,2) == "v ") {
			std::istringstream v(line.substr(2));
			float x, y, z;
			v >> x; v >> y; v >> z;
			m.verts.push_back(Vertex(x, y, z));
		}
		
		
		if (line.substr(0, 2) == "f ") {
			if(line.find('/') != string::npos ){
				std::istringstream v(line.substr(2));
				int x, y, z, a, b, c;
				const char* chh = line.c_str();
			
				sscanf(chh, "f %i//%i %i//%i %i//%i", &x, &a, &y, &b, &z, &c);
			
				m.tris.push_back(Triangle(x, y, z));
			}
			else{
				std::istringstream v(line.substr(2));
				float x, y, z;
				v >> x; v >> y; v >> z;
				m.tris.push_back(Triangle(x, y, z));
			}
		}
	}

	file.close();
	float meshSize = (36 * (m.verts.size()) / 1024);
	cout << "Number of Verticies: " << m.verts.size() << endl;
	cout << "Number of Faces: " << m.tris.size() << endl;
	cout << "Size of Mesh Structure: " << meshSize << "kB" << endl;
}


