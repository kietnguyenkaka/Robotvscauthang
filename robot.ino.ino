#include <AFMotor.h>
#include <PS2X_lib.h>  //for v1.6

PS2X ps2x; // create PS2 Controller Class

AF_DCMotor motorL1(4);
AF_DCMotor motorL2(1);
AF_DCMotor motorR1(3);
AF_DCMotor motorR2(2);

//Xoay 1
#define pin_fwdX1  40
#define pin_bwdX1  42
#define pin_pwmX1  44
//Xoay 2
#define pin_fwdX3  41
#define pin_bwdX3  43
#define pin_pwmX3  45
//Xoay 3
#define pin_fwdX2  48
#define pin_bwdX2  50
#define pin_pwmX2  46


bool Fmove = 0;
bool FLen = 0;
uint8_t SpeedBanh=250;
uint8_t SpeedTruot=200;

void setup() {
  Serial.begin(9600);
  Serial.println("Xe leo cau thang.");

  motorL1.setSpeed(0); 
  motorL1.run(RELEASE);
  motorL2.setSpeed(200); 
  motorL2.run(RELEASE);
  motorR1.setSpeed(200); 
  motorR1.run(RELEASE);
  motorR2.setSpeed(200); 
  motorR2.run(RELEASE);

  pinMode(pin_fwdX1,OUTPUT);
  pinMode(pin_bwdX1,OUTPUT);
  pinMode(pin_pwmX1,OUTPUT);
  
  if(ps2x.config_gamepad(32,28,30,26, true, true)==0) Serial.println("PS2 Ok");   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  delay(500);

}

void loop() {

ps2x.read_gamepad();          //read controller and set large motor to spin at 'vibrate' speed
          
  if(ps2x.Button(PSB_PAD_UP)){
    Serial.println("Toi");
    Tien(SpeedBanh);
    Fmove=1;
  }
  else if(ps2x.Button(PSB_PAD_RIGHT)){
    Serial.println("Phai");
    Phai(SpeedBanh);
    Fmove=1;
  }  
  else if(ps2x.Button(PSB_PAD_LEFT)){
    Serial.println("Trai");
    Trai(SpeedBanh);
    Fmove=1;
  } 
  else if(ps2x.Button(PSB_PAD_DOWN)){
    Serial.println("Lui");  
    Lui(SpeedBanh);
    Fmove=1;
  } 
  else if(Fmove==1){
    Serial.println("Stop");  
    Stop();
    Fmove=0;
  }

  if(ps2x.Button(PSB_L1)) // Len
  {
    if(ps2x.Button(PSB_GREEN)){
      Len1(SpeedTruot);
      FLen=1;
    }
    else if(ps2x.Button(PSB_PINK)){
      Xuong2(SpeedTruot);
      Xuong1(SpeedTruot-50);
      FLen=1;
    } 
    else if(ps2x.Button(PSB_BLUE)){
      Xuong3(SpeedTruot);
      Len2(SpeedTruot);
      FLen=1;
    }
    else if(ps2x.Button(PSB_RED)){
      Len3(SpeedTruot);
      FLen=1;
    }
    else if(FLen==1){
      Dung1();
      Dung2();
      Dung3();
      FLen=0;
    }
  } 
  else if(ps2x.Button(PSB_L2)) // Xuong
  {
    if(ps2x.Button(PSB_GREEN))  {
      Xuong3(SpeedTruot);
      FLen=1;
    }
    else if(ps2x.Button(PSB_PINK)){
      Len3(SpeedTruot-100);
      //Len2(SpeedTruot);
      Xuong2(SpeedTruot);
      FLen=1;
    } 
    else if(ps2x.Button(PSB_BLUE)){
      Len2(SpeedTruot);
      Len1(SpeedTruot-80);
      FLen=1;
    }
    else if(ps2x.Button(PSB_RED)){
      Xuong1(SpeedTruot);
      FLen=1;
    }
    else if(FLen==1){
      Dung1();
      Dung2();
      Dung3();
      FLen=0;
    }
  } 
  else if(ps2x.Button(PSB_R1)) // Len
  {
    if(ps2x.Button(PSB_GREEN))  {
      Len1(SpeedTruot);
      FLen=1;
    }
    else if(ps2x.Button(PSB_PINK)){
      Len2(SpeedTruot);
      FLen=1;
    } 
    else if(ps2x.Button(PSB_BLUE)){
      Len3(SpeedTruot);
      FLen=1;
    }
    else if(FLen==1){
      Dung1();
      Dung2();
      Dung3();
      FLen=0;
    }
  } 
  else if(ps2x.Button(PSB_R2)) // Xuong
  {
    if(ps2x.Button(PSB_GREEN))  {
      Xuong1(SpeedTruot);
      FLen=1;
    }
    else if(ps2x.Button(PSB_PINK)){
      Xuong2(SpeedTruot);
      FLen=1;
    } 
    else if(ps2x.Button(PSB_BLUE)){
      Xuong3(SpeedTruot);
      FLen=1;
    }
    else if(FLen==1){
      Dung1();
      Dung2();
      Dung3();
      FLen=0;
    }
  }
  
  /*
  if(ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)
  {  
    if(ps2x.ButtonPressed(PSB_START)) Serial.println("Start is being held");
    if(ps2x.ButtonPressed(PSB_SELECT)) Serial.println("Select is being held");    
    if(ps2x.ButtonPressed(PSB_L3)) Serial.println("L3 pressed");
    if(ps2x.ButtonPressed(PSB_R3)) Serial.println("R3 pressed");
    if(ps2x.ButtonPressed(PSB_L2)) Serial.println("L2 pressed");
    if(ps2x.ButtonPressed(PSB_R2)) Serial.println("R2 pressed");
    if(ps2x.ButtonPressed(PSB_GREEN))  Serial.println("Triangle pressed");
    if(ps2x.ButtonPressed(PSB_RED)) Serial.println("Circle just pressed");
    if(ps2x.ButtonPressed(PSB_PINK)) Serial.println("Square just released");     
    if(ps2x.ButtonPressed(PSB_BLUE)) Serial.println("X just changed");    
    if(ps2x.ButtonPressed(PSB_L1))  Serial.println("L1 pressed");
    if(ps2x.ButtonPressed(PSB_R1))  Serial.println("R1 pressed");
  }
*/

 delay(50);     

}

