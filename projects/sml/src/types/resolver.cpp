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
#include <sstream>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/resolution_error.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/io/nested_qname_io.hpp"
#include "dogen/sml/io/property_io.hpp"
#include "dogen/sml/io/pod_io.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/types/resolver.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("sml.resolver"));

const std::string empty;
const std::string orphan_pod("Pod's parent could not be located: ");
const std::string orphan_concept("Refined concept could not be located: ");
const std::string undefined_type("Pod has property with undefined type: ");
const std::string missing_dependency("Cannot find dependency: ");
const std::string model_resolved("Resolution has already been done for model");

typedef boost::error_info<struct tag_errmsg, std::string> errmsg_info;

}

namespace dogen {
namespace sml {

resolver::resolver(model& m) : model_(m), has_resolved_(false) { }

void resolver::validate_inheritance_graph(const pod& p) const {
    // FIXME: we should really just check that the parent exists since
    // we know all pods get checked anyway. this results in a lot of
    // double-checks for no reason.
    auto parent(p.parent_name());
    while (parent) {
        qname pqn(*parent);
        const auto i(model_.pods().find(pqn));
        if (i == model_.pods().end()) {
            std::ostringstream stream;
            stream << orphan_pod << ". pod: "
                   << p.name().type_name() << ". parent: "
                   << pqn.type_name();
            BOOST_LOG_SEV(lg, error) << stream.str();
            BOOST_THROW_EXCEPTION(resolution_error(stream.str()));
        }
        parent = i->second.parent_name();
    }
}

void resolver::validate_refinements(const concept& c) const {
    for (const auto& qn : c.refines()) {
        const auto i(model_.concepts().find(qn));
        if (i == model_.concepts().end()) {
            std::ostringstream stream;
            stream << orphan_concept << ". concept: "
                   << c.name().type_name() << ". refined concept: "
                   << qn.type_name();

            BOOST_LOG_SEV(lg, error) << stream.str();
            BOOST_THROW_EXCEPTION(resolution_error(stream.str()));
        }
    }
}

qname resolver::resolve_partial_type(const qname& n) const {
    qname r(n);

    // first try the type as it was read originally.
    const auto& pods(model_.pods());
    r.meta_type(meta_types::pod);
    auto i(pods.find(r));
    if (i != pods.end())
        return r;

    // then try setting module path to the target one
    r.external_module_path(model_.external_module_path());
    i = pods.find(r);
    if (i != pods.end())
        return r;

    // now try all available module paths from references
    for (const auto& pair : references_) {
        const auto ref(pair.second);
        r.external_module_path(ref.external_module_path());
        i = pods.find(r);
        if (i != pods.end())
            return r;
    }

    // reset external module path
    r.external_module_path(std::list<std::string>{});

    // its not a pod, could it be a primitive?
    const auto& primitives(model_.primitives());
    r.meta_type(meta_types::primitive);
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
    r.external_module_path(model_.external_module_path());
    k = enumerations.find(r);
    if (k != enumerations.end())
        return r;

    // now try all available module paths from references
    for (const auto& pair : references_) {
        const auto ref(pair.second);
        r.external_module_path(ref.external_module_path());
        k = enumerations.find(r);
        if (k != enumerations.end())
            return r;
    }

    if (r.model_name().empty()) {
        // it could be a type defined in this model
        r.meta_type(meta_types::pod);
        r.model_name(model_.name());
        r.external_module_path(model_.external_module_path());
        i = pods.find(r);
        if (i != pods.end())
            return r;

        const auto& enumerations(model_.enumerations());
        r.meta_type(meta_types::enumeration);
        auto k(enumerations.find(r));
        if (k != enumerations.end())
            return r;
    }

    BOOST_LOG_SEV(lg, error) << undefined_type << n;
    BOOST_THROW_EXCEPTION(resolution_error(undefined_type + n.type_name()));
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
            auto t(p.type_name());
            resolve_partial_type(t);
            p.type_name(t);
            r.push_back(p);
        } catch (boost::exception& e) {
            std::ostringstream s;
            s << "Pod: " << owner.type_name()
              << " Property: " << p.name()
              << " type: " << p.type_name();
            e << errmsg_info(s.str());
            throw;
        }
    }
    return r;
}

void resolver::resolve_references() {
    for (auto& pair : model_.dependencies()) {
        auto& ref(pair.second);
        const auto i(references_.find(ref.model_name()));

        if (i == references_.end()) {
            BOOST_LOG_SEV(lg, error) << missing_dependency << ref.model_name();
            BOOST_THROW_EXCEPTION(
                resolution_error(missing_dependency + ref.model_name()));
        }
        ref = i->second;
    }
}

void resolver::require_not_has_resolved() const {
    if (!has_resolved())
        return;

    BOOST_LOG_SEV(lg, error) << model_resolved;
    BOOST_THROW_EXCEPTION(resolution_error(model_resolved));
}

void resolver::add_reference(const reference& ref) {
    require_not_has_resolved();
    references_.insert(std::make_pair(ref.model_name(), ref));
}

void resolver::resolve_concepts() {
    for (auto& pair : model_.concepts()) {
        concept& c(pair.second);
        c.properties(resolve_properties(c.name(), c.properties()));
        validate_refinements(c);
    }
}

void resolver::resolve_pods() {
    for (auto& pair : model_.pods()) {
        pod& p(pair.second);
        if (p.generation_type() == generation_types::no_generation)
            continue;

        validate_inheritance_graph(p);
        p.properties(resolve_properties(p.name(), p.properties()));
    }
}

void resolver::resolve() {
    require_not_has_resolved();
    resolve_references();
    resolve_pods();
    resolve_concepts();
    has_resolved_ = true;
}

} }
