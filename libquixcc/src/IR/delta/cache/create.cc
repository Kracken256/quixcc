////////////////////////////////////////////////////////////////////////////////////
///                                                                              ///
///    ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░ ░▒▓██████▓▒░    ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░   ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░          ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓██████▓▒░░▒▓█▓▒░      ░▒▓█▓▒░          ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░          ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░   ///
///    ░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░ ░▒▓██████▓▒░    ///
///      ░▒▓█▓▒░                                                                 ///
///       ░▒▓██▓▒░                                                               ///
///                                                                              ///
///     * QUIX LANG COMPILER - The official compiler for the Quix language.      ///
///     * Copyright (C) 2024 Wesley C. Jones                                     ///
///                                                                              ///
///     The QUIX Compiler Suite is free software; you can redistribute it and/or ///
///     modify it under the terms of the GNU Lesser General Public               ///
///     License as published by the Free Software Foundation; either             ///
///     version 2.1 of the License, or (at your option) any later version.       ///
///                                                                              ///
///     The QUIX Compiler Suite is distributed in the hope that it will be       ///
///     useful, but WITHOUT ANY WARRANTY; without even the implied warranty of   ///
///     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU        ///
///     Lesser General Public License for more details.                          ///
///                                                                              ///
///     You should have received a copy of the GNU Lesser General Public         ///
///     License along with the QUIX Compiler Suite; if not, see                  ///
///     <https://www.gnu.org/licenses/>.                                         ///
///                                                                              ///
////////////////////////////////////////////////////////////////////////////////////

#include <IR/delta/DeltaIR.h>

#include <IR/delta/nodes/Type.h>
#include <IR/delta/nodes/Variable.h>
#include <IR/delta/nodes/Memory.h>
#include <IR/delta/nodes/Cast.h>
#include <IR/delta/nodes/Control.h>
#include <IR/delta/nodes/Segment.h>
#include <IR/delta/nodes/Math.h>

#include <map>

using namespace libquixcc;
using namespace libquixcc::ir;
using namespace libquixcc::ir::delta;

