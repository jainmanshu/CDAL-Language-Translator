/*******************************************************************************
 * Name            : iter2scanner.h
 * Project         : fcal
 * Module          : scanner
 * Description     : Definitions of keywords/constants/etc.
 * Copyright       : 2017 CSCI3081W Staff. All rights reserved.
 * Original Authors : John Harwell, Dan Challou
 *
 ******************************************************************************/

#ifndef PROJECT_INCLUDE_ITER2SCANNER_H_
#define PROJECT_INCLUDE_ITER2SCANNER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace fcal {
namespace scanner {

/*******************************************************************************
 * Constant Definitions
 ******************************************************************************/
/*
 * This enumerated type is used to keep track of what kind of
 * construct was matched.
 */
enum kTokenEnumType {
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
  kIntConst,
  kFloatConst,
  kStringConst,

  // Names
  kVariableName,

  // Punctuation
  kLeftParen,
  kRightParen,
  kLeftCurly,
  kRightCurly,
  kLeftSquare,
  kRightSquare,
  kSemiColon,
  kColon,

  // Operators
  kAssign,
  kPlusSign,
  kStar,
  kDash,
  kForwardSlash,
  kLessThan,
  kLessThanEqual,
  kGreaterThan,
  kGreaterThanEqual,
  kEqualsEquals,
  kNotEquals,
  kAndOp,
  kOrOp,
  kNotOp,

  // Special terminal types
  kEndOfFile,
  kLexicalError
};
typedef enum kTokenEnumType TokenType;

} /* namespace scanner */
} /* namespace fcal */

#endif  // PROJECT_INCLUDE_ITER2SCANNER_H_
