#pragma once
#include <vector>

enum MENU_TYPE { MAIN, PAUSE };
using namespace std;

class MenuMaker
{
public:
	void setMenuType(MENU_TYPE type) { cm =  static_cast<int>(type);  menuType[cm] = type; };
	void setBgTexture(string filepath) { bgTexturePath[cm] = filepath; };
	void setTitleText(string text) { title[cm] = text; };
	void setTitleXPos(float x) { titleXPos[cm] = x; };
	void setTitleYPos(float y) { titleYPos[cm] = y; };
	void setBGXScale(float x) { bgXScale[cm] = x; };
	void setBGYScale(float y) { bgYScale[cm] = y; };
	void setFontSize(float x) { textXSize[cm] = x; };
	void setTextScale(float y) { textYSize[cm] = y; };

	void setButtonXPos(float x) { buttonXPos[cm].push_back(x); };
	void setButtonYPos(float y) { buttonYPos[cm].push_back(y); };
	void setButtonText(string text) { buttonText[cm].push_back(text); };
	void setButtonNormalTexture(string text) { buttonNormTxt[cm].push_back(text); };
	void setButtonHighlightTexture(string text) { buttonHighTxt[cm].push_back(text); };
	void setLevelToTarget(int lvl) { levelTarget[cm].push_back(lvl); };
	void setButtonFontSize(float x) { buttonTextXScale[cm].push_back(x); };
	void setButtonTextScale(float y) { buttonTextYScale[cm].push_back(y); };
	void setButonXScale(float x) { buttonXScale[cm].push_back(x); };
	void setButonYScale(float y) { buttonYScale[cm].push_back(y); };
	void writeMenus();

private:
	void checkTexture(std::string filepath);
	std::vector<std::string> texVec;

	int cm;
	MENU_TYPE menuType[2];
	string bgTexturePath[2];
	string title[2];
	float titleXPos[2];
	float titleYPos[2];
	float bgXPos[2];
	float bgYPos[2];
	float bgXScale[2];
	float bgYScale[2];
	float textXSize[2];
	float textYSize[2];

	vector<float> buttonXPos[2];
	vector<float> buttonYPos[2];
	vector<string> buttonText[2];
	vector<string> buttonNormTxt[2];
	vector<string> buttonHighTxt[2];
	vector<int> levelTarget[2];
	vector<float> buttonXScale[2];
	vector<float> buttonYScale[2];
	vector<float> buttonTextXScale[2];
	vector<float> buttonTextYScale[2];
};

