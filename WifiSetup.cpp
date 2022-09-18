#include <WiFi.h> 
#include "WifiSetup.h"

#ifdef DEBUG
#ifndef p(v)
// add methods and vars here for debug only
#define p(v) Serial.println(v); 
#endif
#else
// redefine the above macros, but they dont do anything
#define p(v)
#endif

void WifiSetup::SetAsAP()
{
    p("Setting device as AP");
    WiFi.softAP(apSSID.c_str(), apPass.c_str());
    isAP = true;
    p("AP IP address: "); 
    IPAddress ip = WiFi.softAPIP();
		ipAddress = ip.toString();
    p(ip); 
  }

  void WifiSetup::Init(String ssid, String password, String hostname, String apName, String apPass)
  {
    p("Initializing Wifi");
    apSSID = apName;
    WifiSetup::apPass = apPass;
		 WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
       WiFi.setHostname(hostname.c_str()); //define hostname
       if(ssid == "" || password == "")
       { 
           p("No SSID or password set");
           SetAsAP();
           return;
       }
       WiFi.mode(WIFI_STA);
       WiFi.begin(ssid.c_str(), password.c_str());
       p("Connecting to WiFi...");
       uint8_t status = WiFi.status();
       int attempts = 0;
       while (status != WL_CONNECTED) 
       { 
           delay(1000); 
           status = WiFi.status();
           attempts++;
           p("Attempts to connect:");
           p(attempts);
           if(attempts > 30) // retry for 30 seconds (approx))
           {
               p("Unable to connect after 30 seconds");
               SetAsAP();
               return;
           }
       }
		  WiFi.setAutoReconnect(true);
		  WiFi.persistent(true);
       IPAddress ip = WiFi.localIP();
		ipAddress = ip.toString();
       Serial.print("IP Address: ");
       Serial.println(ip);
   }
	
	String WifiSetup::GetMACAddress()
	{
		return isAP ? WiFi.softAPmacAddress() : WiFi.macAddress();
	}
	String WifiSetup::GetIPAddress()
	{
			return ipAddress;
		}

bool WifiSetup::isAP(false);
String WifiSetup::ipAddress("");
String WifiSetup::apSSID("ESP32-AP");
String WifiSetup::apPass("ChangeMe");