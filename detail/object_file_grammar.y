//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Wednesday, 14 January 2009 12:06:08 AM
//////////////////////////////////////////////////////////////////////////////
%token_type		{token_def}
%token_prefix	TY_

// int foo = 4

%type contents   { record* }
// %type array_type { array_type* }

	
// root can be either an object or a single declaration
contents ::= object_decl.
contents ::= decl.

// declarations
decls ::= decls decl.
decls ::= decl.
decl ::= assignment.
decl ::= base_assignment.

// type identifier, a::b::c
type_id ::= IDENTIFIER.
type_id ::= SCOPE_OP IDENTIFIER.

// variable identifer
var_id ::= IDENTIFIER.

array_size	 ::= LBRACK INTEGER RBRACK.
array_type	 ::= type_id array_size.
array_type	 ::= array_type array_size.
type	 ::= type_id.
type	 ::= array_type.
variable ::= type var_id.

// assignment
assignment ::= variable EQUALS literal SEMI.
assignment ::= variable LPAREN identifier_list RPAREN EQUALS tuple SEMI.
base_assignment ::= AT IDENTIFIER EQUALS LBRACK decls RBRACK SEMI.

// objects
object_decl ::= LBRACK decls RBRACK.

// identifiers
identifier_list ::= identifier_list COMMA identifier.
identifier_list ::= identifier.
identifier ::= identifier COLON COLON IDENTIFIER.
identifier ::= IDENTIFIER.

// tuples
tuple ::= LBRACK literal_list RBRACK.
literal_list ::= literal_list COMMA literal.
literal_list ::= literal.

// literals
literal ::= STRING.
literal ::= INTEGER.
literal ::= UINTEGER.
literal ::= HEXFLOAT.
literal ::= bool.
literal ::= NULL.
literal ::= tuple.
literal ::= object_decl.

// types
bool ::= TRUE.
bool ::= FALSE.
