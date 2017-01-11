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
#ifndef DOGEN_UPSILON_TYPES_MODEL_HPP
#define DOGEN_UPSILON_TYPES_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include "dogen/upsilon/types/config.hpp"
#include "dogen/upsilon/types/schema.hpp"
#include "dogen/upsilon/types/type_information.hpp"
#include "dogen/upsilon/serialization/model_fwd_ser.hpp"

namespace dogen {
namespace upsilon {

class model final {
public:
    model() = default;
    model(const model&) = default;
    model(model&&) = default;
    ~model() = default;

public:
    model(
        const dogen::upsilon::schema& target,
        const std::list<dogen::upsilon::schema>& refs,
        const std::list<dogen::upsilon::type_information>& type_information,
        const dogen::upsilon::config& config);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::upsilon::model& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::upsilon::model& v, unsigned int version);

public:
    const dogen::upsilon::schema& target() const;
    dogen::upsilon::schema& target();
    void target(const dogen::upsilon::schema& v);
    void target(const dogen::upsilon::schema&& v);

    const std::list<dogen::upsilon::schema>& refs() const;
    std::list<dogen::upsilon::schema>& refs();
    void refs(const std::list<dogen::upsilon::schema>& v);
    void refs(const std::list<dogen::upsilon::schema>&& v);

    const std::list<dogen::upsilon::type_information>& type_information() const;
    std::list<dogen::upsilon::type_information>& type_information();
    void type_information(const std::list<dogen::upsilon::type_information>& v);
    void type_information(const std::list<dogen::upsilon::type_information>&& v);

    const dogen::upsilon::config& config() const;
    dogen::upsilon::config& config();
    void config(const dogen::upsilon::config& v);
    void config(const dogen::upsilon::config&& v);

public:
    bool operator==(const model& rhs) const;
    bool operator!=(const model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(model& other) noexcept;
    model& operator=(model other);

private:
    dogen::upsilon::schema target_;
    std::list<dogen::upsilon::schema> refs_;
    std::list<dogen::upsilon::type_information> type_information_;
    dogen::upsilon::config config_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::upsilon::model& lhs,
    dogen::upsilon::model& rhs) {
    lhs.swap(rhs);
}

}

#endif
