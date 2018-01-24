/*******************************************************************************
 * Name            : parser.h
 * Project         : fcal
 * Module          : parser
 * Description     : A recursive descent parser with operator precedence.
 *
 * Copyright       : 2017 CSCI3081W Staff. All rights reserved.
 * Original Author : Erik Van Wyk
 * Modifications by: Dan Challou, John Harwell
 *
 ******************************************************************************/

#ifndef PROJECT_INCLUDE_PARSER_H_
#define PROJECT_INCLUDE_PARSER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "include/parse_result.h"
#include "include/scanner.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace fcal {
namespace scanner {
class ExtToken;
} /* namespace scanner */
namespace parser {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/* This algorithms is based on the work of Douglas Crockford in "Top
 * Down Operator Precedence", a chapter in the book "Beautiful Code".
 * Mr. Crockford describes in his chapter how his work comes from that
 * of Based on algorithms described Vaughan Pratt in "Top Down Operator
 * Precedence", presented at the ACM Symposium on Principles of
 * Programming Languages.
 *
 * Douglas Crockford's chapter is available at
 *  http://javascript.crockford.com/tdop/tdop.html
 *
 * Vaughan Pratt's paper is available at
 *  http://portal.acm.org/citation.cfm?id=512931
 *
 * These are both quite interesting works and worth reading if you
 * find the problem of parsing to be an interesting one.
 */
class Parser {
 public:
  Parser(void)
      : curr_token_(NULL), prev_token_(NULL), stokens_(NULL), scanner_(NULL) {}
  ~Parser(void);

  ParseResult Parse(const char *text);
  // Parser methods for the nonterminals:

  ParseResult ParseProgram();
  ParseResult parse_decl();
  ParseResult parse_standard_decl();
  ParseResult parse_matrix_decl();
  ParseResult parse_stmts();
  ParseResult parse_stmt();
  ParseResult parse_expr(int rbp);
  // methods for parsing productions for Expr
  ParseResult parse_true_kwd();
  ParseResult parse_false_kwd();
  ParseResult parse_int_const();
  ParseResult parse_float_const();
  ParseResult parse_string_const();
  ParseResult parse_char_const();
  ParseResult parse_variable_name();
  ParseResult parse_nested_expr();
  ParseResult parse_not_expr();
  ParseResult parse_let_expr();
  ParseResult parse_if_expr();
  ParseResult parse_addition(ParseResult left);
  ParseResult parse_multiplication(ParseResult left);
  ParseResult parse_subtraction(ParseResult left);
  ParseResult parse_division(ParseResult left);

  ParseResult parse_relational_expr(ParseResult left);

  // Helper function used by the parser.
  void match(const scanner::TokenType &tt);
  bool attempt_match(const scanner::TokenType &tt);
  bool next_is(const scanner::TokenType &tt);
  void next_token(void);

 private:
  std::string terminal_description(const scanner::TokenType &terminal);
  std::string make_error_msg(const scanner::TokenType &terminal);
  std::string make_error_msg_expected(const scanner::TokenType &terminal);
  std::string make_error_msg(const char *msg);

  scanner::ExtToken *tokens_;
  scanner::ExtToken *curr_token_;
  scanner::ExtToken *prev_token_;

  scanner::Token *stokens_;
  scanner::Scanner *scanner_;
};

} /* namespace parser */
} /* namespace fcal */

#endif  // PROJECT_INCLUDE_PARSER_H_
