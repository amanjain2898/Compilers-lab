
#include<string>
#include<fstream>
#include<iostream>

Code_For_Ast & Assignment_Ast::compile(){
	if(rhs->get_data_type() == int_data_type){
		Ics_Opd *mem_opd = new Mem_Addr_Opd(lhs->get_symbol_entry());
		Code_For_Ast c_ast = rhs->compile();
		Register_Descriptor *reg = c_ast.get_reg();
		Ics_Opd *reg_opd = new Register_Addr_Opd(reg);
		Icode_Stmt *ic_stmt = new Move_IC_Stmt(store,reg_opd,mem_opd);
		list <Icode_Stmt*> ic_list = c_ast.get_icode_list();
		ic_list.push_back(ic_stmt);
		reg->reset_use_for_expr_result();

		return *(new Code_For_Ast(ic_list,reg));
	}
	else if(rhs->get_data_type() == double_data_type){
		Ics_Opd *mem_opd = new Mem_Addr_Opd(lhs->get_symbol_entry());
		Code_For_Ast c_ast = rhs->compile();
		Register_Descriptor *reg = c_ast.get_reg();
		Ics_Opd *reg_opd = new Register_Addr_Opd(reg);
		Icode_Stmt *ic_stmt = new Move_IC_Stmt(store_d,reg_opd,mem_opd);
		list <Icode_Stmt*> ic_list = c_ast.get_icode_list();
		ic_list.push_back(ic_stmt);
		reg->reset_use_for_expr_result();
		return *(new Code_For_Ast(ic_list,reg));
	}
}

Code_For_Ast & Assignment_Ast::compile_and_optimize_ast(Lra_Outcome & lra){

}

//////////////////////////////////////////////////////////////////////////////////

Code_For_Ast & Name_Ast::compile(){
	if(get_data_type()==int_data_type){
		Register_Descriptor *reg = machine_desc_object.get_new_register<int_reg>();
		Ics_Opd *mem_opd = new Mem_Addr_Opd(get_symbol_entry());
		Ics_Opd *reg_opd = new Register_Addr_Opd(reg);
		Icode_Stmt *ic_stmt = new Move_IC_Stmt(load,mem_opd,reg_opd);
		list <Icode_Stmt*> ic_list = list<Icode_Stmt*>();
		ic_list.push_back(ic_stmt);
		return *(new Code_For_Ast(ic_list,reg));
	}
	else if(get_data_type()==double_data_type){
		Register_Descriptor *reg = machine_desc_object.get_new_register<float_reg>();
		Ics_Opd *mem_opd = new Mem_Addr_Opd(get_symbol_entry());
		Ics_Opd *reg_opd = new Register_Addr_Opd(reg);
		Icode_Stmt *ic_stmt = new Move_IC_Stmt(load_d,mem_opd,reg_opd);
		list <Icode_Stmt*> ic_list = list<Icode_Stmt*>();
		ic_list.push_back(ic_stmt);
		return *(new Code_For_Ast(ic_list,reg));
	}
}

Code_For_Ast & Name_Ast::compile_and_optimize_ast(Lra_Outcome & lra){

}

Code_For_Ast & Name_Ast::create_store_stmt(Register_Descriptor * store_register){

}

/////////////////////////////////////////////////////////////////////////////////

template<>
Code_For_Ast & Number_Ast<int>::compile(){
	Register_Descriptor *reg = machine_desc_object.get_new_register<int_reg>();
	Ics_Opd *const_opd = new Const_Opd<int>(constant);
	Ics_Opd *reg_opd = new Register_Addr_Opd(reg);
	Icode_Stmt *ic_stmt = new Move_IC_Stmt(imm_load,const_opd,reg_opd);
	list <Icode_Stmt*> ic_list = list<Icode_Stmt*>();
	ic_list.push_back(ic_stmt);
	return *(new Code_For_Ast(ic_list,reg));
}

template<>
Code_For_Ast & Number_Ast<int>::compile_and_optimize_ast(Lra_Outcome & lra){

}
template<>
Code_For_Ast & Number_Ast<double>::compile(){
	Register_Descriptor *reg = machine_desc_object.get_new_register<float_reg>();
	Ics_Opd *const_opd = new Const_Opd<double>(constant);
	Ics_Opd *reg_opd = new Register_Addr_Opd(reg);
	Icode_Stmt *ic_stmt = new Move_IC_Stmt(imm_load_d,const_opd,reg_opd);
	list <Icode_Stmt*> ic_list = list<Icode_Stmt*>();
	ic_list.push_back(ic_stmt);
	return *(new Code_For_Ast(ic_list,reg));
}	

template<>
Code_For_Ast & Number_Ast<double>::compile_and_optimize_ast(Lra_Outcome & lra){

}

/////////////////////////////////////////////////////////////////////////////////

