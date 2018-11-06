#include "SimpleTimer.h"
#include <EEPROM.h>

SimpleTimer timer;      

#define LED0_0 13
#define LED0_1 12
#define LED0_2 11
#define LED1_0 10
#define LED1_1 9
#define LED1_2 8
#define LED2_0 7 
#define LED2_1 6
#define LED2_2 5
#define LED3_0 4
#define LED3_1 3
#define LED3_2 2
#define LED4_0 14
#define LED4_1 15
#define LED4_2 16
#define LED5_0 17
#define LED5_1 18
#define LED5_2 19
#define LED6_0 20
#define LED6_1 21
#define LED6_2 22
// LED(red)
#define LED_l 23
#define LED_m 24
#define LED_r 25
// 사용자 조작부LED(green)
#define left 45
#define right 44
// PUSH버튼

bool state_l = false;
bool state_r = false;
unsigned short led_place = 1; // 캐릭터 위치
int x;
int y;
int i, j;

bool led_array[8][3] = {0};

void setup() {
  pinMode(LED0_0, OUTPUT); pinMode(LED0_1, OUTPUT); pinMode(LED0_2, OUTPUT); // 1행 
  pinMode(LED1_0, OUTPUT); pinMode(LED1_1, OUTPUT); pinMode(LED1_2, OUTPUT); // 2행 
  pinMode(LED2_0, OUTPUT); pinMode(LED2_1, OUTPUT); pinMode(LED2_2, OUTPUT); // 3행  
  pinMode(LED3_0, OUTPUT); pinMode(LED3_1, OUTPUT); pinMode(LED3_2, OUTPUT); // 4행  
  pinMode(LED4_0, OUTPUT); pinMode(LED4_1, OUTPUT); pinMode(LED4_2, OUTPUT); // 5행  
  pinMode(LED5_0, OUTPUT); pinMode(LED5_1, OUTPUT); pinMode(LED5_2, OUTPUT); // 6행
  pinMode(LED6_0, OUTPUT); pinMode(LED6_1, OUTPUT); pinMode(LED6_2, OUTPUT); // 7행 

  pinMode(LED_l, OUTPUT);  pinMode(LED_m, OUTPUT);  pinMode(LED_r, OUTPUT); // 조작부
  
  pinMode(left, INPUT); //왼쪽 push
  pinMode(right, INPUT); // 오른쪽 push
  
  randomSeed(analogRead(A0));
   
  Serial.begin(9600);
}
bool game_state = false;
bool start_state = false;
bool state_s = false;
bool state_s2 = false;
bool start_rand = true;
bool ran = false;
bool state_d = false;
bool timerBook = false;
bool state_score = false;

