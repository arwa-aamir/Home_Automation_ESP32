#include <WiFi.h>  // esp32 library
#include <IOXhop_FirebaseESP32.h> // firebase library 
#define FIREBASE_HOST "home-auto-68ecd.firebaseio.com"  //Your Firebase //Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "Nd9I75WwCuUWeCXvKCkwdZKNVfa4lxpgqm7RqvfC"
//Your Firebase Database Secret goes here
#define WIFI_SSID "PinkPanther"  //your WiFi SSID for which yout NodeMCU connects
#define WIFI_PASSWORD "AFA123E185"    //Password of your wifi network 
String fireStatus1 = ""; // led status received from firebase 
String fireStatus2 = "";
String fireStatus3 = "";
String fireStatus4 = "";
String fireStatus5 = "";
int fanspeed;
const int water_sensor = 2;  //D4
int k;


// defines variables
long duration;
int distance;


void setup() { 
  Serial.begin(9600); 
  pinMode(water_sensor, INPUT); // Sets the echoPin as an Input
  
  pinMode(12, OUTPUT); 
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT); 
  pinMode(15, OUTPUT);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); //try to connect with wifi
  Serial.print("Connecting to "); 
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) { Serial.print(".");
  delay(500);
}
Serial.println();
Serial.print("Connected to ");

Serial.println(WIFI_SSID); 
Serial.print("IP Address is : ");
Serial.println(WiFi.localIP());  //print local IP address

Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); // connect to firebase

Firebase.setString("LED1", "0");  //send initial string of led status 
Firebase.setString("LED2", "0");
Firebase.setString("LED3", "0");  //send initial string of led status 
Firebase.setString("LED4", "0");
}

void loop() {
  
k=digitalRead(water_sensor);
fireStatus4 = Firebase.getString("LED4");
if (fireStatus4 == "1") {  // compare the input of led status received from firebase

if(k==LOW)
{
  digitalWrite(15, LOW);  // make output led ON
  Serial.println("Led4 Turned ON");
}
else
{
  digitalWrite(15,HIGH);  // make output led OFF
  Serial.println("Led4 Turned OFF");
}

}

else if (fireStatus4 == "0") {  // compare the input of led status received from firebase

Serial.println("Led4 Turned OFF");

digitalWrite(15, HIGH); // make output led OFF

}


else {

Serial.println("Wrong Credential for LED4! Please send ON/OFF");
}

fireStatus1 = Firebase.getString("LED1");  // get led status input from firebase
fireStatus2 = Firebase.getString("LED2");  // get led status input from firebase
fireStatus3 = Firebase.getString("LED3");  // get led status input from firebase
fireStatus5 = Firebase.getString("FANSPEED");


if (fireStatus1 == "1") {  // compare the input of led status received from firebase

Serial.println("Led1 Turned ON");

digitalWrite(12, LOW);  // make output led ON

}

else if (fireStatus1 == "0") { // compare the input of led status received from firebase

Serial.println("Led1 Turned OFF");

digitalWrite(12, HIGH); // make output led OFF

}

else {

Serial.println("Wrong Credential for LED1! Please send ON/OFF");

}


if (fireStatus2 == "1") {  // compare the input of led status received from firebase

Serial.println("Led2 Turned ON");

digitalWrite(13, LOW);  // make output led ON

}

else if (fireStatus2 == "0") {  // compare the input of led status received from firebase

Serial.println("Led2 Turned OFF");

digitalWrite(13, HIGH); // make output led OFF

}
else {

Serial.println("Wrong Credential for LED2! Please send ON/OFF");

}




if (fireStatus3 == "1") {  // compare the input of led status received from firebase

Serial.println("Led3 Turned ON");

digitalWrite(14, LOW);  // make output led ON

}

else if (fireStatus3 == "0") {  // compare the input of led status received from firebase

Serial.println("Led3 Turned OFF");
Serial.println("FAN SPEED IS:");
fanspeed=fireStatus5.toInt();
Serial.println(fanspeed);

digitalWrite(14, HIGH); // make output led OFF

}
else {

Serial.println("Wrong Credential for LED3! Please send ON/OFF");

}

}
