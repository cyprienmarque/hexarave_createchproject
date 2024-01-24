#include <esp_now.h>
#include <WiFi.h>
#include <FastLED.h>

//Define
#define NUM_LEDS  45
#define DATA_PIN1   15
#define DATA_PIN2   2
#define DATA_PIN3   4
#define DATA_PIN4   5
#define DATA_PIN5   18
#define DATA_PIN6   19

// Define the array of leds
CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];
CRGB leds4[NUM_LEDS];
CRGB leds5[NUM_LEDS];
CRGB leds6[NUM_LEDS];

// Structure example to receive datavc
// Must match the sender structure
typedef struct struct_message {
    int id;
    float x;
    float y;
    float z;
    float gx;
    float gy;
    float gz;
} struct_message;

int len;
int i = 0;
int bright = 50;

//TIMER PATTERN
int timepattern1 = 1000;
int timepattern2 = 2000;
int timepattern3 = 3000;
int timepattern4 = 4000;
int timepattern5 = 5000;
int timepattern6 = 6000;
int timepattern7 = 7000;
int timepattern8 = 8000;


unsigned long lastTime = 0;
unsigned long timerDelay = 1000;

//ONE
unsigned long lastTime1 = 0;
unsigned long timerDelay1 = 50;
unsigned long lastTime1_7 = 0;
unsigned long timerDelay1_7 = 50;
bool debut1 = true;
bool debut1_3 = true;
bool debut1_5 = true;
bool debut1_6 = true;
int fadespeed1 = 5;
int compteurpattern1_7 = 0;

//TWO
unsigned long lastTime2 = 0;
unsigned long timerDelay2 = 50;
unsigned long lastTime2_7 = 0;
unsigned long timerDelay2_7 = 50;
bool debut2 = true;
bool debut2_3 = true;
bool debut2_5 = true;
bool debut2_6 = true;
int fadespeed2 = 5;
int compteurpattern2_7 = 0;

//THREE
unsigned long lastTime3 = 0;
unsigned long timerDelay3 = 50;
unsigned long lastTime3_7 = 0;
unsigned long timerDelay3_7 = 50;
bool debut3 = true;
bool debut3_3 = true;
bool debut3_5 = true;
bool debut3_6 = true;
int fadespeed3 = 5;
int compteurpattern3_7 = 0;

//FOUR
unsigned long lastTime4 = 0;
unsigned long timerDelay4 = 50;
unsigned long lastTime4_7 = 0;
unsigned long timerDelay4_7 = 50;
bool debut4 = true;
bool debut4_3 = true;
bool debut4_5 = true;
bool debut4_6 = true;
int fadespeed4 = 5;
int compteurpattern4_7 = 0;

//FIVE
unsigned long lastTime5 = 0;
unsigned long timerDelay5 = 50;
unsigned long lastTime5_7 = 0;
unsigned long timerDelay5_7 = 50;
bool debut5 = true;
bool debut5_3 = true;
bool debut5_5 = true;
bool debut5_6 = true;
int fadespeed5 = 5;
int compteurpattern5_7 = 0;

//SIX
unsigned long lastTime6 = 0;
unsigned long timerDelay6 = 50;
unsigned long lastTime6_7 = 0;
unsigned long timerDelay6_7 = 50;
bool debut6 = true;
bool debut6_3 = true;
bool debut6_5 = true;
bool debut6_6 = true;
int fadespeed6 = 5;
int compteurpattern6_7 = 0;

//TEST OnDataRecv APPELEE
int OnDataReception[6] = {0, 0, 0, 0, 0, 0};

//TEST OnDataRecv APPELEE
int OnDataRecep[6] = {0, 0, 0, 0, 0, 0};

//Test danse sans interruption
int DanseNoInterrupt[6] = {0, 0, 0, 0, 0, 0};

// Create a struct_message called myData
struct_message myData;

// Create a structure to hold the readings from each board
struct_message board1;
struct_message board2;
struct_message board3;
struct_message board4;
struct_message board5;
struct_message board6;

// Create an array with all the structures
struct_message boardsStruct[6] = {board1, board2, board3, board4, board5, board6};

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
  char macStr[18];
  Serial.print("Packet received from: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.println(macStr);
  
  memcpy(&myData, incomingData, sizeof(myData));

  
  Serial.printf("Board ID %u: %u bytes\n", myData.id, len);
  // Update the structures with the new incoming data
  boardsStruct[myData.id-1].x = myData.x;
  boardsStruct[myData.id-1].y = myData.y;
  boardsStruct[myData.id-1].z = myData.z;
  boardsStruct[myData.id-1].gx = myData.gx;
  boardsStruct[myData.id-1].gy = myData.gy;
  boardsStruct[myData.id-1].gz = myData.gz;
  OnDataReception[myData.id-1] = 0;
  Serial.printf("x value: %f \n", boardsStruct[myData.id-1].x);
  Serial.printf("y value: %f \n", boardsStruct[myData.id-1].y);
  Serial.printf("z value: %f \n", boardsStruct[myData.id-1].z);
  Serial.printf("gx value: %f \n", boardsStruct[myData.id-1].gx);
  Serial.printf("gy value: %f \n", boardsStruct[myData.id-1].gy);
  Serial.printf("gz value: %f \n", boardsStruct[myData.id-1].gz);
  Serial.printf("OnDataReception value: %d \n", OnDataReception[myData.id-1]);
  Serial.println();

}
 