static RootNode *root = nullptr;
static std::map<std::pair<const Value<Delta> *, const Value<Delta> *>, const SCast *> scast_insts;
static std::map<std::pair<const Value<Delta> *, const Value<Delta> *>, const UCast *> ucast_insts;
static std::map<std::pair<const Value<Delta> *, const Value<Delta> *>, const PtrICast *> ptricast_insts;
static std::map<std::pair<const Value<Delta> *, const Value<Delta> *>, const IPtrCast *> iptrcast_insts;
static std::map<std::pair<const Value<Delta> *, const Value<Delta> *>, const Bitcast *> bitcast_insts;
static std::map<std::tuple<const Value<Delta> *, const Value<Delta> *, const Value<Delta> *>, IfElse *> ifelse_insts;
static std::map<std::pair<const Value<Delta> *, const Value<Delta> *>, const While *> while_insts;
static std::map<std::string, const Jmp *> jmp_insts;
static std::map<std::string, const Label *> label_insts;
static std::map<const Value<Delta> *, const Ret *> ret_insts;
static std::map<std::pair<std::string, std::vector<const Value<Delta> *>>, const Call *> call_insts;
static std::map<std::pair<const Value<Delta> *, std::vector<const Value<Delta> *>>, const PtrCall *> ptrcall_insts;
static Halt *halt_inst = nullptr;
static std::map<std::pair<const Value<Delta> *, const Value<Delta> *>, const Add *> add_insts;
static std::map<std::pair<const Value<Delta> *, const Value<Delta> *>, const Sub *> sub_insts;
static std::map<std::pair<const Value<Delta> *, const Value<Delta> *>, const Mul *> mul_insts;
static std::map<std::pair<const Value<Delta> *, const Value<Delta> *>, const Div *> div_insts;
static std::map<std::pair<const Value<Delta> *, const Value<Delta> *>, const Mod *> mod_insts;
static std::map<std::pair<const Value<Delta> *, const Value<Delta> *>, const BitAnd *> bitand_insts;
static std::map<std::pair<const Value<Delta> *, const Value<Delta> *>, const BitOr *> bitor_insts;
static std::map<std::pair<const Value<Delta> *, const Value<Delta> *>, const BitXor *> bitxor_insts;
static std::map<const Value<Delta> *, const BitNot *> bitnot_insts;
static std::map<std::pair<const Value<Delta> *, const Value<Delta> *>, const Shl *> shl_insts;
static std::map<std::pair<const Value<Delta> *, const Value<Delta> *>, const Shr *> shr_insts;
static std::map<std::pair<const Value<Delta> *, const Value<Delta> *>, const Rotl *> rotl_insts;
static std::map<std::pair<const Value<Delta> *, const Value<Delta> *>, const Rotr *> rotr_insts;
static std::map<std::pair<const Value<Delta> *, const Value<Delta> *>, const Eq *> eq_insts;
static std::map<std::pair<const Value<Delta> *, const Value<Delta> *>, const Ne *> ne_insts;
static std::map<std::pair<const Value<Delta> *, const Value<Delta> *>, const Lt *> lt_insts;
static std::map<std::pair<const Value<Delta> *, const Value<Delta> *>, const Gt *> gt_insts;
static std::map<std::pair<const Value<Delta> *, const Value<Delta> *>, const Le *> le_insts;
static std::map<std::pair<const Value<Delta> *, const Value<Delta> *>, const Ge *> ge_insts;
static std::map<std::pair<const Value<Delta> *, const Value<Delta> *>, const And *> and_insts;
static std::map<std::pair<const Value<Delta> *, const Value<Delta> *>, const Or *> or_insts;
static std::map<const Value<Delta> *, const Not *> not_insts;
static std::map<std::pair<const Value<Delta> *, const Value<Delta> *>, const Xor *> xor_insts;
static std::map<std::tuple<const Value<Delta> *, const Value<Delta> *, uint64_t>, const Assign *> assign_insts;
static std::map<std::pair<const Value<Delta> *, uint64_t>, const Load *> load_insts;
static std::map<std::pair<const Value<Delta> *, const Value<Delta> *>, const Index *> index_insts;
static std::map<std::tuple<const Value<Delta> *, bool, const std::vector<std::pair<std::string, const Value<Delta> *>>, std::vector<const Value<Delta> *>>, const Segment *> segment_insts;
static I1 *i1_inst = nullptr;
static I8 *i8_inst = nullptr;
static I16 *i16_inst = nullptr;
static I32 *i32_inst = nullptr;
static I64 *i64_inst = nullptr;
static I128 *i128_inst = nullptr;
static U8 *u8_inst = nullptr;
static U16 *u16_inst = nullptr;
static U32 *u32_inst = nullptr;
static U64 *u64_inst = nullptr;
static U128 *u128_inst = nullptr;
static F32 *f32_inst = nullptr;
static F64 *f64_inst = nullptr;
static Void *void_inst = nullptr;
static std::map<const Value<Delta> *, const Ptr *> ptr_insts;
static std::map<std::pair<std::string, std::vector<std::pair<std::string, const Value<Delta> *>>>, const Packet *> packet_insts;
static std::map<std::pair<const Value<Delta> *, uint64_t>, const Array *> array_insts;
static std::map<std::pair<std::vector<const Value<Delta> *>, const Value<Delta> *>, const FType *> ftype_insts;
static std::map<std::pair<std::string, const Value<Delta> *>, const Local *> local_insts;
static std::map<std::tuple<std::string, const Value<Delta> *, const Value<Delta> *, bool, bool>, const Global *> global_insts;
static std::map<std::string, const Number *> number_insts;
static std::map<std::string, const String *> string_insts;

static std::map<delta::NodeType, std::mutex> node_mutexes;

#define lock(type) std::lock_guard<std::mutex> lock(node_mutexes[type])

const RootNode *delta::RootNode::create(std::vector<const Value<Delta> *> children)
{
    lock(NodeType::Root);
    if (root == nullptr)
        root = new RootNode(children);
    return root;
}

const delta::SCast *delta::SCast::create(const Value<Delta> *type, const Value<Delta> *value)
{
    lock(NodeType::SCast);
    auto key = std::make_pair(type, value);
    if (!scast_insts.contains(key))
        scast_insts[key] = new SCast(type, value);
    return scast_insts[key];
}

