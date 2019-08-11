
template class Number_Ast<double>;
template class Number_Ast<int>;



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
	file_buffer << "(" << "Name : " << variable_symbol_entry->get_variable_name() << ")";
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
	file_buffer << "(" << "Num : " << constant << ")";
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
	file_buffer << "(" << "Num : " << constant << ")";
}

template<>
bool Number_Ast<double>::is_value_zero(){
	if(constant == 0){
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

	if(lhs->is_value_zero() && !rhs->is_value_zero()){
		printf("a\n");
		node_data_type = rhs->get_data_type();
	}
	else if(!lhs->is_value_zero() && rhs->is_value_zero()){
		printf("aa\n");
		node_data_type = lhs->get_data_type();
	}

	else if(lhs->is_value_zero() && rhs->is_value_zero()){
		printf("aaa\n");
		node_data_type = lhs->get_data_type();
	}

	else if(lhs->get_data_type() != rhs->get_data_type()){
		fprintf(stderr,"cs316: Error \n");
		return 0;
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
	file_buffer << "(\n" << AST_NODE_SPACE << "Arith: PLUS\n" << AST_SUB_NODE_SPACE << "LHS ";
	lhs->print(file_buffer); 
	file_buffer << "\n"<<AST_SUB_NODE_SPACE<<"RHS ";
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
	file_buffer << "(\n" << AST_NODE_SPACE << "Arith: MINUS\n" << AST_SUB_NODE_SPACE << "LHS ";
	lhs->print(file_buffer); 
	file_buffer << "\n"<<AST_SUB_NODE_SPACE<<"RHS ";
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
	file_buffer << "(\n" << AST_NODE_SPACE << "Arith: DIV\n" << AST_SUB_NODE_SPACE << "LHS ";
	lhs->print(file_buffer); 
	file_buffer << "\n"<<AST_SUB_NODE_SPACE<<"RHS ";
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
	file_buffer << "(\n" << AST_NODE_SPACE << "Arith: MULT\n" << AST_SUB_NODE_SPACE << "LHS ";
	lhs->print(file_buffer); 
	file_buffer << "\n"<<AST_SUB_NODE_SPACE<<"RHS ";
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
	file_buffer << "(\n" << AST_NODE_SPACE << "Arith: UMINUS\n" << AST_SUB_NODE_SPACE << "LHS ";
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

	if(rhs->is_value_zero()){
		return 1;
	}

	if(lhs->get_data_type() != rhs->get_data_type()){
		fprintf(stderr,"cs316: Error \n");
		return 0;
	}
	return 1;
}

void Assignment_Ast::print(ostream & file_buffer){
	file_buffer << "\n" << AST_SPACE << "Asgn:\n" << AST_NODE_SPACE << "LHS ";
	lhs->print(file_buffer);
	file_buffer <<  "\n"<< AST_NODE_SPACE <<"RHS ";
	rhs->print(file_buffer);
}
////////////////////////////////////////////////////////////////


Return_Ast::Return_Ast(int line){

}

Return_Ast::~Return_Ast(){
	
}

void Return_Ast::print(ostream & file_buffer){
	
}

