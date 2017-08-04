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
#ifndef DOGEN_YARN_TYPES_META_MODEL_MODULE_HPP
#define DOGEN_YARN_TYPES_META_MODEL_MODULE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen/yarn/types/meta_model/element.hpp"
#include "dogen/yarn/types/meta_model/orm_module_properties.hpp"
#include "dogen/yarn/serialization/meta_model/module_fwd_ser.hpp"

namespace dogen {
namespace yarn {
namespace meta_model {

/**
 * @brief Container for other modeling elements.
 *
 * Aggregates a group of logically related elements into a unit.
 */
class module final : public dogen::yarn::meta_model::element {
public:
    module(const module&) = default;

public:
    module();

    virtual ~module() noexcept { }

public:
    module(module&& rhs);

public:
    module(
        const dogen::yarn::meta_model::name& name,
        const std::string& documentation,
        const dogen::annotations::annotation& annotation,
        const dogen::yarn::meta_model::origin_types origin_type,
        const boost::optional<dogen::yarn::meta_model::name>& contained_by,
        const bool in_global_module,
        const std::vector<std::string>& stereotypes,
        const dogen::yarn::meta_model::name& meta_name,
        const bool is_element_extension,
        const dogen::yarn::meta_model::element_properties& element_properties,
        const std::list<std::string>& members,
        const bool is_root,
        const bool is_global_module,
        const boost::optional<dogen::yarn::meta_model::orm_module_properties>& orm_properties);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::meta_model::module& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::meta_model::module& v, unsigned int version);

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
    const std::list<std::string>& members() const;
    std::list<std::string>& members();
    void members(const std::list<std::string>& v);
    void members(const std::list<std::string>&& v);
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

    const boost::optional<dogen::yarn::meta_model::orm_module_properties>& orm_properties() const;
    boost::optional<dogen::yarn::meta_model::orm_module_properties>& orm_properties();
    void orm_properties(const boost::optional<dogen::yarn::meta_model::orm_module_properties>& v);
    void orm_properties(const boost::optional<dogen::yarn::meta_model::orm_module_properties>&& v);

public:
    bool operator==(const module& rhs) const;
    bool operator!=(const module& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::yarn::meta_model::element& other) const override;

public:
    void swap(module& other) noexcept;
    module& operator=(module other);

private:
    std::list<std::string> members_;
    bool is_root_;
    bool is_global_module_;
    boost::optional<dogen::yarn::meta_model::orm_module_properties> orm_properties_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::meta_model::module& lhs,
    dogen::yarn::meta_model::module& rhs) {
    lhs.swap(rhs);
}

}

#endif