void Tien(uint8_t _tocDo){
  motorL1.run(BACKWARD);
  motorL2.run(BACKWARD);
  motorR1.run(FORWARD);
  motorR2.run(FORWARD);
  motorL1.setSpeed(_tocDo); 
  motorL2.setSpeed(_tocDo); 
  motorR1.setSpeed(_tocDo); 
  motorR2.setSpeed(_tocDo); 

}

void Lui(uint8_t _tocDo){
  motorL1.run(FORWARD);
  motorL2.run(FORWARD);
  motorR1.run(BACKWARD);
  motorR2.run(BACKWARD);

  motorL1.setSpeed(_tocDo); 
  motorL2.setSpeed(_tocDo); 
  motorR1.setSpeed(_tocDo); 
  motorR2.setSpeed(_tocDo); 
}


void Phai(uint8_t _tocDo){
  motorL1.run(BACKWARD);
  motorL2.run(FORWARD);
  motorR1.run(BACKWARD);
  motorR2.run(FORWARD);

  motorL1.setSpeed(_tocDo); 
  motorL2.setSpeed(_tocDo); 
  motorR1.setSpeed(_tocDo); 
  motorR2.setSpeed(_tocDo); 
}

void Trai(uint8_t _tocDo){
  motorL1.run(FORWARD);
  motorL2.run(BACKWARD);
  motorR1.run(FORWARD);
  motorR2.run(BACKWARD);

  motorL1.setSpeed(_tocDo); 
  motorL2.setSpeed(_tocDo); 
  motorR1.setSpeed(_tocDo); 
  motorR2.setSpeed(_tocDo); 
}

void XoayPhai(uint8_t _tocDo){
  motorL1.run(BACKWARD);
  motorL2.run(BACKWARD);
  motorR1.run(BACKWARD);
  motorR2.run(BACKWARD);

  motorL1.setSpeed(_tocDo); 
  motorL2.setSpeed(_tocDo); 
  motorR1.setSpeed(_tocDo); 
  motorR2.setSpeed(_tocDo); 
}

void XoayTrai(uint8_t _tocDo){
  motorL1.run(FORWARD);
  motorL2.run(FORWARD);
  motorR1.run(FORWARD);
  motorR2.run(FORWARD);

  motorL1.setSpeed(_tocDo); 
  motorL2.setSpeed(_tocDo); 
  motorR1.setSpeed(_tocDo); 
  motorR2.setSpeed(_tocDo); 
}



void Stop(void){
  motorL1.run(RELEASE);
  motorL2.run(RELEASE);
  motorR1.run(RELEASE);
  motorR2.run(RELEASE);

  motorL1.setSpeed(0); 
  motorL2.setSpeed(0); 
  motorR1.setSpeed(0); 
  motorR2.setSpeed(0); 
}

void Len1(uint8_t _speed){
    Serial.println("xoay 1 Len");  
    digitalWrite(pin_fwdX1,HIGH);
    digitalWrite(pin_bwdX1,LOW);
    digitalWrite(pin_pwmX1,HIGH);
}
void Xuong1(uint8_t _speed){
    Serial.println("xoay 1 Xuong");  
    digitalWrite(pin_fwdX1,LOW);
    digitalWrite(pin_bwdX1,HIGH);
    digitalWrite(pin_pwmX1,HIGH);
}
void Dung1(void){
    Serial.println("xoay 1 Dung");  
    digitalWrite(pin_fwdX1,LOW);
    digitalWrite(pin_bwdX1,LOW);
    analogWrite(pin_pwmX1,0);
}

void Len2(uint8_t _speed){
    Serial.println("xoay 2 Len");  
    digitalWrite(pin_fwdX2,LOW);
    digitalWrite(pin_bwdX2,HIGH);
    digitalWrite(pin_pwmX2,HIGH);
}
void Xuong2(uint8_t _speed){
    Serial.println("xoay 2 Xuong");  
    digitalWrite(pin_fwdX2,HIGH);
    digitalWrite(pin_bwdX2,LOW);
    digitalWrite(pin_pwmX2,HIGH);
}
void Dung2(void){
    Serial.println("xoay 2 Dung");  
    digitalWrite(pin_fwdX2,LOW);
    digitalWrite(pin_bwdX2,LOW);
    analogWrite(pin_pwmX2,0);
}

void Len3(uint8_t _speed){
    Serial.println("xoay 3 Len");  
    digitalWrite(pin_fwdX3,HIGH);
    digitalWrite(pin_bwdX3,LOW);
    digitalWrite(pin_pwmX3,HIGH);
}
void Xuong3(uint8_t _speed){
    Serial.println("xoay 3 Xuong");  
    digitalWrite(pin_fwdX3,LOW);
    digitalWrite(pin_bwdX3,HIGH);
    digitalWrite(pin_pwmX3,HIGH);
}
void Dung3(void){
    Serial.println("xoay 3 Dung");  
    digitalWrite(pin_fwdX3,LOW);
    digitalWrite(pin_bwdX3,LOW);
    analogWrite(pin_pwmX3,0);
}

void resetCoCau(uint8_t _speed){

}
