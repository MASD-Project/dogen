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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_NEW_CLASS_INFO_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_NEW_CLASS_INFO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/cpp/serialization/formattables/new_class_info_fwd_ser.hpp"
#include "dogen/cpp/types/formattables/abilities.hpp"
#include "dogen/cpp/types/formattables/class_aspects.hpp"
#include "dogen/cpp/types/formattables/entity.hpp"
#include "dogen/cpp/types/formattables/inheritance.hpp"
#include "dogen/cpp/types/formattables/state.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

class new_class_info final : public dogen::cpp::formattables::entity {
public:
    new_class_info() = default;
    new_class_info(const new_class_info&) = default;
    new_class_info(new_class_info&&) = default;

    virtual ~new_class_info() noexcept { }

public:
    new_class_info(
        const std::string& identity,
        const std::unordered_map<std::string, boost::filesystem::path>& file_path_by_formatter_name,
        const std::string& name,
        const std::string& documentation,
        const std::list<std::string>& namespaces,
        const std::unordered_map<std::string, dogen::cpp::formattables::inclusion>& inclusion_by_formatter_name,
        const std::unordered_map<std::string, std::list<dogen::cpp::formattables::inclusion> >& inclusion_dependencies_by_formatter_name,
        const dogen::cpp::formattables::state& state,
        const dogen::cpp::formattables::inheritance& inheritance,
        const dogen::cpp::formattables::abilities& abilities,
        const dogen::cpp::formattables::class_aspects& aspects);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const new_class_info& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, new_class_info& v, unsigned int version);

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
    const dogen::cpp::formattables::state& state() const;
    dogen::cpp::formattables::state& state();
    void state(const dogen::cpp::formattables::state& v);
    void state(const dogen::cpp::formattables::state&& v);

    const dogen::cpp::formattables::inheritance& inheritance() const;
    dogen::cpp::formattables::inheritance& inheritance();
    void inheritance(const dogen::cpp::formattables::inheritance& v);
    void inheritance(const dogen::cpp::formattables::inheritance&& v);

    const dogen::cpp::formattables::abilities& abilities() const;
    dogen::cpp::formattables::abilities& abilities();
    void abilities(const dogen::cpp::formattables::abilities& v);
    void abilities(const dogen::cpp::formattables::abilities&& v);

    const dogen::cpp::formattables::class_aspects& aspects() const;
    dogen::cpp::formattables::class_aspects& aspects();
    void aspects(const dogen::cpp::formattables::class_aspects& v);
    void aspects(const dogen::cpp::formattables::class_aspects&& v);

public:
    bool operator==(const new_class_info& rhs) const;
    bool operator!=(const new_class_info& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::cpp::formattables::formattable& other) const override;

public:
    void swap(new_class_info& other) noexcept;
    new_class_info& operator=(new_class_info other);

private:
    dogen::cpp::formattables::state state_;
    dogen::cpp::formattables::inheritance inheritance_;
    dogen::cpp::formattables::abilities abilities_;
    dogen::cpp::formattables::class_aspects aspects_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::formattables::new_class_info& lhs,
    dogen::cpp::formattables::new_class_info& rhs) {
    lhs.swap(rhs);
}

}

#endif
