/*******************************************************************************
 * Name            : ast.cc
 * Project         : Iteration-3
 * Module          : parser
 * Copyright       : 2017 CSCI3081W Project-Language Translator.
 * Original Author : Himanshu Jain, Clement Tan
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "include/ast.h"
#include <stdio.h>
#include <string>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace fcal {
namespace ast {

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
 /*! Unparse method for all classes is being initialize in this file
 */

 /* ! Unparse method for Program class which return a string containing
      Program ::= varName '(' ')' '{' Stmts '}'
 */
std::string Program::unparse() {
  return varname_->unparse() + "( ) {\n " + stmts_->unparse() + " }\n";
}

std::string Program::CppCode() {
    return (
            "#include <iostream>\n" "#include \"include/Matrix.h\"\n"
            "#include <math.h>\n" "using namespace std;\n"
             "int " + varname_->CppCode() + "( ) {\n" +
             stmts_->CppCode() + "}");
}



/* !  Unparse method for Varname class which return the variable name
*/
std::string Varname::unparse() {
  return varname_;
}

std::string Varname::CppCode() {
  return varname_;
}

/* !  UNparse method for StmtsEmp class which return empty string
*/
std::string StmtsEmp::unparse() {
  return "";
}

std::string StmtsEmp::CppCode() {
  return "";
}

/* ! Unparse method for StmtsSeq class which return a string containing
     Stmts ::= Stmt Stmts
*/
std::string StmtsSeq::unparse() {
  return stmt_->unparse() + " " + stmts_->unparse();
}

std::string StmtsSeq::CppCode() {
  return stmt_->CppCode() + " " + stmts_->CppCode();
}

/* ! Unparse method for StmtDecl class which return a string containing
     Stmts ::= Decl
*/
std::string StmtDecl::unparse() {
  return decl_->unparse();
}

std::string StmtDecl::CppCode() {
  return decl_->CppCode();
}

/* ! Unparse method for StmtCurly class which return a string containing
     Stmt ::= '{' Stmts '}'
*/
std::string StmtCurly::unparse() {
  return "{\n " + stmts_->unparse() + " \n}\n";
}

std::string StmtCurly::CppCode() {
  return "{\n " + stmts_->CppCode() + " \n}\n";
}

/* ! Unparse method for StmtIf class which return a string containing
     Stmt ::= 'if' '(' Expr ')' Stmt
*/
std::string StmtIf::unparse() {
  return "if ( " + expr_->unparse() + " )" + stmt_->unparse();
}

std::string StmtIf::CppCode() {
  return "if ( " + expr_->CppCode() + " )" + stmt_->CppCode();
}

/* ! Unparse method for StmtIfElse class which return a string containing
     Stmt ::= 'if' '(' Expr ')' Stmt 'else' Stmt
*/
std::string StmtIfElse::unparse() {
  return "if ( " +
          expr_->unparse() +
           " )" +
          stmt1_->unparse() +
          " else " +
          stmt2_->unparse();
}

std::string StmtIfElse::CppCode() {
  return "if ( " +
          expr_->CppCode() +
           " )" +
          stmt1_->CppCode() +
          " else " +
          stmt2_->CppCode();
}

/* ! Unparse method for StmtMultiAssign class which return a string containing
     Stmt ::= varName '[' Expr ':' Expr ']' '=' Expr ';'
*/

std::string StmtMultiAssign::unparse() {
  return varname_->unparse() +
  "[ " + expr1_->unparse() +
  ": " + expr2_->unparse() +
  " ] = " + expr3_->unparse() + ";\n";
}

std::string StmtMultiAssign::CppCode() {
  return  "*(" + varname_->CppCode() +
         ".access(" + expr1_->CppCode() +
         ", " + expr2_->CppCode() +
         ")) = " + expr3_->CppCode() + ";\n";
}

/* ! Unparse method for StmtSingleAssign class which return a string containing
     Stmt ::= varName '=' Expr ';'
*/
std::string StmtSingleAssign::unparse() {
  return varname_->unparse() + " = " + expr_->unparse() + ";\n";
}

std::string StmtSingleAssign::CppCode() {
  return varname_->CppCode() + " = " + expr_->CppCode() + ";\n";
}

/* ! Unparse method for StmtPrint class which return a string containing
     Stmt ::= 'print' '(' Expr ')' ';'
*/
std::string StmtPrint::unparse() {
  return "print ( " + expr_->unparse() + " ) ;\n";
}

