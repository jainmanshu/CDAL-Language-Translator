/*******************************************************************************
 * Name            : parser.h
 * Project         : fcal
 * Module          : parser
 * Copyright       : 2017 CSCI3081W Staff. All rights reserved.
 * Original Author : Erik Van Wyk
 * Modifications by: Dan Challou, John Harwell
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <assert.h>
#include <stdio.h>
#include "include/parser.h"
#include "include/ext_token.h"
#include "include/scanner.h"
#include "include/ast.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace fcal {
namespace parser {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
 /* ! Deconstructor for parser class
 */
Parser::~Parser() {
  if (scanner_) delete scanner_;

  scanner::ExtToken *to_delete1;
  curr_token_ = tokens_;
  while (curr_token_) {
    to_delete1 = curr_token_;
    curr_token_ = curr_token_->next();
    delete to_delete1;
  } /* while() */

  scanner::Token *curr_scanner_token = stokens_;
  scanner::Token *to_delete2;
  while (curr_scanner_token) {
    to_delete2 = curr_scanner_token;
    curr_scanner_token = curr_scanner_token->next();
    delete to_delete2;
  } /* while() */
} /* Parser::~Parser() */

/* ! Constructor for parser class which take const char pointer as argument.
     It sets the attributes which determine whether
     the text is parsed correctly
*/
ParseResult Parser::Parse(const char *text) {
  assert(text != NULL);

  ParseResult pr;
  try {
    scanner_ = new scanner::Scanner();
    stokens_ = scanner_->Scan(text);
    tokens_ = tokens_->ExtendTokenList(this, stokens_);
    assert(tokens_ != NULL);
    curr_token_ = tokens_;
    pr = ParseProgram();
  }
  catch (std::string errMsg) {
    pr.ok(false);
    pr.errors(errMsg);
    pr.ast(NULL);
  }
  return pr;
} /* Parser::parse() */

/*
 * parse methods for non-terminal symbols
 * --------------------------------------
 */

 /* ! Reponsible to parse the Program class, it takes no argument
 */
// Program
ParseResult Parser::ParseProgram() {
  ParseResult pr;
  // root
  // Program ::= varName '(' ')' '{' Stmts '}'
  match(scanner::kVariableName);
  std::string name(prev_token_->lexeme());
  ast::Varname *varname = new ast::Varname(name);
  match(scanner::kLeftParen);
  match(scanner::kRightParen);
  match(scanner::kLeftCurly);
  ParseResult prStmts = parse_stmts();
  ast::Stmts *s = NULL;
  if ( prStmts.ast() ) {
    s = dynamic_cast<ast:: Stmts *>(prStmts.ast());
    if ( !s ) throw ((std::string) "Bad cast of State in parseProgram");
  }
  match(scanner::kRightCurly);
  match(scanner::kEndOfFile);
  ast::Node * program = new ast::Program(varname, s);
  pr.ast(program);
  return pr;
} /* Parser::ParseProgram() */

