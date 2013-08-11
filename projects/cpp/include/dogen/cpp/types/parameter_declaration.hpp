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
#ifndef DOGEN_CPP_TYPES_PARAMETER_DECLARATION_HPP
#define DOGEN_CPP_TYPES_PARAMETER_DECLARATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <string>
#include "dogen/cpp/serialization/parameter_declaration_fwd_ser.hpp"
#include "dogen/cpp/types/declarator_fwd.hpp"

namespace dogen {
namespace cpp {

class parameter_declaration final {
public:
    parameter_declaration() = default;
    parameter_declaration(const parameter_declaration&) = default;
    parameter_declaration(parameter_declaration&&) = default;
    ~parameter_declaration() = default;

public:
    parameter_declaration(
        const boost::shared_ptr<dogen::cpp::declarator>& declarator,
        const std::string& assignment_expression);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const parameter_declaration& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, parameter_declaration& v, unsigned int version);

public:
    const boost::shared_ptr<dogen::cpp::declarator>& declarator() const;
    boost::shared_ptr<dogen::cpp::declarator>& declarator();
    void declarator(const boost::shared_ptr<dogen::cpp::declarator>& v);
    void declarator(const boost::shared_ptr<dogen::cpp::declarator>&& v);

    const std::string& assignment_expression() const;
    std::string& assignment_expression();
    void assignment_expression(const std::string& v);
    void assignment_expression(const std::string&& v);

public:
    bool operator==(const parameter_declaration& rhs) const;
    bool operator!=(const parameter_declaration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(parameter_declaration& other) noexcept;
    parameter_declaration& operator=(parameter_declaration other);

private:
    boost::shared_ptr<dogen::cpp::declarator> declarator_;
    std::string assignment_expression_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::parameter_declaration& lhs,
    dogen::cpp::parameter_declaration& rhs) {
    lhs.swap(rhs);
}

}

#endif
