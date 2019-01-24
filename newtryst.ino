//this is a right following robot
const int motorOne1=9;//left motor foward
const int motorOne2=8;//left motor back
const int motorTwo1=7;
const int motorTwo2=6;
const int motorOneSpeed = 10;
const int motorTwoSpeed = 5;
//A3 is reverse logic
const int IR[4]={A1,A2,A3,A4,A5};
//this shitty setup has a reverse logic IR -A4 
int val[5];
char path[200];
int top=0;
//new variables
int zone=1;
int o=0;
int i=1;

void setup() {
  pinMode(motorOne1,OUTPUT);
  pinMode(motorOne2,OUTPUT);
  pinMode(motorTwo1,OUTPUT);
  pinMode(motorTwo2,OUTPUT);
  pinMode(motorOneSpeed,OUTPUT);
  pinMode(motorTwoSpeed,OUTPUT);
  for(int i=0; i<4; i++) {
    pinMode(IR[i],INPUT);
  }
  analogWrite(motorOneSpeed,150);
  analogWrite(motorTwoSpeed,150);
  Serial.begin(9600);
  delay(100);
  Serial.println("Setup Complete");
}
void loop()
{
    sense();
    if (val[0]==o);   //checking for left
        zone=0;
    
    if (val[4]==o)     //checking for right
    {   
        since=0;
        zone=4;
        while(val[4]==o && val[2]==o && val[0]==o && since<20) //checking for t-point
        {   
            sense();
            since+=1;
            forward(5);
        }
        if(since>20){
            Serial.println("we win");
            digitalWrite(13,HIGH);
            delay(10000);
        }
        
    }
    else if(val[2]==o && zone!=4)
    {
        zone=2;
        if (val[1]==o)   //nudging
        {
            analogWrite(motorOneSpeed,100);
            analogWrite(motorTwoSpeed,150);  //yeh right wali motor h
        }
        else
        {
            analogWrite(motorOneSpeed,150);  //yeh left wali motor h
            analogWrite(motorTwoSpeed,100);  
        }
        forward(5);
        analogWrite(motorOneSpeed,150);
        analogWrite(motorTwoSpeed,150)
        if(val[0]==o)
        {
            zone=0;
        }
    }
    else
    {
        if(zone==4)
        {
            turnRight(30);
            justRight();
        }
        if(zone==0)
        {
            turnLeft(30);
            justLeft();
        }
        if(zone==2)
        {
            turnBackward();
        }
        zone=2;
    }   
}
void turnBackward(){
    turnRight(50);
    justRight();
    path[top]='D';
    top+=1;


}


void justRight()
{
    while(!turnComp(1))
    {
        turnRight(5);
    }
    path[top]='R';
    top+=1;

}
void justLeft()
{
    while(!turnComp(3))
    {
        turnLeft(5);
    }
    path[top]='L';
    top+=1;
}
bool turnComp(int opp)
{
    sense();
    if (val[2]==o || val[opp]==o ){
        return true;
    }
    return false;
}
void sense()
{
  for(int i=0;i<5;i++)
      {
        val[i]=digitalRead(IR[i]);
        Serial.print(val[i]);
      }
      Serial.println();
      //this is a reverse sensor
      val[2]=val[2]+1;
      val[2]=val[2]%2;
}
void turnLeft(int turnTime) {
  Serial.println("Left");
  //right wheel backwards
  digitalWrite(motorOne1,LOW);
  digitalWrite(motorOne2,HIGH);
  //left wheel forward
  digitalWrite(motorTwo1,HIGH);
  digitalWrite(motorTwo2,LOW);
  //till left turn
  delay(turnTime);
  //all at rest
  digitalWrite(motorOne1,LOW);
  digitalWrite(motorOne2,LOW);
  digitalWrite(motorTwo1,LOW);
  digitalWrite(motorTwo2,LOW);
}
void turnRight(int turnTime) {
  Serial.println("Right");
  //right wheel forward
  digitalWrite(motorOne1,HIGH);
  digitalWrite(motorOne2,LOW);
  //left wheel backward
  digitalWrite(motorTwo1,LOW);
  digitalWrite(motorTwo2,HIGH);
  //till right turn
  delay(turnTime);
  //all at rest
  digitalWrite(motorOne1,LOW);
  digitalWrite(motorOne2,LOW);
  digitalWrite(motorTwo1,LOW);
  digitalWrite(motorTwo2,LOW);
}
void forward(int forwardTime) {
  Serial.println("Forward");
  //right wheel forward
  digitalWrite(motorOne1,HIGH);
  digitalWrite(motorOne2,LOW);
  //left wheel forward
  digitalWrite(motorTwo1,HIGH);
  digitalWrite(motorTwo2,LOW);
  //till
  delay(forwardTime);
  //all at rest
  digitalWrite(motorOne1,LOW);
  digitalWrite(motorOne2,LOW);
  digitalWrite(motorTwo1,LOW);
  digitalWrite(motorTwo2,LOW);
}
void backward(int backwardTime) {
  Serial.println("Backward");
  //right wheel backward
  digitalWrite(motorOne1,LOW);
  digitalWrite(motorOne2,HIGH);
  //left wheel backward
  digitalWrite(motorTwo1,LOW);
  digitalWrite(motorTwo2,HIGH);
  //till
  delay(backwardTime);
  //all at rest
  digitalWrite(motorOne1,LOW);
  digitalWrite(motorOne2,LOW);
  digitalWrite(motorTwo1,LOW);
  digitalWrite(motorTwo2,LOW);
}