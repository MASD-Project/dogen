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
#include <regex>
#include <algorithm>
#include <unordered_set>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/string/splitter.hpp"
#include "dogen/yarn/io/name_io.hpp"
#include "dogen/yarn/types/concept.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/element.hpp"
#include "dogen/yarn/types/exception.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/validation_error.hpp"
#include "dogen/yarn/types/element_visitor.hpp"
#include "dogen/yarn/types/model_validator.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.model_validator"));

// FIXME: we've removed the following keywords for now because yarn
// uses these terms. We need to first rename it to package or somesuch
// other name and then add it back.
//
// module, concept
std::array<std::string, 81> cpp_reserved = { {
    "alignas", "alignof", "and", "and_eq", "asm", "atomic_cancel",
    "atomic_commit", "atomic_noexcept", "auto", "bitand", "bitor",
    "break", "case", "catch", "class", "compl", "const",
    "const_cast", "constexpr", "continue", "decltype", "default", "delete",
    "do", "dynamic_cast", "else", "enum", "explicit", "export", "extern",
    "false", "for", "friend", "goto", "if", "import", "inline",
    "mutable", "namespace", "new", "noexcept", "not",
    "not_eq", "nullptr", "operator", "or", "or_eq", "private", "protected",
    "public", "register", "reinterpret_cast", "requires", "return", "sizeof",
    "static", "static_assert", "static_cast", "struct", "switch",
    "synchronized", "template", "this", "thread_local", "throw", "true", "try",
    "typedef", "typeid", "typename", "union", "using", "virtual", "void",
    "volatile", "wchar_t", "while", "xor", "xor_eq", "xor_eqalignas"
    } };

std::array<std::string, 11> cpp_builtins = { {
    "char16_t", "char32_t", "unsigned", "bool", "char", "double", "float",
    "int", "long", "short", "signed"
    }
};

const std::string duplicate_element("Element has an ID already defined: ");
const std::string invalid_string(
    "String is not valid according to the identifier regular expression: ");
const std::string reserved_keyword(
    "String matches a resvered keyword on one of the supported languages: ");
const std::string builtin_name("String matches the name of a built in type: ");
const std::string space(" ");

}

