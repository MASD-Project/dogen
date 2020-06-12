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
#include <array>
#include <string_view>
#include <algorithm>
#include <unordered_set>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/string/splitter.hpp"
#include "dogen.logical/io/entities/name_io.hpp"
#include "dogen.logical/types/helpers/decomposer.hpp"
#include "dogen.logical/types/helpers/validation_error.hpp"
#include "dogen.logical/types/entities/physical/archetype.hpp"
#include "dogen.logical/types/helpers/post_assembly_validator.hpp"

typedef boost::error_info<struct owner, std::string>
errmsg_validation_owner;

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("logical.helpers.post_assembly_validator"));

const std::string space(" ");
const std::regex strict_name_regex("^[a-zA-Z_][a-zA-Z0-9_]*$");
const std::regex loose_name_regex("^[a-zA-Z_][\\-\\.a-zA-Z0-9_]*$");

/*
 * FIXME: we've removed the following keywords for now because masd
 * uses these terms: "module" "class" "enum"
 */
constexpr std::array<std::string_view, 81> cpp_reserved = { {
        "alignas", "alignof", "and", "and_eq", "asm", "atomic_cancel",
        "atomic_commit", "atomic_noexcept", "auto", "bitand", "bitor",
        "break", "case", "catch", "compl", "const",
        "const_cast", "constexpr", "continue", "decltype", "default", "delete",
        "do", "dynamic_cast", "else", "explicit", "export", "extern",
        "false", "for", "friend", "goto", "if", "import", "inline",
        "mutable", "namespace", "new", "noexcept", "not",
        "not_eq", "nullptr", "operator", "or", "or_eq", "private", "protected",
        "public", "register", "reinterpret_cast", "requires", "return",
        "sizeof", "static", "static_assert", "static_cast", "struct", "switch",
        "synchronized", "template", "this", "thread_local", "throw", "true",
        "try", "typedef", "typeid", "typename", "union", "using", "virtual",
        "void", "volatile", "wchar_t", "while", "xor", "xor_eq", "xor_eqalignas"
        "concept"
    } };

constexpr std::array<std::string_view, 11> cpp_builtins = { {
    "char16_t", "char32_t", "unsigned", "bool", "char", "double", "float",
    "int", "long", "short", "signed"
    }
};

/*
 * FIXME: we've removed the following keywords for now because test
 * models use these terms: "base", "class", "enum"
 */
constexpr std::array<std::string_view, 64> csharp_reserved = { {
        "abstract", "as", "break",
        "case", "catch", "checked",
        "const", "continue", "default", "delegate",
        "do", "else", "event",
        "explicit", "extern",   "false", "finally",
        "fixed", "for", "foreach", "goto",
        "if", "implicit", "in", "interface",
        "internal",  "is", "lock", "namespace",
        "new", "null", "operator", "out",
        "override", "params", "private", "protected",
        "public", "readonly", "ref", "return",
        "sealed", "sizeof", "stackalloc", "static",
        "struct", "switch", "this", "throw",
        "true", "try", "typeof", "unchecked",
        "unsafe", "using", "var", "virtual",
        "void", "volatile", "while"
    } };

/*
 * FIXME: we've removed the following builtins for now, because they
 * are being used by the following models:
 *
 * - "object": masd
 * - "string": std
 */
constexpr std::array<std::string_view, 12> csharp_builtins = { {
        "byte", "bool", "char", "double", "float", "int", "long",
        "sbyte", "short",  "uint", "ulong", "ushort"
    }
};

const std::string duplicate_element("Element has an ID already defined: ");
const std::string invalid_string(
    "String is not valid according to the identifier regular expression: ");
const std::string reserved_keyword(
    "String matches a reserved keyword in a supported technical space: ");
const std::string builtin_name("String matches the name of a built in type: ");
const std::string abstract_instance(
    "Attempt to instantiate an abstract type: ");
const std::string invalid_empty_id("Name must have a non-empty id.");
const std::string invalid_logical_meta_element("Meta-element name not found: ");

}

