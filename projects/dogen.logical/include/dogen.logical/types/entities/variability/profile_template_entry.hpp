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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_VARIABILITY_PROFILE_TEMPLATE_ENTRY_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_VARIABILITY_PROFILE_TEMPLATE_ENTRY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include <algorithm>
#include "dogen.logical/types/entities/variability/abstract_profile_entry.hpp"

namespace dogen::logical::entities::variability {

class profile_template_entry final : public dogen::logical::entities::variability::abstract_profile_entry {
public:
    profile_template_entry() = default;
    profile_template_entry(const profile_template_entry&) = default;
    profile_template_entry(profile_template_entry&&) = default;

    virtual ~profile_template_entry() noexcept { }

public:
    profile_template_entry(
        const std::string& documentation,
        const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
        const dogen::logical::entities::name& name,
        const std::string& original_key,
        const std::string& key,
        const std::list<std::string>& value,
        const std::string& instantiation_domain_name);

public:
    void to_stream(std::ostream& s) const override;

public:
    const std::string& instantiation_domain_name() const;
    std::string& instantiation_domain_name();
    void instantiation_domain_name(const std::string& v);
    void instantiation_domain_name(const std::string&& v);

public:
    bool operator==(const profile_template_entry& rhs) const;
    bool operator!=(const profile_template_entry& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::logical::entities::variability::abstract_profile_entry& other) const override;

public:
    void swap(profile_template_entry& other) noexcept;
    profile_template_entry& operator=(profile_template_entry other);

private:
    std::string instantiation_domain_name_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::variability::profile_template_entry& lhs,
    dogen::logical::entities::variability::profile_template_entry& rhs) {
    lhs.swap(rhs);
}

}

#endif
