#ifndef SURREAL_H
#define SURREAL_H

#include <memory>
#include <vector>
#include <string>
#include <format>
#include <numeric>
#include <algorithm>

class Surreal;

struct SurrealValue {
  std::vector<Surreal> l;
  std::vector<Surreal> r;

  SurrealValue(std::vector<Surreal> l, std::vector<Surreal> r);
};

class Surreal {
private:
  std::shared_ptr<const SurrealValue> value;

public:
  Surreal();
  Surreal(std::vector<Surreal> l, std::vector<Surreal> r);

  const std::vector<Surreal> & l() const;
  const std::vector<Surreal> & r() const;

  bool is(const Surreal &) const;
  Surreal simplify() const;

  std::string to_string() const;

  friend bool operator<=(const Surreal & x, const Surreal & y);
  friend bool operator<(const Surreal & x, const Surreal & y);
  friend bool operator>=(const Surreal & x, const Surreal & y);
  friend bool operator>(const Surreal & x, const Surreal & y);
  friend bool operator==(const Surreal & x, const Surreal & y);
  friend bool operator!=(const Surreal & x, const Surreal & y);

  friend Surreal operator+(const Surreal & x);
  friend Surreal operator+(const Surreal & x, const Surreal & y);
  friend Surreal operator-(const Surreal & x);
  friend Surreal operator-(const Surreal & x, const Surreal & y);
  friend Surreal operator*(const Surreal & x, const Surreal & y);
};

#endif
