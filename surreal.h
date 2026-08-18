#ifndef SURREAL_H
#define SURREAL_H

#include <memory>
#include <vector>

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

  friend bool operator<=(const Surreal & x, const Surreal & y);
  friend bool operator<(const Surreal & x, const Surreal & y);
  friend bool operator>=(const Surreal & x, const Surreal & y);
  friend bool operator>(const Surreal & x, const Surreal & y);
  friend bool operator==(const Surreal & x, const Surreal & y);
  friend bool operator!=(const Surreal & x, const Surreal & y);
};

#endif
