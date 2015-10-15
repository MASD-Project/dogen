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
#include "dogen/yarn/types/type_visitor.hpp"
#include "dogen/yarn/types/resolution_error.hpp"
#include "dogen/yarn/io/nested_name_io.hpp"
#include "dogen/yarn/io/property_io.hpp"
#include "dogen/yarn/io/model_io.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/resolver.hpp"

using namespace dogen::utility::log;

namespace {

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

resolver::resolver(model& m) : model_(m), has_resolved_(false) { }

void resolver::validate_inheritance_graph(const object& ao) const {
    auto i(ao.relationships().find(relationship_types::parents));
    if (i == ao.relationships().end())
        return;

    for (const auto& pn : i->second) {
        const auto j(model_.objects().find(pn));
        if (j == model_.objects().end()) {
            std::ostringstream s;
            s << orphan_object << ": " << ao.name().qualified()
              << ". parent: " << pn.qualified();

            BOOST_LOG_SEV(lg, error) << s.str();
            BOOST_THROW_EXCEPTION(resolution_error(s.str()));
        }
    }

    i = ao.relationships().find(relationship_types::original_parents);
    if (i == ao.relationships().end())
        return;

    for (const auto& pn : i->second) {
        const auto j(model_.objects().find(pn));
        if (j == model_.objects().end()) {
            std::ostringstream s;
            s << orphan_object << ": " << ao.name().qualified()
              << ". original parent: " << pn.qualified();

            BOOST_LOG_SEV(lg, error) << s.str();
            BOOST_THROW_EXCEPTION(resolution_error(s.str()));
        }
    }
}

void resolver::validate_refinements(const concept& c) const {
    for (const auto& n : c.refines()) {
        const auto i(model_.concepts().find(n));
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

name resolver::resolve_partial_type(const name& n) const {
    BOOST_LOG_SEV(lg, debug) << "Resolving type:" << n.qualified();

    name r(n);

    // first try the type as it was read originally.
    const auto& objects(model_.objects());
    auto i(objects.find(r));
    if (i != objects.end())
        return r;

    // then try setting module path to the target one
    r.location().external_module_path(
        model_.name().location().external_module_path());
    i = objects.find(r);
    if (i != objects.end())
        return r;

    // now try all available module paths from references
    for (const auto& pair : model_.references()) {
        const auto n(pair.first);
        r.location().external_module_path(
            n.location().external_module_path());
        i = objects.find(r);
        if (i != objects.end())
            return r;
    }

    // reset external module path
    r.location().external_module_path(std::list<std::string>{});

    // its not a object, could it be a primitive?
    const auto& primitives(model_.primitives());
    auto j(primitives.find(r));
    if (j != primitives.end())
        return r;

    // try enumerations
    const auto& enumerations(model_.enumerations());
    auto k(enumerations.find(r));
    if (k != enumerations.end())
        return r;

    // then try setting module path to the target one
    r.location().external_module_path(
        model_.name().location().external_module_path());
    k = enumerations.find(r);
    if (k != enumerations.end())
        return r;

    // now try all available module paths from references
    for (const auto& pair : model_.references()) {
        const auto n(pair.first);
        r.location().external_module_path(
            n.location().external_module_path());
        k = enumerations.find(r);
        if (k != enumerations.end())
            return r;
    }

    if (r.location().original_model_name().empty()) {
        const auto& l(model_.name().location());
        // it could be a type defined in this model
        r.location().original_model_name(l.original_model_name());
        r.location().external_module_path(l.external_module_path());
        i = objects.find(r);
        if (i != objects.end())
            return r;

        auto k(enumerations.find(r));
        if (k != enumerations.end())
            return r;
    }

    // handle the case where a model has a package with the same name
    // as a reference model. FIXME: big hack.
    {
        name n;
        n.simple(r.simple());

        if (!r.location().internal_module_path().empty()) {
            n.location().original_model_name(
                r.location().internal_module_path().front());
        }
        n.location().external_module_path(
            model_.name().location().external_module_path());

        i = objects.find(n);
        if (i != objects.end())
            return n;
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