void INIT(){
  bool start_state = false;
  bool start_rand = true;
  bool ran = false;
  bool timerBook = false;
  bool state_d = false;
  bool state_s = false;
  bool state_s2 = false;
  bool state_score = false;
}
void printMatrix(){
  if (led_array[0][0] == true) digitalWrite(LED0_0, HIGH);if (led_array[0][1] == true) digitalWrite(LED0_1, HIGH);if (led_array[0][2] == true) digitalWrite(LED0_2, HIGH);
  if (led_array[1][0] == true) digitalWrite(LED1_0, HIGH);if (led_array[1][1] == true) digitalWrite(LED1_1, HIGH);if (led_array[1][2] == true) digitalWrite(LED1_2, HIGH);
  if (led_array[2][0] == true) digitalWrite(LED2_0, HIGH);if (led_array[2][1] == true) digitalWrite(LED2_1, HIGH);if (led_array[2][2] == true) digitalWrite(LED2_2, HIGH);
  if (led_array[3][0] == true) digitalWrite(LED3_0, HIGH);if (led_array[3][1] == true) digitalWrite(LED3_1, HIGH);if (led_array[3][2] == true) digitalWrite(LED3_2, HIGH);
  if (led_array[4][0] == true) digitalWrite(LED4_0, HIGH);if (led_array[4][1] == true) digitalWrite(LED4_1, HIGH);if (led_array[4][2] == true) digitalWrite(LED4_2, HIGH);
  if (led_array[5][0] == true) digitalWrite(LED5_0, HIGH);if (led_array[5][1] == true) digitalWrite(LED5_1, HIGH);if (led_array[5][2] == true) digitalWrite(LED5_2, HIGH);
  if (led_array[6][0] == true) digitalWrite(LED6_0, HIGH);if (led_array[6][1] == true) digitalWrite(LED6_1, HIGH);if (led_array[6][2] == true) digitalWrite(LED6_2, HIGH);

  if (led_array[0][0] == false) digitalWrite(LED0_0, LOW);if (led_array[0][1] == false) digitalWrite(LED0_1, LOW);if (led_array[0][2] == false) digitalWrite(LED0_2, LOW);
  if (led_array[1][0] == false) digitalWrite(LED1_0, LOW);if (led_array[1][1] == false) digitalWrite(LED1_1, LOW);if (led_array[1][2] == false) digitalWrite(LED1_2, LOW);
  if (led_array[2][0] == false) digitalWrite(LED2_0, LOW);if (led_array[2][1] == false) digitalWrite(LED2_1, LOW);if (led_array[2][2] == false) digitalWrite(LED2_2, LOW);
  if (led_array[3][0] == false) digitalWrite(LED3_0, LOW);if (led_array[3][1] == false) digitalWrite(LED3_1, LOW);if (led_array[3][2] == false) digitalWrite(LED3_2, LOW);
  if (led_array[4][0] == false) digitalWrite(LED4_0, LOW);if (led_array[4][1] == false) digitalWrite(LED4_1, LOW);if (led_array[4][2] == false) digitalWrite(LED4_2, LOW);
  if (led_array[5][0] == false) digitalWrite(LED5_0, LOW);if (led_array[5][1] == false) digitalWrite(LED5_1, LOW);if (led_array[5][2] == false) digitalWrite(LED5_2, LOW);
  if (led_array[6][0] == false) digitalWrite(LED6_0, LOW);if (led_array[6][1] == false) digitalWrite(LED6_1, LOW);if (led_array[6][2] == false) digitalWrite(LED6_2, LOW);
}

void ALL_led_off(){ // 모든 led소등
  for(y = 0;y < 7;y++){
      for(x = 0;x < 3;x++)
      led_array[y][x] = 0;
  }
  digitalWrite(LED_l, LOW);
  digitalWrite(LED_m, LOW);
  digitalWrite(LED_r, LOW);
  printMatrix();
}

void ALL_led_on(){ // 모든 led점등
  for(y = 0;y < 7;y++){
      for(x = 0;x < 3;x++)
      led_array[y][x] = 1;
  }
  printMatrix();
}

void main_scr(){ // 메인스크린
   led_array[0][0] = 1;                    led_array[0][2] = 1;
   led_array[1][0] = 1;led_array[1][1] = 1;led_array[1][2] = 1;
   led_array[2][0] = 1;                    led_array[2][2] = 1;
   
                       led_array[4][1] = 1;
                       led_array[5][1] = 1;
                       led_array[6][1] = 1;
   printMatrix();
}

void start_scr(){ // 시작 스크린
  led_array[1][0] = 1;led_array[1][1] = 1;led_array[1][2] = 1;
                                          led_array[2][2] = 1;
  led_array[3][0] = 1;led_array[3][1] = 1;led_array[3][2] = 1;
                                          led_array[4][2] = 1;
  led_array[5][0] = 1;led_array[5][1] = 1;led_array[5][2] = 1;
  digitalWrite(LED_l, HIGH);
  digitalWrite(LED_m, HIGH);
  digitalWrite(LED_r, HIGH);
  printMatrix();
  
  delay(500);
  ALL_led_off();
  led_array[1][0] = 1;led_array[1][1] = 1;led_array[1][2] = 1;
                                          led_array[2][2] = 1;
  led_array[3][0] = 1;led_array[3][1] = 1;led_array[3][2] = 1;
  led_array[4][0] = 1;
  led_array[5][0] = 1;led_array[5][1] = 1;led_array[5][2] = 1;
  digitalWrite(LED_l, HIGH);
  digitalWrite(LED_m, HIGH);
  digitalWrite(LED_r, LOW);
  printMatrix();
  
  delay(500);
  ALL_led_off();
                      led_array[1][1] = 1;                   
                      led_array[2][1] = 1;
                      led_array[3][1] = 1;
                      led_array[4][1] = 1;
                      led_array[5][1] = 1;
                     
  digitalWrite(LED_l, HIGH);
  digitalWrite(LED_m, LOW);
  digitalWrite(LED_r, LOW);
  printMatrix();
  
  delay(500);
  ALL_led_off();
  start_state = true;
}

