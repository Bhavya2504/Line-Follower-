//vcc to 5v on breadboard for each sensor
//gnd to gnd on breadboard for each sensor
const int  n = 6; // number of sensors
int sensorPin[n];    // pin that the sensor sig is attached to
int sensorValue[n];         // the sensor value
int sensorMin[n] = {1023, 1023, 1023, 1023, 1023 ,1023}; // minimum sensor value
int sensorMax[n] = {0, 0, 0, 0, 0, 0} ;    // maximum sensor value
int avg[n], con[n], i, j;
int lmf = 3, lmb = 5, rmf = 6, rmb = 9;//pwn pins for motors
int spmax=100;
int spmid=80;
int spmin=50;
int led=13;
int del=400;


/*              Positioning of sensors:                                  5
 *                          
 *                                                              0   1    2    3   4
 */

int pathlength=0; //variable to record the total of path length
int readpath; //variable to call the path record
char path[99]; //array for path record
void setup()
{
  Serial.begin(9600);
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
  sensorPin[0] = A5;//sig of sensor 1 to A0
  sensorPin[1] = A4;//sig of sensor 2 to A1
  sensorPin[2] = A3;//sig of sensor 3 to A2
  sensorPin[3] = A2;//sig of sensor 4 to A3
  sensorPin[4] = A1;//sig of sensor 5 to A4
  sensorPin[5] = A0;//For checking intersections conditions
  Serial.println("HEllO");
  calibrate();
}

void loop()
{

  getvalues();            //else if (con[0] ==  && con[1] ==  && con[2] ==  && con[3]==  && con[4] ==  )

  if (con[0] == 0 && con[1] == 0 && con[2] == 1 && con[3]== 0 && con[4] == 0 ) //010 straight
  {
    gostraight();
  }
  else if (con[0] == 0 && con[1] == 0 && con[2] == 1 && con[3]== 1 && con[4] == 0 ) //001 right
  {
    softright();
  }
  else if (con[0] == 0 && con[1] == 1 && con[2] == 1 && con[3]== 0 && con[4] == 0 ) //100 left
  {
    softleft();
  }
  else if (con[0] ==0  && con[1] ==1  && con[2] ==0  && con[3]== 0 && con[4] == 0 )
  {
    softleft();
  }
  else if (con[0] ==0  && con[1] == 0 && con[2] == 0 && con[3]== 1 && con[4] ==0  )
  {
      softright();
     // goright();
  }
  else if (con[0] == 1 && con[1] == 1 && con[2] == 0 && con[3]== 0 && con[4] == 0 )
  {
    goleft();
  }
  else if (con[0] == 0 && con[1] == 0 && con[2] == 0 && con[3]== 1 && con[4] == 1 )
  {
    goright();
  }
  else if (con[0] == 1 && con[1] == 0 && con[2] == 0 && con[3]== 0 && con[4] == 0 )
  {
    goleft();
  }
  else if (con[0] == 0 && con[1] == 0 && con[2] == 0 && con[3]== 0 && con[4] == 1 )
  {
    goright();
  }
  else if (con[0] == 1 && con[1] == 1 && con[2] == 1 && con[3]== 0 && con[4] == 0 && con[5]==0 )   
  {
    goleft();
  }
  else if (con[0] == 0 && con[1] == 0 && con[2] == 1 && con[3]==1 && con[4] == 1 && con[5]==0 )
  {
    goright();
  }

  //==========================================ADV================================================
   else if ((con[0] == 1 && con[1] == 1 && con[2] == 1 && con[3]== 0 && con[4] == 0 && con[5]== 1 ))   // || (con[0] == 1 && con[1] == 1 && con[2] == 1 && con[3]== 1 && con[4] == 0 && con[5]== 1 )
  {
//    path[pathlength++]='L';
    strongleft();
    delay(200);
    //delay(del);
  }
  else if ((con[0] == 0 && con[1] == 0 && con[2] == 1 && con[3]== 1 && con[4] == 1 && con[5]== 1) )  //|| (con[0] == 0 && con[1] == 1 && con[2] == 1 && con[3]== 1 && con[4] == 1 && con[5]== 1)
  {
//    path[pathlength++]='S';
    gostraight();
   // delay(del);
  }
  else if (con[0] == 1 && con[1] == 1 && con[2] == 1 && con[3]== 1 && con[4] == 1 && con[5] == 1 )     //+, End Point
  {
    gostraight();
    delay(100);
    getvalues();
    if (con[0] == 1 && con[1] == 1 && con[2] == 1 && con[3]== 1 && con[4] == 1 && con[5] == 1 )
    {
      stops();
      delayfun();
    }
    else
    {
    strongleft();
    delay(200);
    strongleft();
    }
   // delay(700);
//    gostraight();
//    delay(del);
//    if ((con[0] == 0 && con[1] == 0 && con[2] == 1 && con[3]== 0 && con[4] == 0 && con[5] == 1)|| (con[0] == 0 && con[1] == 1 && con[2] == 1 && con[3]== 0 && con[4] == 0 && con[5] == 1) || (con[0] == 0 && con[1] == 0 && con[2] == 1 && con[3]== 1 && con[4] == 0 && con[5] == 1))
//    {
//      goleft();
////     path[pathlength++]='L';
//      delay(del);
//    }
//      else if (con[0] == 1 && con[1] == 1 && con[2] == 1 && con[3]== 1 && con[4] == 1 )
//      {
//        path[pathlength++]='E';
//        stops();
//        delayfun();
//      }
    
  }
    
  else if (con[0] == 1 && con[1] == 1 && con[2] == 1 && con[3]==1 && con[4] == 1 && con[5]==0 )    //T point 
  {
    strongleft();
    delay(200);
   // delay(1000);
  }
  else if (con[0] == 0 && con[1] == 0 && con[2] == 0 && con[3]==0 && con[4] == 0 && con[5]==0 )    //U turn 
  {
    strongleft();
  }
  delay(1);
}

