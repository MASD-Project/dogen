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
#include <memory>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/unordered_set_io.hpp"
#include "dogen/yarn/types/resolution_error.hpp"
#include "dogen/yarn/io/name_io.hpp"
#include "dogen/yarn/io/languages_io.hpp"
#include "dogen/yarn/io/name_tree_io.hpp"
#include "dogen/yarn/io/attribute_io.hpp"
#include "dogen/yarn/io/intermediate_model_io.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/separators.hpp"
#include "dogen/yarn/types/pretty_printer.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/yarn/types/string_processor.hpp"
#include "dogen/yarn/types/resolver.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.resolver"));

const std::string empty;
const std::string orphan_object("Object's parent could not be located: ");
const std::string orphan_concept("Refined concept could not be located: ");
const std::string undefined_type("Object has attribute with undefined type: ");
const std::string too_many_defaults(
    "Model has more than one default enumeration: ");
const std::string missing_default(
    "Model does not have a default enumeration type: ");
const std::string invalid_default(
    "Model has a default enumeration type that cannot be found: ");
const std::string qn_missing("Could not find qualified name for language.");

typedef boost::error_info<struct tag_errmsg, std::string> errmsg_info;

}

namespace dogen {
namespace yarn {

template<typename Qualifiable>
inline std::string obtain_qualified(const Qualifiable& q) {
    const auto i(q.qualified().find(languages::cpp));
    if (i == q.qualified().end()) {
        BOOST_LOG_SEV(lg, error) << qn_missing << yarn::languages::cpp;
        BOOST_THROW_EXCEPTION(resolution_error(qn_missing));
    }

    return i->second;
}

bool resolver::is_primitive(const intermediate_model& m, const name& n) const {
    auto i(m.primitives().find(n.id()));
    if (i != m.primitives().end()) {
        BOOST_LOG_SEV(lg, debug) << "Name belongs to a primitive in model.";
        return true;
    }
    return false;
}

bool resolver::is_object(const intermediate_model& m, const name& n) const {
    auto i(m.objects().find(n.id()));
    if (i != m.objects().end()) {
        BOOST_LOG_SEV(lg, debug) << "Name belongs to an object in model.";
        return true;
    }
    return false;
}

bool resolver:: is_concept(const intermediate_model& m, const name& n) const {
    auto i(m.concepts().find(n.id()));
    if (i != m.concepts().end()) {
        BOOST_LOG_SEV(lg, debug) << "Name belongs to a concept in model.";
        return true;
    }
    return false;
}

resolver::indexed_ids resolver::index(const intermediate_model& m) const {
    indexed_ids r;
    for (const auto& pair : m.primitives())
        r.referable_by_attributes.insert(pair.first);

    for (const auto& pair : m.enumerations())
        r.referable_by_attributes.insert(pair.first);

    for (const auto& pair : m.objects()) {
        r.referable_by_attributes.insert(pair.first);
        if (pair.second.type_parameters_settings().always_in_heap())
            r.always_in_heap.insert(pair.first);
    }

    BOOST_LOG_SEV(lg, debug) << "Always in heap: " << r.always_in_heap;
    return r;
}

name resolver::
obtain_default_enumeration_type(const intermediate_model& m) const {
    name r;
    bool found(false);
    for (const auto& pair : m.primitives()) {
        const auto p(pair.second);
        if (p.is_default_enumeration_type()) {
            BOOST_LOG_SEV(lg, debug) << "Found default enumeration name type:"
                                     << p.name().id();

            if (found) {
                BOOST_LOG_SEV(lg, error) << too_many_defaults
                                         << p.name().id();
                BOOST_THROW_EXCEPTION(
                    resolution_error(too_many_defaults + p.name().id()));
            }
            found = true;
            r = p.name();
        }
    }

    if (!found) {
        BOOST_LOG_SEV(lg, error) << missing_default;
        BOOST_THROW_EXCEPTION(resolution_error(missing_default));
    }

    return r;
}

bool resolver::is_name_referable(const indexed_ids& idx, const name& n) const {
    BOOST_LOG_SEV(lg, debug) << "Checking to see if name is referable:" << n;

    const auto i(idx.referable_by_attributes.find(n.id()));
    if (i != idx.referable_by_attributes.end())
        return true;

    BOOST_LOG_SEV(lg, debug) << "Name not found in model or its not referable.";
    return false;
}

name resolver::resolve_partial_type(const intermediate_model& m,
    const indexed_ids& idx, const name& n) const {
    BOOST_LOG_SEV(lg, debug) << "Resolving type:" << n.id();

    /*
     * First try the type as it was read originally. This caters for
     * types placed in the global module.
     */
    if (is_name_referable(idx, n))
        return n;

    /*
     * Then handle the case of the type belonging to the current
     * model. It either has no model name at all, or it has a model
     * name but no external module path. We cater for both cases.
     */
    name_factory nf;
    {
        const auto r(nf.build_combined_element_name(m.name(), n,
                true/*populate_model_name_if_blank*/));

        if (is_name_referable(idx, r))
            return r;
    }

    /*
     * Now handle the case where the type belongs to a reference, but
     * is missing the external module path.
     */
    for (const auto& pair : m.references()) {
        const auto r(nf.build_combined_element_name(pair.first, n));

        if (is_name_referable(idx, r))
            return r;
    }

    /*
     * Finally handle the case where a model has a package with the
     * same name as a reference model.
     */
    {
        auto r(nf.build_promoted_module_name(m.name(), n));
        BOOST_LOG_SEV(lg, error) << r;
        if (is_name_referable(idx, r))
            return r;
    }

    BOOST_LOG_SEV(lg, error) << undefined_type << n.id();
    BOOST_THROW_EXCEPTION(resolution_error(undefined_type + n.id()));
}

void resolver::resolve_partial_type(const intermediate_model& m,
    const indexed_ids& idx, const name& owner, name_tree& nt) const {
    const name n(resolve_partial_type(m, idx, nt.current()));
    nt.current(n);

    const auto i(idx.always_in_heap.find(n.id()));
    nt.are_children_opaque(i != idx.always_in_heap.end());

    pretty_printer pp(separators::double_colons);
    pp.add(obtain_qualified(n));

    /*
     * Strictly speaking this is not directly related to
     * resolution. However, we can only find circular dependencies
     * after we have resolved all names and since we're already here
     * might as well mark them.
     */
    if (owner == nt.current()) {
        nt.is_circular_dependency(true);
        BOOST_LOG_SEV(lg, debug) << "Found circular dependency. Owner: "
                                 << owner.id();
    }

    for (auto& c : nt.children()) {
        resolve_partial_type(m, idx, owner, c);
        pp.add_child(obtain_qualified(c));
    }

    const auto cpp_qn(pp.print());
    nt.qualified()[languages::cpp] = cpp_qn;

    string_processor sp;
    nt.identifiable(sp.to_identifiable(cpp_qn));
}

void resolver::resolve_attributes(const intermediate_model& m,
    const name& owner, const indexed_ids& idx,
    std::list<attribute>& attributes) const {
    for (auto& a : attributes) {
        try {
            resolve_partial_type(m, idx, owner, a.parsed_type());
            BOOST_LOG_SEV(lg, debug) << "Resolved attribute: " << a.name().id();
        } catch (boost::exception& e) {
            std::ostringstream s;
            s << "Owner type name: " << owner.id()
              << " Attribute name: " << a.name()
              << " Attribute type: " << a.parsed_type();
            e << errmsg_info(s.str());
            throw;
        }
    }
}

void resolver::validate_inheritance_graph(const intermediate_model& m,
    const object& o) const {
    if (o.parents().empty())
        return;

    for (const auto& pn : o.parents()) {
        if (!is_object(m, pn)) {
            std::ostringstream s;
            s << orphan_object << ": " << o.name().id()
              << ". parent: " << pn.id();

            BOOST_LOG_SEV(lg, error) << s.str();
            BOOST_THROW_EXCEPTION(resolution_error(s.str()));
        }
    }

    if (o.root_parents().empty())
        return;

    for (const auto& pn : o.root_parents()) {
        if (!is_object(m, pn)) {
            std::ostringstream s;
            s << orphan_object << ": " << o.name().id()
              << ". original parent: " << pn.id();

            BOOST_LOG_SEV(lg, error) << s.str();
            BOOST_THROW_EXCEPTION(resolution_error(s.str()));
        }
    }
}

void resolver::validate_refinements(const intermediate_model& m,
    const concept& c) const {
    for (const auto& n : c.refines()) {
        if (!is_concept(m, n)) {
            std::ostringstream stream;
            stream << orphan_concept << ". concept: "
                   << c.name().id()
                   << ". refined concept: " << n.id();

            BOOST_LOG_SEV(lg, error) << stream.str();
            BOOST_THROW_EXCEPTION(resolution_error(stream.str()));
        }
    }
}

void resolver::
resolve_concepts(const indexed_ids& idx, intermediate_model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Concepts: " << m.concepts().size();

    for (auto& pair : m.concepts()) {
        concept& c(pair.second);

        if (c.generation_type() == generation_types::no_generation)
            continue;

        BOOST_LOG_SEV(lg, debug) << "Resolving: " << c.name().id();
        resolve_attributes(m, c.name(), idx, c.local_attributes());
        validate_refinements(m, c);
    }
}

void resolver::
resolve_objects(const indexed_ids& idx, intermediate_model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Objects: " << m.objects().size();

    for (auto& pair : m.objects()) {
        auto& o(pair.second);

        if (o.generation_type() == generation_types::no_generation)
            continue;

        BOOST_LOG_SEV(lg, debug) << "Resolving: " << o.name().id();
        validate_inheritance_graph(m, o);
        resolve_attributes(m, o.name(), idx, o.local_attributes());
    }
}

void resolver::resolve_enumerations(intermediate_model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Enumerations: " << m.enumerations().size();

    /* if no enumerations exist, we can just exit. This means we can
     * still support models that have no dependencies, provided they
     * do not use enumerations.
     */
    if (m.enumerations().empty())
        return;

    const auto det(obtain_default_enumeration_type(m));
    for (auto& pair : m.enumerations()) {
        auto& e(pair.second);

        if (e.generation_type() == generation_types::no_generation)
            continue;

        BOOST_LOG_SEV(lg, debug) << "Resolving: " << e.name().id();

        const auto ut(e.underlying_type());
        BOOST_LOG_SEV(lg, debug) << "Underlying type: " << ut;

        if (ut.simple().empty()) {
            BOOST_LOG_SEV(lg, debug) << "Defaulting enumeration to type: "
                                     << det.id();
            e.underlying_type(det);
        } else if (!is_primitive(m, ut)) {
            BOOST_LOG_SEV(lg, error) << invalid_default << ut.id();
            BOOST_THROW_EXCEPTION(resolution_error(
                    invalid_default + ut.id()));
        }
    }
}

void resolver::resolve(intermediate_model& m) const {
    auto idx(index(m));
    resolve_concepts(idx, m);
    resolve_objects(idx, m);
    resolve_enumerations(m);
}

} }