Code_For_Ast & Plus_Ast::compile(){
	if(get_data_type() == int_data_type){
		Code_For_Ast lc_ast = lhs->compile();
		Register_Descriptor *lhs_reg = lc_ast.get_reg();
		lhs_reg->set_use_for_expr_result();
		Code_For_Ast rc_ast = rhs->compile();
		Register_Descriptor *rhs_reg = rc_ast.get_reg();
		rhs_reg->set_use_for_expr_result();
		Register_Descriptor *reg = machine_desc_object.get_new_register<int_reg>();
		Ics_Opd *result = new Register_Addr_Opd(reg);
		Ics_Opd *opd1 = new Register_Addr_Opd(lhs_reg);
		Ics_Opd *opd2 = new Register_Addr_Opd(rhs_reg);
		Icode_Stmt *ic_stmt = new Compute_IC_Stmt(add,opd1,opd2,result);
		lhs_reg->reset_use_for_expr_result();
		rhs_reg->reset_use_for_expr_result();
		list <Icode_Stmt*> ic_list = lc_ast.get_icode_list();
		list<Icode_Stmt *>::iterator i1;
		for(i1 = rc_ast.get_icode_list().begin();i1!=rc_ast.get_icode_list().end();i1++){
			ic_list.push_back(*i1);
		}
		ic_list.push_back(ic_stmt);
		return *(new Code_For_Ast(ic_list,reg));

	}
	else if(get_data_type() == double_data_type){
		Code_For_Ast lc_ast = lhs->compile();
		Register_Descriptor *lhs_reg = lc_ast.get_reg();
		lhs_reg->set_use_for_expr_result();
		Code_For_Ast rc_ast = rhs->compile();
		Register_Descriptor *rhs_reg = rc_ast.get_reg();
		rhs_reg->set_use_for_expr_result();
		Register_Descriptor *reg = machine_desc_object.get_new_register<float_reg>();
		Ics_Opd *result = new Register_Addr_Opd(reg);
		Ics_Opd *opd1 = new Register_Addr_Opd(lhs_reg);
		Ics_Opd *opd2 = new Register_Addr_Opd(rhs_reg);
		Icode_Stmt *ic_stmt = new Compute_IC_Stmt(add_d,opd1,opd2,result);
		lhs_reg->reset_use_for_expr_result();
		rhs_reg->reset_use_for_expr_result();
		list <Icode_Stmt*> ic_list = lc_ast.get_icode_list();
		list<Icode_Stmt *>::iterator i1;
		for(i1 = rc_ast.get_icode_list().begin();i1!=rc_ast.get_icode_list().end();i1++){
			ic_list.push_back(*i1);
		}
		ic_list.push_back(ic_stmt);
		return *(new Code_For_Ast(ic_list,reg));
	}
}

Code_For_Ast & Plus_Ast::compile_and_optimize_ast(Lra_Outcome & lra){

}

/////////////////////////////////////////////////////////////////////////////////

Code_For_Ast & Minus_Ast::compile(){
	if(get_data_type() == int_data_type){
		Code_For_Ast lc_ast = lhs->compile();
		Register_Descriptor *lhs_reg = lc_ast.get_reg();
		lhs_reg->set_use_for_expr_result();
		Code_For_Ast rc_ast = rhs->compile();
		Register_Descriptor *rhs_reg = rc_ast.get_reg();
		rhs_reg->set_use_for_expr_result();
		Register_Descriptor *reg = machine_desc_object.get_new_register<int_reg>();
		Ics_Opd *result = new Register_Addr_Opd(reg);
		Ics_Opd *opd1 = new Register_Addr_Opd(lhs_reg);
		Ics_Opd *opd2 = new Register_Addr_Opd(rhs_reg);
		Icode_Stmt *ic_stmt = new Compute_IC_Stmt(sub,opd1,opd2,result);
		lhs_reg->reset_use_for_expr_result();
		rhs_reg->reset_use_for_expr_result();
		list <Icode_Stmt*> ic_list = lc_ast.get_icode_list();
		list<Icode_Stmt *>::iterator i1;
		for(i1 = rc_ast.get_icode_list().begin();i1!=rc_ast.get_icode_list().end();i1++){
			ic_list.push_back(*i1);
		}
		ic_list.push_back(ic_stmt);
		return *(new Code_For_Ast(ic_list,reg));

	}
	else if(get_data_type() == double_data_type){
		Code_For_Ast lc_ast = lhs->compile();
		Register_Descriptor *lhs_reg = lc_ast.get_reg();
		lhs_reg->set_use_for_expr_result();
		Code_For_Ast rc_ast = rhs->compile();
		Register_Descriptor *rhs_reg = rc_ast.get_reg();
		rhs_reg->set_use_for_expr_result();
		Register_Descriptor *reg = machine_desc_object.get_new_register<float_reg>();
		Ics_Opd *result = new Register_Addr_Opd(reg);
		Ics_Opd *opd1 = new Register_Addr_Opd(lhs_reg);
		Ics_Opd *opd2 = new Register_Addr_Opd(rhs_reg);
		Icode_Stmt *ic_stmt = new Compute_IC_Stmt(sub_d,opd1,opd2,result);
		lhs_reg->reset_use_for_expr_result();
		rhs_reg->reset_use_for_expr_result();
		list <Icode_Stmt*> ic_list = lc_ast.get_icode_list();
		list<Icode_Stmt *>::iterator i1;
		for(i1 = rc_ast.get_icode_list().begin();i1!=rc_ast.get_icode_list().end();i1++){
			ic_list.push_back(*i1);
		}
		ic_list.push_back(ic_stmt);
		return *(new Code_For_Ast(ic_list,reg));
	}
}

Code_For_Ast & Minus_Ast::compile_and_optimize_ast(Lra_Outcome & lra){

}

/////////////////////////////////////////////////////////////////////////////////

Code_For_Ast & Divide_Ast::compile(){
	if(get_data_type() == int_data_type){
		Code_For_Ast lc_ast = lhs->compile();
		Register_Descriptor *lhs_reg = lc_ast.get_reg();
		lhs_reg->set_use_for_expr_result();
		Code_For_Ast rc_ast = rhs->compile();
		Register_Descriptor *rhs_reg = rc_ast.get_reg();
		rhs_reg->set_use_for_expr_result();
		Register_Descriptor *reg = machine_desc_object.get_new_register<int_reg>();
		Ics_Opd *result = new Register_Addr_Opd(reg);
		Ics_Opd *opd1 = new Register_Addr_Opd(lhs_reg);
		Ics_Opd *opd2 = new Register_Addr_Opd(rhs_reg);
		Icode_Stmt *ic_stmt = new Compute_IC_Stmt(divd,opd1,opd2,result);
		lhs_reg->reset_use_for_expr_result();
		rhs_reg->reset_use_for_expr_result();
		list <Icode_Stmt*> ic_list = lc_ast.get_icode_list();
		list<Icode_Stmt *>::iterator i1;
		for(i1 = rc_ast.get_icode_list().begin();i1!=rc_ast.get_icode_list().end();i1++){
			ic_list.push_back(*i1);
		}
		ic_list.push_back(ic_stmt);
		return *(new Code_For_Ast(ic_list,reg));

	}
	else if(get_data_type() == double_data_type){
		Code_For_Ast lc_ast = lhs->compile();
		Register_Descriptor *lhs_reg = lc_ast.get_reg();
		lhs_reg->set_use_for_expr_result();
		Code_For_Ast rc_ast = rhs->compile();
		Register_Descriptor *rhs_reg = rc_ast.get_reg();
		rhs_reg->set_use_for_expr_result();
		Register_Descriptor *reg = machine_desc_object.get_new_register<float_reg>();
		Ics_Opd *result = new Register_Addr_Opd(reg);
		Ics_Opd *opd1 = new Register_Addr_Opd(lhs_reg);
		Ics_Opd *opd2 = new Register_Addr_Opd(rhs_reg);
		Icode_Stmt *ic_stmt = new Compute_IC_Stmt(div_d,opd1,opd2,result);
		lhs_reg->reset_use_for_expr_result();
		rhs_reg->reset_use_for_expr_result();
		list <Icode_Stmt*> ic_list = lc_ast.get_icode_list();
		list<Icode_Stmt *>::iterator i1;
		for(i1 = rc_ast.get_icode_list().begin();i1!=rc_ast.get_icode_list().end();i1++){
			ic_list.push_back(*i1);
		}
		ic_list.push_back(ic_stmt);
		return *(new Code_For_Ast(ic_list,reg));
	}
}

