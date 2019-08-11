
#include<string>
#include<fstream>
#include<iostream>

using namespace std;

Eval_Result & Plus_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	if(lhs->get_data_type()==int_data_type){
		Eval_Result *res = new Eval_Result_Value_Int();
		Eval_Result *eval_res_left = new Eval_Result_Value_Int();
		Eval_Result *eval_res_right = new Eval_Result_Value_Int();

		eval_res_left = &lhs->evaluate(eval_env,file_buffer);
		eval_res_right = &rhs->evaluate(eval_env,file_buffer);
		int val = eval_res_left->get_int_value() + eval_res_right->get_int_value();
		res->set_value(val);
		return *res;
	}
	else if(lhs->get_data_type()==double_data_type){
		Eval_Result *res = new Eval_Result_Value_Double();
		Eval_Result *eval_res_left = new Eval_Result_Value_Double();
		Eval_Result *eval_res_right = new Eval_Result_Value_Double();

		eval_res_left = &lhs->evaluate(eval_env,file_buffer);
		eval_res_right = &rhs->evaluate(eval_env,file_buffer);
		double val = eval_res_left->get_double_value() + eval_res_right->get_double_value();
		res->set_value(val);
		return *res;
	}
}

Eval_Result & Minus_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	if(lhs->get_data_type()==int_data_type){
		Eval_Result *res = new Eval_Result_Value_Int();
		Eval_Result *eval_res_left = new Eval_Result_Value_Int();
		Eval_Result *eval_res_right = new Eval_Result_Value_Int();

		eval_res_left = &lhs->evaluate(eval_env,file_buffer);
		eval_res_right = &rhs->evaluate(eval_env,file_buffer);
		int val = eval_res_left->get_int_value() - eval_res_right->get_int_value();
		res->set_value(val);
		return *res;
	}
	else if(lhs->get_data_type()==double_data_type){
		Eval_Result *res = new Eval_Result_Value_Double();
		Eval_Result *eval_res_left = new Eval_Result_Value_Double();
		Eval_Result *eval_res_right = new Eval_Result_Value_Double();

		eval_res_left = &lhs->evaluate(eval_env,file_buffer);
		eval_res_right = &rhs->evaluate(eval_env,file_buffer);
		double val = eval_res_left->get_double_value() - eval_res_right->get_double_value();
		res->set_value(val);
		return *res;
	}
}

Eval_Result & Mult_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	if(lhs->get_data_type()==int_data_type){
		Eval_Result *res = new Eval_Result_Value_Int();
		Eval_Result *eval_res_left = new Eval_Result_Value_Int();
		Eval_Result *eval_res_right = new Eval_Result_Value_Int();

		eval_res_left = &lhs->evaluate(eval_env,file_buffer);
		eval_res_right = &rhs->evaluate(eval_env,file_buffer);
		int val = eval_res_left->get_int_value() * eval_res_right->get_int_value();
		res->set_value(val);
		return *res;
	}
	else if(lhs->get_data_type()==double_data_type){
		Eval_Result *res = new Eval_Result_Value_Double();
		Eval_Result *eval_res_left = new Eval_Result_Value_Double();
		Eval_Result *eval_res_right = new Eval_Result_Value_Double();

		eval_res_left = &lhs->evaluate(eval_env,file_buffer);
		eval_res_right = &rhs->evaluate(eval_env,file_buffer);
		double val = eval_res_left->get_double_value() * eval_res_right->get_double_value();
		res->set_value(val);
		return *res;
	}
}

Eval_Result & Divide_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	if(lhs->get_data_type()==int_data_type){
		Eval_Result *res = new Eval_Result_Value_Int();
		Eval_Result *eval_res_left = new Eval_Result_Value_Int();
		Eval_Result *eval_res_right = new Eval_Result_Value_Int();

		eval_res_left = &lhs->evaluate(eval_env,file_buffer);
		eval_res_right = &rhs->evaluate(eval_env,file_buffer);
		if(eval_res_right->get_int_value() == 0){
			fprintf(stderr,"cs316: Error Cannot divide by 0\n");
			exit(0);
			// return *(new Eval_Result_Value_Int());
		}
		int val = eval_res_left->get_int_value() / eval_res_right->get_int_value();
		res->set_value(val);
		return *res;
	}
	else if(lhs->get_data_type()==double_data_type){
		Eval_Result *res = new Eval_Result_Value_Double();
		Eval_Result *eval_res_left = new Eval_Result_Value_Double();
		Eval_Result *eval_res_right = new Eval_Result_Value_Double();

		eval_res_left = &lhs->evaluate(eval_env,file_buffer);
		eval_res_right = &rhs->evaluate(eval_env,file_buffer);

		if(eval_res_right->get_double_value() == 0){
			fprintf(stderr,"cs316: Error Cannot divide by 0\n");
			exit(0);
			// return *(new Eval_Result_Value_Double());
		}

		double val = eval_res_left->get_double_value() / eval_res_right->get_double_value();

		res->set_value(val);
		return *res;
	}
}


