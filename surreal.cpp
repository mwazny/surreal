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

Surreal Surreal::simplify() const {
  Surreal zero{};
  auto max = std::ranges::max_element(this->l().begin(), this->l().end());
  auto min = std::ranges::min_element(this->r().begin(), this->r().end());

  if (!this->l().empty() && !this->r().empty()) {
    if (*max < zero && zero < *min ) {
      return zero;
    } else {
      return Surreal({max->simplify()}, {min->simplify()});
    }
  } else if (!this->l().empty() && *max >= zero) {
    return Surreal({max->simplify()}, {});
  } else if (!this->r().empty() && *min <= zero) {
    return Surreal({}, {min->simplify()});
  } else {
    return zero;
  }
}

std::string Surreal::to_string() const {
  auto comma_fold = [](const std::string && str, const Surreal & s) {
    return str.empty() ? s.to_string() : std::format("{},{}", str, s.to_string());
  };

  if (this->l().empty() && this->r().empty()) {
    return "{|}";
  } else {
    return std::format("{{{}|{}}}",
                       std::accumulate(this->l().begin(), this->l().end(), std::string(), comma_fold),
                       std::accumulate(this->r().begin(), this->r().end(), std::string(), comma_fold));
  }
}

bool operator<=(const Surreal & x, const Surreal & y) {
  if (x.is(y)) return true;
  
  for (const auto & l : x.l()) {
    if (y <= l) return false;
  }

  for (const auto & r : y.r()) {
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

Surreal operator+(const Surreal & x) {
  return x.simplify();
}

Surreal operator+(const Surreal & x, const Surreal & y) {
  Surreal zero{};

  if (x == zero && y == zero) return zero;
  if (x == zero) return y;
  if (y == zero) return x;

  std::vector<Surreal> l;
  std::vector<Surreal> r;

  for (const auto & xl : x.l()) l.emplace_back(xl + y);
  for (const auto & yl : y.l()) l.emplace_back(yl + x);
  for (const auto & xr : x.r()) r.emplace_back(xr + y);
  for (const auto & yr : y.r()) r.emplace_back(yr + x);

  return Surreal(l, r).simplify();
}

Surreal operator-(const Surreal & x) {
  Surreal zero{};

  if (x == zero) return zero;

  std::vector<Surreal> l;
  std::vector<Surreal> r;

  for (const auto & xl : x.l()) l.emplace_back(-xl);
  for (const auto & xr : x.r()) r.emplace_back(-xr);

  return Surreal(r, l).simplify();
}

Surreal operator-(const Surreal & x, const Surreal & y) {
  return (x + -y).simplify();
}

Surreal operator*(const Surreal & x, const Surreal & y) {
  Surreal zero{};
  Surreal pos_one({zero}, {});
  Surreal neg_one({}, {zero});

  if (x == zero || y == zero) return zero;
  if (x == pos_one) return y;
  if (y == pos_one) return x;
  if (x == neg_one) return -y;
  if (y == neg_one) return -x;

  std::vector<Surreal> l;
  std::vector<Surreal> r;

  for (const auto & xl : x.l()) {
    for (const auto & yl : y.l()) {
      l.emplace_back(xl * y + x * yl - xl * yl);
    }
  }
  for (const auto & xr : x.r()) {
    for (const auto & yr : y.r()) {
      l.emplace_back(xr * y + x * yr - xr * yr);
    }
  }
  for (const auto & xl : x.l()) {
    for (const auto & yr : y.r()) {
      r.emplace_back(xl * y + x * yr - xl * yr);
    }
  }
  for (const auto & xr : x.r()) {
    for (const auto & yl : y.l()) {
      r.emplace_back(yl * x + y * xr - xr * yl);
    }
  }

  return Surreal(l, r).simplify();
}
