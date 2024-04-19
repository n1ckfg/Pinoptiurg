#pragma once

#include "ofMain.h"
#include "ofxURG.h"
#include "ofxCv.h"
#include "ofxOsc.h"
#include "ofxXmlSettings.h"

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
	void mouseScrolled(int x, int y, float scrollX, float scrollY);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void setupOscSender(ofxOscSender& sender, string& oscSendHost, int oscSendPort);
	void sendOscLidar(ofxOscSender& sender, string hostName, string sessionId, int index, ofBuffer& lidarPointsBuffer, int timestamp);
	
	float remap(float value, float min1, float max1, float min2, float max2);

	ofxURG urg;
	int leftBound, topBound, rightBound, bottomBound;

	string oscHost;
	int oscPort;
	ofxXmlSettings settings;
	ofxOscSender sender;
 	ofBuffer lidarPointsBuffer;
 	float minDistance, maxDistance;

};
