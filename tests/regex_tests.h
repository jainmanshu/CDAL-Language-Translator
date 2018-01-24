#include <cxxtest/TestSuite.h>
#include "include/regex.h"

using namespace std;
class RegexTestSuite : public CxxTest::TestSuite {
 public:
  // Tests for makeRegex and matchRegex
  // --------------------------------------------------
  /* These tests ensure that the makeRegex and matchRegex work as
     expected.  These tests are independent from the scanner or
     WordCount application.
   */

  void test_make_matchRegex_match(void) {
    regex_t *re = fcal::scanner::make_regex("^[0-9]+");
    TS_ASSERT(re);
    int numMatchedChars = fcal::scanner::match_regex(re, "123 ");
    TS_ASSERT(numMatchedChars == 3);
  }

  void test_make_matchRegex_no_match(void) {
    regex_t *re = fcal::scanner::make_regex("^[0-9]+");
    TS_ASSERT(re);
    int numMatchedChars = fcal::scanner::match_regex(re, " 123 ");
    TS_ASSERT(numMatchedChars == 0);
  }

  void test_make_matchRegex_match_string_copy(void) {
    regex_t *re = fcal::scanner::make_regex("^[0-9]+");
    TS_ASSERT(re);
    const char *text = "123 ";
    int numMatchedChars = fcal::scanner::match_regex(re, text);
    TS_ASSERT(numMatchedChars == 3);
    std::string lex(text, numMatchedChars);
    TS_ASSERT_EQUALS(lex, "123");
  }

  void test_make_matchRegex_int_keyword(void) {
    regex_t *re = fcal::scanner::make_regex("^int");
    TS_ASSERT(re);
    int numMatchedChars = fcal::scanner::match_regex(re, "int ");
    TS_ASSERT(numMatchedChars == 3);
  }

  void test_make_matchRegex_float_keyword(void) {
    regex_t *re = fcal::scanner::make_regex("^float");
    TS_ASSERT(re);
    int numMatchedChars = fcal::scanner::match_regex(re, "float ");
    TS_ASSERT(numMatchedChars == 5);
  }

  void test_make_matchRegex_String_keyword(void) {
    regex_t *re = fcal::scanner::make_regex("^String");
    TS_ASSERT(re);
    int numMatchedChars = fcal::scanner::match_regex(re, "String ");
    TS_ASSERT(numMatchedChars == 6);
  }

  void test_make_matchRegex_Matrix_keyword(void) {
    regex_t *re = fcal::scanner::make_regex("^Matrix");
    TS_ASSERT(re);
    int numMatchedChars = fcal::scanner::match_regex(re, "Matrix ");
    TS_ASSERT(numMatchedChars == 6);
  }

  // regex test variable name
  void test_make_matchRegex_Variable_keyword(void) {
    regex_t *re = fcal::scanner::make_regex("^[_a-zA-Z][_a-zA-Z0-9]*");
    TS_ASSERT(re);
    int numMatchedChars = fcal::scanner::match_regex(re, "stupid123 ");
    TS_ASSERT(numMatchedChars == 9);
  }

  // regex test int const
  void test_make_matchRegex_int_const_keyword(void) {
    regex_t *re = fcal::scanner::make_regex("^[0-9]+");
    TS_ASSERT(re);
    int numMatchedChars = fcal::scanner::match_regex(re, "2 ");
    TS_ASSERT(numMatchedChars == 1);
  }
};
