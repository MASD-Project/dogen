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
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
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
stitching_properties_factory(const annotations::type_repository& arp)
    : type_group_(make_type_group(arp)) {}

stitching_properties_factory::type_group
stitching_properties_factory::make_type_group(
    const annotations::type_repository& arp) const {
    type_group r;
    bool found_stream_variable_name(false), found_template_path(false),
        found_output_path(false), found_relative_output_directory(false),
        found_inclusion_dependency(false), found_containing_namespaces(false);
    const annotations::type_repository_selector s(arp);
    for (const auto t : s.select_type_by_model_name(traits::model_name())) {
        if (t.name().simple() == traits::stream_variable_name()) {
            r.stream_variable_name = t;
            found_stream_variable_name = true;
        } else if (t.name().simple() == traits::template_path()) {
            r.template_path = t;
            found_template_path = true;
        } else if (t.name().simple() == traits::output_path()) {
            r.output_path = t;
            found_output_path = true;
        } else if (t.name().simple() == traits::relative_output_directory()) {
            r.relative_output_directory = t;
            found_relative_output_directory = true;
        } else if (t.name().simple() == traits::inclusion_dependency()) {
            r.inclusion_dependency = t;
            found_inclusion_dependency = true;
        } else if (t.name().simple() == traits::containing_namespaces()) {
            r.containing_namespaces = t;
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
    const entry_selector s(a);
    const auto& tg(type_group_);
    return s.get_text_content_or_default(tg.stream_variable_name);
}

boost::optional<boost::filesystem::path> stitching_properties_factory::
extract_template_path(const annotations::annotation& a) const {
    using namespace annotations;
    const entry_selector s(a);
    if (!s.has_field(traits::template_path()))
        return boost::optional<boost::filesystem::path>();

    const auto text(s.get_text_content(traits::template_path()));
    return boost::filesystem::path(text);
}

boost::optional<boost::filesystem::path> stitching_properties_factory::
extract_output_path(const annotations::annotation& a) const {
    using namespace annotations;
    const entry_selector s(a);
    if (!s.has_field(traits::output_path()))
        return boost::optional<boost::filesystem::path>();

    const auto text(s.get_text_content(traits::output_path()));
    return boost::filesystem::path(text);
}

boost::optional<boost::filesystem::path> stitching_properties_factory::
extract_relative_output_directory(const annotations::annotation& a) const {
    using namespace annotations;
    const entry_selector s(a);
    if (!s.has_field(traits::relative_output_directory()))
        return boost::optional<boost::filesystem::path>();

    const auto text(s.get_text_content(traits::relative_output_directory()));
    return boost::filesystem::path(text);
}

std::list<std::string> stitching_properties_factory::
extract_inclusion_dependencies(const annotations::annotation& a) const {
    std::list<std::string> r;
    using namespace annotations;
    const entry_selector s(a);
    const auto& t(type_group_.inclusion_dependency);
    if (!s.has_field(t))
        return r;

    return s.get_text_collection_content(t);
}

std::list<std::string> stitching_properties_factory::
extract_containing_namespaces(const annotations::annotation& a) const {
    std::list<std::string> r;
    using namespace annotations;
    const entry_selector s(a);
    const auto& t(type_group_.containing_namespaces);
    if (!s.has_field(t))
        return r;

    const auto cns(s.get_text_content(t));
    if (cns.empty())
        return r;

    using utility::string::splitter;
    return splitter::split_scoped(cns);
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
