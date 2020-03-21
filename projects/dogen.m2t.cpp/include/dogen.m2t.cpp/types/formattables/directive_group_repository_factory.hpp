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
#ifndef DOGEN_M2T_CPP_TYPES_FORMATTABLES_DIRECTIVE_GROUP_REPOSITORY_FACTORY_HPP
#define DOGEN_M2T_CPP_TYPES_FORMATTABLES_DIRECTIVE_GROUP_REPOSITORY_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen.variability/types/entities/feature.hpp"
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.m2t.cpp/types/formattables/model.hpp"
#include "dogen.m2t.cpp/types/formatters/repository.hpp"
#include "dogen.m2t.cpp/types/formattables/locator.hpp"
#include "dogen.m2t.cpp/types/formattables/formattable.hpp"
#include "dogen.m2t.cpp/types/formattables/directive_group_repository.hpp"

namespace dogen::m2t::cpp::formattables {

class directive_group_repository_factory final {
private:
    struct formattater_feature_group {
        variability::entities::feature primary_inclusion_directive;
        variability::entities::feature secondary_inclusion_directive;
    };

    struct feature_group {
        variability::entities::feature inclusion_required;
        std::unordered_map<std::string, formattater_feature_group>
        formattaters_feature_groups;
    };

    feature_group make_feature_group(
        const variability::entities::feature_model& fm,
        const formatters::repository& frp) const;

    bool make_top_level_inclusion_required(const feature_group& fg,
        const variability::entities::configuration& cfg) const;

    boost::optional<directive_group> make_directive_group(
        const feature_group& fg, const std::string& archetype,
        const variability::entities::configuration& cfg) const;

    bool has_inclusion_directive_overrides(
        const variability::entities::configuration& cfg) const;

private:
    std::string to_inclusion_directive(const boost::filesystem::path& p) const;

public:
    typedef std::forward_list<
    std::shared_ptr<formatters::model_to_text_transform>
    > artefact_formatters_type;

    artefact_formatters_type remove_non_includible_formatters(
        const artefact_formatters_type& formatters) const;

    std::unordered_map<std::string, artefact_formatters_type>
    includible_formatters_by_meta_name(const formatters::repository& frp) const;

private:
    void insert_inclusion_directive(const std::string& id,
        const std::string& archetype, const directive_group& dg,
        directive_group_repository& dgrp) const;

    void compute_directives(const feature_group& fg,
        const logical::entities::element& e,
        const artefact_formatters_type& formatters,
        const locator& l, directive_group_repository& dgrp) const;

    directive_group_repository make(
        const feature_group& fg,
        const std::unordered_map<std::string, artefact_formatters_type>& afmt,
        const locator& l,
        const std::unordered_map<std::string, formattable>& formattables) const;

public:
    directive_group_repository
    make(const variability::entities::feature_model& feature_model,
        const formatters::repository& frp,
        const locator& l,
        const std::unordered_map<std::string, formattable>& formattables) const;
};

}

#endif
