#include "visitor.h"

void Visitor::VisitBinaryAST(BinaryAST *ast)
{
}

void Visitor::VisitLiteralAST(LiteralAST *ast)
{
}

void Visitor::VisitVariableAST(VariableAST *ast)
{
}

void Visitor::VisitAssignmentAST(AssignmentAST *ast)
{
}

PrinterVisitor::PrinterVisitor()
{
}

void PrinterVisitor::VisitBinaryAST(BinaryAST *ast)
{
	std::string TOKEN_MAP[] = {"INT_LITERAl", "STRING_LITERAL", "IDENTIFIER", "PLUS", "MINUS", "STAR", "SLASH", "EQUALS"};

	std::cout << "(";
	ast->leftOp->Accept(this);
	std::cout << ", ";
	std::cout << TOKEN_MAP[ast->op.type];
	std::cout << ", ";
	ast->rightOp->Accept(this);
	std::cout << ")";
}

void PrinterVisitor::VisitLiteralAST(LiteralAST *ast)
{
	if (ast->value.type == Token::INT_LITERAL)
		std::cout << std::to_string(ast->value.intLiteral);
	else if (ast->value.type == Token::STRING_LITERAL)
		std::cout << ast->value.stringLiteral;
	else
		std::cerr << "Error printing out invalid type of enum: " + ast->value.type << '\n';
}

void PrinterVisitor::VisitVariableAST(VariableAST *ast)
{
	std::cout << "Variable(" << ast->name.stringLiteral << ")";
}

void PrinterVisitor::VisitAssignmentAST(AssignmentAST *ast)
{
	ast->variable->Accept(this);
	std::cout << " : ";
	ast->value->Accept(this);
	std::cout << '\n';
}

CodeGenVisitor::CodeGenVisitor()
{
}

void CodeGenVisitor::VisitBinaryAST(BinaryAST *ast)
{
	ast->leftOp->Accept(this);
	// int leftValue = intResult;
	asmIR.MOV("rax", std::to_string(intResult));

	ast->rightOp->Accept(this);
	// int rightValue = intResult;
	asmIR.MOV("rdx", std::to_string(intResult));

	// switch (ast->op.type)
	// {
	// case Token::PLUS:
	// 	intResult = leftValue + rightValue;
	// 	break;
	// case Token::MINUS:
	// 	intResult = leftValue - rightValue;
	// 	break;
	// case Token::STAR:
	// 	intResult = leftValue * rightValue;
	// 	break;
	// case Token::SLASH:
	// 	intResult = leftValue / rightValue;
	// 	break;
	// }

	switch (ast->op.type)
	{
	case Token::PLUS:
		asmIR.ADD("rax", "rdx");
		break;
	case Token::MINUS:
		asmIR.SUB("rax", "rdx");
		break;
	case Token::STAR:
		asmIR.IMUL("rax", "rdx");
		break;
	case Token::SLASH:
		asmIR.IDIV("rax", "rdx");
		break;
	}
}

void CodeGenVisitor::VisitLiteralAST(LiteralAST *ast)
{
	intResult = ast->value.intLiteral;
}

void CodeGenVisitor::VisitAssignmentAST(AssignmentAST *ast)
{
	ast->value->Accept(this);

	int variablePointer = VariableToPointer(ast->variable->name.stringLiteral);
	if (variablePointer == -1)
	{
		stackPointer += 4;
		variablePointer = stackPointer;
		variableStackMap.insert({ast->variable->name.stringLiteral, variablePointer});
	}

	asmIR.MOV("DWORD [rbp-" + std::to_string(variablePointer) + "]", "rax");
}

void CodeGenVisitor::VisitVariableAST(VariableAST *ast)
{
}

void CodeGenVisitor::OutputASM()
{
	std::cout << "-----GENERATING ASSEMBLY-----\n";
	std::cout << asmIR.OutputASM() << '\n';
}

int CodeGenVisitor::VariableToPointer(std::string varName)
{
	if (variableStackMap.find(varName) == variableStackMap.end())
	{
		return -1;
	}
	else
	{
		return variableStackMap.at(varName);
	}
}

std::string CodeGenVisitor::GetRegisterAlloc()
{

}

std::string CodeGenVisitor::PushRegisterAlloc()
{

}

std::string CodeGenVisitor::PopRegisterAlloc()
{
	
}