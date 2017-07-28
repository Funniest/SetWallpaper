#include "../SetWallpaper_toDate/editRegistrys.h"

//find Registry key
void editRegistry::showKeyValues() {
	HKEY tmp_hKey;
	char keyName[512];
	DWORD keyName_lens = 512;
	__int32 i = 0;

	std::cout << "Registry finding..." << std::endl;

	//memset keyName buffer(512Byte init to 0)
	tmp_hKey = editRegistry::hKey;
	memset(keyName, 0x00, 512 * sizeof(char));

	std::cout << "** " << editRegistry::path << " **" << std::endl;
	//show my registry key value;
	while (RegEnumValueA(tmp_hKey, i, keyName, &keyName_lens, NULL, NULL, NULL, NULL) != ERROR_NO_MORE_ITEMS) {
		std::cout << "	¦¦" << keyName << std::endl;

		i++;
		memset(keyName, 0x00, 512 * sizeof(char));
	}
}

//delete Registry key
bool editRegistry::delKeyValue(char *m_keyName) {
	switch (RegDeleteValueA(editRegistry::hKey, m_keyName))
	{
		//if delete success
	case ERROR_SUCCESS:
		MessageBoxA(NULL, "Delete Success!!!", NULL, MB_OK);
		return true;
	}

	//else
	MessageBoxA(NULL, "Delete Fail...", NULL, MB_OK);
	return false;
}

//Create registry key
bool editRegistry::createValue(char *m_keyName, char *m_path) {
	//
	switch (RegSetKeyValueA(editRegistry::hKey, NULL, m_keyName, REG_SZ, m_path, strlen(m_path) + 1))
	{
		//if create success
	case ERROR_SUCCESS:
		MessageBoxA(NULL, "create key and insert path data in run reg!!!", NULL, MB_OK);
		return true;
	}

	//else
	MessageBoxA(NULL, "Create key fail...", NULL, MB_OK);
	return false;
}

//find key valuse
bool editRegistry::findKeyValue(char *m_keyName) {
	switch (RegGetValueA(editRegistry::hKey, NULL, m_keyName, RRF_RT_ANY, NULL, NULL, NULL))
	{
		//if find success
	case ERROR_SUCCESS:
		return true;
	}

	//else
	return false;
}