#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

// Defining size, and output pins
#define MAX_DEVICES 4
#define CS_PIN 5

#define MESSAGE_SIZE 41
#define MESSAGE_NUMBER 50

#define BRIGHTNESS 8 //choose 0-15

char messages[MESSAGE_NUMBER][MESSAGE_SIZE];  //Holds messages to host
bool approved[MESSAGE_NUMBER];            //Holds which messages are approved

int messageCount = 0;
int curMessage = 0;

MD_Parola Display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void displaySetup() {
  Display.begin();
  Display.setIntensity(BRIGHTNESS);
  Display.displayClear();
  Display.displayScroll("Graduation!!!", PA_RIGHT, PA_SCROLL_LEFT, 150);
}
void refresh(){     //runs ever loop()
  if (Display.displayAnimate()) {   //if scroll animation is done
    int counter = 0;    //prevents infinite loop if no approved messages exist
    while (approved[curMessage % min(messageCount, 30)] != true && counter <= MESSAGE_NUMBER){    //finds next approved message
      curMessage = (curMessage+1)%min(messageCount,30);
      counter++;
    }
    if (counter <= MESSAGE_NUMBER){
      Display.displayScroll(messages[curMessage], PA_RIGHT, PA_SCROLL_LEFT, 150);
      curMessage = (curMessage+1)%min(messageCount, 30);
      Display.displayReset();
    }
    else{
      Serial.println(approved[0]);
      Serial.println("no message found");
    }
   
    /*for(int i = 0; i < messageCount; i++){
      Serial.println(messages[i]);
    }*/
  }
}

void addMessage(char message[MESSAGE_SIZE]){                  //add new message to array, is set unnaproved
  strcpy(messages[messageCount % MESSAGE_NUMBER], message);
  approved[messageCount % MESSAGE_NUMBER] = false;
  messageCount++;
}

int min(int a, int b){
  if (a < b)
    return a;
  return b;
}
void approve(int number){         //approves a message based on index
  if (number >= 0 && number < MESSAGE_NUMBER && !approved[number])
    approved[number] = true;
  else if (number >= 0 && number < MESSAGE_NUMBER)
    approved[number] = false;
}


unsigned char h2int(char c)   //urldecode helper
{
    if (c >= '0' && c <='9'){
        return((unsigned char)c - '0');
    }
    if (c >= 'a' && c <='f'){
        return((unsigned char)c - 'a' + 10);
    }
    if (c >= 'A' && c <='F'){
        return((unsigned char)c - 'A' + 10);
    }
    return(0);
}

String urldecode(String str)            //conert url symbols like %20 or whatever to their associated characters
{
    
    String encodedString="";
    char c;
    char code0;
    char code1;
    for (int i =0; i < str.length(); i++){
        c=str.charAt(i);
      if (c == '+'){
        encodedString+=' ';  
      }else if (c == '%') {
        i++;
        code0=str.charAt(i);
        i++;
        code1=str.charAt(i);
        c = (h2int(code0) << 4) | h2int(code1);
        encodedString+=c;
      } else{
        
        encodedString+=c;  
      }
      
      yield();
    }
    
   return encodedString;
}
