#define QT 50*16 //quarter-twist
#define HT 100*16 //half-twist
#define EN1 18 //UDLR
#define EN2 19 //FB

char comchar;
//EN,U_DIR,U_STEP,D_DIR,D_STEP,L_DIR,L_STEP,R_DIR,R_STEP,F_DIR,F_STEP,B_DIR,B_STEP
byte outputPin[13] = {0, 2, 3, 4, 5, 6, 7, 8, 9 ,10, 11, 14, 12};
//a clockwise quarter-twist of the “up face” (U) is denoted here by U1, a half-twist by U2, and a counterclockwise quarter-twist by U3. 
//U1,U2,U3,D1,D2,D3,L1,L2,L3,R1,R2,R3,F1,F2,F3,B1,B2,B3

void step(boolean dir, byte dirPin, byte stepperPin, int steps, boolean isEn1)
{
  if(isEn1)
  {
    digitalWrite(EN1, LOW);
  }
  else
  {
    digitalWrite(EN2, LOW);
  }
  digitalWrite(dirPin, dir);
  delay(50);
  for(int i=0; i<steps; i++)
  {
    digitalWrite(stepperPin, HIGH);
    delayMicroseconds(100);
    digitalWrite(stepperPin, LOW);
    delayMicroseconds(100);
  }
  //delayMicroseconds(2000);
  if(isEn1)
  {
    digitalWrite(EN1, HIGH);
  }
  else
  {
    digitalWrite(EN2, HIGH);
  } 
}

void step_debug(boolean dir, byte dirPin, byte stepperPin, int steps, boolean isEn1)
{
  if(isEn1)
  {
    digitalWrite(EN1, LOW);
  }
  else
  {
    digitalWrite(EN2, LOW);
  }
  digitalWrite(dirPin, dir);
  delay(50);
  for(int i=0; i<steps; i++)
  {
    digitalWrite(stepperPin, HIGH);
    delayMicroseconds(100);
    digitalWrite(stepperPin, LOW);
    delayMicroseconds(100);
  }
  delayMicroseconds(2000);
  if(isEn1)
  {
    digitalWrite(EN1, HIGH);
  }
  else
  {
    digitalWrite(EN2, HIGH);
  } 
}

void setup() {
  // put your setup code here, to run once:
  for(int i=0; i<13; i++)
  {
   pinMode(i, OUTPUT);   
  }

  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  digitalWrite(EN1, HIGH);
  digitalWrite(EN2, HIGH);
  Serial.begin(9600);

  while(Serial.read()>= 0){} //clear serialbuffer
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()>0){
    comchar = Serial.read();//读串口第一个字节
    switch(comchar)
    {
      //U1
      case '0':
      step(true, outputPin[1], outputPin[2], QT, true);
      Serial.write(0x55);
      break;
      //U2
      case '1':
      step(true, outputPin[1], outputPin[2], HT, true);
      Serial.write(0x55);
      break;
      //U3
      case '2':
      step(false, outputPin[1], outputPin[2], QT, true);
      Serial.write(0x55);
      break;
      //D1
      case '3':
      step(true, outputPin[3], outputPin[4], QT, true);
      Serial.write(0x55);
      break;
      //D2
      case '4':
      step(true, outputPin[3], outputPin[4], HT, true);
      Serial.write(0x55);
      break;
      //D3
      case '5':
      step(false, outputPin[3], outputPin[4], QT, true);
      Serial.write(0x55);
      break;
      //L1
      case '6':
      step(true, outputPin[5], outputPin[6], QT, true);
      Serial.write(0x55);
      break;
      //L2
      case '7':
      step(true, outputPin[5], outputPin[6], HT, true);
      Serial.write(0x55);
      break;
      //L3
      case '8':
      step(false, outputPin[5], outputPin[6], QT, true);
      Serial.write(0x55);
      break;
      //R1
      case '9':
      step(true, outputPin[7], outputPin[8], QT, true);
      Serial.write(0x55);
      break;
      //R2
      case 'a':
      step(true, outputPin[7], outputPin[8], HT, true);
      Serial.write(0x55);
      break;
      //R3
      case 'b':
      step(false, outputPin[7], outputPin[8], QT, true);
      Serial.write(0x55);
      break;
      //F1
      case 'c':
      step(true, outputPin[9], outputPin[10], QT-1, false);
      Serial.write(0x55);
      break;
      //F2
      case 'd':
      step(true, outputPin[9], outputPin[10], HT-1, false);
      Serial.write(0x55);
      break;
      //F3
      case 'e':
      step(false, outputPin[9], outputPin[10], QT-1, false);
      Serial.write(0x55);
      break;
      //B1
      case 'f':
      step(true, outputPin[11], outputPin[12], QT, false);
      Serial.write(0x55);
      break;
      //B2
      case 'g':
      step(true, outputPin[11], outputPin[12], HT, false);
      Serial.write(0x55);
      break;
      //B3
      case 'h':
      step(false, outputPin[11], outputPin[12], QT, false);
      Serial.write(0x55);
      break;
      
      default:
      Serial.write(comchar);
      break;
    }
  }
}
