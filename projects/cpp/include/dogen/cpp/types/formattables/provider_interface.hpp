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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_PROVIDER_INTERFACE_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_PROVIDER_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <forward_list>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/formatters/types/file.hpp"
#include "dogen/cpp/types/settings/selector.hpp"
#include "dogen/cpp/types/formattables/inclusion.hpp"
#include "dogen/cpp/types/formattables/file_properties.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Provides formattable data.
 */
class provider_interface {
public:
    provider_interface() = default;
    provider_interface(const provider_interface&) = delete;
    provider_interface(provider_interface&&) = default;
    virtual ~provider_interface() noexcept = 0;

public:
    /**
     * @brief Name of the facet that the provider belongs to.
     */
    virtual std::string facet_name() const = 0;

    /**
     * @brief Name of the formatter the provider generates data for.
     */
    virtual std::string formatter_name() const = 0;

    /**
     * @brief Provides the file properties for the supplied qualified
     * name.
     */
    virtual file_properties provide_file_properties(const settings::selector& s,
        const sml::qname& qn) const = 0;

    /**
     * @brief Provides the includes for the supplied qualified name.
     */
    virtual std::list<formattables::inclusion>
    provide_inclusion_dependencies(const settings::selector& s,
        const std::unordered_map<
            sml::qname,
            std::unordered_map<std::string, file_properties>
            >& file_properties_by_formatter_name,
        const sml::model& m) const = 0;
};

} } }

#endif
