#include <esp_now.h>
#include <WiFi.h>
#include <ESP32Servo.h>

// --- HOTSPOT CONFIGURATION ---
const char* ap_ssid = "ESP32_RC_Car";
const char* ap_password = "Password123";

// --- PIN CONFIGURATION (Perfect Match to Your Layout) ---
#define SERVO_PIN 18      
#define RPWM_PIN 25      
#define LPWM_PIN 26      
#define R_EN_PIN 27 
#define L_EN_PIN 14

#define CONV_RPWM_PIN 4    
#define CONV_LPWM_PIN 16   
#define CONV_R_EN_PIN 17   
#define CONV_L_EN_PIN 5    

// --- STATUS LED INDICATOR PINS ---
#define NEUTRAL_LED_PIN 2   
#define CENTER_LED_PIN 15   

Servo steeringServo;

typedef struct struct_message {
    int drive; 
    int steer; 
    int bsrButton; 
} struct_message;

struct_message incomingData;
bool newDataAvailable = false; 

String lastDriveState = "";
String lastSteerState = "";

// --- PROTECTION & RAMPING VARIABLES ---
int currentSpeedRPWM = 0;   
int currentSpeedLPWM = 0;   
const int RAMPING_STEP = 5; 

void OnDataRecv(const esp_now_recv_info *info, const uint8_t *incomingDataPtr, int len) {
    memcpy(&incomingData, incomingDataPtr, sizeof(incomingData));
    newDataAvailable = true; 
}

void setup() {
    Serial.begin(115200);
    delay(2000);

    WiFi.mode(WIFI_AP);
    WiFi.softAP(ap_ssid, ap_password);

    Serial.println("\n------------------------------------------------");
    Serial.println("--- SYSTEM ONLINE: FORWARD DIRECTION FIXED ---");
    Serial.println("------------------------------------------------");

    pinMode(NEUTRAL_LED_PIN, OUTPUT);
    pinMode(CENTER_LED_PIN, OUTPUT);
    digitalWrite(NEUTRAL_LED_PIN, HIGH); 
    digitalWrite(CENTER_LED_PIN, HIGH);  

    ESP32PWM::allocateTimer(0);
    steeringServo.setPeriodHertz(50);
    steeringServo.attach(SERVO_PIN, 500, 2400);

    pinMode(RPWM_PIN, OUTPUT); pinMode(LPWM_PIN, OUTPUT);
    pinMode(R_EN_PIN, OUTPUT); pinMode(L_EN_PIN, OUTPUT);
    digitalWrite(R_EN_PIN, HIGH); digitalWrite(L_EN_PIN, HIGH);

    pinMode(CONV_RPWM_PIN, OUTPUT); pinMode(CONV_LPWM_PIN, OUTPUT);
    pinMode(CONV_R_EN_PIN, OUTPUT); pinMode(CONV_L_EN_PIN, OUTPUT);
    digitalWrite(CONV_R_EN_PIN, HIGH); digitalWrite(CONV_L_EN_PIN, HIGH);

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
    if (newDataAvailable) {
        newDataAvailable = false; 

        // 1. STEERING LOGIC & LED DIRECTION INDICATOR
        int steerValue = incomingData.steer;
        int servoAngle = 90; 
        
        if (steerValue > 2500) {
            servoAngle = map(steerValue, 2500, 4095, 90, 135);
            digitalWrite(CENTER_LED_PIN, LOW);   
        } else if (steerValue < 1500) {
            servoAngle = map(steerValue, 1500, 0, 90, 45);
            digitalWrite(CENTER_LED_PIN, LOW);   
        } else {
            servoAngle = 90;
            digitalWrite(CENTER_LED_PIN, HIGH);  
        }
        steeringServo.write(servoAngle);

        // 2. MAIN REAR DRIVE (FIXED DIRECTION LOGIC)
        int motorValue = incomingData.drive;
        int targetSpeedRPWM = 0;
        int targetSpeedLPWM = 0;

        if (motorValue > 2500) { 
            // Forward Engine
            targetSpeedRPWM = map(motorValue, 2500, 4095, 0, 226); 
            targetSpeedLPWM = 0; 
            digitalWrite(NEUTRAL_LED_PIN, LOW);  
        } else if (motorValue < 1500) { 
            // Backward Engine
            targetSpeedRPWM = 0; 
            targetSpeedLPWM = map(motorValue, 1500, 0, 0, 226);
            digitalWrite(NEUTRAL_LED_PIN, LOW);  
        } else {
            // Neutral Engine
            targetSpeedRPWM = 0;
            targetSpeedLPWM = 0;
            digitalWrite(NEUTRAL_LED_PIN, HIGH); 
        }

        // Software Ramping Engine (Soft Start / Soft Shifting)
        if (currentSpeedRPWM < targetSpeedRPWM) currentSpeedRPWM += RAMPING_STEP;
        else if (currentSpeedRPWM > targetSpeedRPWM) currentSpeedRPWM -= RAMPING_STEP;

        if (currentSpeedLPWM < targetSpeedLPWM) currentSpeedLPWM += RAMPING_STEP;
        else if (currentSpeedLPWM > targetSpeedLPWM) currentSpeedLPWM -= RAMPING_STEP;

        analogWrite(RPWM_PIN, currentSpeedRPWM);
        analogWrite(LPWM_PIN, currentSpeedLPWM);

        // 3. CONVEYOR LOGIC
        if (incomingData.bsrButton == LOW) { 
            analogWrite(CONV_RPWM_PIN, 255); 
            analogWrite(CONV_LPWM_PIN, 0);
        } else {
            analogWrite(CONV_RPWM_PIN, 0);   
            analogWrite(CONV_LPWM_PIN, 0);
        }

        // 4. CLEAN CONSOLE LOGGING
        String currentDriveState = "NEUTRAL";
        String currentSteerState = "CENTER";
        if (motorValue > 2500) currentDriveState = "FORWARD";
        else if (motorValue < 1500) currentDriveState = "BACKWARD";
        if (steerValue > 2500) currentSteerState = "RIGHT";
        else if (steerValue < 1500) currentSteerState = "LEFT";

        if (currentDriveState != lastDriveState || currentSteerState != lastSteerState) {
            Serial.print("Received: [ "); Serial.print(currentDriveState);
            Serial.print(" ] -- [ "); Serial.print(currentSteerState);
            Serial.print(" ] -- Conveyor: ");
            Serial.println(incomingData.bsrButton == LOW ? "[ ON ]" : "[ OFF ]");
            lastDriveState = currentDriveState;
            lastSteerState = currentSteerState;
        }
    }
    delay(10); 
}