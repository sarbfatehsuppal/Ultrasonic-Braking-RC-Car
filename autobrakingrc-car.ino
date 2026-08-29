int distance;
long duration;
int motorSpeed;
const int trigPin=10;
const int echoPin=11;
const int motorPin=9;
const int stopDistance=10;
const int restartDistance=15;
const int slowDistance=30;
const int mediumDistance=50;

bool stopped=false;

void setup()
{
pinMode(motorPin,OUTPUT);
pinMode(echoPin,INPUT);
pinMode(trigPin,OUTPUT);
Serial.begin(9600);
}

void loop()
{
distance=calculateDistance();
Serial.println(distance);

if(distance==-1)
{
  motorSpeed=0;
  stopped=true;
  analogWrite(motorPin,motorSpeed);
  return;
}

if(stopped){
  if(distance>restartDistance)
  {
    stopped=false;
  }
  else{
    analogWrite(motorPin,0);
    return;
   }
  }

  if(distance>mediumDistance){
    motorSpeed=255;
  }
  else if(distance>slowDistance){
    motorSpeed=170;
  }
  else if(distance>stopDistance){
    motorSpeed=140;
  }
  else{
    motorSpeed=0;
    stopped=true;
  }
  analogWrite(motorPin,motorSpeed);
}

int calculateDistance(){
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration=pulseIn(echoPin,HIGH,30000);

  if(duration==0){
    return -1;
  }

  distance=duration*0.034/2;
  return distance;
}