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
#include "dogen/dynamic/types/field_selector.hpp"
#include "dogen/dynamic/types/repository_selector.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/quilt.cpp/types/annotations/building_error.hpp"
#include "dogen/quilt.cpp/types/annotations/inclusion_directive_annotations_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.annotations.inclusion_directive_annotations_factory"));

const std::string empty_formatter_name("Formatter name is empty.");
const std::string missing_formatter_name("Formatter name not found: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace annotations {

inclusion_directive_annotations_factory::
inclusion_directive_annotations_factory(const dynamic::repository& rp,
    const formatters::container& fc)
    : field_definitions_(make_field_definitions(rp, fc)),
      inclusion_required_(get_top_level_inclusion_required_field(rp)) {}

inclusion_directive_annotations_factory::field_definitions
inclusion_directive_annotations_factory::make_field_definitions(
    const dynamic::repository& rp, const std::string& formatter_name) const {

    field_definitions r;
    const dynamic::repository_selector s(rp);
    const auto& id(traits::inclusion_directive());
    r.inclusion_directive = s.select_field_by_name(formatter_name, id);

    const auto& ir(traits::inclusion_required());
    r.inclusion_required = s.select_field_by_name(formatter_name, ir);

    return r;
}

std::unordered_map<
    std::string,
    inclusion_directive_annotations_factory::field_definitions
    >
inclusion_directive_annotations_factory::
make_field_definitions(const dynamic::repository& rp,
    const formatters::container& fc) const {
    std::unordered_map<std::string, field_definitions> r;

    for (const auto f : fc.all_file_formatters()) {
        const auto& oh(f->ownership_hierarchy());
        const auto fn(oh.formatter_name());

        if (fn.empty()) {
            BOOST_LOG_SEV(lg, error) << empty_formatter_name;
            BOOST_THROW_EXCEPTION(building_error(empty_formatter_name));
        }

        if (f->file_type() != formatters::file_types::cpp_header) {
            BOOST_LOG_SEV(lg, debug) << "Skipping formatter: " << fn;
            continue;
        }

        r[oh.formatter_name()] = make_field_definitions(rp, fn);
    }
    return r;
}

dynamic::field_definition inclusion_directive_annotations_factory::
get_top_level_inclusion_required_field(
    const dynamic::repository& rp) const {
    const dynamic::repository_selector s(rp);
    return s.select_field_by_name(traits::cpp::inclusion_required());
}

boost::optional<std::string> inclusion_directive_annotations_factory::
obtain_inclusion_directive_for_formatter(const field_definitions& fd,
    const dynamic::object& o) const {
    boost::optional<std::string> r;

    using namespace dynamic;
    const field_selector fs(o);
    if (!fs.has_field(fd.inclusion_directive))
        return r;

    r = fs.get_text_content(fd.inclusion_directive);
    return r;
}

bool inclusion_directive_annotations_factory::
obtain_inclusion_required_for_formatter(const field_definitions& fd,
    const dynamic::object& o) const {
    using namespace dynamic;
    const field_selector fs(o);
    const auto r(fs.get_boolean_content_or_default(fd.inclusion_required));
    return r;
}

bool inclusion_directive_annotations_factory::
obtain_top_level_inclusion_required(const dynamic::object& o) const {
    using namespace dynamic;
    const field_selector fs(o);
    return fs.get_boolean_content_or_default(inclusion_required_);
}

bool inclusion_directive_annotations_factory::
make_top_level_inclusion_required(const dynamic::object& o) const {
    return obtain_top_level_inclusion_required(o);
}

inclusion_directive_annotations inclusion_directive_annotations_factory::
make_inclusion_directive_annotations(const std::string& formatter_name,
    const dynamic::object& o) const {

    if (formatter_name.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_formatter_name;
        BOOST_THROW_EXCEPTION(building_error(empty_formatter_name));
    }

    const auto i(field_definitions_.find(formatter_name));
    if (i == field_definitions_.end()) {
        BOOST_LOG_SEV(lg, error) << missing_formatter_name;
        BOOST_THROW_EXCEPTION(building_error(missing_formatter_name));
    }

    const auto& fd(i->second);
    inclusion_directive_annotations r;
    const auto req(obtain_inclusion_required_for_formatter(fd, o));
    r.inclusion_required(req);

    const auto directive(obtain_inclusion_directive_for_formatter(fd, o));
    r.inclusion_directive(directive);

    return r;
}

} } } }
