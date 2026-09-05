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
void test_neg();
void test_mul();
void test_distributivity();

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
  test_neg();
  test_mul();
  test_distributivity();

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

  assert_true(neg_one <= neg_half, "-1 <= -1/2");
  assert_true(neg_half <= zero, "-1/2 <= 0");
  assert_true(zero <= pos_half, "0 <= 1/2");
  assert_true(pos_half <= pos_one, "1/2 <= 1");
  
  assert_true(neg_half <= pos_half, "-1/2 <= 1/2");
  assert_true(neg_one <= pos_one, "-1 <= 1");
  
  assert_true(neg_one <= neg_one, "-1 <= -1");
  assert_true(neg_half <= neg_half, "-1/2 <= -1/2");
  assert_true(zero <= zero, "0 <= 0");
  assert_true(pos_half <= pos_half, "1/2 <= 1/2");
  assert_true(pos_one <= pos_one, "1 <= 1");
}

void test_compare_lt() {
  Surreal zero{};                      // { | } = 0
  Surreal pos_one({zero}, {});         // {0| } = 1
  Surreal neg_one({}, {zero});         // { |0} = -1
  Surreal pos_half({zero}, {pos_one}); // {0|1} = 1/2
  Surreal neg_half({neg_one}, {zero}); // {-1|0} = -1/2

  assert_true(neg_one < neg_half, "-1 < -1/2");
  assert_true(neg_half < zero, "-1/2 < 0");
  assert_true(zero < pos_half, "0 < 1/2");
  assert_true(pos_half < pos_one, "1/2 < 1");
  
  assert_true(neg_half < pos_half, "-1/2 < 1/2");
  assert_true(neg_one < pos_one, "-1 < 1");
}

void test_compare_gte() {
  Surreal zero{};                      // { | } = 0
  Surreal pos_one({zero}, {});         // {0| } = 1
  Surreal neg_one({}, {zero});         // { |0} = -1
  Surreal pos_half({zero}, {pos_one}); // {0|1} = 1/2
  Surreal neg_half({neg_one}, {zero}); // {-1|0} = -1/2

  assert_true(pos_one >= pos_half, "1 >= 1/2");
  assert_true(pos_half >= zero, "1/2 >= 0");
  assert_true(zero >= neg_half, "0 >= -1/2");
  assert_true(neg_half >= neg_one, "-1/2 >= -1");

  assert_true(pos_one >= neg_one, "1 >= -1");
  assert_true(pos_half >= neg_half, "1/2 >= -1/2");
  
  assert_true(neg_one >= neg_one, "-1 >= -1");
  assert_true(neg_half >= neg_half, "-1/2 >= -1/2");
  assert_true(zero >= zero, "0 >= 0");
  assert_true(pos_half >= pos_half, "1/2 >= 1/2");
  assert_true(pos_one >= pos_one, "1 >= 1");
}

void test_compare_gt() {
  Surreal zero{};                      // { | } = 0
  Surreal pos_one({zero}, {});         // {0| } = 1
  Surreal neg_one({}, {zero});         // { |0} = -1
  Surreal pos_half({zero}, {pos_one}); // {0|1} = 1/2
  Surreal neg_half({neg_one}, {zero}); // {-1|0} = -1/2

  assert_true(pos_one > pos_half, "1 > 1/2");
  assert_true(pos_half > zero, "1/2 > 0");
  assert_true(zero > neg_half, "0 > -1/2");
  assert_true(neg_half > neg_one, "-1/2 > -1");

  assert_true(pos_one > neg_one, "1 > -1");
  assert_true(pos_half > neg_half, "1/2 > -1/2");
}

void test_compare_eq() {
  Surreal zero{};                      // { | } = 0
  Surreal pos_one({zero}, {});         // {0| } = 1
  Surreal neg_one({}, {zero});         // { |0} = -1
  Surreal pos_half({zero}, {pos_one}); // {0|1} = 1/2
  Surreal neg_half({neg_one}, {zero}); // {-1|0} = -1/2

  Surreal zero_alt({neg_one}, {pos_one});   // {-1|1} = 0
  Surreal pos_one_alt({neg_one, zero}, {}); // {-1, 0 | } = 1

  assert_true(neg_one == neg_one, "0 == 0");
  assert_true(neg_half == neg_half, "-1/2 == -1/2");
  assert_true(zero == zero, "0 == 0");
  assert_true(pos_half == pos_half, "1/2 == 1/2");
  assert_true(pos_one == pos_one, "1 == 1");

  assert_true(zero == zero_alt, "{ | } == 0 == {-1|1}");
  assert_true(pos_one == pos_one_alt, "{0| } == 1 == {-1, 0 | }");
}

void test_compare_neq() {
  Surreal zero{};                      // { | } = 0
  Surreal pos_one({zero}, {});         // {0| } = 1
  Surreal neg_one({}, {zero});         // { |0} = -1
  Surreal pos_half({zero}, {pos_one}); // {0|1} = 1/2
  Surreal neg_half({neg_one}, {zero}); // {-1|0} = -1/2

  assert_true(zero != pos_one, "0 != 1");
  assert_true(pos_one != neg_one, "1 != -1");
  assert_true(neg_one != pos_half, "-1 != 1/2");
  assert_true(pos_half != neg_half, "1/2 != -1/2");
}

