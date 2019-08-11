%{
 extern "C"  void yyerror(char *);
 int yylex(void);
 extern int lineno;
 Symbol_Table* global_symbol_table = new Symbol_Table();
 Symbol_Table* local_symbol_table = new Symbol_Table();
 list<Ast *>* procedure_ast_list = new list<Ast*>();
 string curr_name;
 int dummy = 1;
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
%token PRINT
%token MAIN

%nonassoc x1
%nonassoc x2

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
	
%type<string_value> NAME MAIN
%type<integer_value> INTEGER_NUMBER
%type<double_value> DOUBLE_NUMBER
%type<ast> expr0 constant
%type<ast> assignment_statement
%type<seq_ast> statement_list
%type<ast> statement boolean_statement 
%type<ast> bool_exp	func_call
%type<relational_op> rel_op
%type<ast_list> args opt_args
%type<symbol_table> type_list arg_list optional_arg_list

%%
program			:	global_variable_declaration_list 
					
					procedure_definition_list{
						global_symbol_table->set_table_scope(global);
						local_symbol_table->set_table_scope(local);
						program_object.set_global_table(*global_symbol_table);
					}

					|
					procedure_definition_list{
						global_symbol_table->set_table_scope(global);
						local_symbol_table->set_table_scope(local);
						program_object.set_global_table(*global_symbol_table);
					}

					;


procedure_definition_list	:	procedure_definition
							|	procedure_definition
								procedure_definition_list

procedure_definition	: 		INTEGER NAME  '(' optional_arg_list ')'
	              	   		'{'{ curr_name = *$2+"_";
	              	   			 Procedure* proc = new Procedure(int_data_type,curr_name,lineno);
								 proc->set_formal_param_list(*$4);
								 program_object.set_proc_to_map(curr_name,proc);
	              	   			}
								optional_variable_declaration_list
	                        	procedure_statement_list
	    	           		'}'	{
	    	           				curr_name = *$2+"_";
	    	           				Procedure* proc = new Procedure(int_data_type,curr_name,lineno);
	    	           				proc->set_local_list(*local_symbol_table);
	    	           				proc->set_ast_list(*procedure_ast_list);
	    	           				proc->set_proc_is_defined();
	    	           				if(program_object.is_procedure_exists(curr_name)){
										if(program_object.get_procedure_prototype(curr_name)->get_return_type() != int_data_type){
											fprintf(stderr, "cs316: Error function already declared with different data type\n");
										}
									}
									proc->set_formal_param_list(*$4);
									program_object.set_proc_to_map(curr_name,proc);
									dummy = 1;
	    	           				local_symbol_table = new Symbol_Table();
	    	           				procedure_ast_list = new list<Ast*>();
	    	           			}
    	           			|
	    	           			FLOAT NAME  '(' optional_arg_list ')'
	              	   		'{'{ curr_name = *$2+"_";
	              	   			 Procedure* proc = new Procedure(double_data_type,curr_name,lineno);
								 proc->set_formal_param_list(*$4);
								 program_object.set_proc_to_map(curr_name,proc);
	              	   			 }
								optional_variable_declaration_list
	                        	procedure_statement_list
	    	           		'}'	{
	    	           				curr_name = *$2+"_";
	    	           				Procedure* proc = new Procedure(double_data_type,curr_name,lineno);
	    	           				proc->set_local_list(*local_symbol_table);
	    	           				proc->set_ast_list(*procedure_ast_list);
	    	           				proc->set_proc_is_defined();
	    	           				if(program_object.is_procedure_exists(curr_name)){
										if(program_object.get_procedure_prototype(curr_name)->get_return_type() != double_data_type){
											fprintf(stderr, "cs316: Error function already declared with different data type\n");
										}
									}
									proc->set_formal_param_list(*$4);
									program_object.set_proc_to_map(curr_name,proc);
									dummy = 1;
	    	           				local_symbol_table = new Symbol_Table();
	    	           				procedure_ast_list = new list<Ast*>();
	    	           			}
    	           			|
	    	           			VOID NAME  '(' optional_arg_list ')'
	              	   		'{'{ if(*$2 == "main"){
	              	   				 curr_name = *$2;
		              	   			 Procedure* proc = new Procedure(void_data_type,*$2,lineno);
									 program_object.set_proc_to_map(*$2,proc);
	              	   			}
	              	   			else{	 
		              	   			 curr_name = *$2+"_";
		              	   			 Procedure* proc = new Procedure(void_data_type,curr_name,lineno);
									 proc->set_formal_param_list(*$4);
									 program_object.set_proc_to_map(curr_name,proc);
									}
	              	   			 }
								optional_variable_declaration_list
	                        	procedure_statement_list
	    	           		'}'	{	
	    	           				if(*$2 == "main"){
	    	           					if($4->get_table().size() != 0){
	    	           						fprintf(stderr, "cs316: Error main cannot be passed arguments\n");
	    	           					}
	    	           					curr_name = *$2;
		    	           				Procedure* proc = new Procedure(void_data_type,*$2,lineno);
		    	           				proc->set_local_list(*local_symbol_table);
		    	           				proc->set_ast_list(*procedure_ast_list);
		    	           				proc->set_proc_is_defined();
										program_object.set_proc_to_map(*$2,proc);
										dummy = 1;
		    	           				local_symbol_table = new Symbol_Table();
		    	           				procedure_ast_list = new list<Ast*>();
	    	           				}
	    	           				else{
		    	           				curr_name = *$2+"_";
		    	           				Procedure* proc = new Procedure(void_data_type,curr_name,lineno);
		    	           				proc->set_local_list(*local_symbol_table);
		    	           				proc->set_ast_list(*procedure_ast_list);
		    	           				proc->set_proc_is_defined();
		    	           				if(program_object.is_procedure_exists(curr_name)){
											if(program_object.get_procedure_prototype(curr_name)->get_return_type() != void_data_type){
												fprintf(stderr, "cs316: Error function already declared with different data type\n");
											}
										}
										proc->set_formal_param_list(*$4);
										program_object.set_proc_to_map(curr_name,proc);
										dummy = 1;
		    	           				local_symbol_table = new Symbol_Table();
		    	           				procedure_ast_list = new list<Ast*>();
		    	           			}
	    	           			}
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
				|			INTEGER NAME '(' optional_arg_list ')'{
								curr_name = *$2+"_";
								Procedure *p1 = new Procedure(int_data_type , curr_name, lineno);
								if(program_object.is_procedure_exists(curr_name)){
									if(program_object.get_procedure_prototype(curr_name)->get_return_type() != int_data_type){
										fprintf(stderr, "cs316: Error function already declared with different data type\n");
									}
								}
								p1->set_formal_param_list(*$4);
								program_object.set_proc_to_map(curr_name,p1);
								dummy = 1;
							}
				|			FLOAT NAME '(' optional_arg_list ')'{
								curr_name = *$2+"_";
								Procedure *p1 = new Procedure(double_data_type , curr_name, lineno);
								if(program_object.is_procedure_exists(curr_name)){
									if(program_object.get_procedure_prototype(curr_name)->get_return_type() != double_data_type){
										fprintf(stderr, "cs316: Error function already declared with different data type\n");
									}
								}
								p1->set_formal_param_list(*$4);
								program_object.set_proc_to_map(curr_name,p1);
								dummy = 1;
							}
				|			VOID NAME '(' optional_arg_list ')'{
								curr_name = *$2+"_";
								Procedure *p1 = new Procedure(void_data_type , curr_name, lineno);
								if(program_object.is_procedure_exists(curr_name)){
									if(program_object.get_procedure_prototype(curr_name)->get_return_type() != void_data_type){
										fprintf(stderr, "cs316: Error function already declared with different data type\n");
									}
								}
								p1->set_formal_param_list(*$4);
								program_object.set_proc_to_map(curr_name,p1);
								dummy = 1;
							}
				|			INTEGER NAME '(' type_list ')'{
								curr_name = *$2+"_";
								Procedure *p1 = new Procedure(int_data_type , curr_name, lineno);
								if(program_object.is_procedure_exists(curr_name)){
									if(program_object.get_procedure_prototype(curr_name)->get_return_type() != int_data_type){
										fprintf(stderr, "cs316: Error function already declared with different data type\n");
									}
								}
								p1->set_formal_param_list(*$4);
								program_object.set_proc_to_map(curr_name,p1);
								dummy = 1;
							}
				|			FLOAT NAME '(' type_list ')'{
								curr_name = *$2+"_";
								Procedure *p1 = new Procedure(double_data_type , curr_name, lineno);
								if(program_object.is_procedure_exists(curr_name)){
									if(program_object.get_procedure_prototype(curr_name)->get_return_type() != double_data_type){
										fprintf(stderr, "cs316: Error function already declared with different data type\n");
									}
								}
								p1->set_formal_param_list(*$4);
								program_object.set_proc_to_map(curr_name,p1);
								dummy = 1;
							}
				|			VOID NAME '(' type_list ')'{
								curr_name = *$2+"_";
								Procedure *p1 = new Procedure(void_data_type , curr_name, lineno);
								if(program_object.is_procedure_exists(curr_name)){
									if(program_object.get_procedure_prototype(curr_name)->get_return_type() != void_data_type){
										fprintf(stderr, "cs316: Error function already declared with different data type\n");
									}
								}
								p1->set_formal_param_list(*$4);
								program_object.set_proc_to_map(curr_name,p1);
								dummy = 1;
							}
                ;


type_list	:	INTEGER{
					Symbol_Table* s1 = new Symbol_Table();
					string s = "dummy" + to_string(dummy);
					dummy++;
					Symbol_Table_Entry *se = new Symbol_Table_Entry(s,int_data_type,lineno);
					se->set_data_type(int_data_type);
					s1->push_symbol(se);
					$$ = s1;
				}
			|	FLOAT{
					Symbol_Table* s1 = new Symbol_Table();
					string s = "dummy" + to_string(dummy);
					dummy++;
					Symbol_Table_Entry *se = new Symbol_Table_Entry(s,double_data_type,lineno);
					se->set_data_type(double_data_type);
					s1->push_symbol(se);
					$$ = s1;
				}
			|	type_list ',' INTEGER{
					string s = "dummy" + to_string(dummy);
					dummy++;
					Symbol_Table_Entry *se = new Symbol_Table_Entry(s,int_data_type,lineno);
					se->set_data_type(int_data_type);
					$1->push_symbol(se);
					$$ = $1;
				}
			|	type_list ',' FLOAT{
					string s = "dummy" + to_string(dummy);
					dummy++;
					Symbol_Table_Entry *se = new Symbol_Table_Entry(s,double_data_type,lineno);
					se->set_data_type(double_data_type);
					$1->push_symbol(se);
					$$ = $1;
				}
			;

optional_arg_list : 	/* empty */{
							Symbol_Table *s1 = new Symbol_Table();
							$$ = s1;
						}
				  |		arg_list{
				  			$$ = $1;
				  }

arg_list	:	INTEGER NAME{
					Symbol_Table* s1 = new Symbol_Table();
					string s = *$2+"_";
					Symbol_Table_Entry *se = new Symbol_Table_Entry(s,int_data_type,lineno);
					se->set_data_type(int_data_type);
					s1->push_symbol(se);
					$$ = s1;
				}
			|	FLOAT NAME{
					Symbol_Table* s1 = new Symbol_Table();
					string s = *$2+"_";
					Symbol_Table_Entry *se = new Symbol_Table_Entry(s,double_data_type,lineno);
					se->set_data_type(double_data_type);
					s1->push_symbol(se);
					$$ = s1;
				}
			|	arg_list ',' INTEGER NAME{
					string s = *$4+"_";
					Symbol_Table_Entry *se = new Symbol_Table_Entry(s,int_data_type,lineno);
					se->set_data_type(int_data_type);
					if($1->variable_in_symbol_list_check(s)){
						fprintf(stderr, "cs316: Error argument with same name exists\n");
					}
					$1->push_symbol(se);
					$$ = $1;
				}
			|	arg_list ',' FLOAT NAME{
					string s = *$4+"_";
					Symbol_Table_Entry *se = new Symbol_Table_Entry(s,double_data_type,lineno);
					se->set_data_type(double_data_type);
					if($1->variable_in_symbol_list_check(s)){
						fprintf(stderr, "cs316: Error argument with same name exists\n");
					}
					$1->push_symbol(se);
					$$ = $1;
				}
			;

declaration		:	INTEGER variable_list_int
				| 	FLOAT variable_list_float
               

global_variable_list_int                           :       NAME{
																if(global_symbol_table->variable_in_symbol_list_check(*$1)){
																	fprintf(stderr,"cs316: Error Variable declared twice on line no:%d\n",lineno);
																	exit(0);
																}
																// else if(program_object.is_procedure_exists){

																// }
																else{
																	string s = *$1+"_";
																	Symbol_Table_Entry *se = new Symbol_Table_Entry(s,int_data_type,lineno);
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
																		string s = *$3+"_";
					                                        			Symbol_Table_Entry *se = new Symbol_Table_Entry(s,int_data_type,lineno);
					                                        			se->set_data_type(int_data_type);
																		global_symbol_table->push_symbol(se);
																	}
															}
                                        			;

variable_list_int                           :       NAME{
																string s = *$1 + "_";
																if(local_symbol_table->variable_in_symbol_list_check(s)){
																	fprintf(stderr,"cs316: Error Variable declared twice on line no:%d\n",lineno);
																	exit(0);
																}
																else{
																	Symbol_Table_Entry *se = new Symbol_Table_Entry(s,int_data_type,lineno);
																	se->set_data_type(int_data_type);
																	local_symbol_table->push_symbol(se);
																}
														   }
			                                        |       variable_list_int ',' NAME {
			                                        				string s = *$3+ "_";
			                                        				if(local_symbol_table->variable_in_symbol_list_check(s)){
			                                        					fprintf(stderr,"cs316: Error Variable declared twice on line no:%d\n",lineno);
																		exit(0);
																	}
																	else{
																		Symbol_Table_Entry *se = new Symbol_Table_Entry(s,int_data_type,lineno);
					                                        			se->set_data_type(int_data_type);
																		local_symbol_table->push_symbol(se);
																	}
															}
                                        			;

global_variable_list_float                           :     NAME{
																string s = *$1 + "_";
																if(global_symbol_table->variable_in_symbol_list_check(s)){
																	fprintf(stderr,"cs316: Error Variable declared twice on line no:%d\n",lineno);
																	exit(0);
																}
																else{
																	Symbol_Table_Entry *se = new Symbol_Table_Entry(s,double_data_type,lineno);
																	se->set_data_type(double_data_type);
																	global_symbol_table->push_symbol(se);
																}
														   }
			                                        |       global_variable_list_float ',' NAME{
			                                        				string s = *$3 + "_";
			                                        				if(global_symbol_table->variable_in_symbol_list_check(s)){
																		fprintf(stderr,"cs316: Error Variable declared twice on line no:%d\n",lineno);
																		exit(0);
																	}
																	else{
					                                        			Symbol_Table_Entry *se = new Symbol_Table_Entry(s,double_data_type,lineno);
					                                        			se->set_data_type(double_data_type);
																		global_symbol_table->push_symbol(se);
																	}
															}
                                        			;


variable_list_float                           :       NAME{
																string s = *$1+"_";
																if(local_symbol_table->variable_in_symbol_list_check(s)){
																	fprintf(stderr,"cs316: Error Variable declared twice on line no:%d\n",lineno);
																	exit(0);
																}
																else{
																	Symbol_Table_Entry *se = new Symbol_Table_Entry(s,double_data_type,lineno);
																	se->set_data_type(double_data_type);
																	local_symbol_table->push_symbol(se);
																}
														   }
			                                        |       variable_list_float ',' NAME{
			                                        				string s = *$3+"_";
																	if(local_symbol_table->variable_in_symbol_list_check(s)){
																		fprintf(stderr,"cs316: Error Variable declared twice on line no:%d\n",lineno);
																		exit(0);
																	}
																	else{
					                                        			Symbol_Table_Entry *se = new Symbol_Table_Entry(s,double_data_type,lineno);
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

procedure_statement_list	        :	/* empty */
				|	procedure_statement_list
					statement{
						// $1->ast_push_back($2);
						// $$ = $1;
						procedure_ast_list->push_back($2);
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
		  | PRINT NAME ';'{
		  	string s = *$2+"_";
		  	if(local_symbol_table->variable_in_symbol_list_check(s)){
				Name_Ast *a1 = new Name_Ast(s,local_symbol_table->get_symbol_table_entry(s),lineno);
				a1->set_data_type(local_symbol_table->get_symbol_table_entry(s).get_data_type());
				Print_Ast *p1 = new Print_Ast(a1,lineno);
				$$ = p1;
			}
			else if(program_object.get_procedure_prototype(curr_name)->get_formal_param_list().variable_in_symbol_list_check(s)){
				Name_Ast *a1 = new Name_Ast(s,program_object.get_procedure_prototype(curr_name)->get_formal_param_list().get_symbol_table_entry(s),lineno);
				a1->set_data_type(program_object.get_procedure_prototype(curr_name)->get_formal_param_list().get_symbol_table_entry(s).get_data_type());
				Print_Ast *p1 = new Print_Ast(a1,lineno);
				$$ = p1;	
			}
			else if(global_symbol_table->variable_in_symbol_list_check(s)){
				Name_Ast *a1 = new Name_Ast(s,global_symbol_table->get_symbol_table_entry(s),lineno);
				a1->set_data_type(global_symbol_table->get_symbol_table_entry(s).get_data_type());
				Print_Ast *p1 = new Print_Ast(a1,lineno);
				$$ = p1;
			}
			else{
				fprintf(stderr,"cs316: Error Unitialised variable Error on line %d\n",lineno);
				exit(0);
			}
		  }
		  | RETURN ';' {
		  		if(program_object.get_procedure_prototype(curr_name)->get_return_type() != void_data_type){
		  			fprintf(stderr,"cs316: Error  Return type not matching at line %d\n",lineno);
		  		}
		  		Return_Ast* r1 = new Return_Ast(NULL, curr_name, lineno);
		  		$$ = r1;
		  }
		  | RETURN expr0 ';'{
			  	if(program_object.get_procedure_prototype(curr_name)->get_return_type() != $2->get_data_type()){
		  			fprintf(stderr,"cs316: Error  Return type not matching at line %d\n",lineno);
		  		}
		  		Return_Ast* r1 = new Return_Ast($2, curr_name, lineno);
		  		$$ = r1;
		  }	
		  | func_call ';'{
		  		$$ = $1;
		  }
		  | '{' statement_list '}'{
		  	 $$ = $2;
		  }
 

boolean_statement : boolean_statement AND boolean_statement{
						Logical_Expr_Ast *r1 = new Logical_Expr_Ast($1,_logical_and,$3,lineno);
						r1->set_data_type($1->get_data_type());
						r1->check_ast();
						$$ = r1;
					}
				|   NOT boolean_statement{
						Logical_Expr_Ast *r1 = new Logical_Expr_Ast(NULL,_logical_not,$2,lineno);
						r1->set_data_type($2->get_data_type());
						r1->check_ast();
						$$ = r1;
				}
				|
				boolean_statement OR boolean_statement{
						Logical_Expr_Ast *r1 = new Logical_Expr_Ast($1,_logical_or,$3,lineno);
						r1->set_data_type($1->get_data_type());
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
				r1->set_data_type($1->get_data_type());
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
								string s = *$1 + "_";
								if(local_symbol_table->variable_in_symbol_list_check(s)){
									a1 = new Name_Ast(s,local_symbol_table->get_symbol_table_entry(s),lineno);
									Assignment_Ast *a2 = new Assignment_Ast(a1,$3,lineno);
									if(local_symbol_table->get_symbol_table_entry(s).get_data_type() != $3->get_data_type()){
										if(!a2->check_ast()){
											// exit(0);
										}
									}
									$$ = a2;
								}
								else if(program_object.get_procedure_prototype(curr_name)->get_formal_param_list().variable_in_symbol_list_check(s)){
									a1 = new Name_Ast(s,program_object.get_procedure_prototype(curr_name)->get_formal_param_list().get_symbol_table_entry(s),lineno);
									Assignment_Ast *a2 = new Assignment_Ast(a1,$3,lineno);
									if(program_object.get_procedure_prototype(curr_name)->get_formal_param_list().get_symbol_table_entry(s).get_data_type() != $3->get_data_type()){
										if(!a2->check_ast()){
											// exit(0);
										}
									}
									$$ = a2;
								} 
								else if(global_symbol_table->variable_in_symbol_list_check(s)){
									a1 = new Name_Ast(s,global_symbol_table->get_symbol_table_entry(s),lineno);
									Assignment_Ast *a2 = new Assignment_Ast(a1,$3,lineno);
									if(global_symbol_table->get_symbol_table_entry(s).get_data_type() != $3->get_data_type()){
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
 							| NAME ASSIGN func_call ';'{
 								Name_Ast *a1;
								string s = *$1 + "_";
								if(local_symbol_table->variable_in_symbol_list_check(s)){
									a1 = new Name_Ast(s,local_symbol_table->get_symbol_table_entry(s),lineno);
									Assignment_Ast *a2 = new Assignment_Ast(a1,$3,lineno);
									if(local_symbol_table->get_symbol_table_entry(s).get_data_type() != $3->get_data_type()){
										if(!a2->check_ast()){
											// exit(0);
										}
									}
									$$ = a2;
								}
								else if(program_object.get_procedure_prototype(curr_name)->get_formal_param_list().variable_in_symbol_list_check(s)){
									a1 = new Name_Ast(s,program_object.get_procedure_prototype(curr_name)->get_formal_param_list().get_symbol_table_entry(s),lineno);
									Assignment_Ast *a2 = new Assignment_Ast(a1,$3,lineno);
									if(program_object.get_procedure_prototype(curr_name)->get_formal_param_list().get_symbol_table_entry(s).get_data_type() != $3->get_data_type()){
										if(!a2->check_ast()){
											// exit(0);
										}
									}
									$$ = a2;
								}
								else if(global_symbol_table->variable_in_symbol_list_check(s)){
									a1 = new Name_Ast(s,global_symbol_table->get_symbol_table_entry(s),lineno);
									Assignment_Ast *a2 = new Assignment_Ast(a1,$3,lineno);
									if(global_symbol_table->get_symbol_table_entry(s).get_data_type() != $3->get_data_type()){
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

func_call	:	NAME '(' opt_args ')' {
					string name;
					if(*$1 == "main"){
						name = *$1;
					}
					else{
						name = *$1 + "_";
					}
					if(!program_object.is_procedure_exists(name)){
						fprintf(stderr,"cs316: Error procedure not defined at line %d\n",lineno);
					}
					else{
						program_object.get_procedure_prototype(name)->set_proc_is_called();
					}
					Call_Ast * c1 = new Call_Ast(name,lineno);
					c1->set_actual_param_list(*$3);
					$$ = c1;
				}

opt_args :	/*empty*/{
				list<Ast*> *l1 = new list<Ast*>;
				$$ = l1;
			}
		 |	args{
		 		$$ = $1;
		 }

args 	:	expr0{
				list<Ast*> *l1 = new list<Ast*>;
				l1->push_back($1);
				$$ = l1;
			}
		|	args ',' expr0{
				$1->push_back($3);
				$$ = $1;
			}

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
			string s = *$1 + "_";
			if(local_symbol_table->variable_in_symbol_list_check(s)){
				Name_Ast *a1 = new Name_Ast(s,local_symbol_table->get_symbol_table_entry(s),lineno);
				a1->set_data_type(local_symbol_table->get_symbol_table_entry(s).get_data_type());
				$$ = a1;
			}
			else if(program_object.get_procedure_prototype(curr_name)->get_formal_param_list().variable_in_symbol_list_check(s)){
				Name_Ast *a1 = new Name_Ast(s,program_object.get_procedure_prototype(curr_name)->get_formal_param_list().get_symbol_table_entry(s),lineno);
				a1->set_data_type(program_object.get_procedure_prototype(curr_name)->get_formal_param_list().get_symbol_table_entry(s).get_data_type());
				$$ = a1;	
			} 
			else if(global_symbol_table->variable_in_symbol_list_check(s)){
				Name_Ast *a1 = new Name_Ast(s,global_symbol_table->get_symbol_table_entry(s),lineno);
				a1->set_data_type(global_symbol_table->get_symbol_table_entry(s).get_data_type());
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