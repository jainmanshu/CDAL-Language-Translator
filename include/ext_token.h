/*******************************************************************************
 * Name            : ext_token.h
 * Project         : fcal
 * Module          : scanner
 * Description     : Extension of Token class with new methods for parsing (led,
 *                   nud, lbp), and describing the token.
 * Creation Date   : 02/11/17
 * Copyright       : 2017 CSCI3081W Staff. All rights reserved.
 * Original Author : Erik Van Wyk
 * Modifications by: Dan Challou, John Harwell
 *
 ******************************************************************************/

#ifndef PROJECT_INCLUDE_EXT_TOKEN_H_
#define PROJECT_INCLUDE_EXT_TOKEN_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "include/parser.h"
#include "include/scanner.h"
// #include "include/token.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace fcal {
namespace scanner {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class ExtToken {
 public:
  ExtToken(parser::Parser *p, Token *t)
      : desc_str_(),
        lexeme_(t->lexeme()),
        terminal_(t->terminal()),
        next_(NULL),
        parser_(p) {}
  ExtToken(parser::Parser *p, Token *t, std::string d)
      : desc_str_(d), lexeme_(t->lexeme()),
        terminal_(t->terminal()),
        parser_(p) {}


  virtual ~ExtToken() {}
  virtual parser::ParseResult nud(void) { return parser::ParseResult(); }
  virtual parser::ParseResult led(parser::ParseResult left) { return left; }

  ExtToken *ExtendToken(parser::Parser *p, Token *tokens);
  ExtToken *ExtendTokenList(parser::Parser *p, Token *tokens);

  virtual int lbp() { return 0; }
  virtual std::string description() { return desc_str_; }
  std::string lexeme(void) const { return lexeme_; }
  ExtToken *next(void) const { return next_; }
  scanner::TokenType terminal(void) const { return terminal_; }

 protected:
  parser::Parser *parser(void) { return parser_; }

 private:
  ExtToken(void) : parser_(NULL) {}
  std::string desc_str_;
  std::string lexeme_;
  scanner::TokenType terminal_;
  ExtToken *next_;
  parser::Parser *parser_;
};

/*
 * For each terminal symbol that will play some unique role in the
 * semantic analysis of the program, we need a unique subclass of
 * ExtToken.
 */
class NotOpToken : public ExtToken {
 public:
  NotOpToken(parser::Parser *p, Token *t) : ExtToken(p, t) {}

