#include <ArduinoWebsockets.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <time.h>
#include <DHT.h>
#define DHTPIN 2 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
ESP8266WiFiMulti wifiMulti; // Create an instance of the ESP8266WiFiMulti class called 'wifiMulti'
ESP8266WebServer server(80);   // create a web server on port 80
WebSocketsServer webSocket(81); // create a websocket server on port 81
WiFiClient espClient;
PubSubClient client(espClient);
WiFiClient espClient1;
PubSubClient client1(espClient1);
File fsUploadFile;               // a File variable to temporarily store the received file
#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);
const char *ssid = "ESP8266 Access Point"; // The name of the Wi-Fi network that will be created
const char *password = "bobby123";   //password required to connect, leave blank for an open network
const char *OTAName = "ESP8266";           // A name and a password for the OTA service
const char *OTAPassword = "esp8266";
int screennumber=0;
#define LED_R 2 //inbuilt LED
#define LED_RED     15            // specify the pins with an RGB LED connected
#define LED_GREEN   12
#define LED_BLUE    13
boolean device_one_state = false;
boolean device_two_state = false;
boolean device_three_state = false;
boolean device_four_state = false;
int devicenum=0;
String lms_enabled;
String lms_url;
String lms_port;
String lms_auth;
const char* lms_user_name;
const char* lms_password;
String rms_enabled;
String rms_url;
String rms_port;
String rms_auth;
const char* rms_user_name;
const char* rms_password;
String apname;
int wsClientNumber[5] = { -1, -1, -1, -1, -1};
int lastClientIndex = 0;
const int max_ws_client = 5;
volatile int state = LOW;
const char* mdnsName = "dekuva"; // Domain name for the mDNS responder

//const char* mqtt_server = "broker.mqtt-dashboard.com";
//const char* mqtt_server = "192.168.1.15";

long lastMsg = 0;
char msg[50];
int value = 0;
long lastReconnectAttempt = 0;
long lastReconnectAttempt1 = 0;
long lastReconnectAttempt2 = 0;
long lastReconnectAttempt3 = 0;
long lastReconnectAttempt4 = 0;
float timezone = 5.5;
int dst = 0;
int locmqtime=0;
int remmqtime=0;
boolean loc_mqtt_temp_disable=false;
String loc_mqtt_status_message="Status";
unsigned long temp_disabled_time=0;
unsigned long temp_disabled_time1=0;
boolean rem_mqtt_temp_disable=false;
String rem_mqtt_status_message="Status";
bool rainbow = false;            // The rainbow effect is turned off on startup
unsigned long prevMillis = millis();
int hue = 0;
int n=1;
String port1enable;
String port1pin;
String port1control;
String port1server;
String port1mqtt_topic;
String port1timer_type;
String port1on_time;
String port1off_time_duration;
String port1days;
String port2enable;
String port2pin;
String port2control;
String port2server;
String port2mqtt_topic;
String port2timer_type;
String port2on_time;
String port2off_time_duration;
String port2days;
String port3enable;
String port3pin;
String port3control;
String port3server;
String port3mqtt_topic;
String port3timer_type;
String port3on_time;
String port3off_time_duration;
String port3days;
String port4enable;
String port4pin;
String port4control;
String port4server;
String port4mqtt_topic;
String port4timer_type;
String port4on_time;
String port4off_time_duration;
String port4days;
String port5enable;
String port5pin;
String port5control;
String port5server;
String port5mqtt_topic;
String port5timer_type;
String port5on_time;
String port5off_time_duration;
String port5days;
String port6enable;
String port6pin;
String port6control;
String port6server;
String port6mqtt_topic;
String port6timer_type;
String port6on_time;
String port6off_time_duration;
String port6days;
String port1speed;
String port1type_of_pin;
String port1connected_device;
String port1area;
String port2speed;
String port2type_of_pin;
String port2connected_device;
String port2area;
String port3speed;
String port3type_of_pin;
String port3connected_device;
String port3area;
String port4speed;
String port4type_of_pin;
String port4connected_device;
String port4area;
String port5speed;
String port5type_of_pin;
String port5connected_device;
String port5area;
String port6speed;
String port6type_of_pin;
String port6connected_device;
String port6area;


int port1=0;
int port2=0;
int port3=0;
int port4=0;
int port5=0;
int port6=0;
int pir_value;
int pirState = LOW; // we start, assuming no motion detected
String roomtemperature="0";
String roomhumidity="0";
String operationmode="Normal";
/*__________________________________________________________SETUP__________________________________________________________*/