//============================================================= Calibiration ==========================================================


void calibrate()
{
  for ( i = 0; i < 5000; i++)
  {
    for (j = 0; j < n; j++)//for n sensors
    {
      sensorValue[j] = analogRead(sensorPin[j]);
      // record the maximum sensor value
      if (sensorValue[j] > sensorMax[j])
        sensorMax[j] = sensorValue[j];

      // record the minimum sensor value
      if (sensorValue[j] < sensorMin[j])
        sensorMin[j] = sensorValue[j];
    }
    delay(1);
  }

  Serial.println("Calibration Completed");
  Serial.print("Average is: ");
  for (i = 0; i < n; i++)
  {
    avg[i] = (sensorMax[i] + sensorMin[i]) / 2;
    Serial.println(avg[i]);
  }
  Serial.println("Let's check now :) ");
  digitalWrite(13,HIGH);
  delay(2000);
  digitalWrite(13,LOW);
  gostraightfast();
  delay(300);
}

void getvalues()
{
  for (i = 0; i < n; i++)// n is number of sensors
  {
    sensorValue[i] = analogRead(sensorPin[i]);
    if (sensorValue[i] > avg[i])
      con[i] = 1;//black
    else
      con[i] = 0;//white

    //Serial.print(con[i]);
  }
  //Serial.println(" ");
}

void delayfun()
{
  digitalWrite(11,HIGH);
  delay(5000);
  digitalWrite(11,LOW);
  delay(5000);
}

void gostraight()
{
  analogWrite(lmf, spmax);
  analogWrite(lmb, 0);
  analogWrite(rmf, spmax);
  analogWrite(rmb, 0);
}

void goright()
{
  analogWrite(lmf, spmax);//left motor1
  analogWrite(lmb, 0);//left motor2
  analogWrite(rmf, 0);//right motor1
  analogWrite(rmb, spmax);//right motor2
}

void goleft()
{
  analogWrite(lmf, 0);//left motor1
  analogWrite(lmb, spmax);//left motor2
  analogWrite(rmf, spmax);//right motor1
  analogWrite(rmb, 0);//right motor2
}
void softleft()
{
  analogWrite(lmf, 0);//left motor1
  analogWrite(lmb, 0);//left motor2
  analogWrite(rmf, spmid);//right motor1
  analogWrite(rmb, 0);//right motor2
}
void softright()
{
  analogWrite(lmf, spmid);//left motor1
  analogWrite(lmb, 0);//left motor2
  analogWrite(rmf, 0);//right motor1
  analogWrite(rmb, 0);//right motor2
}

void stops()
{
  analogWrite(lmf, 0);//left motor1
  analogWrite(lmb, 0);//left motor2
  analogWrite(rmf, 0);//right motor1
  analogWrite(rmb, 0);//right motor2
}
void strongleft()
{
  analogWrite(lmf, 0);//left motor1
  analogWrite(lmb, 255);//left motor2
  analogWrite(rmf, 255);//right motor1
  analogWrite(rmb, 0);//right motor2
}
void gostraightfast()
{
  analogWrite(lmf, 200);
  analogWrite(lmb, 0);
  analogWrite(rmf, 200);
  analogWrite(rmb, 0);
}
