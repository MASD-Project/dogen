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
#ifndef DOGEN_ANNOTATIONS_TYPES_OWNERSHIP_HIERARCHY_HPP
#define DOGEN_ANNOTATIONS_TYPES_OWNERSHIP_HIERARCHY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/annotations/serialization/ownership_hierarchy_fwd_ser.hpp"

namespace dogen {
namespace annotations {

/**
 * @brief Hierarchical properties of this name.
 *
 * These must be populated in order, e.g. in order to have a facet we must have a
 * model and in order to have a formatter we must have a facet. We may not have
 * any.
 */
class ownership_hierarchy final {
public:
    ownership_hierarchy() = default;
    ownership_hierarchy(const ownership_hierarchy&) = default;
    ownership_hierarchy(ownership_hierarchy&&) = default;
    ~ownership_hierarchy() = default;

public:
    ownership_hierarchy(
        const std::string& model_name,
        const std::string& facet_name,
        const std::string& formatter_name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::annotations::ownership_hierarchy& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::annotations::ownership_hierarchy& v, unsigned int version);

public:
    /**
     * @brief Name of the model that owns this field, if any.
     */
    /**@{*/
    const std::string& model_name() const;
    std::string& model_name();
    void model_name(const std::string& v);
    void model_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Name of the facet that owns this field, if any.
     */
    /**@{*/
    const std::string& facet_name() const;
    std::string& facet_name();
    void facet_name(const std::string& v);
    void facet_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Name of the formatter that owns this field, if any.
     */
    /**@{*/
    const std::string& formatter_name() const;
    std::string& formatter_name();
    void formatter_name(const std::string& v);
    void formatter_name(const std::string&& v);
    /**@}*/

public:
    bool operator==(const ownership_hierarchy& rhs) const;
    bool operator!=(const ownership_hierarchy& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(ownership_hierarchy& other) noexcept;
    ownership_hierarchy& operator=(ownership_hierarchy other);

private:
    std::string model_name_;
    std::string facet_name_;
    std::string formatter_name_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::annotations::ownership_hierarchy& lhs,
    dogen::annotations::ownership_hierarchy& rhs) {
    lhs.swap(rhs);
}

}

#endif
