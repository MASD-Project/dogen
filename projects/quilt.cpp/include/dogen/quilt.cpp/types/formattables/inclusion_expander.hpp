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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_INCLUSION_EXPANDER_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_INCLUSION_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <memory>
#include <forward_list>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/quilt.cpp/types/annotations/inclusion_directive_annotations_factory.hpp"
#include "dogen/quilt.cpp/types/formatters/container.hpp"
#include "dogen/quilt.cpp/types/formattables/locator.hpp"
#include "dogen/quilt.cpp/types/formattables/formattable.hpp"
#include "dogen/quilt.cpp/types/formattables/inclusion_dependencies_builder_factory.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class inclusion_expander {
private:
    typedef std::forward_list<
    std::shared_ptr<formatters::file_formatter_interface>
    > formatter_list_type;

    formatter_list_type remove_non_includible_formatters(
        const formatter_list_type& formatters) const;

    std::unordered_map<std::type_index, formatter_list_type>
    includible_formatters_by_type_index(const formatters::container& fc) const;

private:
    std::string to_inclusion_directive(const boost::filesystem::path& p) const;

private:
    typedef std::unordered_map<std::string,
                               std::unordered_map<std::string, std::string>
                               >
    inclusion_directives_container_type;

    void insert_inclusion_directive(const std::string& id,
        const std::string& formatter_name, const std::string& directive,
        inclusion_directives_container_type& idc) const;

    void compute_inclusion_directives(const yarn::element& e,
        const annotations::inclusion_directive_annotations_factory& factory,
        const formatter_list_type& formatters, const locator& l,
        inclusion_directives_container_type& idc) const;

    inclusion_directives_container_type compute_inclusion_directives(
        const dynamic::repository& drp, const formatters::container& fc,
        const locator& l,
        const std::unordered_map<std::string, formattable>& formattables) const;

private:
    typedef std::unordered_map<std::string, std::list<std::string>>
        element_inclusion_dependencies_type;

    element_inclusion_dependencies_type compute_inclusion_dependencies(
        const formatters::container& fc,
        const inclusion_dependencies_builder_factory& f,
        const yarn::element& e) const;

    void populate_inclusion_dependencies(const formatters::container& fc,
        const inclusion_directives_container_type& idc,
        std::unordered_map<std::string, formattable>& formattables) const;

public:
    void expand(const dynamic::repository& drp, const formatters::container& fc,
        const locator& l,
        std::unordered_map<std::string, formattable>& formattables) const;
};

} } } }

#endif
