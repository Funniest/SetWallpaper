#pragma warning(disable:4996)

#include <iostream>
#include <string.h>
#include <windows.h>
#include <time.h>

#include "../SetWallpaper_toDate/editRegistrys.h"
#include "../SetWallpaper_toDate/setWallpapers.h"

//Get my time
int getMonth() {
	time_t now = time(0);
	struct tm tStruct;
	
	tStruct = *localtime(&now);
	
	return tStruct.tm_mon + 1;
}

int main() {
	char *slideshowFolder = "C:\\Users\\minsn\\Pictures\\SlideShow\\";

	//
	//SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Run
	editRegistry *eReg = new editRegistry(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
	setWallpaper *sWall;

	//Registry open check
	switch (eReg->result)
	{
	case !ERROR_SUCCESS :
		MessageBoxA(NULL, "Registry open fail...", NULL, MB_OK);
		
		delete(eReg);
		return -1;
	}
	
	//find  slide_Wallpaper value in registry
	if (!eReg->findKeyValue("Slide_Wallpaper")) {
		//At computer boot and start
		if (!eReg->createValue("Slide_Wallpaper", "C:\\Users\\minsn\\Pictures\\SlideShow\\Program.exe")) {
			delete(eReg);
			return -1;
		}
	}

	eReg->showKeyValues();
	//delete
	delete(eReg);
	
	//get month
	__int32 intMonth = getMonth();
	std::cout << "Month : " << intMonth << std::endl;

	//malloc(month size , .jpg(4byte), null(1 byte))
	int month_num = ((intMonth > 10 ? 2 : 1) + 4 + 1) * sizeof(char);
	char *month = (char*)malloc(month_num);
	char *old_month = month;

	memset(month, 0x00, month_num);
	
	itoa(intMonth, month, 10);
	strcat(month, ".jpg"); //month.jpg
	std::cout << "Month to jpg : " << month << std::endl;

	//folder path + picture name + null
	int fullPath_num = (strlen(slideshowFolder) + strlen(month) + 1) * sizeof(char);
	char *fullPath = (char*)malloc(fullPath_num);
	char *old_fullPath = fullPath;
	memset(fullPath, 0x00, fullPath_num);

	strcat(fullPath, slideshowFolder);
	strcat(fullPath, month);
	std::cout << "full path : " << fullPath << std::endl;

	//month is free
	free(old_month);

	sWall = new setWallpaper(fullPath);
	free(old_fullPath);
	
	//set Wallpaper
	if (!sWall->setPicture()) {
		MessageBoxA(NULL, "No changing wallpaper!!!", NULL, MB_OK);
		
		delete(sWall);
		return -1;
	}
	
	//delete
	std::cout << "== END ==" << std::endl;
	delete(sWall);
	return 0;
}