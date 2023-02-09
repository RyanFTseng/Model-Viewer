#pragma once

#include "ofMain.h"


class Triangle {
public:
	vector<std::array<int, 3>> ind;
	Triangle(int tri1, int tri2, int tri3) {
		ind.push_back(array<int, 3>({ tri1, tri2, tri3 }));
	};
};

class Vertex {
public:
	Vertex(float x, float y, float z) {
		position = glm::vec3(x, y, z);
	};
	glm::vec3 position;
};

class Mesh {
	
public:
	vector<Vertex> verts;
	vector<Triangle> tris;

	Vertex selectedVert = Vertex(0, 0, 0);
	int selectVertInd;

	void draw() {
		for (int i = 0; i < tris.size(); i++) {
			glm::vec3 v1 = glm::vec3(verts[tris[i].ind[0][0]-1].position);
			glm::vec3 v2 = glm::vec3(verts[tris[i].ind[0][1]-1].position);
			glm::vec3 v3 = glm::vec3(verts[tris[i].ind[0][2]-1].position);
			ofDrawLine(v1, v2);
			ofDrawLine(v2, v3);
			ofDrawLine(v3, v1);
		}
	};

	void cube() {
		
		verts.clear();
		tris.clear();

		verts.push_back(Vertex(0.0, 0.0, 0.0));
		verts.push_back(Vertex(0.0, 0.0, 1.0));
		verts.push_back(Vertex(0.0, 1.0, 0.0));
		verts.push_back(Vertex(0.0, 1.0, 1.0));
		verts.push_back(Vertex(1.0, 0.0, 0.0));
		verts.push_back(Vertex(1.0, 0.0, 1.0));
		verts.push_back(Vertex(1.0, 1.0, 0.0));
		verts.push_back(Vertex(1.0, 1.0, 1.0));

		tris.push_back(Triangle(1, 7, 5));
		tris.push_back(Triangle(1, 3, 7));
		tris.push_back(Triangle(1, 4, 3));
		tris.push_back(Triangle(1, 2, 4));
		tris.push_back(Triangle(3, 8, 7));
		tris.push_back(Triangle(3, 4, 8));
		tris.push_back(Triangle(5, 7, 8));
		tris.push_back(Triangle(5, 8, 6));
		tris.push_back(Triangle(1, 5, 6));
		tris.push_back(Triangle(1, 6, 2));
		tris.push_back(Triangle(2, 6, 7));
		tris.push_back(Triangle(2, 8, 4));
	};


	void highlightSphere() {
		ofSetColor(ofColor::red);
		ofDrawSphere(selectedVert.position, 0.1);
		
		ofSetColor(ofColor::green);
	}

	void highlightTri() {
		for (int i = 0; i < tris.size(); i++) {
			
			if (selectVertInd == tris[i].ind[0][0]-1 || selectVertInd == tris[i].ind[0][1] - 1 || selectVertInd == tris[i].ind[0][2] - 1) {
				ofSetColor(ofColor::red);
				glm::vec3 v1 = glm::vec3(verts[tris[i].ind[0][0] - 1].position);
				glm::vec3 v2 = glm::vec3(verts[tris[i].ind[0][1] - 1].position);
				glm::vec3 v3 = glm::vec3(verts[tris[i].ind[0][2] - 1].position);
				//cout << tris[i].ind[0][0] - 1 << " " << tris[i].ind[0][1] - 1 << " " << tris[i].ind[0][2] - 1 << endl;
				ofDrawLine(v1, v2);
				ofDrawLine(v2, v3);
				ofDrawLine(v3, v1);
				ofSetColor(ofColor::green);
			}
			
		}
	}

};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void readObjFile(string name);
		
		
		Mesh m;
		ofFile objFile;
		
		ofEasyCam easyCam;
		ofCamera* theCam;
		glm::vec3 intersectPt;
		bool selected = false;
		bool bIntersect;

};




