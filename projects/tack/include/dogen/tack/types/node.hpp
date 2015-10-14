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
#ifndef DOGEN_TACK_TYPES_NODE_HPP
#define DOGEN_TACK_TYPES_NODE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen/tack/types/name.hpp"
#include "dogen/tack/types/node_fwd.hpp"
#include "dogen/tack/serialization/node_fwd_ser.hpp"

namespace dogen {
namespace tack {

class node final {
public:
    node() = default;
    node(const node&) = default;
    node(node&&) = default;
    ~node() = default;

public:
    node(
        const boost::shared_ptr<dogen::tack::node>& parent,
        const dogen::tack::name& data,
        const std::list<boost::shared_ptr<dogen::tack::node> >& children);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const node& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, node& v, unsigned int version);

public:
    const boost::shared_ptr<dogen::tack::node>& parent() const;
    boost::shared_ptr<dogen::tack::node>& parent();
    void parent(const boost::shared_ptr<dogen::tack::node>& v);
    void parent(const boost::shared_ptr<dogen::tack::node>&& v);

    const dogen::tack::name& data() const;
    dogen::tack::name& data();
    void data(const dogen::tack::name& v);
    void data(const dogen::tack::name&& v);

    const std::list<boost::shared_ptr<dogen::tack::node> >& children() const;
    std::list<boost::shared_ptr<dogen::tack::node> >& children();
    void children(const std::list<boost::shared_ptr<dogen::tack::node> >& v);
    void children(const std::list<boost::shared_ptr<dogen::tack::node> >&& v);

public:
    bool operator==(const node& rhs) const;
    bool operator!=(const node& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(node& other) noexcept;
    node& operator=(node other);

private:
    boost::shared_ptr<dogen::tack::node> parent_;
    dogen::tack::name data_;
    std::list<boost::shared_ptr<dogen::tack::node> > children_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::tack::node& lhs,
    dogen::tack::node& rhs) {
    lhs.swap(rhs);
}

}

#endif
