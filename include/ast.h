/*******************************************************************************
 * Name            : regex.h
 * Project         : fcal
 * Module          : ast
 * Description     : Header file for AST
 * Copyright       : 2017 CSCI3081W Staff. All rights reserved.
 * Original Author : Eric Van Wyk
 * Modifications by: John Harwell
 ******************************************************************************/

#ifndef PROJECT_INCLUDE_AST_H_
#define PROJECT_INCLUDE_AST_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <string>
#include "include/scanner.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace fcal {
namespace ast {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /*!
 	\class Node
     This is the Abstract class.
     Program, Stmts, Stmt, Decl, and Expr are derived from this class.
  */
class Node {
 public:
  virtual std::string unparse(void) { return " This should be pure virtual "; }
  virtual std::string CppCode(void) { return " This should be pure virtual"; }
  virtual ~Node(void) {}
};

// These four classes are derived from Node and has concrete classes.

/*!
	\class Stmts
    This is the Stmts Abstract class.
    All Stmts concrete classes are derived from this class.
 */

class Stmts : public Node { };

/*!
	\class Stmt
    This is the Stmt Abstract class.
    All Stmt concrete classes are derived from this class.
 */

class Stmt : public Node { };

/*!
	\class Decl
    This is the Decl Abstract class.
    All Decl concrete classes are derived from this class.
 */

class Decl : public Node { };

/*!
	\class Expr
    This is the Expr Abstract class.
    All Expr concrete classes are derived from this class.
 */

class Expr : public Node { };

/*!
	\class Varname
	\This class is used for taking Variable name in our program.
    The Program constructor requires one parameter.
    \param varname is an Varname (string).
 */

class Varname : public Node {
 public:
    explicit Varname(std::string varname) : varname_(varname) {}
      std::string unparse();
      std::string CppCode();
 private:
    std::string varname_;
};

/*!
	\class Program
	\brief Grammar: Program ::= varName '(' ')' '{' Stmts '}'
    The Program constructor requires two parameters.
    \param varname is a type of Varname (which is a string)
    \param stmts is the program's statements (type of Stmts).
 */

class Program : public Node {
 public:
    explicit Program(Varname * varname,
                     Stmts * stmts) :
                     varname_(varname),
                     stmts_(stmts) {}
    std::string unparse();
    std::string CppCode();

 private:
    Varname * varname_;
    Stmts * stmts_;
};

// The Stmts classes

/*!
	\class StmtsEmp
	\brief Grammar: Stmts ::= <<empty>>
    The StmtsEmp constructor requires no parameters.
 */

class StmtsEmp : public Stmts {
 public:
    StmtsEmp(void) {}
    std::string unparse();
    std::string CppCode();
};

/*!
	\class StmtsSeq
	\brief Grammar: Stmts ::= Stmt Stmts
    The StmtsSeq constructor requires two parameters.
    \param stmt is a statement (Stmt)
    \param stmts is statements (Stmts)
 */

class StmtsSeq : public Stmts {
 public:
    explicit StmtsSeq(Stmt * stmt, Stmts * stmts) :
                      stmt_(stmt), stmts_(stmts) {}
    std::string unparse();
    std::string CppCode();

 private:
    Stmt * stmt_;
    Stmts * stmts_;
};

// The Stmt classes

/*!
	\class StmtDecl
	\brief Grammar: Stmt ::= Decl
    The StmtsDecl constructor requires one parameter.
    \param decl is a declaration (Decl)
 */

class StmtDecl : public Stmt {
 public:
    explicit StmtDecl(Decl * decl) : decl_(decl) {}
    std::string unparse();
    std::string CppCode();

 private:
    Decl * decl_;
};

/*!
	\class StmtsCurly
	\brief Grammar: Stmt ::= '{' Stmts '}'
    The StmtsCurly constructor requires one parameter.
    \param stmts is statements (Stmts)
 */

class StmtCurly : public Stmt {
 public:
    explicit StmtCurly(Stmts *stmts) : stmts_(stmts) {}
    std::string unparse();
    std::string CppCode();

