const int motorOne1=9;//left motor foward
const int motorOne2=8;//left motor back
const int motorTwo1=7;
const int motorTwo2=6;
const int motorOneSpeed = 10;
const int motorTwoSpeed = 5;
//A3 is reverse logic
const int IR[5]={A1,A2,A3,A4,A5};
//this shitty setup has a reverse logic IR -A3 
int val[5];
void setup() {
  pinMode(motorOne1,OUTPUT);
  pinMode(motorOne2,OUTPUT);
  pinMode(motorTwo1,OUTPUT);
  pinMode(motorTwo2,OUTPUT);
  pinMode(motorOneSpeed,OUTPUT);
  pinMode(motorTwoSpeed,OUTPUT);
  analogWrite(motorOneSpeed,150);
  analogWrite(motorTwoSpeed,150);
  Serial.begin(9600);
  delay(100);
}
void loop() {
  moveForward(3000);
}
void moveForward(int forwardTime)
{
  int zone=2;
  for(int t=0;t<forwardTime;t=t+10)
  {
      for(int i=0;i<5;i++)
      {
        val[i]=digitalRead(IR[i]);
        //because that fuckall shitty reverse sensor
        val[2]=val[2]+1;
        val[2]=val[2]%2;
        Serial.print(val[i]); 
      }
      Serial.println();
      Serial.println(zone);
      if(val[0]==0)
      {
        Serial.println("entered");
        //there may be a path towards left
        forward(5);
        zone=0;
        for(int i=0;i<5;i++)
        {
          val[i]=digitalRead(IR[i]);
          //because that fuckall shitty reverse sensor
          val[2]=val[2]+1;
          val[2]=val[2]%2;
        }
        if (val[0]==0 && val[4]==0)
        {
          digitalWrite(13,HIGH);
          Serial.println("win");
        }
        else
        {
          turnRight(10);
          int t=0;
          while(t==0)
          {
            turnRight(5);
            for(int i=0;i<5;i++)
            {
              val[i]=digitalRead(IR[i]);
              //because that fuckall shitty reverse sensor
              val[2]=val[2]+1;
              val[2]=val[2]%2;
            }
            for(int i=0;i<5;i++){
              Serial.print(val[i]);
            }
            Serial.println();
            if (val[2]==0 || val[1]==0 || val[3]==0)
            { 
              t=1;
              if(val[1]==0)
              zone=1;
              else if (val[3]==0)
              zone=3;
              else{
                Serial.println("this does get entered");
                zone=2; 
              }
              
              //move forward
              forward(20);
            }
          }
        }
      } 
      else if(val[4]==0)
      {
        zone=4;
        //there may be a path towards right
        forward(5);
        for(int i=0;i<5;i++)
        {
          val[i]=digitalRead(IR[i]);
          //because that fuckall shitty reverse sensor
          val[2]=val[2]+1;
          val[2]=val[2]%2;
        }
        if (val[0]==0 && val[4]==0)
        {
          digitalWrite(13,HIGH);
          Serial.println("win");
        }
        else
         {
            turnLeft(10);
            int t=0;
            while(t==0)
            {
              turnLeft(5);
              for(int i=0;i<5;i++)
              {
                val[i]=digitalRead(IR[i]);
                //because that fuckall shitty reverse sensor
                val[2]=val[2]+1;
                val[2]=val[2]%2;
              }
              if (val[2]==0 || val[1]==0 || val[3]==0)
              { 
                t=1;
                if(val[1]==0)
                zone=1;
                else if (val[3]==0)
                zone=3;
                else 
                zone=2;
                //move forward
                forward(20);
              }
            }
          }
      } 
      else if (val[2]==0 || val[1]==0 || val[3]==0)
      {
        if(val[1]==0)
          zone=1;
        else if (val[3]==0)
          zone=3;
        else 
          zone=2;
        //move forward
        forward(20);
      }
      else
      {
        if (zone==1)
          turnRight(5);
        if (zone==3)
          turnLeft(5);
        if (zone==4)
          turnRight(10);
        if (zone==0)
          turnLeft(5);
        if (zone==2)
          forward(5);
    }
  }
}
  
void turnRight(int turnTime)
{
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
void turnLeft(int turnTime)
{
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
void forward(int forwardTime)
{
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
void backward(int backwardTime)
{
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