/* ! Responsible to parse all the Decl class, it takes no argument
*/
// MatrixDecl
// identical purpose of parse_decl, handles special matrix syntax.
ParseResult Parser::parse_matrix_decl() {
  ParseResult pr;
  ast::Decl * declnode;
  match(scanner::kMatrixKwd);
  match(scanner::kVariableName);
  std::string var1(prev_token_->lexeme());
  ast::Varname *varname1 = new ast::Varname(var1);
  // Decl ::= 'matrix' varName '[' Expr ':' Expr ']' varName ':' varName  '='
  // Expr ';'
  if (attempt_match(scanner::kLeftSquare)) {
    ParseResult p1 = parse_expr(0);
    ast:: Expr * e1 = NULL;
    if (p1.ast()) {
      e1 = dynamic_cast<ast:: Expr *>(p1.ast());
      if (!e1) throw ((std::string) "Bad cast of State in parse_matrix_decl");
    }
    match(scanner::kColon);
    ParseResult p2 = parse_expr(0);
    ast:: Expr * e2 = NULL;
    if (p2.ast()) {
      e2 = dynamic_cast<ast:: Expr *>(p2.ast());
      if (!e2) throw ((std::string) "Bad cast of State in parse_matrix_decl");
    }

    match(scanner::kRightSquare);
    match(scanner::kVariableName);
    std::string var2(prev_token_->lexeme());
    ast::Varname *varname2 = new ast::Varname(var2);
    match(scanner::kColon);
    match(scanner::kVariableName);
    std::string var3(prev_token_->lexeme());
    ast::Varname *varname3 = new ast::Varname(var3);
    match(scanner::kAssign);
    ParseResult p3 = parse_expr(0);
    ast:: Expr * e3 = NULL;
    if (p3.ast()) {
      e3 = dynamic_cast<ast:: Expr *>(p3.ast());
      if (!e3) throw ((std::string) "Bad cast of State in parse_matrix_decl");
    }
    declnode = new ast::DeclMatrix(varname1, e1, e2, varname2, varname3, e3);
  } else if (attempt_match(scanner::kAssign)) {
      // Decl ::= 'matrix' varName '=' Expr ';'
      ParseResult p1 = parse_expr(0);
      ast:: Expr * e1 = NULL;
      if (p1.ast()) {
        e1 = dynamic_cast<ast:: Expr *>(p1.ast());
        if (!e1) throw ((std::string) "Bad cast of State in parse_matrix_decl");
      }
      declnode = new ast::DeclMatrix2(varname1, e1);
    } else {
      throw((std::string) "Bad Syntax of Matrix Decl in in parseMatrixDecl");
    }
    match(scanner::kSemiColon);
    pr.ast(declnode);
    return pr;
}

/* ! Responsible to parse Declaration for int, float, string and boolean,
     It takes no argument
*/
// standardDecl
// Decl ::= integerKwd varName | floatKwd varName | stringKwd varName
ParseResult Parser::parse_standard_decl() {
  ParseResult pr;
  ast::Decl * declnode;
  if (attempt_match(scanner::kIntKwd)) {  // Type ::= intKwd
      match(scanner::kVariableName);
      std::string var(prev_token_->lexeme());
      ast::Varname *varname = new ast::Varname(var);
      declnode = new ast::DeclInt(varname);
  } else if (attempt_match(scanner::kFloatKwd)) {  // Type ::= floatKwd
      match(scanner::kVariableName);
      std::string var(prev_token_->lexeme());
      ast::Varname *varname = new ast::Varname(var);
      declnode = new ast::DeclFloat(varname);
  } else if (attempt_match(scanner::kStringKwd)) {  // Type ::= stringKwd
      match(scanner::kVariableName);
      std::string var(prev_token_->lexeme());
      ast::Varname *varname = new ast::Varname(var);
      declnode = new ast::DeclString(varname);
  } else if (attempt_match(scanner::kBoolKwd)) {  // Type ::= boolKwd
      match(scanner::kVariableName);
      std::string var(prev_token_->lexeme());
      ast::Varname *varname = new ast::Varname(var);
      declnode = new ast::DeclBool(varname);
  }
  match(scanner::kSemiColon);
  pr.ast(declnode);
  return pr;
}

// Decl
ParseResult Parser::parse_decl() {
  ParseResult pr;
  // Decl :: matrix variableName ....
  if (next_is(scanner::kMatrixKwd)) {
    pr = parse_matrix_decl();
  } else {
    // Decl ::= Type variableName semiColon
    pr = parse_standard_decl();
  }
  return pr;
}

/* ! Responsible to parse Stmts class, it takes no argument
*/
// Stmts
ParseResult Parser::parse_stmts() {
  ParseResult pr;
  ast::Stmts * stmtsnode;
  if (!next_is(scanner::kRightCurly) && !next_is(scanner::kInKwd)) {
    // Stmts ::= Stmt Stmts
    ParseResult pr_stmt = parse_stmt();
    ast::Stmt *s = NULL;
    if (pr_stmt.ast()) {
      s = dynamic_cast<ast:: Stmt *>(pr_stmt.ast());
      if (!s) throw ((std::string) "Bad cast of State in parse_stmts");
    }
    ParseResult pr_stmts = parse_stmts();
    ast::Stmts *s1 = NULL;
    if (pr_stmts.ast()) {
      s1 = dynamic_cast<ast:: Stmts *>(pr_stmts.ast());
      if (!s1) throw ((std::string) "Bad cast of State in parse_stmts");
    }
    stmtsnode = new ast:: StmtsSeq(s, s1);
  } else {
      // Stmts ::=
      // nothing to match.k
      stmtsnode = new ast::StmtsEmp();
  }
  pr.ast(stmtsnode);
  return pr;
}