void setup() {
  pinMode(12, OUTPUT);    // the pins with LEDs connected are outputs
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  digitalWrite(12, LOW); 
  digitalWrite(13, LOW); 
  digitalWrite(14, LOW); 
  digitalWrite(15, LOW); 
  Serial.begin(115200);        // Start the Serial communication to send messages to the computer
  delay(100);
  Serial.println("\r\n");
  pinMode(A0, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display(); 
  startSPIFFS();             // Start the SPIFFS and list all contents
  startWiFi();   // Start a Wi-Fi access point,try to connect access points. wait for either an AP or STA connection
  startOTA();                  // Start the OTA service
  startWebSocket();            // Start a WebSocket server
  startMDNS();                 // Start the mDNS responder
  startServer();               // Start a HTTP server with a file read handler and an upload handler
  updateSsidList();
  mqtt_read();
  readtime();
  readport1data();
  readport2data();
  readport3data();
  readport4data();
  readport5data();
  readport6data();
  dht.begin();
}


void blynkled()
{
  pir_value = digitalRead(14); // read input value from PIR SENSOR
    if (pir_value == HIGH) { // check if the input is HIGH
      digitalWrite(LED_R, HIGH); // turn LED ON
      if (pirState == LOW) {
        // we have just turned on
        Serial.println("Motion detected!");
      
          if (client.connected())client.publish("outWindow","Motion Detected", true); //working
          if (client1.connected())client1.publish("outWindow","Motion Detected", true); //working
        // We only want to print on the output change, not state
        pirState = HIGH;
        }
        } 
        else {
          digitalWrite(LED_R, LOW); // turn LED OFF
            if (pirState == HIGH){
              // we have just turned of
                Serial.println("Motion ended!");
                
          if (client.connected())client.publish("outWindow","Motion---Ended", true); //working
          if (client1.connected())client1.publish("outWindow","Motion---Ended", true); //working
                // We only want to print on the output change, not state
                pirState = LOW;
              }
              }

}
void dht11sensor()
{
  long now2 = millis();
    if (now2 - lastReconnectAttempt4 >= 15000) {
      lastReconnectAttempt4 = now2;
      String temp_topic;
      String humid_topic;
      
      temp_topic=WiFi.macAddress()+"/Temperature";
      humid_topic=WiFi.macAddress()+"/Humidity";
      Serial.print("Temperature Topic-"); Serial.println(temp_topic);
      Serial.print("Humidity Topic-"); Serial.println(humid_topic);
      
      float h = dht.readHumidity();
      // Read temperature as Celsius (the default)
      float t = dht.readTemperature();
      // Read temperature as Fahrenheit (isFahrenheit = true)
      float f = dht.readTemperature(true);

      // Check if any reads failed and exit early (to try again).
      if (isnan(h) || isnan(t) || isnan(f)) {
        Serial.println(F("Failed to read from DHT sensor!"));
          return;
          }

      roomtemperature=t;
      
      roomhumidity=h;
      
      float hif = dht.computeHeatIndex(f, h);
      // Compute heat index in Celsius (isFahreheit = false)
      float hic = dht.computeHeatIndex(t, h, false);
      if (client.connected())
      {
        client.publish(temp_topic.c_str(),roomtemperature.c_str(), true); //working
        client.publish(humid_topic.c_str(),roomhumidity.c_str(), true); //working
        Serial.println("Temperature and Humidity Data Sent on Local Server");
        Serial.print("Temperature Topic - "); Serial.println(temp_topic);
        Serial.print("Humidity Topic - "); Serial.println(humid_topic);
      }
      if (client1.connected())
      {
        client1.publish(temp_topic.c_str(),roomtemperature.c_str(), true); //working
        client1.publish(humid_topic.c_str(),roomhumidity.c_str(), true); //working
        Serial.println(" Temperature and Humidity Data Sent on Remote Server");
        Serial.print("Temperature Topic - "); Serial.println(temp_topic);
        Serial.print("Humidity Topic - "); Serial.println(humid_topic);
      }
     
     wsSendState();
      Serial.print(F("Humidity: "));
      Serial.print(h);
      Serial.print(F("%  Temperature: "));
      Serial.print(t);
      Serial.print(F("°C "));
      Serial.print(f);
      Serial.print(F("°F  Heat index: "));
      Serial.print(hic);
      Serial.print(F("°C "));
      Serial.print(hif);
      Serial.println(F("°F"));
    }
}
/*____________________LOOP____________________________________*/
void readtime()
{
  if(operationmode=="Normal")
  {
    configTime(timezone * 3600, dst * 0, "pool.ntp.org", "time.nist.gov");
    Serial.println("\nWaiting for time");
    while (!time(nullptr)) 
    {
      Serial.print(".");
      delay(1000);
    }
  }
}
void dispscreen()
{
  long now2 = millis();
    if (now2 - lastReconnectAttempt2 >= 5000) {
      lastReconnectAttempt2 = now2;
      
      if(operationmode=="Normal")
        {
            IPAddress local_IP1=WiFi.localIP();
            Serial.println(local_IP1);
            if(local_IP1[0]>0 && local_IP1[0]<255)
              {
                Serial.println("Wifi Network available"); 
              } 
            else
              {
                startWiFi();
              }
                
          time_t now = time(nullptr);
          
         // if (client.connected())client.publish("time",ctime(&now), true); //working
         // if (client1.connected())client1.publish("time",ctime(&now), true); //working
          //if (client.connected())client.publish("IP_Address-1",(WiFi.localIP()).toString().c_str(), true); //working
          //if (client1.connected())client1.publish("IP_Address-1",(WiFi.localIP()).toString().c_str(), true); //working
          }
        if(operationmode=="Stand-alone")
        {
          IPAddress local_IP1=WiFi.softAPIP();
            Serial.println(local_IP1);
        }
      if(screennumber==0)
        {
          clearscreen();
          display.println("Network");
          display.print("SSID: ");
          if(operationmode=="Normal")
            {
            display.println(WiFi.SSID());
            }
          else
            {
            display.println("Not Connected   to Any WiFi N/w");
            }
          if(operationmode=="Normal")display.print("IP: "); 
          if(operationmode=="Normal")display.println(WiFi.localIP()); 
          if(operationmode=="Normal")
          {
            getBarsSignal(WiFi.RSSI());
          }
          else
          {
            displ_sw();
          }
        }
       if(screennumber==1)
        {
          clearscreen();
          display.println("AP");
          display.print("SSID: "); 
          display.println(apname);
          display.print("IP: "); 
          display.println(WiFi.softAPIP()); 
          if(operationmode=="Normal")
          {
            getBarsSignal(WiFi.RSSI());
          }
          else
          {
            displ_sw();
          }         
        }
        if(screennumber==2)
        {
          clearscreen();
          display.println(" ");
          display.println("Local Server Sett.");
          display.println(loc_mqtt_status_message);
          if(operationmode=="Normal")
          {
            getBarsSignal(WiFi.RSSI());
          }
          else
          {
            displ_sw();
          }
          
        }
        if(screennumber==3)
        {
          clearscreen();
          display.println(" ");
          display.println("Remote Server Sett.");
          display.println(rem_mqtt_status_message);
          if(operationmode=="Normal")
          {
            getBarsSignal(WiFi.RSSI());
          }
          else
          {
            displ_sw();
          }
        }
        if(screennumber==5)
        {
          clearscreen();
          display.println("Spare Settings");
          if(operationmode=="Normal")
          {
            getBarsSignal(WiFi.RSSI());
          }
          else
          {
            displ_sw();
          }
        }
        if(screennumber==4)
        {
          clearscreen();
          display.println("");
          display.print("Temp : ");display.println(roomtemperature);
          display.print("Humidity : ");display.println(roomhumidity);
          if(operationmode=="Normal")
          {
            getBarsSignal(WiFi.RSSI());
          }
          else
          {
            displ_sw();
          }
        }
        screennumber+=1;
        if(screennumber==6){
          screennumber=0;
          displ_sw();
        }
      }
}

void localmqtt1()
{
  if (lms_enabled=="Yes")
  {
      if (loc_mqtt_temp_disable==false)
      {
        if (!client.connected()) 
        {
         do
          {
            long now = millis();
            if (now - lastReconnectAttempt >= 10000)
            {
              locmqtime+=1;
              Serial.print("Attempting to connect to Local server .....");  
              Serial.println(locmqtime);
              lastReconnectAttempt = now;
              if (reconnect())
              {
                lastReconnectAttempt=0;
                loc_mqtt_status_message="Connected.";
                locmqtime=0;
                break;
              }
            }
            else
            {
              loc_mqtt_status_message="Waiting Server";
              break;
            }
          }while(locmqtime<=10);

          if (locmqtime>10)
          {
            loc_mqtt_temp_disable=true;
            locmqtime=0;
            loc_mqtt_status_message="Disabled for 15 Min.";
            temp_disabled_time=millis();
          }
          } 
        else 
        {
          client.loop();
          locmqtime=0;
          loc_mqtt_status_message="Connected.";
        }
      }
  else 
      {
        long nowtemp = millis();
        if (nowtemp - temp_disabled_time >= 900000) 
        {
          temp_disabled_time = nowtemp;
          loc_mqtt_status_message="Waiting Server";
          loc_mqtt_temp_disable=false;
        }
      }
  }
     else 
     {
      loc_mqtt_status_message="User Disabled.";
     }
}

void remotemqtt1()
{
  if (rms_enabled=="Yes")
  {
      if (rem_mqtt_temp_disable==false)
      {
        if (!client1.connected()) 
        {
          do
          {
            long now1 = millis();
            if (now1 - lastReconnectAttempt1 >= 10000)
            {
              remmqtime+=1;
              Serial.print("Attempting to connect to Remote server .....");  
              Serial.println(remmqtime);
              lastReconnectAttempt1 = now1;
              if (reconnect1())
              {
                lastReconnectAttempt1=0;
                rem_mqtt_status_message="Connected.";
                remmqtime=0;
                break;
              }
            }
            else
            {
              rem_mqtt_status_message="Waiting Server";
              break;
            }
          }while(remmqtime<=10);

          if (remmqtime>10)
          {
            rem_mqtt_temp_disable=true;
            remmqtime=0;
            rem_mqtt_status_message="Disabled for 15 Min.";
            temp_disabled_time1=millis();
          }
        } 
        else 
        {
          client1.loop();
          remmqtime=0;
          rem_mqtt_status_message="Connected.";
        }
      }
  else 
      {
        long nowtemp1 = millis();
        if (nowtemp1 - temp_disabled_time1 >= 900000) 
        {
          temp_disabled_time1 = nowtemp1;
          rem_mqtt_status_message="Waiting Server";
          rem_mqtt_temp_disable=false;
        }
       }
  }
     else 
     {
      rem_mqtt_status_message="User Disabled.";
     }
}

void disptime()
{
  long now3 = millis();
    if (now3 - lastReconnectAttempt3 >= 500)
    {
      lastReconnectAttempt3 = now3;
     time_t now = time(nullptr);
      display.setTextSize(1); 
      display.setCursor(0,26);display.print("   ");
    //  display.setTextColor(WHITE);display.println(ctime(&now));
          for (int nnn=0;nnn<11;nnn++)
          {
            display.print(ctime(&now)[nnn]);
          }
          for (int nnn=20;nnn<24;nnn++)
          {
            display.print(ctime(&now)[nnn]);
          }
          display.setCursor(0,36);
          display.setTextSize(2);
          display.print("   ");
          for (int nnn=11;nnn<16;nnn++)
          {
            display.print(ctime(&now)[nnn]);
          }
          display.setTextSize(1);
          
          
         
      displ_sw();
    }
}

void loop() 
{
  if(operationmode=="Normal")
  {
  MDNS.update();
  ArduinoOTA.handle();
  disptime();
  }
  
  webSocket.loop();                           // constantly check for websocket events
  server.handleClient();                      // run the server
                          // listen for OTA events
  dispscreen();
  localmqtt1();  
  remotemqtt1();
  
  dht11sensor();  
 /* if(rainbow) {                               // if the rainbow effect is turned on
    if(millis() > prevMillis + 32) {          
      if(++hue == 360)     // Cycle through the color wheel (increment by one degree every 32 ms)
        hue = 0;
      setHue(hue);                            // Set the RGB LED to the right color
      prevMillis = millis();
    }
  }*/
}

/*__________________________________SETUP_FUNCTIONS_____________________________*/

void startWiFi() { 
  apname=readjsonpara("/sitedata.json","hotspot_name");
  String appass=readjsonpara("/sitedata.json","hotspot_password");
  int ssidnum=readjsonlen("/storedssid.json","stored_ssid");
  IPAddress local_IP(192,168,4,4);
  IPAddress gateway(192,168,4,1);
  IPAddress subnet(255,255,255,0);
  locmqtime=0;
  remmqtime=0;
  loc_mqtt_temp_disable=false;
  loc_mqtt_status_message="Status";
  temp_disabled_time=0;
  temp_disabled_time1=0;
  rem_mqtt_temp_disable=false;
  rem_mqtt_status_message="Status";
  //  for(int n=1;n<ssidnum;n++)
  //  {
  //   }
  WiFi.softAPConfig (local_IP, gateway, subnet);
  WiFi.softAP(apname, appass);
  Serial.print("Access Point \"");  Serial.print(apname);  Serial.println("\" started.");
  //display.print("AP: \"");  display.print(apname);
  Serial.print("Soft-AP IP address is : ");  Serial.println(WiFi.softAPIP());
  Serial.print(ssidnum);Serial.println(" SSID Names are stored in data");
  //wifi scan start
  Serial.println("scan started");
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) 
    {
    Serial.println("no networks found");
    } 
  else 
    {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) 
      {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
       }
     }
  // Wait a bit before scanning again
  delay(3000);
  //wifi scan end
  // WiFi.config(static_ip,static_gateway,static_subnet);
  for(int n=0;n<ssidnum;n++)
  {
   const char * ssidname=readjsonarray("/storedssid.json","stored_ssid","ssid",n);
   const char * ssidpass=readjsonarray("/storedssid.json","stored_ssid","password",n);
   Serial.print("SSID: ");  Serial.print(ssidname); 
   Serial.print(",Password :"); Serial.print(ssidpass);Serial.println(" added.");
   wifiMulti.addAP(ssidname,ssidpass);
  }

    wifiMulti.addAP("Net_Plus", "bsnl@123");   // add Wi-Fi networks you want to connect to
    Serial.println("Connecting");
   while (wifiMulti.run() != WL_CONNECTED && WiFi.softAPgetStationNum() < 1) 
   {  
    delay(250);
    Serial.print('.');
    }
    Serial.println("\r\n");
    if(WiFi.softAPgetStationNum() == 0)  // If the ESP is connected to an AP
    {     
    Serial.print("Connected to ");
    Serial.println(WiFi.SSID());         // Tell us what network we're connected to
    Serial.print("IP address:\t");
    Serial.print(WiFi.localIP());     // Send the IP address of the ESP8266 to the computer
    } 
    else 
    {                                   // If a station is connected to the ESP SoftAP
    Serial.print("Station connected to AP \"");
    Serial.print(apname);  
    Serial.println("\"");
    Serial.print(WiFi.localIP()); 
    operationmode="Stand-alone";
    }
    Serial.println("\r\n");
}