std::string StmtPrint::CppCode() {
  return "cout << " + expr_->CppCode() + " ;\n";
}

/* ! Unparse method for StmtRepeat class which return a string containing
     Stmt ::= 'repeat' '(' varName '=' Expr 'to' Expr ')' Stmt
*/
std::string StmtRepeat::unparse() {
  return "repeat ( " +
          varname_->unparse() +
          " = "  + expr1_->unparse() +
          " to " + expr2_->unparse() + " )"
          + stmt_->unparse();
}

std::string StmtRepeat::CppCode() {
  return "for ( " +
          varname_->CppCode() +
          " = "  + expr1_->CppCode() +
          "; " + varname_->CppCode() + "<=" + expr2_->CppCode()
          + "; " + varname_->CppCode() + "++"
          + " )" + stmt_->CppCode() + "\n";
}

/* ! Unparse method for StmtWhile class which return a string containing
     Stmt ::= 'while' '(' Expr ')' Stmt
*/
std::string StmtWhile::unparse() {
  return "while ( " + expr_->unparse() + " )" + stmt_->unparse();
}

std::string StmtWhile::CppCode() {
  return "while ( " + expr_->CppCode() + " )" + stmt_->CppCode();
}

/* ! Unparse method for StmtEmp class which return a string containing
     Stmt ::= ';'
*/
std::string StmtEmp::unparse() {
  return ";\n";
}

std::string StmtEmp::CppCode() {
  return ";\n";
}

/* ! Unparse method for DeclInt class which return a string containing
    Decl ::= 'int' varName ';'
*/
std::string DeclInt::unparse() {
  return "int " + varname_->unparse() + ";\n";
}

std::string DeclInt::CppCode() {
  return "int " + varname_->CppCode() + ";\n";
}
/* ! Unparse method for DeclFloat class which return a string containing
     Decl ::= 'float' varName ';'
*/
std::string DeclFloat::unparse() {
  return "float " + varname_->unparse() + ";\n";
}

std::string DeclFloat::CppCode() {
  return "float " + varname_->CppCode() + ";\n";
}

/* ! Unparse method for DeclString class which return a string containing
     Decl ::= 'string' varName ';'
*/
std::string DeclString::unparse() {
  return "string " + varname_->unparse() + ";\n";
}

std::string DeclString::CppCode() {
    return "string " + varname_->CppCode() + ";\n";
}

/* ! Unparse method for DeclBool class which return a string containing
     Decl ::= 'boolean' varName ';'
*/
std::string DeclBool::unparse() {
  return "bool " + varname_->unparse()+ ";\n";
}

std::string DeclBool::CppCode() {
  return "bool " + varname_->CppCode()+ ";\n";
}

/* ! Unparse method for DeclMatrix class which return a string containing
     Decl ::= 'matrix' varName '[' Expr ':' Expr ']' varName ':' varName  '=' Expr ';'
*/
std::string DeclMatrix::unparse() {
  return "matrix " + varname1_->unparse() +
            "[ " + expr1_->unparse() +
                " : " + expr2_->unparse() +
                      " ]" +
                          varname2_->unparse() + " : " +
                              varname3_->unparse() + " = " +
                                expr3_->unparse() + ";\n";
}
// Doubts in DeclMatrix

std::string DeclMatrix::CppCode() {
  return "matrix " + varname1_->CppCode() +
         "( " + expr1_->CppCode() + "," +
                expr2_->CppCode() + " );\n" +
                "for (int " +
                varname2_->CppCode() + "= 0;" +
                varname2_->CppCode() + "< " +
                expr1_->CppCode() + ";" +
                varname2_ ->CppCode()+ " ++) {\n" +
                "for (int " +
                varname3_->CppCode() + "= 0;"
                + varname3_->CppCode() +"< " +
                expr2_->CppCode() + ";" +
                varname3_->CppCode() + " ++) {\n" +
                "*(" + varname1_->CppCode() +
                ".access(" + varname2_->CppCode() + ", " +
                varname3_->CppCode() + ")) = ("
                + expr3_->CppCode() + ") ; \n} \n} \n";
}

/* ! Unparse method for DeclMatrix2 class which return a string containing
     Decl ::= 'matrix' varName '=' Expr ';'
*/
std::string DeclMatrix2::unparse() {
  return "matrix " + varname_->unparse() + " = " + expr_->unparse() + ";\n";
}

