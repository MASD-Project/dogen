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
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/types/meta_data/reader.hpp"
#include "dogen/sml/types/meta_data/writer.hpp"
#include "dogen/sml/types/meta_data/enrichment_error.hpp"
#include "dogen/cpp/types/meta_data/traits.hpp"
#include "dogen/cpp/types/meta_data/backend_enricher.hpp"

namespace {

std::string id("cpp.backend_enricher");
std::string source_directory("src");
std::string include_directory("include");
std::string header_file_extension("hpp");
std::string implementation_file_extension("cpp");
const std::string could_not_find_module("Could not find module: ");
const std::string no_containing_module_supplied(
    "Expected containing module for type: ");

std::list<std::string> empty_dependencies;

using namespace dogen::utility::log;
static logger lg(logger_factory(id));

}

namespace dogen {
namespace cpp {
namespace meta_data {

/**
 * @brief Obtains the containing module.
 *
 * @pre Must have a containing module.
 */
template<typename IdentifiableContainable>
sml::module containing_module(const sml::model& m,
    const IdentifiableContainable& ic) {

    if (!ic.containing_module()) {
        const auto sn(ic.name().simple_name());
        BOOST_LOG_SEV(lg, error) << no_containing_module_supplied << sn;
        BOOST_THROW_EXCEPTION(sml::meta_data::enrichment_error(
                no_containing_module_supplied + sn));
    }

    const auto qn(*ic.containing_module());
    const auto i(m.modules().find(qn));
    if (i == m.modules().end()) {
        const auto sn(qn.simple_name());
        BOOST_LOG_SEV(lg, error) << could_not_find_module << sn;
        BOOST_THROW_EXCEPTION(sml::meta_data::enrichment_error(
                could_not_find_module + sn));
    }
    return i->second;
}

std::string backend_enricher::id() const {
    return ::id;
}

std::list<std::string> backend_enricher::dependencies() const {
    return empty_dependencies;
}

bool backend_enricher::is_first_stage_enrichment(
    const sml::meta_data::enrichment_types et) const {
    if (et != sml::meta_data::enrichment_types::first_stage) {
        BOOST_LOG_SEV(lg, debug) << "Only first stage enrichment supported.";
        return false;
    }
    return true;
}

void backend_enricher::
setup_defaults(boost::property_tree::ptree& target) const {
    sml::meta_data::writer writer(target);

    writer.add_if_key_not_found(traits::enabled, traits::bool_true);
    writer.add_if_key_not_found(traits::split_project, traits::bool_false);
    writer.add_if_key_not_found(traits::source_directory, source_directory);
    writer.add_if_key_not_found(traits::include_directory, include_directory);
    writer.add_if_key_not_found(traits::header_file_extension,
        header_file_extension);
    writer.add_if_key_not_found(traits::implementation_file_extension,
        implementation_file_extension);
    writer.add_if_key_not_found(traits::enable_facet_folders,
        traits::bool_true);
    writer.add_if_key_not_found(traits::enable_unique_file_names,
        traits::bool_true);
}

void backend_enricher::
perform_first_stage_enrichment(
    const boost::property_tree::ptree& containing_module,
    boost::property_tree::ptree& target) const {
    sml::meta_data::writer writer(target);
    sml::meta_data::reader reader(containing_module);

    writer.add_if_key_not_found(traits::enabled, reader.get(traits::enabled));
    writer.add_if_key_not_found(traits::split_project,
        reader.get(traits::split_project));
    writer.add_if_key_not_found(traits::source_directory,
        reader.get(traits::source_directory));
    writer.add_if_key_not_found(traits::include_directory,
        reader.get(traits::include_directory));
    writer.add_if_key_not_found(traits::header_file_extension,
        reader.get(traits::header_file_extension));
    writer.add_if_key_not_found(traits::implementation_file_extension,
        reader.get(traits::implementation_file_extension));
    writer.add_if_key_not_found(traits::enable_facet_folders,
        reader.get(traits::enable_facet_folders));
    writer.add_if_key_not_found(traits::enable_unique_file_names,
        reader.get(traits::enable_unique_file_names));
}

void backend_enricher::enrich(const sml::model& model,
    const sml::meta_data::enrichment_types enrichment_type,
    sml::concept& target) {
    BOOST_LOG_SEV(lg, debug) << "Enriching concept: " << target.name();
    if (!is_first_stage_enrichment(enrichment_type))
        return;

    const auto cm(containing_module(model, target));
    perform_first_stage_enrichment(cm.meta_data(), target.meta_data());
}

void backend_enricher::enrich(const sml::model& model,
    const sml::meta_data::enrichment_types enrichment_type,
    sml::module& target) {
    BOOST_LOG_SEV(lg, debug) << "Enriching module: " << target.name();
    if (!is_first_stage_enrichment(enrichment_type))
        return;

    if (!target.containing_module()) {
        const auto sn(target.name().simple_name());
        BOOST_LOG_SEV(lg, debug) << "No containing module supplied for '" << sn
                                 << "'. Setting up defaults instead.";
        setup_defaults(target.meta_data());
        return;
    }

    const auto cm(containing_module(model, target));
    perform_first_stage_enrichment(cm.meta_data(), target.meta_data());
}

void backend_enricher::enrich(const sml::model& model,
    const sml::meta_data::enrichment_types enrichment_type,
    sml::type& target) {
    BOOST_LOG_SEV(lg, debug) << "Enriching type: " << target.name();
    if (!is_first_stage_enrichment(enrichment_type))
        return;

    const auto cm(containing_module(model, target));
    perform_first_stage_enrichment(cm.meta_data(), target.meta_data());
}

} } }
