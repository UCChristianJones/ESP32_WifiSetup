#ifndef _WIFISETUP_
#define _WIFISETUP_
#include "Arduino.h"

class WifiSetup
{
	static bool isAP;
	static String ipAddress;
	static String apSSID;
	static String apPass;
  static void SetAsAP();

public:
  static void Init(String ssid, String password, String hostname, String apName = "ESP32-AP", String apPass = "ChangeMe");
	static String GetMACAddress();
	static String GetIPAddress();
};

#endif