Code_For_Ast & Divide_Ast::compile_and_optimize_ast(Lra_Outcome & lra){

}

/////////////////////////////////////////////////////////////////////////////////

Code_For_Ast & Mult_Ast::compile(){
	if(get_data_type() == int_data_type){
		Code_For_Ast lc_ast = lhs->compile();
		Register_Descriptor *lhs_reg = lc_ast.get_reg();
		lhs_reg->set_use_for_expr_result();
		Code_For_Ast rc_ast = rhs->compile();
		Register_Descriptor *rhs_reg = rc_ast.get_reg();
		rhs_reg->set_use_for_expr_result();
		Register_Descriptor *reg = machine_desc_object.get_new_register<int_reg>();
		Ics_Opd *result = new Register_Addr_Opd(reg);
		Ics_Opd *opd1 = new Register_Addr_Opd(lhs_reg);
		Ics_Opd *opd2 = new Register_Addr_Opd(rhs_reg);
		Icode_Stmt *ic_stmt = new Compute_IC_Stmt(mult,opd1,opd2,result);
		lhs_reg->reset_use_for_expr_result();
		rhs_reg->reset_use_for_expr_result();
		list <Icode_Stmt*> ic_list = lc_ast.get_icode_list();
		list<Icode_Stmt *>::iterator i1;
		for(i1 = rc_ast.get_icode_list().begin();i1!=rc_ast.get_icode_list().end();i1++){
			ic_list.push_back(*i1);
		}
		ic_list.push_back(ic_stmt);
		return *(new Code_For_Ast(ic_list,reg));

	}
	else if(get_data_type() == double_data_type){
		Code_For_Ast lc_ast = lhs->compile();
		Register_Descriptor *lhs_reg = lc_ast.get_reg();
		lhs_reg->set_use_for_expr_result();
		Code_For_Ast rc_ast = rhs->compile();
		Register_Descriptor *rhs_reg = rc_ast.get_reg();
		rhs_reg->set_use_for_expr_result();
		Register_Descriptor *reg = machine_desc_object.get_new_register<float_reg>();
		Ics_Opd *result = new Register_Addr_Opd(reg);
		Ics_Opd *opd1 = new Register_Addr_Opd(lhs_reg);
		Ics_Opd *opd2 = new Register_Addr_Opd(rhs_reg);
		Icode_Stmt *ic_stmt = new Compute_IC_Stmt(mult_d,opd1,opd2,result);
		lhs_reg->reset_use_for_expr_result();
		rhs_reg->reset_use_for_expr_result();
		list <Icode_Stmt*> ic_list = lc_ast.get_icode_list();
		list<Icode_Stmt *>::iterator i1;
		for(i1 = rc_ast.get_icode_list().begin();i1!=rc_ast.get_icode_list().end();i1++){
			ic_list.push_back(*i1);
		}
		ic_list.push_back(ic_stmt);
		return *(new Code_For_Ast(ic_list,reg));
	}
}

Code_For_Ast & Mult_Ast::compile_and_optimize_ast(Lra_Outcome & lra){

}

/////////////////////////////////////////////////////////////////////////////////

Code_For_Ast & UMinus_Ast::compile(){
	if(lhs->get_data_type() == int_data_type){
		Code_For_Ast c_ast = lhs->compile();
		Register_Descriptor *opd_reg = c_ast.get_reg();
		opd_reg->set_use_for_expr_result();
		Ics_Opd *opd1 = new Register_Addr_Opd(opd_reg);
		Register_Descriptor *reg = machine_desc_object.get_new_register<int_reg>();
		Ics_Opd *result = new Register_Addr_Opd(reg);
		Icode_Stmt *ic_stmt = new Move_IC_Stmt(uminus,opd1,result);
		list <Icode_Stmt*> ic_list = c_ast.get_icode_list();
		ic_list.push_back(ic_stmt);
		opd_reg->reset_use_for_expr_result();
		return *(new Code_For_Ast(ic_list,reg));
	}
	else if(lhs->get_data_type() == double_data_type){
		Code_For_Ast c_ast = lhs->compile();
		Register_Descriptor *opd_reg = c_ast.get_reg();
		opd_reg->set_use_for_expr_result();
		Ics_Opd *opd1 = new Register_Addr_Opd(opd_reg);
		Register_Descriptor *reg = machine_desc_object.get_new_register<float_reg>();
		Ics_Opd *result = new Register_Addr_Opd(reg);
		Icode_Stmt *ic_stmt = new Move_IC_Stmt(uminus_d,opd1,result);
		list <Icode_Stmt*> ic_list = c_ast.get_icode_list();
		ic_list.push_back(ic_stmt);
		opd_reg->reset_use_for_expr_result();
		return *(new Code_For_Ast(ic_list,reg));
	}
}

Code_For_Ast & UMinus_Ast::compile_and_optimize_ast(Lra_Outcome & lra){

}

/////////////////////////////////////////////////////////////////////////////////

