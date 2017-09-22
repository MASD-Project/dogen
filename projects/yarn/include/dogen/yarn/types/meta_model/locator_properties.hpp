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
#ifndef DOGEN_YARN_TYPES_META_MODEL_LOCATOR_PROPERTIES_HPP
#define DOGEN_YARN_TYPES_META_MODEL_LOCATOR_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen/yarn/types/meta_model/model_segment_properties.hpp"
#include "dogen/yarn/types/meta_model/archetype_group_properties.hpp"
#include "dogen/yarn/types/meta_model/directory_structure_styles.hpp"
#include "dogen/yarn/types/meta_model/intra_kernel_segment_properties.hpp"
#include "dogen/yarn/serialization/meta_model/locator_properties_fwd_ser.hpp"

namespace dogen {
namespace yarn {
namespace meta_model {

class locator_properties final {
public:
    locator_properties(const locator_properties&) = default;
    locator_properties(locator_properties&&) = default;
    ~locator_properties() = default;

public:
    locator_properties();

public:
    locator_properties(
        const dogen::yarn::meta_model::directory_structure_styles directory_structure_style,
        const std::string& name_separator,
        const dogen::yarn::meta_model::model_segment_properties& model_segment_properties,
        const std::unordered_map<std::string, dogen::yarn::meta_model::intra_kernel_segment_properties>& intra_kernel_segment_properties,
        const std::unordered_map<std::string, dogen::yarn::meta_model::archetype_group_properties>& archetype_group_properties);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::meta_model::locator_properties& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::meta_model::locator_properties& v, unsigned int version);

public:
    dogen::yarn::meta_model::directory_structure_styles directory_structure_style() const;
    void directory_structure_style(const dogen::yarn::meta_model::directory_structure_styles v);

    /**
     * @brief Separator to use when concatenating sub-components of a path component.
     */
    /**@{*/
    const std::string& name_separator() const;
    std::string& name_separator();
    void name_separator(const std::string& v);
    void name_separator(const std::string&& v);
    /**@}*/

    const dogen::yarn::meta_model::model_segment_properties& model_segment_properties() const;
    dogen::yarn::meta_model::model_segment_properties& model_segment_properties();
    void model_segment_properties(const dogen::yarn::meta_model::model_segment_properties& v);
    void model_segment_properties(const dogen::yarn::meta_model::model_segment_properties&& v);

    const std::unordered_map<std::string, dogen::yarn::meta_model::intra_kernel_segment_properties>& intra_kernel_segment_properties() const;
    std::unordered_map<std::string, dogen::yarn::meta_model::intra_kernel_segment_properties>& intra_kernel_segment_properties();
    void intra_kernel_segment_properties(const std::unordered_map<std::string, dogen::yarn::meta_model::intra_kernel_segment_properties>& v);
    void intra_kernel_segment_properties(const std::unordered_map<std::string, dogen::yarn::meta_model::intra_kernel_segment_properties>&& v);

    const std::unordered_map<std::string, dogen::yarn::meta_model::archetype_group_properties>& archetype_group_properties() const;
    std::unordered_map<std::string, dogen::yarn::meta_model::archetype_group_properties>& archetype_group_properties();
    void archetype_group_properties(const std::unordered_map<std::string, dogen::yarn::meta_model::archetype_group_properties>& v);
    void archetype_group_properties(const std::unordered_map<std::string, dogen::yarn::meta_model::archetype_group_properties>&& v);

public:
    bool operator==(const locator_properties& rhs) const;
    bool operator!=(const locator_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(locator_properties& other) noexcept;
    locator_properties& operator=(locator_properties other);

private:
    dogen::yarn::meta_model::directory_structure_styles directory_structure_style_;
    std::string name_separator_;
    dogen::yarn::meta_model::model_segment_properties model_segment_properties_;
    std::unordered_map<std::string, dogen::yarn::meta_model::intra_kernel_segment_properties> intra_kernel_segment_properties_;
    std::unordered_map<std::string, dogen::yarn::meta_model::archetype_group_properties> archetype_group_properties_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::meta_model::locator_properties& lhs,
    dogen::yarn::meta_model::locator_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
