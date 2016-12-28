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
#include "dogen/yarn/types/identifiable_and_qualified_builder.hpp"
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

bool resolver::
is_floating_point(const intermediate_model& im, const name& n) const {
    auto i(im.primitives().find(n.id()));
    return i != im.primitives().end() && i->second.is_floating_point();
}

bool resolver::is_primitive(const intermediate_model& im, const name& n) const {
    auto i(im.primitives().find(n.id()));
    if (i != im.primitives().end()) {
        BOOST_LOG_SEV(lg, debug) << "Name belongs to a primitive in model.";
        return true;
    }
    return false;
}

bool
resolver::is_enumeration(const intermediate_model& im, const name& n) const {
    auto i(im.enumerations().find(n.id()));
    if (i != im.enumerations().end()) {
        BOOST_LOG_SEV(lg, debug) << "Name belongs to an enumeration in model.";
        return true;
    }
    return false;
}

bool resolver::is_object(const intermediate_model& im, const name& n) const {
    auto i(im.objects().find(n.id()));
    if (i != im.objects().end()) {
        BOOST_LOG_SEV(lg, debug) << "Name belongs to an object in model.";
        return true;
    }
    return false;
}

bool resolver:: is_concept(const intermediate_model& im, const name& n) const {
    auto i(im.concepts().find(n.id()));
    if (i != im.concepts().end()) {
        BOOST_LOG_SEV(lg, debug) << "Name belongs to a concept in model.";
        return true;
    }
    return false;
}

