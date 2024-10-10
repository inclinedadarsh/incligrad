#include "../include/Value.h"
#include <cmath>

Value::Value(float data, std::string label, std::string op,
             std::vector<Value *> prev)
    : data(data), label(label), op(op), grad(0), prev(prev) {
  this->_backward = [this]() {};
}

std::ostream &operator<<(std::ostream &os, const Value &obj) {
  os << "Value(data=" << obj.data << ")";
  return os;
}

std::ostream &operator<<(std::ostream &os, const Value *obj) {
  if (obj) {
    os << "Value(data=" << obj->data << ")";
  } else {
    os << "NULL Pointer";
  }
  return os;
}

Value *Value::operator+(Value &other) {
  Value *out = new Value(this->data + other.data, "", "+", {this, &other});
  out->_backward = [this, &other, out]() {
    this->grad += 1 * out->grad;
    other.grad += 1 * out->grad;
  };
  return out;
}

Value *Value::operator+(float other) {
  Value *other_obj = new Value(other, "", "", {this});
  return *this + *other_obj;
}

Value *Value::operator*(Value &other) {
  Value *out = new Value(this->data * other.data, "", "*", {this, &other});
  out->_backward = [this, &other, out]() {
    this->grad += other.data * out->grad;
    other.grad += this->data * out->grad;
  };
  return out;
}

Value *Value::operator*(float other) {
  Value *other_obj = new Value(other, "", "", {this});
  return *this * *other_obj;
}

Value *Value::pow(float other) {
  std::string op = std::to_string(this->data) + "^" + std::to_string(other);
  Value *out = new Value(std::pow(this->data, other), "", op, {this});
  out->_backward = [this, other, out]() {
    this->grad += other * std::pow(this->data, other - 1) * out->grad;
  };
  return out;
}

Value *Value::operator/(Value &other) { return *this * *other.pow(-1); }

Value *Value::operator/(float other) {
  Value *other_obj = new Value(other, "", "", {this});
  return *this / *other_obj;
}

Value *Value::operator-() { return *this * -1; }

Value *Value::operator-(Value &other) { return *this + *(-other); }

Value *Value::tanh() {
  float n = this->data;
  float t = (std::exp(2 * n) - 1) / (std::exp(2 * n) + 1);
  Value *out = new Value(t, "", "tanh", {this});

  out->_backward = [this, out, t]() {
    this->grad += (1 - std::pow(t, 2)) * out->grad;
  };

  return out;
}

void Value::backward() {
  std::vector<Value *> topo;
  std::unordered_set<Value *> visited;

  build_topo(visited, this, topo);

  this->grad = 1;
  for (int i = topo.size() - 1; i >= 0; i--) {
    topo[i]->_backward();
  }
}

void Value::build_topo(std::unordered_set<Value *> &visited, Value *v,
                       std::vector<Value *> &topo) {
  if (visited.find(v) == visited.end()) {
    visited.insert(v);
    for (int i = 0; i < v->prev.size(); i++) {
      build_topo(visited, v->prev[i], topo);
    }
    topo.push_back(v);
  }
}
