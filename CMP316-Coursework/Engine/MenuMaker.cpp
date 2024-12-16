#include "pch.h"
#include "MenuMaker.h"
#include <fstream>

void MenuMaker::writeMenus()
{	
	for (int i = 0; i < 2; i++)
	{
		checkTexture(bgTexturePath[i]);
		for (int j = 0; j < buttonHighTxt->size(); j++)
		{
			checkTexture(buttonHighTxt[i][j]);
			checkTexture(buttonNormTxt[i][j]);
		}		
	}

	std::ofstream out;
	out.open("../LoadingFiles/Menus");

	out << texVec.size() << ":";
	for (int i = 0; i < texVec.size(); i++)
	{
		out << texVec[i] << ";";
	}

	for (int i = 0; i < 2; i++)
	{
		out << menuType[i] << ";";
		out << bgTexturePath[i] << ";";
		out << title[i] << ";";
		out << titleXPos[i] << ";";
		out << titleYPos[i] << ";";
		out << bgXPos[i] << ";";
		out << bgYPos[i] << ";";
		out << bgXScale[i] << ";";
		out << bgYScale[i] << ";";
		out << textXSize[i] << ";";
		out << textYSize[i] << ";";

		out << buttonXPos->size() << ":";		
		for (int j = 0; j < buttonXPos->size(); j++)
		{
			out << buttonXPos[i][j] << ";";
			out << buttonYPos[i][j] << ";";
			out << buttonText[i][j] << ";";
			out << buttonNormTxt[i][j] << ";";
			out << buttonHighTxt[i][j] << ";";
			out << levelTarget[i][j] << ";";
			out << buttonXScale[i][j] << ";";
			out << buttonYScale[i][j] << ";";
		}
	}

	out.close();
}

void MenuMaker::checkTexture(std::string filepath)
{

	if (texVec.size() == 0)
	{
		texVec.push_back(filepath);
	}
	else
	{
		bool alreadyExists = false;
		for (int i = 0; i < texVec.size(); ++i)
		{
			if (texVec[i] == filepath)
			{
				alreadyExists = true;
				break;
			}
		}
		if (!alreadyExists)
		{
			texVec.push_back(filepath);
		}
	}
}