/* ! Responsible to parse all Stmt class. It takes no argument
*/
// Stmt
ParseResult Parser::parse_stmt() {
  ParseResult pr;
  ast::Stmt * stmtnode;
  // Stmt ::= Decl
  if (next_is(scanner::kIntKwd) || next_is(scanner::kFloatKwd) ||
      next_is(scanner::kMatrixKwd) || next_is(scanner::kStringKwd) ||
      next_is(scanner::kBoolKwd)) {
    ParseResult prdecl = parse_decl();
    ast::Decl *d = NULL;
    if (prdecl.ast()) {
      d = dynamic_cast<ast:: Decl *>(prdecl.ast());
      if (!d) throw ((std::string) "Bad cast of State in parse_stmt");
    }
    stmtnode = new ast:: StmtDecl(d);
  } else if (attempt_match(scanner::kLeftCurly)) {
    // Stmt ::= '{' Stmts '}'
    ParseResult pr_stmts = parse_stmts();
    ast::Stmts *s1 = NULL;
    if (pr_stmts.ast()) {
      s1 = dynamic_cast<ast:: Stmts *>(pr_stmts.ast());
      if (!s1) throw ((std::string) "Bad cast of State in parse_stmt");
    }
    match(scanner::kRightCurly);
    stmtnode = new ast::StmtCurly(s1);
  } else if (attempt_match(scanner::kIfKwd)) {
    // Stmt ::= 'if' '(' Expr ')' Stmt
    // Stmt ::= 'if' '(' Expr ')' Stmt 'else' Stmt
    match(scanner::kLeftParen);
    ParseResult p1 = parse_expr(0);
    ast:: Expr * e1 = NULL;
    if (p1.ast()) {
      e1 = dynamic_cast<ast:: Expr *>(p1.ast());
      if (!e1) throw ((std::string) "Bad cast of State in parse_stmt");
    }
    match(scanner::kRightParen);
    ParseResult pr_stmt = parse_stmt();
    ast::Stmt *s1 = NULL;
    if (pr_stmt.ast()) {
      s1 = dynamic_cast<ast:: Stmt *>(pr_stmt.ast());
      if (!s1) throw ((std::string) "Bad cast of State in parse_stmt");
    }
    stmtnode = new ast:: StmtIf(e1, s1);

    if (attempt_match(scanner::kElseKwd)) {
      ParseResult pr_stmt = parse_stmt();
      ast::Stmt *s2 = NULL;
      if (pr_stmt.ast()) {
        s2 = dynamic_cast<ast:: Stmt *>(pr_stmt.ast());
        if (!s2) throw ((std::string) "Bad cast of State in parse_stmt");
      }
      stmtnode = new ast:: StmtIfElse(e1, s1, s2);
    }
  } else if (attempt_match(scanner::kVariableName)) {
    /*
     * Stmt ::= varName '=' Expr ';'  | varName '[' Expr ':' Expr ']'
     * '=' Expr ';'
     */
     std::string var1(prev_token_->lexeme());
     ast::Varname *varname1 = new ast::Varname(var1);
    if (attempt_match(scanner::kLeftSquare)) {
      ParseResult p1 = parse_expr(0);
      ast:: Expr * e1 = NULL;
      if (p1.ast()) {
        e1 = dynamic_cast<ast:: Expr *>(p1.ast());
        if (!e1) throw ((std::string) "Bad cast of State in parse_stmt");
      }
      match(scanner::kColon);
      ParseResult p2 = parse_expr(0);
      ast:: Expr * e2 = NULL;
      if (p2.ast()) {
        e2 = dynamic_cast<ast:: Expr *>(p2.ast());
        if (!e2) throw ((std::string) "Bad cast of State in parse_stmt");
      }
      match(scanner::kRightSquare);

    match(scanner::kAssign);
    ParseResult p3 = parse_expr(0);
    ast:: Expr * e3 = NULL;
    if (p3.ast()) {
      e3 = dynamic_cast<ast:: Expr *>(p3.ast());
      if (!e3) throw ((std::string) "Bad cast of State in parse_stmt");
    }
    match(scanner::kSemiColon);
    stmtnode = new ast:: StmtMultiAssign(varname1, e1, e2, e3);
  } else {
          match(scanner::kAssign);
          ParseResult p1 = parse_expr(0);
          ast:: Expr * e1 = NULL;
          if (p1.ast()) {
            e1 = dynamic_cast<ast:: Expr *>(p1.ast());
            if (!e1) throw ((std::string) "Bad cast of State in parse_stmt");
          }
          match(scanner::kSemiColon);
          stmtnode = new ast::StmtSingleAssign(varname1, e1);
      }
      } else if (attempt_match(scanner::kPrintKwd)) {
    // Stmt ::= 'print' '(' Expr ')' ';'
    match(scanner::kLeftParen);
    ParseResult p1 = parse_expr(0);
    ast:: Expr * e1 = NULL;
    if (p1.ast()) {
      e1 = dynamic_cast<ast:: Expr *>(p1.ast());
      if (!e1) throw ((std::string) "Bad cast of State in parse_stmt");
    }
    match(scanner::kRightParen);
    match(scanner::kSemiColon);
    stmtnode = new ast::StmtPrint(e1);
  } else if (attempt_match(scanner::kRepeatKwd)) {
    // Stmt ::= 'repeat' '(' varName '=' Expr 'to' Expr ')' Stmt
    match(scanner::kLeftParen);
    match(scanner::kVariableName);
    std::string var1(prev_token_->lexeme());
    ast::Varname *varname1 = new ast::Varname(var1);
    match(scanner::kAssign);
    ParseResult p1 = parse_expr(0);
    ast:: Expr * e1 = NULL;
    if (p1.ast()) {
      e1 = dynamic_cast<ast:: Expr *>(p1.ast());
      if (!e1) throw ((std::string) "Bad cast of State in parse_stmt");
    }
    match(scanner::kToKwd);
    ParseResult p2 = parse_expr(0);
    ast:: Expr * e2 = NULL;
    if (p2.ast()) {
      e2 = dynamic_cast<ast:: Expr *>(p2.ast());
      if (!e2) throw ((std::string) "Bad cast of State in parse_stmt");
    }
    match(scanner::kRightParen);
    ParseResult pr_stmt = parse_stmt();
    ast::Stmt *s = NULL;
    if (pr_stmt.ast()) {
      s = dynamic_cast<ast:: Stmt *>(pr_stmt.ast());
      if (!s) throw ((std::string) "Bad cast of State in parse_stmts");
    }
    stmtnode = new ast::StmtRepeat(varname1, e1, e2, s);
  } else if (attempt_match(scanner::kWhileKwd)) {
    // Stmt ::= 'while' '(' Expr ')' Stmt
    match(scanner::kLeftParen);
    ParseResult p1 = parse_expr(0);
    ast:: Expr * e1 = NULL;
    if (p1.ast()) {
      e1 = dynamic_cast<ast:: Expr *>(p1.ast());
      if (!e1) throw ((std::string) "Bad cast of State in parse_stmt");
    }
    match(scanner::kRightParen);
    ParseResult pr_stmt = parse_stmt();
    ast::Stmt *s = NULL;
    if (pr_stmt.ast()) {
      s = dynamic_cast<ast:: Stmt *>(pr_stmt.ast());
      if (!s) throw ((std::string) "Bad cast of State in parse_stmts");
    }
    stmtnode = new ast::StmtWhile(e1, s);
  } else if (attempt_match(scanner::kSemiColon)) {
    // Stmt ::= ';
    // parsed a skip
    stmtnode = new ast:: StmtEmp();
    pr.ast(stmtnode);
  } else {
    throw(make_error_msg(curr_token_->terminal()) +
          " while parsing a statement");
  }
  // Stmt ::= variableName assign Expr semiColon
  // pr.ast (new ast::StmtSingleAssign(var1, e1);
  pr.ast(stmtnode);
  return pr;
}

