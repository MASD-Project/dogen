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
#ifndef DOGEN_UPSILON_TYPES_TYPE_HPP
#define DOGEN_UPSILON_TYPES_TYPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include <vector>
#include <algorithm>
#include "dogen/upsilon/types/type_visitor_fwd.hpp"
#include "dogen/upsilon/serialization/type_fwd_ser.hpp"

namespace dogen {
namespace upsilon {

class type {
public:
    type() = default;
    type(const type&) = default;
    type(type&&) = default;

    virtual ~type() noexcept = 0;

public:
    type(
        const std::string& name,
        const std::string& extends,
        const std::string& comment,
        const std::vector<std::string>& tag_refs,
        const std::string& pof_id);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::upsilon::type& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::upsilon::type& v, unsigned int version);

public:
    virtual void accept(const type_visitor& v) const = 0;
    virtual void accept(type_visitor& v) const = 0;
    virtual void accept(const type_visitor& v) = 0;
    virtual void accept(type_visitor& v) = 0;

public:
    virtual void to_stream(std::ostream& s) const;

public:
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

    const std::string& extends() const;
    std::string& extends();
    void extends(const std::string& v);
    void extends(const std::string&& v);

    const std::string& comment() const;
    std::string& comment();
    void comment(const std::string& v);
    void comment(const std::string&& v);

    const std::vector<std::string>& tag_refs() const;
    std::vector<std::string>& tag_refs();
    void tag_refs(const std::vector<std::string>& v);
    void tag_refs(const std::vector<std::string>&& v);

    const std::string& pof_id() const;
    std::string& pof_id();
    void pof_id(const std::string& v);
    void pof_id(const std::string&& v);

protected:
    bool compare(const type& rhs) const;
public:
    virtual bool equals(const type& other) const = 0;

protected:
    void swap(type& other) noexcept;

private:
    std::string name_;
    std::string extends_;
    std::string comment_;
    std::vector<std::string> tag_refs_;
    std::string pof_id_;
};

inline type::~type() noexcept { }

inline bool operator==(const type& lhs, const type& rhs) {
    return lhs.equals(rhs);
}

} }

#endif
