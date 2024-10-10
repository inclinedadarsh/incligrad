#include <cmath>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>
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
      : data(data), label(label), op(""), grad(0), prev(prev) {

    this->_backward = [this]() {};
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
  Value *operator+(Value &other) {
    Value *out = new Value(this->data + other.data, "", "+", {this, &other});
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

  /* Power */
  Value *pow(float other) {
    std::string op = std::to_string(this->data) + "^" + std::to_string(other);
    Value *out = new Value(std::pow(this->data, other), "", op, {this});
    out->_backward = [this, other, out]() {
      this->grad += other * std::pow(this->data, other - 1) * out->grad;
    };
    return out;
  }

  /* Dvision */
  Value *operator/(Value &other) { return *this * *other.pow(-1); }

  Value *operator/(float other) {
    Value *other_obj = new Value(other, "", "", {this});
    return *this / *other_obj;
  }

  /* Negation */
  Value *operator-() { return *this * -1; }

  /* Subtraction */
  Value *operator-(Value &other) { return *this + *(-other); }

  /* Tanh */
  Value *tanh() {
    float n = this->data;
    float t = (std::exp(2 * n) - 1) / (std::exp(2 * n) + 1);
    Value *out = new Value(t, "", "tanh", {this});

    out->_backward = [this, out, t]() {
      this->grad += (1 - std::pow(t, 2)) * out->grad;
    };

    return out;
  }

  /* Backward function */
  void backward() {
    std::vector<Value *> topo;
    std::unordered_set<Value *> visited;

    build_topo(visited, this, topo);

    this->grad = 1;
    for (int i = topo.size() - 1; i >= 0; i--) {
      topo[i]->_backward();
    }
  }

private:
  void build_topo(std::unordered_set<Value *> &visited, Value *v,
                  std::vector<Value *> &topo) {
    if (visited.find(v) == visited.end()) {
      visited.insert(v);
      for (int i = 0; i < v->prev.size(); i++) {
        build_topo(visited, v->prev[i], topo);
      }
      topo.push_back(v);
    }
  }
};

int main(void) {
  Value *a = new Value(2.0, "a");
  Value *b = new Value(3.0, "b");

  Value *c = *a - *b;
  c->label = "c";

  Value *d = new Value(-5.0, "d");

  Value *e = *c * *d;
  e->label = "e";

  e->backward();

  std::cout << "Grad of a: " << a->grad << std::endl;
  std::cout << "Grad of b: " << b->grad << std::endl;

  return 0;
}
