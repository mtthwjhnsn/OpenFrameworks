#pragma once

#include "ofMain.h"

#include "Spout2Sender.h"
#include "NDIoutput.h"
#include "input_selector.h"


struct OutputParams {

	int output_type;
	bool switcher;

};

class output_selector
{
public:
	
	void setup();
	//void update();
	//void draw();
	//void selection();

	OutputParams params;
	
private:



};
