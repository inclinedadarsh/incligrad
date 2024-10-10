#ifndef VALUE_H
#define VALUE_H

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

  Value(float data, std::string label = "", std::string op = "",
        std::vector<Value *> prev = {});

  friend std::ostream &operator<<(std::ostream &os, const Value &obj);
  friend std::ostream &operator<<(std::ostream &os, const Value *obj);

  Value *operator+(Value &other);
  Value *operator+(float other);
  Value *operator*(Value &other);
  Value *operator*(float other);
  Value *pow(float other);
  Value *operator/(Value &other);
  Value *operator/(float other);
  Value *operator-();
  Value *operator-(Value &other);
  Value *tanh();

  void backward();

private:
  void build_topo(std::unordered_set<Value *> &visited, Value *v,
                  std::vector<Value *> &topo);
};

#endif
