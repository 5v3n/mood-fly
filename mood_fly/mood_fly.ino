// (Based on Ethernet's WebClient Example)

#include "WiFly.h"
#include "Credentials.h"

#define RGB_LED_RedPin 6
#define RGB_LED_GreenPin 3
#define RGB_LED_BluePin 5


Client client("data.tweetsentiments.com", 8080);
byte red = 0, blue= 0, green = 0;

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
  char sum=0, led_red=0, led_green=0, led_blue=0;
  if (client.available()) {
    
    if(client.find("neutral\":")){
      char buf[4];
      client.readBytes(buf, 3);
      blue = atoi(buf);
      Serial.println();
      Serial.print("blue: ");
      Serial.println(blue);
    }
    
    if(client.find("positive\":"))
    {
      char buf[4];
      client.readBytes(buf, 3);
      green=atoi(buf);
      Serial.println();
      Serial.print("green: ");
      Serial.println(green);   
    }
 
    if(client.find("negative\":"))
    {
      char buf[4];
      client.readBytes(buf, 3);
      red = atoi(buf);
      Serial.println();
      Serial.print("red: ");
      Serial.println(red);
    }
    
    client.stop();
    
    sum = red+green+blue;
    if (sum != 0){    
      led_red = (255*(red*1.0/sum));
      led_green = (255*(green*1.0/sum));
      led_blue = (255*(blue*1.0/sum));
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
    client.println("GET /api/search.json?topic=fail HTTP/1.0");
    client.println();
    delay(1000);
  } else {
    Serial.println("connection failed");
  }
  }
}


