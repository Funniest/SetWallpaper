#include "../SetWallpaper_toDate/setWallpapers.h"

//set wallpaper
bool setWallpaper::setPicture() {
	if (SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, setWallpaper::path, SPIF_UPDATEINIFILE))
		return true;

	return false;
}