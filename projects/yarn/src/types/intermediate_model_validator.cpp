/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/elements_traversal.hpp"
#include "dogen/yarn/types/intermediate_model_validator.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.intermediate_model_validator"));
/*
std::array<std::string, 93> cpp_reserved = {
    "alignas", "alignof", "and", "and_eq",
    "asm", "atomic_cancel", "atomic_commit", "atomic_noexcept",
    "auto", "bitand", "bitor", "bool",
    "break", "case", "catch", "char",
    "char16_t", "char32_t", "class", "compl",
    "concept", "const", "const_cast", "constexpr",
    "continue", "decltype", "default", "delete",
    "do", "double", "dynamic_cast", "else",
    "enum", "explicit", "export", "extern",
    "false", "float", "for", "friend",
    "goto", "if", "import", "inline",
    "int", "long", "module", "mutable",
    "namespace", "new", "noexcept", "not",
    "not_eq", "nullptr", "operator", "or",
    "or_eq", "private", "protected", "public",
    "register", "reinterpret_cast", "requires", "return",
    "short", "signed", "sizeof", "static",
    "static_assert", "static_cast", "struct", "switch",
    "synchronized", "template", "this", "thread_local",
    "throw", "true", "try", "typedef",
    "typeid", "typename", "union", "unsigned",
    "using", "virtual", "void", "volatile",
    "wchar_t", "while", "xor", "xor_eq", "xor_eqalignas"
};
*/
}

namespace dogen {
namespace yarn {

namespace {

class name_validator final {
public:
    void operator()(const yarn::concept& /*c*/) {}
    void operator()(const yarn::primitive& /*p*/) {}
    void operator()(const dogen::yarn::visitor& /*v*/) { }
    void operator()(const yarn::enumeration& /*e*/) { }
    void operator()(const yarn::object& /*o*/) { }
    void operator()(const yarn::exception& /*e*/) { }
    void operator()(const yarn::module& /*m*/) { }
};

}

void intermediate_model_validator::
sanity_check_all_names(const intermediate_model& im) const {
    name_validator nv;
    yarn::elements_traversal(im, nv);
}

void intermediate_model_validator::
validate(const intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Started validation. Model: " << im.name().id();

    BOOST_LOG_SEV(lg, debug) << "Finished validation.";
}

} }
