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
#include <iostream>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/merging_error.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/sml/io/enumeration_io.hpp"
#include "dogen/sml/io/qualified_name_io.hpp"
#include "dogen/sml/io/nested_qualified_name_io.hpp"
#include "dogen/sml/io/primitive_io.hpp"
#include "dogen/sml/io/property_io.hpp"
#include "dogen/sml/io/pod_io.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/types/merger.hpp"

using namespace dogen::utility::log;

namespace {

static logger lg(logger_factory("merger"));

const std::string orphan_pod("Pod's parent could not be located: ");
const std::string undefined_type("Pod has property with undefined type: ");
const std::string missing_target("No target model found");

typedef boost::error_info<struct tag_errmsg, std::string> errmsg_info;

}

namespace dogen {
namespace sml {
namespace utility {

merger::merger(const bool verbose, const std::string& schema_name)
    : verbose_(verbose), has_target_(false), schema_name_(schema_name) { }

void merger::resolve_parent(const pod& pod) {
    const auto pods(merged_model_.pods());
    auto parent(pod.parent_name());

    while (parent) {
        qualified_name pqn(*parent);
        const auto i(pods.find(pqn));
        if (i == pods.end()) {
            std::ostringstream stream;
            stream << orphan_pod << ". pod: "
                   << pod.name().type_name() << ". parent: "
                   << pqn.type_name();
            BOOST_THROW_EXCEPTION(merging_error(stream.str()));
        }

        parent = i->second.parent_name();
    }
}

void
merger::resolve_partial_type(nested_qualified_name& n) const {
    auto children(n.children());
    for (auto i(children.begin()); i != children.end(); ++i)
        resolve_partial_type(*i);
    n.children(children);

    const auto pods(merged_model_.pods());
    qualified_name r(n.type());

    auto lambda([&]() {
            BOOST_LOG_SEV(lg, debug) << "Resolved type " << n.type()
                                     << ". Result: " << r;
            n.type(r);
        });

    // first try the type as it was read originally.
    r.meta_type(meta_types::pod);
    auto i(pods.find(r));
    if (i != pods.end())
        return lambda();

    // then try setting package path to the target one
    r.external_package_path(merged_model_.external_package_path());
    i = pods.find(r);
    if (i != pods.end())
        return lambda();

    // now try all available package paths
    for (const auto& pair : models_) {
        const auto m(pair.second);
        r.external_package_path(m.external_package_path());
        i = pods.find(r);
        if (i != pods.end())
            return lambda();
    }

    // reset external package path
    r.external_package_path(std::list<std::string>{});

    // its not a pod, could it be a primitive?
    const auto primitives(merged_model_.primitives());
    r.meta_type(meta_types::primitive);
    auto j(primitives.find(r));
    if (j != primitives.end())
        return lambda();

    if (r.model_name().empty() || r.model_name() == merged_model_.name()) {
        // it could be a type defined in this model
        r.meta_type(meta_types::pod);
        r.model_name(merged_model_.name());
        r.external_package_path(merged_model_.external_package_path());
        i = pods.find(r);
        if (i != pods.end())
            return lambda();

        // try enumerations
        const auto enumerations(merged_model_.enumerations());
        BOOST_LOG_SEV(lg, debug) << enumerations;

        r.meta_type(meta_types::enumeration);
        BOOST_LOG_SEV(lg, debug) << r;
        auto k(enumerations.find(r));
        if (k != enumerations.end())
            return lambda();
    }

    BOOST_LOG_SEV(lg, error) << undefined_type << n;
    BOOST_THROW_EXCEPTION(merging_error(undefined_type + n.type().type_name()));
}

std::vector<property>
merger::resolve_properties(const pod& pod) {
    auto r(pod.properties());

    for (unsigned int i(0); i < r.size(); ++i) {
        property property(r[i]);

        try {
            auto t(property.type_name());
            resolve_partial_type(t);
            property.type_name(t);
            r[i] = property;
        } catch (boost::exception& e) {
            std::ostringstream s;
            s << "Pod: " << pod.name().type_name()
              << " Property: " << property.name()
              << " type: " << property.type_name();
            e << errmsg_info(s.str());
            throw;
        }
    }
    return r;
}

void merger::resolve() {
    auto pods(merged_model_.pods());

    for (auto i(pods.begin()); i != pods.end(); ++i) {
        const qualified_name qualified_name(i->first);
        pod& pod(i->second);
        if (pod.generation_type() == generation_types::no_generation)
            continue;

        resolve_parent(pod);
        pod.properties(resolve_properties(pod));
    }
    merged_model_.pods(pods);
}

std::unordered_map<std::string, reference>
merger::compute_dependencies() const {
    if (!has_target_) {
        BOOST_LOG_SEV(lg, error) << "Combining when has_target is false.";
        BOOST_THROW_EXCEPTION(merging_error(missing_target));
    }

    const auto i(models_.find(merged_model_.name()));
    if (i == models_.end()) {
        BOOST_LOG_SEV(lg, error) << "Combining when target model not in map.";
        BOOST_THROW_EXCEPTION(merging_error(missing_target));
    }

    std::unordered_map<std::string, reference> r;
    for (const auto pair : i->second.dependencies()) {
        const auto original_dependency(pair.second);
        const auto i(models_.find(original_dependency.model_name()));
        if (i == models_.end()) {
            BOOST_LOG_SEV(lg, error) << "Cannot find target dependency: "
                                     << original_dependency.model_name();
            BOOST_THROW_EXCEPTION(merging_error(missing_target));
        }

        const auto m(i->second);
        reference ref(m.name(), m.external_package_path(), m.is_system());
        r.insert(std::make_pair(m.name(), ref));
    }
    return r;
}

void merger::combine() {
    merged_model_.dependencies(compute_dependencies());

    auto pods(merged_model_.pods());
    auto primitives(merged_model_.primitives());
    auto enumerations(merged_model_.enumerations());
    auto exceptions(merged_model_.exceptions());

    for (const auto pair : models_) {
        const auto m(pair.second);
        BOOST_LOG_SEV(lg, info) << "Combining model: '" << m.name()
                                << "' pods: " << m.pods().size()
                                << " primitives: " << m.primitives().size()
                                << " enumerations: " << m.enumerations().size()
                                << " exceptions: " << m.exceptions().size();


        for (const auto p : m.pods()) {
            if (p.first.model_name() != m.name()) {
                std::ostringstream stream;
                stream << "Pod does not belong to this model. Model name: '"
                       << m.name() << "'. Pod qualified name: "
                       << p.first;
                BOOST_LOG_SEV(lg, error) << stream.str();
                BOOST_THROW_EXCEPTION(merging_error(stream.str()));
            }

            if (p.first.meta_type() != meta_types::pod) {
                std::ostringstream stream;
                stream << "Pod has incorrect meta_type: '" << p.first;
                BOOST_LOG_SEV(lg, error) << stream.str();
                BOOST_THROW_EXCEPTION(merging_error(stream.str()));
            }

            if (p.first != p.second.name()) {
                std::ostringstream stream;
                stream << "Inconsistency between key and value qualified names: "
                       << " key: " << p.first << " value: " << p.second.name();
                BOOST_LOG_SEV(lg, error) << stream.str();
                BOOST_THROW_EXCEPTION(merging_error(stream.str()));
            }

            pods.insert(p);
        }

        for (const auto p : m.primitives()) {
            primitives.insert(p);
        }

        for (const auto p : m.enumerations()) {
            enumerations.insert(p);
        }

        for (const auto p : m.exceptions()) {
            exceptions.insert(p);
        }
    }
    merged_model_.pods(pods);
    merged_model_.primitives(primitives);
    merged_model_.enumerations(enumerations);
    merged_model_.exceptions(exceptions);
    merged_model_.external_package_path(external_package_path_);
    merged_model_.schema_name(schema_name_);
}

void merger::add_target(model model) {
    if (has_target_) {
        std::ostringstream stream;
        stream << "Only one target expected. Last target model name: '"
               << merged_model_.name() << "'. New target model name: "
               << model.name();
        BOOST_LOG_SEV(lg, error) << stream.str();
        BOOST_THROW_EXCEPTION(merging_error(stream.str()));
    }

    merged_model_.name(model.name());
    merged_model_.leaves(model.leaves());

    has_target_ = true;
    external_package_path_ = model.external_package_path();

    add(model);
    BOOST_LOG_SEV(lg, debug) << "added target model: " << model.name();
}

void merger::add(model model) {

    BOOST_LOG_SEV(lg, debug) << "adding model: " << model.name();
    models_.insert(std::make_pair(model.name(), model));
}

model merger::merge() {
    combine();
    resolve();
    BOOST_LOG_SEV(lg, debug) << "merged model: " << merged_model_;
    return merged_model_;
}

} } }