 private:
  Stmts* stmts_;
};

/*!
	\class StmtIf
	\brief Grammar: Stmt ::= 'if' '(' Expr ')' Stmt
    The StmtIf constructor requires two parameters.
    \param expr is a expression (Expr)
    \param stmt is a statement (Stmt)
 */

class StmtIf : public Stmt {
 public:
    explicit StmtIf(Expr * expr, Stmt * stmt) : expr_(expr), stmt_(stmt) {}
    std::string unparse();
    std::string CppCode();
 private:
    Expr * expr_;
    Stmt * stmt_;
};
/*!
	\class StmtIfElse
	\brief Grammar: Stmt ::= 'if' '(' Expr ')' Stmt 'else' Stmt
    The StmtIfElse constructor requires three parameters.
    \param expr is an expression (Expr)
    \param stmt1 is a statement (Stmt)
    \param stmt2 is a statement (Stmt)
 */
class StmtIfElse : public Stmt {
 public:
    explicit StmtIfElse(Expr * expr,
                        Stmt * stmt1,
                        Stmt * stmt2) :
                        expr_(expr),
                        stmt1_(stmt1),
                        stmt2_(stmt2) {}
    std::string unparse();
    std::string CppCode();

 private:
    Expr * expr_;
    Stmt * stmt1_;
    Stmt * stmt2_;
};

/*!
\class StmtMultiAssign
\brief Grammar: Stmt ::= varName '[' Expr ':' Expr ']' '=' Expr ';'
The StmtMultiAssign constructor requires four parameters.
\param varname is an Varname (string)
\param expr1 is an expression (Expr)
\param expr2 is an expression (Expr)
\param expr3 is an expression (Expr)
*/

class StmtMultiAssign : public Stmt {
 public:
    explicit StmtMultiAssign(Varname * varname,
                             Expr * expr1,
                             Expr * expr2,
                             Expr * expr3) :
                             varname_(varname),
                             expr1_(expr1),
                             expr2_(expr2),
                             expr3_(expr3) {}
    std::string unparse();
    std::string CppCode();

 private:
    Varname * varname_;
    Expr * expr1_;
    Expr * expr2_;
    Expr * expr3_;
};

/*!
\class StmtSingleAssign
\brief Grammar: Stmt ::= varName '=' Expr ';'
The StmtSingleAssign constructor requires two parameters.
\param varname is an Varname (string)
\param expr is an expression (Expr)
*/

class StmtSingleAssign: public Stmt {
 public:
    explicit StmtSingleAssign(Varname * varname,
                              Expr * expr) :
                              varname_(varname),
                              expr_(expr) {}
    std::string unparse();
    std::string CppCode();

 private:
    Varname * varname_;
    Expr * expr_;
};

/*!
	\class StmtPrint
	\brief Grammar: Stmt ::= 'print' '(' Expr ')' ';'
    The StmtPrint constructor requires one parameter.
    \param expr is an expression (Expr)
 */

class StmtPrint : public Stmt {
 public:
    explicit StmtPrint(Expr * expr) : expr_(expr) {}
    std::string unparse();
    std::string CppCode();

 private:
  Expr * expr_;
};

/*!
	\class StmtRepeat
	\brief Grammar: Stmt ::= 'repeat' '(' varName '=' Expr 'to' Expr ')' Stmt
    The StmtRepeat constructor requires four parameters.
    \param varname is an Varname (string)
    \param expr1 is an expression (Expr)
    \param expr2 is an expression (Expr)
    \param stmt is a statement (Stmt)
 */

class StmtRepeat : public Stmt {
 public:
    explicit StmtRepeat(Varname * varname,
                        Expr * expr1,
                        Expr * expr2,
                        Stmt * stmt) :
                        varname_(varname),
                        expr1_(expr1),
                        expr2_(expr2),
                        stmt_(stmt) {}
    std::string unparse();
    std::string CppCode();

