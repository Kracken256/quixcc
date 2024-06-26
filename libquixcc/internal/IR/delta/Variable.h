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

#ifndef __QUIXCC_IR_DELTA_NODES_VARIABLE_H__
#define __QUIXCC_IR_DELTA_NODES_VARIABLE_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <IR/delta/DeltaIR.h>
#include <IR/delta/Expr.h>
#include <IR/delta/Type.h>

namespace libquixcc::ir::delta {
class Local : public Value {
 protected:
  bool print_impl(std::ostream &os, PState &state) const override;
  boost::uuids::uuid hash_impl() const override;
  bool verify_impl() const override;

  Local(std::string name, const Type *type, const Expr *value)
      : name(name), type(type), value(value) {
    ntype = (int)NodeType::Local;
  }

 public:
  static const Local *create(std::string name, const Type *type,
                             const Expr *value = nullptr);

  std::string name;
  const Type *type;
  const Expr *value;
};

class Global : public Value {
 protected:
  bool print_impl(std::ostream &os, PState &state) const override;
  boost::uuids::uuid hash_impl() const override;
  bool verify_impl() const override;

  Global(std::string name, const Type *type, const Expr *value, bool _volatile,
         bool _atomic, bool _extern)
      : name(name),
        type(type),
        value(value),
        _volatile(_volatile),
        _atomic(_atomic),
        _extern(_extern) {
    ntype = (int)NodeType::Global;
  }

 public:
  static const Global *create(std::string name, const Type *type,
                              const Expr *value, bool _volatile, bool _atomic,
                              bool _extern);

  std::string name;
  const Type *type;
  const Expr *value;
  bool _volatile;
  bool _atomic;
  bool _extern;
};

class Number : public Expr {
 protected:
  bool print_impl(std::ostream &os, PState &state) const override;
  boost::uuids::uuid hash_impl() const override;
  bool verify_impl() const override;

  Number(std::string value) : value(value) { ntype = (int)NodeType::Number; }

 public:
  static const Number *create(std::string value);
  const Type *infer() const override;

  std::string value;
};

class String : public Expr {
 protected:
  bool print_impl(std::ostream &os, PState &state) const override;
  boost::uuids::uuid hash_impl() const override;
  bool verify_impl() const override;

  String(std::string value) : value(value) { ntype = (int)NodeType::String; }

 public:
  static const String *create(std::string value);
  const Type *infer() const override;

  std::string value;
};

class List : public Expr {
 protected:
  bool print_impl(std::ostream &os, PState &state) const override;
  boost::uuids::uuid hash_impl() const override;
  bool verify_impl() const override;

  List(std::vector<const Expr *> values) : values(values) {
    ntype = (int)NodeType::List;
  }

 public:
  static const List *create(std::vector<const Expr *> values);
  const Type *infer() const override;

  std::vector<const Expr *> values;
};
}  // namespace libquixcc::ir::delta

#endif  // __QUIXCC_IR_DELTA_NODES_VARIABLE_H__