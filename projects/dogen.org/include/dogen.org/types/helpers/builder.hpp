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
#ifndef DOGEN_ORG_TYPES_HELPERS_BUILDER_HPP
#define DOGEN_ORG_TYPES_HELPERS_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen.org/types/helpers/node_fwd.hpp"

namespace dogen::org::helpers {

class builder final {
public:
    builder() = default;
    builder(const builder&) = default;
    builder(builder&&) = default;
    ~builder() = default;

public:
    explicit builder(const boost::shared_ptr<dogen::org::helpers::node>& root_);

public:
    const boost::shared_ptr<dogen::org::helpers::node>& root_() const;
    boost::shared_ptr<dogen::org::helpers::node>& root_();
    void root_(const boost::shared_ptr<dogen::org::helpers::node>& v);
    void root_(const boost::shared_ptr<dogen::org::helpers::node>&& v);

public:
    bool operator==(const builder& rhs) const;
    bool operator!=(const builder& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(builder& other) noexcept;
    builder& operator=(builder other);

private:
    boost::shared_ptr<dogen::org::helpers::node> root__;
};

}

namespace std {

template<>
inline void swap(
    dogen::org::helpers::builder& lhs,
    dogen::org::helpers::builder& rhs) {
    lhs.swap(rhs);
}

}

#endif
