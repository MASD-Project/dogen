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
#ifndef DOGEN_ANNOTATIONS_TYPES_TYPE_REPOSITORY_HPP
#define DOGEN_ANNOTATIONS_TYPES_TYPE_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen/annotations/types/type.hpp"
#include "dogen/annotations/serialization/type_repository_fwd_ser.hpp"

namespace dogen {
namespace annotations {

class type_repository final {
public:
    type_repository() = default;
    type_repository(const type_repository&) = default;
    type_repository(type_repository&&) = default;
    ~type_repository() = default;

public:
    type_repository(
        const std::list<dogen::annotations::type>& all_types,
        const std::unordered_map<std::string, dogen::annotations::type>& types_by_name,
        const std::unordered_map<std::string, std::list<dogen::annotations::type> >& types_by_facet_name,
        const std::unordered_map<std::string, std::list<dogen::annotations::type> >& types_by_formatter_name,
        const std::unordered_map<std::string, std::list<dogen::annotations::type> >& types_by_model_name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::annotations::type_repository& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::annotations::type_repository& v, unsigned int version);

public:
    /**
     * @brief All the field definitions available, without categorisation.
     */
    /**@{*/
    const std::list<dogen::annotations::type>& all_types() const;
    std::list<dogen::annotations::type>& all_types();
    void all_types(const std::list<dogen::annotations::type>& v);
    void all_types(const std::list<dogen::annotations::type>&& v);
    /**@}*/

    /**
     * @brief All field definitions by qualified field definition name.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::annotations::type>& types_by_name() const;
    std::unordered_map<std::string, dogen::annotations::type>& types_by_name();
    void types_by_name(const std::unordered_map<std::string, dogen::annotations::type>& v);
    void types_by_name(const std::unordered_map<std::string, dogen::annotations::type>&& v);
    /**@}*/

    /**
     * @brief All field definitions for all qualified facet names, for all models.
     */
    /**@{*/
    const std::unordered_map<std::string, std::list<dogen::annotations::type> >& types_by_facet_name() const;
    std::unordered_map<std::string, std::list<dogen::annotations::type> >& types_by_facet_name();
    void types_by_facet_name(const std::unordered_map<std::string, std::list<dogen::annotations::type> >& v);
    void types_by_facet_name(const std::unordered_map<std::string, std::list<dogen::annotations::type> >&& v);
    /**@}*/

    /**
     * @brief All field definitions for all qualified formatter names, for all models.
     */
    /**@{*/
    const std::unordered_map<std::string, std::list<dogen::annotations::type> >& types_by_formatter_name() const;
    std::unordered_map<std::string, std::list<dogen::annotations::type> >& types_by_formatter_name();
    void types_by_formatter_name(const std::unordered_map<std::string, std::list<dogen::annotations::type> >& v);
    void types_by_formatter_name(const std::unordered_map<std::string, std::list<dogen::annotations::type> >&& v);
    /**@}*/

    const std::unordered_map<std::string, std::list<dogen::annotations::type> >& types_by_model_name() const;
    std::unordered_map<std::string, std::list<dogen::annotations::type> >& types_by_model_name();
    void types_by_model_name(const std::unordered_map<std::string, std::list<dogen::annotations::type> >& v);
    void types_by_model_name(const std::unordered_map<std::string, std::list<dogen::annotations::type> >&& v);

public:
    bool operator==(const type_repository& rhs) const;
    bool operator!=(const type_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(type_repository& other) noexcept;
    type_repository& operator=(type_repository other);

private:
    std::list<dogen::annotations::type> all_types_;
    std::unordered_map<std::string, dogen::annotations::type> types_by_name_;
    std::unordered_map<std::string, std::list<dogen::annotations::type> > types_by_facet_name_;
    std::unordered_map<std::string, std::list<dogen::annotations::type> > types_by_formatter_name_;
    std::unordered_map<std::string, std::list<dogen::annotations::type> > types_by_model_name_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::annotations::type_repository& lhs,
    dogen::annotations::type_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
