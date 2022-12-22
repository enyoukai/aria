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
}

CodeGenVisitor::CodeGenVisitor()
{
	// gonan be using gcc to link everything for now
	asmOutput = "global main\n"
				"section .text\n"
				"main:\n"
				"\tpush rbp\n"
				"\tmov rbp, rsp\n"
				"\tleave\n"
				"\tret\n";
}

void CodeGenVisitor::VisitBinaryAST(BinaryAST *ast)
{
}

void CodeGenVisitor::VisitLiteralAST(LiteralAST *ast)
{
	asmOutput += std::to_string(ast->value.intLiteral);
}

void CodeGenVisitor::VisitAssignmentAST(AssignmentAST *ast)
{
	asmOutput += "\tmov DWORD [";
	ast->variable->Accept(this);
	asmOutput += "],";
	ast->value->Accept(this);
}

void CodeGenVisitor::VisitVariableAST(VariableAST *ast)
{
	asmOutput += std::to_string(stackPointer);
}

void CodeGenVisitor::OutputASM()
{
	std::cout << asmOutput << '\n';
}