#pragma once

#include "ast.h"
#include "visitor.h"


class CodeGen
{
public:
	CodeGen(ExprAST expr);
	void Generate();

private:
	ExprAST expr;
};