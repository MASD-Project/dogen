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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_WORKFLOW_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <forward_list>
#include "dogen/sml/types/model.hpp"
#include "dogen/cpp/types/settings/selector.hpp"
#include "dogen/cpp/types/formattables/includes.hpp"
#include "dogen/cpp/types/formattables/transformer.hpp"
#include "dogen/cpp/types/formattables/formattable.hpp"
#include "dogen/cpp/types/formattables/file_properties.hpp"
#include "dogen/cpp/types/formattables/provider_selector_interface.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Generates a list of formattables from a given container of
 * SML elements.
 */
class workflow {
private:
    /**
     * @brief Transforms the supplied SML elements into C++ entities.
     */
    template<typename AssociativeContainerOfElement>
    std::forward_list<std::shared_ptr<formattables::formattable> >
    to_formattables_activity(
        std::unordered_map<sml::qname,
                           std::unordered_map<std::string,
                                              formattables::includes>
                           > includes_by_qname_by_formatter_name,
        std::unordered_map<sml::qname,
                           std::unordered_map<std::string,
                                              formattables::file_properties>
                           > file_properties_by_qname_by_formatter_name,
        const sml::model& m,
        const AssociativeContainerOfElement& c) const {
        std::forward_list<std::shared_ptr<formattables::formattable> > r;
        formattables::transformer t(
            includes_by_qname_by_formatter_name,
            file_properties_by_qname_by_formatter_name, m);

        for (const auto& pair : c) {
            const auto ng(sml::generation_types::no_generation);
            if (pair.second.generation_type() == ng)
                continue;

            r.push_front(t.transform(pair.second));
        }
        return r;
    }

    /**
     * @brief Gets the file properties for the model.
     */
    std::unordered_map<
        sml::qname,
        std::unordered_map<std::string, formattables::file_properties> >
    create_file_properties_activity(const settings::selector& s,
        const provider_selector_interface& ps,
        const sml::model& m) const;

    /**
     * @brief Creates the includes for the model.
     */
    std::unordered_map<
        sml::qname,
        std::unordered_map<std::string, formattables::includes> >
    create_includes_activity(const settings::selector& s,
        const provider_selector_interface& ps, const sml::model& m,
        const std::unordered_map<sml::qname,
        std::unordered_map<std::string, formattables::file_properties> >&
        file_properties_by_formatter_name) const;

public:
    /**
     * @brief Executes the workflow.
     */
    std::forward_list<std::shared_ptr<formattables::formattable> >
    execute(const settings::selector& s, const provider_selector_interface& ps,
        const sml::model& m) const;
};

} } }

#endif
