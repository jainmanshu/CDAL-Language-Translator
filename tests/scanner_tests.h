#include <cxxtest/TestSuite.h>

#include <stdio.h>
#include <iostream>
#include "include/read_input.h"
#include "include/scanner.h"

using namespace std;
namespace scanner = fcal::scanner;
class ScannerTestSuite : public CxxTest::TestSuite
{
public:
    /* A Scanner object is created in the test_setup_code method.
       This is a test, beginning with "test_", so that it is executed
       by the testing framework.  The scanner is used in some tests of
       the method "scan".
     */
    scanner::Scanner *s;
    void test_setup_code () {
      s = new scanner::Scanner();
    }


    // Tests for components and functions used by "scan"
    // --------------------------------------------------

    /* You should test the regular expressions you use to make and match
       regular expressions,and the functions used by makeRegex and
       matchRegex regex_tests.h.
       However, You will likely need to write several tests to
       adequately test  the functions that are called from "scan".
       Once you are confident that the components used by "scan"
       work properly, then you can run tests on the "scan" method itself.
    */

    // You should place tests for these other functions used by
    // scan below.
    void test_set_Next() {
         scanner::Token *tks = new scanner::Token();
         TS_ASSERT(tks != NULL);
         scanner::Token *next = new scanner::Token();
         TS_ASSERT(tks != NULL);
         tks->setNext(next);
         TS_ASSERT_EQUALS(tks->next(), next);
       }
 void test_set_terminal() {
     scanner::Token *tks = new scanner::Token();
     TS_ASSERT(tks != NULL);
     tks->setTerminal(scanner::kIntKwd);
     TS_ASSERT_EQUALS(tks->terminal(),scanner::kIntKwd);

 }
 void test_set_lexeme() {
    scanner::Token *tks = new scanner::Token();
    TS_ASSERT(tks != NULL);
    tks->setLexeme("int");
    TS_ASSERT(tks->lexeme() != "int a b c");
 }
    /* Below is one of the tests for these components in the project
       solution created by your instructor.  It uses a helper
       function function called "tokenMaker_tester", which you have
       not been given.  You are expected to design your own components
       for "scan" and your own mechanisms for easily testing them.

        void xtest_TokenMaker_leftCurly () {
            tokenMaker_tester ("{ ", "^\\{", leftCurly, "{");
        }

        Note that this test is here named "xtest_Token..." The leading
        "x" is so that cxxTest doesn't scan the line above and think
        it is an actual test that isn't commented out.  cxxTest is
        very simple and doesn't even process block comments.
    */
    // void test_scan_int() {
    //     scanner::Token *tks = s->Scan(" int ");
    //     TS_ASSERT(tks != NULL);
    //     TS_ASSERT_EQUALS(tks->terminal(), scanner::kIntKwd);
    //     TS_ASSERT(tks->next() == NULL);
    // }

    /* You must have at least one separate test case for each terminal
       symbol.  Thus, you need a test that will pass or fail based
       solely on the regular expression (and its corresponding code)
       for each terminal symbol.

       This requires a test case for each element of the enumerated
       type tokenType.  This may look something like the sample test
       shown in the comment above.
    */



    // Tests for "scan"
    // --------------------------------------------------

    /* Below are some helper functions and sample tests for testing the
       "scan" method on Scanner.
    */
  void testing_TokenMaker (const char* text, scanner::TokenType terminal, const std::string lexeme) {
   scanner::Token *tks = s->Scan(text);
   TS_ASSERT(tks != NULL);
   TS_ASSERT_EQUALS(tks->terminal(), terminal);
   TS_ASSERT_EQUALS(tks->lexeme(), lexeme);
 }
 void test_all_terminals_kwd () {
    const char* text[] = {"int", "float", "bool", "true",
                                  "false", "string", "matrix",
                                  "let", "in", "end", "if", "then",
                                  "else", "repeat", "while", "print",
                                  "to", "98564", "12.358",
                                  "\"This is a testing Example\"",
                                  "my_variable", "(", ")", "{", "}",
                                  "[", "]", ";", ":", "=", "+", "*",
                                  "-", "/", "<", "<=", ">", ">=", "==",
                                  "!=", "&&", "||", "!", "","$"};
    for (int i=0; i<=44; i++) {
      testing_TokenMaker(text[i], static_cast<scanner::TokenType>(i), text[i]);
    }
  }

    bool tokenMaker_tester (scanner::TokenType termTok, std::string lex, const char *str )
      {
          scanner::Token *tks = s->Scan(str);
          if (termTok == tks->terminal() &&  lex == tks->lexeme())
            return true;
            else
            return false;
      }