const delta::UCast *delta::UCast::create(const Value<Delta> *type, const Value<Delta> *value)
{
    lock(NodeType::UCast);
    auto key = std::make_pair(type, value);
    if (!ucast_insts.contains(key))
        ucast_insts[key] = new UCast(type, value);
    return ucast_insts[key];
}

const delta::PtrICast *delta::PtrICast::create(const Value<Delta> *type, const Value<Delta> *value)
{
    lock(NodeType::PtrICast);
    auto key = std::make_pair(type, value);
    if (!ptricast_insts.contains(key))
        ptricast_insts[key] = new PtrICast(type, value);
    return ptricast_insts[key];
}

const delta::IPtrCast *delta::IPtrCast::create(const Value<Delta> *type, const Value<Delta> *value)
{
    lock(NodeType::IPtrCast);
    auto key = std::make_pair(type, value);
    if (!iptrcast_insts.contains(key))
        iptrcast_insts[key] = new IPtrCast(type, value);
    return iptrcast_insts[key];
}

const delta::Bitcast *delta::Bitcast::create(const Value<Delta> *type, const Value<Delta> *value)
{
    lock(NodeType::Bitcast);
    auto key = std::make_pair(type, value);
    if (!bitcast_insts.contains(key))
        bitcast_insts[key] = new Bitcast(type, value);
    return bitcast_insts[key];
}

const delta::IfElse *delta::IfElse::create(const Value<Delta> *cond, const Value<Delta> *then, const Value<Delta> *els)
{
    lock(NodeType::IfElse);
    auto key = std::make_tuple(cond, then, els);
    if (!ifelse_insts.contains(key))
        ifelse_insts[key] = new IfElse(cond, then, els);
    return ifelse_insts[key];
}

const delta::While *delta::While::create(const Value<Delta> *cond, const Value<Delta> *body)
{
    lock(NodeType::While);
    auto key = std::make_pair(cond, body);
    if (!while_insts.contains(key))
        while_insts[key] = new While(cond, body);
    return while_insts[key];
}

const delta::Jmp *delta::Jmp::create(std::string target)
{
    lock(NodeType::Jmp);
    if (!jmp_insts.contains(target))
        jmp_insts[target] = new Jmp(target);
    return jmp_insts[target];
}

const delta::Label *delta::Label::create(std::string name)
{
    lock(NodeType::Label);
    if (!label_insts.contains(name))
        label_insts[name] = new Label(name);
    return label_insts[name];
}

const delta::Ret *delta::Ret::create(const Value<Delta> *value)
{
    lock(NodeType::Ret);
    if (!ret_insts.contains(value))
        ret_insts[value] = new Ret(value);
    return ret_insts[value];
}

const delta::Call *delta::Call::create(std::string callee, std::vector<const Value<Delta> *> args)
{
    lock(NodeType::Call);
    auto key = std::make_pair(callee, args);
    if (!call_insts.contains(key))
        call_insts[key] = new Call(callee, args);
    return call_insts[key];
}

const delta::PtrCall *delta::PtrCall::create(const Value<Delta> *callee, std::vector<const Value<Delta> *> args)
{
    lock(NodeType::PtrCall);
    auto key = std::make_pair(callee, args);
    if (!ptrcall_insts.contains(key))
        ptrcall_insts[key] = new PtrCall(callee, args);
    return ptrcall_insts[key];
}

const delta::Halt *delta::Halt::create()
{
    lock(NodeType::Halt);
    if (halt_inst == nullptr)
        halt_inst = new Halt();
    return halt_inst;
}

const delta::Add *delta::Add::create(const Value<Delta> *lhs, const Value<Delta> *rhs)
{
    lock(NodeType::Add);
    auto key = std::make_pair(lhs, rhs);
    if (!add_insts.contains(key))
        add_insts[key] = new Add(lhs, rhs);
    return add_insts[key];
}

const delta::Sub *delta::Sub::create(const Value<Delta> *lhs, const Value<Delta> *rhs)
{
    lock(NodeType::Sub);
    auto key = std::make_pair(lhs, rhs);
    if (!sub_insts.contains(key))
        sub_insts[key] = new Sub(lhs, rhs);
    return sub_insts[key];
}

const delta::Mul *delta::Mul::create(const Value<Delta> *lhs, const Value<Delta> *rhs)
{
    lock(NodeType::Mul);
    auto key = std::make_pair(lhs, rhs);
    if (!mul_insts.contains(key))
        mul_insts[key] = new Mul(lhs, rhs);
    return mul_insts[key];
}

