/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include <set>
#include <sstream>
#include <memory>
#include <functional>
#include <iterator>
#include <algorithm>
// #include <iostream>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
// #include "dogen/utility/io/set_io.hpp"
// #include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/io/unordered_set_io.hpp"
#include "dogen/sml/types/abstract_object.hpp"
#include "dogen/sml/types/value_object.hpp"
#include "dogen/sml/types/keyed_entity.hpp"
#include "dogen/sml/types/service.hpp"
#include "dogen/sml/types/factory.hpp"
#include "dogen/sml/types/repository.hpp"
#include "dogen/sml/types/entity.hpp"
#include "dogen/sml/types/keyed_entity.hpp"
#include "dogen/sml/types/type_visitor.hpp"
#include "dogen/sml/types/resolution_error.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/io/nested_qname_io.hpp"
#include "dogen/sml/io/property_io.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/types/resolver.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("sml.resolver"));

const std::string empty;
const std::string orphan_object("Object's parent could not be located: ");
const std::string orphan_concept("Refined concept could not be located: ");
const std::string undefined_type("Object has property with undefined type: ");
const std::string model_resolved("Resolution has already been done for model");

typedef boost::error_info<struct tag_errmsg, std::string> errmsg_info;

}

namespace dogen {
namespace sml {

// FIXME: hack
bool operator<(const qname& lhs, const qname& rhs) {
    return
        lhs.model_name() < rhs.model_name() ||
        (lhs.model_name() == rhs.model_name() &&
            (lhs.external_module_path() < rhs.external_module_path() ||
                (lhs.external_module_path() == rhs.external_module_path() &&
                    (lhs.simple_name() < rhs.simple_name() ||
                        (lhs.simple_name() == rhs.simple_name() &&
                            lhs.meta_type() < rhs.meta_type())))));
}

resolver::resolver(model& m) : model_(m), has_resolved_(false) { }

void resolver::
expand_concept_hierarchy(const qname& qn, std::list<qname>& concepts) const {

    const auto i(model_.concepts().find(qn));
    if (i == model_.concepts().end()) {
        std::ostringstream stream;
        stream << orphan_concept << ". concept: "
               << qn.simple_name() << " could not be found.";

        BOOST_LOG_SEV(lg, error) << stream.str();
        BOOST_THROW_EXCEPTION(resolution_error(stream.str()));
    }

    for (const auto& c : i->second.refines())
        expand_concept_hierarchy(c, concepts);

    concepts.push_back(qn);
}

void resolver::validate_inheritance_graph(const abstract_object& ao) const {
    // FIXME: we should really just check that the parent exists since
    // we know all objects get checked anyway. this results in a lot of
    // double-checks for no reason.
    auto parent(ao.parent_name());
    while (parent) {
        qname pqn(*parent);
        const auto i(model_.objects().find(pqn));
        if (i == model_.objects().end()) {
            std::ostringstream s;
            s << orphan_object << ": " << ao.name().simple_name()
              << ". parent: " << pqn.simple_name();

            BOOST_LOG_SEV(lg, error) << s.str();
            BOOST_THROW_EXCEPTION(resolution_error(s.str()));
        }
        parent = i->second->parent_name();
    }
}

void resolver::validate_refinements(const concept& c) const {
    for (const auto& qn : c.refines()) {
        const auto i(model_.concepts().find(qn));
        if (i == model_.concepts().end()) {
            std::ostringstream stream;
            stream << orphan_concept << ". concept: "
                   << c.name().simple_name() << ". refined concept: "
                   << qn.simple_name();

            BOOST_LOG_SEV(lg, error) << stream.str();
            BOOST_THROW_EXCEPTION(resolution_error(stream.str()));
        }
    }
}

qname resolver::resolve_partial_type(const qname& n) const {
    qname r(n);

    // first try the type as it was read originally.
    const auto& objects(model_.objects());
    r.meta_type(meta_types::value_object);
    auto i(objects.find(r));
    if (i != objects.end())
        return r;

    // then try setting module path to the target one
    r.external_module_path(model_.name().external_module_path());
    i = objects.find(r);
    if (i != objects.end())
        return r;

    // now try all available module paths from references
    for (const auto& qn : model_.references()) {
        r.external_module_path(qn.external_module_path());
        i = objects.find(r);
        if (i != objects.end())
            return r;
    }

    // reset external module path
    r.external_module_path(std::list<std::string>{});

    // its not a object, could it be a primitive?
    r.meta_type(meta_types::primitive);
    const auto& primitives(model_.primitives());
    auto j(primitives.find(r));
    if (j != primitives.end())
        return r;

    // try enumerations
    const auto& enumerations(model_.enumerations());
    r.meta_type(meta_types::enumeration);
    auto k(enumerations.find(r));
    if (k != enumerations.end())
        return r;

    // then try setting module path to the target one
    r.external_module_path(model_.name().external_module_path());
    k = enumerations.find(r);
    if (k != enumerations.end())
        return r;

    // now try all available module paths from references
    for (const auto& qn : model_.references()) {
        r.external_module_path(qn.external_module_path());
        k = enumerations.find(r);
        if (k != enumerations.end())
            return r;
    }

    if (r.model_name().empty()) {
        // it could be a type defined in this model
        r.meta_type(meta_types::value_object);
        r.model_name(model_.name().model_name());
        r.external_module_path(model_.name().external_module_path());
        i = objects.find(r);
        if (i != objects.end())
            return r;

        r.meta_type(meta_types::enumeration);
        auto k(enumerations.find(r));
        if (k != enumerations.end())
            return r;
    }

    BOOST_LOG_SEV(lg, error) << undefined_type << n;
    BOOST_THROW_EXCEPTION(resolution_error(undefined_type + n.simple_name()));
}

void resolver::resolve_partial_type(nested_qname& n) const {
    auto children(n.children());
    for (auto i(children.begin()); i != children.end(); ++i)
        resolve_partial_type(*i);
    n.children(children);

    qname qn(resolve_partial_type(n.type()));
    BOOST_LOG_SEV(lg, debug) << "Resolved type " << n.type()
                             << ". Result: " << qn;
    n.type(qn);
}

std::list<property> resolver::resolve_properties(const qname& owner,
    const std::list<property>& unresolved_properties) const {
    std::list<property> r;

    for (auto p : unresolved_properties) {
        try {
            auto t(p.type());
            resolve_partial_type(t);
            p.type(t);
            r.push_back(p);
        } catch (boost::exception& e) {
            std::ostringstream s;
            s << "Owner type name: " << owner.simple_name()
              << " Property name: " << p.name()
              << " Property type: " << p.type();
            e << errmsg_info(s.str());
            throw;
        }
    }
    return r;
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

        c.properties(resolve_properties(c.name(), c.properties()));
        validate_refinements(c);
    }
}

void resolver::resolve_objects() {
    for (auto& pair : model_.objects()) {
        auto& o(*pair.second);
        if (o.generation_type() == generation_types::no_generation)
            return;

        validate_inheritance_graph(o);
        o.properties(resolve_properties(o.name(), o.properties()));

        //FIXME: start of biggest hack ever
        if (o.modeled_concepts().empty())
            return;

        std::list<qname> expanded_modeled_concepts;
        for (const auto& qn : o.modeled_concepts())
            expand_concept_hierarchy(qn, expanded_modeled_concepts);

        // std::cout << "type: " << o.name().type_name() << std::endl;

        // std::cout << "after expand: " << expanded_modeled_concepts.size()
        //           << std::endl
        //           << " " << expanded_modeled_concepts << std::endl;

        o.modeled_concepts().clear();
        for (const auto& qn : expanded_modeled_concepts)
            o.modeled_concepts().push_back(qn);

        // std::cout << "modeled: " << o.modeled_concepts().size() << std::endl;
    }

    //FIXME: biggest hack ever - continued
    for (auto& pair : model_.objects()) {
        auto& o(*pair.second);

        if (o.modeled_concepts().empty())
            return;

        // std::cout << "type2: " << o.name().type_name() << std::endl;
        // std::cout << "modeled: " << o.modeled_concepts().size()
        // << std::endl;

        std::set<qname> mc;
        for (const auto& qn : o.modeled_concepts())
            mc.insert(qn);

        std::set<qname> pmc;
        auto parent(o.parent_name());
        while (parent) {
            qname pqn(*parent);
            const auto i(model_.objects().find(pqn));
            for (const auto& qn : i->second->modeled_concepts())
                pmc.insert(qn);
            parent = i->second->parent_name();
        }

        // std::cout << "pmc: " << pmc << std::endl
        //           << "mc: " << mc  << std::endl;

        std::set<qname> result;
        std::set_difference(mc.begin(), mc.end(), pmc.begin(), pmc.end(),
            std::inserter(result, result.end()));

        // std::cout << "result: " << result << std::endl;
        auto tmp(o.modeled_concepts());
        o.modeled_concepts().clear();
        for (const auto& qn : tmp) {
            if (result.find(qn) != result.end())
                o.modeled_concepts().push_back(qn);
        }
    }
}

void resolver::resolve() {
    require_not_has_resolved();
    resolve_concepts();
    resolve_objects();
    has_resolved_ = true;
}

} }
