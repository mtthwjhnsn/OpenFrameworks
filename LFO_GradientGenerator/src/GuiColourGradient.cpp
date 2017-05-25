//
//  GuiColourGradient.cpp
//  Kortex_Laser_Jen
//
//  Created by Joshua Batty on 4/4/17.
//
//

#include "GuiColourGradient.h"
#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))

int w = 400;

int h = 180;

//-------------------------------------------------
void GuiColourGradient::setup(ColourGradient *_colour) {
	colour = _colour;

	ofFbo::Settings fboSettings;
	fboSettings.width = w;
	fboSettings.height = h;
	fboSettings.internalformat = GL_RGBA;
	fboSettings.textureTarget = GL_TEXTURE_2D;
	fbo.allocate(fboSettings);
	textureid = fbo.getTexture().texData.textureID;

	//fbo.allocate(wwidth, hheight);
	fbo.begin();
	ofClear(255, 255, 255, 0);
	fbo.end();
	
	gui.setup();
	guiVisible = true;
}

GLuint GuiColourGradient::getTextureID() {
	return textureid;
}

//-------------------------------------------------
void GuiColourGradient::draw() {
	if (guiVisible) {
		
		//IMGUI		
		
		imGui();

		//FBO
		
		fbo.begin();

		ofSetColor(50, 50, 50, 50);
		ofRect(0, 0, w, h);


		float H = h * .5;
		int spacing = 50;
		
		ofSetColor(255, 0, 0);
		ofNoFill();
		ofBeginShape();

		float dc1 = colour->params.dc.x;
		float amp1 = colour->params.amp.x;
		float freq1 = colour->params.freq.x;
		float phase1 = colour->params.phase.x;

		float dc2 = colour->params.dc.y;
		float amp2 = colour->params.amp.y;
		float freq2 = colour->params.freq.y;
		float phase2 = colour->params.phase.y;

		float dc3 = colour->params.dc.z;
		float amp3 = colour->params.amp.z;
		float freq3 = colour->params.freq.z;
		float phase3 = colour->params.phase.z;
		
		for (int i = 0; i < w; i++) {

			float xval = ofMap(i, 0, w, 0.00, 1.00, true);

			ofSetColor(255, 0, 0);
			ofCircle(i, dc1 * H + H * amp1 * sin(6.28318*(freq1*xval + phase1)), 1);
			ofSetColor(0, 255, 0);
			ofCircle(i, dc2 * H + H * amp2 * sin(6.28318*(freq2*xval + phase2)), 1);
			ofSetColor(0, 0, 255);
			ofCircle(i, dc3 * H + H * amp3 * sin(6.28318*(freq3*xval + phase3)), 1);
		
		}

		fbo.end();

	}
}

//--------------------------------------------------------------
void GuiColourGradient::lfo_selection(int* type_param) {
	vector<string> types = { "sine","tri","saw","sqr","rnd" };
	ImGui::Columns(types.size());
	for (int i = 0; i < types.size(); i++) {
		ImGui::RadioButton(ofxImGui::GetUniqueName(types[i]), type_param, i);
		ImGui::NextColumn();
	}
	ImGui::Columns(1);
	ImGui::Separator();
}

//--------------------------------------------------------------
void GuiColourGradient::lfo_selection_red(int* type_param_red) {
	ImGui::Text("RED WAVE");
	ImGui::SameLine();
	if (ImGui::CollapsingHeader("Red_Wave_Type"))
	{
		vector<string> types = { "sine","tri","saw","sqr","rnd" };
		ImGui::Columns(types.size(), "", false);
		for (int i = 0; i < types.size(); i++) {
			ImGui::RadioButton(ofxImGui::GetUniqueName(types[i]), type_param_red, i);
			ImGui::NextColumn();
		}
		ImGui::Columns(1);
		ImGui::Separator();
	}
	/*const char* items[] = { "sine","tri","saw","sqr","rnd" };
	static int item2 = 1;
	ImGui::Combo("red_wave_type", &item2, items, IM_ARRAYSIZE(items));
	*/
}

void GuiColourGradient::lfo_selection_green(int* type_param_green) {
	ImGui::Text("GREEN WAVE");
	ImGui::SameLine();
	if (ImGui::CollapsingHeader("Green_Wave_Type"))
	{
		vector<string> types = { "sine","tri","saw","sqr","rnd" };
		ImGui::Columns(types.size(), "", false);
		for (int i = 0; i < types.size(); i++) {
			ImGui::RadioButton(ofxImGui::GetUniqueName(types[i]), type_param_green, i);
			ImGui::NextColumn();
		}
		ImGui::Columns(1);
		ImGui::Separator();
	}
}

