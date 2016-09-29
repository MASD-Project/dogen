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
#ifndef DOGEN_CPP_TYPES_ANNOTATIONS_INCLUSION_DIRECTIVE_ANNOTATIONS_FACTORY_HPP
#define DOGEN_CPP_TYPES_ANNOTATIONS_INCLUSION_DIRECTIVE_ANNOTATIONS_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include <boost/optional.hpp>
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/dynamic/types/field_definition.hpp"
#include "dogen/quilt.cpp/types/formatters/container.hpp"
#include "dogen/quilt.cpp/types/annotations/inclusion_directive_annotations.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace annotations {

/**
 * @brief Creates the inclusion directive annotations for all
 * formatters.
 */
class inclusion_directive_annotations_factory {
public:
    inclusion_directive_annotations_factory(
        const dynamic::repository& drp, const formatters::container& fc);

private:
    struct field_definitions {
        dynamic::field_definition inclusion_directive;
        dynamic::field_definition inclusion_required;
    };

    field_definitions make_field_definitions(const dynamic::repository& rp,
        const std::string& formatter_name) const;

    std::unordered_map<std::string, field_definitions>
    make_field_definitions(const dynamic::repository& rp,
        const formatters::container& fc) const;

    dynamic::field_definition get_top_level_inclusion_required_field(
        const dynamic::repository& rp) const;

private:
    boost::optional<std::string> obtain_inclusion_directive_for_formatter(
        const field_definitions& fd,
        const dynamic::object& o) const;

    bool obtain_inclusion_required_for_formatter(
        const field_definitions& fd,
        const dynamic::object& o) const;

    bool obtain_top_level_inclusion_required(
        const dynamic::object& o) const;

public:
    bool make_top_level_inclusion_required(const dynamic::object& o) const;

    inclusion_directive_annotations make_inclusion_directive_annotations(
        const std::string& formatter_name, const dynamic::object& o) const;

private:
    const std::unordered_map<std::string, field_definitions> field_definitions_;
    const dynamic::field_definition inclusion_required_;
};

} } } }

#endif
