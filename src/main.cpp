/**
 * @file main.cpp
 * @author Hafidh Hidayat (hafidhhidayat@hotmail.com)
 * @brief 
 * 
 * @copyright Copyright (c) 2023
 * 
 * Github :
 * https://github.com/hafidhh
 * https://github.com/hafidhh/Time-ESP
 */

#if defined (ESP8266)
#include <ESP8266WiFi.h>
#endif

#if defined(ESP32)
#include <WiFi.h>
#endif

// WiFi info
const char* ssid = "your_ssid"; //SSID WIFI
const char* password = "your_password"; // Password WIFI

long prev, now;

/**
 * @brief Connect WiFi
 * 
 * @param ssid 
 * @param password 
 */
void wifi(const char* ssid, const char* password)
{
	Serial.print("Connecting to ");
	Serial.println(ssid);
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(250);
		Serial.print(".");
	}
	Serial.println("");
	Serial.println("WiFi connected");
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
}

/**
 * @brief Get the Time from NTP server
 * 
 * @param timezone GMT+, example >> GMT+7, timezone = 7
 * @return int now (timestamp)
 */
int syncTime(int timezone)
{
	configTime(0, 0, "pool.ntp.org");
	time_t now = time(nullptr);
	while (now < 8 * 3600 * 2) {
		delay(500);
		now = time(nullptr);
	}
	now += (timezone*3600);
	prev = millis();
	return now;
}

/**
 * @brief timestamp to human time
 * 
 * @param time 
 * @return String asctime (human time)
 */
String viewTime(int time)
{
	time_t now = time;
	struct tm timeinfo;
	gmtime_r(&now, &timeinfo);
	return asctime(&timeinfo);
}

void setup()
{
	Serial.begin(9600);
	wifi(ssid, password);
	now = syncTime(7); // GMT+7, change 7 with your timezone
	Serial.print(viewTime(now));
}

void loop()
{
	// Print Time every 30s
	if (millis() - prev >= 30000)
	{
		now += ((millis() - prev) / 1000);
		Serial.print(viewTime(now));
		prev = millis();
	}
}