 private:
    Varname * varname_;
    Expr * expr1_;
    Expr * expr2_;
    Stmt * stmt_;
};
/*!
	\class StmtWhile
	\brief Grammar: Stmt ::= 'while' '(' Expr ')' Stmt
    The StmtWhile constructor requires two parameters.
    \param expr is an expression (Expr)
    \param stmt is a statement (Stmt)
 */
class StmtWhile : public Stmt {
 public:
    explicit StmtWhile(Expr * expr, Stmt * stmt) : expr_(expr), stmt_(stmt) {}
    std::string unparse();
    std::string CppCode();

 private:
    Expr * expr_;
    Stmt * stmt_;
};

/*!
	\class StmtEmp
	\brief Grammar: Stmt ::= ';'
    The StmtEmp constructor requires no parameters.
 */

class StmtEmp : public Stmt {
 public:
    StmtEmp(void)  {}
    std::string unparse();
    std::string CppCode();
};

// The Decl classes

/*!
	\class DeclInt
	\brief Grammar: Decl ::= 'int' varName ';'
    The DeclInt constructor requires one parameter.
    \param varname is an Varname (string)
 */

class DeclInt : public Decl {
 public:
    explicit DeclInt(Varname * varname) : varname_(varname) {}
    std::string unparse();
    std::string CppCode();
 private:
    Varname * varname_;
};

/*!
	\class DeclFloat
	\brief Grammar: Decl ::= 'float' varName ';'
    The Declfloat constructor requires one parameter.
    \param varname is an Varname (string)
 */

class DeclFloat : public Decl {
 public:
    explicit DeclFloat(Varname * varname) :varname_(varname) {}
    std::string unparse();
    std::string CppCode();
 private:
    Varname * varname_;
};

/*!
	\class DeclString
	\brief Grammar: Decl ::= 'string' varName ';'
    The DeclString constructor requires one parameter.
    \param varname is an Varname (string)
 */

class DeclString : public Decl {
 public:
    explicit DeclString(Varname * varname) :varname_(varname) {}
    std::string unparse();
    std::string CppCode();
 private:
    Varname * varname_;
};

/*!
	\class DeclBool
	\brief Grammar: Decl ::= 'bool' varName ';'
    The Declbool constructor requires one parameter.
    \param varname is an Varname (string)
 */

class DeclBool : public Decl {
 public:
    explicit DeclBool(Varname * varname) :varname_(varname) {}
    std::string unparse();
    std::string CppCode();
 private:
    Varname * varname_;
};

/*!
	\class DeclMatrix
	\brief Grammar: Decl ::= 'matrix' varName '[' Expr ':' Expr ']' varName ':' varName  '=' Expr ';'
    The DeclMatrix constructor requires six parameters.
    \param varname1 is an Varname (string)
    \param expr1 is an expression (Expr)
    \param expr2 is an expression (Expr)
    \param varname2 is an Varname (string)
    \param varname3 is an Varname (string)
    \param expr3 is an expression (Expr)
 */

class DeclMatrix : public Decl {
 public:
    explicit DeclMatrix(Varname * varname1,
                        Expr * expr1,
                        Expr * expr2,
                        Varname * varname2,
                        Varname * varname3,
                        Expr * expr3) :
                        varname1_(varname1),
                        expr1_(expr1),
                        expr2_(expr2),
                        varname2_(varname2),
                        varname3_(varname3),
                        expr3_(expr3) {}
    std::string unparse();
    std::string CppCode();

 private:
    Varname * varname1_;
    Expr * expr1_;
    Expr * expr2_;
    Varname * varname2_;
    Varname * varname3_;
    Expr * expr3_;
};

/*!
	\class DeclMatrix2
	\brief Grammar: Decl ::= 'matrix' varName '=' Expr ';'
    The DeclMatrix2 constructor requires two parameters.
    \param varname is an Varname (string)
    \param expr is an expression (Expr)
 */

class DeclMatrix2: public Decl {
 public:
    explicit DeclMatrix2(Varname * varname, Expr * expr) :
                         varname_(varname), expr_(expr) {}
    std::string unparse();
    std::string CppCode();

