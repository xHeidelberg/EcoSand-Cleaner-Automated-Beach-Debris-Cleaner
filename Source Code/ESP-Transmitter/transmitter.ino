#include <esp_now.h>
#include <WiFi.h>

// MAC ADDRESS of Receiver
uint8_t broadcastAddress[] = {0xF4, 0x2D, 0xC9, 0x71, 0xBF, 0x51};

typedef struct struct_message {
    int drive;     
    int steer;    
    int bsrButton;
} struct_message;

struct_message myData;
esp_now_peer_info_t peerInfo;

String lastDriveState = "";
String lastSteerState = "";

void OnDataSent(const wifi_tx_info_t *info, esp_now_send_status_t status) {
}

void setup() {
    Serial.begin(115200);

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_register_send_cb(OnDataSent);
    
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 1;  
    peerInfo.encrypt = false;
    
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }

    pinMode(35, INPUT);        // VRx is on Pin 35
    pinMode(34, INPUT);        // VRy is on Pin 34
    pinMode(32, INPUT_PULLUP); // SW is on Pin 32

    Serial.println("--- Transmitter Ready! Custom Pin Mapping Active ---");
}

void loop() {
    // VRy (Pin 34) controls Drive (Forward/Backward)
    // VRx (Pin 35) controls Steer (Left/Right)
    myData.drive = analogRead(34); 
    myData.steer = analogRead(35);
    myData.bsrButton = digitalRead(32);
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    String currentDriveState = "NEUTRAL";
    String currentSteerState = "CENTER";
    if (myData.drive > 2500) {
        currentDriveState = "FORWARD";
    } else if (myData.drive < 1500) {
        currentDriveState = "BACKWARD";
    }

    if (myData.steer > 2500) {
        currentSteerState = "RIGHT";
    } else if (myData.steer < 1500) {
        currentSteerState = "LEFT";
    }

    if (currentDriveState != lastDriveState || currentSteerState != lastSteerState) {
        Serial.print("Action: [ ");
        Serial.print(currentDriveState);
        Serial.print(" ] -- [ ");
        Serial.print(currentSteerState);
        Serial.println(" ]");
        
        lastDriveState = currentDriveState;
        lastSteerState = currentSteerState;
    }

    delay(20); 
}