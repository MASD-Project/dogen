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
#ifndef DOGEN_SML_TYPES_POD_HPP
#define DOGEN_SML_TYPES_POD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/optional.hpp>
#include <list>
#include <string>
#include <vector>
#include "dogen/sml/serialization/pod_fwd_ser.hpp"
#include "dogen/sml/types/category_types.hpp"
#include "dogen/sml/types/generation_types.hpp"
#include "dogen/sml/types/pod_types.hpp"
#include "dogen/sml/types/property.hpp"
#include "dogen/sml/types/qualified_name.hpp"

namespace dogen {
namespace sml {

class pod final {
public:
    pod(const pod&) = default;
    ~pod() = default;

public:
    pod();

public:
    pod(pod&& rhs);

public:
    pod(
        const dogen::sml::qualified_name& name,
        const std::vector<dogen::sml::property>& properties,
        const boost::optional<dogen::sml::qualified_name>& parent_name,
        const boost::optional<dogen::sml::qualified_name>& original_parent_name,
        const std::list<dogen::sml::qualified_name>& leaves,
        const dogen::sml::generation_types& generation_type,
        const bool is_parent,
        const dogen::sml::category_types& category_type,
        const dogen::sml::pod_types& pod_type,
        const std::string& documentation,
        const unsigned int number_of_type_arguments);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const pod& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, pod& v, unsigned int version);

public:
    /*
     * @brief Qualified name for the type.
     */
    /**@{*/
    dogen::sml::qualified_name name() const {
        return name_;
    }

    void name(const dogen::sml::qualified_name& v) {
        name_ = v;
    }
    /**@}*/

    /*
     * @brief All the properties this pod owns.
     */
    /**@{*/
    std::vector<dogen::sml::property> properties() const {
        return properties_;
    }

    void properties(const std::vector<dogen::sml::property>& v) {
        properties_ = v;
    }
    /**@}*/

    /*
     * @brief Qualified name for the pod's parent, if the pod has one.
     */
    /**@{*/
    boost::optional<dogen::sml::qualified_name> parent_name() const {
        return parent_name_;
    }

    void parent_name(const boost::optional<dogen::sml::qualified_name>& v) {
        parent_name_ = v;
    }
    /**@}*/

    /*
     * @brief Qualified name for the root of the inheritance hierarchy, if the pod is part of one.
     */
    /**@{*/
    boost::optional<dogen::sml::qualified_name> original_parent_name() const {
        return original_parent_name_;
    }

    void original_parent_name(const boost::optional<dogen::sml::qualified_name>& v) {
        original_parent_name_ = v;
    }
    /**@}*/

    /*
     * @brief All concrete types which are indirectly or directly derived from this type.
     */
    /**@{*/
    std::list<dogen::sml::qualified_name> leaves() const {
        return leaves_;
    }

    void leaves(const std::list<dogen::sml::qualified_name>& v) {
        leaves_ = v;
    }
    /**@}*/

    /*
     * @brief What to do with this pod in terms of code generation
     */
    /**@{*/
    dogen::sml::generation_types generation_type() const {
        return generation_type_;
    }

    void generation_type(const dogen::sml::generation_types& v) {
        generation_type_ = v;
    }
    /**@}*/

    /*
     * @brief True if this class is the parent of one or more classes, false otherwise.
     */
    /**@{*/
    bool is_parent() const {
        return is_parent_;
    }

    void is_parent(const bool v) {
        is_parent_ = v;
    }
    /**@}*/

    /*
     * @brief Category of this type - whether its system or user defined.
     */
    /**@{*/
    dogen::sml::category_types category_type() const {
        return category_type_;
    }

    void category_type(const dogen::sml::category_types& v) {
        category_type_ = v;
    }
    /**@}*/

    /*
     * @brief What kind of pod is this.
     */
    /**@{*/
    dogen::sml::pod_types pod_type() const {
        return pod_type_;
    }

    void pod_type(const dogen::sml::pod_types& v) {
        pod_type_ = v;
    }
    /**@}*/

    /*
     * @brief Doxygen documentation for the type.
     */
    /**@{*/
    std::string documentation() const {
        return documentation_;
    }

    void documentation(const std::string& v) {
        documentation_ = v;
    }
    /**@}*/

    /*
     * @brief How many type arguments does this type have
     */
    /**@{*/
    unsigned int number_of_type_arguments() const {
        return number_of_type_arguments_;
    }

    void number_of_type_arguments(const unsigned int v) {
        number_of_type_arguments_ = v;
    }
    /**@}*/

public:
    bool operator==(const pod& rhs) const;
    bool operator!=(const pod& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(pod& other) noexcept;
    pod& operator=(pod other);

private:
    dogen::sml::qualified_name name_;
    std::vector<dogen::sml::property> properties_;
    boost::optional<dogen::sml::qualified_name> parent_name_;
    boost::optional<dogen::sml::qualified_name> original_parent_name_;
    std::list<dogen::sml::qualified_name> leaves_;
    dogen::sml::generation_types generation_type_;
    bool is_parent_;
    dogen::sml::category_types category_type_;
    dogen::sml::pod_types pod_type_;
    std::string documentation_;
    unsigned int number_of_type_arguments_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::sml::pod& lhs,
    dogen::sml::pod& rhs) {
    lhs.swap(rhs);
}

}

#endif
