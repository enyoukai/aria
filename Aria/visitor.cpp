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
	std::string leftValue = result;
	std::string leftRegister = PushRegisterAlloc();

	asmIR.MOV(leftRegister, result);

	ast->rightOp->Accept(this);
	std::string rightValue = result;
	std::string rightRegister = PushRegisterAlloc();

	asmIR.MOV(rightRegister, result);

	switch (ast->op.type)
	{
	case Token::PLUS:
		asmIR.ADD(leftRegister, rightRegister);
		break;
	case Token::MINUS:
		asmIR.SUB(leftRegister, rightRegister);
		break;
	case Token::STAR:
		asmIR.IMUL(leftRegister, rightRegister);
		break;
	case Token::SLASH:
		asmIR.IDIV(leftRegister, rightRegister);
		break;
	}

	PopRegisterAlloc();
	result = CurrentRegisterAlloc();
	PopRegisterAlloc();
}

void CodeGenVisitor::VisitLiteralAST(LiteralAST *ast)
{
	result = std::to_string(ast->value.intLiteral);
}

void CodeGenVisitor::VisitAssignmentAST(AssignmentAST *ast)
{
	ast->value->Accept(this);

	int variablePointer = VariableToPointer(ast->variable->name.stringLiteral);
	if (variablePointer == -1)
	{
		stackPointer += 8;
		variablePointer = stackPointer;
		variableStackMap.insert({ast->variable->name.stringLiteral, variablePointer});
	}

	asmIR.MOV("QWORD [rbp-" + std::to_string(variablePointer) + "]", "rax");
}

void CodeGenVisitor::VisitVariableAST(VariableAST *ast)
{
	result = "[rbp-" + std::to_string(VariableToPointer(ast->name.stringLiteral)) + "]";
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

std::string CodeGenVisitor::CurrentRegisterAlloc()
{
	return CodeGenVisitor::storageRegisters[currentRegisterAlloc];
}

std::string CodeGenVisitor::PushRegisterAlloc()
{
	return CodeGenVisitor::storageRegisters[++currentRegisterAlloc];
}

std::string CodeGenVisitor::PopRegisterAlloc()
{
	return CodeGenVisitor::storageRegisters[currentRegisterAlloc--];
}