  // Test that a list of tokens has no lexicalError tokens.

      bool noLexicalErrors (scanner::Token *tks) {
        scanner::Token *currentToken = tks;
        while (currentToken != NULL) {
          if (currentToken->terminal() == scanner::kLexicalError) {
              printf("problem: %s\n",currentToken->lexeme().c_str());
              fflush(stdout);
                                return false;
            }
            else {
              currentToken = currentToken->next();
            }
        }
        return true;
    }

    /* A quick, but inaccurate, test for scanning files.  It only
       checks that no lexical errors occurred, not that the right
       tokens were returned.
    */
    void scanFileNoLexicalErrors(const char* filename) {
        char *text =  scanner::ReadInputFromFile(filename);
        TS_ASSERT (text);
        scanner::Token *tks = s->Scan(text);
        TS_ASSERT(tks != NULL);
        TS_ASSERT(noLexicalErrors(tks));
    }


    /* This function checks that the terminal fields in the list of
       tokens matches a list of terminals.
    */
  bool sameTerminals(scanner::Token *tks, int numTerms,
                     scanner::TokenType *ts) {
        scanner::Token *currentToken = tks;
        int termIndex = 0;
        while(currentToken != NULL && termIndex < numTerms) {

            if(currentToken->terminal() != ts[termIndex]) {
                printf("item at index: %i: terminal: %i should be terminal: %i\n",termIndex,currentToken->terminal(), ts[termIndex]);
				fflush(stdout);
                return false;
            }
            else {
                ++ termIndex;
                currentToken = currentToken->next();
            }
        }
        return true;
    }


    /* Below are the provided test files that your code should also
       pass.

       You may initially want to rename these tests to "xtest_..." so
       that the CxxTest framework does not see it as a test and won't
       run it as one.  This way you can focus on the tests that you'll
       write above for the individual terminal types first. Then focus
       on these tests.

    */

