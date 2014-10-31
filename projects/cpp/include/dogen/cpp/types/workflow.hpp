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

#include <memory>
#include "dogen/cpp/types/registrar.hpp"
#include "dogen/backend/types/backend_interface.hpp"
#include "dogen/cpp/types/formatters/class_formatter_interface.hpp"
#include "dogen/cpp/types/transformer.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Manages the c++ backend workflow.
 */
class workflow : public backend::backend_interface {
public:
    workflow() = default;
    workflow(const workflow&) = delete;
    workflow(workflow&&) = default;

public:
    ~workflow() noexcept;

private:
    /**
     * @brief Returns the registrar. If it has not yet been
     * initialised, initialises it.
     */
    static cpp::registrar& registrar();

public:
    /**
     * @brief Registers a formatter with the workflow.
     */
    static void register_formatter(
        std::shared_ptr<formatters::class_formatter_interface> f);

private:
    /**
     * @brief Transforms the supplied SML elements into C++ entities.
     */
    template<typename AssociativeContainerOfElement>
    std::forward_list<std::shared_ptr<entity>>
    transform_sml_elements(const sml::model& m,
        const AssociativeContainerOfElement& c) const {
        std::forward_list<std::shared_ptr<entity> > r;
        transformer t(m);
        for (const auto& pair : c)
            r.push_front(t.transform(pair.second));
        return r;
    }

    /**
     * @brief Formats all files for the entity.
     */
    std::forward_list<dogen::formatters::file> format_entity(
        const settings_bundle& s, const entity& e) const;

private:
    /**
     * @brief Create a settings bundle
     */
    settings_bundle create_settings_bundle_activity(
        const dogen::formatters::general_settings& gs) const;

    /**
     * @brief Creates all the files for a given container of SML
     * elements.
     */
    template<typename AssociativeContainerOfElement>
    std::forward_list<dogen::formatters::file>
    create_files_from_sml_container_activity(const sml::model& m,
        const settings_bundle& s,
        const AssociativeContainerOfElement& c) const {
        const auto entities(transform_sml_elements(m, c));
        std::forward_list<dogen::formatters::file> r;
        for (const auto e : entities)
            r.splice_after(r.before_begin(), format_entity(s, *e));
        return r;
    }


public:
    std::string id() const override;

    std::vector<boost::filesystem::path> managed_directories() const override;

    void validate() const override;

    std::forward_list<dogen::formatters::file> generate(
        const dogen::formatters::general_settings& gs,
        const sml::model& m) const override;

private:
    static std::shared_ptr<cpp::registrar> registrar_;
};

} }

#endif
