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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_INCLUSION_DEPENDENCIES_FACTORY_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_INCLUSION_DEPENDENCIES_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_map>
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/types/module.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/concept.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/cpp/types/formattables/container.hpp"
#include "dogen/cpp/types/formattables/inclusion_directives_repository.hpp"
#include "dogen/cpp/types/formattables/inclusion_dependencies_builder_factory.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Creates the inclusion dependencies for a given Yarn entity.
 */
class inclusion_dependencies_factory {
public:
    inclusion_dependencies_factory(
        const inclusion_dependencies_builder_factory& f, const container& c);
public:
    /**
     * @brief Makes inclusion dependencies for an object.
     */
    std::unordered_map<std::string, std::list<std::string> >
    make(const yarn::object& o) const;

    /**
     * @brief Makes inclusion dependencies for an enumeration.
     */
    std::unordered_map<std::string, std::list<std::string> >
    make(const yarn::enumeration& e) const;

    /**
     * @brief Makes inclusion dependencies for a primitive.
     */
    std::unordered_map<std::string, std::list<std::string> >
    make(const yarn::primitive& p) const;

    /**
     * @brief Makes inclusion dependencies for a module.
     */
    std::unordered_map<std::string, std::list<std::string> >
    make(const yarn::module& m) const;

    /**
     * @brief Makes inclusion dependencies for a concept.
     */
    std::unordered_map<std::string, std::list<std::string> >
    make(const yarn::concept& c) const;

    /**
     * @brief Makes inclusion dependencies for a model.
     */
    std::unordered_map<std::string, std::list<std::string> >
    make(const yarn::intermediate_model& m) const;

private:
    const inclusion_dependencies_builder_factory& factory_;
    const container& provider_container_;
};

} } }

#endif
