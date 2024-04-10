#include "llvm/Pass.h"
#include "llvm/Support/Casting.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/IRBuilder.h"

using namespace llvm;

namespace {

struct SkeletonPass : public PassInfoMixin<SkeletonPass> {
    PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM) {
        for (auto &F : M) {
            for (auto& B: F) {
                for (auto& I: B) {
                    if (auto* instr = dyn_cast<BinaryOperator>(&I)) {
                        // Insert at the point where the instr appears(before)
                        IRBuilder<> builder(instr);

                        // Make operands as the same as instr
                        Value* lhs = instr->getOperand(0);
                        Value* rhs = instr->getOperand(1);
                        Value* mul = builder.CreateMul(lhs, rhs);

                        // replace old uses of instr with mul
                        for (auto& use: instr->uses()) {
                            auto* user = use.getUser();
                            user->setOperand(use.getOperandNo(), mul);
                        }

                        // we modified the code
                        return PreservedAnalyses::none();
                    }
                }
            }
        }
        return PreservedAnalyses::all();
    };
};

}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
    return {
        .APIVersion = LLVM_PLUGIN_API_VERSION,
        .PluginName = "Skeleton pass",
        .PluginVersion = "v0.1",
        .RegisterPassBuilderCallbacks = [](PassBuilder &PB) {
            PB.registerPipelineStartEPCallback(
                [](ModulePassManager &MPM, OptimizationLevel Level) {
                    MPM.addPass(SkeletonPass());
                });
        }
    };
}