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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_FILE_PROPERTIES_FACTORY_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_FILE_PROPERTIES_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/object_types.hpp"
#include "dogen/cpp/types/settings/selector.hpp"
#include "dogen/cpp/types/formatters/formatter_types.hpp"
#include "dogen/cpp/types/formattables/file_properties.hpp"
#include "dogen/cpp/types/formatters/formatter_interface.hpp"
#include "dogen/cpp/types/formattables/provider_selector_interface.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Generates the file properties for all types in model.
 */
class file_properties_factory {
private:
    /**
     * @brief Generates all of the file names for the formatters and
     * qualified name.
     */
    std::pair<sml::qname, std::unordered_map<std::string, file_properties> >
    generate(const settings::selector& s,
        const std::forward_list<
            std::shared_ptr<formattables::provider_interface> >& providers,
        const sml::qname& qn) const;

    /**
     * @brief Builds file properties for all objects.
     */
    std::unordered_map<
        sml::qname,
        std::unordered_map<std::string, file_properties>
        >
    file_properties_for_objects(const settings::selector& s,
        const provider_selector_interface& ps,
        const std::unordered_map<sml::qname, sml::object>& objects) const;

public:
    /**
     * @brief Generate file properties for a model.
     */
    std::unordered_map<
        sml::qname,
        std::unordered_map<std::string, file_properties>
        >
    make(const settings::selector& s, const provider_selector_interface& ps,
        const sml::model& m) const;
};

} } }

#endif
