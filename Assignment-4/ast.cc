
template class Number_Ast<double>;
template class Number_Ast<int>;

int Ast::labelCounter = -1;     //insert this line in ast.cc to complete the definition

Ast::Ast(){

}

Data_Type Ast::get_data_type(){
	return node_data_type;
}

void Ast::set_data_type(Data_Type dt){
	node_data_type = dt;
	return;
}

void Ast::print(ostream & file_buffer){

}

bool Ast::is_value_zero(){
	return false;
}

Symbol_Table_Entry & Ast::get_symbol_entry(){

}

bool Ast::check_ast(){

}

Ast::~Ast(){

}

void Ast::print_value(Local_Environment & eval_env, ostream & file_buffer){

}

Eval_Result & Ast::get_value_of_evaluation(Local_Environment & eval_env){

}

void Ast::set_value_of_evaluation(Local_Environment & eval_env, Eval_Result & result){

}



///////////////////////////////////////////////////////////////////

Name_Ast::Name_Ast(string & name, Symbol_Table_Entry & var_entry, int line){
	variable_symbol_entry = &var_entry;
	lineno = line;
	ast_num_child = zero_arity;
	node_data_type = var_entry.get_data_type();
}

void Name_Ast::set_data_type(Data_Type dt){
	node_data_type = dt;
}

Data_Type Name_Ast::get_data_type(){
	return node_data_type;
}

void Name_Ast::print(ostream & file_buffer){
	file_buffer << "Name : " << variable_symbol_entry->get_variable_name();
}

Symbol_Table_Entry & Name_Ast::get_symbol_entry(){
	return *(variable_symbol_entry);
}

//////////////////////////////////////////////////////////////////

/////////////////////

template <>
Number_Ast<int>::Number_Ast(int number, Data_Type constant_data_type, int line){
	constant = number;
	node_data_type = constant_data_type;
	lineno = line;
	ast_num_child = zero_arity;	
}

template<>
void Number_Ast<int>::set_data_type(Data_Type dt){
	node_data_type = dt;
}

template<>
Data_Type Number_Ast<int>::get_data_type(){
	return node_data_type;
}

template<>
void Number_Ast<int>::print(ostream & file_buffer){
	file_buffer << "Num : " << constant;
}

template<>
bool Number_Ast<int>::is_value_zero(){
	if(constant == 0){
		return true;
	}
	return false;
}


/////////////////////

template <>
Number_Ast<double>::Number_Ast(double number, Data_Type constant_data_type, int line){
	constant = number;
	node_data_type = constant_data_type;
	lineno = line;
	ast_num_child = zero_arity;	
}

template<>
void Number_Ast<double>::set_data_type(Data_Type dt){
	node_data_type = dt;
}

template<>
Data_Type Number_Ast<double>::get_data_type(){
	return node_data_type;
}

template<>
void Number_Ast<double>::print(ostream & file_buffer){
	file_buffer  << "Num : " << constant;
}

