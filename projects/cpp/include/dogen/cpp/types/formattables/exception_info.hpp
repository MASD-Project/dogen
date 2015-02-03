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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_EXCEPTION_INFO_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_EXCEPTION_INFO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/cpp/serialization/formattables/exception_info_fwd_ser.hpp"
#include "dogen/cpp/types/formattables/entity.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Represents a C++ exception.
 */
class exception_info final : public dogen::cpp::formattables::entity {
public:
    exception_info() = default;
    exception_info(const exception_info&) = default;
    exception_info(exception_info&&) = default;

    virtual ~exception_info() noexcept { }

public:
    exception_info(
        const std::string& identity,
        const std::string& name,
        const std::string& documentation,
        const std::list<std::string>& namespaces,
        const std::unordered_map<std::string, dogen::cpp::formattables::file_settings>& file_settings_for_formatter);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const exception_info& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, exception_info& v, unsigned int version);

public:
    virtual void accept(const formattable_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(formattable_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(const formattable_visitor& v) override {
        v.visit(*this);
    }

    virtual void accept(formattable_visitor& v) override {
        v.visit(*this);
    }

public:
    void to_stream(std::ostream& s) const override;

public:
    bool operator==(const exception_info& rhs) const;
    bool operator!=(const exception_info& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::cpp::formattables::formattable& other) const override;

public:
    void swap(exception_info& other) noexcept;
    exception_info& operator=(exception_info other);

};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::formattables::exception_info& lhs,
    dogen::cpp::formattables::exception_info& rhs) {
    lhs.swap(rhs);
}

}

#endif
