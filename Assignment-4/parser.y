%{
 extern "C"  void yyerror(char *);
 int yylex(void);
 extern int lineno;
 Symbol_Table* global_symbol_table = new Symbol_Table();
 Symbol_Table* local_symbol_table = new Symbol_Table();
 list<Ast *> procedure_ast_list;
%}


%token INTEGER_NUMBER
%token BBNUM
%token DOUBLE_NUMBER
%token NAME 
%token RETURN
%token INTEGER
%token FLOAT 
%token ASSIGN
%token VOID 
%token UMINUS 
%token DO
%token WHILE
%token IF
%token ELSE
%token LTE
%token GTE
%token GT
%token LT
%token NEQ
%token EQ
%token AND
%token OR
%token NOT

%left IF
%left ELSE
%right '?' ':'
%left OR
%left AND
%left EQ NEQ
%left GT GTE LT LTE
%left '+' '-'
%left '*' '/'
%right NOT UMINUS


%union {
    int integer_value;
	double double_value;
	std::string * string_value;
	list<Ast *> * ast_list;
	Ast * ast;
	Symbol_Table * symbol_table;
	Symbol_Table_Entry * symbol_entry;
	Basic_Block * basic_block; 
	Procedure * procedure;
	Logical_Op logical_op;
	Relational_Op relational_op;
	Sequence_Ast * seq_ast;

}
	
%type<string_value> NAME
%type<integer_value> INTEGER_NUMBER
%type<double_value> DOUBLE_NUMBER
%type<ast> expr0 constant
%type<ast> assignment_statement
%type<seq_ast> statement_list procedure_statement_list
%type<ast> statement boolean_statement 
%type<ast> bool_exp	
%type<relational_op> rel_op

%%
program			:	global_optional_variable_declaration_list
					
					procedure_definition{
						global_symbol_table->set_table_scope(global);
						local_symbol_table->set_table_scope(local);
						program_object.set_global_table(*global_symbol_table);
					}
					;

procedure_definition	: VOID NAME '(' ')'
              	   		'{'
							optional_variable_declaration_list
                        	procedure_statement_list
    	           		'}'	{
    	           				Procedure* proc = new Procedure(void_data_type,*$2,lineno);
    	           				proc->set_local_list(*local_symbol_table);
    	           				proc->set_ast_list(procedure_ast_list);
    	           				program_object.set_procedure(proc,lineno);
    	           			}

global_optional_variable_declaration_list	:	/* empty */
									|	global_variable_declaration_list
									;
                     	;

optional_variable_declaration_list	:	/* empty */
									|	variable_declaration_list
									;

global_variable_declaration_list		:	global_variable_declaration
					 			|	global_variable_declaration_list 
									global_variable_declaration 
								;

variable_declaration_list		:	variable_declaration
					 			|	variable_declaration_list 
									variable_declaration
								;

global_variable_declaration	:	global_declaration ';'

variable_declaration	:	declaration ';'
					;

global_declaration		:	INTEGER global_variable_list_int
				| 			FLOAT global_variable_list_float 
				|   /* empty */
                ;

declaration		:	INTEGER variable_list_int 
				| 	FLOAT variable_list_float 
               

global_variable_list_int                           :       NAME{
																if(global_symbol_table->variable_in_symbol_list_check(*$1)){
																	fprintf(stderr,"cs316: Error Variable declared twice on line no:%d\n",lineno);
																	exit(0);
																}
																else{
																	Symbol_Table_Entry *se = new Symbol_Table_Entry(*$1,int_data_type,lineno);
																	se->set_data_type(int_data_type);
																	global_symbol_table->push_symbol(se);
																}
														   }
			                                        |       global_variable_list_int ',' NAME {
			                                        				if(global_symbol_table->variable_in_symbol_list_check(*$3)){
																		fprintf(stderr,"cs316: Error Variable declared twice on line no: %d\n",lineno);
																		exit(0);
																	}
																	else{
					                                        			Symbol_Table_Entry *se = new Symbol_Table_Entry(*$3,int_data_type,lineno);
					                                        			se->set_data_type(int_data_type);
																		global_symbol_table->push_symbol(se);
																	}
															}
                                        			;

variable_list_int                           :       NAME{
																if(local_symbol_table->variable_in_symbol_list_check(*$1)){
																	fprintf(stderr,"cs316: Error Variable declared twice on line no:%d\n",lineno);
																	exit(0);
																}
																else{
																	Symbol_Table_Entry *se = new Symbol_Table_Entry(*$1,int_data_type,lineno);
																	se->set_data_type(int_data_type);
																	local_symbol_table->push_symbol(se);
																}
														   }
			                                        |       variable_list_int ',' NAME {

			                                        				if(local_symbol_table->variable_in_symbol_list_check(*$3)){
			                                        					fprintf(stderr,"cs316: Error Variable declared twice on line no:%d\n",lineno);
																		exit(0);
																	}
																	else{
																		Symbol_Table_Entry *se = new Symbol_Table_Entry(*$3,int_data_type,lineno);
					                                        			se->set_data_type(int_data_type);
																		local_symbol_table->push_symbol(se);
																	}
															}
                                        			;

