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
#include <boost/filesystem.hpp>
#include "dogen/sml/types/merger.hpp"
#include "dogen/generator/modeling/dia_to_sml.hpp"
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/utility/serialization/xml_helper.hpp"
#include "dogen/dia/xml/hydrator.hpp"
#include "dogen/dia/serialization/diagram_ser.hpp"
#include "dogen/sml/serialization/model_ser.hpp"
#include "dogen/sml/types/primitive_model_factory.hpp"
#include "dogen/sml/types/std_model_factory.hpp"
#include "dogen/sml/types/boost_model_factory.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/generator/modeling/director.hpp"

using namespace dogen::utility::log;

namespace {

static logger lg(logger_factory("director"));

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
namespace generator {
namespace modeling {

director::director(const config::settings& settings)
    : settings_(settings), verbose_(settings_.troubleshooting().verbose()) { }

std::string director::
extension(utility::serialization::archive_types archive_type,
    const std::string& model) const {
    using utility::serialization::archive_types;
    switch (archive_type) {
    case archive_types::xml:
        return xml_extension + model;
    case archive_types::text:
        return text_extension + model;
    case archive_types::binary:
        return binary_extension + model;
    default:
        break;
    }
    throw dogen::utility::exception::invalid_enum_value(invalid_archive_type);
}

bool director::is_save_dia_model_enabled() const {
    return settings_.troubleshooting().save_dia_model() !=
        utility::serialization::archive_types::invalid;
}

void director::
save_diagram(const dia::diagram& d, const std::string& name) const {
    if (!is_save_dia_model_enabled())
        return;

    boost::filesystem::path p(settings_.troubleshooting().debug_dir());
    p /= name;

    using utility::serialization::archive_types;
    archive_types at(settings_.troubleshooting().save_dia_model());
    p.replace_extension(extension(at, dia_model));
    BOOST_LOG_SEV(lg, info) << "Saving Dia model to path: " << p;

    using dogen::utility::serialization::xml_serialize;
    xml_serialize<dia::diagram>(p, d);
}

dia::diagram
director::hydrate_diagram(const boost::filesystem::path& path) const {
    dia::xml::hydrator h(path);
    dia::diagram r(h.hydrate());
    save_diagram(r, path.stem().string());
    return r;
}

bool director::is_save_sml_model_enabled() const {
    return settings_.troubleshooting().save_sml_model() !=
        utility::serialization::archive_types::invalid;
}

void director::
save_model(const sml::model& m, const std::string& prefix) const {
    if (!is_save_sml_model_enabled())
        return;

    boost::filesystem::path p(settings_.troubleshooting().debug_dir());
    p /= prefix + m.name();

    using utility::serialization::archive_types;
    archive_types at(settings_.troubleshooting().save_sml_model());
    p.replace_extension(extension(at, sml_model));
    BOOST_LOG_SEV(lg, info) << "Saving SML model to path: " << p;

    using dogen::utility::serialization::xml_serialize;
    xml_serialize<sml::model>(p, m);
}

sml::pod director::
create_key_system_pod(const sml::pod& p, const bool is_versioned) const {
    sml::qualified_name qn;
    qn.type_name(p.name().type_name() + "_" +
        (is_versioned ? versioned_name : unversioned_name));
    qn.model_name(p.name().model_name());
    qn.package_path(p.name().package_path());
    qn.external_package_path(p.name().external_package_path());
    qn.meta_type(sml::meta_types::pod);

    sml::pod r;
    r.name(qn);
    r.generation_type(p.generation_type());

    const auto vtc(sml::category_types::versioned_key);
    const auto uvtc(sml::category_types::unversioned_key);
    r.category_type(is_versioned ? vtc : uvtc);

    auto props(r.properties());

    sml::qualified_name uint_qn;
    uint_qn.type_name(uint_name);
    uint_qn.meta_type(sml::meta_types::primitive);

    sml::property id;
    id.name(id_name);

    sml::nested_qualified_name nqn;
    nqn.type(uint_qn);
    id.type_name(nqn);
    props.push_back(id);

    if (is_versioned) {
        sml::property version;
        version.name(version_name);

        sml::nested_qualified_name nqn2;
        nqn2.type(uint_qn);
        version.type_name(nqn2);
        props.push_back(version);
    }
    r.properties(props);
    return r;
}

void director::inject_system_types(sml::model& m) const {
    if (settings_.cpp().disable_versioning()) {
        BOOST_LOG_SEV(lg, warn) << "Keys are NOT enabled, "
                                << "NOT injecting them into model.";
        return;
    } else {
        BOOST_LOG_SEV(lg, info) << "Keys are enabled, "
                                << "so injecting them into model.";
    }

    const auto old_pods(m.pods());
    if (old_pods.empty())
        return;

    std::unordered_map<sml::qualified_name, sml::pod> new_pods;
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

            sml::nested_qualified_name nqn;
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

sml::model director::to_sml(const dia::diagram& d, config::reference ref,
    const bool is_target) const {
    const std::string file_name(ref.path().stem().string());
    const std::string epp(ref.external_package_path());
    const std::string name(settings_.modeling().disable_model_package() ?
        empty : file_name);

    using dogen::generator::modeling::dia_to_sml;
    dia_to_sml dia_to_sml(d, name, epp, is_target, verbose_);

    sml::model m(dia_to_sml.transform());
    inject_system_types(m);

    save_model(m, empty);
    return std::move(m);
}

bool director::has_generatable_types(const sml::model& m) const {
    bool r(false);

    auto lambda([](sml::generation_types gt) {
            return
                gt == sml::generation_types::full_generation ||
                gt == sml::generation_types::partial_generation;
        });

    for (const auto pair : m.pods()) {
        const auto p(pair.second);
        if (lambda(p.generation_type())) {
            r = true;
            break;
        }
    }

    for (const auto pair : m.enumerations()) {
        const auto e(pair.second);
        if (lambda(e.generation_type())) {
            r = true;
            break;
        }
    }

    for (const auto pair : m.exceptions()) {
        const auto e(pair.second);
        if (lambda(e.generation_type())) {
            r = true;
            break;
        }
    }

    return r;
}

boost::optional<sml::model> director::create_model() const {
    sml::merger merger(verbose_, settings_.sql().schema_name());
    merger.add(sml::primitive_model_factory::create());
    merger.add(sml::std_model_factory::create());
    merger.add(sml::boost_model_factory::create());

    using sml::model;
    const auto lambda([&](config::reference ref, bool is_target) -> model {
            const dia::diagram d(hydrate_diagram(ref.path()));
            return model(to_sml(d, ref, is_target));
        });

    const bool is_target(true);
    for (const auto r : settings_.modeling().references())
        merger.add(lambda(r, !is_target));

    config::reference tr;
    tr.path(settings_.modeling().target());
    tr.external_package_path(settings_.modeling().external_package_path());
    merger.add_target(lambda(tr, is_target));
    model m(merger.merge());

    BOOST_LOG_SEV(lg, debug) << "Merged model: " << m;
    save_model(m, merged);

    BOOST_LOG_SEV(lg, debug) << "Totals: pods: " << m.pods().size()
                             << " enumerations: " << m.enumerations().size()
                             << " exceptions: " << m.exceptions().size()
                             << " primitives: " << m.primitives().size();

    if (has_generatable_types(m))
        return boost::optional<model>(m);

    BOOST_LOG_SEV(lg, warn) << "No generatable types found.";

    return boost::optional<model>();
}

} } }
