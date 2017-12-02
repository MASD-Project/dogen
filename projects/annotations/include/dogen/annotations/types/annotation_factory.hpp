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
#ifndef DOGEN_ANNOTATIONS_TYPES_ANNOTATIONS_FACTORY_HPP
#define DOGEN_ANNOTATIONS_TYPES_ANNOTATIONS_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen/annotations/types/type.hpp"
#include "dogen/annotations/types/annotation.hpp"
#include "dogen/annotations/types/scope_types.hpp"
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/annotations/types/archetype_location_repository.hpp"

namespace dogen {
namespace annotations {

/**
 * @brief Produces an annotation object from raw data.
 */
class annotation_factory final {
public:
    /**
     * @brief Initialise the annotations object factory.
     *
     * @param data_dirs directories in which to look for data files.
     * @param alrp the archetype location repository.
     * @param trp the type repository.
     */
    annotation_factory(
        const std::vector<boost::filesystem::path>& data_dirs,
        const archetype_location_repository& alrp,
        const type_repository& trp, const bool compatibility_mode);

private:
    struct type_group {
        annotations::type profile;
    };

    friend std::ostream& operator<<(std::ostream& s, const type_group& v);

    type_group make_type_group() const;

    std::string
    obtain_profile_name(const type_group& tg, const annotation& a) const;

private:
    /**
     * @brief Returns the field definition for the qualified name, if
     * any exists.
     */
    boost::optional<type> try_obtain_type(const std::string& n) const;

    /**
     * @brief Ensures the field definition is valid for the current
     * scope.
     */
    void validate_scope(const type& fd,
        const scope_types current_scope) const;

    /**
     * @brief Given a scope, returns the well-known name of its the
     * default profile.
     */
    std::string
    get_default_profile_name_for_scope(const scope_types scope) const;

private:
    /**
     * @brief Converts the raw data into an annotation.
     */
    annotation create_annotation(const scope_types scope,
        const std::unordered_map<std::string, std::list<std::string>>&
        aggregated_entries) const;

    /**
     * @brief Aggregate entry data by key.
     */
    std::unordered_map<std::string, std::list<std::string>>
    aggregate_entries(const std::list<std::pair<std::string, std::string>>&
        entries) const;

    /**
     * @brief Creates the annotation profiles.
     */
    std::unordered_map<std::string, annotation>
    create_annotation_profiles() const;

    std::list<std::string> get_bound_labels(const std::unordered_map<
        std::string, annotation>& profiles, const std::list<std::string>&
        candidate_labels) const;

    /**
     * @brief Augment the original annotation with any profile
     * entries, if it has one.
     */
    annotation
    handle_profiles(const type_group& tg, const std::unordered_map<std::string,
        annotation>& profiles, const std::list<std::string>& candidate_labels,
        const annotation& original) const;

public:
    annotation
    make(const std::list<std::pair<std::string, std::string>>& entries,
        const scope_types scope,
        const std::list<std::string>& candidate_labels) const;

private:
    const std::vector<boost::filesystem::path> data_dirs_;
    const archetype_location_repository& archetype_location_repository_;
    const type_repository& type_repository_;
    const std::unordered_map<std::string, annotation> profiles_;
    const type_group type_group_;
    const bool compatibility_mode_;
};

} }

#endif
