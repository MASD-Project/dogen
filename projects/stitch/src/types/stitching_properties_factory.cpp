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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/string/splitter.hpp"
#include "dogen/annotations/types/field_selector.hpp"
#include "dogen/annotations/types/repository_selector.hpp"
#include "dogen/stitch/types/traits.hpp"
#include "dogen/stitch/types/building_error.hpp"
#include "dogen/stitch/types/stitching_properties_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("stitch.stitching_properties_factory"));

const std::string field_definition_not_found(
    "Could not find expected field definition: ");

}

namespace dogen {
namespace stitch {

stitching_properties_factory::
stitching_properties_factory(const annotations::type_repository& rp)
    : field_definitions_(make_field_definitions(rp)) {}

stitching_properties_factory::field_definitions
stitching_properties_factory::make_field_definitions(
    const annotations::type_repository& rp) const {
    field_definitions r;
    bool found_stream_variable_name(false), found_template_path(false),
        found_output_path(false), found_relative_output_directory(false),
        found_inclusion_dependency(false), found_containing_namespaces(false);
    const annotations::repository_selector s(rp);
    for (const auto fd : s.select_fields_by_model_name(traits::model_name())) {
        if (fd.name().simple() == traits::stream_variable_name()) {
            r.stream_variable_name = fd;
            found_stream_variable_name = true;
        } else if (fd.name().simple() == traits::template_path()) {
            r.template_path = fd;
            found_template_path = true;
        } else if (fd.name().simple() == traits::output_path()) {
            r.output_path = fd;
            found_output_path = true;
        } else if (fd.name().simple() == traits::relative_output_directory()) {
            r.relative_output_directory = fd;
            found_relative_output_directory = true;
        } else if (fd.name().simple() == traits::inclusion_dependency()) {
            r.inclusion_dependency = fd;
            found_inclusion_dependency = true;
        } else if (fd.name().simple() == traits::containing_namespaces()) {
            r.containing_namespaces = fd;
            found_containing_namespaces = true;
        }
    }

    if (!found_stream_variable_name) {
        BOOST_LOG_SEV(lg, error) << field_definition_not_found << " '"
                                 << traits::stream_variable_name();
        BOOST_THROW_EXCEPTION(building_error(field_definition_not_found +
                traits::stream_variable_name()));
    }

    if (!found_template_path) {
        BOOST_LOG_SEV(lg, error) << field_definition_not_found << " '"
                                 << traits::template_path();
        BOOST_THROW_EXCEPTION(building_error(field_definition_not_found
                + traits::template_path()));
    }

    if (!found_output_path) {
        BOOST_LOG_SEV(lg, error) << field_definition_not_found << " '"
                                 << traits::output_path();
        BOOST_THROW_EXCEPTION(building_error(field_definition_not_found
                + traits::output_path()));
    }

    if (!found_relative_output_directory) {
        BOOST_LOG_SEV(lg, error) << field_definition_not_found << " '"
                                 << traits::relative_output_directory();
        BOOST_THROW_EXCEPTION(building_error(field_definition_not_found
                + traits::relative_output_directory()));
    }

    if (!found_inclusion_dependency) {
        BOOST_LOG_SEV(lg, error) << field_definition_not_found << " '"
                                 << traits::inclusion_dependency();
        BOOST_THROW_EXCEPTION(building_error(field_definition_not_found
                + traits::inclusion_dependency()));
    }

    if (!found_containing_namespaces) {
        BOOST_LOG_SEV(lg, error) << field_definition_not_found << " '"
                                 << traits::containing_namespaces();
        BOOST_THROW_EXCEPTION(building_error(field_definition_not_found
                + traits::containing_namespaces()));
    }

    return r;
}

std::string stitching_properties_factory::
extract_stream_variable_name(const annotations::annotation& a) const {
    using namespace annotations;
    const field_selector fs(a);
    const auto& fds(field_definitions_);
    return fs.get_text_content_or_default(fds.stream_variable_name);
}

boost::optional<boost::filesystem::path> stitching_properties_factory::
extract_template_path(const annotations::annotation& a) const {
    using namespace annotations;
    const field_selector fs(a);
    if (!fs.has_field(traits::template_path()))
        return boost::optional<boost::filesystem::path>();

    const auto text(fs.get_text_content(traits::template_path()));
    return boost::filesystem::path(text);
}

boost::optional<boost::filesystem::path> stitching_properties_factory::
extract_output_path(const annotations::annotation& a) const {
    using namespace annotations;
    const field_selector fs(a);
    if (!fs.has_field(traits::output_path()))
        return boost::optional<boost::filesystem::path>();

    const auto text(fs.get_text_content(traits::output_path()));
    return boost::filesystem::path(text);
}

boost::optional<boost::filesystem::path> stitching_properties_factory::
extract_relative_output_directory(const annotations::annotation& a) const {
    using namespace annotations;
    const field_selector fs(a);
    if (!fs.has_field(traits::relative_output_directory()))
        return boost::optional<boost::filesystem::path>();

    const auto text(fs.get_text_content(traits::relative_output_directory()));
    return boost::filesystem::path(text);
}

std::list<std::string> stitching_properties_factory::
extract_inclusion_dependencies(const annotations::annotation& a) const {
    std::list<std::string> r;
    using namespace annotations;
    const field_selector fs(a);
    const auto& fds(field_definitions_.inclusion_dependency);
    if (!fs.has_field(fds))
        return r;

    return fs.get_text_collection_content(fds);
}

std::list<std::string> stitching_properties_factory::
extract_containing_namespaces(const annotations::annotation& a) const {
    std::list<std::string> r;
    using namespace annotations;
    const field_selector fs(a);
    const auto& fds(field_definitions_.containing_namespaces);
    if (!fs.has_field(fds))
        return r;

    const auto s(fs.get_text_content(fds));
    if (s.empty())
        return r;

    using utility::string::splitter;
    return splitter::split_scoped(s);
}

stitching_properties stitching_properties_factory::
make(const annotations::annotation& a) const {
    stitching_properties r;
    r.stream_variable_name(extract_stream_variable_name(a));
    r.template_path(extract_template_path(a));
    r.output_path(extract_output_path(a));
    r.relative_output_directory(extract_relative_output_directory(a));
    r.inclusion_dependencies(extract_inclusion_dependencies(a));
    r.containing_namespaces(extract_containing_namespaces(a));
    return r;
}

} }
