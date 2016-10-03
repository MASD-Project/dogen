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
#ifndef DOGEN_YARN_TYPES_EXCEPTION_HPP
#define DOGEN_YARN_TYPES_EXCEPTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen/yarn/types/element.hpp"
#include "dogen/yarn/serialization/exception_fwd_ser.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Represents an exception which can be thrown.
 */
class exception final : public dogen::yarn::element {
public:
    exception() = default;
    exception(const exception&) = default;
    exception(exception&&) = default;

    virtual ~exception() noexcept { }

public:
    exception(
        const std::string& documentation,
        const dogen::dynamic::object& extensions,
        const dogen::yarn::name& name,
        const dogen::yarn::generation_types generation_type,
        const dogen::yarn::origin_types origin_type,
        const boost::optional<dogen::yarn::name>& contained_by,
        const bool in_global_module,
        const bool is_element_extension);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::exception& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::exception& v, unsigned int version);

public:
    using element::accept;

    virtual void accept(const element_visitor& v) const override;
    virtual void accept(element_visitor& v) const override;
    virtual void accept(const element_visitor& v) override;
    virtual void accept(element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    bool operator==(const exception& rhs) const;
    bool operator!=(const exception& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::yarn::element& other) const override;

public:
    void swap(exception& other) noexcept;
    exception& operator=(exception other);

};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::exception& lhs,
    dogen::yarn::exception& rhs) {
    lhs.swap(rhs);
}

}

#endif
