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
 *  WARNING! Unstable Version
*/
int ledPin=13;
int incomingData=0;
int acknowledgement[]={0,0,0,0};
int fullThrustForward[]={0,1,0,1};
int rightTurn[]={0,1,1,1};
int leftTurn[]={1,1,0,1};
int stopSignal[]={0,0,0,1};

void setup() 
{
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  establishContact();
  while(!Serial);
}

void loop()
{
  while(Serial.available() != 4) ;

  incomingData=Serial.read();
  if(incomingData == '1')
  {
    digitalWrite(ledPin, HIGH);
    Serial.println(incomingData-'0');
    Serial.println("ON");
    sendAcknowledgement();
  }
  else if(incomingData == '2')
  {
    digitalWrite(ledPin, LOW);
    Serial.println(incomingData-'0');
    Serial.println("OFF");
    sendAcknowledgement();
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
      sendAcknowledgement();
      Serial.flush();
      currentTime=millis();
      if(currentTime-lastTime >= 500)
      {
        lastTime=millis();
        digitalWrite(ledPin,pinState);
        pinState=(pinState==HIGH)? LOW : HIGH;//Switches between HIGH and LOW
      }
  }
  sendAcknowledgement();
  Serial.println("ESTABLISHED CONTACT");
  Serial.flush();
}

void sendAcknowledgement()
{
  Serial.write(acknowledgement,4);
  printAcknowledgement();
}

void printAcknowledgement()
{
  Serial.println("0000");
}

