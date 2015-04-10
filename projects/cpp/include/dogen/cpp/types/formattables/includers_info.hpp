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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_INCLUDERS_INFO_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_INCLUDERS_INFO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen/cpp/types/formattables/entity.hpp"
#include "dogen/cpp/serialization/formattables/includers_info_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

class includers_info final : public dogen::cpp::formattables::entity {
public:
    includers_info() = default;
    includers_info(const includers_info&) = default;
    includers_info(includers_info&&) = default;

    virtual ~includers_info() noexcept { }

public:
    includers_info(
        const std::string& identity,
        const std::string& name,
        const std::string& documentation,
        const std::list<std::string>& namespaces,
        const dogen::cpp::settings::bundle& settings);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const includers_info& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, includers_info& v, unsigned int version);

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
    bool operator==(const includers_info& rhs) const;
    bool operator!=(const includers_info& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::cpp::formattables::formattable& other) const override;

public:
    void swap(includers_info& other) noexcept;
    includers_info& operator=(includers_info other);

};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::formattables::includers_info& lhs,
    dogen::cpp::formattables::includers_info& rhs) {
    lhs.swap(rhs);
}

}

#endif
