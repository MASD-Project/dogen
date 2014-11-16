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
#ifndef DOGEN_CPP_TYPES_NEW_CLASS_INFO_HPP
#define DOGEN_CPP_TYPES_NEW_CLASS_INFO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/cpp/serialization/new_class_info_fwd_ser.hpp"
#include "dogen/cpp/types/abilities.hpp"
#include "dogen/cpp/types/class_aspects.hpp"
#include "dogen/cpp/types/entity.hpp"
#include "dogen/cpp/types/inheritance.hpp"
#include "dogen/cpp/types/state.hpp"

namespace dogen {
namespace cpp {

class new_class_info final : public dogen::cpp::entity {
public:
    new_class_info() = default;
    new_class_info(const new_class_info&) = default;
    new_class_info(new_class_info&&) = default;

    virtual ~new_class_info() noexcept { }

public:
    new_class_info(
        const std::string& name,
        const std::string& documentation,
        const std::list<std::string>& namespaces,
        const std::unordered_map<std::string, dogen::cpp::path_spec_details>& path_spec_details_for_formatter,
        const dogen::cpp::state& state,
        const dogen::cpp::inheritance& inheritance,
        const dogen::cpp::abilities& abilities,
        const dogen::cpp::class_aspects& aspects);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const new_class_info& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, new_class_info& v, unsigned int version);

public:
    virtual void accept(const entity_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(entity_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(const entity_visitor& v) override {
        v.visit(*this);
    }

    virtual void accept(entity_visitor& v) override {
        v.visit(*this);
    }

public:
    void to_stream(std::ostream& s) const override;

public:
    const dogen::cpp::state& state() const;
    dogen::cpp::state& state();
    void state(const dogen::cpp::state& v);
    void state(const dogen::cpp::state&& v);

    const dogen::cpp::inheritance& inheritance() const;
    dogen::cpp::inheritance& inheritance();
    void inheritance(const dogen::cpp::inheritance& v);
    void inheritance(const dogen::cpp::inheritance&& v);

    const dogen::cpp::abilities& abilities() const;
    dogen::cpp::abilities& abilities();
    void abilities(const dogen::cpp::abilities& v);
    void abilities(const dogen::cpp::abilities&& v);

    const dogen::cpp::class_aspects& aspects() const;
    dogen::cpp::class_aspects& aspects();
    void aspects(const dogen::cpp::class_aspects& v);
    void aspects(const dogen::cpp::class_aspects&& v);

public:
    bool operator==(const new_class_info& rhs) const;
    bool operator!=(const new_class_info& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::cpp::entity& other) const override;

public:
    void swap(new_class_info& other) noexcept;
    new_class_info& operator=(new_class_info other);

private:
    dogen::cpp::state state_;
    dogen::cpp::inheritance inheritance_;
    dogen::cpp::abilities abilities_;
    dogen::cpp::class_aspects aspects_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::new_class_info& lhs,
    dogen::cpp::new_class_info& rhs) {
    lhs.swap(rhs);
}

}

#endif
