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
#include "dogen/formatters/types/decoration_configuration_factory.hpp"
#include "dogen/quilt.cpp/types/formatters/container.hpp"
#include "dogen/quilt.cpp/types/formattables/locator.hpp"
#include "dogen/quilt.cpp/types/formattables/formattable.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class pre_reduction_workflow {
public:
    std::unordered_map<std::string, formattable> initial_transform(
        const formatters::container& fc, const yarn::model& m) const;

    void expand_enablement(const dynamic::repository& drp,
        const dynamic::object& root_object, const formatters::container& fc,
        std::unordered_map<std::string, formattable>& formattables) const;

    void expand_inclusion(
        const dynamic::repository& drp,
        const formatters::container& fc, const locator& l,
        std::unordered_map<std::string, formattable>& formattables) const;

    void expand_decoration(
        const dogen::formatters::decoration_configuration_factory& dcf,
        std::unordered_map<std::string, formattable>& formattables) const;

    void expand_aspects(const dynamic::repository& drp,
        std::unordered_map<std::string, formattable>& formattables) const;

    void expand_helpers(const dynamic::repository& drp,
        const formatters::container& fc,
        std::unordered_map<std::string, formattable>& formattables) const;

    std::unordered_map<std::string, formattable> reduce(
        std::unordered_map<std::string, formattable>& formattables) const;

    typedef std::unordered_map<std::string, formattable>
    formattables_by_id_type;

    void expand_file_paths_and_guards(const formatters::container& fc,
        const locator& l, formattables_by_id_type& formattables) const;

    void expand_opaque_configuration(const dynamic::repository& drp,
        std::unordered_map<std::string, formattable>& formattables) const;

    std::forward_list<formattable> final_transform(
        const std::unordered_map<std::string, formattable>& formattables) const;

public:
    std::forward_list<formattable>
    execute(const dynamic::repository& drp, const dynamic::object& root_object,
        const dogen::formatters::decoration_configuration_factory& dcf,
        const formatters::container& fc, const locator& l,
        const yarn::model& m) const;
};

} } } }

#endif