/* ! Responsible to parse all Expr class. It takes no argument
*/
// Expr
ParseResult Parser::parse_expr(int rbp) {
  /* Examine current token, without consuming it, to call its
     associated parse methods.  The ExtToken objects have 'nud' and
     'led' methods that are dispatchers that call the appropriate
     parse methods.*/
  ParseResult left = curr_token_->nud();

  while (rbp < curr_token_->lbp()) {
    left = curr_token_->led(left);
  }

  return left;
}

/*
 * parse methods for Expr productions
 * ----------------------------------
 */

 /* ! Responsible to parse boolean true keyword. It takes no argument
 */
// Expr ::= trueKwd
ParseResult Parser::parse_true_kwd() {
  ParseResult pr;
  ast::Expr * exprnode;
  match(scanner::kTrueKwd);
  std::string var1(prev_token_->lexeme());
  ast::Varname *varname1 = new ast::Varname(var1);
  exprnode = new ast::ExprTrue(varname1);
  pr.ast(exprnode);
  return pr;
}

/* ! Responsible to parse boolean false keyword. It takes no argument
*/
// Expr ::= FalseKwd
ParseResult Parser::parse_false_kwd() {
  ParseResult pr;
  ast::Expr * exprnode;
  match(scanner::kFalseKwd);
  std::string var1(prev_token_->lexeme());
  ast::Varname *varname1 = new ast::Varname(var1);
  exprnode = new ast::ExprFalse(varname1);
  pr.ast(exprnode);
  return pr;
}

