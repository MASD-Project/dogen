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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_INCLUSION_DIRECTIVES_REPOSITORY_FACTORY_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_INCLUSION_DIRECTIVES_REPOSITORY_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/yarn/types/model.hpp"
#include "dogen/quilt.cpp/types/annotations/inclusion_directive_annotations_factory.hpp"
#include "dogen/quilt.cpp/types/formatters/container.hpp"
#include "dogen/quilt.cpp/types/formattables/locator.hpp"
#include "dogen/quilt.cpp/types/formattables/path_derivatives_repository.hpp"
#include "dogen/quilt.cpp/types/formattables/inclusion_directives_repository.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

/**
 * @brief Creates the inclusion directives for an Yarn model.
 */
class inclusion_directives_repository_factory {
private:
    typedef std::forward_list<
        std::shared_ptr<formatters::file_formatter_interface>
    > formatter_list_type;

    formatter_list_type
    filter_formatters(const formatter_list_type& formatters) const;

    std::unordered_map<std::type_index, formatter_list_type>
    filter_file_formatters_by_type_index(const formatters::container& fc) const;

private:
    /**
     * @brief Inserts the inclusion directive.
     */
    void insert_inclusion_directive(const std::string& id,
        const std::string& formatter_name, const std::string& directive,
        inclusion_directives_repository& idrp) const;

    /**
     * @brief Converts a relative path to an inclusion directive.
     */
    std::string to_inclusion_directive(const boost::filesystem::path& p) const;

public:
    void populate_repository(const yarn::element& e,
        const annotations::inclusion_directive_annotations_factory& factory,
        const formatter_list_type& formatters,
        const locator& locator, inclusion_directives_repository& idrp) const;

public:
    /**
     * @brief Create the inclusion directives for an Yarn model.
     */
    inclusion_directives_repository make(
        const dynamic::repository& drp, const formatters::container& fc,
        const locator& l, const yarn::model& m) const;
};

} } } }

#endif
