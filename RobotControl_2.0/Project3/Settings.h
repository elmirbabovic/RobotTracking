#pragma once
#include "TackbarValues.h"
#include <string>
#include "ATP/ListaSekv.h"


struct SettingsItem
{
	char name[20];
	TrackbarValues barFront;
	TrackbarValues barRear;
	SettingsItem()
	{
		strcpy_s(name, "profil");
	}

};
struct Settings
{
public:		bool JelIspravnoCitanje()
	{
		return random_value == 2131563;
	}
public: 	Settings()
	{
		random_value = 2131563;
	}

public:	void ResetValues()
{
	random_value = 2131563;
	for (int i = 0; i < 10; ++i)
	{
		strcpy_s(settingsItems[i].name, "Profil ");
		strcat_s(settingsItems[i].name, std::to_string(i).c_str());
		settingsItems[i].barFront = TrackbarValues();
		settingsItems[i].barRear = TrackbarValues();
	}
}

	TrackbarValues& Bar1()
{
		return settingsItems[defaultSettingsItem].barFront;
}
	TrackbarValues& Bar2()
	{
		return settingsItems[defaultSettingsItem].barRear;
	}

private:	int random_value;
public:		SettingsItem settingsItems[10];
public: 	int defaultSettingsItem=0;

public: 	SettingsItem& GetItem(int id)
	{
		return settingsItems[id];
	}
};
