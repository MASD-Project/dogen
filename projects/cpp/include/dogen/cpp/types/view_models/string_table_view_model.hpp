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
#ifndef DOGEN_CPP_TYPES_VIEW_MODELS_STRING_TABLE_VIEW_MODEL_HPP
#define DOGEN_CPP_TYPES_VIEW_MODELS_STRING_TABLE_VIEW_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include <string>
#include <utility>
#include "dogen/cpp/serialization/view_models/string_table_view_model_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace view_models {

class string_table_view_model final {
public:
    string_table_view_model() = default;
    string_table_view_model(const string_table_view_model&) = default;
    string_table_view_model(string_table_view_model&&) = default;
    ~string_table_view_model() = default;

public:
    string_table_view_model(
        const std::string& name,
        const std::string& documentation,
        const std::list<std::pair<std::string, std::string> >& entries);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const string_table_view_model& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, string_table_view_model& v, unsigned int version);

public:
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);

    const std::list<std::pair<std::string, std::string> >& entries() const;
    std::list<std::pair<std::string, std::string> >& entries();
    void entries(const std::list<std::pair<std::string, std::string> >& v);
    void entries(const std::list<std::pair<std::string, std::string> >&& v);

public:
    bool operator==(const string_table_view_model& rhs) const;
    bool operator!=(const string_table_view_model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(string_table_view_model& other) noexcept;
    string_table_view_model& operator=(string_table_view_model other);

private:
    std::string name_;
    std::string documentation_;
    std::list<std::pair<std::string, std::string> > entries_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::view_models::string_table_view_model& lhs,
    dogen::cpp::view_models::string_table_view_model& rhs) {
    lhs.swap(rhs);
}

}

#endif