const delta::Div *delta::Div::create(const Value<Delta> *lhs, const Value<Delta> *rhs)
{
    lock(NodeType::Div);
    auto key = std::make_pair(lhs, rhs);
    if (!div_insts.contains(key))
        div_insts[key] = new Div(lhs, rhs);
    return div_insts[key];
}

const delta::Mod *delta::Mod::create(const Value<Delta> *lhs, const Value<Delta> *rhs)
{
    lock(NodeType::Mod);
    auto key = std::make_pair(lhs, rhs);
    if (!mod_insts.contains(key))
        mod_insts[key] = new Mod(lhs, rhs);
    return mod_insts[key];
}

const delta::BitAnd *delta::BitAnd::create(const Value<Delta> *lhs, const Value<Delta> *rhs)
{
    lock(NodeType::BitAnd);
    auto key = std::make_pair(lhs, rhs);
    if (!bitand_insts.contains(key))
        bitand_insts[key] = new BitAnd(lhs, rhs);
    return bitand_insts[key];
}

const delta::BitOr *delta::BitOr::create(const Value<Delta> *lhs, const Value<Delta> *rhs)
{
    lock(NodeType::BitOr);
    auto key = std::make_pair(lhs, rhs);
    if (!bitor_insts.contains(key))
        bitor_insts[key] = new BitOr(lhs, rhs);
    return bitor_insts[key];
}

const delta::BitXor *delta::BitXor::create(const Value<Delta> *lhs, const Value<Delta> *rhs)
{
    lock(NodeType::BitXor);
    auto key = std::make_pair(lhs, rhs);
    if (!bitxor_insts.contains(key))
        bitxor_insts[key] = new BitXor(lhs, rhs);
    return bitxor_insts[key];
}

const delta::BitNot *delta::BitNot::create(const Value<Delta> *value)
{
    lock(NodeType::BitNot);
    if (!bitnot_insts.contains(value))
        bitnot_insts[value] = new BitNot(value);
    return bitnot_insts[value];
}

const delta::Shl *delta::Shl::create(const Value<Delta> *lhs, const Value<Delta> *rhs)
{
    lock(NodeType::Shl);
    auto key = std::make_pair(lhs, rhs);
    if (!shl_insts.contains(key))
        shl_insts[key] = new Shl(lhs, rhs);
    return shl_insts[key];
}

const delta::Shr *delta::Shr::create(const Value<Delta> *lhs, const Value<Delta> *rhs)
{
    lock(NodeType::Shr);
    auto key = std::make_pair(lhs, rhs);
    if (!shr_insts.contains(key))
        shr_insts[key] = new Shr(lhs, rhs);
    return shr_insts[key];
}

const delta::Rotl *delta::Rotl::create(const Value<Delta> *lhs, const Value<Delta> *rhs)
{
    lock(NodeType::Rotl);
    auto key = std::make_pair(lhs, rhs);
    if (!rotl_insts.contains(key))
        rotl_insts[key] = new Rotl(lhs, rhs);
    return rotl_insts[key];
}

const delta::Rotr *delta::Rotr::create(const Value<Delta> *lhs, const Value<Delta> *rhs)
{
    lock(NodeType::Rotr);
    auto key = std::make_pair(lhs, rhs);
    if (!rotr_insts.contains(key))
        rotr_insts[key] = new Rotr(lhs, rhs);
    return rotr_insts[key];
}

const delta::Eq *delta::Eq::create(const Value<Delta> *lhs, const Value<Delta> *rhs)
{
    lock(NodeType::Eq);
    auto key = std::make_pair(lhs, rhs);
    if (!eq_insts.contains(key))
        eq_insts[key] = new Eq(lhs, rhs);
    return eq_insts[key];
}

const delta::Ne *delta::Ne::create(const Value<Delta> *lhs, const Value<Delta> *rhs)
{
    lock(NodeType::Ne);
    auto key = std::make_pair(lhs, rhs);
    if (!ne_insts.contains(key))
        ne_insts[key] = new Ne(lhs, rhs);
    return ne_insts[key];
}

