#include <iostream>
#include <string>

#include "surreal.h"

void assert_true(bool test, const std::string & description);

void test_compare_lte();
void test_compare_lt();
void test_compare_gte();
void test_compare_gt();
void test_compare_eq();
void test_compare_neq();

void test_add();
void test_sub();

void test_simplify();
void test_to_string();

int main() {
  test_compare_lte();
  test_compare_lt();
  test_compare_gte();
  test_compare_gt();
  test_compare_eq();
  test_compare_neq();

  test_add();
  test_sub();

  test_simplify();
  test_to_string();
  
  return 0;
}

void assert_true(bool test, const std::string & description) {
  std::cout <<  (test ? "[ OK ] " : "[Fail] ") << description << std::endl;
}

void test_compare_lte() {
  Surreal zero{};                      // { | } = 0
  Surreal pos_one({zero}, {});         // {0| } = 1
  Surreal neg_one({}, {zero});         // { |0} = -1
  Surreal pos_half({zero}, {pos_one}); // {0|1} = 1/2
  Surreal neg_half({neg_one}, {zero}); // {-1|0} = -1/2

  assert_true(neg_one <= neg_half, "Negative one is less or equal negative half");
  assert_true(neg_half <= zero, "Negative half is less or equal zero");
  assert_true(zero <= pos_half, "Zero is less or equal plus half");
  assert_true(pos_half <= pos_one, "Plus half is less or equal plus one");
  
  assert_true(neg_half <= pos_half, "Negative half is less or equal plus half");
  assert_true(neg_one <= pos_one, "Negative one is less or equal plus one");
  
  assert_true(neg_one <= neg_one, "Negative one is less or equal negative one");
  assert_true(neg_half <= neg_half, "Negative half is less or equal negative half");
  assert_true(zero <= zero, "Zero is less or equal zero");
  assert_true(pos_half <= pos_half, "Plus half is less or equal plus half");
  assert_true(pos_one <= pos_one, "Plus one is less or equal plus one");
}

void test_compare_lt() {
  Surreal zero{};                      // { | } = 0
  Surreal pos_one({zero}, {});         // {0| } = 1
  Surreal neg_one({}, {zero});         // { |0} = -1
  Surreal pos_half({zero}, {pos_one}); // {0|1} = 1/2
  Surreal neg_half({neg_one}, {zero}); // {-1|0} = -1/2

  assert_true(neg_one < neg_half, "Negative one is less negative half");
  assert_true(neg_half < zero, "Negative half is less zero");
  assert_true(zero < pos_half, "Zero is less plus half");
  assert_true(pos_half < pos_one, "Plus half is less plus one");
  
  assert_true(neg_half < pos_half, "Negative half is less plus half");
  assert_true(neg_one < pos_one, "Negative one is less plus one");
}

void test_compare_gte() {
  Surreal zero{};                      // { | } = 0
  Surreal pos_one({zero}, {});         // {0| } = 1
  Surreal neg_one({}, {zero});         // { |0} = -1
  Surreal pos_half({zero}, {pos_one}); // {0|1} = 1/2
  Surreal neg_half({neg_one}, {zero}); // {-1|0} = -1/2

  assert_true(pos_one >= pos_half, "Plus one is greater or equal plus half");
  assert_true(pos_half >= zero, "Plus half is greater or equal zero");
  assert_true(zero >= neg_half, "Zero is greater or equal negative half");
  assert_true(neg_half >= neg_one, "Negative half is greater or equal negative one");

  assert_true(pos_one >= neg_one, "Plus one is greater or equal negative one");
  assert_true(pos_half >= neg_half, "Plus half is greater or equal negative half");
  
  assert_true(neg_one >= neg_one, "Negative one is greater or equal negative one");
  assert_true(neg_half >= neg_half, "Negative half is greater or equal negative half");
  assert_true(zero >= zero, "Zero is greater or equal zero");
  assert_true(pos_half >= pos_half, "Plus half is greater or equal plus half");
  assert_true(pos_one >= pos_one, "Plus one is greater or equal plus one");
}

void test_compare_gt() {
  Surreal zero{};                      // { | } = 0
  Surreal pos_one({zero}, {});         // {0| } = 1
  Surreal neg_one({}, {zero});         // { |0} = -1
  Surreal pos_half({zero}, {pos_one}); // {0|1} = 1/2
  Surreal neg_half({neg_one}, {zero}); // {-1|0} = -1/2

  assert_true(pos_one > pos_half, "Plus one is greater plus half");
  assert_true(pos_half > zero, "Plus half is greater zero");
  assert_true(zero > neg_half, "Zero is greater negative half");
  assert_true(neg_half > neg_one, "Negative half is greater negative one");

  assert_true(pos_one > neg_one, "Plus one is greater negative one");
  assert_true(pos_half > neg_half, "Plus half is greater negative half");
}

