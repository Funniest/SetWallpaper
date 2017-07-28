#pragma once

#include <iostream>
#include <string.h>
#include <windows.h>

class setWallpaper {
private :
	char* path;

public :
	bool setPicture();

	//Constructor
	setWallpaper(char *m_path) {
		//get picture path
		path = m_path;
	}

	//Destructor
	~setWallpaper() {}
};