  parser::ParseResult nud() { return parser()->parse_not_expr(); }
  std::string description() { return "notOp"; }
};

// True Kwd
class TrueKwdToken : public ExtToken {
 public:
  TrueKwdToken(parser::Parser *p, Token *t) : ExtToken(p, t) {}
  parser::ParseResult nud() { return parser()->parse_true_kwd(); }
  std::string description() { return "true const"; }
};

// False Kwd
class FalseKwdToken : public ExtToken {
 public:
  FalseKwdToken(parser::Parser *p, Token *t) : ExtToken(p, t) {}
  parser::ParseResult nud() { return parser()->parse_false_kwd(); }
  std::string description() { return "false const"; }
};

// Int Const
class IntConstToken : public ExtToken {
 public:
  IntConstToken(parser::Parser *p, Token *t) : ExtToken(p, t) {}
  parser::ParseResult nud() { return parser()->parse_int_const(); }
  std::string description() { return "int const"; }
};

// Float Const
class FloatConstToken : public ExtToken {
 public:
  FloatConstToken(parser::Parser *p, Token *t) : ExtToken(p, t) {}
  parser::ParseResult nud() { return parser()->parse_float_const(); }
  std::string description() { return "float const"; }
};

// String Const
class StringConstToken : public ExtToken {
 public:
  StringConstToken(parser::Parser *p, Token *t) : ExtToken(p, t) {}
  parser::ParseResult nud() { return parser()->parse_string_const(); }
  std::string description() { return "string const"; }
};

// Char Const
class CharConstToken : public ExtToken {
 public:
  CharConstToken(parser::Parser *p, Token *t) : ExtToken(p, t) {}
  parser::ParseResult nud() { return parser()->parse_char_const(); }
  std::string description() { return "char const"; }
};

// Variable Name
class VariableNameToken : public ExtToken {
 public:
  VariableNameToken(parser::Parser *p, Token *t) : ExtToken(p, t) {}
  parser::ParseResult nud() { return parser()->parse_variable_name(); }
  std::string description() { return "variable name"; }
};

class IfToken : public ExtToken {
 public:
  IfToken(parser::Parser *p, Token *t) : ExtToken(p, t) {}
  parser::ParseResult nud() { return parser()->parse_if_expr(); }
  std::string description() { return "'if'"; }
  int lbp() { return 80; }
};
class LetToken : public ExtToken {
 public:
  LetToken(parser::Parser *p, Token *t) : ExtToken(p, t) {}
  parser::ParseResult nud() { return parser()->parse_let_expr(); }
  std::string description() { return "'let'"; }
  int lbp() { return 80; }
};

// Left Paren
class LeftParenToken : public ExtToken {
 public:
  LeftParenToken(parser::Parser *p, Token *t) : ExtToken(p, t) {}
  parser::ParseResult nud() { return parser()->parse_nested_expr(); }
  std::string description() { return "'('"; }
  int lbp() { return 80; }
};

// Plus Sign
class PlusSignToken : public ExtToken {
 public:
  PlusSignToken(parser::Parser *p, Token *t) : ExtToken(p, t) {}
  parser::ParseResult led(parser::ParseResult left) {
    return parser()->parse_addition(left);
  }
  std::string description() { return "'+'"; }
  int lbp() { return 50; }
};

// Star
class StarToken : public ExtToken {
 public:
  StarToken(parser::Parser *p, Token *t) : ExtToken(p, t) {}
  parser::ParseResult led(parser::ParseResult left) {
    return parser()->parse_multiplication(left);
  }
  std::string description() { return "'*'"; }
  int lbp() { return 60; }
};

// Dash
class DashToken : public ExtToken {
 public:
  DashToken(parser::Parser *p, Token *t) : ExtToken(p, t) {}
  parser::ParseResult led(parser::ParseResult left) {
    return parser()->parse_subtraction(left);
  }
  std::string description() { return "'-'"; }
  int lbp() { return 50; }
};

// ForwardSlash
class ForwardSlashToken : public ExtToken {
 public:
  ForwardSlashToken(parser::Parser *p, Token *t) : ExtToken(p, t) {}
  parser::ParseResult led(parser::ParseResult left) {
    return parser()->parse_division(left);
  }
  std::string description() { return "/"; }
  int lbp() { return 60; }
};

// Relational Op
class RelationalOpToken : public ExtToken {
 public:
  RelationalOpToken(parser::Parser *p, Token *t, std::string d)
      : ExtToken(p, t, d) {}
  parser::ParseResult led(parser::ParseResult left) {
    return parser()->parse_relational_expr(left);
  }
  int lbp() { return 30; }
};

// End of File
class EndOfFileToken : public ExtToken {
 public:
  EndOfFileToken(parser::Parser *p, Token *t) : ExtToken(p, t) {}
  std::string description() { return "end of file"; }
};

/*

// Left Angle
class LeftAngleToken : public ExtToken {
public:
LeftAngleToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }

parser::ParseResult led (parser::ParseResult left) {
return parser()->parse_relational_expr (left) ;
}

std::string description() { return "'('"; }
int lbp() { return 40; }
} ;

// Right Angle
class RightAngleToken : public ExtToken {
public:
RightAngleToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }

parser::ParseResult led (parser::ParseResult left) {
return parser()->parse_relational_expr (left) ;
}

std::string description() { return "'('"; }
int lbp() { return 40; }
} ;



// In Kwd
class InKwdToken : public ExtToken {
public:
InKwdToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
std::string description() { return "'In'"; }
} ;

// End Kwd
class EndKwdToken : public ExtToken {
public:
EndKwdToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
std::string description() { return "'End'"; }
} ;

// If Kwd
class IfKwdToken : public ExtToken {
public:
IfKwdToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
parser::ParseResult nud () { return parser()->parse_if_then_else (); }
std::string description() { return "'if'"; }
} ;

// Then Kwd
class ThenKwdToken : public ExtToken {
public:
ThenKwdToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
std::string description() { return "'then'"; }
} ;

// Else Kwd
class ElseKwdToken : public ExtToken {
public:
ElseKwdToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
std::string description() { return "'else'"; }
} ;

// Print Kwd
class PrintKwdToken : public ExtToken {
public:
PrintKwdToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
parser::ParseResult nud () { return parser()->parse_print_expr (); }
std::string description() { return "'print'"; }
} ;

// Read Kwd
class ReadKwdToken : public ExtToken {
public:
ReadKwdToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
parser::ParseResult nud () { return parser()->parse_read_expr (); }
std::string description() { return "'read'"; }
} ;

// Write Kwd
class WriteKwdToken : public ExtToken {
public:
WriteKwdToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
parser::ParseResult nud () { return parser()->parse_write_expr (); }
std::string description() { return "'write'"; }
} ;

// Integer Kwd
class IntegerKwdToken : public ExtToken {
public:
IntegerKwdToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
std::string description() { return "'Integer'"; }
} ;

// Float Kwd
class FloatKwdToken : public ExtToken {
public:
FloatKwdToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
std::string description() { return "'Float'"; }
} ;

// Boolean Kwd
class BooleanKwdToken : public ExtToken {
public:
BooleanKwdToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
std::string description() { return "'Boolean'"; }
} ;

// String Kwd
class StringKwdToken : public ExtToken {
public:
StringKwdToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
std::string description() { return "'String'"; }
} ;

// True Kwd
class TrueKwdToken : public ExtToken {
public:
TrueKwdToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
parser::ParseResult nud () { return parser()->parse_true_kwd (); }
std::string description() { return "'True'"; }
} ;

// False Kwd
class FalseKwdToken : public ExtToken {
public:
FalseKwdToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
parser::ParseResult nud () { return parser()->parse_false_kwd (); }
std::string description() { return "'False'"; }
} ;

// Head Kwd
class HeadKwdToken : public ExtToken {
public:
HeadKwdToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
parser::ParseResult nud () { return parser()->parse_head_expr (); }
std::string description() { return "'Head'"; }
} ;

// Tail Kwd
class TailKwdToken : public ExtToken {
public:
TailKwdToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
parser::ParseResult nud () { return parser()->parse_tail_expr (); }
std::string description() { return "'Tail'"; }
} ;

// Null Kwd
class NullKwdToken : public ExtToken {
public:
NullKwdToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
parser::ParseResult nud () { return parser()->parse_null_expr (); }
std::string description() { return "'Null'"; }
} ;

// Map Kwd
class MapKwdToken : public ExtToken {
public:
MapKwdToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
parser::ParseResult nud () { return parser()->parse_map_expr (); }
std::string description() { return "'Map'"; }
} ;

// Filter Kwd
class FilterKwdToken : public ExtToken {
public:
FilterKwdToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
parser::ParseResult nud () { return parser()->parse_filter_expr (); }
std::string description() { return "filter"; }
} ;

// Fold Kwd
class FoldKwdToken : public ExtToken {
public:
FoldKwdToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
parser::ParseResult nud () { return parser()->parse_fold_expr (); }
std::string description() { return "fold"; }
} ;

// Zip Kwd
class ZipKwdToken : public ExtToken {
public:
ZipKwdToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
parser::ParseResult nud () { return parser()->parse_zip_expr (); }
std::string description() { return "zip"; }
} ;


// Int Const
class IntConstToken : public ExtToken {
public:
IntConstToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
parser::ParseResult nud () { return parser()->parse_int_const (); }
std::string description() { return "integer constant"; }
} ;

// Float Const
class FloatConstToken : public ExtToken {
public:
FloatConstToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
parser::ParseResult nud () { return parser()->parse_float_const (); }
std::string description() { return "floating point constant"; }
} ;

// String Const
class StringConstToken : public ExtToken {
public:
StringConstToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
parser::ParseResult nud () { return parser()->parse_string_const (); }
std::string description() { return "string constant"; }
} ;





// Percent
class PercentToken : public ExtToken {
public:
PercentToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
parser::ParseResult led (parser::ParseResult left) {
return parser()->parseModulus (left) ;
}
std::string description() { return "%"; }
int lbp() { return 60; }
} ;


// Plus Plus
class PlusPlusToken : public ExtToken {
public:
PlusPlusToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
parser::ParseResult led (parser::ParseResult left) {
return parser()->parseAppendExpr (left) ;
}
std::string description() { return "++"; }
int lbp() { return 40; }
} ;

// Dot Dot
class DotDotToken : public ExtToken {
public:
DotDotToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
//    parser::ParseResult led (parser::ParseResult left) {
//        return parser()->parseDotDotExpr (left) ;
//    }
std::string description() { return ".."; }
int lbp() { return 0 ; // 40;
}
} ;


// BackSlash
class BackSlashToken : public ExtToken {
public:
BackSlashToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
parser::ParseResult nud () { return parser()->parseLambdaExpr () ;  }
std::string description() { return "'\'"; }
} ;




// Colon Colon
class ColonColonToken : public ExtToken {
public:
ColonColonToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
std::string description() { return "'::'"; }
} ;

// Colon
class ColonToken : public ExtToken {
public:
ColonToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
parser::ParseResult led (parser::ParseResult left) {
return parser()->parseConsExpr (left) ;
}
std::string description() { return "':'"; }
int lbp() { return 70; }
} ;

// Semicolon
class SemiColonToken : public ExtToken {
public:
SemiColonToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
std::string description() { return "';'"; }
} ;
// Equals Sign
class EqualsSignToken : public ExtToken {
public:
EqualsSignToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
std::string description() { return "'='"; }
} ;

// Tuple Op
class TupleOpToken : public ExtToken {
public:
TupleOpToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
parser::ParseResult nud () { return parser()->parseProjectionExpr (); }
std::string description() { return "tuple projection operator"; }
} ;


*/

/*
// Name Kwd
class NameKwdToken : public ExtToken {
public:
NameKwdToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
std::string description() { return "'name'"; }
} ;

// Platform Kwd
class PlatformKwdToken : public ExtToken {
public:
PlatformKwdToken (parser::Parser *p, Token *t) : ExtToken(p,t) { }
std::string description() { return "'platform'"; }
} ;
*/

} /* namespace scanner */
} /* namespace fcal */

#endif  // PROJECT_INCLUDE_EXT_TOKEN_H_
