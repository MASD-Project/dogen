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
#ifndef DOGEN_TEXT_CPP_TYPES_TRANSFORMS_CONTEXT_HPP
#define DOGEN_TEXT_CPP_TYPES_TRANSFORMS_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen.tracing/types/tracer.hpp"
#include "dogen.text/types/entities/element_archetype.hpp"
#include "dogen.text.cpp/types/formattables/model.hpp"
#include "dogen.text.cpp/types/formattables/element_properties.hpp"
#include "dogen.text.cpp/types/transforms/helper_transform.hpp"

namespace dogen::text::cpp::transforms {

/**
 * @brief Supplies additional information required for formatting.
 */
class context final {
public:
    context(const std::unordered_set<text::entities::element_archetype>&
        enabled_archetype_for_element,
        const formattables::element_properties& element_properties,
        const formattables::model& fm, const std::unordered_map<std::string,
        std::unordered_map<std::string, std::list<std::shared_ptr<
        helper_transform>>>>& helpers,
        boost::shared_ptr<tracing::tracer> tracer);

public:
    const std::unordered_set<text::entities::element_archetype>&
    enabled_archetype_for_element() const;

    const formattables::element_properties& element_properties() const;

    const formattables::model& model() const;

    const std::unordered_map<
        std::string,
        std::unordered_map<
            std::string,
            std::list<std::shared_ptr<helper_transform>>>>&
        helpers() const;

    boost::shared_ptr<tracing::tracer> tracer() const;

private:
    const std::unordered_set<text::entities::element_archetype>&
    enabled_archetype_for_element_;
    const formattables::element_properties& element_properties_;
    const formattables::model& model_;
    const std::unordered_map<
        std::string,
        std::unordered_map<
            std::string, std::list<
                             std::shared_ptr<helper_transform>>>>&
    helpers_;
    boost::shared_ptr<tracing::tracer> tracer_;
};

}

#endif
