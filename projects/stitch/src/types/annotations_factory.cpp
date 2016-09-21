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
#include "dogen/dynamic/types/field_selector.hpp"
#include "dogen/dynamic/types/repository_selector.hpp"
#include "dogen/stitch/types/traits.hpp"
#include "dogen/stitch/types/building_error.hpp"
#include "dogen/stitch/types/annotations_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("stitch.annotations_factory"));

const std::string field_definition_not_found(
    "Could not find expected field definition: ");

}

namespace dogen {
namespace stitch {

annotations_factory::
annotations_factory(const dynamic::repository& rp)
    : formatter_properties_(make_formatter_properties(rp)) {}

annotations_factory::formatter_properties annotations_factory::
make_formatter_properties(const dynamic::repository& rp) const {
    formatter_properties r;
    bool found_stream_variable_name(false), found_template_path(false),
        found_output_path(false), found_relative_output_directory(false),
        found_inclusion_dependency(false), found_containing_namespaces(false);
    const dynamic::repository_selector s(rp);
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

std::string annotations_factory::
extract_stream_variable_name(const dynamic::object& o) const {
    using namespace dynamic;
    const field_selector fs(o);
    const auto& fp(formatter_properties_);
    return fs.get_text_content_or_default(fp.stream_variable_name);
}

boost::optional<boost::filesystem::path> annotations_factory::
extract_template_path(const dynamic::object& o) const {
    using namespace dynamic;
    const field_selector fs(o);
    if (!fs.has_field(traits::template_path()))
        return boost::optional<boost::filesystem::path>();

    const auto text(fs.get_text_content(traits::template_path()));
    return boost::filesystem::path(text);
}

boost::optional<boost::filesystem::path> annotations_factory::
extract_output_path(const dynamic::object& o) const {
    using namespace dynamic;
    const field_selector fs(o);
    if (!fs.has_field(traits::output_path()))
        return boost::optional<boost::filesystem::path>();

    const auto text(fs.get_text_content(traits::output_path()));
    return boost::filesystem::path(text);
}

boost::optional<boost::filesystem::path> annotations_factory::
extract_relative_output_directory(const dynamic::object& o) const {
    using namespace dynamic;
    const field_selector fs(o);
    if (!fs.has_field(traits::relative_output_directory()))
        return boost::optional<boost::filesystem::path>();

    const auto text(fs.get_text_content(traits::relative_output_directory()));
    return boost::filesystem::path(text);
}

std::list<std::string> annotations_factory::
extract_inclusion_dependencies(const dynamic::object& o) const {
    std::list<std::string> r;
    using namespace dynamic;
    const field_selector fs(o);
    const auto& fd(formatter_properties_.inclusion_dependency);
    if (!fs.has_field(fd))
        return r;

    return fs.get_text_collection_content(fd);
}

std::list<std::string> annotations_factory::
extract_containing_namespaces(const dynamic::object& o) const {
    std::list<std::string> r;
    using namespace dynamic;
    const field_selector fs(o);
    const auto& fd(formatter_properties_.containing_namespaces);
    if (!fs.has_field(fd))
        return r;

    const auto s(fs.get_text_content(fd));
    if (s.empty())
        return r;

    using utility::string::splitter;
    return splitter::split_scoped(s);
}

annotations annotations_factory::
make(const dynamic::object& o) const {
    annotations r;
    r.stream_variable_name(extract_stream_variable_name(o));
    r.template_path(extract_template_path(o));
    r.output_path(extract_output_path(o));
    r.relative_output_directory(extract_relative_output_directory(o));
    r.inclusion_dependencies(extract_inclusion_dependencies(o));
    r.containing_namespaces(extract_containing_namespaces(o));
    return r;
}

} }
