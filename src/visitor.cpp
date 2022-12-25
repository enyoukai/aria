#include "visitor.hpp"
#define QWORD 8
#define DWORD 4

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

void Visitor::VisitComparisonAST(ComparisonAST *ast)
{
}

void Visitor::VisitWhileAST(WhileAST *ast) {}
void Visitor::VisitBlockAST(BlockAST *ast) {}

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

void PrinterVisitor::VisitComparisonAST(ComparisonAST *ast)
{
	ast->LHS->Accept(this);
	if (ast->comparisonOp.type == Token::GREATER)
		std::cout << " GREATER ";
	else if (ast->comparisonOp.type == Token::LESSER)
		std::cout << " LESSER ";
	else if (ast->comparisonOp.type == Token::EQUALS)
		std::cout << " EQUALS ";
	ast->RHS->Accept(this);
}

void PrinterVisitor::VisitWhileAST(WhileAST *ast)
{
	std::cout << "while (";
	ast->comparison->Accept(this);
	std::cout << ")\n{";
	std::cerr << "\nSize: " << ast->block.size() << std::endl;
	for (int i = 0; i < ast->block.size(); i++)
	{
		ast->block[i]->Accept(this);
	}
	std::cout << "}";
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
		asmIR.MOV("r8", "rdx");
		asmIR.MOV("r9", "rax");
		asmIR.XOR("rdx", "rdx");
		asmIR.MOV("rax", leftRegister);
		asmIR.IDIV(rightRegister);
		// now we reverse
		// really goofy but i feel like this is just a consequence of how poorly i manage my registers
		// pls fix later
		if (leftRegister != "rax")
		{
			asmIR.MOV(leftRegister, "rax");
			asmIR.MOV("rax", "r9");
		}

		asmIR.MOV("rdx", "r8");
		break;
	}

	PopRegisterAlloc();
	// return PopRegisterAlloc();
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
		stackPointer += QWORD;
		variablePointer = stackPointer;
		variableStackMap.insert({ast->variable->name.stringLiteral, variablePointer});
	}

	asmIR.MOV("QWORD [rbp-" + std::to_string(variablePointer) + "]", result);
}

void CodeGenVisitor::VisitVariableAST(VariableAST *ast)
{
	result = "[rbp-" + std::to_string(VariableToPointer(ast->name.stringLiteral)) + "]";
}

void CodeGenVisitor::VisitComparisonAST(ComparisonAST *ast)
{
	// reminder for later to push registers

	ast->LHS->Accept(this);
	std::string LHS = result;
	std::cerr << "RESULT IN: " << result << std::endl;

	PushRegisterAlloc();

	ast->RHS->Accept(this);
	std::string RHS = result;
	std::cerr << "RESULT IN: " << result << std::endl;

	asmIR.CMP("QWORD " + LHS, RHS); // ok all this is really messy

	PopRegisterAlloc();

	if (ast->comparisonOp.type == Token::EQUALS)
	{
		result = "jne";
	}
	else if (ast->comparisonOp.type == Token::LESSER)
	{
		result = "jge";
	}
	else if (ast->comparisonOp.type == Token::GREATER)
	{
		result = "jle";
	}
}

void CodeGenVisitor::VisitWhileAST(WhileAST *ast)
{
	int currentLoop = loopCounter;
	asmIR.AddLabel("L" + std::to_string(currentLoop));
	ast->comparison->Accept(this);

	asmIR.AddInstruction(result, "L" + std::to_string(currentLoop) + "_exit");
	for (int i = 0; i < ast->block.size(); i++)
		ast->block[i]->Accept(this);

	asmIR.JMP("L" + std::to_string(currentLoop));
	asmIR.AddLabel("L" + std::to_string(currentLoop) + "_exit");

	loopCounter++;
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

// this is a bit of a pain to figure out because if intermediate data is stored on the stack
// but then more local variables are created on top
// you can't really pop just only the intermediate data
// TODO: maybe instead have the assembly class keep track of all the variables that are allocated in scope, and then only start intermediate data from there?
// just do something like sub 	rsp, QWORD * localVars and then push on that
// that's really messy though i don't want the code to get mixed up between the visitor
// idk i feel like not being able to template virtuals is making this a lot harder
// well for now it should be fine because intermediate data only exists during binary operations so it's not like variables are gonna be assigned in that time until after or something
std::string CodeGenVisitor::PopRegisterAlloc()
{
	return CodeGenVisitor::storageRegisters[currentRegisterAlloc--];
}