 private:
    Varname * varname_;
    Expr * expr_;
};
// The Expr classes

/*!
	\class ExprVar
	\brief Grammar: Expr ::= varName
    The ExprVar constructor requires one parameter.
    \param varname is an Varname (string)
 */
class ExprVar : public Expr {
 public:
    explicit ExprVar(Varname * varname) : varname_(varname) {}
    std::string unparse();
    std::string CppCode();

 private:
    Varname * varname_;
};

/*!
	\class ExprIntConst
	\brief Grammar: Expr ::= integerConst
    The ExprIntConst constructor requires one parameter.
	\param varname is an Varname (string)
 */

class ExprIntConst : public Expr {
 public:
    explicit ExprIntConst(Varname * varname) : varname_(varname) {}
    std::string unparse();
    std::string CppCode();

 private:
  Varname * varname_;
};
/*!
	\class ExprFloatConst
	\brief Grammar: Expr ::= floatConst
    The ExprFloatConst constructor requires one parameter.
    \param varname is an Varname (string)
 */
class ExprFloatConst : public Expr {
 public:
    explicit ExprFloatConst(Varname * varname) : varname_(varname) {}
    std::string unparse();
    std::string CppCode();

 private:
    Varname * varname_;
};
/*!
	\class ExprStringConst
	\brief Grammar: Expr ::= stringConst
    The ExprStringConst constructor requires one parameter.
    \param varname is an Varname (string)
 */
class ExprStringConst : public Expr {
 public:
    explicit ExprStringConst(Varname * varname) : varname_(varname) {}
    std::string unparse();
    std::string CppCode();

 private:
    Varname * varname_;
};
/*!
	\class ExprTrue
	\brief Grammar: Expr ::= 'true'
    The ExprTrue constructor requires one parameter.
    \param varname is an Varname (string)
 */
class ExprTrue : public Expr {
 public:
    explicit ExprTrue(Varname * varname) : varname_(varname) {}
    std::string unparse();
    std::string CppCode();

 private:
  Varname * varname_;
};
/*!
	\class ExprFalse
	\brief Grammar: Expr ::= 'false'
    The ExprFalse constructor requires one parameter.
    \param varname is an Varname (string)
 */
class ExprFalse : public Expr {
 public:
    explicit ExprFalse(Varname * varname) : varname_(varname) {}
    std::string unparse();
    std::string CppCode();

 private:
    Varname * varname_;
};

/*!
	\class ExprMulti
	\brief Grammar: Expr ::= Expr '*' Expr
    The ExprMulti constructor requires two parameters.
    \param expr1 is an expression (Expr)
    \param expr2 is an expression (Expr)
 */

class ExprMulti : public Expr {
 public:
  explicit ExprMulti(Expr * expr1,
                      Expr * expr2) :
                      expr1_(expr1),
                      expr2_(expr2) {}
  std::string unparse();
  std::string CppCode();
 private:
    Expr * expr1_;
    Expr * expr2_;
};
/*!
	\class ExprDiv
	\brief Grammar: Expr ::= Expr '/' Expr
    The ExprDiv constructor requires two parameters.
    \param expr1 is an expression (Expr)
    \param expr2 is an expression (Expr)
 */
class ExprDiv: public Expr {
 public:
    explicit ExprDiv(Expr * expr1,
                     Expr * expr2) :
                     expr1_(expr1),
                     expr2_(expr2) {}
    std::string unparse();
    std::string CppCode();

 private:
    Expr * expr1_;
    Expr * expr2_;
};
/*!
	\class ExprPlus
	\brief Grammar: Expr ::= Expr '+' Expr
    The ExprPlus constructor requires two parameters.
    \param expr1 is an expression (Expr)
    \param expr2 is an expression (Expr)
 */
class ExprPlus : public Expr {
 public:
    explicit ExprPlus(Expr * expr1, Expr * expr2) :
                      expr1_(expr1), expr2_(expr2) {}
    std::string unparse();
    std::string CppCode();

 private:
    Expr * expr1_;
    Expr * expr2_;
};
/*!
	\class ExprMinus
	\brief Grammar: Expr ::= Expr '-' Expr
    The ExprMinus constructor requires two parameters.
    \param expr1 is an expression (Expr)
    \param expr2 is an expression (Expr)
 */
class ExprMinus : public Expr {
 public:
    explicit ExprMinus(Expr * expr1, Expr * expr2) :
                       expr1_(expr1), expr2_(expr2) {}
    std::string unparse();
    std::string CppCode();

