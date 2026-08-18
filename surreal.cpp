#include "surreal.h"

SurrealValue::SurrealValue(std::vector<Surreal> l, std::vector<Surreal> r)
  : l(std::move(l)), r(std::move(r))
{}

Surreal::Surreal()
  : value(std::make_shared<const SurrealValue>(std::vector<Surreal>{}, std::vector<Surreal>{}))
{}

Surreal::Surreal(std::vector<Surreal> l, std::vector<Surreal> r)
  : value(std::make_shared<const SurrealValue>(std::move(l), std::move(r)))
{}

const std::vector<Surreal> & Surreal::l() const {
  return this->value->l;
}

const std::vector<Surreal> & Surreal::r() const {
  return this->value->r;
}

bool Surreal::is(const Surreal & other) const {
  return this->value == other.value;
}

bool operator<=(const Surreal & x, const Surreal & y) {
  if (x.is(y)) return true;
  
  for (const auto & l : x.value->l) {
    if (y <= l) return false;
  }

  for (const auto & r : y.value->r) {
    if (r <= x) return false;
  }

  return true;
}

bool operator<(const Surreal & x, const Surreal & y) {
  return !(y <= x);
}

bool operator>=(const Surreal & x, const Surreal & y) {
  return y <= x;
}

bool operator>(const Surreal & x, const Surreal & y) {
  return !(x <= y);
}

bool operator==(const Surreal & x, const Surreal & y) {
  return (x <= y) && (y <= x);
}

bool operator!=(const Surreal & x, const Surreal & y) {
  return !(x == y);
}