/* ! Responsible to parse int const word. It takes no argument
*/
// Expr ::= intConst
ParseResult Parser::parse_int_const() {
  ParseResult pr;
  ast::Expr * exprnode;
  match(scanner::kIntConst);
  std::string var1(prev_token_->lexeme());
  ast::Varname *varname1 = new ast::Varname(var1);
  exprnode = new ast::ExprIntConst(varname1);
  pr.ast(exprnode);
  return pr;
}

/* ! Responsible to parse float const word. It takes no argument
*/
// Expr ::= floatConst
ParseResult Parser::parse_float_const() {
  ParseResult pr;
  ast::Expr * exprnode;
  match(scanner::kFloatConst);
  std::string var1(prev_token_->lexeme());
  ast::Varname *varname1 = new ast::Varname(var1);
  exprnode = new ast::ExprFloatConst(varname1);
  pr.ast(exprnode);
  return pr;
}

/* ! Responsible to parse string const keyword. It takes no argument
*/
// Expr ::= stringConst
ParseResult Parser::parse_string_const() {
  ParseResult pr;
  ast::Expr * exprnode;
  match(scanner::kStringConst);
  std::string var1(prev_token_->lexeme());
  ast::Varname *varname1 = new ast::Varname(var1);
  exprnode = new ast::ExprStringConst(varname1);
  pr.ast(exprnode);
  return pr;
}

/* ! Responsible to parse variable name. It takes no argument
*/
// Expr ::= variableName .....
ParseResult Parser::parse_variable_name() {
  ParseResult pr;
  ast::Expr * exprnode;
  match(scanner::kVariableName);
  std::string var1(prev_token_->lexeme());
  ast::Varname *varname1 = new ast::Varname(var1);
  if (attempt_match(scanner::kLeftSquare)) {
    ParseResult p1 = parse_expr(0);
    ast:: Expr * e1 = NULL;
    if (p1.ast()) {
      e1 = dynamic_cast<ast:: Expr *>(p1.ast());
      if (!e1) throw ((std::string) "Bad cast of State in parse_stmt");
    }
    match(scanner::kColon);
    ParseResult p2 = parse_expr(0);
    ast:: Expr * e2 = NULL;
    if (p2.ast()) {
      e2 = dynamic_cast<ast:: Expr *>(p2.ast());
      if (!e2) throw ((std::string) "Bad cast of State in parse_stmt");
    }
    match(scanner::kRightSquare);
    exprnode = new ast::ExprMatrixRef(varname1, e1, e2);
  }  else if (attempt_match(scanner::kLeftParen)) {
    // Expr ::= varableName '(' Expr ')'
    ParseResult p1 = parse_expr(0);
    ast:: Expr * e1 = NULL;
    if (p1.ast()) {
      e1 = dynamic_cast<ast:: Expr *>(p1.ast());
      if (!e1) throw ((std::string) "Bad cast of State in parse_stmt");
    }
    match(scanner::kRightParen);
    exprnode = new ast::ExprNestedOrFunctionCall(varname1, e1);
  } else {
    exprnode = new ast::ExprVar(varname1);
  }
  pr.ast(exprnode);
  return pr;
}

