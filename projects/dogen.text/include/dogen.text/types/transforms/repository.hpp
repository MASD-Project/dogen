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
#ifndef DOGEN_TEXT_TYPES_TRANSFORMS_REPOSITORY_HPP
#define DOGEN_TEXT_TYPES_TRANSFORMS_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <memory>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.text/types/transforms/helper_transform_fwd.hpp"

namespace dogen::text::transforms {

class repository final {
public:
    repository() = default;
    repository(const repository&) = default;
    repository(repository&&) = default;
    ~repository() = default;

public:
    explicit repository(const std::unordered_map<std::string, std::unordered_map<std::string, std::list<std::shared_ptr<dogen::text::transforms::helper_transform> > > >& helper_transforms);

public:
    const std::unordered_map<std::string, std::unordered_map<std::string, std::list<std::shared_ptr<dogen::text::transforms::helper_transform> > > >& helper_transforms() const;
    std::unordered_map<std::string, std::unordered_map<std::string, std::list<std::shared_ptr<dogen::text::transforms::helper_transform> > > >& helper_transforms();
    void helper_transforms(const std::unordered_map<std::string, std::unordered_map<std::string, std::list<std::shared_ptr<dogen::text::transforms::helper_transform> > > >& v);
    void helper_transforms(const std::unordered_map<std::string, std::unordered_map<std::string, std::list<std::shared_ptr<dogen::text::transforms::helper_transform> > > >&& v);

public:
    bool operator==(const repository& rhs) const;
    bool operator!=(const repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(repository& other) noexcept;
    repository& operator=(repository other);

private:
    std::unordered_map<std::string, std::unordered_map<std::string, std::list<std::shared_ptr<dogen::text::transforms::helper_transform> > > > helper_transforms_;
};

}

namespace std {

template<>
inline void swap(
    dogen::text::transforms::repository& lhs,
    dogen::text::transforms::repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