void startOTA() // Start the OTA service
{ 
  if(operationmode=="Normal")
  {
    
  
    ArduinoOTA.setHostname(OTAName);
    ArduinoOTA.setPassword(OTAPassword);
    ArduinoOTA.onStart([]() {
    Serial.println("Start");
    digitalWrite(LED_RED, 0);    // turn off the LEDs
    digitalWrite(LED_GREEN, 0);
    digitalWrite(LED_BLUE, 0);
    });
    ArduinoOTA.onEnd([]() {
    Serial.println("\r\nEnd");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });
    ArduinoOTA.begin();
    Serial.println("OTA ready\r\n");
    }
}

void startSPIFFS() // Start the SPIFFS and list all contents
{ 
  SPIFFS.begin();                // Start the SPI Flash File System (SPIFFS)
  Serial.println("SPIFFS started. Contents:");
  {
    Dir dir = SPIFFS.openDir("/");
    while (dir.next()) 
    {                      // List the file system contents
    String fileName = dir.fileName();
    size_t fileSize = dir.fileSize();
    Serial.printf("\tFS File: %s, size: %s\r\n", fileName.c_str(), formatBytes(fileSize).c_str());
    }
    Serial.printf("\n");
  }
}

void startWebSocket() { // Start a WebSocket server
  webSocket.begin();             // start the websocket server
  webSocket.onEvent(webSocketEvent);    // if there's an incomming websocket 
  Serial.println("WebSocket server started."); //message, go to function 'webSocketEvent'
}

void startMDNS() { // Start the mDNS responder
   if(operationmode=="Normal")
  { 
  MDNS.begin(mdnsName,WiFi.localIP());                        // start the multicast domain name server
  MDNS.addService("http", "tcp", 80);
  MDNS.addService("ws", "tcp", 81);
  Serial.print("mDNS responder started: http://");
  Serial.print(mdnsName);
  Serial.println(".local");
  }
  if (operationmode=="Stand-alone")
  {
  MDNS.begin(mdnsName,WiFi.softAPIP());                        // start the multicast domain name server
  MDNS.addService("http", "tcp", 80);
  MDNS.addService("ws", "tcp", 81);
  Serial.print("mDNS responder started: http://");
  Serial.print(mdnsName);
  Serial.println(".local");
  }
  

  
}

void startServer() { // Start a HTTP server with a file read handler and an upload handler
  server.on("/edit.html",  HTTP_POST, []() {  // If a POST request is sent to the /edit.html address,
    server.send(200, "text/plain", ""); 
  }, handleFileUpload);                       // go to 'handleFileUpload'
  server.on("/list",HTTP_GET,handleFileList);
  server.on("/updateSsidList",HTTP_GET,updateSsidList1);
  server.on("/updatessidfile",HTTP_GET,updatessidfile1);
  server.on("/updatemqtt",HTTP_GET,updatemqttfile1);
  server.on("/updateserver",HTTP_GET,updateserverfile1);
  server.on("/updategenset",HTTP_GET,updategensetfile1);
  server.on("/updateportdata",HTTP_GET,updateportdatafile1);
  server.on("/rebootsystem",HTTP_GET,rebootsystem);
  server.on("/saveconfig",HTTP_GET,saveConfig);
  server.on("/loadconfig",HTTP_GET,loadConfig);
  server.onNotFound(handleNotFound); // if someone requests any other file or page, go to function 'handleNotFound'
                                             // and check if the file exists
  server.begin();                             // start the HTTP server
  Serial.println("HTTP server started.");
}

/*_____________________________SERVER_HANDLERS________________________________*/
void rebootsystem()
{
  Serial.println("Rebooting System");
  server.sendHeader("Location","/");
  server.send(303);
  delay(5000); 
  ESP.restart();    
}

void updateportdatafile1()
{
  String data1 = server.arg("data1");
  String port=server.arg("data2");
  Serial.println(port);
  Serial.println(data1);
  updateportdatafile(port,data1);
  Serial.println("File Updated");
  server.sendHeader("Location","/portsettings.html");     
  server.send(303);
}
void updateportdatafile(String portid,String getdata1)
{
  String opfilename;
   opfilename="/"+portid+".json";
  Serial.println(opfilename);
  File configFile = SPIFFS.open(opfilename, "w");
  if (!configFile) 
  {
    Serial.print("Failed to open ");
    Serial.print(opfilename);
    Serial.println(" file for writing");
  }
  else
  {
  configFile.println(getdata1);
  configFile.close();
  }
}

void updategensetfile1()
{
  String gensetdata = server.arg("data1");
  Serial.println(gensetdata);
  updategensetfile(gensetdata);
  Serial.println("File Updated");
  server.sendHeader("Location","/generalsettings.html");     
  server.send(303);
}
void updategensetfile(String gendata1)
{
  String mac=WiFi.macAddress();
  String mac1= "{\"mac_id\":\""+mac+"\","+gendata1;
  Serial.println(mac1);
  File configFile = SPIFFS.open("/sitedata.json", "w");
  if (!configFile) 
  {
    Serial.println("Failed to open generalsetting.json file for writing");
  }
  else
  {
  configFile.println(mac1);
  configFile.close();
  }
}

void updateSsidList1()
{
  updateSsidList();
  server.sendHeader("Location","/wifisettings.html");      // Redirect the client to the success page
  server.send(303);
}
void updateserverfile1()
{
  String serverdata = server.arg("data1");
  Serial.println(serverdata);
  updateserverfile(serverdata);
  Serial.println("File Updated");
  server.sendHeader("Location","/serversettings.html");     
  server.send(303);
}
void updatessidfile1()
{
  String ssiddata = server.arg("data1");
  Serial.println(ssiddata);
  updatessidfile(ssiddata);
  Serial.println("File Updated");
  server.sendHeader("Location","/wifisettings.html");     
  server.send(303);
}
void updatemqttfile1()
{
  String mqttdata = server.arg("data1");
  Serial.println(mqttdata);
  updatemqttfile(mqttdata);
  Serial.println("File Updated");
  server.sendHeader("Location","/mqttsettings.html");     
  server.send(303);
}
void updateserverfile(String serverdata1)
{
  File configFile = SPIFFS.open("/server.json", "w");
  if (!configFile) 
  {
    Serial.println("Failed to open server.json file for writing");
  }
  else
  {
  configFile.println(serverdata1);
  configFile.close();
  }
}
void updatemqttfile(String mqttdata1)
{
  File configFile = SPIFFS.open("/mqtt.json", "w");
  if (!configFile) 
  {
    Serial.println("Failed to open mqtt.json file for writing");
  }
  else
  {
  configFile.println(mqttdata1);
  configFile.close();
  }
}
void updatessidfile(String ssiddata1)
{
  File configFile = SPIFFS.open("/storedssid.json", "w");
  if (!configFile) 
  {
    Serial.println("Failed to open storedssid.json file for writing");
  }
  else
  {
  configFile.println(ssiddata1);
  configFile.close();
  }
}
  
