/*
ESP32 Hat Project - A 32x8 matrix LED display hosting a styled webpage allowing others to connect and add messages. Also includes proctoring capabilities
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <DNSServer.h>
#include "Display.h"
#include "HTML.h"

#define PROCTOR_CODE "DuckySecret"

const char *ssid = "AndrewsHat";
const char *password = "SuperSecret";

const byte DNS_PORT = 53;
IPAddress apIP(8,8,4,4); // The default android DNS
DNSServer dnsServer;
WiFiServer server(80);

void setup() {

  displaySetup();

  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  // a valid password must have more than 7 characters
  if (!WiFi.softAP(ssid, password)) {
    log_e("Soft AP creation failed.");
    while(1);
  }
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  dnsServer.start(DNS_PORT, "*", apIP);

  server.begin();

  Serial.println("Server started");

  addMessage("GRADUATION!");
  approve(0);
  addMessage("Hi, I'm Andrew");
  approve(1);
  addMessage("Go Cal!");
  approve(2);
  addMessage(":):):)");
  approve(3);
  addMessage("Berkeley!");
  approve(4);
  addMessage("Hi Mom! Hi Dad!");
  approve(5);


}
void loop() {
  refresh();
  dnsServer.processNextRequest();
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      refresh();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        //Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:

            //client.println("HTTP/1.1 200 OK");
            //client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            Serial.println("currentLine: " + currentLine);
            processLine(currentLine, client);
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":

      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}

//Get the submit message parameter
void processLine(String currentLine, WiFiClient client){
    if (currentLine.startsWith("GET /proctoring/approval")){
        String message = "";
        bool found = false;
        for(int i=currentLine.length()-9; i > 0; i--){    //9 is length of HTTP/1.1
          if (currentLine[i] == '='){
            found = true;
            break;
          }
          else{
            message = currentLine[i] + message;
          }
        }
        if (found){
          approve(message.toInt());
          for (int i = 0; i < messageCount && i < 30; i++){
            client.print("<p>" + String(i) + ". " + String(messages[i]) + " " + String(approved[i]) + "</p>");
          }
          client.print(messages_html);

        }
    }
    else if (currentLine.startsWith("GET /resume")){
      client.println(resume_html);
    }
    else if (currentLine.startsWith("GET /proctoring")){
        String message = "";
        bool found = false;
        for(int i=currentLine.length()-9; i > 0; i--){    //9 is length of HTTP/1.1
          if (currentLine[i] == '='){
            found = true;
            break;
          }
          else{
            message = currentLine[i] + message;
          }
        }
        Serial.println(sizeof(PROCTOR_CODE));
        if (found && (message.substring(0,sizeof(PROCTOR_CODE)-1)).equals(PROCTOR_CODE)){
          for (int i = 0; i < messageCount && i < 30; i++){
            client.print("<p>" + String(i) + ". " + String(messages[i]) + " " + String(approved[i]) + "</p>");
          }
          client.print(messages_html); 
        }
        else{
          client.println(proctor_html);
        }
    }
    else if (currentLine.endsWith(" HTTP/1.1")) {
            Serial.println("found GET line");
            String message = "";
            bool found = false;
            for(int i=currentLine.length()-9; i > 0; i--){    //9 is length of HTTP/1.1
              if (currentLine[i] == '='){
                found = true;
                break;
              }
              else{
                message = currentLine[i] + message;
              }
            }
            if (found && message.length() > 0){
            message = urldecode(message);
            Serial.println("message: " + message);
            if (message.length() < 41 && message.length() > 1)
              addMessage(&message[0]);
            }
            client.print(index_html);
            Serial.println("rendered index");
          }
}
