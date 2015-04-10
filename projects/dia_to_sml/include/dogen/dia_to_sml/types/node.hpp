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
#ifndef DOGEN_DIA_TO_SML_TYPES_NODE_HPP
#define DOGEN_DIA_TO_SML_TYPES_NODE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen/sml/types/qname.hpp"
#include "dogen/dia_to_sml/types/node_fwd.hpp"
#include "dogen/dia_to_sml/serialization/node_fwd_ser.hpp"

namespace dogen {
namespace dia_to_sml {

class node final {
public:
    node() = default;
    node(const node&) = default;
    node(node&&) = default;
    ~node() = default;

public:
    node(
        const boost::shared_ptr<dogen::dia_to_sml::node>& parent,
        const dogen::sml::qname& data,
        const std::list<boost::shared_ptr<dogen::dia_to_sml::node> >& children);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const node& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, node& v, unsigned int version);

public:
    const boost::shared_ptr<dogen::dia_to_sml::node>& parent() const;
    boost::shared_ptr<dogen::dia_to_sml::node>& parent();
    void parent(const boost::shared_ptr<dogen::dia_to_sml::node>& v);
    void parent(const boost::shared_ptr<dogen::dia_to_sml::node>&& v);

    const dogen::sml::qname& data() const;
    dogen::sml::qname& data();
    void data(const dogen::sml::qname& v);
    void data(const dogen::sml::qname&& v);

    const std::list<boost::shared_ptr<dogen::dia_to_sml::node> >& children() const;
    std::list<boost::shared_ptr<dogen::dia_to_sml::node> >& children();
    void children(const std::list<boost::shared_ptr<dogen::dia_to_sml::node> >& v);
    void children(const std::list<boost::shared_ptr<dogen::dia_to_sml::node> >&& v);

public:
    bool operator==(const node& rhs) const;
    bool operator!=(const node& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(node& other) noexcept;
    node& operator=(node other);

private:
    boost::shared_ptr<dogen::dia_to_sml::node> parent_;
    dogen::sml::qname data_;
    std::list<boost::shared_ptr<dogen::dia_to_sml::node> > children_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::dia_to_sml::node& lhs,
    dogen::dia_to_sml::node& rhs) {
    lhs.swap(rhs);
}

}

#endif
