#include <cxxtest/TestSuite.h>

#include "include/ext_token.h"
#include "include/parse_result.h"
#include "include/parser.h"
#include "include/read_input.h"
#include "include/scanner.h"

#include <sstream>

using namespace std;
using namespace fcal::scanner;
using namespace fcal::parser;

class ParserTestSuite : public CxxTest::TestSuite {
 public:

  Parser *p;

  void test_setup_code() {
    p = new Parser();
    TS_ASSERT(p);
  }

  void test_parse_bad_syntax() {
    const char *text =
        ReadInputFromFile("./samples/bad_syntax_good_tokens.dsl");
    TS_ASSERT(text);
    ParseResult pr = p->Parse(text);
    TS_ASSERT(!pr.ok());
  }

  void test_parse_sample_1() {
    const char *filename = "./samples/sample_1.dsl";
    const char *text = ReadInputFromFile(filename);
    TS_ASSERT(text);
    ParseResult pr = p->Parse(text);
    string msg(filename);
    msg += "\n" + pr.errors();
    TSM_ASSERT(msg, pr.ok());
  }

  void test_parse_sample_2() {
    const char *filename = "./samples/sample_2.dsl";
    const char *text = ReadInputFromFile(filename);
    TS_ASSERT(text);
    ParseResult pr = p->Parse(text);
    string msg(filename);
    msg += "\n" + pr.errors();
    TSM_ASSERT(msg, pr.ok());
  }

  void test_parse_sample_3() {
    const char *filename = "./samples/sample_3.dsl";
    const char *text = ReadInputFromFile(filename);
    TS_ASSERT(text);
    ParseResult pr = p->Parse(text);
    string msg(filename);
    msg += "\n" + pr.errors();
    TSM_ASSERT(msg, pr.ok());
  }

  void test_parse_sample_4() {
    const char *filename = "./samples/sample_4.dsl";
    const char *text = ReadInputFromFile(filename);
    TS_ASSERT(text);
    ParseResult pr = p->Parse(text);
    string msg(filename);
    msg += "\n" + pr.errors();
    TSM_ASSERT(msg, pr.ok());
  }

  void test_parse_sample_8() {
    const char *filename = "./samples/sample_8.dsl";
    const char *text = ReadInputFromFile(filename);
    TS_ASSERT(text);
    ParseResult pr = p->Parse(text);
    string msg(filename);
    msg += "\n" + pr.errors();
    TSM_ASSERT(msg, pr.ok());
  }

  void test_parse_sample_5() {
    const char *filename = "./samples/sample_5.dsl";
    const char *text = ReadInputFromFile(filename);
    TS_ASSERT(text);
    // Scanner * s = new Scanner();
    // Token *tks = s->Scan(text);
    // Token * temp = tks;
    // while(temp != NULL) {
    //   std::string ttemp = temp->lexeme();
    //   std::cout << ttemp+"\n";
    //   temp = temp->next();
    // }
    ParseResult pr = p->Parse(text);
    string msg(filename);
    msg += "\n" + pr.errors();
    TSM_ASSERT(msg, pr.ok());
  }

/*****
 * When you have constructed the fcal program specified in the
 * iteration 2 specifications, change the name xtest_parse_mysample below
 * to test_parse_mysample and, if you have created a syntactically correct
 * program, the test should pass when you run it!
 *****/
  void test_parse_mysample() {
    const char *filename = "./samples/mysample.dsl";
    const char *text = ReadInputFromFile(filename);
    TS_ASSERT(text);
    ParseResult pr = p->Parse(text);
    string msg(filename);
    msg += "\n" + pr.errors();
    TSM_ASSERT(msg, pr.ok());
  }

  void test_parse_forestLossV2() {
    const char *filename = "./samples/forest_loss_v2.dsl";
    const char *text = ReadInputFromFile(filename);
    TS_ASSERT(text);
    ParseResult pr = p->Parse(text);
    string msg(filename);
    msg += "\n" + pr.errors();
    TSM_ASSERT(msg, pr.ok());
  }
};
