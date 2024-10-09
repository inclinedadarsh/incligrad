#include <cmath>
#include <iostream>
/*#include <stdexcept>*/
#include <functional>
#include <string>
#include <vector>

class Value {
public:
  float data;
  float grad;
  std::string op;
  std::string label;
  std::vector<Value *> prev;
  std::function<void()> _backward;

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
    /*void _backward() {*/
    /*  this->grad = 1 * out->grad;*/
    /*  this->data = 1 * out->grad;*/
    /*}*/
    /*out->backward = _backward;*/
    out->_backward = [this, &other, out]() {
      this->grad += 1 * out->grad;
      other.grad += 1 * out->grad;
    };
    return out;
  }

  Value *operator+(float other) {
    Value *other_obj = new Value(other, "", "", {this});
    return *this + *other_obj;
  }

  /* Multiplication */
  Value *operator*(Value &other) {
    /*if (other == nullptr) {*/
    /*  throw std::invalid_argument("Cannot add null arugment\n");*/
    /*}*/
    Value *out = new Value(this->data * other.data, "", "*", {this, &other});
    out->_backward = [this, &other, out]() {
      this->grad += other.data * out->grad;
      other.grad += this->data * out->grad;
    };
    return out;
  }

  Value *operator*(float other) {
    Value *other_obj = new Value(other, "", "", {this});
    return *this * *other_obj;
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

  Value *c = *a * *b;
  c->label = "c";

  std::cout << "c: " << c->data << std::endl;
  c->grad = 10;
  c->_backward();

  std::cout << "a grad: " << a->grad << std::endl;

  return 0;
}
