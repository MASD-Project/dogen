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
#ifndef DOGEN_VARIABILITY_TYPES_META_MODEL_PROFILE_TEMPLATE_HPP
#define DOGEN_VARIABILITY_TYPES_META_MODEL_PROFILE_TEMPLATE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include <unordered_set>
#include "dogen.variability/types/meta_model/element.hpp"
#include "dogen.variability/types/meta_model/configuration_point_template.hpp"

namespace dogen::variability::meta_model {

/**
 * @brief Holds a set of templates for configuration points.
 */
class profile_template final : public dogen::variability::meta_model::element {
public:
    profile_template() = default;
    profile_template(const profile_template&) = default;
    profile_template(profile_template&&) = default;

    virtual ~profile_template() noexcept { }

public:
    profile_template(
        const dogen::variability::meta_model::name& name,
        const std::string& description,
        const std::list<std::string>& parents,
        const std::unordered_set<std::string>& stereotype,
        const std::list<dogen::variability::meta_model::configuration_point_template>& templates);

public:
    void to_stream(std::ostream& s) const override;

public:
    const std::list<std::string>& parents() const;
    std::list<std::string>& parents();
    void parents(const std::list<std::string>& v);
    void parents(const std::list<std::string>&& v);

    const std::unordered_set<std::string>& stereotype() const;
    std::unordered_set<std::string>& stereotype();
    void stereotype(const std::unordered_set<std::string>& v);
    void stereotype(const std::unordered_set<std::string>&& v);

    const std::list<dogen::variability::meta_model::configuration_point_template>& templates() const;
    std::list<dogen::variability::meta_model::configuration_point_template>& templates();
    void templates(const std::list<dogen::variability::meta_model::configuration_point_template>& v);
    void templates(const std::list<dogen::variability::meta_model::configuration_point_template>&& v);

public:
    bool operator==(const profile_template& rhs) const;
    bool operator!=(const profile_template& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::variability::meta_model::element& other) const override;

public:
    void swap(profile_template& other) noexcept;
    profile_template& operator=(profile_template other);

private:
    std::list<std::string> parents_;
    std::unordered_set<std::string> stereotype_;
    std::list<dogen::variability::meta_model::configuration_point_template> templates_;
};

}

namespace std {

template<>
inline void swap(
    dogen::variability::meta_model::profile_template& lhs,
    dogen::variability::meta_model::profile_template& rhs) {
    lhs.swap(rhs);
}

}

#endif
