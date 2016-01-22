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
#include "dogen/yarn/io/nested_name_io.hpp"
#include "dogen/yarn/io/property_io.hpp"
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
const std::string undefined_type("Object has property with undefined type: ");
const std::string model_resolved("Resolution has already been done for model");

typedef boost::error_info<struct tag_errmsg, std::string> errmsg_info;

}

namespace dogen {
namespace yarn {

bool resolver::
is_name_in_model(const intermediate_model& m, const name& n) const {
    BOOST_LOG_SEV(lg, debug) << "Finding name:" << n;

    auto i(m.objects().find(n.qualified()));
    if (i != m.objects().end()) {
        BOOST_LOG_SEV(lg, debug) << "Name belongs to an object in model.";
        return true;
    }

    auto j(m.enumerations().find(n.qualified()));
    if (j != m.enumerations().end()) {
        BOOST_LOG_SEV(lg, debug) << "Name belongs to an enumeration in model.";
        return true;
    }

    auto k(m.primitives().find(n.qualified()));
    if (k != m.primitives().end()) {
        BOOST_LOG_SEV(lg, debug) << "Name belongs to a primitive in model.";
        return true;
    }

    BOOST_LOG_SEV(lg, debug) << "Name not found in model.";
    return false;
}

name resolver::
resolve_partial_type(const intermediate_model& m, const name& n) const {
    BOOST_LOG_SEV(lg, debug) << "Resolving type:" << n.qualified();

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

    BOOST_LOG_SEV(lg, error) << undefined_type << n.qualified();
    BOOST_THROW_EXCEPTION(resolution_error(undefined_type + n.qualified()));
}

void resolver::
resolve_partial_type(const intermediate_model& m, nested_name& nn) const {
    for (auto& cnn : nn.children())
        resolve_partial_type(m, cnn);

    const name n(resolve_partial_type(m, nn.parent()));
    BOOST_LOG_SEV(lg, debug) << "Resolved type " << n.qualified() << ".";
    nn.parent(n);
}

void resolver::resolve_properties(const intermediate_model& m,
    const name& owner, std::list<property>& p) const {
    for (auto& prop : p) {
        try {
            resolve_partial_type(m, prop.type());
        } catch (boost::exception& e) {
            std::ostringstream s;
            s << "Owner type name: " << owner.qualified()
              << " Property name: " << prop.name()
              << " Property type: " << prop.type();
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
        const auto j(m.objects().find(pn.qualified()));
        if (j == m.objects().end()) {
            std::ostringstream s;
            s << orphan_object << ": " << o.name().qualified()
              << ". parent: " << pn.qualified();

            BOOST_LOG_SEV(lg, error) << s.str();
            BOOST_THROW_EXCEPTION(resolution_error(s.str()));
        }
    }

    if (o.root_parents().empty())
        return;

    for (const auto& pn : o.root_parents()) {
        const auto j(m.objects().find(pn.qualified()));
        if (j == m.objects().end()) {
            std::ostringstream s;
            s << orphan_object << ": " << o.name().qualified()
              << ". original parent: " << pn.qualified();

            BOOST_LOG_SEV(lg, error) << s.str();
            BOOST_THROW_EXCEPTION(resolution_error(s.str()));
        }
    }
}

void resolver::validate_refinements(const intermediate_model& m,
    const concept& c) const {
    for (const auto& n : c.refines()) {
        const auto i(m.concepts().find(n.qualified()));
        if (i == m.concepts().end()) {
            std::ostringstream stream;
            stream << orphan_concept << ". concept: "
                   << c.name().qualified()
                   << ". refined concept: " << n.qualified();

            BOOST_LOG_SEV(lg, error) << stream.str();
            BOOST_THROW_EXCEPTION(resolution_error(stream.str()));
        }
    }
}

void resolver::resolve_concepts(intermediate_model& m) const {
    for (auto& pair : m.concepts()) {
        concept& c(pair.second);

        if (c.generation_type() == generation_types::no_generation)
            continue;

        resolve_properties(m, c.name(), c.local_properties());
        validate_refinements(m, c);
    }
}

void resolver::resolve_objects(intermediate_model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Objects found: " << m.objects().size();

    for (auto& pair : m.objects()) {
        auto& o(pair.second);
        BOOST_LOG_SEV(lg, debug) << "Resolving type " << o.name().qualified();

        if (o.generation_type() == generation_types::no_generation)
            continue;

        validate_inheritance_graph(m, o);
        resolve_properties(m, o.name(), o.local_properties());
    }
}

void resolver::resolve(intermediate_model& m) const {
    resolve_concepts(m);
    resolve_objects(m);
}

} }
