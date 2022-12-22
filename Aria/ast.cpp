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
