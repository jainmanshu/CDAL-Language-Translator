/*******************************************************************************
 * Name            : ext_token.h
 * Project         : fcal
 * Module          : scanner
 * Copyright       : 2017 CSCI3081W Staff. All rights reserved.
 * Original Author : Erik Van Wyk
 * Modifications by: Dan Challou, John Harwell
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/ext_token.h"
#include <assert.h>
#include <stdio.h>
#include <string>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace fcal {
namespace scanner {

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
ExtToken *ExtToken::ExtendToken(parser::Parser *p, Token *tokens) {
  switch (tokens->terminal()) {
    case kLetKwd:
      return new LetToken(p, tokens);
    case kInKwd:
      return new ExtToken(p, tokens, "'in'");
    case kEndKwd:
      return new ExtToken(p, tokens, "'end'");

    case kIfKwd:
      return new IfToken(p, tokens);
    case kElseKwd:
      return new ExtToken(p, tokens, "'else'");
    case kPrintKwd:
      return new ExtToken(p, tokens, "'print'");
    case kRepeatKwd:
      return new ExtToken(p, tokens, "'repeat'");
    case kThenKwd:
      return new ExtToken(p, tokens, "'then'");
    case kWhileKwd:
      return new ExtToken(p, tokens, "'while'");
    // Keywords

    case kIntKwd:
      return new ExtToken(p, tokens, "'int'");
    case kFloatKwd:
      return new ExtToken(p, tokens, "'float'");
    case kStringKwd:
      return new ExtToken(p, tokens, "'string'");
    case kBoolKwd:
      return new ExtToken(p, tokens, "'boolean'");
    case kTrueKwd:
      return new TrueKwdToken(p, tokens);
    case kFalseKwd:
      return new FalseKwdToken(p, tokens);
    case kMatrixKwd:
      return new ExtToken(p, tokens, "'matrix'");
    case kToKwd:
      return new ExtToken(p, tokens, "'to'");
    // case kBooleanKwd: return new ExtToken(p,tokens,"'boolean'") ;

    // Constants
    case kIntConst:
      return new IntConstToken(p, tokens);
    case kFloatConst:
      return new FloatConstToken(p, tokens);
    case kStringConst:
      return new StringConstToken(p, tokens);

    // Names
    case kVariableName:
      return new VariableNameToken(p, tokens);

    // Punctuation
    case kLeftParen:
      return new LeftParenToken(p, tokens);
    case kRightParen:
      return new ExtToken(p, tokens, ")");
    case kLeftCurly:
      return new ExtToken(p, tokens, "{");
    case kRightCurly:
      return new ExtToken(p, tokens, "}");
    case kLeftSquare:
      return new ExtToken(p, tokens, "[");
    case kRightSquare:
      return new ExtToken(p, tokens, "]");

    // case kColon: return new ExtToken(p,tokens,":") ;
    case kSemiColon:
      return new ExtToken(p, tokens, ";");
    case kColon:
      return new ExtToken(p, tokens, ":");
    case kAssign:
      return new ExtToken(p, tokens, "=");

    case kPlusSign:
      return new PlusSignToken(p, tokens);
    case kStar:
      return new StarToken(p, tokens);
    case kDash:
      return new DashToken(p, tokens);
    case kForwardSlash:
      return new ForwardSlashToken(p, tokens);

    case kEqualsEquals:
    case kLessThan:
    case kGreaterThan:
    case kLessThanEqual:
    case kGreaterThanEqual:
    case kNotEquals:
      return new RelationalOpToken(p, tokens, tokens->lexeme());

    case kNotOp:
      return new NotOpToken(p, tokens);

    case kLexicalError:
      return new ExtToken(p, tokens, "lexical error");
    case kEndOfFile:
      return new EndOfFileToken(p, tokens);

    default:
      printf("%i not implemented extend", tokens->terminal());
      fflush(stdout);
      assert(0);
  } /* switch() */
} /* ExtToken::ExtendToken() */

ExtToken *ExtToken::ExtendTokenList(parser::Parser *p, Token *tokens) {
  ExtToken *ext_tokens = NULL;
  ExtToken *prev_ext_token = NULL;

  while (tokens != NULL) {
    ExtToken *curr_ext_tokens = ExtendToken(p, tokens);

    // Add new ExtToken et to the list
    if (ext_tokens != NULL) {
      prev_ext_token->next_ = curr_ext_tokens;
    } else {
      ext_tokens = curr_ext_tokens;
    }
    prev_ext_token = curr_ext_tokens;

    tokens = tokens->next();
  } /* while() */

  return ext_tokens;
} /* ExtToken::ExtendTokenList() */

} /* namespace scanner */
} /* namespace fcal */
