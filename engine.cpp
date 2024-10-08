#include <iostream>
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
  /* Constructor for value object without labels */
  Value(float data) {
    this->data = data;
    this->label = "";
    this->grad = 0;
    this->op = "";
  }

  Value(float data, std::vector<Value *> prev) {
    this->data = data;
    this->label = "";
    this->grad = 0;
    this->op = "";
    this->prev = prev;
  }

  /* Constructor for value object with labels */
  Value(float data, std::string l) {
    this->data = data;
    this->label = l;
    this->grad = 0;
    this->op = "";
  }

  Value(float data, std::string l, std::vector<Value *> prev) {
    this->data = data;
    this->label = l;
    this->grad = 0;
    this->op = "";
    this->prev = prev;
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
  /* Addition of two objects */
  Value *operator+(Value const &other) {
    Value *out = new Value(this->data + other.data);
    return out;
  }

  /* Addition of an object and an integer */
  Value *operator+(int other) {
    Value *out = new Value(this->data + other);
    return out;
  }

  /* Addition of an object and an float */
  Value *operator+(float other) {
    Value *out = new Value(this->data + other);
    return out;
  }

  /* Multiplication */
  /* Multiplication of two objects */
  Value *operator*(Value const &other) {
    Value *out = new Value(this->data * other.data);
    return out;
  }

  /* Multiplication of an object and an integer */
  Value *operator*(int other) {
    Value *out = new Value(this->data * other);
    return out;
  }

  /* Multiplication of an object and an float */
  Value *operator*(float other) {
    Value *out = new Value(this->data * other);
    return out;
  }
};

/* Addition of an integer and an object */
Value *operator+(int other, const Value &self) {
  Value *out = new Value(self.data + other);
  return out;
}

/* Addition of an integer and an object */
Value *operator+(float other, const Value &self) {
  Value *out = new Value(self.data + other);
  return out;
}

/* Addition of an integer and an object */
Value *operator*(int other, const Value &self) {
  Value *out = new Value(self.data * other);
  return out;
}

/* Addition of an integer and an object */
Value *operator*(float other, const Value &self) {
  Value *out = new Value(self.data * other);
  return out;
}

int main(void) {
  Value *a = new Value(2., "a");
  Value *b = new Value(3., "b");
  Value *c = *a + *b;
  c->label = "c";
  Value *d = new Value(10., "d");
  Value *e = *d * *c;
  e->label = "e";
  Value *f = 3.5f + *e;
  Value *g = *f * 2;

  std::cout << *g;
  return 0;
}