name resolver::
obtain_default_enumeration_type(const intermediate_model& im) const {
    name r;
    bool found(false);
    for (const auto& pair : im.primitives()) {
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

bool resolver::is_name_referable(const indices& idx, const name& n) const {
    BOOST_LOG_SEV(lg, debug) << "Checking to see if name is referable:" << n;

    const auto i(idx.elements_referable_by_attributes().find(n.id()));
    if (i != idx.elements_referable_by_attributes().end())
        return true;

    BOOST_LOG_SEV(lg, debug) << "Name not found in model or its not referable.";
    return false;
}

name resolver::
resolve_name(const intermediate_model& im, const name& context,
    const name& n) const {

    BOOST_LOG_SEV(lg, debug) << "Resolving name: " << n.id();
    BOOST_LOG_SEV(lg, debug) << "Initial state: " << n;
     /*
     * First try the type as it was read originally. This caters for
     * types placed in the global module.
     */
    BOOST_LOG_SEV(lg, debug) << "Resolving as is.";
    if (is_name_referable(im.indices(), n)) {
        BOOST_LOG_SEV(lg, debug) << "Resolution succeeded.";
        return n;
    }

    BOOST_LOG_SEV(lg, debug) << "Resolution failed.";

    /*
     * Then handle the case of the type belonging to the current
     * context. It either has no model name at all, or it has a model
     * name but no external module path. We cater for both cases.
     *
     * Note that at present we expect names to have the internal
     * module path set. This means that if you are inside of a package
     * P and you want to refer to another type T inside of P, you need
     * to qualify it: T::P. It should however by trivial to expand the
     * code below to simply copy the internal module path and to
     * recurse it up all the way to the top.
     */
    BOOST_LOG_SEV(lg, debug) << "Resolving using context: " << context;
    name_factory nf;
    {
        const auto r(nf.build_combined_element_name(context, n,
                true/*populate_model_name_if_blank*/));

        if (is_name_referable(im.indices(), r)) {
            BOOST_LOG_SEV(lg, debug) << "Resolution succeeded.";
            return r;
        }
        BOOST_LOG_SEV(lg, debug) << "Resolution failed.";
    }

    /*
     * Now handle the case where the type belongs to a reference, but
     * is missing the external module path.
     */
    for (const auto& pair : im.references()) {
        const auto& ref(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Resolving using reference: " << ref;
        const auto r(nf.build_combined_element_name(ref, n));

        if (is_name_referable(im.indices(), r)) {
            BOOST_LOG_SEV(lg, debug) << "Resolution succeeded.";
            return r;
        }
        BOOST_LOG_SEV(lg, debug) << "Resolution failed.";
    }

    /*
     * Finally handle the case where a model has a package with the
     * same name as a reference model.
     */
    {
        BOOST_LOG_SEV(lg, debug) << "Resolving as package with model name.";
        auto r(nf.build_promoted_module_name(im.name(), n));
        if (is_name_referable(im.indices(), r)) {
            BOOST_LOG_SEV(lg, debug) << "Resolution succeeded.";
            return r;
        }
        BOOST_LOG_SEV(lg, debug) << "Resolution failed.";
    }

    BOOST_LOG_SEV(lg, error) << undefined_type << n.id();
    BOOST_THROW_EXCEPTION(resolution_error(undefined_type + n.id()));
}

void resolver::resolve_name_tree(const intermediate_model& im,
    const name& owner, name_tree& nt) const {
    const name n(resolve_name(im, owner, nt.current()));

    BOOST_LOG_SEV(lg, debug) << "Resolved name: " << nt.current().id()
                             << " to: " << n.id();
    nt.current(n);
    if (is_primitive(im, n)) {
        nt.is_current_simple_type(true);
        nt.is_floating_point(is_floating_point(im, n));
    } else
        nt.is_current_simple_type(is_enumeration(im, n));

    const auto i(im.indices().objects_always_in_heap().find(n.id()));
    nt.are_children_opaque(i != im.indices().objects_always_in_heap().end());

    identifiable_and_qualified_builder iqb;
    iqb.add(n);

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
        resolve_name_tree(im, owner, c);
        iqb.add(c);
    }

    const auto iq(iqb.build());
    nt.identifiable(iq.first);
    nt.qualified(iq.second);
}

void resolver::resolve_attributes(const intermediate_model& im,
    const name& owner, std::list<attribute>& attributes) const {
    for (auto& a : attributes) {
        try {
            resolve_name_tree(im, owner, a.parsed_type());
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

void resolver::validate_inheritance_graph(const intermediate_model& im,
    const object& o) const {

    /*
     * Ensure that all parents and original parents exist as objects.
     */
    const auto id(o.name().id());
    for (const auto& pn : o.parents()) {
        if (is_object(im, pn))
            continue;

        std::ostringstream s;
        s << orphan_object << ": " << id << ". Parent: " << pn.id();

        BOOST_LOG_SEV(lg, error) << s.str();
        BOOST_THROW_EXCEPTION(resolution_error(s.str()));
    }

    for (const auto& rp : o.root_parents()) {
        if (is_object(im, rp))
            continue;

        std::ostringstream s;
        s << orphan_object << ": " << id << ". Root parent: " << rp.id();

        BOOST_LOG_SEV(lg, error) << s.str();
        BOOST_THROW_EXCEPTION(resolution_error(s.str()));
    }
}

void resolver::validate_refinements(const intermediate_model& im,
    const concept& c) const {

    /*
     * Ensure that all refined concepts exist as concepts.
     */
    const auto id(c.name().id());
    for (const auto& n : c.refines()) {
        if (is_concept(im, n))
            continue;

        std::ostringstream stream;
        stream << orphan_concept << ". Concept: " << id
               << ". Refined concept: " << n.id();

        BOOST_LOG_SEV(lg, error) << stream.str();
        BOOST_THROW_EXCEPTION(resolution_error(stream.str()));
    }
}

void resolver::
resolve_concepts(intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Concepts: " << im.concepts().size();

    for (auto& pair : im.concepts()) {
        concept& c(pair.second);

        BOOST_LOG_SEV(lg, debug) << "Resolving: " << c.name().id();
        resolve_attributes(im, c.name(), c.local_attributes());
        validate_refinements(im, c);
    }
}

void resolver::
resolve_objects(intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Objects: " << im.objects().size();

    for (auto& pair : im.objects()) {
        auto& o(pair.second);

        BOOST_LOG_SEV(lg, debug) << "Resolving: " << o.name().id();
        validate_inheritance_graph(im, o);
        resolve_attributes(im, o.name(), o.local_attributes());
    }
}

void resolver::resolve_enumerations(intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Enumerations: " << im.enumerations().size();

    /*
     * If no enumerations exist, we can just exit. This means we can
     * still support models that have no dependencies, provided they
     * do not use enumerations.
     */
    if (im.enumerations().empty())
        return;

    const auto det(obtain_default_enumeration_type(im));
    for (auto& pair : im.enumerations()) {
        auto& e(pair.second);

        BOOST_LOG_SEV(lg, debug) << "Resolving: " << e.name().id();

        const auto ut(e.underlying_type());
        BOOST_LOG_SEV(lg, debug) << "Underlying type: " << ut;

        if (ut.simple().empty()) {
            BOOST_LOG_SEV(lg, debug) << "Defaulting enumeration to type: "
                                     << det.id();
            e.underlying_type(det);
        } else if (!is_primitive(im, ut)) {
            BOOST_LOG_SEV(lg, error) << invalid_default << ut.id();
            BOOST_THROW_EXCEPTION(resolution_error(
                    invalid_default + ut.id()));
        }
    }
}

void resolver::resolve(intermediate_model& im) const {
    resolve_concepts(im);
    resolve_objects(im);
    resolve_enumerations(im);
}

name resolver::resolve(const intermediate_model& im, const name& context,
    const name& n) const {
    const auto r(resolve_name(im, context, n));
    BOOST_LOG_SEV(lg, debug) << "Resolved name: " << n.id()
                             << " to: " << r.id();
    return r;
}

} }
