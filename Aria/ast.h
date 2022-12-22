#pragma once

#include "token.h"
#include <iostream>
#include <string>
#include <memory>
#include "visitor.h"

class Visitor;

class AST
{
public:
	virtual void Accept(Visitor *);
};

class BinaryAST : public AST
{
public:
	BinaryAST(std::unique_ptr<AST> LHS, std::unique_ptr<AST> RHS, Token op);
	void Accept(Visitor *) override;

	std::unique_ptr<AST> leftOp, rightOp;
	Token op;

private:
};

class LiteralAST : public AST
{
public:
	LiteralAST(Token value);
	void Accept(Visitor *) override;

	Token value;

private:
};