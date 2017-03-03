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
#include <boost/optional.hpp>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/element.hpp"
#include "dogen/yarn/serialization/module_fwd_ser.hpp"
#include "dogen/yarn/types/orm_module_configuration.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Container for other modeling elements.
 *
 * Aggregates a group of logically related elements into a unit.
 */
class module final : public dogen::yarn::element {
public:
    module(const module&) = default;

public:
    module();

    virtual ~module() noexcept { }

public:
    module(module&& rhs);

public:
    module(
        const std::string& documentation,
        const dogen::annotations::annotation& annotation,
        const dogen::yarn::name& name,
        const dogen::yarn::origin_types origin_type,
        const boost::optional<dogen::yarn::name>& contained_by,
        const bool in_global_module,
        const std::vector<std::string>& stereotypes,
        const bool is_element_extension,
        const std::list<dogen::yarn::name>& members,
        const bool is_root,
        const bool is_global_module,
        const boost::optional<dogen::yarn::orm_module_configuration>& orm_configuration);

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

    /**
     * @brief If true, this module is thee root module of the model.
     */
    /**@{*/
    bool is_root() const;
    void is_root(const bool v);
    /**@}*/

    /**
     * @brief If true, this module is the pseudo module that models the global namespace.
     */
    /**@{*/
    bool is_global_module() const;
    void is_global_module(const bool v);
    /**@}*/

    const boost::optional<dogen::yarn::orm_module_configuration>& orm_configuration() const;
    boost::optional<dogen::yarn::orm_module_configuration>& orm_configuration();
    void orm_configuration(const boost::optional<dogen::yarn::orm_module_configuration>& v);
    void orm_configuration(const boost::optional<dogen::yarn::orm_module_configuration>&& v);

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
    bool is_root_;
    bool is_global_module_;
    boost::optional<dogen::yarn::orm_module_configuration> orm_configuration_;
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
