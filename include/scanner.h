/*******************************************************************************
 * Name            : scanner.h
 * Project         : fcal
 * Module          : scanner
 * Description     : Header file for scanner module
 * Copyright       : 2017 CSCI3081W Staff. All rights reserved.
 * Original Author : Eric Van Wyk
 * Modifications by: John Harwell
 ******************************************************************************/

#ifndef PROJECT_INCLUDE_SCANNER_H_
#define PROJECT_INCLUDE_SCANNER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <regex.h>
#include <string>


/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace fcal {
namespace scanner {
/* below are the possible terminal types for each token */

/* This enumerated type is used to keep track of what kind of
   construct was matched.
 */

enum kTokenEnumType {
    /*Keywords*/
    kIntKwd,
    kFloatKwd,
    kBoolKwd,
    kTrueKwd,
    kFalseKwd,
    kStringKwd,
    kMatrixKwd,
    kLetKwd,
    kInKwd,
    kEndKwd,
    kIfKwd,
    kThenKwd,
    kElseKwd,
    kRepeatKwd,
    kWhileKwd,
    kPrintKwd,
    kToKwd,

    // Constants
    /*13*/ kIntConst,
    kFloatConst,
    kStringConst,

    // Names
    /*16*/ kVariableName,

    // Punctuation
    /*17*/ kLeftParen,
    kRightParen,
    kLeftCurly,
    kRightCurly,
    /*21*/ kLeftSquare,
    kRightSquare,

    kSemiColon,
    kColon,

    // Operators
    /*25*/ kAssign,
    kPlusSign,
    kStar,
    kDash,
    kForwardSlash,
    /*30*/ kLessThan,
    kLessThanEqual,
    kGreaterThan,
    kGreaterThanEqual,
    /*34*/ kEqualsEquals,
    kNotEquals,
    /*36*/ kAndOp,
    kOrOp,
    kNotOp,

    // Special terminal types
    /*39*/ kEndOfFile,
    kLexicalError
  };

  typedef enum kTokenEnumType TokenType;

/*******************************************************************************
 * Class Definitions
 *
 * You will need to define a Token class (remember, a pointer of type Token *
 * is returned by the scan method of the scanner class.)
 * Also, Classes are typically declared (and sometimes also defined) in
 * their own header files
 *
 * You will also need to define a Scanner class with a scan and other methods
 ******************************************************************************/
// class for Token

/*!
	\class Token
	\This Class is used to construct Token.
    The ToKen class has six memeber function.
    \Function terminal() to return terminal_.
    \Function lexeme() to return lexeme_.
    \Function Next() to return next_.
    \Function setTerminal() to intialize and set terminal.
    \Function setLexeme() to intialize and set lexeme.
    \Function setNext() to intialize and set to next token.
 */

class Token {
 private:
  TokenType terminal_;
  std::string lexeme_;
  Token * next_;

 public:
  TokenType terminal() {return terminal_;}
  std::string lexeme() {return lexeme_;}
  Token * next() {return next_;}
  void setTerminal(TokenType terminal2) {terminal_ = terminal2;}
  void setLexeme(std::string lexeme2) {lexeme_ = lexeme2;}
  void setNext(Token * token2) {next_ = token2;}
};
// Class for scanner

/*!
	\class Scanner
	\This Class is used to construct Scannig the text.
    The Scanner class has a efaultu constructor with no arguments.
 */

class Scanner {
 public:
  regex_t * regexes[43];
  Token * Scan(const char *text);
  Scanner();
};

int consume_whitespace_and_comments(regex_t *white_space,
                                     regex_t *block_comment,
                                     regex_t *line_comment,
                                     const char *text);
} /* namespace scanner */
} /* namespace fcal */

#endif  // PROJECT_INCLUDE_SCANNER_H_
