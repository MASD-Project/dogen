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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTERS_INCLUDE_CMAKELISTS_FORMATTER_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTERS_INCLUDE_CMAKELISTS_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/quilt.cpp/types/formatters/artefact_formatter_interface.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

class include_cmakelists_formatter final : public artefact_formatter_interface {
public:
    static std::string static_artefact();

public:
    std::string formatter_name() const override;
    annotations::archetype_location archetype_location() const override;
    const yarn::meta_model::name& meta_name() const override;

public:
    std::list<std::string> inclusion_dependencies(
        const formattables::dependencies_builder_factory& f,
        const yarn::meta_model::element& e) const override;

    inclusion_support_types inclusion_support_type() const override;

    boost::filesystem::path inclusion_path(
        const formattables::locator& l,
        const yarn::meta_model::name& n) const override;

    boost::filesystem::path full_path(
        const formattables::locator& l,
        const yarn::meta_model::name& n) const override;

public:
    dogen::formatters::artefact format(const context& ctx,
    const yarn::meta_model::element& e) const override;
};

} } } }

#endif
