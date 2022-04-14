//Authors:
 // Yash Kumar Sahu, CED19I039
 // Velidi Pradeep, EDM19B018
 // P. Lakshmi Viswanadh, EDM19B021 

#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <Wire.h>
#include "time.h"
#include <OneWire.h>
#include <DallasTemperature.h>

uint32_t global_time=0;

// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

//-----------------------------------------------
//############## Input Data Here ##############
//-----------------------------------------------
// Insert your network credentials
//Remember about FORTIGATE LOGIN
#define WIFI_SSID "GalaxyA50"
#define WIFI_PASSWORD "prrx1526"

// Insert Firebase project API Key
#define API_KEY "AIzaSyBvqj0F81vLwr8Uhf1whPZa-68Ojcq7Q-c"

// Insert Authorized Email and Corresponding Password
#define USER_EMAIL "jalalerthelp@gmail.com"
#define USER_PASSWORD "12345678"

// Insert RTDB URLefine the RTDB URL
#define DATABASE_URL "https://esp-firebase-demo-d4766-default-rtdb.asia-southeast1.firebasedatabase.app/"

//##############################################


// Define Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Variable to save USER UID
String uid;

// Database main path (to be updated in setup with the user UID)
String databasePath;
// Database child nodes
String tempPath = "/temperature";
String humPath = "/humidity";
String presPath = "/pressure";
String timePath = "/timestamp";

// Parent Node (to be updated in every loop)
String parentPath;

int timestamp;
FirebaseJson json;

const char* ntpServer = "pool.ntp.org";

// Timer variables (send new readings every three minutes)
unsigned long sendDataPrevMillis = 0;
unsigned long timerDelay = 10000;

// GPIO where the DS18B20 is connected to
const int oneWireBus = 4;     

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

// DS18B20 Get sensor readings
float readDSTemperatureC() {
  // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  sensors.requestTemperatures(); 
  float tempC = sensors.getTempCByIndex(0);

  if(tempC == -127.00) {
    Serial.println("Failed to read from DS18B20 sensor");
    return -1;
  } else {
    //Serial.print("Temperature Celsius: ");
    //Serial.println(tempC); 
  }
  return tempC;
}


// Initialize WiFi
void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println();
}


// Function that gets current epoch time
unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    //Serial.println("Failed to obtain time");
    return(global_time++);
  }
  time(&now);
  return now;
}

//#############################################################
//-------------- SETUP Function -------------------------------
//#############################################################
void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);
  
  // Start the DS18B20 sensor
  sensors.begin();

  initWiFi();
  configTime(0, 0, ntpServer);


  // Assign the api key (required)
  config.api_key = API_KEY;

  // Assign the user sign in credentials
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  // Assign the RTDB URL (required)
  config.database_url = DATABASE_URL;

  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);

  // Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  // Assign the maximum retry of token generation
  config.max_token_generation_retry = 5;

  // Initialize the library with the Firebase authen and config
  Firebase.begin(&config, &auth);

  // Getting the user UID might take a few seconds
  Serial.println("Getting User UID");
  while ((auth.token.uid) == "") {
    Serial.print('.');
    delay(1000);
  }
  // Print user UID
  uid = auth.token.uid.c_str();
  Serial.print("User UID: ");
  Serial.println(uid);

  // Update database path
  databasePath = "/UsersData/" + uid + "/readings";

}


//#############################################################
//-------------- LOOP Function -------------------------------
//#############################################################
void loop() {
  //sensors.requestTemperatures(); 
  float temperatureC = readDSTemperatureC();
  //Serial.print(temperatureC);
  //Serial.println("ºC");

  // Send new readings to database
  if (Firebase.ready() && (millis() - sendDataPrevMillis > timerDelay || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();

    //Get current timestamp
    timestamp = getTime();
    Serial.print ("time: ");
    Serial.println (timestamp);

    parentPath= databasePath + "/" + String(timestamp);

    json.set(tempPath.c_str(), String(temperatureC));
    json.set(humPath.c_str(), String(temperatureC));
    json.set(presPath.c_str(), String(temperatureC));
    json.set(timePath, String(timestamp));
    Serial.printf("Set json... %s\n", Firebase.RTDB.setJSON(&fbdo, parentPath.c_str(), &json) ? "ok" : fbdo.errorReason().c_str());
  }
    
}
