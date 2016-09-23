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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_FORMATTER_PROPERTIES_REPOSITORY_FACTORY_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_FORMATTER_PROPERTIES_REPOSITORY_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_map>
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/options/types/cpp_options.hpp"
#include "dogen/yarn/types/model.hpp"
#include "dogen/quilt.cpp/types/annotations/path_annotations.hpp"
#include "dogen/quilt.cpp/types/annotations/element_annotations_repository.hpp"
#include "dogen/quilt.cpp/types/formatters/container.hpp"
#include "dogen/quilt.cpp/types/formattables/locator.hpp"
#include "dogen/quilt.cpp/types/formattables/enablement_repository.hpp"
#include "dogen/quilt.cpp/types/formattables/path_derivatives_repository.hpp"
#include "dogen/quilt.cpp/types/formattables/formatter_properties_repository.hpp"
#include "dogen/quilt.cpp/types/formattables/inclusion_directives_repository.hpp"
#include "dogen/quilt.cpp/types/formattables/inclusion_dependencies_repository.hpp"
#include "dogen/quilt.cpp/types/formattables/inclusion_dependencies_builder_factory.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

/**
 * @brief Creates the formatter properties repository.
 */
class formatter_properties_repository_factory {
private:
    struct merged_formatter_data {
        std::unordered_map<std::string, path_derivatives> path_derivatives_;
        std::unordered_map<std::string, std::list<std::string> >
        inclusion_dependencies;
        std::unordered_map<std::string, bool> enablement;
        std::unordered_set<std::string> enabled_formatters;
        std::unordered_map<std::string, std::string>
        facet_directory_for_facet;
    };

private:
    /**
     * @brief Create the inclusion directives repository.
     */
    inclusion_directives_repository create_inclusion_directives_repository(
        const dynamic::repository& srp, const formatters::container& fc,
        const locator& l, const yarn::model& m) const;

    /**
     * @brief Create the inclusion dependencies repository.
     */
    inclusion_dependencies_repository create_inclusion_dependencies_repository(
        const inclusion_dependencies_builder_factory& bf,
        const formatters::container& fc, const yarn::model& m) const;

    /**
     * @brief Creates the enablement repository.
     */
    enablement_repository
    create_enablement_repository(const dynamic::repository& srp,
        const dynamic::object& root_object,
        const formatters::container& fc,
        const yarn::model& m) const;

    /**
     * @brief Merge all data structures.
     */
    std::unordered_map<yarn::name, merged_formatter_data>
    merge(const path_derivatives_repository& pdrp,
        const inclusion_dependencies_repository& idrp,
        const enablement_repository& erp,
        const std::unordered_map<std::string, std::string>& fdff) const;

    /**
     * @brief Produce the formatter properties.
     */
    formatter_properties_repository
    create_formatter_properties(
        const std::unordered_map<yarn::name, merged_formatter_data>& mfd) const;

public:
    formatter_properties_repository make(
        const dynamic::repository& srp,
        const dynamic::object& root_object,
        const std::unordered_map<std::string, std::string>& fdff,
        const path_derivatives_repository& pdrp, const locator& l,
        const formatters::container& fc,
        const yarn::model& m) const;
};

} } } }

#endif
