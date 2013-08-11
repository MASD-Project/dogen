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
#ifndef DOGEN_CPP_TYPES_TEMPLATE_ID_HPP
#define DOGEN_CPP_TYPES_TEMPLATE_ID_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include <string>
#include "dogen/cpp/serialization/template_id_fwd_ser.hpp"
#include "dogen/cpp/types/template_argument.hpp"

namespace dogen {
namespace cpp {

class template_id final {
public:
    template_id() = default;
    template_id(const template_id&) = default;
    template_id(template_id&&) = default;
    ~template_id() = default;

public:
    template_id(
        const std::string& template_name,
        const std::list<dogen::cpp::template_argument>& template_argument_list);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const template_id& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, template_id& v, unsigned int version);

public:
    const std::string& template_name() const;
    std::string& template_name();
    void template_name(const std::string& v);
    void template_name(const std::string&& v);

    const std::list<dogen::cpp::template_argument>& template_argument_list() const;
    std::list<dogen::cpp::template_argument>& template_argument_list();
    void template_argument_list(const std::list<dogen::cpp::template_argument>& v);
    void template_argument_list(const std::list<dogen::cpp::template_argument>&& v);

public:
    bool operator==(const template_id& rhs) const;
    bool operator!=(const template_id& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(template_id& other) noexcept;
    template_id& operator=(template_id other);

private:
    std::string template_name_;
    std::list<dogen::cpp::template_argument> template_argument_list_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::template_id& lhs,
    dogen::cpp::template_id& rhs) {
    lhs.swap(rhs);
}

}

#endif
