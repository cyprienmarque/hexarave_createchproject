#include <esp_now.h>
#include <WiFi.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

int ledblue = 2;

uint8_t broadcastAddress[] = {0xB0, 0xA7, 0x32, 0x27, 0xFA, 0x50};

#define BOARD_ID 4

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  int id;
  float x;
  float y;
  float z;
  float gx;
  float gy;
  float gz;
} struct_message;

// Create a struct_message called myData
struct_message myData;

unsigned long lastTime = 0;
unsigned long timerDelay = 100;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  pinMode(ledblue, OUTPUT);

  // Init Serial Monitor
  Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  
  //ACCELEROMETER PART  
	// Try to initialize accelerometer
  	if (!mpu.begin()) {
		Serial.println("Failed to find MPU6050 chip");
		while (1) {
		  delay(10);
		}
	}
	Serial.println("MPU6050 Found!");

	// set accelerometer range to +-8G
	mpu.setAccelerometerRange(MPU6050_RANGE_2_G);

	// set gyro range to +- 500 deg/s
	mpu.setGyroRange(MPU6050_RANGE_500_DEG);

	// set filter bandwidth to 21 Hz
	mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  delay(100);
}
 
void loop() {
  /* Get new sensor events with the readings */
	sensors_event_t a, g, temp;
	mpu.getEvent(&a, &g, &temp);

  // Send message via ESP-NOW
  if ((millis() - lastTime) > timerDelay) {
    
    /*
    //  Version vitesse angulaire :
    // Affichage des valeurs envoyées
    Serial.print("X: ");
    Serial.print(g.gyro.x);
    Serial.print(" rad/s");
    Serial.print(" | ");
    Serial.print("Y: ");
    Serial.print(g.gyro.y);
    Serial.print(" rad/s");
    Serial.print(" | ");
    Serial.print("Z: ");
    Serial.print(g.gyro.z);
    Serial.print(" rad/s");
    Serial.println();

    // Set values to send
    myData.id = BOARD_ID;
    myData.x = g.gyro.x;
    myData.y = g.gyro.y;
    myData.z = g.gyro.z;
    */

    a.acceleration.x = a.acceleration.x/9.81;
    a.acceleration.y = a.acceleration.y/9.81;
    a.acceleration.z = a.acceleration.z/9.81;

    //  Version accélération linéaire :
    Serial.print("X: ");
    Serial.print(a.acceleration.x);
    Serial.print(" g");
    Serial.print(" | ");
    Serial.print("Y: ");
    Serial.print(a.acceleration.y);
    Serial.print(" g");
    Serial.print(" | ");
    Serial.print("Z: ");
    Serial.print(a.acceleration.z);
    Serial.print(" g");
    Serial.println();

    //Vitesse angulaire :
    Serial.print("X': ");
    Serial.print(g.gyro.x);
    Serial.print(" degré/s");
    Serial.print(" | ");
    Serial.print("Y': ");
    Serial.print(g.gyro.y);
    Serial.print(" degré/s");
    Serial.print(" | ");
    Serial.print("Z': ");
    Serial.print(g.gyro.z);
    Serial.print(" degré/s");
    Serial.println();

    // Set values to send
    myData.id = BOARD_ID;
    myData.x = a.acceleration.x;
    myData.y = a.acceleration.y;
    myData.z = a.acceleration.z;
    myData.gx = g.gyro.x;
    myData.gy = g.gyro.y;
    myData.gz = g.gyro.z;

    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

    if (result == ESP_OK) {
      Serial.println("Sent with success");
    }
    else {
      Serial.println("Error sending the data");
    }

    lastTime = millis();
  }
}