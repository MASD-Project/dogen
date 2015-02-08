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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_FORMATTABLE_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_FORMATTABLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include <string>
#include <unordered_map>
#include "dogen/cpp/serialization/formattables/formattable_fwd_ser.hpp"
#include "dogen/cpp/types/formattables/file_properties.hpp"
#include "dogen/cpp/types/formattables/formattable_visitor.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

class formattable {
public:
    formattable() = default;
    formattable(const formattable&) = default;
    formattable(formattable&&) = default;

    virtual ~formattable() noexcept = 0;

public:
    formattable(
        const std::string& identity,
        const std::unordered_map<std::string, dogen::cpp::formattables::file_properties>& file_properties_by_formatter_name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const formattable& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, formattable& v, unsigned int version);

public:
    virtual void accept(const formattable_visitor& v) const = 0;
    virtual void accept(formattable_visitor& v) const = 0;
    virtual void accept(const formattable_visitor& v) = 0;
    virtual void accept(formattable_visitor& v) = 0;

public:
    virtual void to_stream(std::ostream& s) const;

public:
    const std::string& identity() const;
    std::string& identity();
    void identity(const std::string& v);
    void identity(const std::string&& v);

    const std::unordered_map<std::string, dogen::cpp::formattables::file_properties>& file_properties_by_formatter_name() const;
    std::unordered_map<std::string, dogen::cpp::formattables::file_properties>& file_properties_by_formatter_name();
    void file_properties_by_formatter_name(const std::unordered_map<std::string, dogen::cpp::formattables::file_properties>& v);
    void file_properties_by_formatter_name(const std::unordered_map<std::string, dogen::cpp::formattables::file_properties>&& v);

protected:
    bool compare(const formattable& rhs) const;
public:
    virtual bool equals(const formattable& other) const = 0;

protected:
    void swap(formattable& other) noexcept;

private:
    std::string identity_;
    std::unordered_map<std::string, dogen::cpp::formattables::file_properties> file_properties_by_formatter_name_;
};

inline formattable::~formattable() noexcept { }

inline bool operator==(const formattable& lhs, const formattable& rhs) {
    return lhs.equals(rhs);
}

} } }



#endif
