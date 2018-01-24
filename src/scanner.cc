/*******************************************************************************
 * Name            : read_input.cc
 * Project         : fcal
 * Module          : scanner
 * Description     : Implementation of input reader utility
 * Copyright       : 2017 CSCI3081W Staff. All rights curerved.
 * Original Author : Eric Van Wyk
 * Modifications by: John Harwell
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "include/scanner.h"
#include "include/read_input.h"
#include "include/regex.h"


  /*******************************************************************************
  * Functions
  ******************************************************************************/
namespace fcal {
namespace scanner {
    // scanner constructor
    /* ! Constructor for Scanner class, it initialize all the regexes for all the Tokens
         and store it in a regex_t pointer type 2D array.
    */
    Scanner::Scanner(void) {
      const char * format[] = {
        "^int",
        "^float",
        "^bool",
        "^true",
        "^false",
        "^string",
        "^matrix",
        "^let",
        "^in",
        "^end",
        "^if",
        "^then",
        "^else",
        "^repeat",
        "^while",
        "^print",
        "^to",
        "^[0-9]+",
        "^-?[0-9]*\\.[0-9]+",
        "^\"(\\\\.|[^\"])*\"",
        "^[_a-zA-Z][_a-zA-Z0-9]*",
        "^\\(",
        "^\\)",
        "^\\{",
        "^\\}",
        "^\\[",
        "^\\]",
        "^;",
        "^:",
        "^=",
        "^\\+",
        "^\\*",
        "^\\-",
        "^\\/",
        "^<",
        "^<=",
        "^>",
        "^>=",
        "^==",
        "^!=",
        "^&&",
        "^\\|\\|",
        "^!"
      };


      for (int i = 0; i <=kNotOp ; i++) {
        regexes[i] = make_regex(format[i]);
      }
      }

