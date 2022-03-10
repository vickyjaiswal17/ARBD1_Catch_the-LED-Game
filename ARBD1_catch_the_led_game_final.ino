#include<TimerOne.h>
#include <LiquidCrystal.h>
int rs = 4, en = 5, d4 = 0, d5 = 1, d6 = 2, d7 = 3;
LiquidCrystal  lcd(rs, en, d4, d5, d6, d7);
const int CP[4] = {A2,A3,A4,A5};    //Charlieplexed LEDs Pinmap
const int POT = A6;               //Potentiometer Pin
char pattern[12][4] = {             //LEDs Pattern
  "Zz01", //1
  "Z0z1", //2
  "0Zz1", //3
  "Z01z", //4
  "0Z1z", //5
  "Zz10", //6
  "01Zz", //7
  "Z1z0", //8
  "Z10z", //9
  "1Zz0", //10
  "1Z0z", //11
  "10Zz"  //12
};                    
int DELAY=500 ;
int buttonPin=A1; 
int buzzerPin=6;
int p=0,n=1,a,b,c=1,d=0,key,m=1,val1,val2,val3,val4,level=1,score=0,buz=0;
void setup() {
  // put your setup code here, to run once:
 pinMode(buttonPin,INPUT);
 pinMode(buzzerPin,OUTPUT);
 lcd.begin(16, 2);
 lcd.setCursor(0,0);
 lcd.print("Start Game:");
 Timer1.initialize(10000);
 Timer1.attachInterrupt(LEDglow);
}
void loop() {
  // put your main code here, to run repeatedly:
   key=analogRead(buttonPin);
  if((key > 600) && (key < 725) && n==1)
  { 
    n=2;
    m=1;
    analogWrite(buzzerPin,100);
    lcd.clear();
    lcd.print("Level:");
    lcd.print(level);
  }
   do
    {
      key=analogRead(buttonPin); 
      delay(20); 
    } while((key > 600) && (key < 725) && m==1);
    
    if(n==2)
    {
      analogWrite(buzzerPin,0);
      m=2;
    }

  for(int i=0 ; i<12 ;i++){ 
     if(n==2 && m==2){
      analogWrite(buzzerPin,125);
      delay(5);
      analogWrite(buzzerPin,0);   
     for(int j=0 ; j<4 ;j++){
      if(pattern[i][j] == 'Z')
      {
        a=j;
      }
      if(pattern[i][j] == 'z')
      {
        b=j;
      }
       if(pattern[i][j] == '0')
      {
        c=j; 
      }
       if(pattern[i][j] == '1')
      {
        d=j;
      } 
    }
    delay(DELAY); 
  }
}
 do
  {
    key=analogRead(buttonPin); 
    delay(20); 
  } while((key > 600) && (key < 725) && m==3);
  if(n==3)
   {
     analogWrite(buzzerPin,0);
     m=4;
   }
       
if(n==3)
{
  if(val3==1 && val4==0 && DELAY>50)
  {
    score+=100;
    n=4;
    DELAY-=50;
    level+=1;
    lcd.clear();
    lcd.print("Great!! ");
    delay(3000);
    lcd.clear();
    lcd.print("Score:");
    lcd.print(score);
    lcd.setCursor(0,1);
    lcd.print("Next Level:");
    lcd.print(level);
  }
  else if(val3==1 && val4==0 && DELAY<=50){
    score+=200;
    n=4;
    DELAY-=10;
    level+=1;
    lcd.clear();
    lcd.print("Great!! ");
    delay(3000);
    lcd.clear();
    lcd.print("Score:");
    lcd.print(score);
    lcd.setCursor(0,1);
    lcd.print("Next Level:");
    lcd.print(level);
  }
  else
  {
    analogWrite(buzzerPin,70);
    delay(1000);
    analogWrite(buzzerPin,0);
    n=4;
    level=1;
    DELAY=500;
    lcd.clear();
    lcd.print("Sorry! You Lost");
    delay(3000);
    lcd.clear();
    lcd.print("Score:");
    lcd.print(score);
    lcd.setCursor(0,1);
    lcd.print("Start Again:");
    score=0;
  }
}

 do
  {
    key=analogRead(buttonPin); 
    delay(20); 
  } while((key > 600) && (key < 725) && m==4);
  if(n==4)
  {
     m=5;
     n=1;
  }

  
}    
void LEDglow()
{
  key=analogRead(buttonPin);
  if((key > 600) && (key < 725) && m==2)
    {
     n=3;
     m=3;
     analogWrite(buzzerPin,105);
     val1=a;
     val2=b;
     val3=c;
     val4=d;
     return;
    }
  if(p==1 && n==3)
  {
    pinMode(CP[val1],INPUT);
    pinMode(CP[val2],INPUT);
    pinMode(CP[val3],OUTPUT);
    pinMode(CP[val4],OUTPUT);
    digitalWrite(CP[val3],LOW);
    digitalWrite(CP[val4],HIGH);
     p=0;
     return;
  }
   
  if(p==1 && n==2)
  {
    pinMode(CP[a],INPUT); //to disconnect this pin
    pinMode(CP[b],INPUT);  //to disconnect this pin 
    pinMode(CP[c],OUTPUT);  
    pinMode(CP[d],OUTPUT);
    digitalWrite(CP[c],LOW);
    digitalWrite(CP[d],HIGH);
     p=0;
     return;
  }
 if(p==0 )
  {
    pinMode(CP[0],OUTPUT);
    pinMode(CP[1],OUTPUT);
    pinMode(CP[2],INPUT);
    pinMode(CP[3],INPUT);
    digitalWrite(CP[1],LOW);
    digitalWrite(CP[0],HIGH);
    
    p=1;
    return;
  }
}
