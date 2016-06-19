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
#include "dogen/yarn/io/name_tree_io.hpp"
#include "dogen/yarn/io/attribute_io.hpp"
#include "dogen/yarn/io/intermediate_model_io.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/name_factory.hpp"
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

typedef boost::error_info<struct tag_errmsg, std::string> errmsg_info;

}

namespace dogen {
namespace yarn {

bool resolver::is_primitive(const intermediate_model& m, const name& n) const {
    auto i(m.primitives().find(n.id()));
    if (i != m.primitives().end()) {
        BOOST_LOG_SEV(lg, debug) << "Name belongs to a primitive in model.";
        return true;
    }
    return false;
}

bool resolver::is_enumeration(const intermediate_model& m, const name& n) const {
    auto i(m.enumerations().find(n.id()));
    if (i != m.enumerations().end()) {
        BOOST_LOG_SEV(lg, debug) << "Name belongs to an enumeration in model.";
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

bool resolver::
is_name_in_model(const intermediate_model& m, const name& n) const {
    BOOST_LOG_SEV(lg, debug) << "Finding name:" << n;

    if (is_object(m, n) || is_enumeration(m, n) || is_primitive(m, n))
        return true;

    BOOST_LOG_SEV(lg, debug) << "Name not found in model.";
    return false;
}

name resolver::
resolve_partial_type(const intermediate_model& m, const name& n) const {
    BOOST_LOG_SEV(lg, debug) << "Resolving type:" << n.id();

    /* First try the type as it was read originally. This caters for
     * types placed in the global module.
     */
    if (is_name_in_model(m, n))
        return n;

    /* Then handle the case of the type belonging to the current
     * model. It either has no model name at all, or it has a model
     * name but no external module path. We cater for both cases.
     */
    name_factory nf;
    {
        const auto r(nf.build_combined_element_name(m.name(), n,
                true/*populate_model_name_if_blank*/));

        if (is_name_in_model(m, r))
            return r;
    }

    /* Now handle the case where the type belongs to a reference, but
     * is missing the external module path.
     */
    for (const auto& pair : m.references()) {
        const auto r(nf.build_combined_element_name(pair.first, n));

        if (is_name_in_model(m, r))
            return r;
    }

    /* Finally handle the case where a model has a package with the
     * same name as a reference model.
     */
    {
        auto r(nf.build_promoted_module_name(m.name(), n));
        BOOST_LOG_SEV(lg, error) << r;
        if (is_name_in_model(m, r))
            return r;
    }

    BOOST_LOG_SEV(lg, error) << undefined_type << n.id();
    BOOST_THROW_EXCEPTION(resolution_error(undefined_type + n.id()));
}

void resolver::
resolve_partial_type(const intermediate_model& m, name_tree& nt) const {
    for (auto& cnt : nt.children())
        resolve_partial_type(m, cnt);

    const name n(resolve_partial_type(m, nt.parent()));
    BOOST_LOG_SEV(lg, debug) << "Resolved type " << n.id() << ".";
    nt.parent(n);
}

void resolver::resolve_attributes(const intermediate_model& m,
    const name& owner, std::list<attribute>& attributes) const {
    for (auto& a : attributes) {
        try {
            resolve_partial_type(m, a.parsed_type());
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

void resolver::resolve_concepts(intermediate_model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Concepts: " << m.concepts().size();

    for (auto& pair : m.concepts()) {
        concept& c(pair.second);

        if (c.generation_type() == generation_types::no_generation)
            continue;

        BOOST_LOG_SEV(lg, debug) << "Resolving: " << c.name().id();
        resolve_attributes(m, c.name(), c.local_attributes());
        validate_refinements(m, c);
    }
}

void resolver::resolve_objects(intermediate_model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Objects: " << m.objects().size();

    for (auto& pair : m.objects()) {
        auto& o(pair.second);

        if (o.generation_type() == generation_types::no_generation)
            continue;

        BOOST_LOG_SEV(lg, debug) << "Resolving: " << o.name().id();
        validate_inheritance_graph(m, o);
        resolve_attributes(m, o.name(), o.local_attributes());
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
    resolve_concepts(m);
    resolve_objects(m);
    resolve_enumerations(m);
}

} }
