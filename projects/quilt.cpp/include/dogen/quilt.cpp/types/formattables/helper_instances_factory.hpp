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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_HELPER_INSTANCES_FACTORY_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_HELPER_INSTANCES_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_set>
#include "dogen/yarn/types/property.hpp"
#include "dogen/yarn/types/name_tree.hpp"
#include "dogen/quilt.cpp/types/formattables/helper_instance.hpp"
#include "dogen/quilt.cpp/types/settings/helper_settings_repository.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class helper_instances_factory {
public:
    helper_instances_factory(
        const settings::helper_settings_repository& hsrp);

private:
    void make(const yarn::name_tree& nt,
        std::list<helper_instance>& instances,
        std::unordered_set<std::string>& types_done) const;
    
public:
    std::list<helper_instance>
    make(const std::list<yarn::property>& properties) const;

private:
    const settings::helper_settings_repository& helper_settings_;
};

} } } }

#endif
