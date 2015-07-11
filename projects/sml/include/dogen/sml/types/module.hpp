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
#ifndef DOGEN_SML_TYPES_MODULE_HPP
#define DOGEN_SML_TYPES_MODULE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen/sml/types/qname.hpp"
#include "dogen/dynamic/types/object.hpp"
#include "dogen/sml/types/origin_types.hpp"
#include "dogen/sml/types/generation_types.hpp"
#include "dogen/sml/serialization/module_fwd_ser.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Packaging unit.
 *
 * Aggregates a group of logically related types into a unit.
 */
class module final {
public:
    module(const module&) = default;
    ~module() = default;

public:
    module();

public:
    module(module&& rhs);

public:
    module(
        const std::string& documentation,
        const dogen::dynamic::object& extensions,
        const dogen::sml::qname& name,
        const dogen::sml::generation_types generation_type,
        const dogen::sml::origin_types origin_type,
        const boost::optional<dogen::sml::qname>& containing_module,
        const std::list<dogen::sml::qname>& members);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const module& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, module& v, unsigned int version);

public:
    /**
     * @brief Code comments.
     *
     * These are expected to follow the grammar of the comment processing tools
     * of the programming language in question, e.g. Doxygen for C++, JavaDoc
     * for Java, etc.
     */
    /**@{*/
    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);
    /**@}*/

    /**
     * @brief Dynamic extensions for this element.
     */
    /**@{*/
    const dogen::dynamic::object& extensions() const;
    dogen::dynamic::object& extensions();
    void extensions(const dogen::dynamic::object& v);
    void extensions(const dogen::dynamic::object&& v);
    /**@}*/

    /**
     * @brief Fully qualified name.
     *
     */
    /**@{*/
    const dogen::sml::qname& name() const;
    dogen::sml::qname& name();
    void name(const dogen::sml::qname& v);
    void name(const dogen::sml::qname&& v);
    /**@}*/

    /**
     * @brief What to do with this type in terms of code generation.
     */
    /**@{*/
    dogen::sml::generation_types generation_type() const;
    void generation_type(const dogen::sml::generation_types v);
    /**@}*/

    /**
     * @brief How was this model element originated.
     */
    /**@{*/
    dogen::sml::origin_types origin_type() const;
    void origin_type(const dogen::sml::origin_types v);
    /**@}*/

    /**
     * @brief Name of the module in which we are contained.
     */
    /**@{*/
    const boost::optional<dogen::sml::qname>& containing_module() const;
    boost::optional<dogen::sml::qname>& containing_module();
    void containing_module(const boost::optional<dogen::sml::qname>& v);
    void containing_module(const boost::optional<dogen::sml::qname>&& v);
    /**@}*/

    /**
     * @brief All the model elements contained in this module.
     */
    /**@{*/
    const std::list<dogen::sml::qname>& members() const;
    std::list<dogen::sml::qname>& members();
    void members(const std::list<dogen::sml::qname>& v);
    void members(const std::list<dogen::sml::qname>&& v);
    /**@}*/

public:
    bool operator==(const module& rhs) const;
    bool operator!=(const module& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(module& other) noexcept;
    module& operator=(module other);

private:
    std::string documentation_;
    dogen::dynamic::object extensions_;
    dogen::sml::qname name_;
    dogen::sml::generation_types generation_type_;
    dogen::sml::origin_types origin_type_;
    boost::optional<dogen::sml::qname> containing_module_;
    std::list<dogen::sml::qname> members_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::sml::module& lhs,
    dogen::sml::module& rhs) {
    lhs.swap(rhs);
}

}

#endif