void handleNotFound() // if the requested file or page doesn't exist,
{                     // return a 404 not found error
  if(!handleFileRead(server.uri()))
  {     // check if the file exists in the flash memory (SPIFFS), if so, send it
    server.send(404, "text/plain", "404: File Not Found");
  }
}
void handleFileDelete() 
{
  if (server.args() == 0) return server.send(500, "text/plain", "BAD ARGS");
  String path = server.arg(0);
  Serial.println("handleFileDelete: " + path);
  if (path == "/") return server.send(500, "text/plain", "BAD PATH");
  if (!SPIFFS.exists(path)) return server.send(404, "text/plain", "FileNotFound");
  SPIFFS.remove(path);
  server.send(200, "text/plain", "");
  path = String();
}

void handleFileCreate() {
  if (server.args() == 0) return server.send(500, "text/plain", "BAD ARGS");
  String path = server.arg(0);
  Serial.println("handleFileCreate: " + path);
  if (path == "/") return server.send(500, "text/plain", "BAD PATH");
  if (SPIFFS.exists(path)) return server.send(500, "text/plain", "FILE EXISTS");
  File file = SPIFFS.open(path, "w");
  if (file)
    file.close();
  else
    return server.send(500, "text/plain", "CREATE FAILED");
  server.send(200, "text/plain", "");
  path = String();
}

bool handleFileRead(String path) { // send the right file to the client (if it exists)
  Serial.println("handleFileRead: " + path);
  if (path.endsWith("/")) path += "index.html";   // If a folder is requested, send the index file
  String contentType = getContentType(path);      // Get the MIME type
  String pathWithGz = path + ".gz";
  if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)) 
  {                 // If the file exists, either as a compressed archive, or normal
    if (SPIFFS.exists(pathWithGz))                // If there's a compressed version available
      path += ".gz";                                         // Use the compressed verion
      File file = SPIFFS.open(path, "r");                    // Open the file
      size_t sent = server.streamFile(file, contentType);    // Send it to the client
      file.close();                                          // Close the file again
      Serial.println(String("\tSent file: ") + path);
      return true;
  }
   Serial.println(String("\tFile Not Found: ") + path);   // If the file doesn't exist, return false
  return false;
}
void handleFileList(){
  String output="<p>Go to <a href=\"/\"> Home Page</a> .</p>";
  output=output+"<p>Go to <a href=\"/edit.html\"> upload</a> Page to upload new files to device.</p>";
  output +="[";
  Dir dir = SPIFFS.openDir("/");
    while (dir.next()) {                      // List the file system contents
      String fileName = dir.fileName();
      size_t fileSize = dir.fileSize();
     //Serial.printf("\tFS File: %s, size: %s\r\n", fileName.c_str(), formatBytes(fileSize).c_str());
      output =output+ "<br>" + fileName.c_str()+"&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp     "+ formatBytes(fileSize).c_str()+"<br>";
    }
    //   Serial.printf("\n");
    output +="]";
    
    server.send(200, "text/html", output);
    
}

void handleFileUpload(){ // upload a new file to the SPIFFS
  HTTPUpload& upload = server.upload();
  String path;
  if(upload.status == UPLOAD_FILE_START){
    path = upload.filename;
    if(!path.startsWith("/")) path = "/"+path;
    if(!path.endsWith(".gz")) {                // The file server always prefers a compressed version of a file 
      String pathWithGz = path+".gz";         // So if an uploaded file is not compressed, the existing compressed
      if(SPIFFS.exists(pathWithGz))          // version of that file must be deleted (if it exists)
         SPIFFS.remove(pathWithGz);
    }
    Serial.print("handleFileUpload Name: "); Serial.println(path);
    fsUploadFile = SPIFFS.open(path, "w");   // Open the file for writing in SPIFFS (create if it doesn't exist)
    path = String();
  } else if(upload.status == UPLOAD_FILE_WRITE){
    if(fsUploadFile)
      fsUploadFile.write(upload.buf, upload.currentSize); // Write the received bytes to the file
  } else if(upload.status == UPLOAD_FILE_END){
    if(fsUploadFile) {                                    // If the file was successfully created
      fsUploadFile.close();                               // Close the file again
      Serial.print("handleFileUpload Size: "); Serial.println(upload.totalSize);
      server.sendHeader("Location","/success.html");      // Redirect the client to the success page
      server.send(303);
    } else {
      server.send(500, "text/plain", "500: couldn't create file");
    }
  }
}

void setmqtt(const char* topic11, const char* data11,boolean retained)
{
  if (client.connected())
  {
    client.publish(topic11,data11,retained);  
  }
  if (client1.connected())
  {
    client1.publish(topic11,data11,retained);
  }
}
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) 
{ 
  String onnn="1";
  String offf="0";
  switch (type) {
    case WStype_DISCONNECTED:             // if the websocket is disconnected
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED: {              // if a new websocket connection is established
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        int index = (num % max_ws_client);
        if (index <= 0) index = 0;
        wsClientNumber[index] = num;
        Serial.printf("Save client index %d :%u\n", index, num);
        wsSendState();
       // rainbow = false;                  // Turn rainbow off when a new connection is established
      }
      break;
    case WStype_TEXT:                     // if new text data is received
      Serial.printf("[%u] get Text: %s\n", num, payload);
      if (payload[0] == '#') {            // we get RGB data
        uint32_t rgb = (uint32_t) strtol((const char *) &payload[1], NULL, 16);   // decode rgb data
        int r = ((rgb >> 20) & 0x3FF);                     // 10 bits per color, so R: bits 20-29
        int g = ((rgb >> 10) & 0x3FF);                     // G: bits 10-19
        int b =          rgb & 0x3FF;                      // B: bits  0-9

        analogWrite(LED_RED,   r);                         // write it to the LED output pins
        analogWrite(LED_GREEN, g);
        analogWrite(LED_BLUE,  b);
      } else if (payload[0] == 'R') {         // the browser sends an R when the rainbow effect is enabled
        rainbow = true;
      } else if (payload[0] == 'N') {           // the browser sends an N when the rainbow effect is disabled
        rainbow = false;
      } else if (payload[0] == '1') {
        setStatus(true);
        wsSendState();
         setmqtt(port1mqtt_topic.c_str(),onnn.c_str(),true);// client.publish("inTopic","1");
      }
        else if (payload[0] == '0') {
        setStatus(false);
        wsSendState();
        setmqtt(port1mqtt_topic.c_str(),offf.c_str(),true);
       // client.publish(port1mqtt_topic.c_str(),"0");
      }
      else if (payload[0] == '3') {
        setStatus1(true);
        wsSendState();
        setmqtt(port2mqtt_topic.c_str(),onnn.c_str(),true);
        //client.publish("inTopic","3");
      }
      else if (payload[0] == '2') {
        setStatus1(false);
        wsSendState();
        setmqtt(port2mqtt_topic.c_str(),offf.c_str(),true);
        //client.publish("inTopic","2");
      }else if (payload[0] == '5') {
        setStatus2(true);
        wsSendState();
        setmqtt(port3mqtt_topic.c_str(),onnn.c_str(),true);
        //client.publish("inTopic","5");
      }
      else if (payload[0] == '4') {
        setStatus2(false);
        wsSendState();
        setmqtt(port3mqtt_topic.c_str(),offf.c_str(),true);
        //client.publish("inTopic","4");
      }else if (payload[0] == '7') {
        setStatus3(true);
        wsSendState();
        setmqtt(port4mqtt_topic.c_str(),onnn.c_str(),true);
       // client.publish("inTopic","7");
      }
      else if (payload[0] == '6') {
        setStatus3(false);
        wsSendState();
        setmqtt(port4mqtt_topic.c_str(),offf.c_str(),true);
       // client.publish("inTopic","6");
      }
      break;
  }
}



