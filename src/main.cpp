#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

/*
typedef struct message {
    char text[32];
    int intVal;
    float floatVal;
} message;

message myMessage;
*/

typedef struct traffic_light_states {
    int id;        //   
    int delay;     // in miliseconds
} traffic_light_states;

// set pin numbers
const int ledRed = 0;       // the red LED pin
const int ledOrange =  1;   // the orange LED pin
const int ledGreen =  2;    // the green LED pin
const int switchMS = 3;     // master/slave input

// declare the array of states
traffic_light_states current_state;


// void messageReceived(const esp_now_recv_info *info, const uint8_t* incomingData, int len){
void messageReceived(const uint8_t* macAddr, const uint8_t* incomingData, int len){
    memcpy(&current_state, incomingData, sizeof(current_state));
    Serial.print("ID: ");
    Serial.println(current_state.id);
    Serial.print("Delay: ");
    Serial.println(current_state.delay);
    Serial.println();
}

void setup(){
    Serial.begin(115200);
    // delay(1000); // uncomment if your serial monitor is empty
    WiFi.mode(WIFI_STA);
    
    // configure LED outputs
    pinMode(ledRed, OUTPUT);
    pinMode(ledOrange, OUTPUT);
    pinMode(ledGreen, OUTPUT);

    // configure master/slave switch input
    // LOW: master (same decoding as transmitter), HIGH: slave (default)
    pinMode(switchMS, INPUT_PULLUP);

    // initialize the prim. traffic light
    digitalWrite(ledRed, LOW);
    digitalWrite(ledOrange, LOW);
    digitalWrite(ledGreen, LOW);

    if (esp_now_init() == ESP_OK) {
        Serial.println("ESPNow Init success");
    }
    else {
        Serial.println("ESPNow Init fail");
        return;
    }

    esp_now_register_recv_cb(messageReceived);
}
 
void loop(){
    // master, same as transmitter
    if (digitalRead(switchMS) == LOW) {
        switch (current_state.id) {
            case 0:
                /* A: red, B: green */
                digitalWrite(ledRed, HIGH);
                digitalWrite(ledOrange, LOW);
                digitalWrite(ledGreen, LOW);
                break;
            case 1:
                digitalWrite(ledRed, HIGH);
                digitalWrite(ledOrange, LOW);
                digitalWrite(ledGreen, LOW);
                break;

            case 2: 
                digitalWrite(ledRed, HIGH);
                digitalWrite(ledOrange, LOW);
                digitalWrite(ledGreen, LOW);
                break;

            case 3: 
                digitalWrite(ledRed, HIGH);
                digitalWrite(ledOrange, HIGH);
                digitalWrite(ledGreen, LOW);
                break;

            case 4:
                digitalWrite(ledRed, LOW);
                digitalWrite(ledOrange, LOW);
                digitalWrite(ledGreen, HIGH);
                break;

            case 5:
                digitalWrite(ledRed, LOW);
                digitalWrite(ledOrange, HIGH);
                digitalWrite(ledGreen, LOW);
                break;

            case 6:
                digitalWrite(ledRed, HIGH);
                digitalWrite(ledOrange, LOW);
                digitalWrite(ledGreen, LOW);
                break;

            case 7: 
                digitalWrite(ledRed, HIGH);
                digitalWrite(ledOrange, LOW);
                digitalWrite(ledGreen, LOW);
                break;

            default:
                break;
        }
    } else {
        // slave, the opposite to the transitter
        switch (current_state.id) {
            case 0:
                digitalWrite(ledRed, LOW);
                digitalWrite(ledOrange, LOW);
                digitalWrite(ledGreen, HIGH);
                break;
            case 1:
                digitalWrite(ledRed, LOW);
                digitalWrite(ledOrange, HIGH);
                digitalWrite(ledGreen, LOW);
                break;

            case 2: 
                digitalWrite(ledRed, HIGH);
                digitalWrite(ledOrange, LOW);
                digitalWrite(ledGreen, LOW);
                break;

            case 3: 
                digitalWrite(ledRed, HIGH);
                digitalWrite(ledOrange, LOW);
                digitalWrite(ledGreen, LOW);
                break;

            case 4:
                digitalWrite(ledRed, HIGH);
                digitalWrite(ledOrange, LOW);
                digitalWrite(ledGreen, LOW);
                break;

            case 5:
                digitalWrite(ledRed, HIGH);
                digitalWrite(ledOrange, LOW);
                digitalWrite(ledGreen, LOW);
                break;

            case 6:
                digitalWrite(ledRed, HIGH);
                digitalWrite(ledOrange, LOW);
                digitalWrite(ledGreen, LOW);
                break;

            case 7: 
                digitalWrite(ledRed, HIGH);
                digitalWrite(ledOrange, HIGH);
                digitalWrite(ledGreen, LOW);
                break;

            default:
                break;
        }
    }
}