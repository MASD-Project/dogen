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
#ifndef MASD_DOGEN_VARIABILITY_TYPES_TYPE_REPOSITORY_HPP
#define MASD_DOGEN_VARIABILITY_TYPES_TYPE_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "masd.dogen.variability/types/type.hpp"

namespace masd::dogen::variability {

class type_repository final {
public:
    type_repository() = default;
    type_repository(const type_repository&) = default;
    type_repository(type_repository&&) = default;
    ~type_repository() = default;

public:
    type_repository(
        const std::list<masd::dogen::variability::type>& all_types,
        const std::unordered_map<std::string, masd::dogen::variability::type>& types_by_name,
        const std::unordered_map<std::string, std::list<masd::dogen::variability::type> >& types_by_facet_name,
        const std::unordered_map<std::string, std::list<masd::dogen::variability::type> >& types_by_formatter_name,
        const std::unordered_map<std::string, std::list<masd::dogen::variability::type> >& types_by_backend_name,
        const std::unordered_map<std::string, masd::dogen::variability::type>& partially_matchable_types);

public:
    /**
     * @brief All the types available, without categorisation.
     */
    /**@{*/
    const std::list<masd::dogen::variability::type>& all_types() const;
    std::list<masd::dogen::variability::type>& all_types();
    void all_types(const std::list<masd::dogen::variability::type>& v);
    void all_types(const std::list<masd::dogen::variability::type>&& v);
    /**@}*/

    /**
     * @brief Types by qualified name.
     */
    /**@{*/
    const std::unordered_map<std::string, masd::dogen::variability::type>& types_by_name() const;
    std::unordered_map<std::string, masd::dogen::variability::type>& types_by_name();
    void types_by_name(const std::unordered_map<std::string, masd::dogen::variability::type>& v);
    void types_by_name(const std::unordered_map<std::string, masd::dogen::variability::type>&& v);
    /**@}*/

    /**
     * @brief Types by facet names, for all models.
     */
    /**@{*/
    const std::unordered_map<std::string, std::list<masd::dogen::variability::type> >& types_by_facet_name() const;
    std::unordered_map<std::string, std::list<masd::dogen::variability::type> >& types_by_facet_name();
    void types_by_facet_name(const std::unordered_map<std::string, std::list<masd::dogen::variability::type> >& v);
    void types_by_facet_name(const std::unordered_map<std::string, std::list<masd::dogen::variability::type> >&& v);
    /**@}*/

    /**
     * @brief Types by formatter names, for all models.
     */
    /**@{*/
    const std::unordered_map<std::string, std::list<masd::dogen::variability::type> >& types_by_formatter_name() const;
    std::unordered_map<std::string, std::list<masd::dogen::variability::type> >& types_by_formatter_name();
    void types_by_formatter_name(const std::unordered_map<std::string, std::list<masd::dogen::variability::type> >& v);
    void types_by_formatter_name(const std::unordered_map<std::string, std::list<masd::dogen::variability::type> >&& v);
    /**@}*/

    /**
     * @brief Types by backend name.
     */
    /**@{*/
    const std::unordered_map<std::string, std::list<masd::dogen::variability::type> >& types_by_backend_name() const;
    std::unordered_map<std::string, std::list<masd::dogen::variability::type> >& types_by_backend_name();
    void types_by_backend_name(const std::unordered_map<std::string, std::list<masd::dogen::variability::type> >& v);
    void types_by_backend_name(const std::unordered_map<std::string, std::list<masd::dogen::variability::type> >&& v);
    /**@}*/

    /**
     * @brief Types which can be partially matched.
     */
    /**@{*/
    const std::unordered_map<std::string, masd::dogen::variability::type>& partially_matchable_types() const;
    std::unordered_map<std::string, masd::dogen::variability::type>& partially_matchable_types();
    void partially_matchable_types(const std::unordered_map<std::string, masd::dogen::variability::type>& v);
    void partially_matchable_types(const std::unordered_map<std::string, masd::dogen::variability::type>&& v);
    /**@}*/

public:
    bool operator==(const type_repository& rhs) const;
    bool operator!=(const type_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(type_repository& other) noexcept;
    type_repository& operator=(type_repository other);

private:
    std::list<masd::dogen::variability::type> all_types_;
    std::unordered_map<std::string, masd::dogen::variability::type> types_by_name_;
    std::unordered_map<std::string, std::list<masd::dogen::variability::type> > types_by_facet_name_;
    std::unordered_map<std::string, std::list<masd::dogen::variability::type> > types_by_formatter_name_;
    std::unordered_map<std::string, std::list<masd::dogen::variability::type> > types_by_backend_name_;
    std::unordered_map<std::string, masd::dogen::variability::type> partially_matchable_types_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::variability::type_repository& lhs,
    masd::dogen::variability::type_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