bool updateSsidList() 
{
  int n = WiFi.scanNetworks();
  String inc_type;
  Serial.println("scan done");
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& root1  = jsonBuffer.createObject();
  JsonArray& Button1 = root1.createNestedArray("detected_ssid");
  for(int i=0; i<n; i++)
  {
    JsonObject& ButtonID = Button1.createNestedObject();
    ButtonID["ssid"] = WiFi.SSID(i);
    ButtonID["signal"] = WiFi.RSSI(i);
    if (WiFi.encryptionType(i) == ENC_TYPE_NONE) inc_type="None";
    if (WiFi.encryptionType(i) == ENC_TYPE_AUTO) inc_type="Auto";
    if (WiFi.encryptionType(i) == ENC_TYPE_WEP) inc_type="WEP";
    if (WiFi.encryptionType(i) == ENC_TYPE_TKIP) inc_type="WPA";
    if (WiFi.encryptionType(i) == ENC_TYPE_CCMP) inc_type="WPA2";
    ButtonID["type"] =inc_type;
   }
   File configFile = SPIFFS.open("/detectedssid.json", "w");
   if (!configFile) 
   {
    Serial.println("Failed to open config file for writing");
    server.send(500,"text/plain","could not update file");
    return false;
    }
    root1.printTo(configFile);
    Serial.println("Detected SSID List Updated.");
    delay(5000);
    configFile.close();
    return true;
}
/*______________________Json Read and write function______________________*/
bool saveConfig() {
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
    Serial.println("no networks found");
  } 
  else 
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
    }
  }
  char *username[]={"Varinder","Deepti","Kriti"};
  char *password[]={"abc","def","ghi"};
  char *protection[]={"open","open","protected"};
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& root  = jsonBuffer.createObject();
  JsonArray& Button = root.createNestedArray("detected_ssid");
  for(int i=0; i<n; i++)
   {
    JsonObject& ButtonID = Button.createNestedObject();
    ButtonID["ssid"] = WiFi.SSID(i);
    ButtonID["signal"] = WiFi.RSSI(i);
    ButtonID["type"] = (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? "Open " : "Protected";
    
   }

   /*
  JsonObject& root = jsonBuffer.createObject();
  root["serverName"] = "api.example.com1";
  root["accessToken"] = "128du9as8du12eoue8da98h123ueh9h98";
  JsonArray& mqtt= root.createNestedArray("data");
  mqtt.add(double_with_n_digits(48.756080,6));
  mqtt.add(double_with_n_digits(2.302038,6));
  mqtt.add(("2.302038"));
 JsonObject& data1= root.createNestedObject("data1");
  data1.set("temprature","30.1");
  data1.set("Humadity","70.1");
 */
 /*
 JsonObject& data1= root.createNestedObject("detected_ssid");
// JsonArray& data1= data.createNestedArray("1");
  data1.set("ssid","detectedNet_Plus");
  data1.set("Ppssword","bsnl@123");
  data1.set("type","open");
  */

  /*
  JsonObject& root  = jsonBuffer.createObject();
  JsonArray& Button = root.createNestedArray("BTN");

  root["METHOD"]  = "GET";
  root["ID"]       = 123;
  root["IP"]       = "192.168.1.7";
  root["VER"]    = "Version";
  root["PW"]     = "Power";
  root["TEMP"]     = "Temperature";

  JsonObject& Button1 = Button.createNestedObject();
  Button1["ID"] = 1;
  Button1["STT"] = 0;

  JsonObject& Button2 = Button.createNestedObject();
  Button2["ID"]   = 2;
  Button2["STT"] = 1;

  JsonObject& Button3 = Button.createNestedObject();
  Button3["ID"]   = 3;
  Button3["STT"] = 0;

  */
  File configFile = SPIFFS.open("/detectedssid.json", "w");
  if (!configFile) 
  {
    Serial.println("Failed to open config file for writing");
    return false;
  }
  root.printTo(configFile);
  configFile.close();
  return true;
}
bool loadConfig() 
{
  File configFile = SPIFFS.open("/config.json", "r");
  if (!configFile) 
  {
    Serial.println("Failed to open config file");
    return false;
  }
  size_t size = configFile.size();
  if (size > 1024) 
  {
    Serial.println("Config file size is too large");
    return false;
  }
                     // Allocate a buffer to store contents of the file.
  std::unique_ptr<char[]> buf(new char[size]);

  // We don't use String here because ArduinoJson library requires the input
  // buffer to be mutable. If you don't use ArduinoJson, you may as well
  // use configFile.readString instead.
  configFile.readBytes(buf.get(), size);
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(buf.get());
  if (!json.success()) 
  {
    Serial.println("Failed to parse config file");
    return false;
  }
  const char* serverName = json["Varinder"]["serverName"];
  const char* accessToken = json["Varinder"]["accessToken"];
  // Real world application would store these values in some variables for
  // later use.
  Serial.print("Loaded serverName: ");
  Serial.println(serverName);
  Serial.print("Loaded accessToken: ");
  Serial.println(accessToken);
  configFile.close();
  return true;
}

String readjsonpara(String filename,String Parameter) 
{
  File configFile = SPIFFS.open(filename, "r");
  if (!configFile) {
    Serial.print("Failed to open ");Serial.print(filename);
    Serial.println(" file");
    return "False";
  }
  size_t size = configFile.size();
  if (size > 1024) {
    Serial.println("Config file size is too large");
    return "False";
  }
  std::unique_ptr<char[]> buf(new char[size]);
  configFile.readBytes(buf.get(), size);
  StaticJsonBuffer<1024> jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(buf.get());
  if (!json.success()) 
  {
    Serial.println("Failed to parse config file");
    return "False";
  }
  const char* param1 = json[Parameter];
  Serial.print("Parameter: ");
  Serial.print(param1);
  Serial.println(" returned.");
  configFile.close();
  return param1;
}

const char * readjsonparachar(String filename,String Parameter) 
{
  File configFile = SPIFFS.open(filename, "r");
  if (!configFile) 
  {
    Serial.print("Failed to open ");Serial.print(filename);
    Serial.println(" file");
    return "False";
  }
  size_t size = configFile.size();
  if (size > 1024) 
  {
    Serial.println("Config file size is too large");
    return "False";
  }
  std::unique_ptr<char[]> buf(new char[size]);
  configFile.readBytes(buf.get(), size);
  StaticJsonBuffer<1024> jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(buf.get());
  if (!json.success()) 
  {
    Serial.println("Failed to parse config file");
    return "False";
  }
  const char* param1 = json[Parameter];
  Serial.print("Parameter: ");
  Serial.print(param1);
  Serial.println(" returned.");
  configFile.close();
  return param1;
}

String readjsonparaint(String filename,String Parameter) 
{
  File configFile = SPIFFS.open(filename, "r");
  if (!configFile) {
    Serial.print("Failed to open ");Serial.print(filename);
    Serial.println(" file");
    return "False";
  }
  size_t size = configFile.size();
  if (size > 1024) {
    Serial.println("Config file size is too large");
    return "False";
  }
  std::unique_ptr<char[]> buf(new char[size]);
  configFile.readBytes(buf.get(), size);
  StaticJsonBuffer<1024> jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(buf.get());
  if (!json.success()) {
    Serial.println("Failed to parse config file");
    return "False";
  }
  const char* param1 = json[Parameter];
  Serial.print("Parameter: ");
  Serial.print(param1);
  Serial.println(" returned.");
  configFile.close();
  return param1;
}

const char * readjsonarray(String filename,String Para, String subpara, int recno) 
{
  File configFile = SPIFFS.open(filename, "r");
  if (!configFile) {
    Serial.print("Failed to open ");Serial.print(filename);
    Serial.println(" file");
    return "False";
  }
  size_t size = configFile.size();
  if (size > 1024) {
    Serial.println("Config file size is too large");
    return "False";
  }
  std::unique_ptr<char[]> buf(new char[size]);
  configFile.readBytes(buf.get(), size);
  StaticJsonBuffer<1024> jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(buf.get());
  if (!json.success()) {
    Serial.println("Failed to parse config file");
    return "False";
  }
  const char* param1 = json[Para][recno][subpara];
  configFile.close();
  return param1;
}


int readjsonlen(String filename,String Parameter) 
{
  int n=0;
  File configFile = SPIFFS.open(filename, "r");
  if (!configFile) {
    Serial.print("Failed to open ");Serial.print(filename);
    Serial.println(" file");
    return 0;
  }
  size_t size = configFile.size();
  if (size > 1024) {
    Serial.println("Config file size is too large");
    return 0;
  }
  std::unique_ptr<char[]> buf(new char[size]);
  configFile.readBytes(buf.get(), size);
  StaticJsonBuffer<1024> jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(buf.get());
  if (!json.success()) {
    Serial.println("Failed to parse config file");
    return 0;
  }
   n=json[Parameter].size();
  configFile.close();
  return n;
}

/*____________________HELPER_FUNCTIONS__________________*/