namespace dogen {
namespace yarn {

class name_collector final : public element_visitor {
private:
    void add_name(const name& n);
    void add_names(const std::list<name>& names);
    void process_element(const element& e);
    void process_attributes(const std::list<attribute>& attrs);

public:
    using yarn::element_visitor::visit;
    void visit(const yarn::concept& c);
    void visit(const yarn::module& m);
    void visit(const yarn::enumeration& e);
    void visit(const yarn::exception& e);
    void visit(const yarn::object& o);
    void visit(const yarn::primitive& p);

public:
    const std::list<name>& result() const;

private:
    std::list<name> result_;
};

void name_collector::add_name(const name& n) {
    result_.push_back(n);
}
void name_collector::add_names(const std::list<name>& names) {
    for (const auto& n : names)
        add_name(n);
}

void name_collector::process_attributes(const std::list<attribute>& attrs) {
    for (const auto& attr : attrs)
        add_name(attr.name());
}

void name_collector::process_element(const element& e) {
    add_name(e.name());
}

void name_collector::visit(const yarn::concept& c) {
    process_element(c);
    process_attributes(c.local_attributes());
}

void name_collector::visit(const yarn::module& m) {
    /*
     * The global module represents the unnamed global
     * namespace. There can only be one of these and it is generated
     * internally by Dogen so there is nothing to validate.
     */
    if (m.is_global_module())
        return;

    result_.push_back(m.name());
}

void name_collector::visit(const yarn::enumeration& e) {
    process_element(e);
    // FIXME: add enumerator names
}

void name_collector::visit(const yarn::exception& e) {
    process_element(e);
}

void name_collector::visit(const yarn::object& o) {
    process_element(o);
    process_attributes(o.local_attributes());
}

void name_collector::visit(const yarn::primitive& p) {
    process_element(p);
}

const std::list<name>& name_collector::result() const {
    return result_;
}

bool model_validator::allow_spaces_in_built_in_types(const languages l) const {
    return l == languages::cpp;
}

void model_validator::
sanity_check_string(const std::string& s, bool check_not_builtin) const {
    static std::regex name_regex("^[a-zA-Z_][a-zA-Z0-9_]*$");
    if (!std::regex_match(s, name_regex)) {
        BOOST_LOG_SEV(lg, error) << invalid_string << "'" << s << "'";
        BOOST_THROW_EXCEPTION(validation_error(invalid_string + s));
    }

    const auto i(std::find(cpp_reserved.begin(), cpp_reserved.end(), s));
    if (i != cpp_reserved.end()) {
        BOOST_LOG_SEV(lg, error) << reserved_keyword << s;
        BOOST_THROW_EXCEPTION(validation_error(reserved_keyword + s));
    }

    if (check_not_builtin) {
        const auto j(std::find(cpp_builtins.begin(), cpp_builtins.end(), s));
        if (j != cpp_builtins.end()) {
            BOOST_LOG_SEV(lg, error) << builtin_name << s;
            BOOST_THROW_EXCEPTION(validation_error(builtin_name + s));
        }
    }

    BOOST_LOG_SEV(lg, debug) << "String passed all sanity checks: " << s;
}

void model_validator::
sanity_check_strings(const std::list<std::string>& strings) const {
    for (const auto& s : strings)
        sanity_check_string(s);
}

std::list<name>
model_validator::decompose_model_into_element_names(const model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Obtaining a list of all names for model: "
                             << m.name().id();

    /*
     * Collect the names of all elements and attributes.
     */
    name_collector nc;
    for (const auto& ptr : m.elements()) {
        const auto& e(*ptr);
        e.accept(nc);
    }

    /*
     * Note that we do not add the model name itself; this is because
     * we will validate the model's module, which is generated from
     * the model name.
     */
    const auto names(nc.result());
    return names;
}

/*
void model_validator::
non_refined_concepts_should_have_at_least_one_property(const model& im) const {
    for (const auto& c : im.concepts()) {
    }
}
*/

void model_validator::sanity_check_name(
    const name& n, const bool allow_spaces_in_built_in_types) const {

    /*
     * Built-in types are defined at the global namespace level; if we
     * are at the global namespace level, then built-ins are valid
     * element names. In this case, we should not check the name
     * against the built-in list.
     */
    const auto& l(n.location());
    const bool at_global_namespace(l.external_modules().empty() &&
        l.model_modules().empty() &&
        l.internal_modules().empty());
    const bool check_not_builtin(!at_global_namespace);

    /*
     * Sanity check all of the components of the name. Bit of a hack
     * here: if we are at global namespace and our model is in a
     * language where built-ins can have spaces, we split the name on
     * space and validate each component separately.
     */
    BOOST_LOG_SEV(lg, debug) << "at_global_namespace: " << at_global_namespace
                             << " allow_spaces_in_built_in_types: "
                             << allow_spaces_in_built_in_types;
    if (at_global_namespace && allow_spaces_in_built_in_types) {
        using utility::string::splitter;
        const auto splitted(splitter::split_scoped(n.simple(), space));
        BOOST_LOG_SEV(lg, debug) << "Splitted simple name: " << splitted;
        for (const auto& s : splitted)
            sanity_check_string(s, check_not_builtin);
    } else
        sanity_check_string(n.simple(), check_not_builtin);

    sanity_check_strings(l.external_modules());
    sanity_check_strings(l.model_modules());
    sanity_check_strings(l.internal_modules());

    if (!l.element().empty())
        sanity_check_string(l.element());
}

void model_validator::sanity_check_all_names(const model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Sanity checking all names.";
    std::unordered_set<std::string> ids_done;
    const auto names(decompose_model_into_element_names(m));

    for (const auto& n : names) {
        const auto& id(n.id());
        BOOST_LOG_SEV(lg, debug) << "Sanity checking: '" << id << "'";

        /*
         * Element identifier must be unique across all model
         * elements.
         */
        const auto inserted(ids_done.insert(id).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_element << id;
            BOOST_THROW_EXCEPTION(validation_error(duplicate_element + id));
        }

        /*
         * Element name must pass all sanity checks.
         */
        const bool allow_spaces(allow_spaces_in_built_in_types(m.language()));
        sanity_check_name(n, allow_spaces);

        BOOST_LOG_SEV(lg, debug) << "Name is valid.";
    }
    BOOST_LOG_SEV(lg, debug) << "Finished sanity checking all names.";
}

void model_validator::validate(const model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Started validation. Model: " << m.name().id();
    sanity_check_all_names(m);
    BOOST_LOG_SEV(lg, debug) << "Finished validation.";
}

} }
