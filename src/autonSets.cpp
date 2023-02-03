#include "main.h"
void blue1(){
  baseMove(-20);
  waitBase(1000);
  delay(100);
  baseTurn (90, 1.12, 1.1);
  waitBase(1000);
  baseMove(-4.5, 0.22, 0);
  waitBase(1000);
  setIntakeSpeed(-127);
  delay(110);
  setIntakeSpeed(0); //enough time for 2 disc intake
  baseMove(10);
  waitBase(1000);
  baseTurn(45);
  waitBase(1000);
  baseMove(32, 0.15, 1);
  waitBase(2000);
  baseTurn(116, 1.3, 0.9);
  delay(500);
  shootCata();
  delay(600);
  baseTurn(209);
  waitBase(1000);
  setIntakeSpeed(127);
  baseMove(-30);
  waitBase(2000);
  baseTurn(133);
  waitBase(1000);
  setIntakeSpeed(0);
  baseMove(8);
  delay(500);
  shootCata();
  delay(600);
  baseTurn(220);
  waitBase(1000);
  setIntakeSpeed(-127);
  baseMove(-60, 0.15, 0.8);
  waitBase(5000);
}
void blue2(){

}
void red1(){

}
void red2(){

}
void skills(){

}