/* ! Responsible to parse nested expression. It takes no argument
*/
// Expr ::= leftParen Expr rightParen
ParseResult Parser::parse_nested_expr() {
  ParseResult pr;
  ast::Expr * exprnode;
  match(scanner::kLeftParen);
  ParseResult p1 = parse_expr(0);
  ast:: Expr * e1 = NULL;
  if (p1.ast()) {
    e1 = dynamic_cast<ast:: Expr *>(p1.ast());
    if (!e1) throw ((std::string) "Bad cast of State in parse_stmt");
  }
  match(scanner::kRightParen);
  exprnode = new ast::ExprParan(e1);
  pr.ast(exprnode);
  return pr;
}

/* ! Responsible to parse if expression and if else expression. It takes no argument
*/
// Expr ::= 'if' Expr 'then' Expr 'else' Expr
ParseResult Parser::parse_if_expr() {
  ParseResult pr;
  ast::Expr * exprnode;
  match(scanner::kIfKwd);
  ParseResult p1 = parse_expr(0);
  ast:: Expr * e1 = NULL;
  if (p1.ast()) {
    e1 = dynamic_cast<ast:: Expr *>(p1.ast());
    if (!e1) throw ((std::string) "Bad cast of State in parse_if_expr");
  }  match(scanner::kThenKwd);
  ParseResult p2 = parse_expr(0);
  ast:: Expr * e2 = NULL;
  if (p2.ast()) {
    e2 = dynamic_cast<ast:: Expr *>(p2.ast());
    if (!e2) throw ((std::string) "Bad cast of State in parse_if_expr");
  }
  match(scanner::kElseKwd);
  ParseResult p3 = parse_expr(0);
  ast:: Expr * e3 = NULL;
  if (p3.ast()) {
    e3 = dynamic_cast<ast:: Expr *>(p3.ast());
    if (!e3) throw ((std::string) "Bad cast of State in parse_if_expr");
  }
  exprnode = new ast::ExprIf(e1, e2, e3);
  pr.ast(exprnode);
  return pr;
}

/* ! Responsible to parse let expression. It takes no argument
*/
// Expr ::= 'let' Stmts 'in' Expr 'end'
ParseResult Parser::parse_let_expr() {
  ParseResult pr;
  ast::Expr * exprnode;
  match(scanner::kLetKwd);
  ParseResult pr_stmts = parse_stmts();
  ast::Stmts *s1 = NULL;
  if (pr_stmts.ast()) {
    s1 = dynamic_cast<ast:: Stmts *>(pr_stmts.ast());
    if (!s1) throw ((std::string) "Bad cast of State in parse_let_expr");
  }
  match(scanner::kInKwd);
  ParseResult p1 = parse_expr(0);
  ast:: Expr * e1 = NULL;
  if (p1.ast()) {
    e1 = dynamic_cast<ast:: Expr *>(p1.ast());
    if (!e1) throw ((std::string) "Bad cast of State in parse_let_expr");
  }
  match(scanner::kEndKwd);
  exprnode = new ast::ExprLet(s1, e1);
  pr.ast(exprnode);

  return pr;
}

/* ! Responsible to parse not experssion. It takes no argument
*/
// Expr ::= '!' Expr
ParseResult Parser::parse_not_expr() {
  ParseResult pr;
  ast::Expr * exprnode;
  match(scanner::kNotOp);
  ParseResult p1 = parse_expr(0);
  ast:: Expr * e1 = NULL;
  if (p1.ast()) {
    e1 = dynamic_cast<ast:: Expr *>(p1.ast());
    if (!e1) throw ((std::string) "Bad cast of State in parse_not_expr");
  }
  exprnode = new ast::ExprNot(e1);
  pr.ast(exprnode);
  return pr;
}

