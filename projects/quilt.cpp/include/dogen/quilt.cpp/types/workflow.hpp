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
#include "dogen/annotations/types/object.hpp"
#include "dogen/annotations/types/repository.hpp"
#include "dogen/formatters/types/repository.hpp"
#include "dogen/formatters/types/decoration_properties_factory.hpp"
#include "dogen/yarn/types/model.hpp"
#include "dogen/quilt/types/backend_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/container.hpp"
#include "dogen/quilt.cpp/types/formattables/model.hpp"

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
    std::forward_list<boost::filesystem::path> make_data_directories() const;

    /**
     * @brief Creates the formatters' repository.
     */
    dogen::formatters::repository create_formatters_repository(const
        std::forward_list<boost::filesystem::path>& data_directories) const;

    /**
     * @brief Create the decoration configuration factory.
     */
    dogen::formatters::decoration_properties_factory
    create_decoration_properties_factory(
            const annotations::repository& drp,
            const dogen::formatters::repository& frp,
            const annotations::object& root_object) const;

    /**
     * @brief Create the formattables representation of the yarn model.
     */
    formattables::model create_formattables_model(
        const std::forward_list<boost::filesystem::path>& data_directories,
        const options::cpp_options& opts,
        const annotations::repository& drp,
        const annotations::object& root_object,
        const dogen::formatters::decoration_properties_factory& dpf,
        const formatters::container& fc, const yarn::model& m) const;

    /**
     * @brief Create the files representation of the formattables model.
     */
    std::forward_list<dogen::formatters::file>
    format(const formattables::model& fm) const;

public:
    std::string name() const override;

    std::forward_list<boost::filesystem::path>
    managed_directories(const options::knitting_options& ko,
        const yarn::name& model_name) const override;

    std::forward_list<annotations::ownership_hierarchy>
        ownership_hierarchy() const override;

    std::forward_list<dogen::formatters::file> generate(
        const options::knitting_options& ko,
        const annotations::repository& drp,
        const yarn::model& m) const override;
};

} } }

#endif
