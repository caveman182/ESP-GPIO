

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

/////////////////////////////////////////////////////////////////////////////////This code takes an active high or low on pin input GPIO 14 even though the code says input 5!!


//int BUTTON_PIN = D2; //button is connected to GPIO pin D1
int BUTTON_PIN = D5; //button is connected to GPIO pin D1
// Update these with values suitable for your network.
const char* ssid = "your-ssid";//put your wifi ssid here
const char* password = "your-password";//put your wifi password here.
const char* mqtt_server = "192.168.x.x";


WiFiClient esp01;
PubSubClient client(esp01);
long lastMsg = 0;
char msg[50];

void setup_wifi() {
   delay(100);
  // We start by connecting to a WiFi network
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) 
{
  
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    //if you MQTT broker has clientID,username and password
    //please change following line to    if (client.connect(clientId,userName,passWord))
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
     //once connected to MQTT broker, subscribe command if any
      client.subscribe("lounge");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);

  pinMode(BUTTON_PIN,INPUT);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();
  int status;
  //send message every 2 second
  if (now - lastMsg > 2000) {
     lastMsg = now;
     status=digitalRead(BUTTON_PIN);
     String msg="Button status: ";
     if(status==HIGH )
     {
        
        msg="on";
        delay(100);
       char message[58];
       msg.toCharArray(message,58);
       Serial.println(message);
       //publish sensor data to MQTT broker
      client.publish("lounge", message);
       }
     else
     {
      
      msg="off";
       char message[58];
       msg.toCharArray(message,58);
       Serial.println(message);
       //publish sensor data to MQTT broker      
      client.publish("lounge", message);
     }
    }
     
}

//////////// delete the below code if it doesn't work//////////////


// Lamp - LED - GPIO 4 = D2 on ESP-12E NodeMCU board
const int lamp = 4;
////////new code below
//const int pin5input = 5;


void Setup()
{
/////////////////////////////////////////////////////////////pinMode (pin5input,INPUT);
}

/////////new code above
// Timers auxiliar variables
long now = millis();
long lastMeasure = 0;

// Don't change the function below. This functions connects your ESP8266 to your router
/*///////////////////////////////////////////////////////////////////////////////////////////////////////void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
}
*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// This functions is executed when some device publishes a message to a topic that your ESP8266 is subscribed to
// Change the function below to add logic to your program, so when a device publishes a message to a topic that 
// your ESP8266 is subscribed you can actually do something
void callback(String topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic room/lamp, you check if the message is either on or off. Turns the lamp GPIO according to the message
  //if(topic=="lamp"){
  //    Serial.print("Changing lamp to ");
  //    if(messageTemp == "on"){
  //      digitalWrite(lamp, HIGH);
  //      Serial.print("On");
  //    }
  //    else if(messageTemp == "off"){
  //      digitalWrite(lamp, LOW);
  //      Serial.print("Off");
  //    }
//  }
//  Serial.println();
//}

if(topic=="lamp"){
      Serial.print("Changing lamp to ");
      if(messageTemp == "on"){
        digitalWrite(lamp, HIGH);
        Serial.print("On");
      }
      else if(messageTemp == "off"){
        digitalWrite(lamp, LOW);
        Serial.print("Off");
      }
  }
  Serial.println();
}


