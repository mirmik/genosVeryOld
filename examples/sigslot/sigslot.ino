#include "genos.h"
#include "genos/sigslot/sigslot.h"


class A
{
  public:
  int mtd (int i, float f) 
  {
    Serial.print("mtd\t");
    Serial.print(i);
    Serial.print('\t');
    Serial.println(f);
  };
} a;

int func(int i, float f){
  Serial.print("func\t");
  Serial.print(i);
  Serial.print('\t');
  Serial.println(f);
};

sigslot<int,int, float> s;

void setup() {
  
  Serial.begin(9600);
  s += func;
  s += method(a, A::mtd);
  s(3, 0.97);
  Serial.println();
  
  s -= method(a, A::mtd);
  s(2, 42.24);
  Serial.println();
  
  s != func;
  s(8, 12.7);
  Serial.println();
  
  s.clear();
  s(8,9);
}

void loop() {
  
}