void test_add() {
  Surreal zero{};                      // { | } = 0
  Surreal pos_one({zero}, {});         // {0| } = 1
  Surreal neg_one({}, {zero});         // { |0} = -1
  Surreal pos_two({pos_one}, {});      // {1| } = 2
  Surreal pos_half({zero}, {pos_one}); // {0|1} = 1/2

  assert_true((zero + zero) == zero, "0 + 0 = 0");
  assert_true((zero + pos_one) == pos_one, "0 + 1 = 1");
  assert_true((zero + neg_one) == neg_one, "0 + -1 = -1");
  assert_true((pos_one + zero) == pos_one, "1 + 0 = 1");
  assert_true((pos_one + pos_one) == pos_two, "1 + 1 = 2");
  assert_true((pos_half + pos_half) == pos_one, "1/2 + 1/2 = 1");
}

void test_sub() {
  Surreal zero{};                      // { | } = 0
  Surreal pos_one({zero}, {});         // {0| } = 1
  Surreal neg_one({}, {zero});         // { |0} = -1
  Surreal pos_two({pos_one}, {});      // {1| } = 2
  Surreal pos_half({zero}, {pos_one}); // {0|1} = 1/2

  assert_true((zero - zero) == zero, "0 - 0 = 0");
  assert_true((zero - pos_one) == neg_one, "0 - 1 = -1");
  assert_true((zero - neg_one) == pos_one, "0 - -1 = 1");
  assert_true((pos_one - zero) == pos_one, "1 - 0 = 1");
  assert_true((pos_one - pos_one) == zero, "1 - 1 = 0");
  assert_true((pos_one - pos_half) == pos_half, "1 - 1/2 = 1/2");
  assert_true((pos_half - pos_half) == zero, "1/2 - 1/2 = 0");
}

void test_neg() {
  Surreal zero{};                      // { | } = 0
  Surreal pos_one({zero}, {});         // {0| } = 1
  Surreal neg_one({}, {zero});         // { |0} = -1

  assert_true(-zero == zero, "-0 = 0");
  assert_true(-pos_one == neg_one, "-(1) = -1");
  assert_true(-neg_one == pos_one, "-(-1) = 1");
}

void test_mul() {
  Surreal zero{};                      // { | } = 0
  Surreal pos_one({zero}, {});         // {0| } = 1
  Surreal neg_one({}, {zero});         // { |0} = -1
  Surreal pos_two({pos_one}, {});      // {1| } = 2
  Surreal pos_half({zero}, {pos_one}); // {0|1} = 1/2

  assert_true((zero * zero) == zero, "0 * 0 = 0");
  assert_true((zero * pos_one) == zero, "0 * 1 = 0");
  assert_true((zero * neg_one) == zero, "0 * -1 = 0");
  assert_true((pos_one * pos_one) == pos_one, "1 * 1 = 1");
  assert_true((pos_one * pos_two) == pos_two, "1 * 2 = 2");
  assert_true((pos_one * neg_one) == neg_one, "1 * -1 = -1");
  assert_true((neg_one * neg_one) == pos_one, "-1 * -1 = 1");
  assert_true((pos_two * pos_half) == pos_one, "2 * 1/2 = 1");
}

void test_distributivity() {
  Surreal zero{};                      // { | } = 0
  Surreal pos_one({zero}, {});         // {0| } = 1
  Surreal pos_half({zero}, {pos_one}); // {0|1} = 1/2

  // distributivity: a * (b + c) == (a * b) + (a * c)
  assert_true((pos_half * (pos_one + pos_one)) == ((pos_half * pos_one) + (pos_half * pos_one)),
              "1/2 * (1 + 1) == 1/2*1 + 1/2*1");
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

  assert_true(zero == zero_alt.simplify(), "{ | } = 0 = {-1|1}");
  assert_true(pos_one == pos_one_alt.simplify(), "{0| } = 1 = {-2,-1,0| }");
  assert_true(pos_two == pos_two_alt1.simplify(), "{1| } = 2 = {1|3}");
  assert_true(pos_two == pos_two_alt2.simplify(), "{1| } = 2 = {3/2|3}");
}

void test_to_string() {
  Surreal zero{};                                 // { | } = 0
  Surreal pos_one({zero}, {});                    // {0| } = 1
  Surreal neg_one({}, {zero});                    // { |0} = -1
  Surreal pos_two({pos_one}, {});                 // {1| } = 2
  Surreal neg_two({}, {neg_one});                 // { |-1} = -2
  Surreal pos_one_and_half({pos_one}, {pos_two}); // {1|2} = 3/2

  assert_true(zero.to_string() == "{|}", "0 = {|}");
  assert_true(pos_one.to_string() == "{{|}|}", "1 = {{|}|}");
  assert_true(neg_one.to_string() == "{|{|}}", "-1 = {|{|}}");
  assert_true(pos_two.to_string() == "{{{|}|}|}", "2 = {{{|}|}|}");
  assert_true(neg_two.to_string() == "{|{|{|}}}", "-2 = {|{|{|}}}");
  assert_true(pos_one_and_half.to_string() == "{{{|}|}|{{{|}|}|}}", "3/2 = {{{|}|}|{{{|}|}|}}");
}