Eval_Result & UMinus_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	if(lhs->get_data_type()==int_data_type){
		Eval_Result *res = new Eval_Result_Value_Int();
		Eval_Result *eval_res_left = new Eval_Result_Value_Int();

		eval_res_left = &lhs->evaluate(eval_env,file_buffer);
		int val = (-1)*(eval_res_left->get_int_value());
		res->set_value(val);
		return *res;
	}
	else if(lhs->get_data_type()==double_data_type){
		Eval_Result *res = new Eval_Result_Value_Double();
		Eval_Result *eval_res_left = new Eval_Result_Value_Double();

		eval_res_left = &lhs->evaluate(eval_env,file_buffer);
		double val = (-1.0)*(eval_res_left->get_double_value());
		res->set_value(val);
		return *res;
	}
}


Eval_Result & Relational_Expr_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	if(lhs_condition->get_data_type()==int_data_type){
		Eval_Result *res = new Eval_Result_Value_Int();
		Eval_Result *lhs_val = new Eval_Result_Value_Int();
		Eval_Result *rhs_val = new Eval_Result_Value_Int();

		lhs_val = &lhs_condition->evaluate(eval_env,file_buffer);
		rhs_val = &rhs_condition->evaluate(eval_env,file_buffer);

		int eval_res_left = lhs_val->get_int_value();
		int eval_res_right = rhs_val->get_int_value();

		if(rel_op == greater_than){
			if(eval_res_left > eval_res_right){
				res->set_value(1);
				return *res;
			}
			else{
				res->set_value(0);
				return *res;
			}
		}
		if(rel_op == greater_equalto){
			if(eval_res_left >= eval_res_right){
				res->set_value(1);
				return *res;
			}
			else{
				res->set_value(0);
				return *res;
			}
		}
		if(rel_op == less_than){
			if(eval_res_left < eval_res_right){

				res->set_value(1);
				return *res;
			}
			else{
				res->set_value(0);
				return *res;
			}
		}
		if(rel_op == less_equalto){
			if(eval_res_left <= eval_res_right){
				res->set_value(1);
				return *res;
			}
			else{
				res->set_value(0);
				return *res;
			}
		}
		if(rel_op == equalto){
			if(eval_res_left == eval_res_right){
				res->set_value(1);
				return *res;
			}
			else{
				res->set_value(0);
				return *res;
			}
		}
		if(rel_op == not_equalto){
			if(eval_res_left != eval_res_right){
				res->set_value(1);
				return *res;
			}
			else{
				res->set_value(0);
				return *res;
			}
		}
	}
	else if(lhs_condition->get_data_type()==double_data_type){
		Eval_Result *res = new Eval_Result_Value_Int();
		Eval_Result *lhs_val = new Eval_Result_Value_Double();
		Eval_Result *rhs_val = new Eval_Result_Value_Double();

		lhs_val = &lhs_condition->evaluate(eval_env,file_buffer);
		rhs_val = &rhs_condition->evaluate(eval_env,file_buffer);

		double eval_res_left = lhs_val->get_double_value();
		double eval_res_right = rhs_val->get_double_value();

		if(rel_op == greater_than){
			if(eval_res_left > eval_res_right){
				res->set_value(1);
				return *res;
			}
			else{
				res->set_value(0);
				return *res;
			}
		}
		if(rel_op == greater_equalto){
			if(eval_res_left >= eval_res_right){
				res->set_value(1);
				return *res;
			}
			else{
				res->set_value(0);
				return *res;
			}
		}
		if(rel_op == less_than){
			if(eval_res_left < eval_res_right){

				res->set_value(1);
				return *res;
			}
			else{
				res->set_value(0);
				return *res;
			}
		}
		if(rel_op == less_equalto){
			if(eval_res_left <= eval_res_right){
				res->set_value(1);
				return *res;
			}
			else{
				res->set_value(0);
				return *res;
			}
		}
		if(rel_op == equalto){
			if(eval_res_left == eval_res_right){
				res->set_value(1);
				return *res;
			}
			else{
				res->set_value(0);
				return *res;
			}
		}
		if(rel_op == not_equalto){
			if(eval_res_left != eval_res_right){
				res->set_value(1);
				return *res;
			}
			else{
				res->set_value(0);
				return *res;
			}
		}
	}
}

