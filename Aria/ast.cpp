#include "ast.h"

void AST::Accept(Visitor *visitor)
{
	std::cerr << "debug::generic ast trying to call visitor" << std::endl;
};

BinaryAST::BinaryAST(std::unique_ptr<AST> LHS, std::unique_ptr<AST> RHS, Token op) : leftOp(std::move(LHS)), rightOp(std::move(RHS)), op(op) {}

void BinaryAST::Accept(Visitor *visitor)
{
	visitor->VisitBinaryAST(this);
}

LiteralAST::LiteralAST(Token value) : value(value) {}

void LiteralAST::Accept(Visitor *visitor)
{
	visitor->VisitLiteralAST(this);
}

VariableAST::VariableAST(Token name) : name(name) {}

void VariableAST::Accept(Visitor *visitor)
{
	visitor->VisitVariableAST(this);
}

AssignmentAST::AssignmentAST(std::unique_ptr<VariableAST> variable, std::unique_ptr<AST> value) : variable(std::move(variable)), value(std::move(value)) {}
void AssignmentAST::Accept(Visitor *visitor)
{
	visitor->VisitAssignmentAST(this);
}
