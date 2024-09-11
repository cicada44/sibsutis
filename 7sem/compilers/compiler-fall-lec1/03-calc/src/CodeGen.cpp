#include "CodeGen.h"
#include "llvm/ADT/StringMap.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/raw_ostream.h"

//using namespace llvm;

namespace {
class ToIRVisitor : public ASTVisitor {
  llvm::Module *M;
  llvm::IRBuilder<> Builder;
  llvm::Type *VoidTy;
  llvm::Type *Int32Ty;
  llvm::PointerType *PtrTy;
  llvm::Constant *Int32Zero;

  llvm::Value *V;
  llvm::StringMap<llvm::Value *> nameMap;

public:
  ToIRVisitor(llvm::Module *M) : M(M), Builder(M->getContext()) {
    VoidTy = llvm::Type::getVoidTy(M->getContext());
    Int32Ty = llvm::Type::getInt32Ty(M->getContext());
    PtrTy = llvm::PointerType::getUnqual(M->getContext());
    Int32Zero = llvm::ConstantInt::get(Int32Ty, 0, true);
  }

  void run(AST *Tree) {
    // Generate main function()
    llvm::FunctionType *MainFty = llvm::FunctionType::get(
        Int32Ty, {Int32Ty, PtrTy}, false);
    llvm::Function *MainFn = llvm::Function::Create(
        MainFty, llvm::GlobalValue::ExternalLinkage, "main", M);
    llvm::BasicBlock *BB = llvm::BasicBlock::Create(M->getContext(),
                                        "entry", MainFn);
    Builder.SetInsertPoint(BB);

    Tree->accept(*this);

    llvm::FunctionType *CalcWriteFnTy =
        llvm::FunctionType::get(VoidTy, {Int32Ty}, false);
    llvm::Function *CalcWriteFn = llvm::Function::Create(
        CalcWriteFnTy, llvm::GlobalValue::ExternalLinkage,
        "calc_write", M);
    // Generate call to runt-time library: calc_write(int v)
    Builder.CreateCall(CalcWriteFnTy, CalcWriteFn, {V});

    Builder.CreateRet(Int32Zero);
  }

  virtual void visit(Factor &Node) override {
    if (Node.getKind() == Factor::Ident) {
      V = nameMap[Node.getVal()];
    } else {
      int intval;
      Node.getVal().getAsInteger(10, intval);
      V = llvm::ConstantInt::get(Int32Ty, intval, true);
    }
  };

  virtual void visit(BinaryOp &Node) override {
    Node.getLeft()->accept(*this);
    llvm::Value *Left = V;
    Node.getRight()->accept(*this);
    llvm::Value *Right = V;
    switch (Node.getOperator()) {
    case BinaryOp::Plus:
      V = Builder.CreateNSWAdd(Left, Right);
      break;
    case BinaryOp::Minus:
      V = Builder.CreateNSWSub(Left, Right);
      break;
    case BinaryOp::Mul:
      V = Builder.CreateNSWMul(Left, Right);
      break;
    case BinaryOp::Div:
      V = Builder.CreateSDiv(Left, Right);
      break;
    }
  };

  virtual void visit(WithDecl &Node) override {
    llvm::FunctionType *ReadFty =
        llvm::FunctionType::get(Int32Ty, {PtrTy}, false);
    llvm::Function *ReadFn = llvm::Function::Create(
        ReadFty, llvm::GlobalValue::ExternalLinkage, "calc_read",
        M);
    for (auto I = Node.begin(), E = Node.end(); I != E;
         ++I) {
      llvm::StringRef Var = *I;

      // Create call to calc_read function.
      llvm::Constant *StrText = llvm::ConstantDataArray::getString(
          M->getContext(), Var);
      llvm::GlobalVariable *Str = new llvm::GlobalVariable(
          *M, StrText->getType(),
          /*isConstant=*/true, llvm::GlobalValue::PrivateLinkage,
          StrText, llvm::Twine(Var).concat(".str"));
      llvm::CallInst *Call =
          Builder.CreateCall(ReadFty, ReadFn, {Str});

      nameMap[Var] = Call;
    }

    Node.getExpr()->accept(*this);
  };
};
} // namespace

void CodeGen::compile(AST *Tree) {
  llvm::LLVMContext Ctx;
  llvm::Module *M = new llvm::Module("calc.expr", Ctx);
  ToIRVisitor ToIR(M);
  ToIR.run(Tree);
  M->print(llvm::outs(), nullptr);
}