    // The "endOfFile" token is always the last one in the list of tokens.
    void test_terminal_int_kwd() {
      bool goodmatch = tokenMaker_tester (scanner::kIntKwd, "int", " int ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kIntKwd, "int", " xyzint");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_float_kwd() {
      bool goodmatch = tokenMaker_tester (scanner::kFloatKwd, "float", " float ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kFloatKwd, "int", " int ");
      TS_ASSERT (badmatch == false);

    }

    void test_terminal_bool_kwd() {
      bool goodmatch = tokenMaker_tester (scanner::kBoolKwd, "bool", " bool ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kBoolKwd, "bool", " boolean123");
      TS_ASSERT (badmatch == false);

    }

    void test_terminal_true_kwd() {
      bool goodmatch = tokenMaker_tester (scanner::kTrueKwd, "true", " true ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kTrueKwd, "true", " correct");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_false_kwd() {
      bool goodmatch = tokenMaker_tester (scanner::kFalseKwd, "false", " false ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kFalseKwd, "false", " wrong");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_string_kwd() {
      bool goodmatch = tokenMaker_tester (scanner::kStringKwd, "string", " string ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kStringKwd, "string", " string123");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_matrix_kwd() {
      bool goodmatch = tokenMaker_tester (scanner::kMatrixKwd, "matrix", " matrix ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kMatrixKwd, "matrix", " Matrixxyz");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_let_kwd() {
      bool goodmatch = tokenMaker_tester (scanner::kLetKwd, "let", " let ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kLetKwd, "let", " testing123");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_in_kwd() {
      bool goodmatch = tokenMaker_tester (scanner::kInKwd, "in", " in ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kInKwd, "in" , " testing123 ");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_end_kwd() {
      bool goodmatch = tokenMaker_tester (scanner::kEndKwd, "end", " end ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kEndKwd, "end", " ending");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_if_kwd() {
      bool goodmatch = tokenMaker_tester (scanner::kIfKwd, "if", " if ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kIfKwd, "if", " xyzabc");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_then_kwd() {
      bool goodmatch = tokenMaker_tester (scanner::kThenKwd, "then", " then ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kThenKwd, "then", " then123");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_else_kwd() {
      bool goodmatch = tokenMaker_tester (scanner::kElseKwd, "else", " else ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kElseKwd, "else", " else123");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_repeat_kwd() {
      bool goodmatch = tokenMaker_tester (scanner::kRepeatKwd, "repeat", " repeat ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kRepeatKwd, "repeat", " non-repeating");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_while_kwd() {
      bool goodmatch = tokenMaker_tester (scanner::kWhileKwd, "while", " while ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kWhileKwd, "while", " test");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_print_kwd() {
      bool goodmatch = tokenMaker_tester (scanner::kPrintKwd, "print", " print ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kPrintKwd, "print", " printing");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_to_kwd() {
      bool goodmatch = tokenMaker_tester (scanner::kToKwd, "to", " to ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kToKwd, "to", " tooo");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_int_const() {
      bool goodmatch = tokenMaker_tester (scanner::kIntConst, "25", " 25 ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kIntConst, "1234", " 123");
      TS_ASSERT (badmatch == false);
      }

    void test_terminal_float_const() {
      bool goodmatch = tokenMaker_tester (scanner::kFloatConst, "23.5", " 23.5 ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kFloatConst, "123.4", " 123.0");
      TS_ASSERT (badmatch == false);
      }

    void test_terminal_string_const() {
      bool goodmatch = tokenMaker_tester (scanner::kStringConst, "\"This is rolling\"","\"This is rolling\"");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kStringConst, "\"This is rolling\"","\"This is not rolling\"");
      TS_ASSERT (badmatch == false);
     }

    void test_terminal_variable_name() {
      bool goodmatch = tokenMaker_tester (scanner::kVariableName, "Var_123","Var_123");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kVariableName, "Var_1234","Var_Xyz");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_left_paren() {
      bool goodmatch = tokenMaker_tester (scanner::kLeftParen, "(", "( ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kLeftParen, "(", ")");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_right_paren() {
      bool goodmatch = tokenMaker_tester (scanner::kRightParen, ")", ") ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kRightParen, ")", "( ");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_left_curly() {
      bool goodmatch = tokenMaker_tester (scanner::kLeftCurly, "{", "{ ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kLeftCurly, "{", "} ");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_right_curly() {
      bool goodmatch = tokenMaker_tester (scanner::kRightCurly, "}", "} ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kRightCurly, "}", "{ ");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_left_square() {
      bool goodmatch = tokenMaker_tester (scanner::kLeftSquare, "[", "[ ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kLeftSquare, "[", "] ");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_right_square() {
      bool goodmatch = tokenMaker_tester (scanner::kRightSquare, "]", "] ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kRightSquare, "]", "[ ");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_semi_colon() {
      bool goodmatch = tokenMaker_tester (scanner::kSemiColon, ";", "; ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kSemiColon, ";", ", ");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_colon() {
      bool goodmatch = tokenMaker_tester (scanner::kColon, ":", ": ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kColon, ":", "|| ");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_assign() {
      bool goodmatch = tokenMaker_tester (scanner::kAssign, "=", "= ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kAssign, "=", "!= ");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_plus_sign() {
      bool goodmatch = tokenMaker_tester (scanner::kPlusSign, "+", "+ ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kPlusSign, "+", "- ");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_star_sign() {
      bool goodmatch = tokenMaker_tester (scanner::kStar, "*", "* ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kStar, "*", " + ");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_dash() {
      bool goodmatch = tokenMaker_tester (scanner::kDash, "-", " - ");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kDash, "-", "_");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_forward_slash() {
      bool goodmatch = tokenMaker_tester (scanner::kForwardSlash, "/", "/");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kForwardSlash, " / ", " p/p");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_less_than() {
      bool goodmatch = tokenMaker_tester (scanner::kLessThan, "<", "<");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kLessThan, "<", ">");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_less_than_equal() {
      bool goodmatch = tokenMaker_tester (scanner::kLessThanEqual, "<=", "<=");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kLessThanEqual, "<=", ">=");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_greater_than() {
      bool goodmatch = tokenMaker_tester (scanner::kGreaterThan, ">", ">");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kGreaterThan, ">", "<");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_greater_than_equal() {
      bool goodmatch = tokenMaker_tester (scanner::kGreaterThanEqual, ">=", ">=");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kGreaterThanEqual, ">=", "<=");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_equal_equal() {
      bool goodmatch = tokenMaker_tester (scanner::kEqualsEquals, "==", "==");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kEqualsEquals, "==", "!=");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_not_equals() {
      bool goodmatch = tokenMaker_tester (scanner::kNotEquals, "!=", "!=");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kNotEquals, "!=", "==");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_and_op() {
      bool goodmatch = tokenMaker_tester (scanner::kAndOp, "&&", "&&");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kAndOp, "&&", "||");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_or_op() {
      bool goodmatch = tokenMaker_tester (scanner::kOrOp, "||", "||");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kOrOp, "||", "|");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_not_op() {
      bool goodmatch = tokenMaker_tester (scanner::kNotOp, "!", "!");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kNotOp, "!", "!=");
      TS_ASSERT (badmatch == false);
    }

    void test_terminal_lexical_error() {
      bool goodmatch = tokenMaker_tester (scanner::kLexicalError, "@", "@");
      TS_ASSERT (goodmatch == true);
      bool badmatch = tokenMaker_tester (scanner::kLexicalError, "@", "&&");
      TS_ASSERT (badmatch == false);
    }
    void test_scan_empty() {
        scanner::Token *tks = s->Scan("  ");
        TS_ASSERT(tks != NULL);
        TS_ASSERT_EQUALS(tks->terminal(), scanner::kEndOfFile);
        TS_ASSERT(tks->next() == NULL);
    }

    void test_scan_empty_comment() {
        scanner::Token *tks = s->Scan(" /* a comment */ ");
        TS_ASSERT(tks != NULL);
        TS_ASSERT_EQUALS(tks->terminal(), scanner::kEndOfFile);
        TS_ASSERT(tks->next() == NULL);
    }


    // When a lexical error occurs, the scanner creates a token with a
    // single-character lexeme and lexicalError as the terminal.
     void test_scan_lexicalErrors() {
          scanner::Token *tks = s->Scan("$&1 ");
          TS_ASSERT(tks != NULL);
          TS_ASSERT_EQUALS(tks->terminal(), scanner::kLexicalError);
          TS_ASSERT_EQUALS(tks->lexeme(), "$");
          tks = tks->next();
          TS_ASSERT(tks != NULL);
          TS_ASSERT_EQUALS(tks->terminal(), scanner::kLexicalError);
          TS_ASSERT_EQUALS(tks->lexeme(), "&");
          tks = tks->next();
          TS_ASSERT(tks != NULL);
          TS_ASSERT_EQUALS(tks->terminal(), scanner::kIntConst);
          TS_ASSERT_EQUALS(tks->lexeme(), "1");
          tks = tks->next();
          TS_ASSERT(tks != NULL);
          TS_ASSERT_EQUALS(tks->terminal(), scanner::kEndOfFile);
          TS_ASSERT(tks->next() == NULL);
      }


    // A test for scanning numbers and a variable.

        void test_scan_some_operator() {
         scanner::Token *tks = s->Scan(" 123 && 12.34");
         TS_ASSERT(tks != NULL);
         scanner::TokenType ts[] = { scanner::kIntConst, scanner::kAndOp, scanner::kFloatConst,
                                            scanner::kEndOfFile };
         TS_ASSERT( sameTerminals( tks, 2, ts));
     }

    void test_scan_nums_vars() {
        scanner::Token *tks = s->Scan(" 123 x 12.34 ");
        TS_ASSERT(tks != NULL);
        scanner::TokenType ts[] = { scanner::kIntConst, scanner::kVariableName,
                                           scanner::kFloatConst, scanner::kEndOfFile };
        TS_ASSERT( sameTerminals( tks, 4, ts));
    }


    /* This test checks that the scanner returns a list of tokens with
       the correct terminal fields.  It doesn't check that the lexemes
       are correct.
     */

        void test_scan_bad_syntax_good_tokens() {
            const char *filename = "./samples/bad_syntax_good_tokens.dsl";
            char *text =  scanner::ReadInputFromFile(filename);
            TS_ASSERT(text);
            scanner::Token *tks = NULL;
            tks = s->Scan( text);
            TS_ASSERT(tks != NULL);
            scanner::TokenType ts[] = {
              scanner::kIntConst, scanner::kIntConst, scanner::kIntConst, scanner::kIntConst,
              scanner::kStringConst, scanner::kStringConst, scanner::kStringConst,
              scanner::kFloatConst, scanner::kFloatConst, scanner::kFloatConst,
              scanner::kMatrixKwd,
              scanner::kSemiColon, scanner::kColon, scanner::kToKwd,
              scanner::kLeftCurly, scanner::kLeftParen, scanner::kRightCurly, scanner::kRightParen,
              scanner::kPlusSign, scanner::kStar, scanner::kDash, scanner::kForwardSlash,
              scanner::kEqualsEquals, scanner::kLessThanEqual,
              scanner::kGreaterThanEqual, scanner::kNotEquals,
              scanner::kAssign,
              scanner::kVariableName, scanner::kVariableName, scanner::kVariableName, scanner::kVariableName,
              scanner::kVariableName, scanner::kVariableName, scanner::kVariableName,
              scanner::kIntKwd, scanner::kFloatKwd, scanner::kStringKwd,
              scanner::kEndOfFile
            };
            int count = 38;
            TS_ASSERT( sameTerminals( tks, count, ts));
        }

    void test_scan_sample_forestLoss() {
        scanFileNoLexicalErrors("./samples/forest_loss_v2.dsl");
    }



};
