////////////////////////////////////////////////////////////////////////////////
///                                                                          ///
///  ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░ ░▒▓██████▓▒░  ///
/// ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ ///
/// ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░        ///
/// ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓██████▓▒░░▒▓█▓▒░      ░▒▓█▓▒░        ///
/// ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░        ///
/// ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ ///
///  ░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░ ░▒▓██████▓▒░  ///
///    ░▒▓█▓▒░                                                               ///
///     ░▒▓██▓▒░                                                             ///
///                                                                          ///
///   * QUIX LANG COMPILER - The official compiler for the Quix language.    ///
///   * Copyright (C) 2024 Wesley C. Jones                                   ///
///                                                                          ///
///   The QUIX Compiler Suite is free software; you can redistribute it or   ///
///   modify it under the terms of the GNU Lesser General Public             ///
///   License as published by the Free Software Foundation; either           ///
///   version 2.1 of the License, or (at your option) any later version.     ///
///                                                                          ///
///   The QUIX Compiler Suite is distributed in the hope that it will be     ///
///   useful, but WITHOUT ANY WARRANTY; without even the implied warranty of ///
///   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      ///
///   Lesser General Public License for more details.                        ///
///                                                                          ///
///   You should have received a copy of the GNU Lesser General Public       ///
///   License along with the QUIX Compiler Suite; if not, see                ///
///   <https://www.gnu.org/licenses/>.                                       ///
///                                                                          ///
////////////////////////////////////////////////////////////////////////////////

#include <IR/delta/Memory.h>

boost::uuids::uuid libquixcc::ir::delta::Assign::hash_impl() const {
  return Hasher().gettag().add(rank).add(var).add(value).hash();
}

bool libquixcc::ir::delta::Assign::verify_impl() const {
  return var->verify() && value->verify();
}

boost::uuids::uuid libquixcc::ir::delta::PostInc::hash_impl() const {
  return Hasher().gettag().add(var).hash();
}

bool libquixcc::ir::delta::PostInc::verify_impl() const {
  return var->verify();
}

boost::uuids::uuid libquixcc::ir::delta::PostDec::hash_impl() const {
  return Hasher().gettag().add(var).hash();
}

bool libquixcc::ir::delta::PostDec::verify_impl() const {
  return var->verify();
}

boost::uuids::uuid libquixcc::ir::delta::AddressOf::hash_impl() const {
  return Hasher().gettag().add(lhs).hash();
}

bool libquixcc::ir::delta::AddressOf::verify_impl() const {
  return lhs->verify();
}

boost::uuids::uuid libquixcc::ir::delta::Deref::hash_impl() const {
  return Hasher().gettag().add(lhs).hash();
}

bool libquixcc::ir::delta::Deref::verify_impl() const { return lhs->verify(); }

boost::uuids::uuid libquixcc::ir::delta::Member::hash_impl() const {
  return Hasher().gettag().add(lhs).add(field).add(field_type).hash();
}

bool libquixcc::ir::delta::Member::verify_impl() const {
  return lhs->verify() && field_type->verify();
}

boost::uuids::uuid libquixcc::ir::delta::Index::hash_impl() const {
  return Hasher().gettag().add(expr).add(index).add(type).hash();
}

bool libquixcc::ir::delta::Index::verify_impl() const {
  return expr->verify() && index->verify() && type->verify();
}