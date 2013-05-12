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
#ifndef DOGEN_CPP_TYPES_NESTED_TYPE_VIEW_MODEL_HPP
#define DOGEN_CPP_TYPES_NESTED_TYPE_VIEW_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include <string>
#include "dogen/cpp/serialization/nested_type_view_model_fwd_ser.hpp"
#include "dogen/cpp/types/nested_type_view_model.hpp"

namespace dogen {
namespace cpp {

class nested_type_view_model final {
public:
    nested_type_view_model(const nested_type_view_model&) = default;
    nested_type_view_model(nested_type_view_model&&) = default;
    ~nested_type_view_model() = default;

public:
    nested_type_view_model();

public:
    nested_type_view_model(
        const std::string& name,
        const std::string& identifiable_name,
        const std::string& complete_name,
        const std::string& complete_identifiable_name,
        const bool is_primitive,
        const bool is_enumeration,
        const bool is_string_like,
        const bool is_char_like,
        const bool is_int_like,
        const bool is_sequence_container,
        const bool is_associative_container,
        const bool is_smart_pointer,
        const bool is_optional_like,
        const bool is_variant_like,
        const std::list<dogen::cpp::nested_type_view_model>& children,
        const std::list<std::string>& namespaces,
        const bool is_filesystem_path,
        const bool is_date,
        const bool is_ptime,
        const bool is_time_duration,
        const bool is_pair);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const nested_type_view_model& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, nested_type_view_model& v, unsigned int version);

public:
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

    const std::string& identifiable_name() const;
    std::string& identifiable_name();
    void identifiable_name(const std::string& v);
    void identifiable_name(const std::string&& v);

    const std::string& complete_name() const;
    std::string& complete_name();
    void complete_name(const std::string& v);
    void complete_name(const std::string&& v);

    const std::string& complete_identifiable_name() const;
    std::string& complete_identifiable_name();
    void complete_identifiable_name(const std::string& v);
    void complete_identifiable_name(const std::string&& v);

    bool is_primitive() const;
    void is_primitive(const bool v);

    bool is_enumeration() const;
    void is_enumeration(const bool v);

    bool is_string_like() const;
    void is_string_like(const bool v);

    bool is_char_like() const;
    void is_char_like(const bool v);

    bool is_int_like() const;
    void is_int_like(const bool v);

    bool is_sequence_container() const;
    void is_sequence_container(const bool v);

    bool is_associative_container() const;
    void is_associative_container(const bool v);

    bool is_smart_pointer() const;
    void is_smart_pointer(const bool v);

    bool is_optional_like() const;
    void is_optional_like(const bool v);

    bool is_variant_like() const;
    void is_variant_like(const bool v);

    const std::list<dogen::cpp::nested_type_view_model>& children() const;
    std::list<dogen::cpp::nested_type_view_model>& children();
    void children(const std::list<dogen::cpp::nested_type_view_model>& v);
    void children(const std::list<dogen::cpp::nested_type_view_model>&& v);

    const std::list<std::string>& namespaces() const;
    std::list<std::string>& namespaces();
    void namespaces(const std::list<std::string>& v);
    void namespaces(const std::list<std::string>&& v);

    bool is_filesystem_path() const;
    void is_filesystem_path(const bool v);

    bool is_date() const;
    void is_date(const bool v);

    bool is_ptime() const;
    void is_ptime(const bool v);

    bool is_time_duration() const;
    void is_time_duration(const bool v);

    bool is_pair() const;
    void is_pair(const bool v);

public:
    bool operator==(const nested_type_view_model& rhs) const;
    bool operator!=(const nested_type_view_model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(nested_type_view_model& other) noexcept;
    nested_type_view_model& operator=(nested_type_view_model other);

private:
    std::string name_;
    std::string identifiable_name_;
    std::string complete_name_;
    std::string complete_identifiable_name_;
    bool is_primitive_;
    bool is_enumeration_;
    bool is_string_like_;
    bool is_char_like_;
    bool is_int_like_;
    bool is_sequence_container_;
    bool is_associative_container_;
    bool is_smart_pointer_;
    bool is_optional_like_;
    bool is_variant_like_;
    std::list<dogen::cpp::nested_type_view_model> children_;
    std::list<std::string> namespaces_;
    bool is_filesystem_path_;
    bool is_date_;
    bool is_ptime_;
    bool is_time_duration_;
    bool is_pair_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::nested_type_view_model& lhs,
    dogen::cpp::nested_type_view_model& rhs) {
    lhs.swap(rhs);
}

}

#endif
