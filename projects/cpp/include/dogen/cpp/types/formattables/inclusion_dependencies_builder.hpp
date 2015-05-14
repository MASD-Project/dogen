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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_INCLUSION_DEPENDENCIES_BUILDER_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_INCLUSION_DEPENDENCIES_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include "dogen/dynamic/schema/types/object.hpp"
#include "dogen/cpp/types/formattables/inclusion_directives_repository.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Helps in building the inclusion dependencies for a given
 * formatter.
 */
class inclusion_dependencies_builder {
public:
    explicit inclusion_dependencies_builder(
        const inclusion_directives_repository& rp);

public:
    /**
     * @brief Adds the supplied inclusion directive.
     */
    void add(const std::string& inclusion_directive);

    /**
     * @brief Adds the inclusion directive for the supplied formatter
     * name and qname.
     */
    void add(const sml::qname& qn, const std::string& formatter_name);

    /**
     * @brief Adds the inclusion directives for the supplied
     * formatter name, for each of the supplied qnames.
     */
    void add(const std::list<sml::qname>& qn,
        const std::string& formatter_name);

public:
    /**
     * @brief Builds the inclusion dependencies. All additions must
     * have been performed already.
     */
    std::list<std::string> build();

private:
    const inclusion_directives_repository& repository_;
    std::list<std::string> inclusion_dependencies_;
};

} } }

#endif
