/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_CPP_TYPES_WORKFLOW_HPP
#define DOGEN_CPP_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <memory>
#include <forward_list>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen/dynamic/schema/types/repository.hpp"
#include "dogen/backend/types/backend_interface.hpp"
#include "dogen/cpp/types/settings/workflow.hpp"
#include "dogen/cpp/types/formattables/formattable.hpp"
#include "dogen/sml/types/model.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Manages the c++ backend workflow.
 */
class workflow final : public backend::backend_interface {
public:
    workflow() = default;
    workflow(const workflow&) = delete;
    workflow(workflow&&) = default;

public:
    ~workflow() noexcept;

private:
    /**
     * @brief Create the formattables.
     */
    std::forward_list<std::shared_ptr<formattables::formattable> >
        create_formattables_activty(const settings::workflow& sw,
            const sml::model& m) const;

    /**
     * @brief Create the files.
     */
    std::forward_list<dogen::formatters::file>
    format_activty(const std::forward_list<
            std::shared_ptr<formattables::formattable>
            >& f) const;

public:
    std::string id() const override;

    std::vector<boost::filesystem::path> managed_directories() const override;

    void validate() const override;

    std::forward_list<dogen::formatters::file> generate(
        const config::knitting_options& o,
        const dynamic::schema::repository& rp,
        const sml::model& m) const override;
};

} }

#endif