Code_For_Ast & Conditional_Expression_Ast::compile(){
	if(cond->get_data_type()==int_data_type){
		Code_For_Ast cond_ast = cond->compile();
		list<Icode_Stmt*> ics_list = cond_ast.get_icode_list();
		string label1 = get_new_label();
		Register_Descriptor *cond_reg = cond_ast.get_reg();
		cond_reg->set_use_for_expr_result();
		Ics_Opd *opd0 = new Register_Addr_Opd(cond_reg);

		Icode_Stmt *ic_stmt = new Control_Flow_IC_Stmt(beq,opd0,NULL,label1,0);

		ics_list.push_back(ic_stmt);

		Code_For_Ast l_ast = lhs->compile();

		Register_Descriptor *l_reg = l_ast.get_reg();
		l_reg->set_use_for_expr_result();

		Code_For_Ast r_ast = rhs->compile();

		Register_Descriptor *r_reg = r_ast.get_reg();
		r_reg->set_use_for_expr_result();


		Register_Descriptor *reg;
		if(lhs->get_data_type() == int_data_type){
			reg = machine_desc_object.get_new_register<int_reg>();
		}
		else if(lhs->get_data_type() == double_data_type){
			reg = machine_desc_object.get_new_register<float_reg>();
		}
		reg->set_use_for_expr_result();

		Ics_Opd *opd1 = new Register_Addr_Opd(l_reg);
		Ics_Opd *opd2 = new Register_Addr_Opd(machine_desc_object.spim_register_table[zero]);
		Ics_Opd *result1 = new Register_Addr_Opd(reg);

		Icode_Stmt *ic_stmt1 = new Compute_IC_Stmt(or_t,opd1,opd2,result1);

		string label2 = get_new_label();
			
		list<Icode_Stmt *>::iterator i1;
		for(i1 = l_ast.get_icode_list().begin();i1!=l_ast.get_icode_list().end();i1++){
			ics_list.push_back(*i1);
		}

		ics_list.push_back(ic_stmt1);
		Icode_Stmt *ic_stmt2 = new Label_IC_Stmt(j,label2);
		ics_list.push_back(ic_stmt2);
		Icode_Stmt *ic_stmt3 = new Label_IC_Stmt(label,label1);
		ics_list.push_back(ic_stmt3);

		for(i1 = r_ast.get_icode_list().begin();i1!=r_ast.get_icode_list().end();i1++){
			ics_list.push_back(*i1);
		}
		
		Ics_Opd *opd3 = new Register_Addr_Opd(r_reg);
		Ics_Opd *result2 = new Register_Addr_Opd(reg);

		Icode_Stmt *ic_stmt4 = new Compute_IC_Stmt(or_t	,opd3,opd2,result2);

		ics_list.push_back(ic_stmt4);


		Icode_Stmt *ic_stmt5 = new Label_IC_Stmt(label,label2);
		ics_list.push_back(ic_stmt5);

		l_reg->reset_use_for_expr_result();
		r_reg->reset_use_for_expr_result();
		cond_reg->reset_use_for_expr_result();
		reg->reset_use_for_expr_result();

		return *(new Code_For_Ast(ics_list,reg));
	}
	else if(cond->get_data_type()==double_data_type){

		Code_For_Ast cond_ast = cond->compile();

		Register_Descriptor* reg2 = machine_desc_object.get_new_register<int_reg>();
		reg2->set_use_for_expr_result();

		list<Icode_Stmt*> ics_list = cond_ast.get_icode_list();
		string label1 = get_new_label();

		list<Icode_Stmt *>::iterator i4 = --cond_ast.get_icode_list().end();
		Icode_Stmt *ic_stmt;
		if((*i4)->get_op().get_op() == sle_d || (*i4)->get_op().get_op() == slt_d || (*i4)->get_op().get_op() == seq_d)
			ic_stmt = new Label_IC_Stmt(bc1f,label1);
		else
			ic_stmt = new Label_IC_Stmt(bc1t,label1);

		ics_list.push_back(ic_stmt);

		Code_For_Ast l_ast = lhs->compile();

		Register_Descriptor *l_reg = l_ast.get_reg();
		l_reg->set_use_for_expr_result();

		Code_For_Ast r_ast = rhs->compile();

		Register_Descriptor *r_reg = r_ast.get_reg();
		r_reg->set_use_for_expr_result();


		Register_Descriptor *reg;
		if(lhs->get_data_type() == int_data_type){
			reg = machine_desc_object.get_new_register<int_reg>();
		}
		else if(lhs->get_data_type() == double_data_type){
			reg = machine_desc_object.get_new_register<float_reg>();
		}
		reg->set_use_for_expr_result();

		Ics_Opd *opd1 = new Register_Addr_Opd(l_reg);
		Ics_Opd *opd2 = new Register_Addr_Opd(machine_desc_object.spim_register_table[zero]);
		Ics_Opd *result1 = new Register_Addr_Opd(reg);

		Icode_Stmt *ic_stmt1 = new Compute_IC_Stmt(or_t,opd1,opd2,result1);

		string label2 = get_new_label();
			
		list<Icode_Stmt *>::iterator i1;
		for(i1 = l_ast.get_icode_list().begin();i1!=l_ast.get_icode_list().end();i1++){
			ics_list.push_back(*i1);
		}

		ics_list.push_back(ic_stmt1);
		Icode_Stmt *ic_stmt2 = new Label_IC_Stmt(j,label2);
		ics_list.push_back(ic_stmt2);
		Icode_Stmt *ic_stmt3 = new Label_IC_Stmt(label,label1);
		ics_list.push_back(ic_stmt3);

		for(i1 = r_ast.get_icode_list().begin();i1!=r_ast.get_icode_list().end();i1++){
			ics_list.push_back(*i1);
		}
		
		Ics_Opd *opd3 = new Register_Addr_Opd(r_reg);
		Ics_Opd *result2 = new Register_Addr_Opd(reg);

		Icode_Stmt *ic_stmt4 = new Compute_IC_Stmt(or_t	,opd3,opd2,result2);

		ics_list.push_back(ic_stmt4);


		Icode_Stmt *ic_stmt5 = new Label_IC_Stmt(label,label2);
		ics_list.push_back(ic_stmt5);

		l_reg->reset_use_for_expr_result();
		r_reg->reset_use_for_expr_result();
		reg->reset_use_for_expr_result();

		return *(new Code_For_Ast(ics_list,reg));
	}
}