std::string DeclMatrix2::CppCode() {
  return "matrix " + varname_->CppCode() + " ( " + expr_->CppCode() + ");\n";
}


/* ! Unparse method for ExprVar class which return a string containing
     Expr ::= varName
*/
std::string ExprVar::unparse() {
  return varname_->unparse();
}

std::string ExprVar::CppCode() {
  return varname_->CppCode();
}

/* ! Unparse method for ExprIntConst class which return a string containing
     Expr ::= integerConst
*/
std::string ExprIntConst::unparse() {
    return varname_->unparse();
}

std::string ExprIntConst::CppCode() {
    return varname_->CppCode();
}

/* ! Unparse method for ExprFloatConst class which return a string containing
     Expr ::= floatConst
*/
std::string ExprFloatConst::unparse() {
    return varname_->unparse();
}

std::string ExprFloatConst::CppCode() {
    return varname_->CppCode();
}


/* ! Unparse method for ExprStringConst class which return a string containing
     Expr ::= stringConst
*/
std::string ExprStringConst::unparse() {
    return varname_->unparse();
}

std::string ExprStringConst::CppCode() {
    return varname_->CppCode();
}

/* ! Unparse method for ExprTrue class which return a string containing
     Expr ::= 'True'
*/
std::string ExprTrue::unparse() {
    return varname_->unparse();
}

std::string ExprTrue::CppCode() {
    return varname_->CppCode();
}

/* ! Unparse method for ExprFalse class which return a string containing
     Expr ::= 'False'
*/
std::string ExprFalse::unparse() {
    return varname_->unparse();
}

std::string ExprFalse::CppCode() {
    return varname_->CppCode();
}

/* ! Unparse method for ExprMulti class which return a string containing
     Expr ::= Expr '*' Expr
*/
std::string ExprMulti::unparse() {
  return expr1_->unparse() + " * " + expr2_->unparse();
}

std::string ExprMulti::CppCode() {
  return "( " + expr1_->CppCode() + " * " + expr2_->CppCode() + ")";
}

/* ! Unparse method for ExprDiv class which return a string containing
     Expr ::= Expr '/' Expr
*/
std::string ExprDiv::unparse() {
  return expr1_->unparse() + " / " + expr2_->unparse();
}

std::string ExprDiv::CppCode() {
  return "( " + expr1_->CppCode() + " / " + expr2_->CppCode() + ")";
}

/* ! Unparse method for ExprPlus class which return a string containing
     Expr ::= Expr '+' Expr
*/
std::string ExprPlus::unparse() {
  return expr1_->unparse() + " + " + expr2_->unparse();
}

std::string ExprPlus::CppCode() {
  return "( " + expr1_->CppCode() + " + " + expr2_->CppCode() + ")";
}

/* ! Unparse method for ExprMinus class which return a string containing
     Expr ::= Expr '-' Expr
*/
std::string ExprMinus::unparse() {
  return expr1_->unparse() + " - " + expr2_->unparse();
}

std::string ExprMinus::CppCode() {
  return "( " + expr1_->CppCode() + " - " + expr2_->CppCode() + ")";
}

/* ! Unparse method for ExprGreater class which return a string containing
     Expr ::= Expr '>' Expr
*/
std::string ExprGreater::unparse() {
  return expr1_->unparse() + " > " + expr2_->unparse();
}

std::string ExprGreater::CppCode() {
  return "( " + expr1_->CppCode() + " > " + expr2_->CppCode() + ")";
}

/* ! Unparse method for ExprGreaterThanEqual class which return a string containing
     Expr ::= Expr '>=' Expr
*/
std::string ExprGreaterThanEqual::unparse() {
  return expr1_->unparse() + " >= " + expr2_->unparse();
}

std::string ExprGreaterThanEqual::CppCode() {
  return "( " + expr1_->CppCode() + " >= " + expr2_->CppCode() + ")";
}

/* ! Unparse method for ExprLesser class which return a string containing
     Expr ::= Expr '<' Expr
*/
std::string ExprLesser::unparse() {
  return expr1_->unparse() + " < " + expr2_->unparse();
}

std::string ExprLesser::CppCode() {
  return "( " + expr1_->CppCode() + " < " + expr2_->CppCode() + ")";
}

/* ! Unparse method for ExprLesserThanEqual class which return a string containing
     Expr ::= Expr '<=' Expr
*/
std::string ExprLesserThanEqual::unparse() {
  return expr1_->unparse() + " <= " + expr2_->unparse();
}

