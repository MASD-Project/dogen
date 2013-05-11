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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/types/injection_error.hpp"
#include "dogen/sml/types/injector.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("sml.injector"));

const std::string empty;
const std::string merged("merged_");
const std::string xml_extension(".xml");
const std::string text_extension(".txt");
const std::string binary_extension(".bin");
const std::string dia_model("dia");
const std::string sml_model("sml");
const std::string versioned_name("versioned_key");
const std::string unversioned_name("unversioned_key");
const std::string uint_name("unsigned int");
const std::string id_name("id");
const std::string version_name("version");
const std::string missing_identity_attribute(
    "Expected entity to have at least one identity attribute: ");
const std::string duplicate_qname(
    "Attempt to add pod with a name that already exists in model: ");

}

namespace dogen {
namespace sml {

pod injector::create_key(const qname& qn, const generation_types gt,
    const std::vector<property>& properties, const bool versioned) const {

    qname kqn;
    kqn.type_name(qn.type_name() + "_" +
        (versioned ? versioned_name : unversioned_name));
    kqn.model_name(qn.model_name());
    kqn.package_path(qn.package_path());
    kqn.external_package_path(qn.external_package_path());
    kqn.meta_type(meta_types::pod);

    pod r;
    r.name(kqn);
    r.generation_type(gt);
    r.pod_type(pod_types::value);

    const auto vtc(category_types::versioned_key);
    const auto uvtc(category_types::unversioned_key);
    r.category_type(versioned ? vtc : uvtc);
    r.properties(properties);

    if (versioned)
        inject_version(r);

    BOOST_LOG_SEV(lg, debug) << "Created key: " << kqn.type_name();
    return r;
}

void injector::inject_keys(model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Injecting keys.";

    std::list<pod> keys;
    for (const auto& pair : m.pods()) {
        const auto& pod(pair.second);

        if (!pod.is_keyed())
            continue;

        std::vector<property> identity_properties;
        for (const auto& prop : pod.properties()) {
            if (prop.is_identity_attribute())
                identity_properties.push_back(prop);
        }

        if (identity_properties.empty()) {
            BOOST_LOG_SEV(lg, error) << missing_identity_attribute
                                     << pod.name();

            BOOST_THROW_EXCEPTION(injection_error(missing_identity_attribute +
                    boost::lexical_cast<std::string>(pod.name())));
        }

        const bool unversioned(false);
        const auto gt(pod.generation_type());
        const auto qn(pod.name());
        keys.push_back(create_key(qn, gt, identity_properties, unversioned));

        const bool versioned(true);
        if (pod.is_versioned())
            keys.push_back(create_key(qn, gt, identity_properties, versioned));
    }

    for (const auto& k : keys) {
        const auto r(m.pods().insert(std::make_pair(k.name(), k)));
        if (!r.second) {
            BOOST_LOG_SEV(lg, error) << duplicate_qname << k.name();

            BOOST_THROW_EXCEPTION(injection_error(duplicate_qname +
                    boost::lexical_cast<std::string>(k.name())));
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Done injecting keys. Total: " << keys.size();

}

void injector::inject_version(pod& p) const {
    BOOST_LOG_SEV(lg, debug) << "Injecting version property to type: "
                             << p.name();

    qname qn;
    qn.type_name(uint_name);
    qn.meta_type(meta_types::primitive);

    nested_qname nqn;
    nqn.type(qn);

    property v;
    v.name(version_name);
    v.type_name(nqn);

    p.properties().push_back(v);
}

void injector::inject_version(model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Injecting version property.";

    for (auto& pair : m.pods()) {
        auto& pod(pair.second);

        if (pod.is_versioned())
            inject_version(pod);
    }

    BOOST_LOG_SEV(lg, debug) << "Done injecting version property.";
}

void injector::inject(model& m) const {
    inject_version(m);
    inject_keys(m);
}

} }
