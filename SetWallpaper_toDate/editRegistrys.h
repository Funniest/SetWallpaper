#pragma once

#include <iostream>
#include <string.h>
#include <windows.h>

class editRegistry {
private:
	HKEY hKey; //Registry handler
	char* path;

public:
	LONG result; //Registry func result

	void showKeyValues(); //show Registry key
	bool findKeyValue(char *m_keyName); //find Registry key
	bool delKeyValue(char *m_keyName); //delete Registry key
	bool createValue(char *m_keyName, char *m_path); //create Registry key or Set key

	//Constructor Over loading (By user)
	editRegistry(HKEY m_hKey, char* m_path) {
		//Open run registry
		result = RegOpenKeyExA(m_hKey, m_path, 0, KEY_ALL_ACCESS, &hKey);

		path = m_path;
	}

	//Destructor
	~editRegistry() {
		//close registry
		std::cout << "Registry edit success!!!" << std::endl;
		RegCloseKey(hKey);
	}
};