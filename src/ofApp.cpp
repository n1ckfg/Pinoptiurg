#include "ofApp.h"

using namespace cv;
using namespace ofxCv;

//--------------------------------------------------------------
void ofApp::setup(){
    settings.loadFile("settings.xml");
    
    leftBound = settings.getValue("settings:left_bound", -2000);
    topBound = settings.getValue("settings:top_bound", -2000);
    rightBound = settings.getValue("settings:right_bound", 2000);
    bottomBound = settings.getValue("settings:bottom_bound", 2000);

    oscHost = settings.getValue("settings:osc_host", "127.0.0.1");
    oscPort = settings.getValue("settings:osc_port", 7110);
    setupOscSender(sender, oscHost, oscPort);

    ofSetVerticalSync(false);
    ofHideCursor();

    urg.setup();

    // example: ROI with simple rectangle
    //urg.setRoi(ofRectangle(leftBound, topBound, rightBound, bottomBound));

    // example: ROI with irregular shape
    //ofPolyline line;
    //line.addVertex(-500, -2100);
    //line.addVertex(550, -2200);
    //line.addVertex(505, -200);
    //line.addVertex(-400, -300);
    //line.addVertex(-600, -1000);
    //line.close();
    //urg.setRoi(line);

    urg.start();
}

void ofApp::setupOscSender(ofxOscSender& sender, string& oscSendHost, int oscSendPort) {
    sender.setup(oscSendHost, oscSendPort);
    cout << "\nSending OSC to " << oscSendHost << " on port: " << oscSendPort << endl;
}

void ofApp::sendOscLidar(ofxOscSender& sender, string hostName, string sessionId, int index, ofBuffer& lidarPointsBuffer, int timestamp) {
    ofxOscMessage m;
    m.setAddress("/lidar"); // ssibi
    
    m.addStringArg(hostName);
    m.addStringArg(sessionId);
    m.addIntArg(index);
    m.addBlobArg(lidarPointsBuffer);
    m.addIntArg(timestamp);

    sender.sendMessage(m);
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    //urg.drawRadius();

    //vector<ofVec2f> maskPoints = urg.getMaskPoints();
    //urg.drawPoints(maskPoints, 150, ofColor(0,0,0,128), false);

    //vector<ofVec2f> calibrationPoints = urg.getPoints();
    //urg.drawPoints(calibrationPoints, 10, ofColor::azure, false);

    //vector<ofVec2f> blobs = urg.getPoints(300);
    //urg.drawPoints(blobs, 100);

    //int numblobs = blobs.size();

    //ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()) + "fps", 30, 30);
    //ofDrawBitmapStringHighlight(ofToString(numblobs) + " blobs", 30, 50);

    //vector<ofVec2f> targetPoints = calibrationPoints;
    
    vector<float> distances = urg.getDistances(false);

    float pointsData[distances.size()]; 
    for (int j=0; j<distances.size(); j++) {
        pointsData[j] = distances[j];
    }
    char const * pPoints = reinterpret_cast<char const *>(pointsData);
    std::string pointsString(pPoints, pPoints + sizeof pointsData);
    lidarPointsBuffer.set(pointsString); 

    sendOscLidar(sender, "temp", "temp", 0, lidarPointsBuffer, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == ' ') {
        urg.calibrateMask(150); // set 15cm tolerance
    }
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

void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){
	urg.setDrawZoom(urg.getDrawZoom()+scrollY*.05);
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
