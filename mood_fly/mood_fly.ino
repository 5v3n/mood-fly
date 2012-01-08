// (Based on Ethernet's WebClient Example)

#include "WiFly.h"
#include "Credentials.h"

#define RGB_LED_RedPin 6
#define RGB_LED_GreenPin 3
#define RGB_LED_BluePin 5


Client client("query.yahooapis.com", 80);
byte red = 0, blue= 0, green = 0;
char led_red=0, led_green=0, led_blue=0;

void setup() { 
  Serial.begin(9600);

  WiFly.begin();
  
  if (!WiFly.join(ssid, passphrase)) {
    Serial.println("Association failed.");
    while (1) {
      // Hang on failure.
    }
  }   
}

void loop() {
  char sum=0;
  boolean valueFound = false;
  if (client.available()) {
    
    if(client.find("positive\":\""))
    {
      valueFound = true;
      char buf[4];
      client.readBytes(buf, 3);
      green=atoi(buf);
      Serial.println();
      Serial.print("green: ");
      Serial.println(green);   
    }

    if(client.find("negative\":\""))
    {
      valueFound = true;
      char buf[4];
      client.readBytes(buf, 3);
      red = atoi(buf);
      Serial.println();
      Serial.print("red: ");
      Serial.println(red);
    }
    
    if(client.find("neutral\":\"")){
      valueFound = true;
      char buf[4];
      client.readBytes(buf, 3);
      blue = atoi(buf);
      Serial.println();
      Serial.print("blue: ");
      Serial.println(blue);
    }
    
    client.stop();
    
    if(valueFound){
    sum = red+green+blue;
    if (sum != 0){    
      led_red = (255*(red*1.0/sum));
      led_green = (255*(green*1.0/sum));
      led_blue = (255*(blue*1.0/sum));
    }
    }
    
     // set the brightness of the LED:
     analogWrite(RGB_LED_RedPin, 255-led_red);
     analogWrite(RGB_LED_GreenPin, 255-led_green);
     analogWrite(RGB_LED_BluePin, 255-led_blue);
    

  }
  
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    Serial.println("red:");
    Serial.println((byte)led_red);
    Serial.println("green:");
    Serial.println((byte)led_green);
    Serial.println("blue:");
    Serial.println((byte)led_blue);
    Serial.println();
    Serial.println("connecting...");

  if (client.connect()) {
    Serial.println("connected");

    char topicToAnalyze[] = "fail";

    String request = "GET ";
    //use yahoo yql web api to do the numbercrunching - arduino is too slow to process tweet sentiments results locally (70s+)
    request += "http://query.yahooapis.com/v1/public/yql?q=SELECT%20positive,%20negative,%20neutral%20FROM%20json%20WHERE%20url%20%3D%20%22http://data.tweetsentiments.com:8080/api/search.json%3Ftopic%3D";
    request += topicToAnalyze;
    request += "%22&format=json";
    request += " HTTP/1.0";
    Serial.println( request );
    // do the HTTP GET request
    client.println( request );		
    client.println();
 
  } else {
    Serial.println("connection failed");
  }
  }
}


