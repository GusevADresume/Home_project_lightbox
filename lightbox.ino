//*************************************************************************
//-----------------------Переменные----------------------------------------
//*************************************************************************
#define PIN 2        // кнопка подключена сюда (PIN --- КНОПКА --- GND)
#define front 15 //Front lights pin
#define rear 14 //Rear lights pin
#define devices1 16 //первая релюшка допов
#define devices2 10 //вторая релюшка допов
#include "GyverButton.h"
GButton butt1(PIN);

int frontflag = 0;
int rearflag = 0;
int a;
uint32_t tm;

//*************************************************************************
//-----------------------Первичные настройки-------------------------------
//*************************************************************************
void setup() { 
Serial.begin(9600);
butt1.setDebounce(50);        // настройка антидребезга (по умолчанию 80 мс)
butt1.setTimeout(1500);        // настройка таймаута на удержание (по умолчанию 500 мс)
butt1.setClickTimeout(1000);   // настройка таймаута между кликами (по умолчанию 300 мс)
butt1.setDirection(NORM_OPEN);
pinMode(front,OUTPUT);
pinMode(rear,OUTPUT);
pinMode(devices1,OUTPUT);
pinMode(devices2,OUTPUT);

digitalWrite(front,HIGH);
digitalWrite(rear,HIGH);
digitalWrite(devices1,HIGH);
digitalWrite(devices2,HIGH);
}
//************************************************************************
//----------------------Главный цикл--------------------------------------
//*************************************************************************

void loop() {
butt1.tick();  // обязательная функция отработки. Должна постоянно опрашиваться
timer();
lightup();
if (butt1.isClick()){ // При одиночном нажатии вызывается функция передних огней
forntfunc();
}
if (butt1.isHolded()) { // При долгом нажатии вызывается функция задних огней
rearfunc();
}
devices();
}


//********************************************************************************
//---------------------------------Lights func's----------------------------------
//********************************************************************************

//-----Front lights func------
void forntfunc(){
  Serial.println("ffunc on");
if (frontflag==0){
  //digitalWrite(front, LOW);
  Serial.println("frontfunc on");
  frontflag=1;
  return;
}
if (frontflag==1){
  Serial.println("ffunc off");
  //digitalWrite(front, HIGH);
  Serial.println("frontfunc  off");
  frontflag=0;}
}


//-----Rear lights func------
void rearfunc(){
  if (rearflag==0){
  digitalWrite(rear, LOW);
  Serial.println("rear lihghts on");
  rearflag=1;
  return;
}
if (rearflag==1){
  digitalWrite(rear, HIGH);
  Serial.println("rear lihghts off");
  rearflag=0;}
}
//----- lights up func---------
void lightup(){ 
  if (tm>10000){
    if (frontflag==1){digitalWrite(front, LOW);}//Включаем передний свет
    if (rearflag==1){digitalWrite(rear, LOW);} // Включаем задний габарит
  }
  if (frontflag==0){digitalWrite(front, HIGH);}//Выклюдчаем передний свет
  if (rearflag==0){digitalWrite(rear, HIGH);} //Выключаем задний габарит 

}
void timer(){
uint32_t  times;

if (millis() - times > 10000){            //замеряем разницу времени для отсчета паузы после зажигания
  times = millis();
  tm+=1;}

 if (a>=7000){
  tm=7000;
 }
}
void devices (){
  if (tm>10){
    digitalWrite(devices1, LOW);
    digitalWrite(devices2, LOW);
    //Serial.println("devices on");
    //Serial.println(tm);

}
}