void start(){
  if(state_s == false)
      main_scr();
      
  if((digitalRead(left) == LOW || digitalRead(right) == LOW) && state_s2 == false){
      state_s = true;
      ALL_led_off();
      start_scr();
      state_s2 = true;
      game_state = true;
   }
   
}

void enemy_car_pattern(){// 적 생성 함수
  if(start_rand == true){
    for(i = 0;i < 3;i++)
      led_array[0][i] = random(100)%2;
   if((led_array[0][0] == 1 && led_array[0][1] == 1 && led_array[0][2] == 1)
   || (led_array[0][0] == 0 && led_array[0][1] == 0 && led_array[0][2] == 0)) // x축이 모두 1or 0이면 재실행
       enemy_car_pattern();
  }
 start_rand = false;

 if(ran == true){
  if(led_array[1][0] == 1 && led_array[1][1] == 0 && led_array[1][2] == 0){
      led_array[0][0] = random(100)%2;
      led_array[0][1] = random(100)%2;
      if(led_array[0][1] == 1)
        led_array[0][2] = 0;
      else
        led_array[0][2] = 1;}
  if(led_array[1][0] == 1 && led_array[1][1] == 1 && led_array[1][2] == 0){
      led_array[0][0] = random(100)%2;
      led_array[0][2] = 0;
      if(led_array[0][0] == 1)
        led_array[0][1] = 0;
      else
        led_array[0][1] = 1;}
      
  if(led_array[1][0] == 1 && led_array[1][1] == 0 && led_array[1][2] == 1){
      led_array[0][0] = random(100)%2;
      led_array[0][1] = 0;
      if(led_array[0][0] == 1)
        led_array[0][2] = 0;
        else
        led_array[0][2] = 1;}
     
  if(led_array[1][0] == 0 && led_array[1][1] == 1 && led_array[1][2] == 1){
      led_array[0][0] = 0;
      led_array[0][1] = random(100)%2;
      led_array[0][2] = random(100)%2;}
  if(led_array[1][0] == 0 && led_array[1][1] == 0 && led_array[1][2] == 1){
      led_array[0][0] = random(100)%2;
      led_array[0][2] = random(100)%2;
      if(led_array[0][0] == 1)
        led_array[0][1] = 0;
      else
        led_array[0][1] = 1;}
  if(led_array[1][0] == 0 && led_array[1][1] == 1 && led_array[1][2] == 0){
      led_array[0][0] = random(100)%2;
      led_array[0][1] = random(100)%2;
      if(led_array[0][0] == 1)
        led_array[0][2] = 0;
      else
        led_array[0][2] = 1;}
  if(led_array[1][0] == 0 && led_array[1][1] == 0 && led_array[1][2] == 0){
      led_array[0][0] = random(100)%2;
      led_array[0][1] = random(100)%2;
      if(led_array[0][1] == 1)
        led_array[0][2] = 0;
      else
        led_array[0][2] = 1;}
        
if(led_array[1][1] == 1 && led_array[1][0] == 0 && led_array[1][2] == 0){
  for(i = 0;i<3;i++)
      led_array[0][i] = 0;
   }
}
  printMatrix();
  ran = true;
}

unsigned short score =  0;

void enemy_car_down(){
  
     if(state_d == false)
        enemy_car_pattern();
     
      for(y = 7; y >= 0; y--)
        for(x = 0; x < 3; x++){
          if (y == 0)
              led_array[y][x] = false;
          else{
              led_array[y][x] = led_array[y - 1][x];
              led_array[y-1][x] = false;
            }
  }
  timerBook = false;
  score += 1;
 
  level();
}

unsigned long car_speed = 500;

void level(){
  if(score < 16)
   car_speed;
  else if(score >= 16 && score < 86)
   car_speed -= 5;
  else if(score >= 86)
   car_speed = 140;
}
  
void Dead_screen(){
   for(i = 0; i < 2; i ++){
    ALL_led_on();
    printMatrix();
    delay(100);
    ALL_led_off();
    printMatrix();
    delay(100);
   }
}
int player = 0;

