#include <iostream>

#include "CodeGen.h"
#include "Parser.h"
#include "Sema.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/raw_ostream.h"

static llvm::cl::opt<std::string>
    Input(llvm::cl::Positional,
          llvm::cl::desc("<input expression>"),
          llvm::cl::init(""));

int main(int argc, const char **argv)
{
    // Init LLVM
    llvm::InitLLVM X(argc, argv);
    llvm::cl::ParseCommandLineOptions(
        argc, argv, "calc - the expression compiler\n");

    Lexer Lex(Input);
    
    // Dump all input tokens
    //Token token;
    //for (Lex.next(token); token.getKind() != Token::TokenKind::eoi; Lex.next(token)) {
    //    std::cout << token.getKind() << ": " << token.getText().str() << "\n";
    //}
    

    #if 1
    // Parse input and build abstract syntax tree
    Parser Parser(Lex);
    AST *Tree = Parser.parse();
    if (!Tree || Parser.hasError()) {
        llvm::errs() << "Syntax errors occured\n";
        return EXIT_FAILURE;
    }

    //
    // Perform symantic analysis:
    // Variable redeclaration: with a, a: 1+2
    // Undefined variable: a,b: 1 + c - d
    //
    Sema Semantic;
    if (Semantic.semantic(Tree)) {
        llvm::errs() << "Semantic errors occured\n";
        return EXIT_FAILURE;
    }

    // Generate LLVM IR code
    CodeGen CodeGenerator;
    CodeGenerator.compile(Tree);
    #endif

    return EXIT_SUCCESS;
}