const delta::Lt *delta::Lt::create(const Value<Delta> *lhs, const Value<Delta> *rhs)
{
    lock(NodeType::Lt);
    auto key = std::make_pair(lhs, rhs);
    if (!lt_insts.contains(key))
        lt_insts[key] = new Lt(lhs, rhs);
    return lt_insts[key];
}

const delta::Gt *delta::Gt::create(const Value<Delta> *lhs, const Value<Delta> *rhs)
{
    lock(NodeType::Gt);
    auto key = std::make_pair(lhs, rhs);
    if (!gt_insts.contains(key))
        gt_insts[key] = new Gt(lhs, rhs);
    return gt_insts[key];
}

const delta::Le *delta::Le::create(const Value<Delta> *lhs, const Value<Delta> *rhs)
{
    lock(NodeType::Le);
    auto key = std::make_pair(lhs, rhs);
    if (!le_insts.contains(key))
        le_insts[key] = new Le(lhs, rhs);
    return le_insts[key];
}

const delta::Ge *delta::Ge::create(const Value<Delta> *lhs, const Value<Delta> *rhs)
{
    lock(NodeType::Ge);
    auto key = std::make_pair(lhs, rhs);
    if (!ge_insts.contains(key))
        ge_insts[key] = new Ge(lhs, rhs);
    return ge_insts[key];
}

const delta::And *delta::And::create(const Value<Delta> *lhs, const Value<Delta> *rhs)
{
    lock(NodeType::And);
    auto key = std::make_pair(lhs, rhs);
    if (!and_insts.contains(key))
        and_insts[key] = new And(lhs, rhs);
    return and_insts[key];
}

const delta::Or *delta::Or::create(const Value<Delta> *lhs, const Value<Delta> *rhs)
{
    lock(NodeType::Or);
    auto key = std::make_pair(lhs, rhs);
    if (!or_insts.contains(key))
        or_insts[key] = new Or(lhs, rhs);
    return or_insts[key];
}

const delta::Not *delta::Not::create(const Value<Delta> *value)
{
    lock(NodeType::Not);
    if (!not_insts.contains(value))
        not_insts[value] = new Not(value);
    return not_insts[value];
}

const delta::Xor *delta::Xor::create(const Value<Delta> *lhs, const Value<Delta> *rhs)
{
    lock(NodeType::Xor);
    auto key = std::make_pair(lhs, rhs);
    if (!xor_insts.contains(key))
        xor_insts[key] = new Xor(lhs, rhs);
    return xor_insts[key];
}

const delta::Assign *delta::Assign::create(const Value<Delta> *var, const Value<Delta> *value, uint64_t rank)
{
    lock(NodeType::Assign);
    auto key = std::make_tuple(var, value, rank);
    if (!assign_insts.contains(key))
        assign_insts[key] = new Assign(var, value, rank);
    return assign_insts[key];
}

const delta::Load *delta::Load::create(const Value<Delta> *var, uint64_t rank)
{
    lock(NodeType::Load);
    auto key = std::make_pair(var, rank);
    if (!load_insts.contains(key))
        load_insts[key] = new Load(var, rank);
    return load_insts[key];
}

const delta::Index *delta::Index::create(const Value<Delta> *var, const Value<Delta> *index)
{
    lock(NodeType::Index);
    auto key = std::make_pair(var, index);
    if (!index_insts.contains(key))
        index_insts[key] = new Index(var, index);
    return index_insts[key];
}

const delta::Segment *delta::Segment::create(const Value<Delta> *ret, bool pure, const std::vector<std::pair<std::string, const Value<Delta> *>> &params, const std::vector<const Value<Delta> *> &stmts)
{
    lock(NodeType::Segment);
    auto key = std::make_tuple(ret, pure, params, stmts);
    if (!segment_insts.contains(key))
        segment_insts[key] = new Segment(ret, pure, params, stmts);
    return segment_insts[key];
}

const delta::I1 *delta::I1::create()
{
    lock(NodeType::I1);
    if (i1_inst == nullptr)
        i1_inst = new I1();
    return i1_inst;
}

const delta::I8 *delta::I8::create()
{
    lock(NodeType::I8);
    if (i8_inst == nullptr)
        i8_inst = new I8();
    return i8_inst;
}

const delta::I16 *delta::I16::create()
{
    lock(NodeType::I16);
    if (i16_inst == nullptr)
        i16_inst = new I16();
    return i16_inst;
}

