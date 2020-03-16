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
#ifndef DOGEN_LOGICAL_TYPES_META_MODEL_ORM_ODB_TARGETS_HPP
#define DOGEN_LOGICAL_TYPES_META_MODEL_ORM_ODB_TARGETS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "dogen.logical/types/meta_model/orm/odb_target.hpp"

namespace dogen::logical::meta_model::orm {

class odb_targets final {
public:
    odb_targets() = default;
    odb_targets(const odb_targets&) = default;
    odb_targets(odb_targets&&) = default;
    ~odb_targets() = default;

public:
    odb_targets(
        const std::string& main_target_name,
        const std::string& common_odb_options,
        const std::list<dogen::logical::meta_model::orm::odb_target>& targets);

public:
    const std::string& main_target_name() const;
    std::string& main_target_name();
    void main_target_name(const std::string& v);
    void main_target_name(const std::string&& v);

    const std::string& common_odb_options() const;
    std::string& common_odb_options();
    void common_odb_options(const std::string& v);
    void common_odb_options(const std::string&& v);

    const std::list<dogen::logical::meta_model::orm::odb_target>& targets() const;
    std::list<dogen::logical::meta_model::orm::odb_target>& targets();
    void targets(const std::list<dogen::logical::meta_model::orm::odb_target>& v);
    void targets(const std::list<dogen::logical::meta_model::orm::odb_target>&& v);

public:
    bool operator==(const odb_targets& rhs) const;
    bool operator!=(const odb_targets& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(odb_targets& other) noexcept;
    odb_targets& operator=(odb_targets other);

private:
    std::string main_target_name_;
    std::string common_odb_options_;
    std::list<dogen::logical::meta_model::orm::odb_target> targets_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::meta_model::orm::odb_targets& lhs,
    dogen::logical::meta_model::orm::odb_targets& rhs) {
    lhs.swap(rhs);
}

}

#endif