/////////////////////////////////////////////////////////////////////////////////

Code_For_Ast & Relational_Expr_Ast::compile(){
	if(lhs_condition->get_data_type()==int_data_type){
		Code_For_Ast lc_ast = lhs_condition->compile();
		Register_Descriptor *lhs_reg = lc_ast.get_reg();
		lhs_reg->set_use_for_expr_result();
		Code_For_Ast rc_ast = rhs_condition->compile();
		Register_Descriptor *rhs_reg = rc_ast.get_reg();
		rhs_reg->set_use_for_expr_result();
		Register_Descriptor *reg = machine_desc_object.get_new_register<int_reg>();
		Ics_Opd *result = new Register_Addr_Opd(reg);
		Ics_Opd *opd1 = new Register_Addr_Opd(lhs_reg);
		Ics_Opd *opd2 = new Register_Addr_Opd(rhs_reg);
		Icode_Stmt *ic_stmt;
		if(rel_op == equalto){
			ic_stmt = new Compute_IC_Stmt(seq,opd1,opd2,result);
		}
		else if(rel_op == not_equalto){
			ic_stmt = new Compute_IC_Stmt(sne,opd1,opd2,result);
		}
		else if(rel_op == greater_equalto){
			ic_stmt = new Compute_IC_Stmt(sge,opd1,opd2,result);
		}
		else if(rel_op == greater_than){
			ic_stmt = new Compute_IC_Stmt(sgt,opd1,opd2,result);
		}
		else if(rel_op == less_than){
			ic_stmt = new Compute_IC_Stmt(slt,opd1,opd2,result);
		}
		else if(rel_op == less_equalto){
			ic_stmt = new Compute_IC_Stmt(sle,opd1,opd2,result);
		}
		lhs_reg->reset_use_for_expr_result();
		rhs_reg->reset_use_for_expr_result();
		list <Icode_Stmt*> ic_list = lc_ast.get_icode_list();
		list<Icode_Stmt *>::iterator i1;
		for(i1 = rc_ast.get_icode_list().begin();i1!=rc_ast.get_icode_list().end();i1++){
			ic_list.push_back(*i1);
		}
		ic_list.push_back(ic_stmt);
		return *(new Code_For_Ast(ic_list,reg));
	}
	else if(lhs_condition->get_data_type()==double_data_type){
		Code_For_Ast lc_ast = lhs_condition->compile();
		Register_Descriptor *lhs_reg = lc_ast.get_reg();
		lhs_reg->set_use_for_expr_result();
		Code_For_Ast rc_ast = rhs_condition->compile();
		Register_Descriptor *rhs_reg = rc_ast.get_reg();
		rhs_reg->set_use_for_expr_result();
		Ics_Opd *opd1 = new Register_Addr_Opd(lhs_reg);
		Ics_Opd *opd2 = new Register_Addr_Opd(rhs_reg);
		Icode_Stmt *ic_stmt;
		if(rel_op == equalto){
			ic_stmt = new Move_IC_Stmt(seq_d,opd2,opd1);
		}
		else if(rel_op == not_equalto){
			ic_stmt = new Move_IC_Stmt(sne_d,opd2,opd1);
		}
		else if(rel_op == greater_equalto){
			ic_stmt = new Move_IC_Stmt(sge_d,opd2,opd1);
		}
		else if(rel_op == greater_than){
			ic_stmt = new Move_IC_Stmt(sgt_d,opd2,opd1);
		}
		else if(rel_op == less_than){
			ic_stmt = new Move_IC_Stmt(slt_d,opd2,opd1);
		}
		else if(rel_op == less_equalto){
			ic_stmt = new Move_IC_Stmt(sle_d,opd2,opd1);
		}
		lhs_reg->reset_use_for_expr_result();
		rhs_reg->reset_use_for_expr_result();
		list <Icode_Stmt*> ic_list = lc_ast.get_icode_list();
		list<Icode_Stmt *>::iterator i1;
		for(i1 = rc_ast.get_icode_list().begin();i1!=rc_ast.get_icode_list().end();i1++){
			ic_list.push_back(*i1);
		}
		ic_list.push_back(ic_stmt);
		return *(new Code_For_Ast(ic_list,NULL));	
	}
}

/////////////////////////////////////////////////////////////////////////////////

Code_For_Ast & Logical_Expr_Ast::compile(){
	if(rhs_op->get_data_type()==double_data_type){
		exit(0);
	}
	if(lhs_op!=NULL){
		if(lhs_op->get_data_type()==double_data_type){
			exit(0);
		}
	}
	Code_For_Ast lc_ast;
	Register_Descriptor *lhs_reg;
	Ics_Opd *opd1;
	if(lhs_op != NULL){
		lc_ast = lhs_op->compile();
		lhs_reg = lc_ast.get_reg();
		lhs_reg->set_use_for_expr_result();
		opd1 = new Register_Addr_Opd(lhs_reg);
	}
	else{
		lhs_reg = machine_desc_object.get_new_register<int_reg>();
		lhs_reg->set_use_for_expr_result();
		opd1 = new Register_Addr_Opd(lhs_reg);
	}
	Code_For_Ast rc_ast = rhs_op->compile();
	Register_Descriptor *rhs_reg = rc_ast.get_reg();
	rhs_reg->set_use_for_expr_result();
	Register_Descriptor *reg = machine_desc_object.get_new_register<int_reg>();
	Ics_Opd *result = new Register_Addr_Opd(reg);
	Ics_Opd *opd2 = new Register_Addr_Opd(rhs_reg);
	Icode_Stmt *ic_stmt;
	if(bool_op == _logical_not){
		ic_stmt = new Compute_IC_Stmt(not_t,opd2,opd1,result);
	}
	else if(bool_op == _logical_and){
		ic_stmt = new Compute_IC_Stmt(and_t,opd1,opd2,result);
	}
	else if(bool_op == _logical_or){
		ic_stmt = new Compute_IC_Stmt(or_t,opd1,opd2,result);
	}
	list <Icode_Stmt*> ic_list;
	if(lhs_op != NULL){
		ic_list = lc_ast.get_icode_list();
	}
	else{
		Ics_Opd *const_opd = new Const_Opd<int>(1);
		Ics_Opd *reg_opd = new Register_Addr_Opd(lhs_reg);
		Icode_Stmt *ic_stmt1 = new Move_IC_Stmt(imm_load,const_opd,reg_opd);
		ic_list.push_back(ic_stmt1);
	}
	list<Icode_Stmt *>::iterator i1;
	for(i1 = rc_ast.get_icode_list().begin();i1!=rc_ast.get_icode_list().end();i1++){
		ic_list.push_back(*i1);
	}
	ic_list.push_back(ic_stmt);
	lhs_reg->reset_use_for_expr_result();
	rhs_reg->reset_use_for_expr_result();
	return *(new Code_For_Ast(ic_list,reg));
}

