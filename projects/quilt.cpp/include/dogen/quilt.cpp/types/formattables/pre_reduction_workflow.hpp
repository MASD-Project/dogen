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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_PRE_REDUCTION_WORKFLOW_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_PRE_REDUCTION_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <forward_list>
#include <unordered_map>
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/yarn/types/model.hpp"
#include "dogen/quilt.cpp/types/formatters/container.hpp"
#include "dogen/quilt.cpp/types/formattables/formattable.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class pre_reduction_workflow {
public:
    void expand_enablement(const dynamic::repository& drp,
        const dynamic::object& root_object, const formatters::container& fc,
        std::unordered_map<std::string, formattable>& formattables) const;

    std::unordered_map<std::string, formattable>
    transform(const formatters::container& fc, const yarn::model& m) const;

public:
    std::unordered_map<std::string, formattable>
    execute(const dynamic::repository& drp, const dynamic::object& root_object,
        const formatters::container& fc, const yarn::model& m) const;
};

} } } }

#endif