global_variable_list_float                           :     NAME{
																if(global_symbol_table->variable_in_symbol_list_check(*$1)){
																	fprintf(stderr,"cs316: Error Variable declared twice on line no:%d\n",lineno);
																	exit(0);
																}
																else{
																	Symbol_Table_Entry *se = new Symbol_Table_Entry(*$1,double_data_type,lineno);
																	se->set_data_type(double_data_type);
																	global_symbol_table->push_symbol(se);
																}
														   }
			                                        |       global_variable_list_float ',' NAME{
			                                        				if(global_symbol_table->variable_in_symbol_list_check(*$3)){
																		fprintf(stderr,"cs316: Error Variable declared twice on line no:%d\n",lineno);
																		exit(0);
																	}
																	else{
					                                        			Symbol_Table_Entry *se = new Symbol_Table_Entry(*$3,double_data_type,lineno);
					                                        			se->set_data_type(double_data_type);
																		global_symbol_table->push_symbol(se);
																	}
															}
                                        			;


variable_list_float                           :       NAME{

																if(local_symbol_table->variable_in_symbol_list_check(*$1)){
																	fprintf(stderr,"cs316: Error Variable declared twice on line no:%d\n",lineno);
																	exit(0);
																}
																else{
																	Symbol_Table_Entry *se = new Symbol_Table_Entry(*$1,double_data_type,lineno);
																	se->set_data_type(double_data_type);
																	local_symbol_table->push_symbol(se);
																}
														   }
			                                        |       variable_list_float ',' NAME{
			                                        				if(local_symbol_table->variable_in_symbol_list_check(*$3)){
																		fprintf(stderr,"cs316: Error Variable declared twice on line no:%d\n",lineno);
																		exit(0);
																	}
																	else{
					                                        			Symbol_Table_Entry *se = new Symbol_Table_Entry(*$3,double_data_type,lineno);
					                                        			se->set_data_type(double_data_type);
																		local_symbol_table->push_symbol(se);
																	}
															}
                                        			;
                                  
statement_list	        :	statement{ 
								Sequence_Ast* a1 = new Sequence_Ast(lineno); 
								a1->ast_push_back($1);
								$$ = a1;
							}
				|	statement_list
					statement{
						$1->ast_push_back($2);
						$$ = $1;
					}
				;

procedure_statement_list	        :	/* empty */{ Sequence_Ast* a1 = new Sequence_Ast(lineno); $$ = a1;}
				|	procedure_statement_list
					statement{
						$1->ast_push_back($2);
						$$ = $1;
						procedure_ast_list.push_back($2);
					}
				;


statement : IF'(' boolean_statement ')' statement ELSE statement %prec ELSE{
			 Selection_Statement_Ast* s1 = new Selection_Statement_Ast($3,$5,$7,lineno);
			 $$ = s1;
			 $$->check_ast();
		  }
		  | IF '(' boolean_statement ')' statement %prec IF{
				Selection_Statement_Ast* s1 = new Selection_Statement_Ast($3,$5,NULL,lineno);
				$$ = s1;
				$$->check_ast();
			}
		  | WHILE '(' boolean_statement ')' statement{
		  	 Iteration_Statement_Ast* i1 = new Iteration_Statement_Ast($3,$5,lineno,false);
		  	 i1->check_ast();
		  	 $$ = i1;
		  }
		  | DO statement WHILE '(' boolean_statement ')' ';'{
		  	 Iteration_Statement_Ast* i1 = new Iteration_Statement_Ast($5,$2,lineno,true);
		  	 i1->check_ast();
		  	 $$ = i1;
		  }
		  | assignment_statement{
		  	 $$ = $1;
		  }
		  | '{' statement_list '}'{
		  	 $$ = $2;
		  }
 

boolean_statement : boolean_statement AND boolean_statement{
						Logical_Expr_Ast *r1 = new Logical_Expr_Ast($1,_logical_and,$3,lineno);
						r1->check_ast();
						$$ = r1;
					}
				|   NOT boolean_statement{
						Logical_Expr_Ast *r1 = new Logical_Expr_Ast(NULL,_logical_not,$2,lineno);
						$$ = r1;
				}
				|
				boolean_statement OR boolean_statement{
						Logical_Expr_Ast *r1 = new Logical_Expr_Ast($1,_logical_or,$3,lineno);
						r1->check_ast();
						$$ = r1;
					}
				|	'(' boolean_statement ')'{
						$$ = $2;
				}
				|	bool_exp{
					$$ = $1;
				}