 private:
    Expr * expr1_;
    Expr * expr2_;
};
/*!
	\class ExprGreater
	\brief Grammar: Expr ::= Expr '>' Expr
    The ExprGreater constructor requires two parameters.
    \param expr1 is an expression (Expr)
    \param expr2 is an expression (Expr)
 */
class ExprGreater : public Expr {
 public:
    explicit ExprGreater(Expr * expr1, Expr * expr2) :
                         expr1_(expr1), expr2_(expr2) {}
    std::string unparse();
    std::string CppCode();

 private:
    Expr * expr1_;
    Expr * expr2_;
};
/*!
	\class ExprGreaterThanEqual
	\brief Grammar: Expr ::= Expr '>=' Expr
    The ExprGreaterThanEqual constructor requires two parameters.
    \param expr1 is an expression (Expr)
    \param expr2 is an expression (Expr)
 */
class ExprGreaterThanEqual : public Expr {
 public:
    explicit ExprGreaterThanEqual(Expr * expr1, Expr * expr2) :
                                  expr1_(expr1), expr2_(expr2) {}
    std::string unparse();
    std::string CppCode();

 private:
    Expr * expr1_;
    Expr * expr2_;
};
/*!
	\class ExprLesser
	\brief Grammar: Expr ::= Expr '<' Expr
    The ExprLesser constructor requires two parameters.
    \param expr1 is an expression (Expr)
    \param expr2 is an expression (Expr)
 */
class ExprLesser : public Expr {
 public:
    explicit ExprLesser(Expr * expr1, Expr * expr2) :
                        expr1_(expr1), expr2_(expr2) {}
    std::string unparse();
    std::string CppCode();

 private:
    Expr * expr1_;
    Expr * expr2_;
};
/*!
	\class ExprLesserThanEqual
	\brief Grammar: Expr ::= Expr '<=' Expr
    The ExprLesserThanEqual constructor requires two parameters.
    \param expr1 is an expression (Expr)
    \param expr2 is an expression (Expr)
 */
class ExprLesserThanEqual : public Expr {
 public:
    explicit ExprLesserThanEqual(Expr * expr1, Expr * expr2) :
                                 expr1_(expr1), expr2_(expr2) {}
    std::string unparse();
    std::string CppCode();

 private:
    Expr * expr1_;
    Expr * expr2_;
};
/*!
	\class ExprDoubleEqual
	\brief Grammar: Expr ::= Expr '==' Expr
    The ExprDoubleEqual constructor requires two parameters.
    \param expr1 is an expression (Expr)
    \param expr2 is an expression (Expr)
 */
class ExprDoubleEqual : public Expr {
 public:
    explicit ExprDoubleEqual(Expr * expr1, Expr * expr2) :
                             expr1_(expr1), expr2_(expr2) {}
    std::string unparse();
    std::string CppCode();

 private:
    Expr * expr1_;
    Expr * expr2_;
};

/*!
	\class ExprNotEqual
	\brief Grammar: Expr ::= Expr '!=' Expr
    The ExprNotEquals constructor requires two parameters.
    \param expr1 is an expression (Expr)
    \param expr2 is an expression (Expr)
 */
class ExprNotEqual : public Expr {
 public:
    explicit ExprNotEqual(Expr * expr1, Expr * expr2) :
                          expr1_(expr1), expr2_(expr2) {}
    std::string unparse();
    std::string CppCode();

 private:
    Expr * expr1_;
    Expr * expr2_;
};

/*!
	\class ExprAndOp
	\brief Grammar: Expr ::= Expr '&&' Expr
    The ExprAndOp constructor requires two parameters.
    \param expr1 is an expression (Expr)
    \param expr2 is an expression (Expr)
 */

class ExprAndOp : public Expr {
 public:
    explicit ExprAndOp(Expr * expr1, Expr * expr2) :
                       expr1_(expr1), expr2_(expr2) {}
    std::string unparse();
    std::string CppCode();

