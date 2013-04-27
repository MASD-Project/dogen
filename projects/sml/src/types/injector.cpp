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
#include "dogen/utility/log/logger.hpp"
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
const std::string invalid_archive_type("Invalid or unexpected archive type");

}

namespace dogen {
namespace sml {

injector::injector() : add_versioning_types_(true) {}

injector::injector(const bool add_versioning_types)
    : add_versioning_types_(add_versioning_types) { }

pod injector::
create_key_system_pod(const sml::pod& p, const bool is_versioned) const {
    sml::qname qn;
    qn.type_name(p.name().type_name() + "_" +
        (is_versioned ? versioned_name : unversioned_name));
    qn.model_name(p.name().model_name());
    qn.package_path(p.name().package_path());
    qn.external_package_path(p.name().external_package_path());
    qn.meta_type(sml::meta_types::pod);

    sml::pod r;
    r.name(qn);
    r.generation_type(p.generation_type());
    r.pod_type(sml::pod_types::value);

    const auto vtc(sml::category_types::versioned_key);
    const auto uvtc(sml::category_types::unversioned_key);
    r.category_type(is_versioned ? vtc : uvtc);

    auto props(r.properties());

    sml::qname uint_qn;
    uint_qn.type_name(uint_name);
    uint_qn.meta_type(sml::meta_types::primitive);

    sml::property id;
    id.name(id_name);

    sml::nested_qname nqn;
    nqn.type(uint_qn);
    id.type_name(nqn);
    props.push_back(id);

    if (is_versioned) {
        sml::property version;
        version.name(version_name);

        sml::nested_qname nqn2;
        nqn2.type(uint_qn);
        version.type_name(nqn2);
        props.push_back(version);
    }
    r.properties(props);
    return r;
}

void injector::inject_legacy_keys(model& m) const {
    if (!add_versioning_types_) {
        BOOST_LOG_SEV(lg, warn) << "Keys are NOT enabled, "
                                << "NOT injecting them into model.";
        return;
    }

    BOOST_LOG_SEV(lg, info) << "Keys are enabled, "
                            << "so injecting them into model.";

    const auto old_pods(m.pods());
    if (old_pods.empty())
        return;

    std::unordered_map<sml::qname, sml::pod> new_pods;
    const bool is_versioned(true);
    for (auto i(std::begin(old_pods)); i != std::end(old_pods); ++i) {
        auto pod(i->second);

        if (pod.parent_name()) {
            new_pods.insert(std::make_pair(pod.name(), pod));
            continue;
        }

        auto props(pod.properties());
        if (pod.pod_type() == sml::pod_types::entity) {
            const auto versioned_pod(create_key_system_pod(pod, is_versioned));
            new_pods.insert(std::make_pair(versioned_pod.name(), versioned_pod));

            sml::property vk_prop;
            vk_prop.name(versioned_name);

            sml::nested_qname nqn;
            nqn.type(versioned_pod.name());
            vk_prop.type_name(nqn);

            const auto unversioned_pod(create_key_system_pod(pod, !is_versioned));
            new_pods.insert(
                std::make_pair(unversioned_pod.name(), unversioned_pod));
            props.push_back(vk_prop);
        }

        pod.properties(props);
        new_pods.insert(std::make_pair(pod.name(), pod));
    }
    m.pods(new_pods);
}

void injector::inject_versioning(model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Injecting version property.";

    if (m.pods().empty())
        return;

    for (auto& pair : m.pods()) {
        auto& pod(pair.second);

        if (!pod.is_versioned())
            continue;

        sml::qname qn;
        qn.type_name(uint_name);
        qn.meta_type(sml::meta_types::primitive);

        sml::nested_qname nqn;
        nqn.type(qn);

        sml::property v;
        v.name(version_name);
        v.type_name(nqn);

        pod.properties().push_back(v);
    }
}

void injector::inject(model& m) const {
    inject_legacy_keys(m);
    inject_versioning(m);
}

} }