void test_compare_eq() {
  Surreal zero{};                      // { | } = 0
  Surreal pos_one({zero}, {});         // {0| } = 1
  Surreal neg_one({}, {zero});         // { |0} = -1
  Surreal pos_half({zero}, {pos_one}); // {0|1} = 1/2
  Surreal neg_half({neg_one}, {zero}); // {-1|0} = -1/2

  Surreal zero_alt({neg_one}, {pos_one});   // {-1|1} = 0
  Surreal pos_one_alt({neg_one, zero}, {}); // {-1, 0 | } = 1

  assert_true(neg_one == neg_one, "Negative one is equals negative one");
  assert_true(neg_half == neg_half, "Negative half is equals negative half");
  assert_true(zero == zero, "Zero is equals zero");
  assert_true(pos_half == pos_half, "Plus half is equals plus half");
  assert_true(pos_one == pos_one, "Plus one is equals plus one");

  assert_true(zero == zero_alt, "Zero equals alt zero");
  assert_true(pos_one == pos_one_alt, "Plus one equals alt plus one");
}

void test_compare_neq() {
  Surreal zero{};                      // { | } = 0
  Surreal pos_one({zero}, {});         // {0| } = 1
  Surreal neg_one({}, {zero});         // { |0} = -1
  Surreal pos_half({zero}, {pos_one}); // {0|1} = 1/2
  Surreal neg_half({neg_one}, {zero}); // {-1|0} = -1/2

  assert_true(zero != pos_one, "Zero is not equals to plus one");
  assert_true(pos_one != neg_one, "Plus one is not equals to negative one");
  assert_true(neg_one != pos_half, "Negative one is not equals plus half");
  assert_true(pos_half != neg_half, "Plus half is not equals negative half");
}

void test_add() {
  Surreal zero{};                      // { | } = 0
  Surreal pos_one({zero}, {});         // {0| } = 1
  Surreal pos_two({pos_one}, {});      // {1| } = 2
  Surreal pos_half({zero}, {pos_one}); // {0|1} = 1/2

  assert_true((zero + zero) == zero, "Zero plus zero equals zero");
  assert_true((zero + pos_one) == pos_one, "Zero plus one equals one");
  assert_true((pos_one + zero) == pos_one, "One plus zero equals one");
  assert_true((pos_one + pos_one) == pos_two, "One plus one equals two");
  assert_true((pos_half + pos_half) == pos_one, "Half plus half equals one");
}

void test_sub() {
  Surreal zero{};                      // { | } = 0
  Surreal pos_one({zero}, {});         // {0| } = 1
  Surreal neg_one({}, {zero});         // { |0} = -1
  Surreal pos_two({pos_one}, {});      // {1| } = 2
  Surreal pos_half({zero}, {pos_one}); // {0|1} = 1/2

  assert_true((zero - zero) == zero, "Zero minus zero equals zero");
  assert_true((zero - pos_one) == neg_one, "Zero minus one equals negative one");
  assert_true((pos_one - zero) == pos_one, "One minus zero equals one");
  assert_true((pos_one - pos_one) == zero, "One minus one equals zero");
  assert_true((pos_one - pos_half) == pos_half, "One minus half equals half");
  assert_true((pos_half - pos_half) == zero, "Half minus half equals zero");
}

void test_simplify() {
  Surreal zero{};                                 // { | } = 0
  Surreal pos_one({zero}, {});                    // {0| } = 1
  Surreal neg_one({}, {zero});                    // { |0} = -1
  Surreal pos_two({pos_one}, {});                 // {1| } = 2
  Surreal neg_two({}, {neg_one});                 // { |-1} = -2
  Surreal pos_three({pos_two}, {});               // {2| } = 3
  Surreal pos_one_and_half({pos_one}, {pos_two}); // {1|2} = 3/2

  Surreal zero_alt({neg_one}, {pos_one});                // {-1|1} = 0
  Surreal pos_one_alt({neg_two, neg_one, zero}, {});     // {-2,-1,0| } = 1
  Surreal pos_two_alt1({pos_one, }, {pos_three});        // {1|3} = 2
  Surreal pos_two_alt2({pos_one_and_half}, {pos_three}); // {3/2|3} = 2

  assert_true(zero == zero_alt.simplify(), "Zero equals simplified alt zero");
  assert_true(pos_one == pos_one_alt.simplify(), "Plus one equals simplified alt plus one");
  assert_true(pos_two == pos_two_alt1.simplify(), "Plus two equals simplified alt plus two");
  assert_true(pos_two == pos_two_alt2.simplify(), "Plus two equals simplified alt plus two");
}

void test_to_string() {
  Surreal zero{};                                 // { | } = 0
  Surreal pos_one({zero}, {});                    // {0| } = 1
  Surreal neg_one({}, {zero});                    // { |0} = -1
  Surreal pos_two({pos_one}, {});                 // {1| } = 2
  Surreal neg_two({}, {neg_one});                 // { |-1} = -2
  Surreal pos_one_and_half({pos_one}, {pos_two}); // {1|2} = 3/2

  assert_true(zero.to_string() == "{|}", "Zero to string equals `{|}`");
  assert_true(pos_one.to_string() == "{{|}|}", "Plus one to string equals `{{|}|}`");
  assert_true(neg_one.to_string() == "{|{|}}", "Negative one to string equals `{|{|}}`");
  assert_true(pos_two.to_string() == "{{{|}|}|}", "Plus two to string equals `{{{|}|}|}`");
  assert_true(neg_two.to_string() == "{|{|{|}}}", "Negative two to string equals `{|{|{|}}}`");
  assert_true(pos_one_and_half.to_string() == "{{{|}|}|{{{|}|}|}}",
              "Plus one and half to string equals `{{{|}|}|{{{|}|}|}}`");
}