    /* ! Scan function that takes in const char pointer and convert each text into a
         sequence of linkedlist with the correct token and lexeme associate with
    */
    Token * Scanner::Scan(const char * text) {
     Token * traverse = new Token();
     Token * res = traverse;
     if (text == NULL) {
        return res;
     }

    // Scanner regex;
       regex_t * white_space = make_regex("^[\n\t\r ]+");
       regex_t * block_comment = make_regex("^/\\*([^\\*]|\\*+[^\\*/])*\\*+/");
       regex_t * line_comment = make_regex("^//[^\n\r]*");
      // regex_t * tint = make_regex("^int");
      // regex_t * tfloat = make_regex("^float");
      // regex_t * tbool = make_regex("^bool");
      // regex_t * ttrue = make_regex("^true");
      // regex_t * tfalse = make_regex("^false");
      // regex_t * tstring = make_regex("^string");
      // regex_t * tmatrix = make_regex("^matrix");
      // regex_t * tlet = make_regex("^let");
      // regex_t * tin = make_regex("^in");
      // regex_t * tend = make_regex("^end");
      // regex_t * tif = make_regex("^if");
      // regex_t * tthen = make_regex("^then");
      // regex_t * telse = make_regex("^else");
      // regex_t * trepeat = make_regex("^repeat");
      // regex_t * twhile = make_regex("^while");
      // regex_t * tprint = make_regex("^print");
      // regex_t * tto = make_regex("^to");
      //
      // regex_t * tintconst = make_regex("^[0-9]+");
      // // regex_t * tfloatconst = make_regex("^[0-9]+(\\.[0-9][0-9]+)+");
      // regex_t * tfloatconst = make_regex("^-?[0-9]*\\.[0-9]+");
      // regex_t * tstringconst = make_regex("^\"(\\\\.|[^\"])*\"");
      //
      // regex_t * tvariablename = make_regex("^[_a-zA-Z][_a-zA-Z0-9]*");
      //
      // regex_t * tLeftparen = make_regex("^\\(");
      // regex_t * tRightparen = make_regex("^\\)");
      // regex_t * tLeftcurly = make_regex("^\\{");
      // regex_t * trightcurly = make_regex("^\\}");
      // regex_t * tLeftsquare = make_regex("^\\[");
      // regex_t * tRightsquare = make_regex("^\\]");
      // regex_t * tSemicolon = make_regex("^;");
      // regex_t * tColon = make_regex("^:");
      //
      // regex_t * tAssign = make_regex("^=");
      // regex_t * tPlusSign = make_regex("^\\+");
      // regex_t * tStar = make_regex("^\\*");
      // regex_t * tDash = make_regex("^\\-");
      // regex_t * tForwardslash = make_regex("^\\/");
      // regex_t * tLessthan = make_regex("^<");
      // regex_t * tLessthanequal = make_regex("^<=");
      // regex_t * tGreaterthan = make_regex("^>");
      // regex_t * tGreaterthanequal = make_regex("^>=");
      // regex_t * tEqualequal = make_regex("^==");
      // regex_t * tNotequal = make_regex("^!=");
      // regex_t * tAndop = make_regex("^&&");
      // regex_t * tOrop = make_regex("^\\|\\|");
      // regex_t * tNotop = make_regex("^!");

      // regex_t * tendof = make_regex("^\\\0");

      int num_matched_chars = 0;
      num_matched_chars =
       consume_whitespace_and_comments(white_space, block_comment,
                                      line_comment, text);
      text = text + num_matched_chars;
      int max_num_matched_chars = 0;
      std::string texts;

      while (text[0] != '\0') {
        max_num_matched_chars = 0;
        TokenType temp = kLexicalError;
        // Try to match the keyword Foo, tint
        num_matched_chars = match_regex(regexes[kIntKwd], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kIntKwd;
        }
        // Try to match a word, tfloat
        num_matched_chars = match_regex(regexes[kFloatKwd], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kFloatKwd;
        }
        // bool
        num_matched_chars = match_regex(regexes[kBoolKwd], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kBoolKwd;
        }
        // true
        num_matched_chars = match_regex(regexes[kTrueKwd], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kTrueKwd;
        }
        // false
        num_matched_chars = match_regex(regexes[kFalseKwd], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kFalseKwd;
        }

        // Try to match an integer constant tstring
        num_matched_chars = match_regex(regexes[kStringKwd], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kStringKwd;
        }
        // matrix
        num_matched_chars = match_regex(regexes[kMatrixKwd], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kMatrixKwd;
        }
        // let
        num_matched_chars = match_regex(regexes[kLetKwd], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kLetKwd;
        }
        // in
        num_matched_chars = match_regex(regexes[kInKwd], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kInKwd;
        }
        // end
        num_matched_chars = match_regex(regexes[kEndKwd], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kEndKwd;
        }
        // if
        num_matched_chars = match_regex(regexes[kIfKwd], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kIfKwd;
        }
        // then
        num_matched_chars = match_regex(regexes[kThenKwd], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kThenKwd;
        }
        // else
        num_matched_chars = match_regex(regexes[kElseKwd], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kElseKwd;
        }
        // repeat
        num_matched_chars = match_regex(regexes[kRepeatKwd], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kRepeatKwd;
        }
        // while
        num_matched_chars = match_regex(regexes[kWhileKwd], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kWhileKwd;
        }
        // print
        num_matched_chars = match_regex(regexes[kPrintKwd], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kPrintKwd;
        }
        // to
        num_matched_chars = match_regex(regexes[kToKwd], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kToKwd;
        }
        // intconst
        num_matched_chars = match_regex(regexes[kIntConst], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kIntConst;
        }
        // floatconst
        num_matched_chars = match_regex(regexes[kFloatConst], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kFloatConst;
        }
        // string const not fixed, tstringconst
        num_matched_chars = match_regex(regexes[kStringConst], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kStringConst;
        }
        // variablename
        num_matched_chars = match_regex(regexes[kVariableName], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kVariableName;
        }
        // leftparen
        num_matched_chars = match_regex(regexes[kLeftParen], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kLeftParen;
        }
        // Rightparen
        num_matched_chars = match_regex(regexes[kRightParen], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kRightParen;
        }
        // Leftcurly
        num_matched_chars = match_regex(regexes[kLeftCurly], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kLeftCurly;
        }
        // rightcurly
        num_matched_chars = match_regex(regexes[kRightCurly], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kRightCurly;
        }
        // Leftsquare
        num_matched_chars = match_regex(regexes[kLeftSquare], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kLeftSquare;
        }
        // Rightsquare
        num_matched_chars = match_regex(regexes[kRightSquare], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kRightSquare;
        }
        // Semicolon
        num_matched_chars = match_regex(regexes[kSemiColon], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kSemiColon;
        }
        // Colon
        num_matched_chars = match_regex(regexes[kColon], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kColon;
        }
        // Assign
        num_matched_chars = match_regex(regexes[kAssign], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kAssign;
        }
        // PlusSign
        num_matched_chars = match_regex(regexes[kPlusSign], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kPlusSign;
        }
        // Star
        num_matched_chars = match_regex(regexes[kStar], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kStar;
        }
        // Dash
        num_matched_chars = match_regex(regexes[kDash], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kDash;
        }
        // Forwardslash
        num_matched_chars = match_regex(regexes[kForwardSlash], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kForwardSlash;
        }
        // Lessthan
        num_matched_chars = match_regex(regexes[kLessThan], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kLessThan;
        }
        // Lessthanequal
        num_matched_chars = match_regex(regexes[kLessThanEqual], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kLessThanEqual;
        }
        // Greaterthan
        num_matched_chars = match_regex(regexes[kGreaterThan], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kGreaterThan;
        }
        // Greaterthanequal
        num_matched_chars = match_regex(regexes[kGreaterThanEqual], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kGreaterThanEqual;
        }
        // Equalequal
        num_matched_chars = match_regex(regexes[kEqualsEquals], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kEqualsEquals;
        }
        // Notequal
        num_matched_chars = match_regex(regexes[kNotEquals], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kNotEquals;
        }
        // Andop
        num_matched_chars = match_regex(regexes[kAndOp], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kAndOp;
        }
        // Orop
        num_matched_chars = match_regex(regexes[kOrOp], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kOrOp;
        }
        // Notop
        num_matched_chars = match_regex(regexes[kNotOp], text);
        if (num_matched_chars > max_num_matched_chars) {
          max_num_matched_chars = num_matched_chars;
          temp = kNotOp;
        }

        // num_matched_chars = match_regex(tendof, text);
        // if (num_matched_chars > max_num_matched_chars) {
        //   max_num_matched_chars = num_matched_chars;
        //   temp = kEndOfFile;
        // }
        for (int i = 0 ; i < max_num_matched_chars; i++) {
          texts += text[i];
        }

        Token * cur = new Token();

        switch (temp) {
          case kIntKwd:
            cur->setTerminal(kIntKwd);
            cur->setLexeme("int");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kFloatKwd:
            cur->setTerminal(kFloatKwd);
            cur->setLexeme("float");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kBoolKwd:
            cur->setTerminal(kBoolKwd);
            cur->setLexeme("bool");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kTrueKwd:
            cur->setTerminal(kTrueKwd);
            cur->setLexeme("true");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kFalseKwd:
            cur->setTerminal(kFalseKwd);
            cur->setLexeme("false");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kStringKwd:
            cur->setTerminal(kStringKwd);
            cur->setLexeme("string");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kMatrixKwd:
            cur->setTerminal(kMatrixKwd);
            cur->setLexeme("matrix");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kLetKwd:
            cur->setTerminal(kLetKwd);
            cur->setLexeme("let");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kInKwd:
            cur->setTerminal(kInKwd);
            cur->setLexeme("in");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kEndKwd:
            cur->setTerminal(kEndKwd);
            cur->setLexeme("end");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kIfKwd:
            cur->setTerminal(kIfKwd);
            cur->setLexeme("if");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kThenKwd:
            cur->setTerminal(kThenKwd);
            cur->setLexeme("then");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kElseKwd:
            cur->setTerminal(kElseKwd);
            cur->setLexeme("else");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kRepeatKwd:
            cur->setTerminal(kRepeatKwd);
            cur->setLexeme("repeat");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kWhileKwd:
            cur->setTerminal(kWhileKwd);
            cur->setLexeme("while");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kPrintKwd:
            cur->setTerminal(kPrintKwd);
            cur->setLexeme("print");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kToKwd:
            cur->setTerminal(kToKwd);
            cur->setLexeme("to");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kIntConst:
            // texts += text[0];
            cur->setTerminal(kIntConst);
            cur->setLexeme(texts);
            texts = "";
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kFloatConst:
            // texts += text[0];
            cur->setTerminal(kFloatConst);
            cur->setLexeme(texts);
            texts = "";
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kStringConst:
            // texts += text[0];
            cur->setTerminal(kStringConst);
            cur->setLexeme(texts);
            texts = "";
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kVariableName:
            // texts += text[0];
            cur->setTerminal(kVariableName);
            cur->setLexeme(texts);
            texts = "";
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kLeftParen:
            cur->setTerminal(kLeftParen);
            cur->setLexeme("(");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kRightParen:
            cur->setTerminal(kRightParen);
            cur->setLexeme(")");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kLeftCurly:
            cur->setTerminal(kLeftCurly);
            cur->setLexeme("{");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kRightCurly:
            cur->setTerminal(kRightCurly);
            cur->setLexeme("}");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kLeftSquare:
            cur->setTerminal(kLeftSquare);
            cur->setLexeme("[");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kRightSquare:
            cur->setTerminal(kRightSquare);
            cur->setLexeme("]");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kSemiColon:
            cur->setTerminal(kSemiColon);
            cur->setLexeme(";");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kColon:
            cur->setTerminal(kColon);
            cur->setLexeme(":");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kAssign:
            cur->setTerminal(kAssign);
            cur->setLexeme("=");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kPlusSign:
            cur->setTerminal(kPlusSign);
            cur->setLexeme("+");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kStar:
            cur->setTerminal(kStar);
            cur->setLexeme("*");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kDash:
            cur->setTerminal(kDash);
            cur->setLexeme("-");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kForwardSlash:
            cur->setTerminal(kForwardSlash);
            cur->setLexeme("/");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kLessThan:
            cur->setTerminal(kLessThan);
            cur->setLexeme("<");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kLessThanEqual:
            cur->setTerminal(kLessThanEqual);
            cur->setLexeme("<=");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kGreaterThan:
            cur->setTerminal(kGreaterThan);
            cur->setLexeme(">");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kGreaterThanEqual:
            cur->setTerminal(kGreaterThanEqual);
            cur->setLexeme(">=");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kEqualsEquals:
            cur->setTerminal(kEqualsEquals);
            cur->setLexeme("==");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kNotEquals:
            cur->setTerminal(kNotEquals);
            cur->setLexeme("!=");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kAndOp:
            cur->setTerminal(kAndOp);
            cur->setLexeme("&&");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kOrOp:
            cur->setTerminal(kOrOp);
            cur->setLexeme("||");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kNotOp:
            cur->setTerminal(kNotOp);
            cur->setLexeme("!");
            traverse->setNext(cur);
            traverse = cur;
            break;
          case kLexicalError:
            texts += text[0];
            cur->setTerminal(kLexicalError);
            cur->setLexeme(texts);
            texts = "";
            traverse->setNext(cur);
            traverse = cur;
            break;
          default:
            break;
        }
        if (temp == kLexicalError) {
            text = text + 1;
        } else {
            text = text + max_num_matched_chars;
        }
        num_matched_chars =
        consume_whitespace_and_comments(white_space, block_comment,
                                        line_comment, text);
        text = text + num_matched_chars;
        texts = "";
      }
      Token * last = new Token();
      last->setTerminal(kEndOfFile);
      last->setLexeme(text);
      traverse->setNext(last);
      traverse = last;
      // Token * ttemp = res->next();
      // while(ttemp != NULL) {
      //   std::string temp = res->lexeme();
      //   std::cout << temp << std::endl;
      //   ttemp = ttemp->next();
      // }
      return res->next();
    }

    int consume_whitespace_and_comments(regex_t *white_space,
                                        regex_t *block_comment,
                                        regex_t *line_comment,
                                        const char *text) {
      int num_matched_chars = 0;
      int total_num_matched_chars = 0;
      int still_consuming_white_space;

      do {
        still_consuming_white_space = 0;  // exit loop if not curet by a match

        // Try to match white space
        num_matched_chars = match_regex(white_space, text);
        total_num_matched_chars += num_matched_chars;
        if (num_matched_chars > 0) {
          text = text + num_matched_chars;
          still_consuming_white_space = 1;
        }

        // Try to match block comments
        num_matched_chars = match_regex(block_comment, text);
        total_num_matched_chars += num_matched_chars;
        if (num_matched_chars > 0) {
          text = text + num_matched_chars;
          still_consuming_white_space = 1;
        }
        // Try to match line comment comments
  num_matched_chars = match_regex(line_comment, text);
  total_num_matched_chars += num_matched_chars;
  if (num_matched_chars > 0) {
    text = text + num_matched_chars;
    still_consuming_white_space = 1;
  }
      } while (still_consuming_white_space);

      return total_num_matched_chars;
    } /* consume_whitespace_and_comments() */


  } /* namespace scanner */
} /* namespace fcal */