void Dead(){
    for(i = 0;i<3;i++){
      if(led_array[7][i] == 1 && led_place == i){
          digitalWrite(LED_l, LOW);
          digitalWrite(LED_m, LOW);
          digitalWrite(LED_r, LOW);
          ALL_led_off();
          
          
          if(state_score == false){
            Dead_screen();
            score_scr();
            delay(300);
            ALL_led_off();
            delay(300);
            score_scr();
            delay(300);
            ALL_led_off();
            delay(300);
            score_scr();
            delay(300);
            ALL_led_off();
            rank();
            rank_scr();
            game_state = false;
          }
          state_d = true;
    }
  }
}
short f_score;

void score_scr(){
  f_score = score / 7;
  
if(f_score < 8){ 
  for(y = 6; y >= 7 - f_score; y--){
       led_array[y][0] = 1;
       printMatrix();
       delay(70);
  }
}
if(f_score >= 8 && f_score < 15){
    for(y = 6;y >= 0; y--){
      led_array[y][0] = 1;
       printMatrix();
       delay(70);
  }
   for(y = 6;y >= 14 - f_score; y--){
      led_array[y][1] = 1;
       printMatrix();
       delay(70);
  }
}
if(f_score >= 15 && f_score < 21){
  for(x = 0;x < 2; x++){
   for(y = 6;y >= 0; y--){
     led_array[y][x] = 1;
      printMatrix();
      delay(70);
   }
  }
   for(y = 6;y >= 21 - f_score; y--){
       led_array[y][2] = 1;
       printMatrix();
       delay(70);
    }
  }
  if(f_score >= 21){
    for(x = 0;x < 3; x++){
      for(y = 6;y >= 0; y--){
     led_array[y][x] = 1;
      printMatrix();
      delay(70);
     }
   }
  }
 state_score = true;
}
int eep_count;

void game_data(){
    if(EEPROM.read(10) >= 9){
      for(i = 0; i <= 10; i++)
         EEPROM.write(i,0);
    }
    if(EEPROM.read(10) < 9){
      eep_count = EEPROM.read(10);
      eep_count++;
      EEPROM.write(10, eep_count);
      }
    player = EEPROM.read(10);
}
int ranking = 1;

