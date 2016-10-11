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
#ifndef DOGEN_YARN_TYPES_MODULE_HPP
#define DOGEN_YARN_TYPES_MODULE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <algorithm>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/element.hpp"
#include "dogen/yarn/serialization/module_fwd_ser.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Container for other modeling elements.
 *
 * Aggregates a group of logically related elements into a unit.
 */
class module final : public dogen::yarn::element {
public:
    module() = default;
    module(const module&) = default;
    module(module&&) = default;

    virtual ~module() noexcept { }

public:
    module(
        const std::string& documentation,
        const dogen::annotations::annotation& annotation,
        const dogen::yarn::name& name,
        const dogen::yarn::generation_types generation_type,
        const dogen::yarn::origin_types origin_type,
        const boost::optional<dogen::yarn::name>& contained_by,
        const bool in_global_module,
        const std::unordered_set<dogen::yarn::stereotypes>& stereotypes,
        const bool is_element_extension,
        const std::list<dogen::yarn::name>& members);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::module& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::module& v, unsigned int version);

public:
    using element::accept;

    virtual void accept(const element_visitor& v) const override;
    virtual void accept(element_visitor& v) const override;
    virtual void accept(const element_visitor& v) override;
    virtual void accept(element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief All the model elements contained in this module.
     */
    /**@{*/
    const std::list<dogen::yarn::name>& members() const;
    std::list<dogen::yarn::name>& members();
    void members(const std::list<dogen::yarn::name>& v);
    void members(const std::list<dogen::yarn::name>&& v);
    /**@}*/

public:
    bool operator==(const module& rhs) const;
    bool operator!=(const module& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::yarn::element& other) const override;

public:
    void swap(module& other) noexcept;
    module& operator=(module other);

private:
    std::list<dogen::yarn::name> members_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::module& lhs,
    dogen::yarn::module& rhs) {
    lhs.swap(rhs);
}

}

#endif
