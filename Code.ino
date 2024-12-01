#include <WiFi.h>
#include <WiFiClient.h> 
#include <WebServer.h> 
#include <ESPmDNS.h>

int aye;
const int buzzer = 5;
const char *ssid = "Vishnu";
const char *password = "vishnu123"; WebServer server(80);

void handleRoot() { 
  char msg[1500];
  snprintf(msg, 1500,
 "<html>\
  <head>\
<meta http-equiv='refresh' content='2'/>\
<meta name='viewport' content='width=device-width, initial-scale=1'>\
<link rel='stylesheet'
href='https://use.fontawesome.com/releases/v5.7.2/css/all
.css'
integrity='sha384-
fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9R whKkMHpvLbHG9Sr' crossorigin='anonymous'>\
<title>FLAME DETECTOR - ESP 32</title>\
<style>\
html { font-family: Arial; display: inline-block; margin: 0px auto; text-align: center;}\
h2 { font-size: 3.0rem; }\ p { font-size: 3.0rem; }\
.units { font-size: 1.2rem; }\
.dht-labels{ font-size: 1.5rem; vertical-align:middle; padding-bottom: 15px;}\
</style>\
</head>\
<body>\
<h2>FLAME DETECTOR - ESP32</h2>\
 
<h4> by Vishnu Sai</h4>\
<p>\
<i class='fas fa-thermometer-half' style='color:#ca3517;'></i>\
<span class='dht-labels'>FLAME</span>\
<span>%.2f</span>\
</p>\
</body>\
</html>", getflame()
);
server.send(200, "text/html", msg);
}

void setup(void) {
  pinMode(buzzer, OUTPUT);
  pinMode(36, INPUT); //initialize Flame sensor output pin connected pin as input.
  pinMode(LED_BUILTIN, OUTPUT);// initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
 
  WiFi.begin(ssid, password); 
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to "); 
  Serial.println(ssid);
  Serial.print("IP address: "); 
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) 
{ 
  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks 
  aye = analogRead(36);
  if(aye < 800){
    Serial.println("Fire"); digitalWrite(5, HIGH);
  }
  else{
    Serial.println("No fire"); digitalWrite(5, LOW);
  }
  delay(1000);
}

float getflame() { 
  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks 
  aye = analogRead(36);
  if(aye < 800){
    Serial.println("Fire"); return 1;
  }
  else{
    Serial.println("No fire"); return 0;
  }
}
