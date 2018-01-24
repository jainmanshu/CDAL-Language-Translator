/*******************************************************************************
 * Name            : parse_result.h
 * Project         : fcal
 * Module          : parser
 * Description     : a simple object for holding the result of a parse.
 * Copyright       : 2017 CSCI3081W Staff. All rights reserved.
 * Original Author : Erik Van Wyk
 * Modifications by: Dan Challou, John Harwell
 *
 ******************************************************************************/

#ifndef PROJECT_INCLUDE_PARSE_RESULT_H_
#define PROJECT_INCLUDE_PARSE_RESULT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "include/ast.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace fcal {
namespace parser {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class ParseResult {
 public:
  ParseResult(void) : errors_(), ast_(NULL), ok_(true) {}

  bool ok(void) const { return ok_; }
  void ok(bool result_in) { ok_ = result_in; }
  std::string errors(void) const { return errors_; }
  void errors(const std::string str_in) { errors_ = str_in;}
  ast::Node *ast(void) { return ast_; }
  void ast(ast::Node * Node_ptr) { ast_ = Node_ptr; }

 private:
  std::string errors_;
  ast::Node *ast_;
  bool ok_;
};

} /* namespace parser */
} /* namespace fcal */

#endif /* PROJECT_INCLUDE_PARSE_RESULT_H_ */
