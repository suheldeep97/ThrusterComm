/*  
 *  Refer the binary codes for speed and
 *  0000 is universal acknowledgement signal
 *  handshake signal binary(int) 0000 sent from the arduino
 *  handshake signal binary(int) 1111 sent from the computer
 *  0101 full thrust forward
 *  0111 right turn
 *  1101 left turn
 *  0001 stop
 *  
 *  As of now the universal codes havn't been implemented yet.
 *  Arduino starts sending 0 on startup
 *  Contact is established when Computer sends 0
 *  
 *  1-Start 
 *  2-Stop
*/
int ledPin=13;
int incomingData=0;

void setup() 
{
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  establishContact();
  while(!Serial);
}

void loop()
{
  while(Serial.available() == 0) ;

  incomingData=Serial.read();
  if(incomingData == '1')
  {
    digitalWrite(ledPin, HIGH);
    Serial.println(incomingData-'0');
    Serial.println("ON");
    Serial.write(0000);
  }
  else if(incomingData == '2')
  {
    digitalWrite(ledPin, LOW);
    Serial.println(incomingData-'0');
    Serial.println("OFF");
    Serial.write(0000);
  }
  incomingData=-1;
  Serial.flush();
}

void establishContact()
{
  int lastTime=millis();
  int currentTime=millis();
  int pinState=LOW;
  while(Serial.read()!= '0')
  {
      Serial.println(0);
      Serial.flush();
      currentTime=millis();
      if(currentTime-lastTime >= 500)
      {
        lastTime=millis();
        digitalWrite(ledPin,pinState);
        pinState=(pinState==HIGH)?LOW:HIGH;//Switches between HIGH and LOW
      }
  }
  Serial.println(0);
  Serial.println("ESTABLISHED CONTACT");
  Serial.flush();
}