namespace dogen::logical::helpers {

template<typename Container>
inline void check_not_in_container(const Container& c, const std::string& str,
    const std::string& error_msg) {
    const auto i(std::find(c.begin(), c.end(), str));
    if (i != c.end()) {
        BOOST_LOG_SEV(lg, error) << error_msg << str;
        BOOST_THROW_EXCEPTION(validation_error(error_msg + str));
    }
}

bool post_assembly_validator::
allow_spaces_in_built_in_types(const entities::technical_space l) {
    return l == entities::technical_space::cpp;
}

void post_assembly_validator::validate_string(const std::string& s,
    const std::regex& regex, bool check_not_builtin) {
    BOOST_LOG_SEV(lg, trace) << "Sanity checking string: " << s;

    /*
     * String must match the regular expression for a valid
     * identifier across all supported technical_space.
     */
    if (!std::regex_match(s, regex)) {
        BOOST_LOG_SEV(lg, error) << invalid_string << "'" << s << "'";
        BOOST_THROW_EXCEPTION(validation_error(invalid_string + s));
    }

    /*
     * String must not be in our list of reserved keywords for C++.
     */
    check_not_in_container(cpp_reserved, s, reserved_keyword);

    /*
     * String must not be in our list of reserved keywords for C#.
     */
    check_not_in_container(csharp_reserved, s, reserved_keyword);

    if (check_not_builtin) {
        /*
         * String must not be in our list of builtins for C++.
         */
        check_not_in_container(cpp_builtins, s, builtin_name);

        /*
         * String must not be in our list of builtins for C#.
         */
        check_not_in_container(csharp_builtins, s, builtin_name);
    }

    BOOST_LOG_SEV(lg, trace) << "String passed all sanity checks.";
}

void post_assembly_validator::validate_strings(
    const std::list<std::string>& strings, const std::regex& regex) {
    for (const auto& s : strings)
        validate_string(s, regex);
}

void post_assembly_validator::validate_name(const entities::name& n,
    const std::regex& regex, const bool allow_spaces_in_built_in_types) {
    /*
     * All names must have a non-empty id.
     */
    if (n.qualified().dot().empty()) {
        BOOST_LOG_SEV(lg, error) << invalid_empty_id;
        BOOST_THROW_EXCEPTION(validation_error(invalid_empty_id));
    }

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
     * technical space where built-ins can have spaces, we split the
     * name on space and validate each component separately.
     */
    BOOST_LOG_SEV(lg, trace) << "at_global_namespace: "
                             << at_global_namespace
                             << " allow_spaces_in_built_in_types: "
                             << allow_spaces_in_built_in_types;

    if (at_global_namespace && allow_spaces_in_built_in_types) {
        using utility::string::splitter;
        const auto splitted(splitter::split_delimited(n.simple(), space));
        BOOST_LOG_SEV(lg, trace) << "Splitted simple name: " << splitted;
        for (const auto& s : splitted)
            validate_string(s, regex, check_not_builtin);
    } else
        validate_string(n.simple(), regex, check_not_builtin);

    validate_strings(l.external_modules(), regex);
    validate_strings(l.model_modules(), regex);
    validate_strings(l.internal_modules(), regex);

    if (!l.element().empty())
        validate_string(l.element(), regex);
}

void post_assembly_validator::
validate_names(const std::list<std::pair<std::string, entities::name>>& names,
    const entities::technical_space l) {
    BOOST_LOG_SEV(lg, debug) << "Validating names.";
    std::unordered_set<std::string> ids_done;

    const bool allow_spaces(allow_spaces_in_built_in_types(l));
    for (const auto& pair : names) {
        const auto& owner(pair.first);
        const auto& n(pair.second);
        const auto& id(n.qualified().dot());
        BOOST_LOG_SEV(lg, trace) << "Validating: '" << id << "'"
                                 << " owner id: '" << owner << "'";

        try {
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
            validate_name(n, strict_name_regex, allow_spaces);

            BOOST_LOG_SEV(lg, trace) << "Name is valid.";
        } catch (boost::exception& e) {
            e << errmsg_validation_owner(owner);
            throw;
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Finished validating names.";
}

void post_assembly_validator::validate_meta_names(
    const std::list<std::pair<std::string, entities::name>>& meta_names) {
    BOOST_LOG_SEV(lg, debug) << "Validating all meta-names.";

    /*
     * Note that we can't just simply call validate_names here because
     * meta-names are known to have duplicates - i.e. we use the same
     * meta-model element many times).
     */
    for (const auto& pair : meta_names) {
        const auto& owner(pair.first);
        const auto& n(pair.second);
        const auto& id(n.qualified().dot());
        BOOST_LOG_SEV(lg, trace) << "Validating: '" << id << "'"
                                 << " owner id: '" << owner << "'";

        try {
            /*
             * Element name must pass all sanity checks.
             */
            validate_name(n, strict_name_regex, false/*allow_spaces*/);

            BOOST_LOG_SEV(lg, trace) << "Name is valid.";
        } catch (boost::exception& e) {
            e << errmsg_validation_owner(owner);
            throw;
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Finished validating all meta-names.";
}

void post_assembly_validator::
validate_name_tree(const std::unordered_set<std::string>& abstract_elements,
    const entities::technical_space ts, const entities::name_tree& nt,
    const bool inherit_opaqueness_from_parent) {
    const auto& ae(abstract_elements);
    const auto id(nt.current().qualified().dot());
    const bool is_abstract(ae.find(id) != ae.end());
    if (is_abstract && !inherit_opaqueness_from_parent) {
        BOOST_LOG_SEV(lg, error) << abstract_instance << id;
        BOOST_THROW_EXCEPTION(validation_error(abstract_instance + id));
    }

    for (const auto& c : nt.children())
        validate_name_tree(ae, ts, c, nt.are_children_opaque());
}

void post_assembly_validator::validate_name_trees(
    const std::unordered_set<std::string>& abstract_elements,
    const entities::technical_space ts,
    const std::list<std::pair<std::string, entities::name_tree>>& nts) {
    BOOST_LOG_SEV(lg, debug) << "Validating name trees.";

    /*
     * The only validation we perform on name trees at present is done
     * just for c++, so we can ignore all other technical_space. Note
     * that we already resolve all of the names in the name tree so we
     * know they are valid. These are just additional checks we
     * perform on these names.
     */
    if (ts != entities::technical_space::cpp)
        return;

    for (const auto& pair : nts) {
        const auto& owner(pair.first);
        const auto& nt(pair.second);
        BOOST_LOG_SEV(lg, trace) << "Validating: '"
                                 << nt.qualified().dot() << "'";

        try {
            validate_name_tree(abstract_elements, ts, nt);
        } catch (boost::exception& e) {
            e << errmsg_validation_owner(owner);
            throw;
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Validated name trees.";
}

void post_assembly_validator::
validate_physical_archetypes(const entities::model& m) {
    const auto& mns(m.meta_names());
    const auto& archs(m.physical_elements().archetypes());
    for (const auto& pair : archs) {
        const auto& arch(*pair.second);
        const auto lmeid(arch.logical_meta_element_id());
        const auto i(mns.find(lmeid));
        if (i == mns.end()) {
            BOOST_LOG_SEV(lg, error) << invalid_logical_meta_element << lmeid;
            BOOST_THROW_EXCEPTION(
                validation_error(invalid_logical_meta_element + lmeid));
        }
    }
}

void post_assembly_validator::
validate(const indices& idx, const entities::model& m) {
    BOOST_LOG_SEV(lg, debug) << "Started validation. Model: "
                             << m.name().qualified().dot();

    const auto ts(m.input_technical_space());
    const auto dr(decomposer::decompose(m));
    validate_names(dr.names(), ts);
    validate_meta_names(dr.meta_names());
    validate_name_trees(idx.abstract_elements(), ts, dr.name_trees());
    validate_physical_archetypes(m);

    BOOST_LOG_SEV(lg, debug) << "Finished validation.";
}

}