std::string ExprLesserThanEqual::CppCode() {
  return "( " + expr1_->CppCode() + " <= " + expr2_->CppCode() + ")";
}

/* ! Unparse method for ExprDoubleEqual class which return a string containing
     Expr ::= Expr '==' Expr
*/
std::string ExprDoubleEqual::unparse() {
  return expr1_->unparse() + " == " + expr2_->unparse();
}

std::string ExprDoubleEqual::CppCode() {
  return "( " + expr1_->CppCode() + " == " + expr2_->CppCode() + ")";
}
/* ! Unparse method for ExprNotEqual class which return a string containing
     Expr ::= Expr '!=' Expr
*/
std::string ExprNotEqual::unparse() {
  return expr1_->unparse() + " != " + expr2_->unparse();
}

std::string ExprNotEqual::CppCode() {
  return "( " + expr1_->CppCode() + " != " + expr2_->CppCode() + ")";
}

/* ! Unparse method for ExprAndOp class which return a string containing
     Expr ::= Expr '&&' Expr
*/
std::string ExprAndOp::unparse() {
  return expr1_->unparse() + " && " + expr2_->unparse();
}

std::string ExprAndOp::CppCode() {
  return "( " + expr1_->CppCode() + " && " + expr2_->CppCode() + ")";
}

/* ! Unparse method for ExprOrOp class which return a string containing
     Expr ::= Expr '||' Expr
*/
std::string ExprOrOp::unparse() {
  return expr1_->unparse() + " || " + expr2_->unparse();
}

std::string ExprOrOp::CppCode() {
  return "( " + expr1_->CppCode() + " || " + expr2_->CppCode() + ")";
}


/* ! Unparse method for ExprMatrixRef class which return a string containing
     Expr ::= varName '[' Expr ':' Expr ']'
 */
std::string ExprMatrixRef::unparse() {
  return varname_->unparse() + "[ " +
         expr1_->unparse() + " : " +
         expr2_->unparse() + " ]";
}

std::string ExprMatrixRef::CppCode() {
  return "*( " + varname_->CppCode() + ".access(" +
         expr1_->CppCode() + " , " +
         expr2_->CppCode() + " ))";
}

/* ! Unparse method for ExprMatrixRef class which return a string containing
     Expr ::= varName '(' Expr ')'
 */
std::string ExprNestedOrFunctionCall::unparse() {
  return varname_->unparse() + "( " + expr1_->unparse() + " )";
}

// Don't Know how this will represent in CppCode
std::string ExprNestedOrFunctionCall::CppCode() {
  if (varname_->CppCode() == "matrix_read") {
    return "matrix::"+varname_->CppCode() + " (" + expr1_->CppCode() + ") ";
  } else if (varname_->CppCode() == "ceil") {
    return varname_->CppCode() + "("+expr1_->CppCode() +");\n";
  } else {
    return expr1_->CppCode()+"."+varname_->CppCode()+"();\n";
  }
}


/* ! Unparse method for ExprParan class which return a string containing
     Expr ::= '(' Expr ')'
 */
std::string ExprParan::unparse() {
    return "( " + expr_->unparse() + " )";
}

std::string ExprParan::CppCode() {
    return "( " + expr_->CppCode() + " )";
}

/* ! Unparse method for ExprLet class which return a string containing
     Expr ::= 'let' Stmts 'in' Expr 'end'
 */
std::string ExprLet::unparse() {
  return "let " + stmts_->unparse() + " in " + expr_->unparse() + " end ";
}

std::string ExprLet::CppCode() {
  return "({ \n" + stmts_->CppCode() + "\n" + expr_->CppCode() + "; \n})";
}

/* ! Unparse method for ExprIf class which return a string containing
    Expr ::= 'if' Expr 'then' Expr 'else' Expr
 */
std::string ExprIf::unparse() {
  return "if " + expr1_->unparse() +
        " then " + expr2_->unparse() +
        " else " + expr3_->unparse();
}

std::string ExprIf::CppCode() {
  return expr1_->CppCode() +
        " ? " + expr2_->CppCode() +
        " : " + expr3_->CppCode();
}


/* ! Unparse method for ExprNot class which return a string containing
     Expr ::= '!' Expr
 */
std::string ExprNot::unparse() {
  return  "! " + expr_->unparse();
}

std::string ExprNot::CppCode() {
  return  "! " + expr_->CppCode();
}
} /* namespace ast */
} /* namespace fcal */
