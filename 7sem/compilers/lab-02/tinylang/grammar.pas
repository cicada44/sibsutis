(*
   Subset of Modula-2

   Module can have a list of imported modules, declarations, and a block
   containing statements that run at initialization time

   Data types: INTEGER, BOOLEAN
*)

compilationUnit : "MODULE" identifier ";" ( import )* block identifier "." ;

Import : ( "FROM" identifier )? "IMPORT" identList ";" ;

Block : ( declaration )* ( "BEGIN" statementSequence )? "END" ;

declaration : "CONST" ( constantDeclaration ";" )*
  | "VAR" ( variableDeclaration ";" )*
  | procedureDeclaration ";" ;

constantDeclaration : identifier "=" expression ;

(*
  The type name can come from another module and is prefixed
  by the module name in this case -- qualified identifier
*)
variableDeclaration : identList ":" qualident ;
qualident : identifier ( "." identifier )* ;
identList : identifier ( "," identifier)* ;

(*
  Procedures can have parameters and a return type
  Normal parameters are passed as values, and VAR parameters are passed by reference
*)
procedureDeclaration : "PROCEDURE" identifier ( formalParameters )? ";" block identifier ;
formalParameters : "(" ( formalParameterList )? ")" ( ":" qualident )? ;
formalParameterList : formalParameter (";" formalParameter )* ;
formalParameter : ( "VAR" )? identList ":" qualident ;

statementSequence : statement ( ";" statement )* ;

(* Assignment or a procedure call *)
statement : qualident ( ":=" expression | ( "(" ( expList )? ")" )? )
  | ifStatement | whileStatement | "RETURN" ( expression )? ;

ifStatement : "IF" expression "THEN" statementSequence
  ( "ELSE" statementSequence )? "END" ;

whileStatement : "WHILE" expression "DO" statementSequence "END" ;

expList : expression ( "," expression )* ;

expression : simpleExpression ( relation simpleExpression )? ;

relation : "=" | "#" | "<" | "<=" | ">" | ">=" ;

simpleExpression : ( "+" | "-" )? term ( addOperator term )* ;

addOperator : "+" | "-" | "OR" ;

term : factor ( mulOperator factor )* ;

mulOperator : "*" | "/" | "DIV" | "MOD" | "AND" ;

factor : integer_literal | "(" expression ")" | "NOT" factor
  | qualident ( "(" ( expList )? ")" )? ;

(*
  identifier -- name hat begins with a letter or an underscore, followed by letters, digits, and underscores
  integer_literal -- sequence of decimal digits or a sequence of hexadecimal digits, followed by the letter H
*)
