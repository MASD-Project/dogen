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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_WORKFLOW_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <utility>
#include <forward_list>
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/formatters/types/decoration_configuration_factory.hpp"
#include "dogen/options/types/cpp_options.hpp"
#include "dogen/yarn/types/model.hpp"
#include "dogen/quilt.cpp/types/formattables/registrar.hpp"
#include "dogen/quilt.cpp/types/annotations/path_annotations.hpp"
#include "dogen/quilt.cpp/types/annotations/element_annotations_repository.hpp"
#include "dogen/quilt.cpp/types/annotations/aspect_annotations_repository.hpp"
#include "dogen/quilt.cpp/types/annotations/helper_annotations_repository.hpp"
#include "dogen/quilt.cpp/types/annotations/aspect_annotations_repository.hpp"
#include "dogen/quilt.cpp/types/annotations/streaming_annotations_repository.hpp"
#include "dogen/quilt.cpp/types/formatters/container.hpp"
#include "dogen/quilt.cpp/types/formattables/locator.hpp"
#include "dogen/quilt.cpp/types/formattables/path_derivatives_repository.hpp"
#include "dogen/quilt.cpp/types/formattables/element_properties_repository.hpp"
#include "dogen/quilt.cpp/types/formattables/formatter_properties_repository.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

/**
 * @brief Generates a list of properties from a given container of
 * Yarn elements.
 */
class workflow {
public:
    /**
     * @brief Returns the registrar. If it has not yet been
     * initialised, initialises it.
     */
    static formattables::registrar& registrar();

private:
    /**
     * @brief Creates the path annotations.
     */
    std::unordered_map<std::string, annotations::path_annotations>
    create_path_annotations(const dynamic::repository& drp,
        const dynamic::object& root_object,
        const formatters::container& fc) const;

    /**
     * @brief Computes the facet directory name of each facet.
     */
    std::unordered_map<std::string, std::string>
    facet_directory_for_facet(const formatters::container& fc,
        const std::unordered_map<std::string,
        annotations::path_annotations>& ps) const;

    /**
     * @brief Create the helper annotations repository.
     */
    annotations::helper_annotations_repository
    create_helper_annotations_repository(
        const dynamic::repository& drp, const yarn::model& m) const;

    /**
     * @brief Create the aspect annotations repository
     */
    annotations::aspect_annotations_repository
    create_aspect_annotations_repository(const dynamic::repository& drp,
        const yarn::model& m) const;

    /**
     * @brief Create the path derivatives repository.
     */
    path_derivatives_repository create_path_derivatives_repository(
        const locator& l, const yarn::model& m) const;

    /**
     * @brief Creates the formatter properties.
     */
    formatter_properties_repository
    create_formatter_properties(const dynamic::repository& drp,
        const dynamic::object& root_object,
        const std::unordered_map<std::string, std::string>& fdff,
        const path_derivatives_repository& pdrp,
        const locator& l,
        const formatters::container& fc,
        const yarn::model& m) const;

    /**
     * @brief Creates the element properties.
     */
    element_properties_repository create_element_properties_repository(
        const dogen::formatters::decoration_configuration_factory& dcf,
        const annotations::helper_annotations_repository& hsrp,
        const annotations::aspect_annotations_repository& asrp,
        const annotations::streaming_annotations_repository& ssrp,
        const formatters::container& fc,
        const formatter_properties_repository& fprp,
        const yarn::model& m) const;

public:
    /**
     * @brief Executes the workflow.
     */
    element_properties_repository execute(const options::cpp_options& opts,
        const dynamic::repository& drp,
        const dynamic::object& root_object,
        const dogen::formatters::decoration_configuration_factory& dcf,
        const formatters::container& fc,
        const annotations::streaming_annotations_repository& ssrp,
        const yarn::model& m) const;

private:
    static std::shared_ptr<formattables::registrar> registrar_;
};

} } } }

#endif
