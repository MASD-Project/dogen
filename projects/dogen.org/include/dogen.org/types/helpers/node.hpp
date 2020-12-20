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
#ifndef DOGEN_ORG_TYPES_HELPERS_NODE_HPP
#define DOGEN_ORG_TYPES_HELPERS_NODE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen.org/types/helpers/node_fwd.hpp"
#include "dogen.org/types/entities/headline.hpp"

namespace dogen::org::helpers {

class node final {
public:
    node() = default;
    node(const node&) = default;
    node(node&&) = default;
    ~node() = default;

public:
    node(
        const dogen::org::entities::headline& data,
        const std::list<boost::shared_ptr<dogen::org::helpers::node> >& children);

public:
    const dogen::org::entities::headline& data() const;
    dogen::org::entities::headline& data();
    void data(const dogen::org::entities::headline& v);
    void data(const dogen::org::entities::headline&& v);

    const std::list<boost::shared_ptr<dogen::org::helpers::node> >& children() const;
    std::list<boost::shared_ptr<dogen::org::helpers::node> >& children();
    void children(const std::list<boost::shared_ptr<dogen::org::helpers::node> >& v);
    void children(const std::list<boost::shared_ptr<dogen::org::helpers::node> >&& v);

public:
    bool operator==(const node& rhs) const;
    bool operator!=(const node& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(node& other) noexcept;
    node& operator=(node other);

private:
    dogen::org::entities::headline data_;
    std::list<boost::shared_ptr<dogen::org::helpers::node> > children_;
};

}

namespace std {

template<>
inline void swap(
    dogen::org::helpers::node& lhs,
    dogen::org::helpers::node& rhs) {
    lhs.swap(rhs);
}

}

#endif
