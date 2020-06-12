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
#ifndef DOGEN_TEXT_CPP_TYPES_TRANSFORMS_TYPES_BACKEND_CLASS_HEADER_TRANSFORM_TRANSFORM_HPP
#define DOGEN_TEXT_CPP_TYPES_TRANSFORMS_TYPES_BACKEND_CLASS_HEADER_TRANSFORM_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.text.cpp/types/transforms/model_to_text_transform.hpp"

namespace dogen::text::cpp::transforms::types {

class backend_class_header_transform_transform final : public model_to_text_transform {
public:
    static const physical::entities::archetype& static_archetype();
    const physical::entities::archetype& archetype() const override;

public:
    std::list<std::string> inclusion_dependencies(
        const formattables::dependencies_builder_factory& f,
        const logical::entities::element& e) const override;

    inclusion_support_types inclusion_support_type() const override;

    boost::filesystem::path inclusion_path(
        const formattables::locator& l,
        const logical::entities::name& n) const override;

    boost::filesystem::path full_path(
        const formattables::locator& l,
        const logical::entities::name& n) const override;

public:
    void apply(const context& ctx, const logical::entities::element& e,
        physical::entities::artefact& a) const override;
};

}

#endif