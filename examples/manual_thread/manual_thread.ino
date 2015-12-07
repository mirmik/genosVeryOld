#include "genos.h"
#include "genos/subst/subst.h"
#include "genos/stack/static_stack.h"


thread first, second , third;
static_stack<300> stck1;
static_stack<300> stck2;


void setup() {
  pinMode(13, 1);
  Serial.begin(9600);
  
  init_current_thread(&first, RAMEND);
  set_stack_thread(&second, stck1.top());
  set_stack_thread(&third,  stck2.top());
  
  if (!fork_thread(&second)) while (1) loop2();
  if (!fork_thread(&third))  while (1) loop3();
};


void loop() {
  digitalWrite(13, 0);
  change_thread(&second);
  digitalWrite(13, 1);
  change_thread(&second);
}

void loop2() {
  Serial.println("Loop2!");
  change_thread(&third);
};

void loop3() {
  delay(200);
  change_thread(&first);
};