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
#ifndef DOGEN_TEXT_CPP_TYPES_FORMATTABLES_INCLUSION_EXPANDER_HPP
#define DOGEN_TEXT_CPP_TYPES_FORMATTABLES_INCLUSION_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_set>
#include "dogen.variability/types/entities/feature.hpp"
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.physical/types/entities/element_archetype.hpp"
#include "dogen.text.cpp/types/formattables/model.hpp"
#include "dogen.text.cpp/types/formattables/locator.hpp"
#include "dogen.text.cpp/types/transforms/repository.hpp"
#include "dogen.text.cpp/types/formattables/formattable.hpp"
#include "dogen.text.cpp/types/formattables/dependencies_builder_factory.hpp"
#include "dogen.text.cpp/types/formattables/directive_group_repository.hpp"

namespace dogen::text::cpp::formattables {

/**
 * @brief Generates all inclusion dependencies.
 *
 * In formattables we use two similar terms with very different
 * meanings: inclusion directive and inclusion dependency.
 *
 * An inclusion directive is a string with delimiters but without the
 * #include pragma. For example "a/b/c.hpp" and <a/b/c.hpp> are
 * inclusion directives; note that the quotes and angle brackets are
 * part of the directive. An inclusion directive group is a group of
 * such things. There should be an inclusion directive group
 * associated with every ordered pair (name, archetype). The inclusion
 * directive group repository contains the complete set of inclusion
 * directive groups - the inclusion directives domain if you'd like.
 *
 * Inclusion dependencies are a set of inclusion directives. They are
 * also associated with a pair (name, archetype). The inclusion
 * dependencies for each formatter are created by the formatter
 * themselves since they are relative to the formatter - i.e. for the
 * same element (and even archetype) different formatters will
 * generate different dependencies. It uses the inclusion directives
 * precomputed from the model to assemble the inclusion dependencies
 * that the formatter needs in order to generate a compilable C++
 * file.
 *
 */
class inclusion_expander {
private:
    directive_group_repository create_directive_groups(
        const variability::entities::feature_model& feature_model,
        const transforms::repository& frp, const locator& l,
        const std::unordered_map<std::string, formattable>& formattables) const;

public:
    typedef std::unordered_map<std::string, std::list<std::string>>
    element_inclusion_dependencies_type;

    element_inclusion_dependencies_type compute_inclusion_dependencies(
        const transforms::repository& frp,
        const dependencies_builder_factory& f,
        const logical::entities::element& e) const;

    void populate_inclusion_dependencies(const transforms::repository& frp,
        const dependencies_builder_factory& df,
        std::unordered_map<std::string, formattable>& formattables) const;

public:
    void expand(const variability::entities::feature_model& feature_model,
        const std::unordered_set<physical::entities::element_archetype>&
        enabled_archetype_for_element,
        const transforms::repository& frp, const locator& l, model& fm) const;
};

}

#endif