/////////////////////////////////////////////////////////////////////////////////

Code_For_Ast & Selection_Statement_Ast::compile(){
	if(cond->get_data_type()==int_data_type){
		Code_For_Ast cond_ast = cond->compile();
		Register_Descriptor *cond_reg = cond_ast.get_reg();
		cond_reg->set_use_for_expr_result();

		Code_For_Ast then_ast = then_part->compile();

		Ics_Opd *opd1 = new Register_Addr_Opd(cond_reg);
		string label1 = get_new_label();
		Icode_Stmt *ic_stmt = new Control_Flow_IC_Stmt(beq,opd1,NULL,label1,0);

		list<Icode_Stmt*> ics_list = cond_ast.get_icode_list();
		ics_list.push_back(ic_stmt);
		list<Icode_Stmt *>::iterator i1;
		for(i1 = then_ast.get_icode_list().begin();i1!=then_ast.get_icode_list().end();i1++){
			ics_list.push_back(*i1);
		}
		if(else_part != NULL){	
			string label2 = get_new_label();
			Icode_Stmt *ic_stmt1 = new Label_IC_Stmt(j,label2);
			ics_list.push_back(ic_stmt1);
			Icode_Stmt *ic_stmt2 = new Label_IC_Stmt(label,label1);
			ics_list.push_back(ic_stmt2);
			Code_For_Ast else_ast;
			else_ast = else_part->compile();
			list<Icode_Stmt *>::iterator i1;
			for(i1 = else_ast.get_icode_list().begin();i1!=else_ast.get_icode_list().end();i1++){
				ics_list.push_back(*i1);
			}
			Icode_Stmt *ic_stmt3 = new Label_IC_Stmt(label,label2);
			ics_list.push_back(ic_stmt3);
		}
		else{
			Icode_Stmt *ic_stmt2 = new Label_IC_Stmt(label,label1);
			ics_list.push_back(ic_stmt2);
		}
		cond_reg->reset_use_for_expr_result();
		return *(new Code_For_Ast(ics_list,NULL));
	}
	else if(cond->get_data_type()==double_data_type){
		Code_For_Ast cond_ast = cond->compile();

		Register_Descriptor* reg2 = machine_desc_object.get_new_register<int_reg>();
		reg2->set_use_for_expr_result();


		string label1 = get_new_label();
		list<Icode_Stmt *>::iterator i4 = --cond_ast.get_icode_list().end();

		Icode_Stmt *ic_stmt;
		if((*i4)->get_op().get_op() == sle_d || (*i4)->get_op().get_op() == slt_d || (*i4)->get_op().get_op() == seq_d)
			ic_stmt = new Label_IC_Stmt(bc1f,label1);
		else
			ic_stmt = new Label_IC_Stmt(bc1t,label1);
		Code_For_Ast then_ast = then_part->compile();

		list<Icode_Stmt*> ics_list = cond_ast.get_icode_list();
		ics_list.push_back(ic_stmt);
		list<Icode_Stmt *>::iterator i1;
		for(i1 = then_ast.get_icode_list().begin();i1!=then_ast.get_icode_list().end();i1++){
			ics_list.push_back(*i1);
		}
		if(else_part != NULL){	
			string label2 = get_new_label();
			Icode_Stmt *ic_stmt1 = new Label_IC_Stmt(j,label2);
			ics_list.push_back(ic_stmt1);
			Icode_Stmt *ic_stmt2 = new Label_IC_Stmt(label,label1);
			ics_list.push_back(ic_stmt2);
			Code_For_Ast else_ast;
			else_ast = else_part->compile();
			list<Icode_Stmt *>::iterator i1;
			for(i1 = else_ast.get_icode_list().begin();i1!=else_ast.get_icode_list().end();i1++){
				ics_list.push_back(*i1);
			}
			Icode_Stmt *ic_stmt3 = new Label_IC_Stmt(label,label2);
			ics_list.push_back(ic_stmt3);
		}
		else{
			Icode_Stmt *ic_stmt2 = new Label_IC_Stmt(label,label1);
			ics_list.push_back(ic_stmt2);
		}
		return *(new Code_For_Ast(ics_list,NULL));
	}
}

/////////////////////////////////////////////////////////////////////////////////