/* ! Responsible to parse addition expression. It takes ParseResult variable that match the left expression
*/
// Expr ::= Expr plusSign Expr
ParseResult Parser::parse_addition(ParseResult prLeft) {
  // parser has already matchekD left expression
  ParseResult pr;
  ast::Expr * exprnode;
  // parse_expr(prev_token_->lbp());
  ast:: Expr * e1 = NULL;
  if (prLeft.ast()) {
    e1 = dynamic_cast<ast:: Expr *>(prLeft.ast());
    if (!e1) throw ((std::string) "Bad cast of State in parse_not_expr");
  }
  match(scanner::kPlusSign);
  ParseResult p1 = parse_expr(prev_token_->lbp());
  ast:: Expr * e2 = NULL;
  if (p1.ast()) {
    e2 = dynamic_cast<ast:: Expr *>(p1.ast());
    if (!e2) throw ((std::string) "Bad cast of State in parse_not_expr");
  }
  exprnode = new ast::ExprPlus(e1, e2);
  pr.ast(exprnode);
  return pr;
}

/* ! Responsible to parse multiplication expression. It takes ParseResult variable that match the left expression
*/
// Expr ::= Expr star Expr
ParseResult Parser::parse_multiplication(ParseResult prLeft) {
  // parser has already matchekD left expression
  ParseResult pr;
  ast::Expr * exprnode;
  // parse_expr(prev_token_->lbp());
  ast:: Expr * e1 = NULL;
  if (prLeft.ast()) {
    e1 = dynamic_cast<ast:: Expr *>(prLeft.ast());
    if (!e1) throw ((std::string) "Bad cast of State in parse_not_expr");
  }
  match(scanner::kStar);
  ParseResult p1 = parse_expr(prev_token_->lbp());
  ast:: Expr * e2 = NULL;
  if (p1.ast()) {
    e2 = dynamic_cast<ast:: Expr *>(p1.ast());
    if (!e2) throw ((std::string) "Bad cast of State in parse_not_expr");
  }
  exprnode = new ast::ExprMulti(e1, e2);
  pr.ast(exprnode);
  return pr;
}

/* ! Responsible to parse subtraction expression. It takes ParseResult variable that match the left expression
*/
// Expr ::= Expr dash Expr
ParseResult Parser::parse_subtraction(ParseResult prLeft) {
  // parser has already matchekD left expression
  ParseResult pr;
  ast::Expr * exprnode;
  // parse_expr(prev_token_->lbp());
  ast:: Expr * e1 = NULL;
  if (prLeft.ast()) {
    e1 = dynamic_cast<ast:: Expr *>(prLeft.ast());
    if (!e1) throw ((std::string) "Bad cast of State in parse_not_expr");
  }
  match(scanner::kDash);
  ParseResult p1 = parse_expr(prev_token_->lbp());
  ast:: Expr * e2 = NULL;
  if (p1.ast()) {
    e2 = dynamic_cast<ast:: Expr *>(p1.ast());
    if (!e2) throw ((std::string) "Bad cast of State in parse_not_expr");
  }
  exprnode = new ast::ExprMinus(e1, e2);
  pr.ast(exprnode);
  return pr;
}

/* ! Responsible to parse divide expression. It takes ParseResult variable that match the left expression
*/
// Expr ::= Expr forwardSlash Expr
ParseResult Parser::parse_division(ParseResult prLeft) {
  // parser has already matchekD left expression
  ParseResult pr;
  ast::Expr * exprnode;
  // parse_expr(prev_token_->lbp());
  ast:: Expr * e1 = NULL;
  if (prLeft.ast()) {
    e1 = dynamic_cast<ast:: Expr *>(prLeft.ast());
    if (!e1) throw ((std::string) "Bad cast of State in parse_not_expr");
  }
  match(scanner::kForwardSlash);
  ParseResult p1 = parse_expr(prev_token_->lbp());
  ast:: Expr * e2 = NULL;
  if (p1.ast()) {
    e2 = dynamic_cast<ast:: Expr *>(p1.ast());
    if (!e2) throw ((std::string) "Bad cast of State in parse_not_expr");
  }
  exprnode = new ast::ExprDiv(e1, e2);
  pr.ast(exprnode);
  return pr;
}

