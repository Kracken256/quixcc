#include <parse/nodes/literal.h>

#include <iostream>
static uint8_t get_numbits(const std::string &s)
{
    if (s.find('.') != std::string::npos)
    {
        float f0 = std::stof(s);
        double f1 = std::stod(s);
        const double delta = 0.0000001;

        return std::abs(f0 - f1) < delta ? 64 : 32;
    }

    uint64_t val = std::stoull(s);
    uint8_t bits = 0;
    while (val)
    {
        val >>= 1;
        bits++;
    }

    if (bits > 32)
        return 64;
    else if (bits > 16)
        return 32;
    else if (bits > 8)
        return 16;
    return 8;
}

std::string libj::IntegerLiteralNode::to_json() const
{
    return "{\"type\":\"number\",\"value\":\"" + m_val + "\"}";
}

llvm::Constant *libj::IntegerLiteralNode::codegen(libj::LLVMContext &ctx) const
{
    return llvm::ConstantInt::get(*ctx.m_ctx, llvm::APInt(get_numbits(m_val), m_val, 10));
}

std::shared_ptr<libj::ParseNode> libj::IntegerLiteralNode::clone() const
{
    return std::make_shared<IntegerLiteralNode>(*this);
}

std::string libj::FloatLiteralNode::to_json() const
{
    return "{\"type\":\"number\",\"value\":\"" + m_val + "\"}";
}

llvm::Constant *libj::FloatLiteralNode::codegen(libj::LLVMContext &ctx) const
{
    if (get_numbits(m_val) > 32)
    {
        return llvm::ConstantFP::get(*ctx.m_ctx, llvm::APFloat(llvm::APFloat::IEEEdouble(), m_val));
    }

    return llvm::ConstantFP::get(*ctx.m_ctx, llvm::APFloat(llvm::APFloat::IEEEsingle(), m_val));
}

std::shared_ptr<libj::ParseNode> libj::FloatLiteralNode::clone() const
{
    return std::make_shared<FloatLiteralNode>(*this);
}

std::string libj::StringLiteralNode::to_json() const
{
    return "{\"type\":\"string\",\"value\":\"" + m_val + "\"}";
}

llvm::Constant *libj::StringLiteralNode::codegen(libj::LLVMContext &ctx) const
{
    auto str = llvm::ConstantDataArray::getString(*ctx.m_ctx, m_val);

    auto global = new llvm::GlobalVariable(*ctx.m_module, str->getType(), true, llvm::GlobalValue::InternalLinkage, str);

    llvm::Constant *zero = llvm::Constant::getNullValue(llvm::IntegerType::getInt32Ty(*ctx.m_ctx));
    llvm::Constant *indices[] = {zero, zero};
    return llvm::ConstantExpr::getGetElementPtr(str->getType(), global, indices, true);
}

std::shared_ptr<libj::ParseNode> libj::StringLiteralNode::clone() const
{
    return std::make_shared<StringLiteralNode>(*this);
}

std::string libj::CharLiteralNode::to_json() const
{
    return "{\"type\":\"char\",\"value\":\"" + m_val + "\"}";
}

llvm::Constant *libj::CharLiteralNode::codegen(libj::LLVMContext &ctx) const
{
    return llvm::ConstantInt::get(*ctx.m_ctx, llvm::APInt(8, m_val[0]));
}

std::shared_ptr<libj::ParseNode> libj::CharLiteralNode::clone() const
{
    return std::make_shared<CharLiteralNode>(*this);
}