void rank(){
  game_data();
   EEPROM.write(player, score);
   
   for(i = 1;i < 10;i++){
    if(EEPROM.read(i) > score)
      ranking++;
   }
}
void rank_scr(){
  if(ranking == 1){
                      led_array[1][1] = 1;                   
                      led_array[2][1] = 1;
                      led_array[3][1] = 1;
                      led_array[4][1] = 1;
                      led_array[5][1] = 1;
  
   printMatrix(); 
  }
 if(ranking == 2){ 
  led_array[1][0] = 1;led_array[1][1] = 1;led_array[1][2] = 1;
                                          led_array[2][2] = 1;
  led_array[3][0] = 1;led_array[3][1] = 1;led_array[3][2] = 1;
  led_array[4][0] = 1;
  led_array[5][0] = 1;led_array[5][1] = 1;led_array[5][2] = 1;

  printMatrix();                   
 }
 if(ranking == 3){ 
  led_array[1][0] = 1;led_array[1][1] = 1;led_array[1][2] = 1;
                                          led_array[2][2] = 1;
  led_array[3][0] = 1;led_array[3][1] = 1;led_array[3][2] = 1;
                                          led_array[4][2] = 1;
  led_array[5][0] = 1;led_array[5][1] = 1;led_array[5][2] = 1;

  printMatrix();                   
 }
 if(ranking == 4){ 
  led_array[1][0] = 1;                    led_array[1][2] = 1;
  led_array[2][0] = 1;                    led_array[2][2] = 1;
  led_array[3][0] = 1;led_array[3][1] = 1;led_array[3][2] = 1;
                                          led_array[4][2] = 1;
                                          led_array[5][2] = 1;

  printMatrix();                   
 }
 if(ranking == 5){ 
  led_array[1][0] = 1;led_array[1][1] = 1;led_array[1][2] = 1;
  led_array[2][0] = 1;                    
  led_array[3][0] = 1;led_array[3][1] = 1;led_array[3][2] = 1;
                                          led_array[4][2] = 1;
  led_array[5][0] = 1;led_array[5][1] = 1;led_array[5][2] = 1;

  printMatrix();                   
 }
  if(ranking == 6){ 
  led_array[1][0] = 1;led_array[1][1] = 1;led_array[1][2] = 1;
  led_array[2][0] = 1;                    
  led_array[3][0] = 1;led_array[3][1] = 1;led_array[3][2] = 1;
  led_array[4][0] = 1;                    led_array[4][2] = 1;                    
  led_array[5][0] = 1;led_array[5][1] = 1;led_array[5][2] = 1;

  printMatrix();                   
 }
 if(ranking == 7){ 
  led_array[1][0] = 1;led_array[1][1] = 1;led_array[1][2] = 1;
  led_array[2][0] = 1;                    led_array[2][2] = 1;
                                          led_array[3][2] = 1;
                                          led_array[4][2] = 1;                    
                                          led_array[5][2] = 1;

  printMatrix();                   
 }
 if(ranking == 8){ 
  led_array[1][0] = 1;led_array[1][1] = 1;led_array[1][2] = 1;
  led_array[2][0] = 1;                    led_array[2][2] = 1;
  led_array[3][0] = 1;led_array[3][1] = 1;led_array[3][2] = 1;
  led_array[4][0] = 1;                    led_array[4][2] = 1;
  led_array[5][0] = 1;led_array[5][1] = 1;led_array[5][2] = 1;

  printMatrix();                   
 }
 if(ranking == 9){ 
  led_array[1][0] = 1;led_array[1][1] = 1;led_array[1][2] = 1;
  led_array[2][0] = 1;                    led_array[2][2] = 1;
  led_array[3][0] = 1;led_array[3][1] = 1;led_array[3][2] = 1;
                                          led_array[4][2] = 1;
  led_array[5][0] = 1;led_array[5][1] = 1;led_array[5][2] = 1;

  printMatrix();                   
 }
}
void My_car_shift(){ // 캐릭터 시프트 함수
  if(led_place > 0){
   if (digitalRead(left) == LOW && state_l == false){
      Serial.println("left");
      delay(10);
      led_place --;
      state_l = true;
  }
  if(digitalRead(left) == HIGH && state_l == true){
      delay(10);
      state_l = false;
    }
  }
  if(led_place < 2){
   if (digitalRead(right) == LOW  && state_r == false){
      Serial.println("right");
      delay(10);
      led_place ++;
      state_r = true;
    }
  if(digitalRead(right) == HIGH && state_r == true){
      delay(10);
      state_r = false;
    }
  }
  if(led_place == 0){ // 왼쪽일때
    digitalWrite(LED_l, HIGH);
    digitalWrite(LED_m, LOW);
    digitalWrite(LED_r, LOW);
  }
  if(led_place == 1){ // 가운데일때
    digitalWrite(LED_l, LOW);
    digitalWrite(LED_m, HIGH);
    digitalWrite(LED_r, LOW);
  }
  if(led_place == 2){ // 오른쪽일때
    digitalWrite(LED_l, LOW);
    digitalWrite(LED_m, LOW);
    digitalWrite(LED_r, HIGH);
  }
}
bool stop_state = false;
bool stop2_state = false;

void stop_car(){
  if(digitalRead(left) == LOW && digitalRead(right) == LOW && stop_state == false)
      stop2_state = true;
      stop_state = true;
  if(digitalRead(left) == HIGH && digitalRead(right) == HIGH && stop_state == true)
      stop2_state = false;    
      stop_state = false;
}
void game(){
  start();
  
 if(timerBook == false && start_state == true && state_d == false && stop2_state == false) {
    timer.setTimeout(car_speed, enemy_car_down);
    timerBook = true;
 }
 if(state_d == false)
   My_car_shift();
 
   
 if(start_state == true)
    Dead();
 if(game_state == true)
    stop_car();
    
   /* if ((digitalRead(left) == LOW || digitalRead(right) == LOW) && state_d == true && state_score == true){
          INIT();
          loop();
      }*/
}
bool serial = false;
void loop(){
   game();
   timer.run();
   
  if(serial == false){ 
  Serial.println(EEPROM.read(1));
  Serial.println(EEPROM.read(2));
  Serial.println(EEPROM.read(3));
  Serial.println(EEPROM.read(4));
  Serial.println(EEPROM.read(5));
  Serial.println(EEPROM.read(6));
  Serial.println(EEPROM.read(7));
  Serial.println(EEPROM.read(8));
  Serial.println(EEPROM.read(9));
  serial = true;
  }
   
   /*for(i = 0; i < 20; i++)
    EEPROM.write(i,0);*/
}
