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
#ifndef DOGEN_GENERATION_CPP_TYPES_FORMATTABLES_DIRECTIVE_GROUP_REPOSITORY_FACTORY_HPP
#define DOGEN_GENERATION_CPP_TYPES_FORMATTABLES_DIRECTIVE_GROUP_REPOSITORY_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen.annotations/types/type.hpp"
#include "dogen.annotations/types/type_repository.hpp"
#include "dogen.generation.cpp/types/formattables/model.hpp"
#include "dogen.generation.cpp/types/formatters/repository.hpp"
#include "dogen.generation.cpp/types/formattables/locator.hpp"
#include "dogen.generation.cpp/types/formattables/formattable.hpp"
#include "dogen.generation.cpp/types/formattables/directive_group_repository.hpp"

namespace dogen::generation::cpp::formattables {

class directive_group_repository_factory final {
private:
    struct formattater_type_group {
        annotations::type primary_inclusion_directive;
        annotations::type secondary_inclusion_directive;
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

    boost::optional<directive_group> make_directive_group(
        const type_group& tg, const std::string& archetype,
        const annotations::annotation& a) const;

    bool has_inclusion_directive_overrides(
        const annotations::annotation& a) const;

private:
    std::string to_inclusion_directive(const boost::filesystem::path& p) const;

public:
    typedef std::forward_list<
    std::shared_ptr<formatters::artefact_formatter_interface>
    > artefact_formatters_type;

    artefact_formatters_type remove_non_includible_formatters(
        const artefact_formatters_type& formatters) const;

    std::unordered_map<std::string, artefact_formatters_type>
    includible_formatters_by_meta_name(const formatters::repository& frp) const;

private:
    void insert_inclusion_directive(const std::string& id,
        const std::string& archetype, const directive_group& dg,
        directive_group_repository& dgrp) const;

    void compute_directives(const type_group& tg,
        const modeling::meta_model::element& e,
        const artefact_formatters_type& formatters,
        const locator& l, directive_group_repository& dgrp) const;

    directive_group_repository make(const type_group& tg,
        const std::unordered_map<std::string, artefact_formatters_type>& afmt,
        const locator& l,
        const std::unordered_map<std::string, formattable>& formattables) const;

public:
    directive_group_repository
    make(const annotations::type_repository& atrp,
        const formatters::repository& frp, const locator& l,
        const std::unordered_map<std::string, formattable>& formattables) const;
};

}

#endif
