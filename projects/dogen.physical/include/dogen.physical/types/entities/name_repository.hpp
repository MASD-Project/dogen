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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_NAME_REPOSITORY_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_NAME_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "dogen.physical/types/entities/name.hpp"
#include "dogen.physical/types/entities/name_group.hpp"

namespace dogen::physical::entities {

/**
 * @brief Repository containing physical names, indexed as required by use cases.
 */
class name_repository final {
public:
    name_repository() = default;
    name_repository(const name_repository&) = default;
    name_repository(name_repository&&) = default;
    ~name_repository() = default;

public:
    name_repository(
        const std::list<dogen::physical::entities::name>& all,
        const std::unordered_map<std::string, std::unordered_set<std::string> >& facet_names_by_backend_name,
        const std::unordered_map<std::string, std::unordered_set<std::string> >& formatter_names_by_backend_name,
        const std::unordered_map<std::string, dogen::physical::entities::name_group>& by_meta_name,
        const std::unordered_map<std::string, std::unordered_map<std::string, std::list<std::string> > >& by_backend_by_facet);

public:
    const std::list<dogen::physical::entities::name>& all() const;
    std::list<dogen::physical::entities::name>& all();
    void all(const std::list<dogen::physical::entities::name>& v);
    void all(const std::list<dogen::physical::entities::name>&& v);

    const std::unordered_map<std::string, std::unordered_set<std::string> >& facet_names_by_backend_name() const;
    std::unordered_map<std::string, std::unordered_set<std::string> >& facet_names_by_backend_name();
    void facet_names_by_backend_name(const std::unordered_map<std::string, std::unordered_set<std::string> >& v);
    void facet_names_by_backend_name(const std::unordered_map<std::string, std::unordered_set<std::string> >&& v);

    const std::unordered_map<std::string, std::unordered_set<std::string> >& formatter_names_by_backend_name() const;
    std::unordered_map<std::string, std::unordered_set<std::string> >& formatter_names_by_backend_name();
    void formatter_names_by_backend_name(const std::unordered_map<std::string, std::unordered_set<std::string> >& v);
    void formatter_names_by_backend_name(const std::unordered_map<std::string, std::unordered_set<std::string> >&& v);

    const std::unordered_map<std::string, dogen::physical::entities::name_group>& by_meta_name() const;
    std::unordered_map<std::string, dogen::physical::entities::name_group>& by_meta_name();
    void by_meta_name(const std::unordered_map<std::string, dogen::physical::entities::name_group>& v);
    void by_meta_name(const std::unordered_map<std::string, dogen::physical::entities::name_group>&& v);

    const std::unordered_map<std::string, std::unordered_map<std::string, std::list<std::string> > >& by_backend_by_facet() const;
    std::unordered_map<std::string, std::unordered_map<std::string, std::list<std::string> > >& by_backend_by_facet();
    void by_backend_by_facet(const std::unordered_map<std::string, std::unordered_map<std::string, std::list<std::string> > >& v);
    void by_backend_by_facet(const std::unordered_map<std::string, std::unordered_map<std::string, std::list<std::string> > >&& v);

public:
    bool operator==(const name_repository& rhs) const;
    bool operator!=(const name_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(name_repository& other) noexcept;
    name_repository& operator=(name_repository other);

private:
    std::list<dogen::physical::entities::name> all_;
    std::unordered_map<std::string, std::unordered_set<std::string> > facet_names_by_backend_name_;
    std::unordered_map<std::string, std::unordered_set<std::string> > formatter_names_by_backend_name_;
    std::unordered_map<std::string, dogen::physical::entities::name_group> by_meta_name_;
    std::unordered_map<std::string, std::unordered_map<std::string, std::list<std::string> > > by_backend_by_facet_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::name_repository& lhs,
    dogen::physical::entities::name_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