 private:
    Expr * expr1_;
    Expr * expr2_;
};
/*!
	\class ExprOrOp
	\brief Grammar: Expr ::= Expr '||' Expr
    The ExprOrOp constructor requires two parameters.
    \param expr1 is an expression (Expr)
    \param expr2 is an expression (Expr)
 */
class ExprOrOp : public Expr {
 public:
    explicit ExprOrOp(Expr * expr1, Expr * expr2) :
                      expr1_(expr1), expr2_(expr2) {}
    std::string unparse();
    std::string CppCode();

 private:
    Expr * expr1_;
    Expr * expr2_;
};
/*!
	\class ExprMatrixRef
	\brief Grammar: Expr ::= varName '[' Expr ':' Expr ']'
    The ExprMatrixRef constructor requires three parameters.
    \param varname is an Varname (string)
    \param expr1 is an expression (Expr)
    \param expr2 is an expression (Expr)
 */
class ExprMatrixRef : public Expr {
 public:
    explicit ExprMatrixRef(Varname * varname, Expr * expr1, Expr * expr2) :
                          varname_(varname), expr1_(expr1), expr2_(expr2) {}
    std::string unparse();
    std::string CppCode();

 private:
    Varname * varname_;
    Expr * expr1_;
    Expr * expr2_;
};
/*!
	\class ExprNestedOrFunctionCall
	\brief Grammar: Expr ::= varName '(' Expr ')'
    The ExprNestedOrFunctionCall constructor requires two parameters.
    \param varname is an Varname (string)
    \param expr1 is an expression (Expr)
 */
class ExprNestedOrFunctionCall : public Expr {
 public:
    explicit ExprNestedOrFunctionCall(Varname * varname, Expr * expr1) :
                                      varname_(varname), expr1_(expr1) {}
    std::string unparse();
    std::string CppCode();

 private:
    Varname * varname_;
    Expr * expr1_;
};
/*!
	\class ExprParan
	\brief Grammar: Expr ::= '(' Expr ')'
    The ExprParan constructor requires one parameter.
    \param expr is an expression (Expr)
 */
class ExprParan : public Expr {
 public:
    explicit ExprParan(Expr * expr): expr_(expr) {}
    std::string unparse();
    std::string CppCode();

 private:
    Expr * expr_;
};
/*!
	\class ExprLet
	\brief Grammar: Expr ::= 'let' Stmts 'in' Expr 'end'
    The ExprLet constructor requires two parameters.
    \param stmts is statements (Stmts)
    \param expr is an expression (Expr)
 */
class ExprLet : public Expr {
 public:
    explicit ExprLet(Stmts * stmts, Expr * expr) :
                     stmts_(stmts) , expr_(expr) {}
    std::string unparse();
    std::string CppCode();

 private:
    Stmts * stmts_;
    Expr * expr_;
};
/*!
	\class ExprIf
	\brief Grammar: Expr ::= 'if' Expr 'then' Expr 'else' Expr
    The ExprIf constructor requires three parameters.
    \param expr1 is an expression (Expr)
    \param expr2 is an expression (Expr)
    \param expr3 is an expression (Expr)
 */
class ExprIf : public Expr {
 public:
    explicit ExprIf(Expr * expr1, Expr * expr2, Expr * expr3) :
                    expr1_(expr1), expr2_(expr2), expr3_(expr3) {}
    std::string unparse();
    std::string CppCode();

 private:
    Expr * expr1_;
    Expr * expr2_;
    Expr * expr3_;
};
/*!
	\class ExprNot
	\brief Grammar: Expr ::= '!' Expr
    The ExprNot constructor requires one parameter.
    \param expr is an expression (Expr)
 */
class ExprNot : public Expr {
 public:
    explicit ExprNot(Expr * expr) : expr_(expr) {}
    std::string unparse();
    std::string CppCode();

 private:
    Expr * expr_;
};
} /* namespace ast */
} /* namespace fcal */

#endif  // PROJECT_INCLUDE_AST_H_
