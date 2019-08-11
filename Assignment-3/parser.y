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

%left '+' '-'
%left '*' '/'

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
}
	
%type<string_value> NAME
%type<integer_value> INTEGER_NUMBER
%type<double_value> DOUBLE_NUMBER
%type<ast> expr expr1 expr2 expr3 constant



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
                        	statement_list
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
				|   /* empty */
                ;

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
                                  
statement_list	        :	/* empty */
				|	statement_list
					assignment_statement
				;

assignment_statement	:	NAME ASSIGN expr ';'{
								Name_Ast *a1;
								if(local_symbol_table->variable_in_symbol_list_check(*$1)){
									a1 = new Name_Ast(*$1,local_symbol_table->get_symbol_table_entry(*$1),lineno);
									Assignment_Ast *a2 = new Assignment_Ast(a1,$3,lineno);
									procedure_ast_list.push_back(a2);
									if(local_symbol_table->get_symbol_table_entry(*$1).get_data_type() != $3->get_data_type()){
										if(!a2->check_ast()){
											// exit(0);
										}
									}
								}
								else if(global_symbol_table->variable_in_symbol_list_check(*$1)){
									a1 = new Name_Ast(*$1,global_symbol_table->get_symbol_table_entry(*$1),lineno);
									Assignment_Ast *a2 = new Assignment_Ast(a1,$3,lineno);
									procedure_ast_list.push_back(a2);
									if(global_symbol_table->get_symbol_table_entry(*$1).get_data_type() != $3->get_data_type()){
										if(!a2->check_ast()){
											// exit(0);
										}
									}
								}
								else{
									fprintf(stderr,"cs316: Error Undeclared variable Error on line %d\n",lineno);
									exit(0);
								}
 							}
						;

expr	:	expr '+' expr1 {
					Plus_Ast *a1 = new Plus_Ast($1,$3,lineno);
					a1->set_data_type($1->get_data_type());
					$$ = a1;
					$$->check_ast();
			}		 
		| expr '-' expr1{
					Minus_Ast *a1 = new Minus_Ast($1,$3,lineno);
					a1->set_data_type($1->get_data_type());
					$$ = a1;
					$$->check_ast();
				} 
		| expr1{
			$$ = $1;
		}
		;

expr1	:	expr1 '*' expr2{
					Mult_Ast *a1 = new Mult_Ast($1,$3,lineno);
					a1->set_data_type($1->get_data_type());
					$$ = a1;
					if(!$$->check_ast()){
						// exit(0);
					}
		}  
		| expr1 '/' expr2 {
					Divide_Ast *a1 = new Divide_Ast($1,$3,lineno);
					a1->set_data_type($1->get_data_type());
					$$ = a1;
					if(!$$->check_ast()){
						// exit(0);
					}
		}

		| expr2{
			$$ = $1;
		}
		;

expr2   :   '-' expr3{
			UMinus_Ast *a1 = new UMinus_Ast($2,NULL,lineno);
			a1->set_data_type($2->get_data_type());
			$$ = a1;
		}	 
		| expr3{
			$$ = $1;
		}
		;

expr3   :  constant {
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
		| '('expr')'{
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