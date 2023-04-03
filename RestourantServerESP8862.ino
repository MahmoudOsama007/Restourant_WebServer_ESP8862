#include<ESP8266WiFi.h>
#include<WiFiClinent.h>
#include<ESP8266WebServer.h>

//LCD 
#include<Wire.h>
#include<Liquidcrystal_I2C.h>
Liquidcrystal_I2C lcd(0x3f,16,2)

//Buzzer
#define table_1   D7 
#define table_2   D6
#define table_3   D5
#define table_4   D4



//wifi config
const char ssid[]="xxxxxxxxxxxxxxxxxxxxxx";
const char psasword[]="xxxxxxxxxxxxxxxxxxxxxx";

IPAddress serverIP(192,168,1,50);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

// create webserver
ESP8862WebServer server(80);

//web page
char temp[1300];
char htmlpage[1300]="<!DOCTYPE html>\
<html lang=\”en\”>\
<head>\
<title>Restourant</title>\
<meta charset=\”utf-8\”>\
<meta http-eqin=\"refresh\" content = \"5; url=http://192.168.1.50\"/>\
<meta name=\”viewport\” content=\”width=device-width, initial-scale=1\”>\
<link rel=\”stylesheet\” href=\”https://cdn.jsdelivr.net/npm/bootstrap@4.6.2/dist/css/bootstrap.min.css\”>\
<script src=\”https://cdn.jsdelivr.net/npm/jquery@3.6.3/dist/jquery.slim.min.js\”></script>\
<script src=\”https://cdn.jsdelivr.net/npm/popper.js@1.16.1/dist/umd/popper.min.js\”></script>\
<script src=\”https://cdn.jsdelivr.net/npm/bootstrap@4.6.2/dist/js/bootstrap.bundle.min.js\”></script>\
</head>\
<body>\
<div class=\”jumbotron text-center\”>\
<h1>My Restourant Page</h1>\
<p>short description for the Restourant!</p>\ 
</div>\
<div class=\”jumbotron text-center\”>\
<div class=\”btn-group-vertical\”>\
<a href=\”/?Table_1\” class=\”btn btn-success\" role=\”button\”>Table_1 Order Finish</a>\
<a href=\”/?Table_2\” class=\”btn btn-warning\" role=\”button\”>Table_2 Order Finish</a>\
<a href=\”/?Table_3\” class=\”btn btn-success\" role=\”button\”>Table_3 Order Finish</a>\
<a href=\”/?Table_4\” class=\”btn btn-warning\" role=\”button\”>Table_4 Order Finish</a>\
</div>\
</div>\
</body>\
</html>\";


void setup() {
  // put your setup code here, to run once:

WiFi.config(serverIP,gateway,subnet);
WiFi.begin(ssid,password);

//tabl_1
pinMode(tabl_1,OUTPUT);
digitalWrite(tabl_1,LOW);
//tabl_2
pinMode(tabl_2,OUTPUT);
digitalWrite(tabl_2,LOW);
//tabl_3
pinMode(tabl_3,OUTPUT);
digitalWrite(tabl_3,LOW);
//tabl_4
pinMode(tabl_4,OUTPUT);
digitalWrite(tabl_4,LOW);

// LCD INIT
lcd.init();
lcd.backlight();
lcd.clear();
lcd.print("Conecting...");
lcd.setCursor(0,1);
lcd.print(".");

//wait for connect
byte counter = 0;
while(WiFi.status != WL_CONNECTED){
  delay(500);
  counter++;
  lcd.setCursor(0,1);
  lcd.print(".");
}

// handle server page
server.on("\",handleRoot);
server.onNotFound(handleNotFound);

server.begin();
lcd.clear();
lcd.print("Server Started");
lcd.setCursor(0,1);
lcd.print(WiFi.localIP());



}


void loop() {
  // put your main code here, to run repeatedly:
server.handleClient();
}

void handleRoot(){
  
  // ************ tabl_1 ************
  
  if(server.argName(0)=="table_1"){
    digitalWrite(tabl_1,HIGH);
    lcd.print(" Your Order Is Finished ");
    delay(5000);
    digitalWrite(tabl_1,LOW);
    
    
    }
    
  // ************ tabl_2 ************
  
  if(server.argName(0)=="tabl_2"){
   digitalWrite(tabl_2,HIGH);
    lcd.print(" Your Order Is Finished ");
    delay(5000);
    digitalWrite(tabl_2,LOW);
    }
    
    // ************ tabl_3 ************
    
    if(server.argName(0)=="tabl_3"){
    digitalWrite(tabl_3,HIGH);
    lcd.print(" Your Order Is Finished ");
    delay(5000);
    digitalWrite(tabl_3,LOW);
    
    }

   // ************ tabl_4 ************
   
    if(server.argName(0)=="tabl_4"){
    
    digitalWrite(tabl_4,HIGH);
    lcd.print(" Your Order Is Finished ");
    delay(5000);
    digitalWrite(tabl_4,LOW);
    
    
    }
  
  }

void handleNotFound(){
  
  server.send(404,"text/html","<h1>Page Not Found</h1>");
  
  
  
  
  }
