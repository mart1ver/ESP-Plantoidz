/*
CONFIG FILE
*/



// we define the button pin for wifimanager
#define TRIGGER_PIN 34                // !!!! 34 for olimex ,33 esp32 dev kit
const char* apPassword = "password";  // password used for the acces point
#define portalDelay 120               // timeout for the ap to retry connection
bool wm_nonblocking = false;          // change to true to use non blocking
WiFiManager wm;                       // global wm instance

WiFiManagerParameter custom_field;   // global param ( for non blocking w params )
WiFiManagerParameter custom_field2;  // global param ( for non blocking w params )
WiFiManagerParameter custom_field3;  // global param ( for non blocking w params )
WiFiManagerParameter custom_field4;  // global param ( for non blocking w params )

static bool eth_connected = false;  // is eth connected ?


// Information about the LED strip itself
#define LED_PIN 3
#define NUM_LEDS 25
#define CHIPSET WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
#define BRIGHTNESS 128
#define I2S_PORT_TX I2S_NUM_0
#define I2S_PORT_RX I2S_NUM_0

// AMP I2S CONNECTIONS
#define I2S_DOUT 13
#define I2S_BCLK 14  // this should be the same as I2S_SCK for the mic
#define I2S_LRC 15   // this should be the same as I2S_WS for the mic

// MIC I2S CONNECTIONS
#define I2S_SD 2
#define I2S_WS 15
#define I2S_SCK 14

// AUDIO QUALITY SETTINGS
#define I2S_SAMPLE_RATE (16000)
#define I2S_SAMPLE_BITS (16)
#define I2S_READ_LEN (1024)
#define bufferCnt 10
#define bufferLen 1024
int16_t sBuffer[bufferLen];

// modes
#define MODE_IDLE 0
#define MODE_LISTEN 1
#define MODE_THINK 2
#define MODE_SPEAK 3
int MODE = 0;  // set initial modality to 0 | MODE_IDLE 0, MODE_LISTEN 1, MODE_THINK 2, MODE_SPEAK 3

char ESP_ID[25];
char websocket_server_host[25];
char websocket_server_port_mic[5];
char websocket_server_port_amp[5];

void ReadFromFS();

void ReadFromFS() {
    //we define the plant id based on conf file in the filesystem
    strcpy( ESP_ID, returnFile(SPIFFS, "/plantid.txt").c_str());
    // default server credentials to be put in the wifimanager
    strcpy( websocket_server_host , returnFile(SPIFFS, "/serverip.txt").c_str());  // adress of the server ,must be stored in file sys. modifiable via wifimanager
    strcpy( websocket_server_port_mic , returnFile(SPIFFS, "/port1.txt").c_str()); // <WEBSOCKET_SERVER_PORT> for the mic streaming
    strcpy( websocket_server_port_amp , returnFile(SPIFFS, "/port2.txt").c_str()); // <WEBSOCKET_SERVER_PORT> for the sound streaming

}
