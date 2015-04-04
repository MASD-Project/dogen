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
#ifndef DOGEN_CPP_TYPES_EXPANSION_INCLUSION_DEPENDENCIES_FACTORY_HPP
#define DOGEN_CPP_TYPES_EXPANSION_INCLUSION_DEPENDENCIES_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_map>
#include "dogen/sml/types/module.hpp"
#include "dogen/sml/types/object.hpp"
#include "dogen/sml/types/concept.hpp"
#include "dogen/sml/types/primitive.hpp"
#include "dogen/sml/types/enumeration.hpp"
#include "dogen/cpp/types/expansion/container.hpp"
#include "dogen/cpp/types/expansion/path_derivatives.hpp"

namespace dogen {
namespace cpp {
namespace expansion {

/**
 * @brief Creates the inclusion dependencies for a given SML entity.
 */
class inclusion_dependencies_factory {
public:
    inclusion_dependencies_factory(const container& c,
        const std::unordered_map<
            sml::qname,
            std::unordered_map<std::string, expansion::path_derivatives>
            >& pd);

public:
    /**
     * @brief Create inclusion dependencies.
     */
    /**@{*/
    std::unordered_map<std::string,std::list<std::string> >
    make(const dogen::sml::object& o) const;

    std::unordered_map<std::string,std::list<std::string> >
    make(const dogen::sml::enumeration& e) const;

    std::unordered_map<std::string,std::list<std::string> >
    make(const dogen::sml::primitive& p) const;

    std::unordered_map<std::string,std::list<std::string> >
    make(const dogen::sml::module& m) const;

    std::unordered_map<std::string,std::list<std::string> >
    make(const dogen::sml::concept& c) const;
    /**@}*/

private:
    const container& container_;
    const std::unordered_map<
        sml::qname,
        std::unordered_map<std::string, expansion::path_derivatives>
        >& path_derivatives_;
};

} } }

#endif
