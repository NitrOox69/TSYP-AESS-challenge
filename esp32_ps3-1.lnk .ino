#include <Ps3Controller.h>

const int freq = 5000;
const int resolution = 6;
const int gauche = 1;
const int droite = 1;
int player = 1;
int battery = 1;

int ena = 33;
int in1 = 25;
int in2 = 26;
int in3 = 27;
int in4 = 14;
int enb = 12;

int lx;
int LX;
int RY;
int ry;
int X;
int right;
int left;

void notify()
{
  lx = Ps3.data.analog.stick.lx;
  ry = Ps3.data.analog.stick.ry;
  RY = map(abs(ry),0,128,100,255);
  LX = map(abs(lx),0,128,50,RY);
  
   if (ry < -10){
      if (lx < -10){
        digitalWrite(in1,HIGH);
        digitalWrite(in2,LOW);
        digitalWrite(in3,HIGH);
        digitalWrite(in4,LOW);
        ledcWrite(droite,RY);
        ledcWrite(gauche,RY-LX);
        Serial.println("yasar");  
      }
      else if (lx > 10){
        digitalWrite(in1,HIGH);
        digitalWrite(in2,LOW);
        digitalWrite(in3,HIGH);
        digitalWrite(in4,LOW);
        ledcWrite(droite,RY-LX);
        ledcWrite(gauche,RY); 
        Serial.println("ymin");
     }
      else{
        digitalWrite(in1,HIGH);
        digitalWrite(in2,LOW);
        digitalWrite(in3,HIGH);
        digitalWrite(in4,LOW);
        ledcWrite(droite,RY);
        ledcWrite(gauche,RY);
        Serial.println("9dam");
   }
   }
   else if (ry > 10){
      if (lx < -10){
        digitalWrite(in1,LOW);
        digitalWrite(in2,HIGH);
        digitalWrite(in3,LOW);
        digitalWrite(in4,HIGH);
        ledcWrite(droite,RY);
        ledcWrite(gauche,RY-LX);
        Serial.println("ysar");    
      }
      else if (lx > 10){
        digitalWrite(in1,LOW);
        digitalWrite(in2,HIGH);
        digitalWrite(in3,LOW);
        digitalWrite(in4,HIGH);
        ledcWrite(droite,RY-LX);
        ledcWrite(gauche,RY); 
        Serial.println("ymin");
   }
   else{
        digitalWrite(in1,LOW);
        digitalWrite(in2,HIGH);
        digitalWrite(in3,LOW);
        digitalWrite(in4,HIGH);
        ledcWrite(droite,RY);
        ledcWrite(gauche,RY);
        Serial.println("9dam");
        Serial.println(RY-LX);
        Serial.println(RY);
   }
   }
   else{
        digitalWrite(in1,LOW);
        digitalWrite(in2,LOW);
        digitalWrite(in3,LOW);
        digitalWrite(in4,LOW);
        ledcWrite(droite,0);
        ledcWrite(gauche,0); 
        Serial.println("stop"); 
        Serial.println(RY-LX);
        Serial.println(RY);  
   }


        
        right = map((Ps3.data.analog.button.r2),0,255,90,255);
        left = map((Ps3.data.analog.button.l2),0,255,90,255);
        if((Ps3.data.analog.button.l2>15)&&(Ps3.data.analog.button.r2<15)){
        digitalWrite(in1,LOW);
        digitalWrite(in2,HIGH);
        digitalWrite(in3,HIGH);
        digitalWrite(in4,LOW);
        ledcWrite(droite,left);
        ledcWrite(gauche,left);        
        }
        if((Ps3.data.analog.button.l2<15)&&(Ps3.data.analog.button.r2>15)){
        digitalWrite(in1,HIGH);
        digitalWrite(in2,LOW);
        digitalWrite(in3,LOW);
        digitalWrite(in4,HIGH);
        ledcWrite(droite,right);
        ledcWrite(gauche,right); 
        }

    if( battery != Ps3.data.status.battery ){
        battery = Ps3.data.status.battery;
        Serial.print("The controller battery is ");
        if( battery == ps3_status_battery_charging )      Serial.println("charging");
        else if( battery == ps3_status_battery_full )     Serial.println("FULL");
        else if( battery == ps3_status_battery_high )     Serial.println("HIGH");
        else if( battery == ps3_status_battery_low)       Serial.println("LOW");
        else if( battery == ps3_status_battery_dying )    Serial.println("DYING");
        else if( battery == ps3_status_battery_shutdown ) Serial.println("SHUTDOWN");
        else Serial.println("UNDEFINED");
    }

}

void onConnect(){
    Serial.println("Connected.");
}

void setup()
{
  pinMode(ena,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(enb,OUTPUT);



    Serial.begin(115200);

    Ps3.attach(notify);
    Ps3.attachOnConnect(onConnect);
    Ps3.begin("5a:5a:5a:5a:5a:5a");
    Serial.println("Ready.");

    ledcSetup(gauche, freq, resolution);
    ledcSetup(droite, freq, resolution);

    ledcAttachPin(ena, gauche);
    ledcAttachPin(enb, droite);

    
}

void loop()
{
    if(!Ps3.isConnected())
        return;

    //-------------------- Player LEDs -------------------
    Serial.print("Setting LEDs to player "); Serial.println(player, DEC);
    Ps3.setPlayer(player);

    player += 1;
    if(player > 10) player = 0;


    //------ Digital cross/square/triangle/circle buttons ------
    if( Ps3.data.button.cross && Ps3.data.button.down )
        Serial.println("Pressing both the down and cross buttons");
    if( Ps3.data.button.square && Ps3.data.button.left )
        Serial.println("Pressing both the square and left buttons");
    if( Ps3.data.button.triangle && Ps3.data.button.up )
        Serial.println("Pressing both the triangle and up buttons");
    if( Ps3.data.button.circle && Ps3.data.button.right )
        Serial.println("Pressing both the circle and right buttons");

    if( Ps3.data.button.l1 && Ps3.data.button.r1 )
        Serial.println("Pressing both the left and right bumper buttons");
    if( Ps3.data.button.l2 && Ps3.data.button.r2 )
        Serial.println("Pressing both the left and right trigger buttons");
    if( Ps3.data.button.l3 && Ps3.data.button.r3 )
        Serial.println("Pressing both the left and right stick buttons");
    if( Ps3.data.button.select && Ps3.data.button.start )
        Serial.println("Pressing both the select and start buttons");

    delay(2000);
}
