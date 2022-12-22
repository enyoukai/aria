#include "ast.h"

std::string ExprAST::Print() { return "what"; };
void ExprAST::CodeGen(){};
void ExprAST::Accept(Visitor *visitor){};

BinaryAST::BinaryAST(std::unique_ptr<ExprAST> LHS, std::unique_ptr<ExprAST> RHS, Token op) : leftOp(std::move(LHS)), rightOp(std::move(RHS)), op(op) {}
std::string BinaryAST::Print()
{
	std::string TOKEN_MAP[] = {"INT_LITERAl", "STRING_LITERAL", "IDENTIFIER", "PLUS", "MINUS", "STAR", "SLASH", "EQUALS"};
	return "(" + leftOp->Print() + " " + TOKEN_MAP[op.type] + " " + rightOp->Print() + ")";
}
void BinaryAST::Accept(Visitor *visitor) {}

LiteralAST::LiteralAST(Token value) : value(value) {}
std::string LiteralAST::Print()
{
	if (value.type == Token::STRING_LITERAL)
		return value.stringLiteral;
	return std::to_string(value.intLiteral);
}
void LiteralAST::Accept(Visitor *visitor) {}
