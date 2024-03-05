#include <parse/nodes/function.h>

std::string libjcc::FunctionDeclNode::to_json() const
{
    std::string ret = "{";
    ret += "\"name\": \"" + m_name + "\",";
    ret += "\"params\": [";
    for (size_t i = 0; i < m_params.size(); i++)
    {
        ret += "{";
        ret += "\"name\": \"" + m_params[i].name + "\",";
        ret += "\"type\": " + m_params[i].type->to_json() + ",";
        ret += "\"value\": " + m_params[i].value->to_json();
        ret += "}";
        if (i < m_params.size() - 1)
            ret += ",";
    }
    ret += "],";
    ret += "\"return_type\": " + m_return_type->to_json() + ",";
    ret += "\"variadic\": " + std::to_string(m_variadic) + ",";
    ret += "\"pure\": " + std::to_string(m_pure) + ",";
    ret += "\"thread_safe\": " + std::to_string(m_thread_safe) + ",";
    ret += "\"foreign\": " + std::to_string(m_foreign) + ",";
    ret += "\"nothrow\": " + std::to_string(m_nothrow);
    ret += "}";
    return ret;
}

llvm::Function *libjcc::FunctionDeclNode::codegen(LLVMContext &ctx) const
{
    std::vector<llvm::Type *> params;
    for (const auto &param : m_params)
    {
        params.push_back(param.type->codegen(ctx));
    }
    llvm::FunctionType *ftype = llvm::FunctionType::get(m_return_type->codegen(ctx), params, m_variadic);
    llvm::Function *func;

    if (ctx.m_pub)
        func = llvm::Function::Create(ftype, llvm::Function::ExternalLinkage, m_name, ctx.m_module.get());
    else
        func = llvm::Function::Create(ftype, llvm::Function::PrivateLinkage, m_name, ctx.m_module.get());

    size_t i = 0;
    for (auto &arg : func->args())
    {
        arg.setName(m_params[i].name);
        i++;
    }
    return func;
}

std::shared_ptr<libjcc::ParseNode> libjcc::FunctionDeclNode::clone() const
{
    return std::make_shared<FunctionDeclNode>(*this);
}

std::string libjcc::FunctionDefNode::to_json() const
{
    std::string ret = "{";
    ret += "\"decl\": " + m_decl->to_json() + ",";
    ret += "\"body\": " + m_body->to_json();
    ret += "}";
    return ret;
}

llvm::Value *libjcc::FunctionDefNode::codegen(LLVMContext &ctx) const
{
    llvm::Function *func = m_decl->codegen(ctx);
    llvm::BasicBlock *bb = llvm::BasicBlock::Create(*ctx.m_ctx, "entry", func);
    ctx.m_builder->SetInsertPoint(bb);
    m_body->codegen(ctx);

    if (func->getReturnType()->isVoidTy())
        ctx.m_builder->CreateRetVoid();

    return func;
}

std::shared_ptr<libjcc::ParseNode> libjcc::FunctionDefNode::clone() const
{
    return std::make_shared<FunctionDefNode>(*this);
}