Code_For_Ast & Iteration_Statement_Ast::compile(){
	if(cond->get_data_type() == int_data_type){
		string label1 = get_new_label();
		string label2 = get_new_label();
		list<Icode_Stmt*> ics_list;

		if(!is_do_form){
			ics_list.push_back(new Label_IC_Stmt(j,label2));
		}
		ics_list.push_back(new Label_IC_Stmt(label,label1));

		Code_For_Ast cond_ast = cond->compile();
		Register_Descriptor *cond_reg = cond_ast.get_reg();
		cond_reg->set_use_for_expr_result();

		Code_For_Ast body_ast = body->compile();
		list<Icode_Stmt *>::iterator i1;
		for(i1 = body_ast.get_icode_list().begin();i1!=body_ast.get_icode_list().end();i1++){
			ics_list.push_back(*i1);
		}
		ics_list.push_back(new Label_IC_Stmt(label,label2));
		
		for(i1 = cond_ast.get_icode_list().begin();i1!=cond_ast.get_icode_list().end();i1++){
			ics_list.push_back(*i1);
		}	

		Ics_Opd *opd1 = new Register_Addr_Opd(cond_reg);
		Icode_Stmt *ic_stmt = new Control_Flow_IC_Stmt(bne,opd1,NULL,label1,0);

		ics_list.push_back(ic_stmt);
		cond_reg->reset_use_for_expr_result();

		return *(new Code_For_Ast(ics_list,NULL));
	}
	else if(cond->get_data_type() == double_data_type){
		string label1 = get_new_label();
		string label2 = get_new_label();
		list<Icode_Stmt*> ics_list;

		if(!is_do_form){
			ics_list.push_back(new Label_IC_Stmt(j,label2));
		}
		ics_list.push_back(new Label_IC_Stmt(label,label1));

		Code_For_Ast cond_ast = cond->compile();

		Register_Descriptor* reg2 = machine_desc_object.get_new_register<int_reg>();
		reg2->set_use_for_expr_result();
		
		Code_For_Ast body_ast = body->compile();
		list<Icode_Stmt *>::iterator i1;
		for(i1 = body_ast.get_icode_list().begin();i1!=body_ast.get_icode_list().end();i1++){
			ics_list.push_back(*i1);
		}
		ics_list.push_back(new Label_IC_Stmt(label,label2));
		
		for(i1 = cond_ast.get_icode_list().begin();i1!=cond_ast.get_icode_list().end();i1++){
			ics_list.push_back(*i1);
		}	

		list<Icode_Stmt *>::iterator i4 = --cond_ast.get_icode_list().end();

		Icode_Stmt *ic_stmt;
		if((*i4)->get_op().get_op() == sle_d || (*i4)->get_op().get_op() == slt_d || (*i4)->get_op().get_op() == seq_d)
			ic_stmt = new Label_IC_Stmt(bc1t,label1);
		else
			ic_stmt = new Label_IC_Stmt(bc1f,label1);

		ics_list.push_back(ic_stmt);

		return *(new Code_For_Ast(ics_list,NULL));
	}
}

/////////////////////////////////////////////////////////////////////////////////

Code_For_Ast & Sequence_Ast::compile(){
	list<Ast *>::iterator i1;
	for(i1 = statement_list.begin();i1!=statement_list.end();i1++){
		Code_For_Ast c1 = (*i1)->compile();

		list<Icode_Stmt *>::iterator i2;
		for(i2 = c1.get_icode_list().begin();i2!=c1.get_icode_list().end();i2++){
			sa_icode_list.push_back(*i2);
		}
	}
	return *(new Code_For_Ast(sa_icode_list,NULL));
}

void Sequence_Ast::print_icode(ostream & file_buffer){
	list<Icode_Stmt *>::iterator i2;
	for(i2 = sa_icode_list.begin();i2!=sa_icode_list.end();i2++){
		(*i2)->print_icode(file_buffer);
	}
}

void Sequence_Ast::print_assembly(ostream & file_buffer){
	list<Icode_Stmt *>::iterator i2;
	for(i2 = sa_icode_list.begin();i2!=sa_icode_list.end();i2++){
		(*i2)->print_assembly(file_buffer);
	}
}

//////////////////////////////////////////////////////////////////////////////

Code_For_Ast & Print_Ast::compile(){
	if(var->get_data_type() == int_data_type){
		Register_Descriptor *reg = machine_desc_object.spim_register_table[v0];
		Ics_Opd *const_opd = new Const_Opd<int>(1);
		Ics_Opd *reg_opd = new Register_Addr_Opd(reg);
		Icode_Stmt *ic_stmt = new Move_IC_Stmt(imm_load,const_opd,reg_opd);
		list <Icode_Stmt*> ic_list;
		ic_list.push_back(ic_stmt);

		Register_Descriptor *reg1 = machine_desc_object.spim_register_table[a0];
		Ics_Opd *mem_opd = new Mem_Addr_Opd(var->get_symbol_entry());
		Ics_Opd *reg_opd1 = new Register_Addr_Opd(reg1);
		Icode_Stmt *ic_stmt1 = new Move_IC_Stmt(load,mem_opd,reg_opd1);
		ic_list.push_back(ic_stmt1);

		Icode_Stmt *ic_stmt2 = new Print_IC_Stmt();
		ic_list.push_back(ic_stmt2);

		return *(new Code_For_Ast(ic_list,NULL));
	} 
	else{
		Register_Descriptor *reg = machine_desc_object.spim_register_table[v0];
		Ics_Opd *const_opd = new Const_Opd<int>(3);
		Ics_Opd *reg_opd = new Register_Addr_Opd(reg);
		Icode_Stmt *ic_stmt = new Move_IC_Stmt(imm_load,const_opd,reg_opd);
		list <Icode_Stmt*> ic_list = list<Icode_Stmt*>();
		ic_list.push_back(ic_stmt);

		Register_Descriptor *reg1 = machine_desc_object.spim_register_table[f12];
		Ics_Opd *mem_opd = new Mem_Addr_Opd(var->get_symbol_entry());
		Ics_Opd *reg_opd1 = new Register_Addr_Opd(reg1);
		Icode_Stmt *ic_stmt1 = new Move_IC_Stmt(load_d,mem_opd,reg_opd1);
		ic_list.push_back(ic_stmt1);

		Icode_Stmt *ic_stmt2 = new Print_IC_Stmt();
		ic_list.push_back(ic_stmt2);

		return *(new Code_For_Ast(ic_list,NULL));
	}

}



/////////////////////////////////////////////////////////////////////////////////

