#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
 
#define ssid      "nova 5"       //WIFI name of the device in the current environment
#define password  "10061006"     //WIFI password of the device in the current environment
 
WiFiUDP Udp;//Instantiating WiFi UDP objects
unsigned int localUdpPort = 1234;  // Customize the local listening port
unsigned int remoteUdpPort = 4321;  // Customize the remote listening port
char incomingPacket[255];  // Save messages sent by the Udp tool

String str = "press";
int count = 0;
 
void setup()
{
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // Turn off LED 
  Serial.begin(9600);//Open serial port
  
  WiFi.begin(ssid, password);//Link to Wi-Fi
  while (WiFi.status() != WL_CONNECTED)//Wait for connection
  {
    delay(500);
//    Serial.print(".");
  }
//  Serial.println("Successful link");
 
  if(Udp.begin(localUdpPort)){//Start Udp listening service
//    Serial.println("Successful Listen");
    //Print the local ip address, which will be used in the UDP tool
    //WiFi.localIP().toString().c_str() Used to convert the obtained local IP address into a string    
//    Serial.printf("Listening to IP：%s, UDP port：%d\n", WiFi.localIP().toString().c_str(), localUdpPort);
  }else{
//    Serial.println("Failed Listen");
  }
}
 
void loop()
{
  while (Serial.available()) {
    char ch = Serial.read();
    if(ch == str[count]){
      count ++;
      if(count == 5){
        sendCallBack("press");
        count = 0;
      }
    }else{
      count = 0;
    }
  }
  
  //Parsing Udp packets
  int packetSize = Udp.parsePacket();//Get the parsing package
  if (packetSize)//Parse package is not empty
  {
    //Udp packet received
    //Udp.remoteIP().toString().c_str()Used to convert the obtained remote IP address into a string
//    Serial.printf("From Remote IP：%s（port：%d）的数据包字节数：%d\n", Udp.remoteIP().toString().c_str(), Udp.remotePort(), packetSize);
      
    // Read Udp packets and store them incomingPacket
    int len = Udp.read(incomingPacket, 255);//Return the number of packet bytes
    if (len > 0)
    { 
      incomingPacket[len] = 0;//Clear cache
//      Serial.printf("UDP mainbody: %s\n", incomingPacket);//Print information to the serial port
 
      //strcmp函数是string compare(字符串比较)的缩写，用于比较两个字符串并根据比较结果返回整数。
      //基本形式为strcmp(str1,str2)，若str1=str2，则返回零；若str1<str2，则返回负数；若str1>str2，则返回正数。
      
      if (strcmp(incomingPacket, "LED_OFF") == 0) // LED_OFF  
      {  
        digitalWrite(LED_BUILTIN, HIGH); // Turn off LED  
        sendCallBack("LED has been turn off\n");  
      }  
      else if (strcmp(incomingPacket, "LED_ON") == 0) // LED_ON  
      {  
        digitalWrite(LED_BUILTIN, LOW); // Turn on LED  
        sendCallBack("LED has been turn on\n"); 
      }
      else if (strncmp(incomingPacket, "m:",2) == 0){
        String temp = "m";
        for(int i=2; i<strlen(incomingPacket); i++){
          temp+=(incomingPacket[i]);
        }
        temp+="\n";
        Serial.println(temp);
      }
      else if (strncmp(incomingPacket, "d:",2) == 0){
        String temp = "d";
        int len = 9;
        for(int i=2; i<len; i++){
          if(strlen(incomingPacket)>i)
            temp+=(incomingPacket[i]);
          else
            temp+=" ";
        }
        Serial.println(temp);
        temp = "";
      }
      else // If the command is wrong, call sendCallBack
      {  
      }  
    }
  }
}
 
//Send messages to udp tools
void sendCallBack(const char *buffer)
{  
  Udp.beginPacket(Udp.remoteIP(), remoteUdpPort);//Configure remote ip address and port
  Udp.write(buffer); //Write data to the transmit buffer
  Udp.endPacket(); //Send data 
}