String formatBytes(size_t bytes) { // convert sizes in bytes to KB and MB
  if (bytes < 1024) {
    return String(bytes) + "B";
  } else if (bytes < (1024 * 1024)) {
    return String(bytes / 1024.0) + "KB";
  } else if (bytes < (1024 * 1024 * 1024)) {
    return String(bytes / 1024.0 / 1024.0) + "MB";
  }else {
    return String(bytes / 1024.0 / 1024.0 / 1024.0) + "GB";
  }
}

String getContentType(String filename) 
{
  if (server.hasArg("download")) return "application/octet-stream";
  else if (filename.endsWith(".htm")) return "text/html";
  else if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".png")) return "image/png";
  else if (filename.endsWith(".gif")) return "image/gif";
  else if (filename.endsWith(".jpg")) return "image/jpeg";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".xml")) return "text/xml";
  else if (filename.endsWith(".pdf")) return "application/x-pdf";
  else if (filename.endsWith(".zip")) return "application/x-zip";
  else if (filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}

void wsSendState()
{
  time_t now = time(nullptr);
  String json = "{";
  json += "\"devices\":[";
 
  //json += +"\":";
  json += "{";//{
  json += "\"state1\":";
  if (device_one_state) json += "\"on";
  else json += "\"off";
  json += "\",\"state2\":";
  if (device_two_state) json += "\"on";
  else json += "\"off";
  json += "\",\"state3\":";
  if (device_three_state) json += "\"on";
  else json += "\"off";
  json += "\",\"state4\":";
  if (device_four_state) json += "\"on";
  else json += "\"off";
  json += "\",\"roomtemperature\":";
  json += "\"";
  json += roomtemperature;
  json += "\",\"roomhumidity\":";
  json += "\"";
  json += roomhumidity;
  json += "\",\"ConnectedNetwork\":";
  json += "\"";
  json += WiFi.SSID();
  json += "\",\"IpAddress\":";
  json += "\"";
  json += (WiFi.localIP()).toString();
  json += "\",\"ApSsid\":";
  json += "\"";
  json += apname;
  json += "\",\"ApIp\":";
  json += "\"";
  json += (WiFi.softAPIP()).toString();
  json += "\",\"LocalServer\":";
  json += "\"";
  json += loc_mqtt_status_message;
  json += "\",\"RemoteServer\":";
  json += "\"";
  json += rem_mqtt_status_message;
  json += "\",\"WifiSignalStrength\":";
  json += "\"";
  json += WiFi.RSSI();
  
  json += "\"}";
  json += "]";
  json += "}";
  int numcl = 0;
  for (numcl = 0; numcl < max_ws_client; numcl++)
  {
    if (wsClientNumber[numcl] != -1)
      webSocket.sendTXT(wsClientNumber[numcl], json);
  }
 json = String();
}

void changestate() {
  state = !state;
  setStatus(state);
  wsSendState();
}
String getContentType1(String filename) { 
  if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}

void setHue(int hue) { 
  hue %= 360;                   // hue is an angle between 0 and 359°
  float radH = hue*3.142/180;   // Convert degrees to radians
  float rf, gf, bf;
  
  if(hue>=0 && hue<120)
      {        // Convert from HSI color space to RGB              
    rf = cos(radH*3/4);
    gf = sin(radH*3/4);
    bf = 0;
      } 
    else if(hue>=120 && hue<240)
      {
    radH -= 2.09439;
    gf = cos(radH*3/4);
    bf = sin(radH*3/4);
    rf = 0;
      } else if(hue>=240 && hue<360){
    radH -= 4.188787;
    bf = cos(radH*3/4);
    rf = sin(radH*3/4);
    gf = 0;
  }
  int r = rf*rf*1023;
  int g = gf*gf*1023;
  int b = bf*bf*1023;
  analogWrite(LED_RED,   r);    // Write the right color to the LED output pins
  analogWrite(LED_GREEN, g);
  analogWrite(LED_BLUE,  b);
}

void setStatus(boolean st)
{
  devicenum=1;
  if (st)
  {
    device_one_state = true;
    Serial.print("Change state:");
    Serial.println(st);
    digitalWrite(port1, HIGH); // Xuất trạng thái  ra chân GPIO16
  }
  else
  {
    device_one_state = false;
    Serial.print("Change state:");
    Serial.println(st);
    digitalWrite(port1, LOW); // Xuất trạng thái  ra chân GPIO16
  }
}

void setStatus1(boolean st)
{
  devicenum=2;
  if (st)
  {
    device_two_state = true;
    Serial.print("Change state:");
    Serial.println(st);
    digitalWrite(port2, HIGH); // Xuất trạng thái  ra chân GPIO16
  }
  else
  {
    device_two_state = false;
    Serial.print("Change state:");
    Serial.println(st);
    digitalWrite(port2, LOW); // Xuất trạng thái  ra chân GPIO16
  }
}

void setStatus2(boolean st)
{
  devicenum=3;
  if (st)
  {
    device_three_state = true;
    Serial.print("Change state:");
    Serial.println(st);
    digitalWrite(port3, HIGH); // Xuất trạng thái  ra chân GPIO16
  }
  else
  {
    device_three_state = false;
    Serial.print("Change state:");
    Serial.println(st);
    digitalWrite(port3, LOW); // Xuất trạng thái  ra chân GPIO16
  }
}

void setStatus3(boolean st)
{
  devicenum=4;
  if (st)
  {
    device_four_state = true;
    Serial.print("Change state:");
    Serial.println(st);
    digitalWrite(port4, HIGH); // Xuất trạng thái  ra chân GPIO16
  }
  else
  {
    device_four_state = false;
    Serial.print("Change state:");
    Serial.println(st);
    digitalWrite(port4, LOW); // Xuất trạng thái  ra chân GPIO16
  }
}

boolean reconnect() 
{
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection to Local Server ");
    Serial.print(lms_url);
    String clientId = "ESP8266Client-"+WiFi.macAddress();
 //   clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) 
    {
      Serial.println(".......connected");
     // client.publish("outTopic", "hello world",true);
     // client.subscribe("outTemperature");
      //client.subscribe("humidity");
      
      startintopic();
      return client.connected();
    } else 
    {
      Serial.print(" failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      return client.connected();
    }
  }
}

