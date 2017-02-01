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
#include <boost/filesystem/path.hpp>
#include "dogen/annotations/types/type.hpp"
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/quilt.cpp/types/formattables/model.hpp"
#include "dogen/quilt.cpp/types/formatters/repository.hpp"
#include "dogen/quilt.cpp/types/formattables/locator.hpp"
#include "dogen/quilt.cpp/types/formattables/formattable.hpp"
#include "dogen/quilt.cpp/types/formattables/inclusion_dependencies_builder_factory.hpp"
#include "dogen/quilt.cpp/types/formattables/inclusion_directive_configuration.hpp"
#include "dogen/quilt.cpp/types/formattables/inclusion_directive_group_repository.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class inclusion_directive_group_repository_factory final {
private:
    struct formattater_type_group {
        annotations::type inclusion_directive;
        annotations::type inclusion_required;
    };
    friend std::ostream& operator<<(std::ostream& s,
        const formattater_type_group& v);

    struct type_group {
        annotations::type inclusion_required;
        std::unordered_map<std::string, formattater_type_group>
        formattaters_type_groups;
    };
    friend std::ostream& operator<<(std::ostream& s,
        const type_group& v);

    type_group make_type_group(const annotations::type_repository& atrp,
        const formatters::repository& frp) const;

    bool make_top_level_inclusion_required(const type_group& tg,
        const annotations::annotation& a) const;

    inclusion_directive_configuration make_inclusion_directive_configuration(
        const type_group& tg, const std::string& archetype,
        const annotations::annotation& a) const;

private:
    std::string to_inclusion_directive(const boost::filesystem::path& p) const;

public:
    typedef std::forward_list<
    std::shared_ptr<formatters::artefact_formatter_interface>
    > formatter_list_type;

    typedef std::unordered_map<
        std::type_index,
        inclusion_directive_group_repository_factory::formatter_list_type
    > formatters_by_type_index_type;

private:
    void insert_inclusion_directive(const std::string& id,
        const std::string& archetype, const std::string& directive,
        inclusion_directive_group_repository& idgrp) const;

    void compute_inclusion_directives(const type_group& tg,
        const yarn::element& e, const formatter_list_type& formatters,
        const locator& l, inclusion_directive_group_repository& idgrp) const;

public:
    inclusion_directive_group_repository
    make(const type_group& tg, const formatters_by_type_index_type& afti,
        const locator& l,
        const std::unordered_map<std::string, formattable>& formattables) const;
};

} } } }

#endif
