#include "../include/Value.h"
#include <iostream>

int main(void) {
  Value *x1 = new Value(2.0, "x1");
  Value *x2 = new Value(0.0, "x2");
  Value *w1 = new Value(-3.0, "w1");
  Value *w2 = new Value(1.0, "w2");
  Value *b = new Value(6.8813735870195432, "b");

  Value *x1w1 = *x1 * *w1;
  x1w1->label = "x1 * w1";
  Value *x2w2 = *x2 * *w2;
  x2w2->label = "x2 * w2";

  Value *x1w1x2w2 = *x1w1 + *x2w2;
  x1w1x2w2->label = "x1*w1 + x2*w2";

  Value *n = *x1w1x2w2 + *b;
  n->label = "n";

  Value *o = n->tanh();
  o->label = "o";

  std::cout << "o data: " << o->data << std::endl;

  o->backward();

  std::cout << "x1 grad: " << x1->grad << std::endl;
  std::cout << "x2 grad: " << x2->grad << std::endl;
  std::cout << "w1 grad: " << w1->grad << std::endl;
  std::cout << "w2 grad: " << w2->grad << std::endl;

  // Clean up allocated memory
  delete x1;
  delete x2;
  delete w1;
  delete w2;
  delete b;
  delete x1w1;
  delete x2w2;
  delete x1w1x2w2;
  delete n;
  delete o;

  return 0;
}
