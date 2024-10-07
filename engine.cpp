#include <iostream>
#include <string>

class Value {
public:
  float data;
  float grad;
  std::string op;
  std::string label;

  /* Constructor starts */
  /* Constructor for value object without labels */
  Value(float d) {
    this->data = d;
    this->label = "";
    this->grad = 0;
    this->op = "";
  }

  /* Constructor for value object with labels */
  Value(float d, std::string l) {
    this->data = d;
    this->label = l;
    this->grad = 0;
    this->op = "";
  }
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
  Value *operator+(Value const &other) {
    Value *out = new Value(this->data + other.data);
    return out;
  }

  /* Multiplication */
  Value *operator*(Value const &other) {
    Value *out = new Value(this->data * other.data);
    return out;
  }
};

int main(void) {
  Value *a = new Value(2., "a");
  Value *b = new Value(3., "b");
  Value *c = *a + *b;
  c->label = "c";
  Value *d = new Value(10., "d");
  Value *e = *d * *c;
  e->label = "e";

  std::cout << *e;
  return 0;
}
