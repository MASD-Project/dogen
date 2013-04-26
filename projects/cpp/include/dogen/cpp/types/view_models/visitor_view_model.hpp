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
#ifndef DOGEN_CPP_TYPES_VIEW_MODELS_VISITOR_VIEW_MODEL_HPP
#define DOGEN_CPP_TYPES_VIEW_MODELS_VISITOR_VIEW_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include <string>
#include "dogen/cpp/serialization/view_models/visitor_view_model_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace view_models {

class visitor_view_model final {
public:
    visitor_view_model() = default;
    visitor_view_model(const visitor_view_model&) = default;
    visitor_view_model(visitor_view_model&&) = default;
    ~visitor_view_model() = default;

public:
    visitor_view_model(
        const std::string& name,
        const std::list<std::string>& types);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const visitor_view_model& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, visitor_view_model& v, unsigned int version);

public:
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

    const std::list<std::string>& types() const;
    std::list<std::string>& types();
    void types(const std::list<std::string>& v);
    void types(const std::list<std::string>&& v);

public:
    bool operator==(const visitor_view_model& rhs) const;
    bool operator!=(const visitor_view_model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(visitor_view_model& other) noexcept;
    visitor_view_model& operator=(visitor_view_model other);

private:
    std::string name_;
    std::list<std::string> types_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::view_models::visitor_view_model& lhs,
    dogen::cpp::view_models::visitor_view_model& rhs) {
    lhs.swap(rhs);
}

}

#endif