Eval_Result & Logical_Expr_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	Eval_Result *res = new Eval_Result_Value_Int();
	Eval_Result *eval_res_left = new Eval_Result_Value_Int();
	Eval_Result *eval_res_right = new Eval_Result_Value_Int();

	if(bool_op==_logical_and){
		eval_res_left = &lhs_op->evaluate(eval_env,file_buffer);
		eval_res_right = &rhs_op->evaluate(eval_env,file_buffer);
		int val;
		if(eval_res_left->get_int_value()==1 && eval_res_right->get_int_value()==1){
			val = 1;
		}
		else{
			val = 0;
		}
		res->set_value(val);
	}
	if(bool_op==_logical_or){
		eval_res_left = &lhs_op->evaluate(eval_env,file_buffer);
		eval_res_right = &rhs_op->evaluate(eval_env,file_buffer);
		int val;
		if(eval_res_left->get_int_value()==1 || eval_res_right->get_int_value()==1){
			val = 1;
		}
		else{
			val = 0;
		}
		res->set_value(val);
	}
	if(bool_op==_logical_not){
		eval_res_right = &rhs_op->evaluate(eval_env,file_buffer);
		int val;
		if(eval_res_right->get_int_value()==1){
			val = 0;
		}
		else{
			val = 1;
		}
		res->set_value(val);
	}
	return *res;
}

Eval_Result & Selection_Statement_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	if(cond->evaluate(eval_env,file_buffer).get_int_value() == 1){
		return then_part->evaluate(eval_env,file_buffer);
	}
	else{
		if(else_part!=NULL){
			return else_part->evaluate(eval_env,file_buffer);
		}
		return *(new Eval_Result_Value_Int());
	}
}	


Eval_Result & Iteration_Statement_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	if(is_do_form){
		do{
			body->evaluate(eval_env,file_buffer);
		}
		while(cond->evaluate(eval_env,file_buffer).get_int_value() == 1);
	}
	else{
		while(cond->evaluate(eval_env,file_buffer).get_int_value() == 1){
			body->evaluate(eval_env,file_buffer);
		}
	}
	// if(cond->evaluate(eval_env,file_buffer).get_int_value() == 1){
	// 	return body->evaluate(eval_env,file_buffer);
	// }
	// else if(cond->evaluate(eval_env,file_buffer).get_int_value() == 0){
	Eval_Result *res = new Eval_Result_Value_Int();
	res->set_value(1);
	return *res;
	// }
}

Eval_Result & Sequence_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	list<Ast *>::iterator i1;
	for(i1 = statement_list.begin();i1!=statement_list.end();i1++){
		(*i1)->evaluate(eval_env,file_buffer);
	}
	return *(new Eval_Result_Value_Int());
}


template <>
Eval_Result & Number_Ast<int>::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	Eval_Result *res = new Eval_Result_Value_Int();
	res->set_value(constant);
	return *res;
}

template <>
Eval_Result & Number_Ast<double>::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	Eval_Result *res = new Eval_Result_Value_Double();
	res->set_value(constant);
	return *res;
}


Eval_Result & Name_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	if(eval_env.does_variable_exist(variable_symbol_entry->get_variable_name())){
		if(eval_env.is_variable_defined(variable_symbol_entry->get_variable_name())){
			Eval_Result* res = eval_env.get_variable_value(variable_symbol_entry->get_variable_name());
			return *res;
		}
		else{
			fprintf(stderr, "cs316: Error variable needs to be defined\n" );
			return *(new Eval_Result_Value_Int());
		}
	}
	else if(interpreter_global_table.is_variable_defined(variable_symbol_entry->get_variable_name())){
		Eval_Result* res = interpreter_global_table.get_variable_value(variable_symbol_entry->get_variable_name());
		return *res;
	}
	else{
		fprintf(stderr, "cs316: Error variable needs to be defined\n" );
		return *(new Eval_Result_Value_Int());
	}
}


Eval_Result & Name_Ast::get_value_of_evaluation(Local_Environment & eval_env){
	if(eval_env.does_variable_exist(variable_symbol_entry->get_variable_name())){
		if(eval_env.is_variable_defined(variable_symbol_entry->get_variable_name())){
			Eval_Result* res = eval_env.get_variable_value(variable_symbol_entry->get_variable_name());
			return *res;
		}
		else{
			fprintf(stderr, "cs316: Error variable needs to be defined\n" );
			return *(new Eval_Result_Value_Int());
		}
	}
	else if(interpreter_global_table.is_variable_defined(variable_symbol_entry->get_variable_name())){
		Eval_Result* res = interpreter_global_table.get_variable_value(variable_symbol_entry->get_variable_name());
		return *res;
	}
	else{
		fprintf(stderr, "cs316: Error variable needs to be defined\n" );
		return *(new Eval_Result_Value_Int());
	}	
}

