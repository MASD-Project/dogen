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

resolver::resolver(intermediate_model& m) : model_(m), has_resolved_(false) { }

bool resolver::is_name_in_model(const name& n) const {
    BOOST_LOG_SEV(lg, debug) << "Finding name:" << n;

    auto i(model_.objects().find(n.qualified()));
    if (i != model_.objects().end()) {
        BOOST_LOG_SEV(lg, debug) << "Name belongs to an object in model.";
        return true;
    }

    auto j(model_.enumerations().find(n.qualified()));
    if (j != model_.enumerations().end()) {
        BOOST_LOG_SEV(lg, debug) << "Name belongs to an enumeration in model.";
        return true;
    }

    auto k(model_.primitives().find(n.qualified()));
    if (k != model_.primitives().end()) {
        BOOST_LOG_SEV(lg, debug) << "Name belongs to a primitive in model.";
        return true;
    }

    BOOST_LOG_SEV(lg, debug) << "Name not found in model.";
    return false;
}

name resolver::resolve_partial_type(const name& n) const {
    BOOST_LOG_SEV(lg, debug) << "Resolving type:" << n.qualified();

    /* First try the type as it was read originally. This caters for
     * types placed in the global module.
     */
    if (is_name_in_model(n))
        return n;

    /* Then handle the case of the type belonging to the current
     * model. It either has no model name at all, or it has a model
     * name but no external module path. We cater for both cases.
     */
    name_factory nf;
    {
        const auto r(nf.build_combined_element_name(model_.name(), n,
                true/*populate_model_name_if_blank*/));

        if (is_name_in_model(r))
            return r;
    }

    /* Now handle the case where the type belongs to a reference, but
     * is missing the external module path.
     */
    for (const auto& pair : model_.references()) {
        const auto r(nf.build_combined_element_name(pair.first, n));

        if (is_name_in_model(r))
            return r;
    }

    /* Finally handle the case where a model has a package with the
     * same name as a reference model.
     */
    {
        auto r(nf.build_promoted_module_name(model_.name(), n));
        BOOST_LOG_SEV(lg, error) << r;
        if (is_name_in_model(r))
            return r;
    }

    BOOST_LOG_SEV(lg, error) << undefined_type << n.qualified();
    BOOST_THROW_EXCEPTION(resolution_error(undefined_type + n.qualified()));
}

void resolver::resolve_partial_type(nested_name& nn) const {
    for (auto& cnn : nn.children())
        resolve_partial_type(cnn);

    name n(resolve_partial_type(nn.type()));
    BOOST_LOG_SEV(lg, debug) << "Resolved type " << n.qualified() << ".";
    nn.type(n);
}

void resolver::
resolve_properties(const name& owner, std::list<property>& p) const {
    for (auto& prop : p) {
        try {
            resolve_partial_type(prop.type());
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

void resolver::validate_inheritance_graph(const object& o) const {
    if (o.parents().empty())
        return;

    for (const auto& pn : o.parents()) {
        const auto j(model_.objects().find(pn.qualified()));
        if (j == model_.objects().end()) {
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
        const auto j(model_.objects().find(pn.qualified()));
        if (j == model_.objects().end()) {
            std::ostringstream s;
            s << orphan_object << ": " << o.name().qualified()
              << ". original parent: " << pn.qualified();

            BOOST_LOG_SEV(lg, error) << s.str();
            BOOST_THROW_EXCEPTION(resolution_error(s.str()));
        }
    }
}

void resolver::validate_refinements(const concept& c) const {
    for (const auto& n : c.refines()) {
        const auto i(model_.concepts().find(n.qualified()));
        if (i == model_.concepts().end()) {
            std::ostringstream stream;
            stream << orphan_concept << ". concept: "
                   << c.name().qualified()
                   << ". refined concept: " << n.qualified();

            BOOST_LOG_SEV(lg, error) << stream.str();
            BOOST_THROW_EXCEPTION(resolution_error(stream.str()));
        }
    }
}

void resolver::require_not_has_resolved() const {
    if (!has_resolved())
        return;

    BOOST_LOG_SEV(lg, error) << model_resolved;
    BOOST_THROW_EXCEPTION(resolution_error(model_resolved));
}

void resolver::resolve_concepts() {
    for (auto& pair : model_.concepts()) {
        concept& c(pair.second);

        if (c.generation_type() == generation_types::no_generation)
            continue;

        resolve_properties(c.name(), c.local_properties());
        validate_refinements(c);
    }
}

void resolver::resolve_objects() {
    BOOST_LOG_SEV(lg, debug) << "Objects found: " << model_.objects().size();

    for (auto& pair : model_.objects()) {
        auto& o(pair.second);
        BOOST_LOG_SEV(lg, debug) << "Resolving type " << o.name().qualified();

        if (o.generation_type() == generation_types::no_generation)
            continue;

        validate_inheritance_graph(o);
        resolve_properties(o.name(), o.local_properties());
    }
}

void resolver::resolve() {
    require_not_has_resolved();
    resolve_concepts();
    resolve_objects();
    has_resolved_ = true;
}

} }