const delta::I32 *delta::I32::create()
{
    lock(NodeType::I32);
    if (i32_inst == nullptr)
        i32_inst = new I32();
    return i32_inst;
}

const delta::I64 *delta::I64::create()
{
    lock(NodeType::I64);
    if (i64_inst == nullptr)
        i64_inst = new I64();
    return i64_inst;
}

const delta::I128 *delta::I128::create()
{
    lock(NodeType::I128);
    if (i128_inst == nullptr)
        i128_inst = new I128();
    return i128_inst;
}

const delta::U8 *delta::U8::create()
{
    lock(NodeType::U8);
    if (u8_inst == nullptr)
        u8_inst = new U8();
    return u8_inst;
}

const delta::U16 *delta::U16::create()
{
    lock(NodeType::U16);
    if (u16_inst == nullptr)
        u16_inst = new U16();
    return u16_inst;
}

const delta::U32 *delta::U32::create()
{
    lock(NodeType::U32);
    if (u32_inst == nullptr)
        u32_inst = new U32();
    return u32_inst;
}

const delta::U64 *delta::U64::create()
{
    lock(NodeType::U64);
    if (u64_inst == nullptr)
        u64_inst = new U64();
    return u64_inst;
}

const delta::U128 *delta::U128::create()
{
    lock(NodeType::U128);
    if (u128_inst == nullptr)
        u128_inst = new U128();
    return u128_inst;
}

const delta::F32 *delta::F32::create()
{
    lock(NodeType::F32);
    if (f32_inst == nullptr)
        f32_inst = new F32();
    return f32_inst;
}

const delta::F64 *delta::F64::create()
{
    lock(NodeType::F64);
    if (f64_inst == nullptr)
        f64_inst = new F64();
    return f64_inst;
}

const delta::Void *delta::Void::create()
{
    lock(NodeType::Void);
    if (void_inst == nullptr)
        void_inst = new Void();
    return void_inst;
}

const delta::Ptr *delta::Ptr::create(Value<Delta> *type)
{
    lock(NodeType::Ptr);
    if (!ptr_insts.contains(type))
        ptr_insts[type] = new Ptr(type);
    return ptr_insts[type];
}

const delta::Packet *delta::Packet::create(std::vector<std::pair<std::string, const Value<Delta> *>> fields, std::string name)
{
    lock(NodeType::Packet);
    auto key = std::make_pair(name, fields);
    if (!packet_insts.contains(key))
        packet_insts[key] = new Packet(fields, name);
    return packet_insts[key];
}

const delta::Array *delta::Array::create(Value<Delta> *type, uint64_t size)
{
    lock(NodeType::Array);
    auto key = std::make_pair(type, size);
    if (!array_insts.contains(key))
        array_insts[key] = new Array(type, size);
    return array_insts[key];
}

const delta::FType *delta::FType::create(std::vector<const Value<Delta> *> params, const Value<Delta> *ret)
{
    lock(NodeType::FType);
    auto key = std::make_pair(params, ret);
    if (!ftype_insts.contains(key))
        ftype_insts[key] = new FType(params, ret);
    return ftype_insts[key];
}

const delta::Local *delta::Local::create(std::string name, const Value<Delta> *type)
{
    lock(NodeType::Local);
    auto key = std::make_pair(name, type);
    if (!local_insts.contains(key))
        local_insts[key] = new Local(name, type);
    return local_insts[key];
}

const delta::Global *delta::Global::create(std::string name, const Value<Delta> *type, const Value<Delta> *value, bool _volatile, bool _atomic)
{
    lock(NodeType::Global);
    auto key = std::make_tuple(name, type, value, _volatile, _atomic);
    if (!global_insts.contains(key))
        global_insts[key] = new Global(name, type, value, _volatile, _atomic);
    return global_insts[key];
}

const delta::Number *delta::Number::create(std::string value)
{
    lock(NodeType::Number);
    if (!number_insts.contains(value))
        number_insts[value] = new Number(value);
    return number_insts[value];
}

const delta::String *delta::String::create(std::string value)
{
    lock(NodeType::String);
    if (!string_insts.contains(value))
        string_insts[value] = new String(value);
    return string_insts[value];
}