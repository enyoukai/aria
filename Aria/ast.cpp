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

ComparisonAST::ComparisonAST(std::unique_ptr<AST> LHS, std::unique_ptr<AST> RHS, Token comparisonOp) : LHS(std::move(LHS)), RHS(std::move(RHS)), comparisonOp(comparisonOp) {}
void ComparisonAST::Accept(Visitor *visitor)
{
	visitor->VisitComparisonAST(this);
}

WhileAST::WhileAST(std::unique_ptr<AST> comparison, std::vector<std::unique_ptr<AST>> const &block) : comparison(std::move(comparison)), block(block) {}
void WhileAST::Accept(Visitor *visitor)
{
	visitor->VisitWhileAST(this);
}