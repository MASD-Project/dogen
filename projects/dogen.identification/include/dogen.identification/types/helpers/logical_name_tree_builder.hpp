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
#ifndef DOGEN_IDENTIFICATION_TYPES_HELPERS_LOGICAL_NAME_TREE_BUILDER_HPP
#define DOGEN_IDENTIFICATION_TYPES_HELPERS_LOGICAL_NAME_TREE_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <boost/shared_ptr.hpp>

namespace dogen::identification::helpers {

class logical_name_tree_builder final {
public:
    logical_name_tree_builder() = default;
    logical_name_tree_builder(const logical_name_tree_builder&) = default;
    logical_name_tree_builder(logical_name_tree_builder&&) = default;
    ~logical_name_tree_builder() = default;

public:
    logical_name_tree_builder(
        const std::list<std::string>& names_,
        const boost::shared_ptr<dogen::identification::helpers::node>& root_,
        const boost::shared_ptr<dogen::identification::helpers::node>& current_);

public:
    const std::list<std::string>& names_() const;
    std::list<std::string>& names_();
    void names_(const std::list<std::string>& v);
    void names_(const std::list<std::string>&& v);

    const boost::shared_ptr<dogen::identification::helpers::node>& root_() const;
    boost::shared_ptr<dogen::identification::helpers::node>& root_();
    void root_(const boost::shared_ptr<dogen::identification::helpers::node>& v);
    void root_(const boost::shared_ptr<dogen::identification::helpers::node>&& v);

    const boost::shared_ptr<dogen::identification::helpers::node>& current_() const;
    boost::shared_ptr<dogen::identification::helpers::node>& current_();
    void current_(const boost::shared_ptr<dogen::identification::helpers::node>& v);
    void current_(const boost::shared_ptr<dogen::identification::helpers::node>&& v);

public:
    bool operator==(const logical_name_tree_builder& rhs) const;
    bool operator!=(const logical_name_tree_builder& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(logical_name_tree_builder& other) noexcept;
    logical_name_tree_builder& operator=(logical_name_tree_builder other);

private:
    std::list<std::string> names__;
    boost::shared_ptr<dogen::identification::helpers::node> root__;
    boost::shared_ptr<dogen::identification::helpers::node> current__;
};

}

namespace std {

template<>
inline void swap(
    dogen::identification::helpers::logical_name_tree_builder& lhs,
    dogen::identification::helpers::logical_name_tree_builder& rhs) {
    lhs.swap(rhs);
}

}

#endif
