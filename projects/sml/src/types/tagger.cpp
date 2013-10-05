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
#include "dogen/sml/types/tags.hpp"
#include "dogen/sml/types/tag_adaptor.hpp"
#include "dogen/sml/types/tag_router.hpp"
#include "dogen/sml/types/tagger.hpp"

namespace {

const std::string cpp_header_extension(".hpp");
const std::string cpp_implementation_extension(".cpp");

const std::string empty_postfix;
const std::string types_postfix;
const std::string forward_decls_postfix("_fwd");
const std::string io_postfix("_io");
const std::string hash_postfix("_hash");
const std::string serialization_postfix("_ser");
const std::string test_data_postfix("_td");
const std::string odb_postfix("_pragmas");

const std::string types_directory("types");
const std::string io_directory("io");
const std::string hash_directory("hash");
const std::string serialization_directory("serialization");
const std::string test_data_directory("test_data");
const std::string odb_directory("odb");

const bool is_header_file(true);

}

namespace dogen {
namespace sml {

void tagger::
from_settings(const config::cpp_settings& s, model& m) const {
    tag_router router(make_tag_router(m));

    router.route_if_key_not_found(tags::split_project,
        s.split_project() ? tags::bool_false : tags::bool_true);

    router.route_if_key_not_found(tags::cpp::header_file_extension,
        s.header_extension());

    router.route_if_key_not_found(tags::cpp::implementation_file_extension,
        s.source_extension());

    router.route_if_key_not_found(tags::cpp::enable_facet_folders,
        s.disable_facet_folders() ? tags::bool_false : tags::bool_true);

    router.route_if_key_not_found(tags::cpp::enable_unique_file_names,
        s.disable_unique_file_names() ?
        tags::bool_false : tags::bool_true);

    using config::cpp_facet_types;
    const auto& ss(tags::status_supported);

    if (is_facet_enabled(s.enabled_facets(), cpp_facet_types::types)) {
        router.route_if_key_not_found(tags::cpp::types::status, ss);

        router.route_if_key_not_found(
            tags::cpp::types::generate_complete_constructor,
            s.disable_complete_constructor() ?
            tags::bool_false : tags::bool_true);

        router.route_if_key_not_found(
            tags::cpp::types::includers_file::generate,
            s.disable_facet_includers() ?
            tags::bool_false : tags::bool_true);

        router.route_if_key_not_found(
            tags::cpp::types::directory_name,
            s.domain_facet_folder());
    }

    if (is_facet_enabled(s.enabled_facets(), cpp_facet_types::hash)) {
        router.route_if_key_not_found(tags::cpp::hash::standard::status, ss);

        router.route_if_key_not_found(
            tags::cpp::hash::standard::includers_file::generate,
            s.disable_facet_includers() ?
            tags::bool_false : tags::bool_true);

        router.route_if_key_not_found(
            tags::cpp::types::directory_name,
            s.hash_facet_folder());
    }

    if (is_facet_enabled(s.enabled_facets(), cpp_facet_types::io)) {
        router.route_if_key_not_found(tags::cpp::io::status, ss);

        router.route_if_key_not_found(
            tags::cpp::io::enable_integrated_io,
            s.use_integrated_io() ?
            tags::bool_true : tags::bool_false);

        router.route_if_key_not_found(
            tags::cpp::io::includers_file::generate,
            s.disable_facet_includers() ?
            tags::bool_false : tags::bool_true);

        router.route_if_key_not_found(
            tags::cpp::types::directory_name,
            s.io_facet_folder());
    }

    if (is_facet_enabled(s.enabled_facets(), cpp_facet_types::serialization)) {
        const auto& key(tags::cpp::serialization::boost::status);
        router.route_if_key_not_found(key, ss);

        router.route_if_key_not_found(
            tags::cpp::serialization::boost::enable_xml_serialization,
            s.disable_xml_serialization() ?
            tags::bool_false : tags::bool_true);

        router.route_if_key_not_found(
            tags::cpp::serialization::boost::includers_file::generate,
            s.disable_facet_includers() ?
            tags::bool_false : tags::bool_true);

        router.route_if_key_not_found(
            tags::cpp::types::directory_name,
            s.serialization_facet_folder());
    }

    if (is_facet_enabled(s.enabled_facets(), cpp_facet_types::test_data)) {
        const auto& key(tags::cpp::test_data::status);
        router.route_if_key_not_found(key, ss);

        router.route_if_key_not_found(
            tags::cpp::test_data::includers_file::generate,
            s.disable_facet_includers() ?
            tags::bool_false : tags::bool_true);

        router.route_if_key_not_found(
            tags::cpp::types::directory_name,
            s.test_data_facet_folder());
    }

    if (is_facet_enabled(s.enabled_facets(), cpp_facet_types::odb)) {
        router.route_if_key_not_found(tags::cpp::odb::status, ss);

        router.route_if_key_not_found(
            tags::cpp::odb::includers_file::generate,
            s.disable_facet_includers() ?
            tags::bool_false : tags::bool_true);

        router.route_if_key_not_found(
            tags::cpp::types::directory_name,
            s.odb_facet_folder());
    }
}

bool tagger::is_facet_enabled(
    const std::set<config::cpp_facet_types> enabled_facets,
    const config::cpp_facet_types facet) const {
    const auto i(enabled_facets.find(facet));
    return i != enabled_facets.end();
}

std::string tagger::
filename_for_qname(const model& m, const bool split_project,
    const bool is_header, const qname& qn, const std::string& facet_directory,
    const std::string& facet_postfix,
    const std::string& additional_postfix,
    const std::string& extension) const {

    boost::filesystem::path r;

    if (split_project) {
        for(auto n : qn.external_module_path())
            r /= n;
    }

    if (split_project)
        r /= qn.model_name();
    else if (is_header) {
        for(auto n : qn.external_module_path())
            r /= n;
        r /= qn.model_name();
    }

    auto adaptor(make_tag_adaptor(m));
    if (adaptor.is_true(tags::cpp::enable_facet_folders))
        r /= facet_directory;

    for(auto n : qn.module_path())
        r /= n;

    std::ostringstream stream;
    stream << qn.simple_name() << additional_postfix;

    if (adaptor.is_true(tags::cpp::enable_unique_file_names))
        stream << facet_postfix;

    stream << extension;

    r /= stream.str();

    return r.generic_string();
}

void tagger::tag_type(type& /*t*/) const {
}

void tagger::tag(model& m) const {
    tag_router router(make_tag_router(m));
    router.route_if_key_not_found(tags::generate_preamble, tags::bool_true);

    router.route_if_key_not_found(tags::cpp::header_file_extension,
        cpp_header_extension);

    router.route_if_key_not_found(tags::cpp::implementation_file_extension,
        cpp_implementation_extension);

    router.route_if_key_not_found(tags::cpp::enable_facet_folders,
        tags::bool_true);

    router.route_if_key_not_found(tags::cpp::enable_unique_file_names,
        tags::bool_true);

    router.route_if_key_not_found(tags::cpp::forward_declaration_postfix,
        forward_decls_postfix);

    const auto& ss(tags::status_supported);
    router.route_if_key_not_found(tags::cpp::types::status, ss);

    auto adaptor(make_tag_adaptor(m));
    if (adaptor.is_true(tags::cpp::types::status)) {
        router.route_if_key_not_found(tags::cpp::types::directory_name,
            types_directory);

        router.route_if_key_not_found(tags::cpp::types::postfix,
            types_postfix);

        // only generate a types file for models when there is
        // documentation for the model.
        if (!m.documentation().empty()) {
            router.route_if_key_not_found(
                tags::cpp::types::header_file::generate, tags::bool_true);

            const auto fn(filename_for_qname(m,
                    adaptor.is_true(tags::split_project),
                    is_header_file,
                    m.name(),
                    adaptor.get(tags::cpp::types::directory_name),
                    adaptor.get(tags::cpp::types::postfix),
                    empty_postfix,
                    adaptor.get(tags::cpp::header_file_extension)));

            router.route_if_key_not_found(
                tags::cpp::types::header_file::file_name, fn);
        }
    }
}

void tagger::tag(const config::cpp_settings& s, model& m) const {
    from_settings(s, m);
    tag(m);
}

} }
