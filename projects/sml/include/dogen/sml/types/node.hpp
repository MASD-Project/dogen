/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_SML_TYPES_NODE_HPP
#define DOGEN_SML_TYPES_NODE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <list>
#include "dogen/sml/serialization/node_fwd_ser.hpp"
#include "dogen/sml/types/node.hpp"
#include "dogen/sml/types/qname.hpp"

namespace dogen {
namespace sml {

class node final {
public:
    node() = default;
    node(const node&) = default;
    node(node&&) = default;
    ~node() = default;

public:
    node(
        const boost::shared_ptr<dogen::sml::node>& parent,
        const dogen::sml::qname& data,
        const std::list<boost::shared_ptr<dogen::sml::node> >& children);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const node& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, node& v, unsigned int version);

public:
    const boost::shared_ptr<dogen::sml::node>& parent() const;
    boost::shared_ptr<dogen::sml::node>& parent();
    void parent(const boost::shared_ptr<dogen::sml::node>& v);
    void parent(const boost::shared_ptr<dogen::sml::node>&& v);

    const dogen::sml::qname& data() const;
    dogen::sml::qname& data();
    void data(const dogen::sml::qname& v);
    void data(const dogen::sml::qname&& v);

    const std::list<boost::shared_ptr<dogen::sml::node> >& children() const;
    std::list<boost::shared_ptr<dogen::sml::node> >& children();
    void children(const std::list<boost::shared_ptr<dogen::sml::node> >& v);
    void children(const std::list<boost::shared_ptr<dogen::sml::node> >&& v);

public:
    bool operator==(const node& rhs) const;
    bool operator!=(const node& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(node& other) noexcept;
    node& operator=(node other);

private:
    boost::shared_ptr<dogen::sml::node> parent_;
    dogen::sml::qname data_;
    std::list<boost::shared_ptr<dogen::sml::node> > children_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::sml::node& lhs,
    dogen::sml::node& rhs) {
    lhs.swap(rhs);
}

}

#endif