void Name_Ast::set_value_of_evaluation(Local_Environment & eval_env, Eval_Result & result){
	if(eval_env.does_variable_exist(variable_symbol_entry->get_variable_name())){
		string name = variable_symbol_entry->get_variable_name();
		eval_env.put_variable_value(result,name);
	}
	else if(interpreter_global_table.does_variable_exist(variable_symbol_entry->get_variable_name())){
		string name = variable_symbol_entry->get_variable_name();
		interpreter_global_table.put_variable_value(result,name);
	} 
	else{
		fprintf(stderr, "cs316: Error variable needs to be declared\n" );
	}
}

void Name_Ast::print_value(Local_Environment & eval_env, ostream & file_buffer){
	if(node_data_type == int_data_type){
		if(eval_env.does_variable_exist(variable_symbol_entry->get_variable_name())){
			Eval_Result *eval = eval_env.get_variable_value(variable_symbol_entry->get_variable_name());
			int value = eval->get_int_value();
			file_buffer << "\n" << AST_SPACE << variable_symbol_entry->get_variable_name() << " : " << value << "\n\n";
		}
		else{
			Eval_Result *eval = interpreter_global_table.get_variable_value(variable_symbol_entry->get_variable_name());
			int value = eval->get_int_value();
			file_buffer << "\n" << AST_SPACE << variable_symbol_entry->get_variable_name() << " : " << value << "\n\n";
		}
	}
	else if(node_data_type == double_data_type){
		if(eval_env.does_variable_exist(variable_symbol_entry->get_variable_name())){
			Eval_Result *eval = eval_env.get_variable_value(variable_symbol_entry->get_variable_name());
			double value = eval->get_double_value();
			file_buffer << "\n" << AST_SPACE << variable_symbol_entry->get_variable_name() << " : " << value << "\n\n";
		}
		else{
			Eval_Result *eval = interpreter_global_table.get_variable_value(variable_symbol_entry->get_variable_name());
			double value = eval->get_double_value();
			file_buffer << "\n" << AST_SPACE << variable_symbol_entry->get_variable_name() << " : " << value << "\n\n";
		}
	}
}


Eval_Result & Assignment_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	Data_Type dt = rhs->get_data_type();
	if(dt==int_data_type){
		Eval_Result *rhs_eval = new Eval_Result_Value_Int();
		rhs_eval = &(rhs->evaluate(eval_env,file_buffer));
		rhs_eval->set_variable_status(true);
		rhs_eval->set_result_enum(int_result);
		if(eval_env.does_variable_exist(lhs->get_symbol_entry().get_variable_name())){
			eval_env.put_variable_value(*rhs_eval,lhs->get_symbol_entry().get_variable_name());
			print(file_buffer);
			lhs->print_value(eval_env,file_buffer);
		}
		else if(interpreter_global_table.does_variable_exist(lhs->get_symbol_entry().get_variable_name())){
			interpreter_global_table.put_variable_value(*rhs_eval,lhs->get_symbol_entry().get_variable_name());
			print(file_buffer);
			lhs->print_value(interpreter_global_table,file_buffer);
		}
		else{
			fprintf(stderr, "cs316: Error variable needs to be declared\n" );
		}
		return *rhs_eval;
	}
	else if(dt==double_data_type){
		Eval_Result *rhs_eval = new Eval_Result_Value_Double();
		rhs_eval = &(rhs->evaluate(eval_env,file_buffer));
		rhs_eval->set_variable_status(true);
		rhs_eval->set_result_enum(double_result);
		if(eval_env.does_variable_exist(lhs->get_symbol_entry().get_variable_name())){
			eval_env.put_variable_value(*rhs_eval,lhs->get_symbol_entry().get_variable_name());
			print(file_buffer);
			lhs->print_value(eval_env,file_buffer);
		}
		else if(interpreter_global_table.does_variable_exist(lhs->get_symbol_entry().get_variable_name())){
			interpreter_global_table.put_variable_value(*rhs_eval,lhs->get_symbol_entry().get_variable_name());
			print(file_buffer);
			lhs->print_value(interpreter_global_table,file_buffer);
		}
		else{
			fprintf(stderr, "cs316: Error variable needs to be declared\n" );
		}
		return *rhs_eval;
	}

}


Eval_Result & Conditional_Expression_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	if(cond->evaluate(eval_env,file_buffer).get_int_value() == 1){
		return lhs->evaluate(eval_env,file_buffer);
	}
	else{
		return rhs->evaluate(eval_env,file_buffer);
	}	
}