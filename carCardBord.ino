#include <Servo.h>

#define led 50
#define buz 22
#define l1 41
#define l2 43
#define r1 33
#define r2 35
#define se 28
#define r 10
#define g 9
#define b 8
#define ldr A0
#define pot A3
#define fls 4


Servo myservo;

String input;
int ser = 180;
bool left = false, right = false;
bool ff=false, bb=false;
unsigned long mil = 20000;

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(buz, OUTPUT);
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(fls, OUTPUT);

  pinMode (ldr, INPUT);
  pinMode (pot, INPUT);

  myservo.attach(se);

  myservo.write(160);

  digitalWrite(buz, 1);
  rgb(0, 255, 255);
  delay(700);
  digitalWrite(buz, 0);
  rgb(0, 0, 0);
  delay(1000);
  rgb(0, 255, 0);

}

//-fnc
void rgb(int aa, int bb, int cc) {
  analogWrite(r, aa);
  analogWrite(g, bb);
  analogWrite(b, cc);
}

void st() {
  digitalWrite(l1, 0);
  digitalWrite(r1, 0);
  digitalWrite(l2, 0);
  digitalWrite(r2, 0);

  rgb(0, 255, 0);

}
void fw() {
  digitalWrite(l1, 1);
  digitalWrite(r1, 1);
  digitalWrite(l2, 0);
  digitalWrite(r2, 0);

  rgb(0, 0, 255);
}
void bw() {
  digitalWrite(l1, 0);
  digitalWrite(r1, 0);
  digitalWrite(l2, 1);
  digitalWrite(r2, 1);

  rgb(255, 0, 0);
}
void ri() {
  digitalWrite(l1, 1);
  digitalWrite(r1, 0);
  digitalWrite(l2, 0);
  digitalWrite(r2, 1);

  rgb(220, 255, 255);
}
void le() {
  digitalWrite(l1, 0);
  digitalWrite(r1, 1);
  digitalWrite(l2, 1);
  digitalWrite(r2, 0);

  rgb(220, 255, 255);
}

void trf() {
  digitalWrite(l1, 1);
  digitalWrite(r1, 1);
  digitalWrite(l2, 0);
  digitalWrite(r2, 1);

  rgb(220, 255, 255);
}

void tlf() {
  digitalWrite(l1, 1);
  digitalWrite(r1, 1);
  digitalWrite(l2, 1);
  digitalWrite(r2, 0);

  rgb(220, 255, 255);
}

void trb() {
  digitalWrite(l1, 0);
  digitalWrite(r1, 1);
  digitalWrite(l2, 1);
  digitalWrite(r2, 1);

  rgb(220, 255, 255);
}

void tlb() {
  digitalWrite(l1, 1);
  digitalWrite(r1, 0);
  digitalWrite(l2, 1);
  digitalWrite(r2, 1);

  rgb(220, 255, 255);
}
void b1() {
  digitalWrite(buz, 1);
}
void b0() {
  digitalWrite(buz, 0);
}

void loop() {
  input = "";

  while (Serial3.available()) {
    input += (char)Serial3.read();
    delay(5);
    mil = millis() + 20000;
  }

  //-----------for phone
  if(input=="0"){
    input="@oo";
  }
  else if (input=="o"){
    input="@o";
  }
  //for phone

  if (input == "@l") {
    left = true;
  }
  else if (input == "@r") {
    right = true;
  }
  else if (input == "@o") {
    left = false;
    right = false;
  }

  if (input == "@ww") {
    ff = true;
  }
  else if (input == "@ss") {
    bb = true;
  }
  else if (input == "@oo") {
    ff = false;
    bb = false;
  }





  if (input == "light on") {
    digitalWrite(led, 1);
  }
  else if (input == "light off") {
    digitalWrite(led, 0);
  }
  
  //-----turn
  else if (ff && right) {
    trf();
  }
  else if (ff && left) {
    tlf();
  }
  else if (bb && right) {
    trb();
  }
  else if (bb && left) {
    tlb();
  }

  else if (input == "@oo"|| input == "o" || input == "0") {
    st();
  }
  
  else if (input == "@ww" || ff) {
    fw();
  }
  else if (input == "@ss" || bb) {
    bw();
  }


  


  else if (input == "@aa") {
    le();
  }
  else if (input == "@dd") {
    ri();
  }
  else if (input == "@u") {
    ser -= 20;
    if (ser < 0) {
      ser = 0;
    }
    Serial.println(ser);
    myservo.write(ser);
    delay(15);
  }
  else if (input == "@d") {
    ser += 20;
    if (ser > 160) {
      ser = 160;
    }
    Serial.println(ser);
    myservo.write(ser);
    delay(15);
  }
  else if (input == "@i1" || input == "@m1") {
    b1();
  }
  else if (input == "@i0" || input == "@m0" || input == "M") {
    b0();
  }
  else if (input == "@j1" || input == "@n1") {
    digitalWrite(led, 1);
  }
  else if (input == "@j0" || input == "@n0" || input == "N") {
    digitalWrite(led, 0);
  }
  else if (input.substring(0, 2) == "@x") {
    int p = input.substring(2, input.length()).toInt();
    myservo.write(map(p, 0, 100, 160, 0));
    delay(15);
  }

  if (analogRead(ldr) < analogRead(pot)) {
    digitalWrite(fls, 1);
  }
  else {
    digitalWrite(fls, 0);
  }


  if (mil < millis()) {
    analogWrite(g, 70);
  }




  if (input != "") {
    Serial.println(input);
  }


  //Serial.println((String)analogRead(ldr) + "\t" + analogRead(pot));
  //Serial3.println((String)"Light: "+analogRead(ldr)+","+analogRead(pot)+","+"a"+","+"b"+","+"c");

}