template<>
bool Number_Ast<double>::is_value_zero(){
	if(constant == 0.0){
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////

void Arithmetic_Expr_Ast::set_data_type(Data_Type dt){
	node_data_type = dt;
}

Data_Type Arithmetic_Expr_Ast::get_data_type(){
	return node_data_type;
}

bool Arithmetic_Expr_Ast::check_ast(){
	if(rhs!=NULL){
		if(lhs->get_data_type() != rhs->get_data_type()){
			fprintf(stderr,"cs316: Error in Arithmetic_Expr_Ast\n");
			return 0;
		}
	}
	return 1;
}

void Arithmetic_Expr_Ast::print(ostream & file_buffer){
	
}


//////////////////////////////////////////////////////////////

Plus_Ast::Plus_Ast(Ast * l, Ast * r, int line){
	lhs = l;
	rhs = r;
	lineno = line;
	ast_num_child = binary_arity;
}

void Plus_Ast::print(ostream & file_buffer){
	file_buffer << "\n" << AST_NODE_SPACE << "Arith: PLUS\n" << AST_SUB_NODE_SPACE << "LHS (";
	lhs->print(file_buffer);
	file_buffer << ")"; 
	file_buffer << "\n"<<AST_SUB_NODE_SPACE<<"RHS (";
	rhs->print(file_buffer);
	file_buffer << ")";
}


///////////////////////////////////////////////////////////////

Minus_Ast::Minus_Ast(Ast * l, Ast * r, int line){
	lhs = l;
	rhs = r;
	lineno = line;
	ast_num_child = binary_arity;
}

void Minus_Ast::print(ostream & file_buffer){
	file_buffer << "\n" << AST_NODE_SPACE << "Arith: MINUS\n" << AST_SUB_NODE_SPACE << "LHS (";
	lhs->print(file_buffer);
	file_buffer << ")"; 
	file_buffer << "\n"<<AST_SUB_NODE_SPACE<<"RHS (";
	rhs->print(file_buffer);
	file_buffer << ")";
}

///////////////////////////////////////////////////////////////

Divide_Ast::Divide_Ast(Ast * l, Ast * r, int line){
	lhs = l;
	rhs = r;
	lineno = line;
	ast_num_child = binary_arity;
}

void Divide_Ast::print(ostream & file_buffer){
	file_buffer << "\n" << AST_NODE_SPACE << "Arith: DIV\n" << AST_SUB_NODE_SPACE << "LHS (";
	lhs->print(file_buffer);
	file_buffer << ")"; 
	file_buffer << "\n"<<AST_SUB_NODE_SPACE<<"RHS (";
	rhs->print(file_buffer);
	file_buffer << ")";	
}

///////////////////////////////////////////////////////////////

Mult_Ast::Mult_Ast(Ast * l, Ast * r, int line){
	lhs = l;
	rhs = r;
	lineno = line;
	ast_num_child = binary_arity;
}

void Mult_Ast::print(ostream & file_buffer){
	file_buffer << "\n" << AST_NODE_SPACE << "Arith: MULT\n" << AST_SUB_NODE_SPACE << "LHS (";
	lhs->print(file_buffer); 
	file_buffer << ")";
	file_buffer << "\n"<<AST_SUB_NODE_SPACE<<"RHS (";
	rhs->print(file_buffer);
	file_buffer << ")";	
}

///////////////////////////////////////////////////////////////

UMinus_Ast::UMinus_Ast(Ast * l, Ast * r, int line){
	lhs = l;
	rhs = r;
	lineno = line;
	ast_num_child = unary_arity;
}

void UMinus_Ast::print(ostream & file_buffer){
	file_buffer << "\n" << AST_NODE_SPACE << "Arith: UMINUS\n" << AST_SUB_NODE_SPACE << "LHS (";
	lhs->print(file_buffer);
	file_buffer << ")";
}



////////////////////////////////////////////////////////////////


Assignment_Ast::Assignment_Ast(Ast * temp_lhs, Ast * temp_rhs, int line){
	lhs = temp_lhs;
	rhs = temp_rhs;
	lineno = line;
	ast_num_child = binary_arity;
}

bool Assignment_Ast::check_ast(){
	if(lhs->get_data_type() != rhs->get_data_type()){
		fprintf(stderr,"cs316: Error in Assignment_Ast \n");
		return 0;
	}
	return 1;
}

void Assignment_Ast::print(ostream & file_buffer){
	file_buffer << "\n" << AST_SPACE << "Asgn:\n" << AST_NODE_SPACE << "LHS (";
	lhs->print(file_buffer);
	file_buffer << ")";
	file_buffer <<  "\n"<< AST_NODE_SPACE <<"RHS (";
	rhs->print(file_buffer);
	file_buffer << ")";
}
////////////////////////////////////////////////////////////////


Return_Ast::Return_Ast(int line){

}

Return_Ast::~Return_Ast(){
	
}

void Return_Ast::print(ostream & file_buffer){
		
}

Eval_Result & Return_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){

}


/////////////////////////////////////////////////////////////////
Relational_Expr_Ast::Relational_Expr_Ast(Ast * lhs, Relational_Op rop, Ast * rhs, int line){
	lhs_condition = lhs;
	rhs_condition = rhs;
	rel_op = rop;
	lineno = line;
}

Data_Type Relational_Expr_Ast::get_data_type(){
	return node_data_type;
}

void Relational_Expr_Ast::set_data_type(Data_Type dt){
	node_data_type = dt;
	return;
}

bool Relational_Expr_Ast::check_ast(){
	if(lhs_condition->get_data_type() == rhs_condition->get_data_type()){
		return true;
	}
	return false;
}

void Relational_Expr_Ast::print(ostream & file_buffer){
	if(rel_op == greater_than){
		file_buffer << "\n" << AST_NODE_SPACE << "Condition:" << " GT\n" << AST_SUB_NODE_SPACE << "LHS (";
		lhs_condition->print(file_buffer);
		file_buffer << ")";
		file_buffer <<  "\n"<< AST_SUB_NODE_SPACE <<"RHS (";
		rhs_condition->print(file_buffer);
		file_buffer << ")";
	}
	else if(rel_op == less_than){
		file_buffer << "\n" << AST_NODE_SPACE << "Condition:" << " LT\n" << AST_SUB_NODE_SPACE << "LHS (";
		lhs_condition->print(file_buffer);
		file_buffer << ")";
		file_buffer <<  "\n"<< AST_SUB_NODE_SPACE <<"RHS (";
		rhs_condition->print(file_buffer);
		file_buffer << ")";
	}
	else if(rel_op == greater_equalto){
		file_buffer << "\n" << AST_NODE_SPACE << "Condition:" << " GE\n" << AST_SUB_NODE_SPACE << "LHS (";
		lhs_condition->print(file_buffer);
		file_buffer << ")";
		file_buffer <<  "\n"<< AST_SUB_NODE_SPACE <<"RHS (";
		rhs_condition->print(file_buffer);
		file_buffer << ")";
	}
	else if(rel_op == less_equalto){
		file_buffer << "\n" << AST_NODE_SPACE << "Condition:" << " LE\n" << AST_SUB_NODE_SPACE << "LHS (";
		lhs_condition->print(file_buffer);
		file_buffer << ")";
		file_buffer <<  "\n"<< AST_SUB_NODE_SPACE <<"RHS (";
		rhs_condition->print(file_buffer);
		file_buffer << ")";
	}
	else if(rel_op == equalto){
		file_buffer << "\n" << AST_NODE_SPACE << "Condition:" << " EQ\n" << AST_SUB_NODE_SPACE << "LHS (";
		lhs_condition->print(file_buffer);
		file_buffer << ")";
		file_buffer <<  "\n"<< AST_SUB_NODE_SPACE <<"RHS (";
		rhs_condition->print(file_buffer);
		file_buffer << ")";
	}
	else if(rel_op == not_equalto){
		file_buffer << "\n" << AST_NODE_SPACE << "Condition:" << " NE\n" << AST_SUB_NODE_SPACE << "LHS (";
		lhs_condition->print(file_buffer);
		file_buffer << ")";
		file_buffer <<  "\n"<< AST_SUB_NODE_SPACE <<"RHS (";
		rhs_condition->print(file_buffer);
		file_buffer << ")";
	}
	
}

/////////////////////////////////////////////////////////////////

Logical_Expr_Ast::Logical_Expr_Ast(Ast * lhs, Logical_Op bop, Ast * rhs, int line){
	lhs_op = lhs;
	rhs_op = rhs;
	bool_op = bop;
	lineno = line;
}

Data_Type Logical_Expr_Ast::get_data_type(){
	return node_data_type;
}

void Logical_Expr_Ast::set_data_type(Data_Type dt){
	node_data_type = dt;
	return;
}

bool Logical_Expr_Ast::check_ast(){
	if(lhs_op!=NULL){
		if(lhs_op->get_data_type() == rhs_op->get_data_type()){
			return true;
		}
		else return false;
	}
	else return true;
}

void Logical_Expr_Ast::print(ostream & file_buffer){
	if(bool_op == _logical_and){
		file_buffer << "\n" << AST_NODE_SPACE << "Condition:" << " AND\n" << AST_SUB_NODE_SPACE << "LHS (";
		lhs_op->print(file_buffer);

		file_buffer <<  ")\n"<< AST_SUB_NODE_SPACE <<"RHS (";
		rhs_op->print(file_buffer);
		file_buffer << ")";
	}	
	else if(bool_op == _logical_or){
		file_buffer << "\n" << AST_NODE_SPACE << "Condition:" << " OR\n" << AST_SUB_NODE_SPACE << "LHS (";
		lhs_op->print(file_buffer);

		file_buffer <<  ")\n"<< AST_SUB_NODE_SPACE <<"RHS (";
		rhs_op->print(file_buffer);
		file_buffer << ")";
	}
	else if(bool_op == _logical_not){
		file_buffer << "\n" << AST_NODE_SPACE << "Condition:" << " NOT\n" << AST_SUB_NODE_SPACE << "RHS (";
		rhs_op->print(file_buffer);

		file_buffer << ")";
	}
}

/////////////////////////////////////////////////////////////////

Selection_Statement_Ast::Selection_Statement_Ast(Ast * cond1,Ast* then_part1, Ast* else_part1, int line){
	cond = cond1;
	then_part = then_part1;
	else_part = else_part1;
	lineno = line;
}

Data_Type Selection_Statement_Ast::get_data_type(){
	return node_data_type;
}

void Selection_Statement_Ast::set_data_type(Data_Type dt){
	node_data_type = dt;
	return;
}

bool Selection_Statement_Ast::check_ast(){
	if(else_part!= NULL){
		if(cond->check_ast() && then_part->check_ast() && else_part->check_ast()){
			return true;
		}
	}
	else{
		if(cond->check_ast() && then_part->check_ast()){
			return true;
		}
	}
	return false;
}

void Selection_Statement_Ast::print(ostream & file_buffer){

	file_buffer << "\n" << AST_SPACE << "IF : \n" << AST_SPACE << "CONDITION (";
	cond->print(file_buffer);

	file_buffer <<  ")\n"<< AST_SPACE <<"THEN (";
	then_part->print(file_buffer);

	file_buffer << ")";

	if(else_part != NULL){
		file_buffer << "\n" <<  AST_SPACE <<"ELSE (";
		else_part->print(file_buffer);

		file_buffer << ")";
	}

}

/////////////////////////////////////////////////////////////////

Iteration_Statement_Ast::Iteration_Statement_Ast(Ast * cond1, Ast* body1, int line, bool do_form){
	cond = cond1;
	body = body1;
	is_do_form = do_form;
	lineno = line;
}

Data_Type Iteration_Statement_Ast::get_data_type(){
	return node_data_type;
}

void Iteration_Statement_Ast::set_data_type(Data_Type dt){
	node_data_type = dt;
	return;
}

bool Iteration_Statement_Ast::check_ast(){
	if(cond->check_ast() && body->check_ast()){
		return true;
	}
	return false;
}

void Iteration_Statement_Ast::print(ostream & file_buffer){
	if(is_do_form){
		file_buffer << "\n" << AST_SPACE << "DO (";
		body->print(file_buffer);

		file_buffer <<  ")\n"<< AST_SPACE <<"WHILE CONDITION (";
		cond->print(file_buffer);

		file_buffer << ")";
	}
	else{
		file_buffer << "\n" << AST_SPACE << "WHILE : \n" << AST_SPACE << "CONDITION (";
		cond->print(file_buffer);

		file_buffer <<  ")\n"<< AST_SPACE <<"BODY (";
		body->print(file_buffer);

		file_buffer << ")";
	}
}

/////////////////////////////////////////////////////////////////

Sequence_Ast::Sequence_Ast(int line){
	statement_list = list<Ast*>();
	// sa_icode_list = list<Icode_Stmt *>();
	lineno = line;
	labelCounter++;
}

void Sequence_Ast::ast_push_back(Ast *ast){
	statement_list.push_back(ast);
}

void Sequence_Ast::print(ostream & file_buffer){
	list<Ast*>::iterator it;
	for(it = statement_list.begin();it!=statement_list.end();it++){
		file_buffer  << "\n" << AST_NODE_SPACE;
		(*it)->print(file_buffer);
	}	

}

/////////////////////////////////////////////////////////////////


Conditional_Expression_Ast::Conditional_Expression_Ast(Ast* cond1, Ast* l, Ast* r, int line){
	cond = cond1;
	lhs = l;
	rhs = r;
	lineno = line;
}

void Conditional_Expression_Ast::print(ostream & file_buffer){
	file_buffer << "\n" << AST_SPACE << "Cond:\n" << AST_NODE_SPACE << "IF_ELSE";
	cond->print(file_buffer);

	file_buffer <<  "\n"<< AST_NODE_SPACE <<"LHS (";
	lhs->print(file_buffer);
	file_buffer << ")";

	file_buffer <<  "\n"<< AST_NODE_SPACE <<"RHS (";
	rhs->print(file_buffer);
	file_buffer << ")";
}