bool_exp : expr0 rel_op expr0{
				Relational_Expr_Ast *r1 = new Relational_Expr_Ast($1,$2,$3,lineno);
				r1->check_ast();
				$$ = r1;
			}

rel_op : LTE{ $$ = less_equalto;} 
		| EQ{ $$ = equalto;} 
		| NEQ{ $$ = not_equalto;}
		| GTE{ $$ = greater_equalto;} 
		| GT{ $$ = greater_than;} 
		| LT{ $$ = less_than;}


assignment_statement	:	NAME ASSIGN expr0 ';'{
								Name_Ast *a1;
								if(local_symbol_table->variable_in_symbol_list_check(*$1)){
									a1 = new Name_Ast(*$1,local_symbol_table->get_symbol_table_entry(*$1),lineno);
									Assignment_Ast *a2 = new Assignment_Ast(a1,$3,lineno);
									if(local_symbol_table->get_symbol_table_entry(*$1).get_data_type() != $3->get_data_type()){
										if(!a2->check_ast()){
											// exit(0);
										}
									}
									$$ = a2;
								}
								else if(global_symbol_table->variable_in_symbol_list_check(*$1)){
									a1 = new Name_Ast(*$1,global_symbol_table->get_symbol_table_entry(*$1),lineno);
									Assignment_Ast *a2 = new Assignment_Ast(a1,$3,lineno);
									if(global_symbol_table->get_symbol_table_entry(*$1).get_data_type() != $3->get_data_type()){
										if(!a2->check_ast()){
											// exit(0);
										}
									}
									$$ = a2;
								}
								else{
									fprintf(stderr,"cs316: Error Undeclared variable Error on line %d\n",lineno);
									exit(0);
								}
 							}
						;


expr0 : boolean_statement '?' expr0 ':' expr0{
			Conditional_Expression_Ast * a1 = new Conditional_Expression_Ast($1,$3,$5,lineno);
			a1->set_data_type($3->get_data_type());
			$$ = a1;
			$$->check_ast();
		}
		|
			expr0 '+' expr0 {
					Plus_Ast *a1 = new Plus_Ast($1,$3,lineno);
					a1->set_data_type($1->get_data_type());
					$$ = a1;
					$$->check_ast();
			}		 
		| expr0 '-' expr0{
					Minus_Ast *a1 = new Minus_Ast($1,$3,lineno);
					a1->set_data_type($1->get_data_type());
					$$ = a1;
					$$->check_ast();
				} 
		| 
		expr0 '*' expr0{
					Mult_Ast *a1 = new Mult_Ast($1,$3,lineno);
					a1->set_data_type($1->get_data_type());
					$$ = a1;
					if(!$$->check_ast()){
						// exit(0);
					}
		}  
		| expr0 '/' expr0 {
					Divide_Ast *a1 = new Divide_Ast($1,$3,lineno);
					a1->set_data_type($1->get_data_type());
					$$ = a1;
					if(!$$->check_ast()){
						// exit(0);
					}
		}

		| '-' expr0 %prec UMINUS{
			UMinus_Ast *a1 = new UMinus_Ast($2,NULL,lineno);
			a1->set_data_type($2->get_data_type());
			$$ = a1;
		}	 
		|   constant {
			$$ = $1;
		}

		| NAME{
			if(local_symbol_table->variable_in_symbol_list_check(*$1)){
				Name_Ast *a1 = new Name_Ast( *$1,local_symbol_table->get_symbol_table_entry( *$1),lineno);
				a1->set_data_type(local_symbol_table->get_symbol_table_entry( *$1).get_data_type());
				$$ = a1;
			}
			else if(global_symbol_table->variable_in_symbol_list_check(*$1)){
				Name_Ast *a1 = new Name_Ast( *$1,global_symbol_table->get_symbol_table_entry( *$1),lineno);
				a1->set_data_type(global_symbol_table->get_symbol_table_entry( *$1).get_data_type());
				$$ = a1;
			}
			else{
				fprintf(stderr,"cs316: Error Unitialised variable Error on line %d\n",lineno);
				exit(0);
			}
		} 
		| '('expr0')'{
			$$ = $2;
		}


constant		:	INTEGER_NUMBER{
						Number_Ast<int> *a1 = new Number_Ast<int>($1,int_data_type,lineno);
						$$ = a1;
				}
				|   DOUBLE_NUMBER{
						Number_Ast<double> *a1 = new Number_Ast<double>($1,double_data_type,lineno);
						$$ = a1;
				}
				;

%%

extern "C" void yyerror(char *s) {
 fprintf(stderr, "%s\n", s);
 return;
}