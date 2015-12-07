#include "genos.h"
#include "genos/iostream/iostream.h"
#include "genos/sigslot/sigslot.h"

using namespace genos;;

Serial_ostream_adapter SOA;
ostream os(SOA);

int func1(int i, float d){os << i*1 << d<< endl;};
int func2(int i, float d){os << i*2 << d<< endl;};
int func3(int i, float d){os << i*3 << d<< endl;};

class A{};
  
void setup() {
os << setw(10);
  sigslot<int,int, float> s;
  s += func1;
  s += func2;
  s += func3;
  s(3, 0.97);
  }

void loop() {

}