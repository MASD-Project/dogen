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
#ifndef DOGEN_CPP_TYPES_TRANSFORMER_HPP
#define DOGEN_CPP_TYPES_TRANSFORMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <set>
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/enumeration.hpp"
#include "dogen/cpp/types/file_info.hpp"
#include "dogen/config/types/cpp_settings.hpp"
#include "dogen/config/types/cpp_facet_types.hpp"

namespace dogen {
namespace cpp {

class transformer {
public:
    transformer() = delete;
    transformer(const transformer&) = default;
    ~transformer() = default;
    transformer& operator=(const transformer&) = delete;
    transformer(transformer&& rhs) = default;

public:
    transformer(const config::cpp_settings& s);

private:
    /**
     * @brief Returns the available facets for the given inputs.
     *
     * @param mt Meta-type which we want to process.
     * @param pt Pod type to process; must be set to invalid if the
     * meta-type is not a pod.
     */
    std::set<config::cpp_facet_types> facet_types(const sml::meta_types mt,
        const sml::pod_types pt = sml::pod_types::invalid) const;

private:
    /**
     * @brief Flattens all the SML namespace information stored in qname
     * into a list of strings with C++ namespaces.
     */
    std::list<std::string>
    transform_namespaces(const dogen::sml::qname& qn) const;

    /**
     * @brief Transforms a SML enumeration into an enumeration info.
     */
    enumeration_info transform_enumeration(const sml::enumeration& e) const;

public:
    std::list<file_info> transform(const sml::enumeration& e) const;

private:
    const config::cpp_settings& settings_;
};

} }

#endif