boolean reconnect1() 
{
  while (!client1.connected()) {
    Serial.print("Attempting MQTT connection to Remote Server ");
    Serial.print(rms_url);
    String clientId = "ESP8266Client"+WiFi.macAddress();
 //   clientId += String(random(0xffff), HEX);
    if (client1.connect(clientId.c_str())) 
    {
      Serial.println(".......connected");
      client1.publish("outTopic", "hello world",true);
      //client1.subscribe("inTopic");
      startintopic1();
      return client1.connected();
    } else 
    {
      Serial.print(" failed, rc=");
      Serial.print(client1.state());
      Serial.println(" try again in 5 seconds");
      return client1.connected();
    }
  }
}
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived on Local Server[");Serial.print(topic);Serial.print("] ");
  
  
  for (int i = 0; i < length; i++) 
  {
    Serial.print((char)payload[i]);
  }
  Serial.println("");
  
  char *cstring = (char *) payload;
  cstring[length] = '\0';
  String aaa= cstring;
  String toopic= String(topic);
  Serial.print(toopic);
  Serial.println(" - topic Name");
 /* if (toopic=="outTemperature")
  {
   
    //String aaa=String(* payload);
    roomtemperature=aaa;
    wsSendState();
    Serial.print(roomtemperature);
    Serial.println(" - temperature");
    }
  if (toopic=="humidity")
  {
   
    roomhumidity=(char *) payload+'\0';
    Serial.print(roomhumidity);
    wsSendState();
    Serial.println(" - Humidity");
  }*/
  if (toopic==port1mqtt_topic)
  {
    if ((char)payload[0] == '0') 
    {
     if (client1.connected() && digitalRead(port1pin.toInt())==HIGH)
          {
            client1.publish(toopic.c_str(),"0",true);
          }
    setStatus(false);
    wsSendState();  
     } 
     else if((char)payload[0] == '1')
     {
        if (client1.connected() && digitalRead(port1pin.toInt())==LOW)
          {
            client1.publish(toopic.c_str(),"1",true);
          }
        setStatus(true);
        wsSendState(); 
      }
  }
  if (toopic==port2mqtt_topic)
  {
    if ((char)payload[0] == '0') 
    {
      if (client1.connected() && digitalRead(port2pin.toInt())==HIGH)
          {
            client1.publish(toopic.c_str(),"0",true);
          }
        setStatus1(false);
        wsSendState();
        
     } 
     else if((char)payload[0] == '1')
      {
        if (client1.connected() && digitalRead(port2pin.toInt())==LOW)
          {
            client1.publish(toopic.c_str(),"1",true);
          }
        setStatus1(true);
        wsSendState(); 
        
      }
  }
  if (toopic==port3mqtt_topic)
  {
    if ((char)payload[0] == '0') 
    {
      if (client1.connected() && digitalRead(port3pin.toInt())==HIGH)
          {
            client1.publish(toopic.c_str(),"0",true);
          }
        setStatus2(false);
        wsSendState();  
       
    } 
    else if((char)payload[0] == '1')
    {
    if (client1.connected() && digitalRead(port3pin.toInt())==LOW)
          {
            client1.publish(toopic.c_str(),"1",true);
          }
    setStatus2(true);
        wsSendState();  
       
    }
  }
  if (toopic==port4mqtt_topic)
  {
    if ((char)payload[0] == '0') 
      {
      if (client1.connected() && digitalRead(port4pin.toInt())==HIGH)
          {
            client1.publish(toopic.c_str(),"0",true);
          }
          setStatus3(false);
          wsSendState(); 
       } 
       else if((char)payload[0] == '1')
            {
            if (client1.connected() && digitalRead(port4pin.toInt())==LOW)
            {
            client1.publish(toopic.c_str(),"1",true);
            }
            setStatus3(true);
            wsSendState();
            }
  }
}
void callback1(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived on Remote Server [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  String load=String(payload[0]);
  String toopic= String(topic);
  
  if (toopic==port1mqtt_topic)
  {
    if ((char)payload[0] == '0') 
    {
      if (client.connected() && digitalRead(port1pin.toInt())==HIGH)
          {
            client.publish(toopic.c_str(),"0",true);
          }
    setStatus(false);
        wsSendState();  
    } 
    else if((char)payload[0] == '1')
    {
    if (client.connected() && digitalRead(port1pin.toInt())==LOW)
          {
            client.publish(toopic.c_str(),"1",true);
          }
    setStatus(true);
        wsSendState();  
  }
  }
  if (toopic==port2mqtt_topic)
  {
    if ((char)payload[0] == '0') 
    {
      if (client.connected() && digitalRead(port2pin.toInt())==HIGH)
          {
            client.publish(toopic.c_str(),"0",true);
          }
    setStatus1(false);
        wsSendState();  
  } else if((char)payload[0] == '1')
  {
    if (client.connected() && digitalRead(port2pin.toInt())==LOW)
          {
            client.publish(toopic.c_str(),"1",true);
          }
    setStatus1(true);
        wsSendState();  
  }
  }
  if (toopic==port3mqtt_topic)
  {
    if ((char)payload[0] == '0') 
    {
      if (client.connected() && digitalRead(port3pin.toInt())==HIGH)
          {
            client.publish(toopic.c_str(),"0",true);
          }
    setStatus2(false);
        wsSendState();  
  } else if((char)payload[0] == '1')
  {
    if (client.connected() && digitalRead(port3pin.toInt())==LOW)
          {
            client.publish(toopic.c_str(),"1",true);
          }
    setStatus2(true);
        wsSendState();  
  }
  }
  if (toopic==port4mqtt_topic)
  {
    if ((char)payload[0] == '0') 
    {
      if (client.connected() && digitalRead(port4pin.toInt())==HIGH)
          {
            client.publish(toopic.c_str(),"0",true);
          }
    setStatus3(false);
        wsSendState();  
  } else if((char)payload[0] == '1')
  {
    if (client.connected() && digitalRead(port4pin.toInt())==LOW)
          {
            client.publish(toopic.c_str(),"1",true);
          }
    setStatus3(true);
        wsSendState();  
  }
  }
}

void mqtt_read()
{
  lms_enabled= readjsonpara("/mqtt.json","lms_enabled");
  lms_url =readjsonpara("/mqtt.json","lms_url");
  lms_port =readjsonpara("/mqtt.json","lms_port");
  lms_auth =readjsonpara("/mqtt.json","lms_auth");
  lms_user_name =readjsonparachar("/mqtt.json","lms_user_name");
  lms_password =readjsonparachar("/mqtt.json","lms_password");
  rms_enabled =readjsonpara("/mqtt.json","rms_enabled");
  rms_url =readjsonpara("/mqtt.json","rms_url");
  rms_port =readjsonpara("/mqtt.json","rms_port");
  rms_auth =readjsonpara("/mqtt.json","rms_auth");
  rms_user_name =readjsonparachar("/mqtt.json","rms_user_name");
  rms_password =readjsonparachar("/mqtt.json","rms_password"); 
  Serial.println(lms_enabled);
  Serial.println(lms_url);
  Serial.println(lms_port);
  Serial.println(lms_auth);
  Serial.println(lms_user_name);
  Serial.println(lms_password);
  Serial.println(rms_enabled);
  Serial.println(rms_url);
  Serial.println(rms_port);
  Serial.println(rms_auth);
  Serial.println(rms_user_name);
  Serial.println(rms_password);
  
  
  if(operationmode=="Stand-alone")
    {
    lms_enabled="No";
    rms_enabled="No";
  }

  
  if(lms_enabled=="Yes")
  {
   client.setServer(lms_url.c_str(), lms_port.toInt());
   // client.setServer(mqtt_server, lms_port.toInt());
   client.setCallback(callback);
   Serial.print("Local Mqtt Server Enabled=");
   Serial.print(lms_enabled);
   Serial.print(" at IP Address:");
   Serial.print(lms_url);
   Serial.print(" and Port:");
   Serial.println(lms_port);
   }
   if(rms_enabled=="Yes")
   {
   client1.setServer(rms_url.c_str(), rms_port.toInt());
   client1.setCallback(callback1);
   Serial.print("Remote Mqtt Server Enabled=");
   Serial.print(rms_enabled);
   Serial.print(" at IP Address:");
   Serial.print(rms_url);
   Serial.print(" and Port:");
   Serial.println(rms_port);
    }
}

void getBarsSignal(long rssi)
{
   int bars;
    if (rssi > -55) { bars = 5;} 
    else if (rssi < -55 & rssi > -65) { bars = 4;}
    else if (rssi < -65 & rssi > -75) { bars = 3;} 
    else if (rssi < -75 & rssi > -85) { bars = 2;} 
    else if (rssi < -85 & rssi > -96) { bars = 1;} 
    else { bars = 0; }
    for (int b=0; b <= bars; b++) 
         { display.fillRect(110 + (b*3),4 - (b*1),2,b*1,WHITE); 
            display.drawRect(90,1,16,4, WHITE);
         }
          display.display();
          
}

void clearscreen(){
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
}

void clearscreen1(){
      
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println("                      ");
      display.println("                      ");
      display.println("                      ");
      display.println("                      ");
      display.setCursor(0,0);
}

void displ_sw()
{
  if(!device_one_state){display.drawRect(14,54,10,10,WHITE);}
  else{display.fillRect(14,54,10,10,WHITE);}
  if(!device_two_state){display.drawRect(42,54,10,10,WHITE);}
  else{display.fillRect(42,54,10,10,WHITE);}
  if(!device_three_state){display.drawRect(70,54,10,10,WHITE);}
  else{display.fillRect(70,54,10,10,WHITE);}
  if(!device_four_state){display.drawRect(98,54,10,10,WHITE);}
  else{display.fillRect(98,54,10,10,WHITE);}
  display.display();
}

void readport1data()
{
  port1enable=readjsonpara("/port1.json","enable_status"); Serial.println(port1enable);
  port1pin=readjsonpara("/port1.json","gpio");Serial.println(port1pin);
  port1control=readjsonpara("/port1.json","control");Serial.println(port1control);
  port1server=readjsonpara("/port1.json","server");Serial.println(port1server);
  port1mqtt_topic=readjsonpara("/port1.json","mqtt_topic");Serial.println(port1mqtt_topic);
  port1timer_type=readjsonpara("/port1.json","timer_type"); Serial.println(port1timer_type);
  port1on_time=readjsonpara("/port1.json","on_time");Serial.println(port1on_time);
  port1off_time_duration=readjsonpara("/port1.json","off_time_duration"); Serial.println(port1off_time_duration);
  port1days=readjsonpara("/port1.json","days");Serial.println(port1days);
  port1speed=readjsonpara("/port1.json","speed");Serial.println(port1speed);
  port1type_of_pin=readjsonpara("/port1.json","type_of_pin");Serial.println(port1type_of_pin);
  port1connected_device=readjsonpara("/port1.json","connected_device");Serial.println(port1connected_device);
  port1area=readjsonpara("/port1.json","area");Serial.println(port1area);
  port1=port1pin.toInt();
  if (port1type_of_pin=="Switch")
  {
    pinMode(port1, OUTPUT);
  }
  
 }
 

 void readport2data()
 {
  port2enable=readjsonpara("/port2.json","enable_status");Serial.println(port2enable);
  port2pin=readjsonpara("/port2.json","gpio");Serial.println(port2pin);
  port2control=readjsonpara("/port2.json","control");Serial.println(port2control);
  port2server=readjsonpara("/port2.json","server");Serial.println(port2server);
  port2mqtt_topic=readjsonpara("/port2.json","mqtt_topic");Serial.println(port2mqtt_topic);
  port2timer_type=readjsonpara("/port2.json","timer_type"); Serial.println(port2timer_type);
  port2on_time=readjsonpara("/port2.json","on_time");Serial.println(port2on_time);
  port2off_time_duration=readjsonpara("/port2.json","off_time_duration"); Serial.println(port2off_time_duration);
  port2days=readjsonpara("/port2.json","days");Serial.println(port2days);
  port2speed=readjsonpara("/port2.json","speed");Serial.println(port2speed);
  port2type_of_pin=readjsonpara("/port2.json","type_of_pin");Serial.println(port2type_of_pin);
  port2connected_device=readjsonpara("/port2.json","connected_device");Serial.println(port2connected_device);
  port2area=readjsonpara("/port2.json","area");Serial.println(port2area);
  port2=port2pin.toInt();
  if (port2type_of_pin=="Switch")
  {
  pinMode(port2, OUTPUT);
  }
 }

 void readport3data()
 {
  port3enable=readjsonpara("/port3.json","enable_status");Serial.println(port3enable);
  port3pin=readjsonpara("/port3.json","gpio");Serial.println(port3pin);
  port3control=readjsonpara("/port3.json","control"); Serial.println(port3control);
  port3server=readjsonpara("/port3.json","server");Serial.println(port3server);
  port3mqtt_topic=readjsonpara("/port3.json","mqtt_topic");Serial.println(port3mqtt_topic);
  port3timer_type=readjsonpara("/port3.json","timer_type");Serial.println(port3timer_type);
  port3on_time=readjsonpara("/port3.json","on_time");Serial.println(port3on_time);
  port3off_time_duration=readjsonpara("/port3.json","off_time_duration");Serial.println(port3off_time_duration);
  port3days=readjsonpara("/port3.json","days"); Serial.println(port3days);
  port3speed=readjsonpara("/port3.json","speed");Serial.println(port3speed);
  port3type_of_pin=readjsonpara("/port3.json","type_of_pin");Serial.println(port3type_of_pin);
  port3connected_device=readjsonpara("/port3.json","connected_device");Serial.println(port3connected_device);
  port3area=readjsonpara("/port3.json","area");Serial.println(port3area);
  port3=port3pin.toInt();
  if (port3type_of_pin=="Switch")
  {
  pinMode(port3, OUTPUT);
  }
 }

 void readport4data()
 {
  port4enable=readjsonpara("/port4.json","enable_status");Serial.println(port4enable);
  port4pin=readjsonpara("/port4.json","gpio");Serial.println(port4pin);
  port4control=readjsonpara("/port4.json","control"); Serial.println(port4control);
  port4server=readjsonpara("/port4.json","server");Serial.println(port4server);
  port4mqtt_topic=readjsonpara("/port4.json","mqtt_topic");Serial.println(port4mqtt_topic);
  port4timer_type=readjsonpara("/port4.json","timer_type");Serial.println(port4timer_type);
  port4on_time=readjsonpara("/port4.json","on_time");Serial.println(port4on_time);
  port4off_time_duration=readjsonpara("/port4.json","off_time_duration");Serial.println(port4off_time_duration);
  port4days=readjsonpara("/port4.json","days");Serial.println(port4days);
  port4speed=readjsonpara("/port4.json","speed");Serial.println(port4speed);
  port4type_of_pin=readjsonpara("/port4.json","type_of_pin");Serial.println(port4type_of_pin);
  port4connected_device=readjsonpara("/port4.json","connected_device");Serial.println(port4connected_device);
  port4area=readjsonpara("/port4.json","area");Serial.println(port4area);
  port4=port4pin.toInt();
  if (port4type_of_pin=="Switch")
  {
    pinMode(port4, OUTPUT);
  }
  
  
 }

 void readport5data()
 {
  port5enable=readjsonpara("/port5.json","enable_status");Serial.println(port5enable);
  port5pin=readjsonpara("/port5.json","gpio");Serial.println(port5pin);
  port5control=readjsonpara("/port5.json","control");Serial.println(port5control);
  port5server=readjsonpara("/port5.json","server");Serial.println(port5server);
  port5mqtt_topic=readjsonpara("/port5.json","mqtt_topic");Serial.println(port5mqtt_topic);
  port5timer_type=readjsonpara("/port5.json","timer_type");Serial.println(port5timer_type);
  port5on_time=readjsonpara("/port5.json","on_time");Serial.println(port5on_time);
  port5off_time_duration=readjsonpara("/port5.json","off_time_duration");Serial.println(port5off_time_duration);
  port5days=readjsonpara("/port5.json","days");Serial.println(port5days);
  port5speed=readjsonpara("/port5.json","speed");Serial.println(port5speed);
  port5type_of_pin=readjsonpara("/port5.json","type_of_pin");Serial.println(port5type_of_pin);
  port5connected_device=readjsonpara("/port5.json","connected_device");Serial.println(port5connected_device);
  port5area=readjsonpara("/port5.json","area");Serial.println(port5area);
  port5=port5pin.toInt();
  if (port5type_of_pin=="Switch")
  {
  pinMode(port5, OUTPUT);
  }
 }
 
 void readport6data()
 {
  port6enable=readjsonpara("/port6.json","enable_status");Serial.println(port5enable);
  port6pin=readjsonpara("/port6.json","gpio");Serial.println(port5pin);
  port6control=readjsonpara("/port6.json","control");Serial.println(port5control);
  port6server=readjsonpara("/port6.json","server");Serial.println(port5server);
  port6mqtt_topic=readjsonpara("/port6.json","mqtt_topic");Serial.println(port5mqtt_topic);
  port6timer_type=readjsonpara("/port6.json","timer_type");Serial.println(port5timer_type);
  port6on_time=readjsonpara("/port6.json","on_time");Serial.println(port5on_time);
  port6off_time_duration=readjsonpara("/port6.json","off_time_duration");Serial.println(port5off_time_duration);
  port6days=readjsonpara("/port6.json","days");Serial.println(port5days);
  port6speed=readjsonpara("/port6.json","speed");Serial.println(port6speed);
  port6type_of_pin=readjsonpara("/port6.json","type_of_pin");Serial.println(port6type_of_pin);
  port6connected_device=readjsonpara("/port6.json","connected_device");Serial.println(port6connected_device);
  port6area=readjsonpara("/port6.json","area");Serial.println(port6area);
  port6=port6pin.toInt();
  if (port6type_of_pin=="Switch")
  {
  pinMode(port6, OUTPUT);
  }
 }

 void startintopic()
 {
  if(port1enable=="Enable")
  {
    if (port1control=="Server" && port1server=="MQTT")
    {
      client.subscribe(port1mqtt_topic.c_str());
    }
    }
   if(port2enable=="Enable")
  {
    if (port2control=="Server" && port2server=="MQTT")
    {
      client.subscribe(port2mqtt_topic.c_str());
    }
    }
   if(port3enable=="Enable")
  {
    if (port3control=="Server" && port3server=="MQTT")
    {
      client.subscribe(port3mqtt_topic.c_str());
    }
    }
   if(port4enable=="Enable")
  {
    if (port4control=="Server" && port4server=="MQTT")
    {
      client.subscribe(port4mqtt_topic.c_str());
    }
    }
  if(port5enable=="Enable")
  {
    if (port5control=="Server" && port5server=="MQTT")
    {
      client.subscribe(port5mqtt_topic.c_str());
    }
    }
  }

 void startintopic1()
 {
  if(port1enable=="Enable")
  {
    if (port1control=="Server" && port1server=="MQTT")
    {
      client1.subscribe(port1mqtt_topic.c_str());
    }
    }
   if(port2enable=="Enable")
  {
    if (port2control=="Server" && port2server=="MQTT")
    {
      client1.subscribe(port2mqtt_topic.c_str());
    }
    }
   if(port3enable=="Enable")
  {
    if (port3control=="Server" && port3server=="MQTT")
    {
      client1.subscribe(port3mqtt_topic.c_str());
    }
    }
   if(port4enable=="Enable")
  {
    if (port4control=="Server" && port4server=="MQTT")
    {
      client1.subscribe(port4mqtt_topic.c_str());
    }
    }
  if(port5enable=="Enable")
  {
    if (port5control=="Server" && port5server=="MQTT")
    {
      client1.subscribe(port5mqtt_topic.c_str());
    }
    }
  }
 
