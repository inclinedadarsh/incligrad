#include <cmath>
#include <iostream>
/*#include <stdexcept>*/
#include <string>
#include <vector>

class Value {
public:
  float data;
  float grad;
  std::string op;
  std::string label;
  std::vector<Value *> prev;

  /* Constructor starts */
  Value(float data, std::string label = "", std::string op = "",
        std::vector<Value *> prev = {})
      : data(data), label(label), op(""), grad(0), prev(prev) {}
  /* Constructor ends */

  /* Methods for printing objects using std::cout */
  /* Method for object */
  friend std::ostream &operator<<(std::ostream &os, const Value &obj) {
    os << "Value(data=" << obj.data << ")" << std::endl;
    return os;
  }

  /* Method for object pointer */
  friend std::ostream &operator<<(std::ostream &os, const Value *obj) {
    if (obj) {
      os << "Value(data=" << obj->data << ")" << std::endl;
    } else {
      os << "NULL Pointer";
    }
    return os;
  }
  /* Printing methods end */

  /* General operators overloaded */
  /* Addition */
  Value *operator+(Value &other) {
    /*if (other == nullptr) {*/
    /*  throw std::invalid_argument("Cannot add null arugment\n");*/
    /*}*/
    Value *out = new Value(this->data + other.data, "", "+", {this, &other});
    return out;
  }

  Value *operator+(float other) {
    Value *other_obj = new Value(other, "", "", {this});
    Value *out =
        new Value(this->data + other_obj->data, "", "+", {this, other_obj});
    return out;
  }

  /* Multiplication */
  Value *operator*(Value &other) {
    /*if (other == nullptr) {*/
    /*  throw std::invalid_argument("Cannot add null arugment\n");*/
    /*}*/
    Value *out = new Value(this->data * other.data, "", "*", {this, &other});
    return out;
  }

  Value *operator*(float other) {
    Value *other_obj = new Value(other, "", "", {this});
    Value *out =
        new Value(this->data * other_obj->data, "", "*", {this, other_obj});
    return out;
  }
};

/*Value *operator+(Value *lhs, Value *rhs) {*/
/*  if (lhs == nullptr) {*/
/*    throw std::invalid_argument("Left-hand side cannot be null\n");*/
/*  }*/
/*  return lhs->operator+(rhs);*/
/*}*/

int main(void) {
  Value *a = new Value(2.0);
  Value *b = new Value(3.0);

  Value *c = *a + *b;
  c->label = "c";

  Value *d = new Value(10., "d");
  Value *e = *d * *c;
  e->label = "e";

  Value *f = *e + 3.5f;
  f->label = "f";

  Value *g = *f * 2;
  g->label = "g";

  return 0;
}
