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
#include "dogen/dia/serialization/diagram_ser.hpp"
#include "dogen/sml/serialization/model_ser.hpp"
#include "dogen/utility/serialization/xml_helper.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/engine/types/persister.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("engine.persister"));

const std::string empty;
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
namespace engine {

persister::persister(const config::settings& settings) :
    settings_(settings) {}

std::string persister::extension(config::archive_types archive_type,
    const std::string& model) const {
    using config::archive_types;
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
    BOOST_LOG_SEV(lg, error) << invalid_archive_type;
    BOOST_THROW_EXCEPTION(
        dogen::utility::exception::invalid_enum_value(invalid_archive_type));
}

bool persister::is_save_dia_model_enabled() const {
    return settings_.troubleshooting().save_dia_model() !=
        config::archive_types::invalid;
}

bool persister::is_save_sml_model_enabled() const {
    return settings_.troubleshooting().save_sml_model() !=
        config::archive_types::invalid;
}

void persister::
save_diagram(const dia::diagram& d, const std::string& name) const {
    if (!is_save_dia_model_enabled())
        return;

    boost::filesystem::path p(settings_.troubleshooting().debug_dir());
    p /= name;

    using config::archive_types;
    archive_types at(settings_.troubleshooting().save_dia_model());
    p.replace_extension(extension(at, dia_model));
    BOOST_LOG_SEV(lg, info) << "Saving Dia model to path: " << p;

    using dogen::utility::serialization::xml_serialize;
    xml_serialize<dia::diagram>(p, d);
}

void persister::
save_model(const sml::model& m, const std::string& prefix) const {
    if (!is_save_sml_model_enabled())
        return;

    boost::filesystem::path p(settings_.troubleshooting().debug_dir());
    p /= prefix + m.name();

    using config::archive_types;
    archive_types at(settings_.troubleshooting().save_sml_model());
    p.replace_extension(extension(at, sml_model));
    BOOST_LOG_SEV(lg, info) << "Saving SML model to path: " << p;

    using dogen::utility::serialization::xml_serialize;
    xml_serialize<sml::model>(p, m);
}

} }