void GuiColourGradient::lfo_selection_blue(int* type_param_blue) {
	ImGui::Text("BLUE WAVE");
	ImGui::SameLine();
	if (ImGui::CollapsingHeader("Blue_Wave_Type"))
	{
		vector<string> types = { "sine","tri","saw","sqr","rnd" };
		ImGui::Columns(types.size(), "", false);
		for (int i = 0; i < types.size(); i++) {
			ImGui::RadioButton(ofxImGui::GetUniqueName(types[i]), type_param_blue, i);
			ImGui::NextColumn();
		}
		ImGui::Columns(1);
		ImGui::Separator();
	}
}

//--------------------------------------------------------------

#define TEX_ID (ImTextureID)(uintptr_t)

bool GuiColourGradient::imGui()
{
	int gui_width = 700;
	auto mainSettings = ofxImGui::Settings();
	mainSettings.windowPos = ofVec2f(ofGetWidth() - gui_width, 10);
	
	//mainSettings.windowSize = ofVec2f(ofGetWidth(), ofGetHeight());

	this->gui.begin();
	{
		if (ofxImGui::BeginWindow("Gradient Generator", mainSettings, false))
		{
			ImGui::Text("%.1f FPS (%.3f ms/frame)", ofGetFrameRate(), 1000.0f / ImGui::GetIO().Framerate);

			if (ofxImGui::BeginTree("Master", mainSettings))
			{
				//lfo_selection(&colour->params.palette_lfo_type);
				ImGui::SliderFloat("num bands", &colour->params.num_bands, 1, 100);
				ImGui::SliderFloat("animate speed", &colour->params.animate_speed, 0.0, 1.0);
				ofxImGui::EndTree(mainSettings);
			}


			//----COLOURS
			if (ofxImGui::BeginTree("COLOURS", mainSettings))
			{

				ImGui::ImageButton(TEX_ID getTextureID(), ofVec2f(400, 180));
				
				//ImGui::PlotLines("LFO", , 100);


				//HEADINGS
				ImGui::Columns(5);
				ImGui::Text("");
				ImGui::NextColumn();
				ImGui::Text("DC");
				ImGui::NextColumn();
				ImGui::Text("AMP");
				ImGui::NextColumn();
				ImGui::Text("FREQ");
				ImGui::NextColumn();
				ImGui::Text("PHASE");
				ImGui::Columns(1);
				ImGui::Separator();



				// red wave tyoe
				lfo_selection_red(&colour->params.palette_lfo_red);


				//red paramaters
				ImGui::Columns(5);
				ImGui::Separator();

				if (ImGui::Button("rand_red"))
				{
					colour->params.dc[0] = ofRandom(-1.00, 1.00);
					colour->params.amp[0] = ofRandom(-1.00, 1.00);
					colour->params.freq[0] = ofRandom(-1.00, 1.00);
					colour->params.phase[0] = ofRandom(-1.00, 1.00);
				}

				ImGui::NextColumn();
				ImGui::SliderFloat("R_dc", &colour->params.dc[0], 0.0, 1.0);
				ImGui::NextColumn();
				ImGui::SliderFloat("R_amp", &colour->params.amp[0], 0.0, 1.0);
				ImGui::NextColumn();
				ImGui::SliderFloat("R_freq", &colour->params.freq[0], 0.0, 1.0);
				ImGui::NextColumn();
				ImGui::SliderFloat("R_phase", &colour->params.phase[0], 0.0, 1.0);
				ImGui::Columns(1);
				ImGui::Separator();


				//green wave type
				lfo_selection_green(&colour->params.palette_lfo_green);


				//green paramaters
				ImGui::Columns(5);
				ImGui::Separator();
				if (ImGui::Button("rand_green"))
				{
					colour->params.dc[1] = ofRandom(-1.00, 1.00);
					colour->params.amp[1] = ofRandom(-1.00, 1.00);
					colour->params.freq[1] = ofRandom(-1.00, 1.00);
					colour->params.phase[1] = ofRandom(-1.00, 1.00);
				}

				ImGui::NextColumn();
				ImGui::SliderFloat("G_dc", &colour->params.dc[1], 0.0, 1.0);
				ImGui::NextColumn();
				ImGui::SliderFloat("G_amp", &colour->params.amp[1], 0.0, 1.0);
				ImGui::NextColumn();
				ImGui::SliderFloat("G_freq", &colour->params.freq[1], 0.0, 1.0);
				ImGui::NextColumn();
				ImGui::SliderFloat("G_phase", &colour->params.phase[1], 0.0, 1.0);
				ImGui::Columns(1);
				ImGui::Separator();


				//blue wave type
				lfo_selection_blue(&colour->params.palette_lfo_blue);

				//blue paramaters
				ImGui::Columns(5);
				ImGui::Separator();

				if (ImGui::Button("rand_blue"))
				{
					colour->params.dc[2] = ofRandom(-1.00, 1.00);
					colour->params.amp[2] = ofRandom(-1.00, 1.00);
					colour->params.freq[2] = ofRandom(-1.00, 1.00);
					colour->params.phase[2] = ofRandom(-1.00, 1.00);
				}
				ImGui::NextColumn();
				ImGui::SliderFloat("B_dc", &colour->params.dc[2], 0.0, 1.0);
				ImGui::NextColumn();
				ImGui::SliderFloat("B_amp", &colour->params.amp[2], 0.0, 1.0);
				ImGui::NextColumn();
				ImGui::SliderFloat("B_freq", &colour->params.freq[2], 0.0, 1.0);
				ImGui::NextColumn();
				ImGui::SliderFloat("B_phase", &colour->params.phase[2], 0.0, 1.0);
				ImGui::Columns(1);
				ImGui::Separator();


				ImGui::Columns(5);
				ImGui::Separator();
				if (ImGui::Button("rand_all"))
				{
					colour->params.dc[0] = ofRandom(-1.00, 1.00);
					colour->params.amp[0] = ofRandom(-1.00, 1.00);
					colour->params.freq[0] = ofRandom(-1.00, 1.00);
					colour->params.phase[0] = ofRandom(-1.00, 1.00);

					colour->params.dc[1] = ofRandom(-1.00, 1.00);
					colour->params.amp[1] = ofRandom(-1.00, 1.00);
					colour->params.freq[1] = ofRandom(-1.00, 1.00);
					colour->params.phase[1] = ofRandom(-1.00, 1.00);

					colour->params.dc[2] = ofRandom(-1.00, 1.00);
					colour->params.amp[2] = ofRandom(-1.00, 1.00);
					colour->params.freq[2] = ofRandom(-1.00, 1.00);
					colour->params.phase[2] = ofRandom(-1.00, 1.00);
				}
				ImGui::NextColumn();
				if (ImGui::Button("rand_dc"))
				{
					colour->params.dc[0] = ofRandom(-1.00, 1.00);
					colour->params.dc[1] = ofRandom(-1.00, 1.00);
					colour->params.dc[2] = ofRandom(-1.00, 1.00);
				}
				ImGui::NextColumn();
				if (ImGui::Button("rand_amp"))
				{
					colour->params.amp[0] = ofRandom(-1.00, 1.00);
					colour->params.amp[1] = ofRandom(-1.00, 1.00);
					colour->params.amp[2] = ofRandom(-1.00, 1.00);
				}
				ImGui::NextColumn();
				if (ImGui::Button("rand_freq"))
				{
					colour->params.freq[0] = ofRandom(-1.00, 1.00);
					colour->params.freq[1] = ofRandom(-1.00, 1.00);
					colour->params.freq[2] = ofRandom(-1.00, 1.00);
				}
				ImGui::NextColumn();
				if (ImGui::Button("rand_phase"))
				{
					colour->params.phase[0] = ofRandom(-1.00, 1.00);
					colour->params.phase[1] = ofRandom(-1.00, 1.00);
					colour->params.phase[2] = ofRandom(-1.00, 1.00);
				}
				ImGui::Columns(1);
				ImGui::Separator();

				ofxImGui::EndTree(mainSettings);
			}

			//----ALL
			if (ofxImGui::BeginTree("LFOs", mainSettings)) {


				//----FREQ LFO
				if (ofxImGui::BeginTree("FREQ LFO", mainSettings)) {
					lfo_selection(&colour->params.freq_lfo_type);
					ImGui::SliderFloat("amp", &colour->params.freq_lfo_amp, 0.0, 1.0);
					ImGui::SliderFloat("speed", &colour->params.freq_lfo_speed, 0.0, 1.0);
					ImGui::SliderFloat("freq", &colour->params.freq_cycle_speed, 0.0, 1.0);
					ofxImGui::EndTree(mainSettings);
				}
				//----AMP LFO
				if (ofxImGui::BeginTree("AMP LFO", mainSettings)) {
					lfo_selection(&colour->params.amp_lfo_type);
					ImGui::SliderFloat("amp", &colour->params.amp_lfo_amp, 0.0, 1.0);
					ImGui::SliderFloat("speed", &colour->params.amp_lfo_speed, 0.0, 1.0);
					ImGui::SliderFloat("freq", &colour->params.amp_cycle_speed, 0.0, 1.0);
					ofxImGui::EndTree(mainSettings);
				}
				//----PHASE LFO
				if (ofxImGui::BeginTree("PHASE LFO", mainSettings)) {
					lfo_selection(&colour->params.phase_lfo_type);
					ImGui::SliderFloat("amp", &colour->params.phase_lfo_amp, 0.0, 1.0);
					ImGui::SliderFloat("speed", &colour->params.phase_lfo_speed, 0.0, 1.0);
					ImGui::SliderFloat("freq", &colour->params.phase_cycle_speed, 0.0, 1.0);
					ofxImGui::EndTree(mainSettings);
				}
				ofxImGui::EndTree(mainSettings);
				
			}
			ofxImGui::EndWindow(mainSettings);
		}
		this->gui.end();
		return mainSettings.mouseOverGui;
	}
}