Code_For_Ast & Return_Ast::compile(){
	list <Icode_Stmt*> ic_list = list<Icode_Stmt*>();
	if(return_value != NULL){
		Code_For_Ast c1 = return_value->compile();
		Register_Descriptor *reg1 = c1.get_reg();
		list<Icode_Stmt *>::iterator i2;
		for(i2 = c1.get_icode_list().begin();i2!=c1.get_icode_list().end();i2++){
			ic_list.push_back(*i2);
		}
		if(return_value->get_data_type() == int_data_type){
			Ics_Opd *mem_opd = new Register_Addr_Opd(machine_desc_object.spim_register_table[v1]);
			Ics_Opd *reg_opd = new Register_Addr_Opd(reg1);
			Icode_Stmt *ic_stmt = new Move_IC_Stmt(mov,reg_opd,mem_opd);
			reg1->reset_use_for_expr_result();
			ic_list.push_back(ic_stmt);
		}
		else if(return_value->get_data_type() == double_data_type){
			Ics_Opd *mem_opd = new Register_Addr_Opd(machine_desc_object.spim_register_table[f0]);
			Ics_Opd *reg_opd = new Register_Addr_Opd(reg1);
			Icode_Stmt *ic_stmt = new Move_IC_Stmt(move_d,reg_opd,mem_opd);
			reg1->reset_use_for_expr_result();
			ic_list.push_back(ic_stmt);
		}
	}
	Icode_Stmt *ic_stmt = new Label_IC_Stmt(ret_inst,proc_name);
	ic_list.push_back(ic_stmt);
	return *(new Code_For_Ast(ic_list,NULL));
}

Code_For_Ast & Return_Ast::compile_and_optimize_ast(Lra_Outcome & lra){

}

/////////////////////////////////////////////////////////////////////////////////

Code_For_Ast & Call_Ast::compile(){
	list <Icode_Stmt*> ic_list = list<Icode_Stmt*>();
	list<Ast*>::iterator i1;
	Procedure *p1 = program_object.get_procedure_prototype(procedure_name);
	Symbol_Table s1 = p1->get_formal_param_list();
	list<Symbol_Table_Entry *>l1 = s1.get_table();
	list<Symbol_Table_Entry *>::iterator i3 = --l1.end();

	if(l1.size() != actual_param_list.size()){
		fprintf(stderr,"cs316: Error Number of arguments do not match\n");
		exit(0);
	}
	

	int offset = 0;
	for(i1=--actual_param_list.end();i1 != --actual_param_list.begin();i1--){

		// printf("%s\n",(*i3)->get_variable_name().c_str());
		if((*i3)->get_data_type() != (*i1)->get_data_type()){
			fprintf(stderr,"cs316: Error arguments type do not match\n");		
		}
		string name = (*i3)->get_variable_name();
		Symbol_Table_Entry* ss = new Symbol_Table_Entry(name,(*i3)->get_data_type(),(*i3)->get_lineno(),sp_ref);
		ss->set_start_offset(offset);
		ss->set_symbol_scope(formal);
		if((*i3)->get_data_type() == int_data_type) offset -= 4;
		if((*i3)->get_data_type() == double_data_type) offset -= 8;
		Code_For_Ast c1 = (*i1)->compile();
		Register_Descriptor *reg1 = c1.get_reg();
		list<Icode_Stmt *>::iterator i2;
		for(i2 = c1.get_icode_list().begin();i2!=c1.get_icode_list().end();i2++){
			ic_list.push_back(*i2);
		}
		if((*i1)->get_data_type() == int_data_type){
			Ics_Opd *mem_opd = new Mem_Addr_Opd(*ss);
			Ics_Opd *reg_opd = new Register_Addr_Opd(reg1);
			Icode_Stmt *ic_stmt = new Move_IC_Stmt(store,reg_opd,mem_opd);
			reg1->reset_use_for_expr_result();
			ic_list.push_back(ic_stmt);
		}
		else if((*i1)->get_data_type() == double_data_type){
			// printf("here\n");
			Ics_Opd *mem_opd = new Mem_Addr_Opd(*ss);
			Ics_Opd *reg_opd = new Register_Addr_Opd(reg1);
			Icode_Stmt *ic_stmt = new Move_IC_Stmt(store_d,reg_opd,mem_opd);
			reg1->reset_use_for_expr_result();
			ic_list.push_back(ic_stmt);
		}
		i3--;
	}

	if(offset!=0){
		Ics_Opd *result = new Register_Addr_Opd(machine_desc_object.spim_register_table[sp]);
		Ics_Opd *opd1 = new Register_Addr_Opd(machine_desc_object.spim_register_table[sp]);
		Ics_Opd *opd2 = new Const_Opd<int>(-offset);
		Icode_Stmt *ic_stmt11 = new Compute_IC_Stmt(sub,opd1,opd2,result);
		ic_list.push_back(ic_stmt11);
	}

	Icode_Stmt *ic_stmt = new Label_IC_Stmt(jal,procedure_name);
	ic_list.push_back(ic_stmt);
	
	if(offset!=0){
		Ics_Opd *result = new Register_Addr_Opd(machine_desc_object.spim_register_table[sp]);
		Ics_Opd *opd1 = new Register_Addr_Opd(machine_desc_object.spim_register_table[sp]);
		Ics_Opd *opd2 = new Const_Opd<int>(-offset);
		Icode_Stmt *ic_stmt11 = new Compute_IC_Stmt(add,opd1,opd2,result);
		ic_list.push_back(ic_stmt11);
	}
	
	Register_Descriptor* reg2;
	if(node_data_type == int_data_type){
		return_value_reg = machine_desc_object.spim_register_table[v1];
		reg2 = machine_desc_object.get_new_register<int_reg>();
		Ics_Opd *reg_opd = new Register_Addr_Opd(return_value_reg);
		Ics_Opd *mem_opd = new Register_Addr_Opd(reg2);
		Icode_Stmt *ic_stmt = new Move_IC_Stmt(mov,reg_opd,mem_opd);
		reg2->reset_use_for_expr_result();
		ic_list.push_back(ic_stmt);
	}
	else if(node_data_type == double_data_type){
		return_value_reg = machine_desc_object.spim_register_table[f0];
		reg2 = machine_desc_object.get_new_register<float_reg>();
		Ics_Opd *reg_opd = new Register_Addr_Opd(return_value_reg);
		Ics_Opd *mem_opd = new Register_Addr_Opd(reg2);
		Icode_Stmt *ic_stmt = new Move_IC_Stmt(move_d,reg_opd,mem_opd);
		reg2->reset_use_for_expr_result();
		ic_list.push_back(ic_stmt);
	}

	return *(new Code_For_Ast(ic_list,reg2));
}

Code_For_Ast & Call_Ast::compile_and_optimize_ast(Lra_Outcome & lra){

}