// Expr ::= Expr equalEquals Expr
// Expr ::= Expr lessThanEquals Expr
// Expr ::= Expr greaterThanEquals Expr
// Expr ::= Expr notEquals Expr
// Expr ::= Expr leftAngle Expr
// Expr ::= Expr rightAngle Expr
/* Notice that for relational operators we use just one parse
   function.  This shows another possible means for implementing
   expressions, as opposed to the method used for arithmetic
   expressions in which each operation has its own parse method.  It
   will depend on what we do in iteration 3 in building an abstract
   syntax tree to decide which method is better.
*/
/* ! Responsible to parse all logical expression. It takes ParseResult variable that match the left expression
*/
ParseResult Parser::parse_relational_expr(ParseResult prLeft) {
  // parser has already matchekD left expression
  ParseResult pr;
  ast::Expr * exprnode;
  ast:: Expr * e1 = NULL;
  if (prLeft.ast()) {
    e1 = dynamic_cast<ast:: Expr *>(prLeft.ast());
    if (!e1) throw ((std::string) "Bad cast of State in parse_not_expr");
  }
  next_token();
  // just advance token, since examining it in parse_expr caused
  // this method being called.
  std::string op = prev_token_->lexeme();

  ParseResult p1 = parse_expr(prev_token_->lbp());
  ast:: Expr * e2 = NULL;
  if (p1.ast()) {
    e2 = dynamic_cast<ast:: Expr *>(p1.ast());
    if (!e2) throw ((std::string) "Bad cast of State in parse_not_expr");
  }
  if (op == ">") {
    exprnode = new ast::ExprGreater(e1, e2);
  } else if (op == ">=") {
    exprnode = new ast::ExprGreaterThanEqual(e1, e2);
  } else if (op == "<") {
    exprnode = new ast::ExprLesser(e1, e2);
  } else if (op == "<=") {
    exprnode = new ast::ExprLesserThanEqual(e1, e2);
  } else if (op == "!=") {
    exprnode = new ast::ExprNotEqual(e1, e2);
  } else if (op == "==") {
    exprnode = new ast::ExprDoubleEqual(e1, e2);
  } else if (op == "&&") {
    exprnode = new ast::ExprAndOp(e1, e2);
  } else if (op == "||") {
    exprnode = new ast::ExprOrOp(e1, e2);
  } else {
    throw((std::string) "Invalid operator in parse_relational_expr");
  }
  pr.ast(exprnode);
  return pr;
}

// Helper function used by the parser.

void Parser::match(const scanner::TokenType &tt) {
  if (!attempt_match(tt)) {
    throw(make_error_msg_expected(tt));
  }
}

bool Parser::attempt_match(const scanner::TokenType &tt) {
  if (curr_token_->terminal() == tt) {
    next_token();
    return true;
  }
  return false;
}

bool Parser::next_is(const scanner::TokenType &tt) {
  return curr_token_->terminal() == tt;
}

void Parser::next_token() {
  if (curr_token_ == NULL) {
    throw(std::string(
        "Internal Error: should not call nextToken in unitialized state"));
  } else if (curr_token_->terminal() == scanner::kEndOfFile &&
           curr_token_->next() == NULL) {
    prev_token_ = curr_token_;
  } else if (curr_token_->terminal() != scanner::kEndOfFile &&
             curr_token_->next() == NULL) {
    throw(make_error_msg("Error: tokens end with endOfFile"));
  } else {
    prev_token_ = curr_token_;
    curr_token_ = curr_token_->next();
  }
}

std::string Parser::terminal_description(const scanner::TokenType &terminal) {
  scanner::Token *dummy_token = new scanner::Token();
  scanner::ExtToken *dummy_ext_token =
  new scanner::ExtToken(this, dummy_token);
  std::string s = dummy_ext_token->
  ExtendToken(this, dummy_token)->description();
  delete dummy_token;
  delete dummy_ext_token;
  return s;
}

std::string Parser::make_error_msg_expected(
    const scanner::TokenType &terminal) {
  std::string s = (std::string) "Expected " + terminal_description(terminal) +
                  " but found " + curr_token_->description();
  return s;
}

std::string Parser::make_error_msg(const scanner::TokenType &terminal) {
  std::string s = (std::string) "Unexpected symbol " +
                  terminal_description(terminal) +
                  " but found " + curr_token_->description();;
  return s;
}

std::string Parser::make_error_msg(const char *msg) { return msg; }

} /* namespace parser */
} /* namespace fcal */
