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
#ifndef DOGEN_QUILT_CPP_TYPES_WORKFLOW_HPP
#define DOGEN_QUILT_CPP_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <memory>
#include <forward_list>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/formatters/types/repository.hpp"
#include "dogen/formatters/types/decoration_configuration_factory.hpp"
#include "dogen/yarn/types/model.hpp"
#include "dogen/quilt/types/backend_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/container.hpp"
#include "dogen/quilt.cpp/types/annotations/opaque_annotations_builder.hpp"
#include "dogen/quilt.cpp/types/annotations/streaming_annotations_repository.hpp"
#include "dogen/quilt.cpp/types/annotations/element_annotations_repository.hpp"
#include "dogen/quilt.cpp/types/formattables/element_properties_repository.hpp"

namespace dogen {
namespace quilt {
namespace cpp {

/**
 * @brief Manages the c++ backend workflow.
 */
class workflow final : public quilt::backend_interface {
public:
    workflow() = default;
    workflow(const workflow&) = delete;
    workflow(workflow&&) = default;

public:
    ~workflow() noexcept;

private:
    /**
     * @brief Creates the formatters' repository.
     */
    dogen::formatters::repository create_formatters_repository(
        const std::forward_list<boost::filesystem::path>& dirs) const;

    /**
     * @brief Create the decoration configuration factory.
     */
    dogen::formatters::decoration_configuration_factory
    create_decoration_configuration_factory(
            const dynamic::repository& drp,
            const dogen::formatters::repository& frp,
            const dynamic::object& root_object) const;

    /**
     * @brief Creates the opaque annotations builder.
     */
    annotations::opaque_annotations_builder
    create_opaque_annotations_builder(const dynamic::repository& rp) const;

    /**
     * @brief Create the streaming annotations repository.
     */
    annotations::streaming_annotations_repository
        create_streaming_annotations_repository(const dynamic::repository& drp,
            const yarn::model& m) const;

    /**
     * @brief Create the element annotations repository
     */
    annotations::element_annotations_repository
    create_element_annotations_repository(
        const annotations::opaque_annotations_builder& osb,
        const yarn::model& m) const;

    /**
     * @brief Create the properties.
     */
    formattables::element_properties_repository
        create_properties(const options::cpp_options& opts,
        const dynamic::repository& drp,
        const dynamic::object& root_object,
        const dogen::formatters::decoration_configuration_factory& dcf,
        const formatters::container& fc,
        const annotations::streaming_annotations_repository& ssrp,
        const yarn::model& m) const;

    void test_new_formattables_workflow(
        const dynamic::repository& rp, const dynamic::object& root_object,
        const formatters::container& fc, const yarn::model& m,
        const formattables::element_properties_repository& legacy) const;

    /**
     * @brief Returns only the generatable elements.
     */
    std::forward_list<boost::shared_ptr<yarn::element> >
    extract_generatable_elements(const yarn::model& m) const;

    /**
     * @brief Create the files.
     */
    std::forward_list<dogen::formatters::file>
    format(const annotations::streaming_annotations_repository& ssrp,
        const annotations::element_annotations_repository& esrp,
        const formattables::element_properties_repository& eprp,
        const std::forward_list<
        boost::shared_ptr<yarn::element> >& elements) const;

public:
    std::string name() const override;

    std::forward_list<boost::filesystem::path>
    managed_directories(const options::knitting_options& ko,
        const dynamic::repository& drp,
        const yarn::model& m) const override;

    std::forward_list<dynamic::ownership_hierarchy>
        ownership_hierarchy() const override;

    std::forward_list<dogen::formatters::file> generate(
        const options::knitting_options& ko,
        const dynamic::repository& drp,
        const yarn::model& m) const override;
};

} } }

#endif