void setup() {
  // Initialize fast led
  FastLED.addLeds<WS2812, DATA_PIN1>(leds1, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<WS2812, DATA_PIN2>(leds2, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<WS2812, DATA_PIN3>(leds3, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<WS2812, DATA_PIN4>(leds4, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<WS2812, DATA_PIN5>(leds5, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<WS2812, DATA_PIN6>(leds6, NUM_LEDS).setCorrection(TypicalLEDStrip);
  

  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {

  //Maximum mouvement + Test danse sans interruption
  for(int i = 0; i<=5; i++){
    DanseNoInterrupt[i]++;
    if(abs(boardsStruct[i].x) > 1){
      boardsStruct[i].x = 1;
    }
    if(abs(boardsStruct[i].y) > 1){
      boardsStruct[i].y = 1;
    }
    if(abs(boardsStruct[i].z) > 1){
      boardsStruct[i].z = 1;
    }
    if(abs(boardsStruct[i].gx) < 0.2 && abs(boardsStruct[i].gy) < 0.2 && abs(boardsStruct[i].gz) < 0.2 ){
      DanseNoInterrupt[i] = 0;
      if(i == 0){
        debut1 = true;
        debut1_3 = true;
        debut1_5 = true;
        debut1_6 = true;
      }

      if(i == 1){
        debut2 = true;
        debut2_3 = true;
        debut2_5 = true;
        debut2_6 = true;
      }

      if(i == 2){
        debut3 = true;
        debut3_3 = true;
        debut3_5 = true;
        debut3_6 = true;
      }

      if(i == 3){
        debut4 = true;
        debut4_3 = true;
        debut4_5 = true;
        debut4_6 = true;
      }

      if(i == 4){
        debut5 = true;
        debut5_3 = true;
        debut5_5 = true;
        debut5_6 = true;
      }

      if(i == 5){
        debut6 = true;
        debut6_3 = true;
        debut6_5 = true;
        debut6_6 = true;
      }
    }
    
  }


  //TEST BRACELET ETEINT
  if ((millis() - lastTime) > timerDelay) {
    for(int i = 0; i <= 5; i++ ){
      OnDataReception[i]++;
    }
    lastTime = millis();
  }

  //INITIALISATION POUR TRIANGLE 1
  static int direction1 = 1; // 1 pour aller vers la droite, -1 pour aller vers la gauche
  static int direction1_2 = 1; 
  static int direction1_3 = 1; 
  static int currentPixel1 = 0;
  static int currentPixel1_2 = 0;
  static int currentPixel1_3 = 0;

  //INITIALISATION POUR TRIANGLE 2
  static int direction2 = 1; // 1 pour aller vers la droite, -1 pour aller vers la gauche
  static int direction2_2 = 1; 
  static int direction2_3 = 1; 
  static int currentPixel2 = 0;
  static int currentPixel2_2 = 0;
  static int currentPixel2_3 = 0;

  //INITIALISATION POUR TRIANGLE 3
  static int direction3 = 1; // 1 pour aller vers la droite, -1 pour aller vers la gauche
  static int direction3_2 = 1; 
  static int direction3_3 = 1; 
  static int currentPixel3 = 0;
  static int currentPixel3_2 = 0;
  static int currentPixel3_3 = 0;

  //INITIALISATION POUR TRIANGLE 4
  static int direction4 = 1; // 1 pour aller vers la droite, -1 pour aller vers la gauche
  static int direction4_2 = 1; 
  static int direction4_3 = 1; 
  static int currentPixel4 = 0;
  static int currentPixel4_2 = 0;
  static int currentPixel4_3 = 0;

  //INITIALISATION POUR TRIANGLE 5
  static int direction5 = 1; // 1 pour aller vers la droite, -1 pour aller vers la gauche
  static int direction5_2 = 1; 
  static int direction5_3 = 1; 
  static int currentPixel5 = 0;
  static int currentPixel5_2 = 0;
  static int currentPixel5_3 = 0;

  //INITIALISATION POUR TRIANGLE 6
  static int direction6 = 1; // 1 pour aller vers la droite, -1 pour aller vers la gauche
  static int direction6_2 = 1; 
  static int direction6_3 = 1; 
  static int currentPixel6 = 0;
  static int currentPixel6_2 = 0;
  static int currentPixel6_3 = 0;

//LUMIERE 1
  if((millis() - lastTime1) >= timerDelay1) {

    //Vitesse selon mouvement du bracelet 1
    float speed1f = abs(boardsStruct[0].gx)+abs(boardsStruct[0].gy)+abs(boardsStruct[0].gz);
    if(speed1f < 1){
      speed1f = 1;
    }
    int speed1 = speed1f;
    timerDelay1 = 70/sqrt(speed1);
    if(timerDelay1 < 5){
      timerDelay1 = 5;
    }
    //Vitesse de fade
    fadespeed1 = 2*speed1f*sqrt(speed1f);
    //Vitesse pattern 7
    timerDelay1_7 = 800/sqrt(speed1);

    if(OnDataReception[0]<5 && DanseNoInterrupt[0]>0){

      //PATTERN 1 ALLER INFINI
      if( timepattern1 >= DanseNoInterrupt[0])
      {
        // Déplacer le pixel
        currentPixel1 += direction1;
        // Changer la direction6 si on atteint le bord
        if (currentPixel1 == NUM_LEDS) {
          currentPixel1 = 0; // Revenir au début
        }
        // Allumer la LED actuelle
        leds1[currentPixel1].setRGB(255*abs(boardsStruct[0].x), 255*abs(boardsStruct[0].y), 255*abs(boardsStruct[0].z));
        FastLED.show();
      }


      //PATTERN 2 ALLER INFINI x2
      if( timepattern2 >= DanseNoInterrupt[0] && DanseNoInterrupt[0] > timepattern1){
        // Déplacer le pixel
        if(debut1 == true){
          if(currentPixel1 >30){
            currentPixel1_2 = currentPixel1 - 30;
          }
          if(currentPixel1 <= 30){
            currentPixel1_2 = currentPixel1 + 15;
          }
        }
        currentPixel1 += direction1;
        currentPixel1_2 += direction1;
        // Changer la direction6 si on atteint le bord
        if (currentPixel1 == NUM_LEDS) {
          currentPixel1 = 0; // Revenir au début
        }
        if (currentPixel1_2 == NUM_LEDS) {
          currentPixel1_2 = 0; // Revenir au début
        }
        // Allumer la LED actuelle
        leds1[currentPixel1].setRGB(255*abs(boardsStruct[0].x), 255*abs(boardsStruct[0].y), 255*abs(boardsStruct[0].z));
        leds1[currentPixel1_2].setRGB(255*abs(boardsStruct[0].x), 255*abs(boardsStruct[0].y), 255*abs(boardsStruct[0].z));
        FastLED.show();
        Serial.print(DanseNoInterrupt[0]);
        debut1 = false;
      }
      

      //PATTERN 3 ALLER INFINI x3
      if( timepattern3 >= DanseNoInterrupt[0] && DanseNoInterrupt[0] > timepattern2){
        // Déplacer le pixel
        if(debut1_3 == true){
          if(currentPixel1_2 >30){
            currentPixel1_3 = currentPixel1_2 - 30;
          }
          if(currentPixel1_2 <= 30){
            currentPixel1_3 = currentPixel1_2 + 15;
          }
        }
        currentPixel1 += direction1;
        currentPixel1_2 += direction1;
        currentPixel1_3 += direction1;
        // Changer la direction6 si on atteint le bord
        if (currentPixel1 == NUM_LEDS) {
          currentPixel1 = 0; // Revenir au début
        }
        if (currentPixel1_2 == NUM_LEDS) {
          currentPixel1_2 = 0; // Revenir au début
        }
        if (currentPixel1_3 == NUM_LEDS) {
          currentPixel1_3 = 0; // Revenir au début
        }
        // Allumer la LED actuelle
        leds1[currentPixel1].setRGB(255*abs(boardsStruct[0].x), 255*abs(boardsStruct[0].y), 255*abs(boardsStruct[0].z));
        leds1[currentPixel1_2].setRGB(255*abs(boardsStruct[0].x), 255*abs(boardsStruct[0].y), 255*abs(boardsStruct[0].z));
        leds1[currentPixel1_3].setRGB(255*abs(boardsStruct[0].x), 255*abs(boardsStruct[0].y), 255*abs(boardsStruct[0].z));
        FastLED.show();
        Serial.print(DanseNoInterrupt[0]);
        debut1_3 = false;
      }


      //PATTERN 4 ALLER RETOUR
      if(timepattern4 >= DanseNoInterrupt[0] && DanseNoInterrupt[0] > timepattern3){
        // Déplacer le pixel
        currentPixel1 += direction1;
        // Changer la direction6 si on atteint les bords
        if (currentPixel1 == NUM_LEDS || currentPixel1 == -1) {
          direction1 *= -1; // Changer de direction6
          currentPixel1 += direction1; // Ajuster pour éviter de déborder
        }
        // Allumer la LED actuelle
        leds1[currentPixel1].setRGB(255*abs(boardsStruct[0].x), 255*abs(boardsStruct[0].y), 255*abs(boardsStruct[0].z));
        FastLED.show();
      }


      //PATTERN 5 ALLER RETOUR x2
      if( timepattern5 >= DanseNoInterrupt[0] && DanseNoInterrupt[0] > timepattern4){
        // Déplacer le pixel
        if(debut1_5 == true){
          if(currentPixel1 >30){
            currentPixel1_2 = currentPixel1 - 30;
          }
          if(currentPixel1 <= 30){
            currentPixel1_2 = currentPixel1 + 15;
          }
        }
        currentPixel1 += direction1;
        currentPixel1_2 += direction1_2;
        // Changer la direction6 si on atteint le bord
        if (currentPixel1 == NUM_LEDS || currentPixel1 == -1) {
          direction1 *= -1; // Changer de direction6
          currentPixel1 += direction1; // Ajuster pour éviter de déborder
        }
        if (currentPixel1_2 == NUM_LEDS || currentPixel1_2 == -1) {
          direction1_2 *= -1; // Changer de direction6
          currentPixel1_2 += direction1_2; // Ajuster pour éviter de déborder
        }
        // Allumer la LED actuelle
        leds1[currentPixel1].setRGB(255*abs(boardsStruct[0].x), 255*abs(boardsStruct[0].y), 255*abs(boardsStruct[0].z));
        leds1[currentPixel1_2].setRGB(255*abs(boardsStruct[0].x), 255*abs(boardsStruct[0].y), 255*abs(boardsStruct[0].z));
        FastLED.show();
        Serial.print(DanseNoInterrupt[0]);
        debut1_5 = false;
      }

      //PATTERN 6 ALLER RETOUR x3
      if( timepattern6 >= DanseNoInterrupt[0] && DanseNoInterrupt[0] > timepattern5){
        // Déplacer le pixel
        if(debut1_6 == true){
          if(currentPixel1_2 >30){
            currentPixel1_3 = currentPixel1_2 - 30;
          }
          if(currentPixel1_2 <= 30){
            currentPixel1_3 = currentPixel1_2 + 15;
          }
        }
        currentPixel1 += direction1;
        currentPixel1_2 += direction1_2;
        currentPixel1_3 += direction1_3;
        // Changer la direction6 si on atteint le bord
        // Changer la direction6 si on atteint le bord
        if (currentPixel1 == NUM_LEDS || currentPixel1 == -1) {
          direction1 *= -1; // Changer de direction6
          currentPixel1 += direction1; // Ajuster pour éviter de déborder
        }
        if (currentPixel1_2 == NUM_LEDS || currentPixel1_2 == -1) {
          direction1_2 *= -1; // Changer de direction6
          currentPixel1_2 += direction1_2; // Ajuster pour éviter de déborder
        }
        if (currentPixel1_3 == NUM_LEDS || currentPixel1_3 == -1) {
          direction1_3 *= -1; // Changer de direction6
          currentPixel1_3 += direction1_3; // Ajuster pour éviter de déborder
        }
        // Allumer la LED actuelle
        leds1[currentPixel1].setRGB(255*abs(boardsStruct[0].x), 255*abs(boardsStruct[0].y), 255*abs(boardsStruct[0].z));
        leds1[currentPixel1_2].setRGB(255*abs(boardsStruct[0].x), 255*abs(boardsStruct[0].y), 255*abs(boardsStruct[0].z));
        leds1[currentPixel1_3].setRGB(255*abs(boardsStruct[0].x), 255*abs(boardsStruct[0].y), 255*abs(boardsStruct[0].z));
        FastLED.show();
        Serial.print(DanseNoInterrupt[0]);
        debut1_6 = false;
      }


      //PATTERN 7 Flash 1/3
      if(timepattern7 >= DanseNoInterrupt[0] && DanseNoInterrupt[0] > timepattern6){
        if((millis() - lastTime1_7) >= timerDelay1_7){
          int compteur1_7 = compteurpattern1_7 + 15;
          while( compteurpattern1_7 < compteur1_7){
            leds1[compteurpattern1_7].setRGB(255*abs(boardsStruct[0].x), 255*abs(boardsStruct[0].y), 255*abs(boardsStruct[0].z));;
            compteurpattern1_7++;
          }
          if(compteurpattern1_7 >= 45){
            compteurpattern1_7 = 0;
          }
          lastTime1_7 = millis();
        }
      }


      //PATTERN 8 Flash
      if(timepattern8 >= DanseNoInterrupt[0] && DanseNoInterrupt[0] > timepattern7){
        if((millis() - lastTime1_7) >= timerDelay1_7){
          while( compteurpattern1_7 < 45){
            leds1[compteurpattern1_7].setRGB(255*abs(boardsStruct[0].x), 255*abs(boardsStruct[0].y), 255*abs(boardsStruct[0].z));;
            compteurpattern1_7++;
          }
          compteurpattern1_7 = 0;
          lastTime1_7 = millis();
        }
      }
    }
  lastTime1 = millis();
  }
  fadeToBlackBy( leds1, NUM_LEDS, fadespeed1);
  FastLED.show();

  
//LUMIERE 2
  if((millis() - lastTime2) >= timerDelay2) {

    //Vitesse selon mouvement du bracelet 1
    float speed2f = abs(boardsStruct[1].gx)+abs(boardsStruct[1].gy)+abs(boardsStruct[1].gz);
    if(speed2f < 1){
      speed2f = 1;
    }
    int speed2 = speed2f;
    timerDelay2 = 70/sqrt(speed2);
    if(timerDelay2 < 5){
      timerDelay2 = 5;
    }
    //Vitesse de fade
    fadespeed2 = 2*speed2f*sqrt(speed2f);
    //Vitesse pattern 7
    timerDelay2_7 = 800/sqrt(speed2);

    if(OnDataReception[1]<5 && DanseNoInterrupt[1]>0){

      //PATTERN 1 ALLER INFINI
      if( timepattern1 >= DanseNoInterrupt[1])
      {
        // Déplacer le pixel
        currentPixel2 += direction2;
        // Changer la direction6 si on atteint le bord
        if (currentPixel2 == NUM_LEDS) {
          currentPixel2 = 0; // Revenir au début
        }
        // Allumer la LED actuelle
        leds2[currentPixel2].setRGB(255*abs(boardsStruct[1].x), 255*abs(boardsStruct[1].y), 255*abs(boardsStruct[1].z));
        FastLED.show();
      }


      //PATTERN 2 ALLER INFINI x2
      if( timepattern2 >= DanseNoInterrupt[1] && DanseNoInterrupt[1] > timepattern1){
        // Déplacer le pixel
        if(debut2 == true){
          if(currentPixel2 >30){
            currentPixel2_2 = currentPixel2 - 30;
          }
          if(currentPixel2 <= 30){
            currentPixel2_2 = currentPixel2 + 15;
          }
        }
        currentPixel2 += direction2;
        currentPixel2_2 += direction2;
        // Changer la direction6 si on atteint le bord
        if (currentPixel2 == NUM_LEDS) {
          currentPixel2 = 0; // Revenir au début
        }
        if (currentPixel2_2 == NUM_LEDS) {
          currentPixel2_2 = 0; // Revenir au début
        }
        // Allumer la LED actuelle
        leds2[currentPixel2].setRGB(255*abs(boardsStruct[1].x), 255*abs(boardsStruct[1].y), 255*abs(boardsStruct[1].z));
        leds2[currentPixel2_2].setRGB(255*abs(boardsStruct[1].x), 255*abs(boardsStruct[1].y), 255*abs(boardsStruct[1].z));
        FastLED.show();
        Serial.print(DanseNoInterrupt[1]);
        debut2 = false;
      }
      

      //PATTERN 3 ALLER INFINI x3
      if( timepattern3 >= DanseNoInterrupt[1] && DanseNoInterrupt[1] > timepattern2){
        // Déplacer le pixel
        if(debut2_3 == true){
          if(currentPixel2_2 >30){
            currentPixel2_3 = currentPixel2_2 - 30;
          }
          if(currentPixel2_2 <= 30){
            currentPixel2_3 = currentPixel2_2 + 15;
          }
        }
        currentPixel2 += direction2;
        currentPixel2_2 += direction2;
        currentPixel2_3 += direction2;
        // Changer la direction6 si on atteint le bord
        if (currentPixel2 == NUM_LEDS) {
          currentPixel2 = 0; // Revenir au début
        }
        if (currentPixel2_2 == NUM_LEDS) {
          currentPixel2_2 = 0; // Revenir au début
        }
        if (currentPixel2_3 == NUM_LEDS) {
          currentPixel2_3 = 0; // Revenir au début
        }
        // Allumer la LED actuelle
        leds2[currentPixel2].setRGB(255*abs(boardsStruct[1].x), 255*abs(boardsStruct[1].y), 255*abs(boardsStruct[1].z));
        leds2[currentPixel2_2].setRGB(255*abs(boardsStruct[1].x), 255*abs(boardsStruct[1].y), 255*abs(boardsStruct[1].z));
        leds2[currentPixel2_3].setRGB(255*abs(boardsStruct[1].x), 255*abs(boardsStruct[1].y), 255*abs(boardsStruct[1].z));
        FastLED.show();
        Serial.print(DanseNoInterrupt[1]);
        debut2_3 = false;
      }


      //PATTERN 4 ALLER RETOUR
      if(timepattern4 >= DanseNoInterrupt[1] && DanseNoInterrupt[1] > timepattern3){
        // Déplacer le pixel
        currentPixel2 += direction2;
        // Changer la direction6 si on atteint les bords
        if (currentPixel2 == NUM_LEDS || currentPixel2 == -1) {
          direction2 *= -1; // Changer de direction6
          currentPixel2 += direction2; // Ajuster pour éviter de déborder
        }
        // Allumer la LED actuelle
        leds2[currentPixel2].setRGB(255*abs(boardsStruct[1].x), 255*abs(boardsStruct[1].y), 255*abs(boardsStruct[1].z));
        FastLED.show();
      }


      //PATTERN 5 ALLER RETOUR x2
      if( timepattern5 >= DanseNoInterrupt[1] && DanseNoInterrupt[1] > timepattern4){
        // Déplacer le pixel
        if(debut2_5 == true){
          if(currentPixel2 >30){
            currentPixel2_2 = currentPixel2 - 30;
          }
          if(currentPixel2 <= 30){
            currentPixel2_2 = currentPixel2 + 15;
          }
        }
        currentPixel2 += direction2;
        currentPixel2_2 += direction2_2;
        // Changer la direction6 si on atteint le bord
        if (currentPixel2 == NUM_LEDS || currentPixel2 == -1) {
          direction2 *= -1; // Changer de direction6
          currentPixel2 += direction2; // Ajuster pour éviter de déborder
        }
        if (currentPixel2_2 == NUM_LEDS || currentPixel2_2 == -1) {
          direction2_2 *= -1; // Changer de direction6
          currentPixel2_2 += direction2_2; // Ajuster pour éviter de déborder
        }
        // Allumer la LED actuelle
        leds2[currentPixel2].setRGB(255*abs(boardsStruct[1].x), 255*abs(boardsStruct[1].y), 255*abs(boardsStruct[1].z));
        leds2[currentPixel2_2].setRGB(255*abs(boardsStruct[1].x), 255*abs(boardsStruct[1].y), 255*abs(boardsStruct[1].z));
        FastLED.show();
        Serial.print(DanseNoInterrupt[1]);
        debut2_5 = false;
      }

      //PATTERN 6 ALLER RETOUR x3
      if( timepattern6 >= DanseNoInterrupt[1] && DanseNoInterrupt[1] > timepattern5){
        // Déplacer le pixel
        if(debut2_6 == true){
          if(currentPixel2_2 >30){
            currentPixel2_3 = currentPixel2_2 - 30;
          }
          if(currentPixel2_2 <= 30){
            currentPixel2_3 = currentPixel2_2 + 15;
          }
        }
        currentPixel2 += direction2;
        currentPixel2_2 += direction2_2;
        currentPixel2_3 += direction2_3;
        // Changer la direction6 si on atteint le bord
        // Changer la direction6 si on atteint le bord
        if (currentPixel2 == NUM_LEDS || currentPixel2 == -1) {
          direction2 *= -1; // Changer de direction6
          currentPixel2 += direction2; // Ajuster pour éviter de déborder
        }
        if (currentPixel2_2 == NUM_LEDS || currentPixel2_2 == -1) {
          direction2_2 *= -1; // Changer de direction6
          currentPixel2_2 += direction2_2; // Ajuster pour éviter de déborder
        }
        if (currentPixel2_3 == NUM_LEDS || currentPixel2_3 == -1) {
          direction2_3 *= -1; // Changer de direction6
          currentPixel2_3 += direction2_3; // Ajuster pour éviter de déborder
        }
        // Allumer la LED actuelle
        leds2[currentPixel2].setRGB(255*abs(boardsStruct[1].x), 255*abs(boardsStruct[1].y), 255*abs(boardsStruct[1].z));
        leds2[currentPixel2_2].setRGB(255*abs(boardsStruct[1].x), 255*abs(boardsStruct[1].y), 255*abs(boardsStruct[1].z));
        leds2[currentPixel2_3].setRGB(255*abs(boardsStruct[1].x), 255*abs(boardsStruct[1].y), 255*abs(boardsStruct[1].z));
        FastLED.show();
        Serial.print(DanseNoInterrupt[1]);
        debut2_6 = false;
      }


      //PATTERN 7 Flash 1/3
      if(timepattern7 >= DanseNoInterrupt[1] && DanseNoInterrupt[1] > timepattern6){
        if((millis() - lastTime2_7) >= timerDelay2_7){
          int compteur2_7 = compteurpattern2_7 + 15;
          while( compteurpattern2_7 < compteur2_7){
            leds2[compteurpattern2_7].setRGB(255*abs(boardsStruct[1].x), 255*abs(boardsStruct[1].y), 255*abs(boardsStruct[1].z));;
            compteurpattern2_7++;
          }
          if(compteurpattern2_7 >= 45){
            compteurpattern2_7 = 0;
          }
          lastTime2_7 = millis();
        }
      }

      //PATTERN 8 Flash
      if(timepattern8 >= DanseNoInterrupt[1] && DanseNoInterrupt[1] > timepattern7){
        if((millis() - lastTime2_7) >= timerDelay2_7){
          while( compteurpattern2_7 < 45){
            leds2[compteurpattern2_7].setRGB(255*abs(boardsStruct[1].x), 255*abs(boardsStruct[1].y), 255*abs(boardsStruct[1].z));;
            compteurpattern2_7++;
          }
          compteurpattern2_7 = 0;
          lastTime2_7 = millis();
        }
      }
    }
  lastTime2 = millis();
  }
  fadeToBlackBy( leds2, NUM_LEDS, fadespeed2);
  FastLED.show();


//LUMIERE 3
  if((millis() - lastTime3) >= timerDelay3) {

    //Vitesse selon mouvement du bracelet 1
    float speed3f = abs(boardsStruct[2].gx)+abs(boardsStruct[2].gy)+abs(boardsStruct[2].gz);
    if(speed3f < 1){
      speed3f = 1;
    }
    int speed3 = speed3f;
    timerDelay3 = 70/sqrt(speed3);
    if(timerDelay3 < 5){
      timerDelay3 = 5;
    }
    //Vitesse de fade
    fadespeed3 = 2*speed3f*sqrt(speed3f);
    //Vitesse pattern 7
    timerDelay3_7 = 800/sqrt(speed3);

    if(OnDataReception[2]<5 && DanseNoInterrupt[2]>0){

      //PATTERN 1 ALLER INFINI
      if( timepattern1 >= DanseNoInterrupt[2])
      {
        // Déplacer le pixel
        currentPixel3 += direction3;
        // Changer la direction6 si on atteint le bord
        if (currentPixel3 == NUM_LEDS) {
          currentPixel3 = 0; // Revenir au début
        }
        // Allumer la LED actuelle
        leds3[currentPixel3].setRGB(255*abs(boardsStruct[2].x), 255*abs(boardsStruct[2].y), 255*abs(boardsStruct[2].z));
        FastLED.show();
      }


      //PATTERN 2 ALLER INFINI x2
      if( timepattern2 >= DanseNoInterrupt[2] && DanseNoInterrupt[2] > timepattern1){
        // Déplacer le pixel
        if(debut3 == true){
          if(currentPixel3 >30){
            currentPixel3_2 = currentPixel3 - 30;
          }
          if(currentPixel3 <= 30){
            currentPixel3_2 = currentPixel3 + 15;
          }
        }
        currentPixel3 += direction3;
        currentPixel3_2 += direction3;
        // Changer la direction6 si on atteint le bord
        if (currentPixel3 == NUM_LEDS) {
          currentPixel3 = 0; // Revenir au début
        }
        if (currentPixel3_2 == NUM_LEDS) {
          currentPixel3_2 = 0; // Revenir au début
        }
        // Allumer la LED actuelle
        leds3[currentPixel3].setRGB(255*abs(boardsStruct[2].x), 255*abs(boardsStruct[2].y), 255*abs(boardsStruct[2].z));
        leds3[currentPixel3_2].setRGB(255*abs(boardsStruct[2].x), 255*abs(boardsStruct[2].y), 255*abs(boardsStruct[2].z));
        FastLED.show();
        Serial.print(DanseNoInterrupt[2]);
        debut3 = false;
      }
      

      //PATTERN 3 ALLER INFINI x3
      if( timepattern3 >= DanseNoInterrupt[2] && DanseNoInterrupt[2] > timepattern2){
        // Déplacer le pixel
        if(debut3_3 == true){
          if(currentPixel3_2 >30){
            currentPixel3_3 = currentPixel3_2 - 30;
          }
          if(currentPixel3_2 <= 30){
            currentPixel3_3 = currentPixel3_2 + 15;
          }
        }
        currentPixel3 += direction3;
        currentPixel3_2 += direction3;
        currentPixel3_3 += direction3;
        // Changer la direction6 si on atteint le bord
        if (currentPixel3 == NUM_LEDS) {
          currentPixel3 = 0; // Revenir au début
        }
        if (currentPixel3_2 == NUM_LEDS) {
          currentPixel3_2 = 0; // Revenir au début
        }
        if (currentPixel3_3 == NUM_LEDS) {
          currentPixel3_3 = 0; // Revenir au début
        }
        // Allumer la LED actuelle
        leds3[currentPixel3].setRGB(255*abs(boardsStruct[2].x), 255*abs(boardsStruct[2].y), 255*abs(boardsStruct[2].z));
        leds3[currentPixel3_2].setRGB(255*abs(boardsStruct[2].x), 255*abs(boardsStruct[2].y), 255*abs(boardsStruct[2].z));
        leds3[currentPixel3_3].setRGB(255*abs(boardsStruct[2].x), 255*abs(boardsStruct[2].y), 255*abs(boardsStruct[2].z));
        FastLED.show();
        Serial.print(DanseNoInterrupt[2]);
        debut3_3 = false;
      }


      //PATTERN 4 ALLER RETOUR
      if(timepattern4 >= DanseNoInterrupt[2] && DanseNoInterrupt[2] > timepattern3){
        // Déplacer le pixel
        currentPixel3 += direction3;
        // Changer la direction6 si on atteint les bords
        if (currentPixel3 == NUM_LEDS || currentPixel3 == -1) {
          direction3 *= -1; // Changer de direction6
          currentPixel3 += direction3; // Ajuster pour éviter de déborder
        }
        // Allumer la LED actuelle
        leds3[currentPixel3].setRGB(255*abs(boardsStruct[2].x), 255*abs(boardsStruct[2].y), 255*abs(boardsStruct[2].z));
        FastLED.show();
      }


      //PATTERN 5 ALLER RETOUR x2
      if( timepattern5 >= DanseNoInterrupt[2] && DanseNoInterrupt[2] > timepattern4){
        // Déplacer le pixel
        if(debut3_5 == true){
          if(currentPixel3 >30){
            currentPixel3_2 = currentPixel3 - 30;
          }
          if(currentPixel3 <= 30){
            currentPixel3_2 = currentPixel3 + 15;
          }
        }
        currentPixel3 += direction3;
        currentPixel3_2 += direction3_2;
        // Changer la direction6 si on atteint le bord
        if (currentPixel3 == NUM_LEDS || currentPixel3 == -1) {
          direction3 *= -1; // Changer de direction6
          currentPixel3 += direction3; // Ajuster pour éviter de déborder
        }
        if (currentPixel3_2 == NUM_LEDS || currentPixel3_2 == -1) {
          direction3_2 *= -1; // Changer de direction6
          currentPixel3_2 += direction3_2; // Ajuster pour éviter de déborder
        }
        // Allumer la LED actuelle
        leds3[currentPixel3].setRGB(255*abs(boardsStruct[2].x), 255*abs(boardsStruct[2].y), 255*abs(boardsStruct[2].z));
        leds3[currentPixel3_2].setRGB(255*abs(boardsStruct[2].x), 255*abs(boardsStruct[2].y), 255*abs(boardsStruct[2].z));
        FastLED.show();
        Serial.print(DanseNoInterrupt[2]);
        debut3_5 = false;
      }

      //PATTERN 6 ALLER RETOUR x3
      if( timepattern6 >= DanseNoInterrupt[2] && DanseNoInterrupt[2] > timepattern5){
        // Déplacer le pixel
        if(debut3_6 == true){
          if(currentPixel3_2 >30){
            currentPixel3_3 = currentPixel3_2 - 30;
          }
          if(currentPixel3_2 <= 30){
            currentPixel3_3 = currentPixel3_2 + 15;
          }
        }
        currentPixel3 += direction3;
        currentPixel3_2 += direction3_2;
        currentPixel3_3 += direction3_3;
        // Changer la direction6 si on atteint le bord
        // Changer la direction6 si on atteint le bord
        if (currentPixel3 == NUM_LEDS || currentPixel3 == -1) {
          direction3 *= -1; // Changer de direction6
          currentPixel3 += direction3; // Ajuster pour éviter de déborder
        }
        if (currentPixel3_2 == NUM_LEDS || currentPixel3_2 == -1) {
          direction3_2 *= -1; // Changer de direction6
          currentPixel3_2 += direction3_2; // Ajuster pour éviter de déborder
        }
        if (currentPixel3_3 == NUM_LEDS || currentPixel3_3 == -1) {
          direction3_3 *= -1; // Changer de direction6
          currentPixel3_3 += direction3_3; // Ajuster pour éviter de déborder
        }
        // Allumer la LED actuelle
        leds3[currentPixel3].setRGB(255*abs(boardsStruct[2].x), 255*abs(boardsStruct[2].y), 255*abs(boardsStruct[2].z));
        leds3[currentPixel3_2].setRGB(255*abs(boardsStruct[2].x), 255*abs(boardsStruct[2].y), 255*abs(boardsStruct[2].z));
        leds3[currentPixel3_3].setRGB(255*abs(boardsStruct[2].x), 255*abs(boardsStruct[2].y), 255*abs(boardsStruct[2].z));
        FastLED.show();
        Serial.print(DanseNoInterrupt[2]);
        debut3_6 = false;
      }


      //PATTERN 7 Flash 1/3
      if(timepattern7 >= DanseNoInterrupt[2] && DanseNoInterrupt[2] > timepattern6){
        if((millis() - lastTime3_7) >= timerDelay3_7){
          int compteur3_7 = compteurpattern3_7 + 15;
          while( compteurpattern3_7 < compteur3_7){
            leds3[compteurpattern3_7].setRGB(255*abs(boardsStruct[2].x), 255*abs(boardsStruct[2].y), 255*abs(boardsStruct[2].z));;
            compteurpattern3_7++;
          }
          if(compteurpattern3_7 >= 45){
            compteurpattern3_7 = 0;
          }
          lastTime3_7 = millis();
        }
      }


      //PATTERN 8 Flash
      if(timepattern8 >= DanseNoInterrupt[2] && DanseNoInterrupt[2] > timepattern7){
        if((millis() - lastTime3_7) >= timerDelay3_7){
          while( compteurpattern3_7 < 45){
            leds3[compteurpattern3_7].setRGB(255*abs(boardsStruct[2].x), 255*abs(boardsStruct[2].y), 255*abs(boardsStruct[2].z));;
            compteurpattern3_7++;
          }
          compteurpattern3_7 = 0;
          lastTime3_7 = millis();
        }
      }
    }
  lastTime3 = millis();
  }
  fadeToBlackBy( leds3, NUM_LEDS, fadespeed3);
  FastLED.show();


//LUMIERE 4
  if((millis() - lastTime4) >= timerDelay4) {

    //Vitesse selon mouvement du bracelet 1
    float speed4f = abs(boardsStruct[3].gx)+abs(boardsStruct[3].gy)+abs(boardsStruct[3].gz);
    if(speed4f < 1){
      speed4f = 1;
    }
    int speed4 = speed4f;
    timerDelay4 = 70/sqrt(speed4);
    if(timerDelay4 < 5){
      timerDelay4 = 5;
    }
    //Vitesse de fade
    fadespeed4 = 2*speed4f*sqrt(speed4f);
    //Vitesse pattern 7
    timerDelay4_7 = 800/sqrt(speed4);

    if(OnDataReception[3]<5 && DanseNoInterrupt[3]>0){

      //PATTERN 1 ALLER INFINI
      if( timepattern1 >= DanseNoInterrupt[3])
      {
        // Déplacer le pixel
        currentPixel4 += direction4;
        // Changer la direction6 si on atteint le bord
        if (currentPixel4 == NUM_LEDS) {
          currentPixel4 = 0; // Revenir au début
        }
        // Allumer la LED actuelle
        leds4[currentPixel4].setRGB(255*abs(boardsStruct[3].x), 255*abs(boardsStruct[3].y), 255*abs(boardsStruct[3].z));
        FastLED.show();
      }


      //PATTERN 2 ALLER INFINI x2
      if( timepattern2 >= DanseNoInterrupt[3] && DanseNoInterrupt[3] > timepattern1){
        // Déplacer le pixel
        if(debut4 == true){
          if(currentPixel4 >30){
            currentPixel4_2 = currentPixel4 - 30;
          }
          if(currentPixel4 <= 30){
            currentPixel4_2 = currentPixel4 + 15;
          }
        }
        currentPixel4 += direction4;
        currentPixel4_2 += direction4;
        // Changer la direction6 si on atteint le bord
        if (currentPixel4 == NUM_LEDS) {
          currentPixel4 = 0; // Revenir au début
        }
        if (currentPixel4_2 == NUM_LEDS) {
          currentPixel4_2 = 0; // Revenir au début
        }
        // Allumer la LED actuelle
        leds4[currentPixel4].setRGB(255*abs(boardsStruct[3].x), 255*abs(boardsStruct[3].y), 255*abs(boardsStruct[3].z));
        leds4[currentPixel4_2].setRGB(255*abs(boardsStruct[3].x), 255*abs(boardsStruct[3].y), 255*abs(boardsStruct[3].z));
        FastLED.show();
        Serial.print(DanseNoInterrupt[3]);
        debut4 = false;
      }
      

      //PATTERN 3 ALLER INFINI x3
      if( timepattern3 >= DanseNoInterrupt[3] && DanseNoInterrupt[3] > timepattern2){
        // Déplacer le pixel
        if(debut4_3 == true){
          if(currentPixel4_2 >30){
            currentPixel4_3 = currentPixel4_2 - 30;
          }
          if(currentPixel4_2 <= 30){
            currentPixel4_3 = currentPixel4_2 + 15;
          }
        }
        currentPixel4 += direction4;
        currentPixel4_2 += direction4;
        currentPixel4_3 += direction4;
        // Changer la direction6 si on atteint le bord
        if (currentPixel4 == NUM_LEDS) {
          currentPixel4 = 0; // Revenir au début
        }
        if (currentPixel4_2 == NUM_LEDS) {
          currentPixel4_2 = 0; // Revenir au début
        }
        if (currentPixel4_3 == NUM_LEDS) {
          currentPixel4_3 = 0; // Revenir au début
        }
        // Allumer la LED actuelle
        leds4[currentPixel4].setRGB(255*abs(boardsStruct[3].x), 255*abs(boardsStruct[3].y), 255*abs(boardsStruct[3].z));
        leds4[currentPixel4_2].setRGB(255*abs(boardsStruct[3].x), 255*abs(boardsStruct[3].y), 255*abs(boardsStruct[3].z));
        leds4[currentPixel4_3].setRGB(255*abs(boardsStruct[3].x), 255*abs(boardsStruct[3].y), 255*abs(boardsStruct[3].z));
        FastLED.show();
        Serial.print(DanseNoInterrupt[3]);
        debut4_3 = false;
        
      }


      //PATTERN 4 ALLER RETOUR
      if(timepattern4 >= DanseNoInterrupt[3] && DanseNoInterrupt[3] > timepattern3){
        // Déplacer le pixel
        currentPixel4 += direction4;
        // Changer la direction6 si on atteint les bords
        if (currentPixel4 == NUM_LEDS || currentPixel4 == -1) {
          direction4 *= -1; // Changer de direction6
          currentPixel4 += direction4; // Ajuster pour éviter de déborder
        }
        // Allumer la LED actuelle
        leds4[currentPixel4].setRGB(255*abs(boardsStruct[3].x), 255*abs(boardsStruct[3].y), 255*abs(boardsStruct[3].z));
        FastLED.show();
      }


      //PATTERN 5 ALLER RETOUR x2
      if( timepattern5 >= DanseNoInterrupt[3] && DanseNoInterrupt[3] > timepattern4){
        // Déplacer le pixel
        if(debut4_5 == true){
          if(currentPixel4 >30){
            currentPixel4_2 = currentPixel4 - 30;
          }
          if(currentPixel4 <= 30){
            currentPixel4_2 = currentPixel4 + 15;
          }
        }
        currentPixel4 += direction4;
        currentPixel4_2 += direction4_2;
        // Changer la direction6 si on atteint le bord
        if (currentPixel4 == NUM_LEDS || currentPixel4 == -1) {
          direction4 *= -1; // Changer de direction6
          currentPixel4 += direction4; // Ajuster pour éviter de déborder
        }
        if (currentPixel4_2 == NUM_LEDS || currentPixel4_2 == -1) {
          direction4_2 *= -1; // Changer de direction6
          currentPixel4_2 += direction4_2; // Ajuster pour éviter de déborder
        }
        // Allumer la LED actuelle
        leds4[currentPixel4].setRGB(255*abs(boardsStruct[3].x), 255*abs(boardsStruct[3].y), 255*abs(boardsStruct[3].z));
        leds4[currentPixel4_2].setRGB(255*abs(boardsStruct[3].x), 255*abs(boardsStruct[3].y), 255*abs(boardsStruct[3].z));
        FastLED.show();
        Serial.print(DanseNoInterrupt[3]);
        debut4_5 = false;
      }

      //PATTERN 6 ALLER RETOUR x3
      if( timepattern6 >= DanseNoInterrupt[3] && DanseNoInterrupt[3] > timepattern5){
        // Déplacer le pixel
        if(debut4_6 == true){
          if(currentPixel4_2 >30){
            currentPixel4_3 = currentPixel4_2 - 30;
          }
          if(currentPixel4_2 <= 30){
            currentPixel4_3 = currentPixel4_2 + 15;
          }
        }
        currentPixel4 += direction4;
        currentPixel4_2 += direction4_2;
        currentPixel4_3 += direction4_3;
        // Changer la direction6 si on atteint le bord
        // Changer la direction6 si on atteint le bord
        if (currentPixel4 == NUM_LEDS || currentPixel4 == -1) {
          direction4 *= -1; // Changer de direction6
          currentPixel4 += direction4; // Ajuster pour éviter de déborder
        }
        if (currentPixel4_2 == NUM_LEDS || currentPixel4_2 == -1) {
          direction4_2 *= -1; // Changer de direction6
          currentPixel4_2 += direction4_2; // Ajuster pour éviter de déborder
        }
        if (currentPixel4_3 == NUM_LEDS || currentPixel4_3 == -1) {
          direction4_3 *= -1; // Changer de direction6
          currentPixel4_3 += direction4_3; // Ajuster pour éviter de déborder
        }
        // Allumer la LED actuelle
        leds4[currentPixel4].setRGB(255*abs(boardsStruct[3].x), 255*abs(boardsStruct[3].y), 255*abs(boardsStruct[3].z));
        leds4[currentPixel4_2].setRGB(255*abs(boardsStruct[3].x), 255*abs(boardsStruct[3].y), 255*abs(boardsStruct[3].z));
        leds4[currentPixel4_3].setRGB(255*abs(boardsStruct[3].x), 255*abs(boardsStruct[3].y), 255*abs(boardsStruct[3].z));
        FastLED.show();
        Serial.print(DanseNoInterrupt[3]);
        debut4_6 = false;
      }


      //PATTERN 7 Flash 1/3
      if(timepattern7 >= DanseNoInterrupt[3] && DanseNoInterrupt[3] > timepattern6){
        if((millis() - lastTime4_7) >= timerDelay4_7){
          int compteur4_7 = compteurpattern4_7 + 15;
          while( compteurpattern4_7 < compteur4_7){
            leds4[compteurpattern4_7].setRGB(255*abs(boardsStruct[3].x), 255*abs(boardsStruct[3].y), 255*abs(boardsStruct[3].z));;
            compteurpattern4_7++;
          }
          if(compteurpattern4_7 >= 45){
            compteurpattern4_7 = 0;
          }
          lastTime4_7 = millis();
        }
      }


      //PATTERN 8 Flash
      if(timepattern8 >= DanseNoInterrupt[3] && DanseNoInterrupt[3] > timepattern7){
        if((millis() - lastTime4_7) >= timerDelay4_7){
          while( compteurpattern4_7 < 45){
            leds4[compteurpattern4_7].setRGB(255*abs(boardsStruct[3].x), 255*abs(boardsStruct[3].y), 255*abs(boardsStruct[3].z));;
            compteurpattern4_7++;
          }
          compteurpattern4_7 = 0;
          lastTime4_7 = millis();
        }
      }
    }
  lastTime4 = millis();
  }
  fadeToBlackBy( leds4, NUM_LEDS, fadespeed4);
  FastLED.show();


//LUMIERE 5
  if ((millis() - lastTime5) >= timerDelay5) {

    //Vitesse selon mouvement du bracelet 1
    float speed5f = abs(boardsStruct[4].gx) + abs(boardsStruct[4].gy) + abs(boardsStruct[4].gz);
    if (speed5f < 1) {
      speed5f = 1;
    }
    int speed5 = speed5f;
    timerDelay5 = 70 / sqrt(speed5);
    if (timerDelay5 < 5) {
      timerDelay5 = 5;
    }
    //Vitesse de fade
    fadespeed5 = 2*speed5f*sqrt(speed5f);
    //Vitesse pattern 7
    timerDelay5_7 = 800 / sqrt(speed5);

    if (OnDataReception[4] < 5 && DanseNoInterrupt[4] > 0) {

      //PATTERN 1 ALLER INFINI
      if (timepattern1 >= DanseNoInterrupt[4]) {
        // Déplacer le pixel
        currentPixel5 += direction5;
        // Changer la direction6 si on atteint le bord
        if (currentPixel5 == NUM_LEDS) {
          currentPixel5 = 0;  // Revenir au début
        }
        // Allumer la LED actuelle
        leds5[currentPixel5].setRGB(255 * abs(boardsStruct[4].x), 255 * abs(boardsStruct[4].y), 255 * abs(boardsStruct[4].z));
        FastLED.show();
      }


      //PATTERN 2 ALLER INFINI x2
      if (timepattern2 >= DanseNoInterrupt[4] && DanseNoInterrupt[4] > timepattern1) {
        // Déplacer le pixel
        if (debut5 == true) {
          if (currentPixel5 > 30) {
            currentPixel5_2 = currentPixel5 - 30;
          }
          if (currentPixel5 <= 30) {
            currentPixel5_2 = currentPixel5 + 15;
          }
        }
        currentPixel5 += direction5;
        currentPixel5_2 += direction5;
        // Changer la direction6 si on atteint le bord
        if (currentPixel5 == NUM_LEDS) {
          currentPixel5 = 0;  // Revenir au début
        }
        if (currentPixel5_2 == NUM_LEDS) {
          currentPixel5_2 = 0;  // Revenir au début
        }
        // Allumer la LED actuelle
        leds5[currentPixel5].setRGB(255 * abs(boardsStruct[4].x), 255 * abs(boardsStruct[4].y), 255 * abs(boardsStruct[4].z));
        leds5[currentPixel5_2].setRGB(255 * abs(boardsStruct[4].x), 255 * abs(boardsStruct[4].y), 255 * abs(boardsStruct[4].z));
        FastLED.show();
        Serial.print(DanseNoInterrupt[4]);
        debut5 = false;
      }


      //PATTERN 3 ALLER INFINI x3
      if (timepattern3 >= DanseNoInterrupt[4] && DanseNoInterrupt[4] > timepattern2) {
        // Déplacer le pixel
        if (debut5_3 == true) {
          if (currentPixel5_2 > 30) {
            currentPixel5_3 = currentPixel5_2 - 30;
          }
          if (currentPixel5_2 <= 30) {
            currentPixel5_3 = currentPixel5_2 + 15;
          }
        }
        currentPixel5 += direction5;
        currentPixel5_2 += direction5;
        currentPixel5_3 += direction5;
        // Changer la direction6 si on atteint le bord
        if (currentPixel5 == NUM_LEDS) {
          currentPixel5 = 0;  // Revenir au début
        }
        if (currentPixel5_2 == NUM_LEDS) {
          currentPixel5_2 = 0;  // Revenir au début
        }
        if (currentPixel5_3 == NUM_LEDS) {
          currentPixel5_3 = 0;  // Revenir au début
        }
        // Allumer la LED actuelle
        leds5[currentPixel5].setRGB(255 * abs(boardsStruct[4].x), 255 * abs(boardsStruct[4].y), 255 * abs(boardsStruct[4].z));
        leds5[currentPixel5_2].setRGB(255 * abs(boardsStruct[4].x), 255 * abs(boardsStruct[4].y), 255 * abs(boardsStruct[4].z));
        leds5[currentPixel5_3].setRGB(255 * abs(boardsStruct[4].x), 255 * abs(boardsStruct[4].y), 255 * abs(boardsStruct[4].z));
        FastLED.show();
        Serial.print(DanseNoInterrupt[4]);
        debut5_3 = false;
      }


      //PATTERN 4 ALLER RETOUR
      if (timepattern4 >= DanseNoInterrupt[4] && DanseNoInterrupt[4] > timepattern3) {
        // Déplacer le pixel
        currentPixel5 += direction5;
        // Changer la direction6 si on atteint les bords
        if (currentPixel5 == NUM_LEDS || currentPixel5 == -1) {
          direction5 *= -1;             // Changer de direction6
          currentPixel5 += direction5;  // Ajuster pour éviter de déborder
        }
        // Allumer la LED actuelle
        leds5[currentPixel5].setRGB(255 * abs(boardsStruct[4].x), 255 * abs(boardsStruct[4].y), 255 * abs(boardsStruct[4].z));
        FastLED.show();
      }


      //PATTERN 5 ALLER RETOUR x2
      if (timepattern5 >= DanseNoInterrupt[4] && DanseNoInterrupt[4] > timepattern4) {
        // Déplacer le pixel
        if (debut5_5 == true) {
          if (currentPixel5 > 30) {
            currentPixel5_2 = currentPixel5 - 30;
          }
          if (currentPixel5 <= 30) {
            currentPixel5_2 = currentPixel5 + 15;
          }
        }
        currentPixel5 += direction5;
        currentPixel5_2 += direction5_2;
        // Changer la direction6 si on atteint le bord
        if (currentPixel5 == NUM_LEDS || currentPixel5 == -1) {
          direction5 *= -1;             // Changer de direction6
          currentPixel5 += direction5;  // Ajuster pour éviter de déborder
        }
        if (currentPixel5_2 == NUM_LEDS || currentPixel5_2 == -1) {
          direction5_2 *= -1;               // Changer de direction6
          currentPixel5_2 += direction5_2;  // Ajuster pour éviter de déborder
        }
        // Allumer la LED actuelle
        leds5[currentPixel5].setRGB(255 * abs(boardsStruct[4].x), 255 * abs(boardsStruct[4].y), 255 * abs(boardsStruct[4].z));
        leds5[currentPixel5_2].setRGB(255 * abs(boardsStruct[4].x), 255 * abs(boardsStruct[4].y), 255 * abs(boardsStruct[4].z));
        FastLED.show();
        Serial.print(DanseNoInterrupt[4]);
        debut5_5 = false;
      }

      //PATTERN 6 ALLER RETOUR x3
      if (timepattern6 >= DanseNoInterrupt[4] && DanseNoInterrupt[4] > timepattern5) {
        // Déplacer le pixel
        if (debut5_6 == true) {
          if (currentPixel5_2 > 30) {
            currentPixel5_3 = currentPixel5_2 - 30;
          }
          if (currentPixel5_2 <= 30) {
            currentPixel5_3 = currentPixel5_2 + 15;
          }
        }
        currentPixel5 += direction5;
        currentPixel5_2 += direction5_2;
        currentPixel5_3 += direction5_3;
        // Changer la direction6 si on atteint le bord
        // Changer la direction6 si on atteint le bord
        if (currentPixel5 == NUM_LEDS || currentPixel5 == -1) {
          direction5 *= -1;             // Changer de direction6
          currentPixel5 += direction5;  // Ajuster pour éviter de déborder
        }
        if (currentPixel5_2 == NUM_LEDS || currentPixel5_2 == -1) {
          direction5_2 *= -1;               // Changer de direction6
          currentPixel5_2 += direction5_2;  // Ajuster pour éviter de déborder
        }
        if (currentPixel5_3 == NUM_LEDS || currentPixel5_3 == -1) {
          direction5_3 *= -1;               // Changer de direction6
          currentPixel5_3 += direction5_3;  // Ajuster pour éviter de déborder
        }
        // Allumer la LED actuelle
        leds5[currentPixel5].setRGB(255 * abs(boardsStruct[4].x), 255 * abs(boardsStruct[4].y), 255 * abs(boardsStruct[4].z));
        leds5[currentPixel5_2].setRGB(255 * abs(boardsStruct[4].x), 255 * abs(boardsStruct[4].y), 255 * abs(boardsStruct[4].z));
        leds5[currentPixel5_3].setRGB(255 * abs(boardsStruct[4].x), 255 * abs(boardsStruct[4].y), 255 * abs(boardsStruct[4].z));
        FastLED.show();
        Serial.print(DanseNoInterrupt[4]);
        debut5_6 = false;
      }


      //PATTERN 7 Flash 1/3
      if (timepattern7 >= DanseNoInterrupt[4] && DanseNoInterrupt[4] > timepattern6) {
        if ((millis() - lastTime5_7) >= timerDelay5_7) {
          int compteur5_7 = compteurpattern5_7 + 15;
          while (compteurpattern5_7 < compteur5_7) {
            leds5[compteurpattern5_7].setRGB(255 * abs(boardsStruct[4].x), 255 * abs(boardsStruct[4].y), 255 * abs(boardsStruct[4].z));
            ;
            compteurpattern5_7++;
          }
          if (compteurpattern5_7 >= 45) {
            compteurpattern5_7 = 0;
          }
          lastTime5_7 = millis();
        }
      }


      //PATTERN 8 Flash
      if (timepattern8 >= DanseNoInterrupt[4] && DanseNoInterrupt[4] > timepattern7) {
        if ((millis() - lastTime5_7) >= timerDelay5_7) {
          while (compteurpattern5_7 < 45) {
            leds5[compteurpattern5_7].setRGB(255 * abs(boardsStruct[4].x), 255 * abs(boardsStruct[4].y), 255 * abs(boardsStruct[4].z));
            compteurpattern5_7++;
          }
          compteurpattern5_7 = 0;
          lastTime5_7 = millis();
        }
      }
    }
    lastTime5 = millis();
  }
  fadeToBlackBy( leds5, NUM_LEDS, fadespeed5);
  FastLED.show();


//LUMIERE 6
  if((millis() - lastTime6) >= timerDelay6) {

    //Vitesse selon mouvement du bracelet 6
    float speed6f = abs(boardsStruct[5].gx)+abs(boardsStruct[5].gy)+abs(boardsStruct[5].gz);
    if(speed6f < 1){
      speed6f = 1;
    }
    int speed6 = speed6f;
    timerDelay6 = 70/sqrt(speed6);
    if(timerDelay6 < 5){
      timerDelay6 = 5;
    }
    //Vitesse de fade
    fadespeed6 = 2*speed6f*sqrt(speed6f);
    //Vitesse pattern 7
    timerDelay6_7 = 800/sqrt(speed6);

    if(OnDataReception[5]<5 && DanseNoInterrupt[5]>0){

      //PATTERN 1 ALLER INFINI
      if( timepattern1 >= DanseNoInterrupt[5])
      {
        // Déplacer le pixel
        currentPixel6 += direction6;
        // Changer la direction6 si on atteint le bord
        if (currentPixel6 == NUM_LEDS) {
          currentPixel6 = 0; // Revenir au début
        }
        // Allumer la LED actuelle
        leds6[currentPixel6].setRGB(255*abs(boardsStruct[5].x), 255*abs(boardsStruct[5].y), 255*abs(boardsStruct[5].z));
        FastLED.show();
      }


      //PATTERN 2 ALLER INFINI x2
      if( timepattern2 >= DanseNoInterrupt[5] && DanseNoInterrupt[5] > timepattern1){
        // Déplacer le pixel
        if(debut6 == true){
          if(currentPixel6 >30){
            currentPixel6_2 = currentPixel6 - 30;
          }
          if(currentPixel6 <= 30){
            currentPixel6_2 = currentPixel6 + 15;
          }
        }
        currentPixel6 += direction6;
        currentPixel6_2 += direction6;
        // Changer la direction6 si on atteint le bord
        if (currentPixel6 == NUM_LEDS) {
          currentPixel6 = 0; // Revenir au début
        }
        if (currentPixel6_2 == NUM_LEDS) {
          currentPixel6_2 = 0; // Revenir au début
        }
        // Allumer la LED actuelle
        leds6[currentPixel6].setRGB(255*abs(boardsStruct[5].x), 255*abs(boardsStruct[5].y), 255*abs(boardsStruct[5].z));
        leds6[currentPixel6_2].setRGB(255*abs(boardsStruct[5].x), 255*abs(boardsStruct[5].y), 255*abs(boardsStruct[5].z));
        FastLED.show();
        Serial.print(DanseNoInterrupt[5]);
        debut6 = false;
      }
      

      //PATTERN 3 ALLER INFINI x3
      if( timepattern3 >= DanseNoInterrupt[5] && DanseNoInterrupt[5] > timepattern2){
        // Déplacer le pixel
        if(debut6_3 == true){
          if(currentPixel6_2 >30){
            currentPixel6_3 = currentPixel6_2 - 30;
          }
          if(currentPixel6_2 <= 30){
            currentPixel6_3 = currentPixel6_2 + 15;
          }
        }
        currentPixel6 += direction6;
        currentPixel6_2 += direction6;
        currentPixel6_3 += direction6;
        // Changer la direction6 si on atteint le bord
        if (currentPixel6 == NUM_LEDS) {
          currentPixel6 = 0; // Revenir au début
        }
        if (currentPixel6_2 == NUM_LEDS) {
          currentPixel6_2 = 0; // Revenir au début
        }
        if (currentPixel6_3 == NUM_LEDS) {
          currentPixel6_3 = 0; // Revenir au début
        }
        // Allumer la LED actuelle
        leds6[currentPixel6].setRGB(255*abs(boardsStruct[5].x), 255*abs(boardsStruct[5].y), 255*abs(boardsStruct[5].z));
        leds6[currentPixel6_2].setRGB(255*abs(boardsStruct[5].x), 255*abs(boardsStruct[5].y), 255*abs(boardsStruct[5].z));
        leds6[currentPixel6_3].setRGB(255*abs(boardsStruct[5].x), 255*abs(boardsStruct[5].y), 255*abs(boardsStruct[5].z));
        FastLED.show();
        Serial.print(DanseNoInterrupt[5]);
        debut6_3 = false;
      }


      //PATTERN 4 ALLER RETOUR
      if(timepattern4 >= DanseNoInterrupt[5] && DanseNoInterrupt[5] > timepattern3){
        // Déplacer le pixel
        currentPixel6 += direction6;
        // Changer la direction6 si on atteint les bords
        if (currentPixel6 == NUM_LEDS || currentPixel6 == -1) {
          direction6 *= -1; // Changer de direction6
          currentPixel6 += direction6; // Ajuster pour éviter de déborder
        }
        // Allumer la LED actuelle
        leds6[currentPixel6].setRGB(255*abs(boardsStruct[5].x), 255*abs(boardsStruct[5].y), 255*abs(boardsStruct[5].z));
        FastLED.show();
      }


      //PATTERN 5 ALLER RETOUR x2
      if( timepattern5 >= DanseNoInterrupt[5] && DanseNoInterrupt[5] > timepattern4){
        // Déplacer le pixel
        if(debut6_5 == true){
          if(currentPixel6 >30){
            currentPixel6_2 = currentPixel6 - 30;
          }
          if(currentPixel6 <= 30){
            currentPixel6_2 = currentPixel6 + 15;
          }
        }
        currentPixel6 += direction6;
        currentPixel6_2 += direction6_2;
        // Changer la direction6 si on atteint le bord
        if (currentPixel6 == NUM_LEDS || currentPixel6 == -1) {
          direction6 *= -1; // Changer de direction6
          currentPixel6 += direction6; // Ajuster pour éviter de déborder
        }
        if (currentPixel6_2 == NUM_LEDS || currentPixel6_2 == -1) {
          direction6_2 *= -1; // Changer de direction6
          currentPixel6_2 += direction6_2; // Ajuster pour éviter de déborder
        }
        // Allumer la LED actuelle
        leds6[currentPixel6].setRGB(255*abs(boardsStruct[5].x), 255*abs(boardsStruct[5].y), 255*abs(boardsStruct[5].z));
        leds6[currentPixel6_2].setRGB(255*abs(boardsStruct[5].x), 255*abs(boardsStruct[5].y), 255*abs(boardsStruct[5].z));
        FastLED.show();
        Serial.print(DanseNoInterrupt[5]);
        debut6_5 = false;
      }

      //PATTERN 6 ALLER RETOUR x3
      if( timepattern6 >= DanseNoInterrupt[5] && DanseNoInterrupt[5] > timepattern5){
        // Déplacer le pixel
        if(debut6_6 == true){
          if(currentPixel6_2 >30){
            currentPixel6_3 = currentPixel6_2 - 30;
          }
          if(currentPixel6_2 <= 30){
            currentPixel6_3 = currentPixel6_2 + 15;
          }
        }
        currentPixel6 += direction6;
        currentPixel6_2 += direction6_2;
        currentPixel6_3 += direction6_3;
        // Changer la direction6 si on atteint le bord
        // Changer la direction6 si on atteint le bord
        if (currentPixel6 == NUM_LEDS || currentPixel6 == -1) {
          direction6 *= -1; // Changer de direction6
          currentPixel6 += direction6; // Ajuster pour éviter de déborder
        }
        if (currentPixel6_2 == NUM_LEDS || currentPixel6_2 == -1) {
          direction6_2 *= -1; // Changer de direction6
          currentPixel6_2 += direction6_2; // Ajuster pour éviter de déborder
        }
        if (currentPixel6_3 == NUM_LEDS || currentPixel6_3 == -1) {
          direction6_3 *= -1; // Changer de direction6
          currentPixel6_3 += direction6_3; // Ajuster pour éviter de déborder
        }
        // Allumer la LED actuelle
        leds6[currentPixel6].setRGB(255*abs(boardsStruct[5].x), 255*abs(boardsStruct[5].y), 255*abs(boardsStruct[5].z));
        leds6[currentPixel6_2].setRGB(255*abs(boardsStruct[5].x), 255*abs(boardsStruct[5].y), 255*abs(boardsStruct[5].z));
        leds6[currentPixel6_3].setRGB(255*abs(boardsStruct[5].x), 255*abs(boardsStruct[5].y), 255*abs(boardsStruct[5].z));
        FastLED.show();
        Serial.print(DanseNoInterrupt[5]);
        debut6_6 = false;
      }


      //PATTERN 7 Flash 1/3
      if(timepattern7 >= DanseNoInterrupt[5] && DanseNoInterrupt[5] > timepattern6){
        if((millis() - lastTime6_7) >= timerDelay6_7){
          int compteur6_7 = compteurpattern6_7 + 15;
          while( compteurpattern6_7 < compteur6_7){
            leds6[compteurpattern6_7].setRGB(255*abs(boardsStruct[5].x), 255*abs(boardsStruct[5].y), 255*abs(boardsStruct[5].z));;
            compteurpattern6_7++;
          }
          if(compteurpattern6_7 >= 45){
            compteurpattern6_7 = 0;
          }
          lastTime6_7 = millis();
        }
      }


      //PATTERN 8 Flash
      if(timepattern8 >= DanseNoInterrupt[5] && DanseNoInterrupt[5] > timepattern7){
        if((millis() - lastTime6_7) >= timerDelay6_7){
          while( compteurpattern6_7 < 45){
            leds6[compteurpattern6_7].setRGB(255*abs(boardsStruct[5].x), 255*abs(boardsStruct[5].y), 255*abs(boardsStruct[5].z));;
            compteurpattern6_7++;
          }
          compteurpattern6_7 = 0;
          lastTime6_7 = millis();
        }
      }
    }
  lastTime6 = millis();
  }
  fadeToBlackBy( leds6, NUM_LEDS, fadespeed6);
  FastLED.show();


  int NombreBracelet = 0;
  for(int i =0; i <= 5; i++){
    if(OnDataReception[i] < 5){
      OnDataRecep[i]=1;
      NombreBracelet++;
    }
    else{
      OnDataRecep[i]=0;
    }
  }
  timepattern1 = 1000/NombreBracelet;
  timepattern2 = 2000/NombreBracelet;
  timepattern3 = 3000/NombreBracelet;
  timepattern4 = 4000/NombreBracelet;
  timepattern5 = 5000/NombreBracelet;
  timepattern6 = 6000/NombreBracelet;
  timepattern7 = 7000/NombreBracelet;
  timepattern8 = 8000/NombreBracelet;

}
