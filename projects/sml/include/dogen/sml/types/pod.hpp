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
#include <utility>
#include <vector>
#include "dogen/sml/serialization/pod_fwd_ser.hpp"
#include "dogen/sml/types/category_types.hpp"
#include "dogen/sml/types/generation_types.hpp"
#include "dogen/sml/types/pod_types.hpp"
#include "dogen/sml/types/property.hpp"
#include "dogen/sml/types/qname.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Represents a plain C++ object with basic associated behaviours.
 *
 * The name pod is misleading because its actually not used in the strict sense of POD as defined here:
 *
 *  <a href="http://en.wikipedia.org/wiki/Plain_old_data_structure">Plain old data structure</a>.
 */
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
        const dogen::sml::qname& name,
        const std::vector<dogen::sml::property>& properties,
        const boost::optional<dogen::sml::qname>& parent_name,
        const boost::optional<dogen::sml::qname>& original_parent_name,
        const std::list<dogen::sml::qname>& leaves,
        const dogen::sml::generation_types& generation_type,
        const bool is_parent,
        const dogen::sml::category_types& category_type,
        const dogen::sml::pod_types& pod_type,
        const std::string& documentation,
        const unsigned int number_of_type_arguments,
        const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters,
        const bool is_visitable,
        const bool is_immutable,
        const bool is_versioned,
        const bool is_keyed,
        const bool is_comparable,
        const bool is_fluent,
        const bool is_aggregate_root,
        const boost::optional<dogen::sml::qname>& versioned_key,
        const boost::optional<dogen::sml::qname>& unversioned_key,
        const std::list<dogen::sml::qname>& modeled_concepts);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const pod& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, pod& v, unsigned int version);

public:
    /**
     * @brief Qualified name for the type.
     *
     */
    /**@{*/
    const dogen::sml::qname& name() const;
    dogen::sml::qname& name();
    void name(const dogen::sml::qname& v);
    void name(const dogen::sml::qname&& v);
    /**@}*/

    /**
     * @brief All the properties this pod owns.
     */
    /**@{*/
    const std::vector<dogen::sml::property>& properties() const;
    std::vector<dogen::sml::property>& properties();
    void properties(const std::vector<dogen::sml::property>& v);
    void properties(const std::vector<dogen::sml::property>&& v);
    /**@}*/

    /**
     * @brief Qualified name for the pod's parent, if the pod has one.
     */
    /**@{*/
    const boost::optional<dogen::sml::qname>& parent_name() const;
    boost::optional<dogen::sml::qname>& parent_name();
    void parent_name(const boost::optional<dogen::sml::qname>& v);
    void parent_name(const boost::optional<dogen::sml::qname>&& v);
    /**@}*/

    /**
     * @brief Qualified name for the root of the inheritance hierarchy, if the pod is part of one.
     */
    /**@{*/
    const boost::optional<dogen::sml::qname>& original_parent_name() const;
    boost::optional<dogen::sml::qname>& original_parent_name();
    void original_parent_name(const boost::optional<dogen::sml::qname>& v);
    void original_parent_name(const boost::optional<dogen::sml::qname>&& v);
    /**@}*/

    /**
     * @brief All concrete types which are indirectly or directly derived from this type.
     */
    /**@{*/
    const std::list<dogen::sml::qname>& leaves() const;
    std::list<dogen::sml::qname>& leaves();
    void leaves(const std::list<dogen::sml::qname>& v);
    void leaves(const std::list<dogen::sml::qname>&& v);
    /**@}*/

    /**
     * @brief What to do with this pod in terms of code generation
     */
    /**@{*/
    dogen::sml::generation_types generation_type() const;
    void generation_type(const dogen::sml::generation_types& v);
    /**@}*/

    /**
     * @brief True if this class is the parent of one or more classes, false otherwise.
     */
    /**@{*/
    bool is_parent() const;
    void is_parent(const bool v);
    /**@}*/

    /**
     * @brief Category of this type - whether its system or user defined.
     */
    /**@{*/
    dogen::sml::category_types category_type() const;
    void category_type(const dogen::sml::category_types& v);
    /**@}*/

    /**
     * @brief What kind of pod is this.
     */
    /**@{*/
    dogen::sml::pod_types pod_type() const;
    void pod_type(const dogen::sml::pod_types& v);
    /**@}*/

    /**
     * @brief Doxygen documentation for the type.
     */
    /**@{*/
    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);
    /**@}*/

    /**
     * @brief How many type arguments does this type have
     */
    /**@{*/
    unsigned int number_of_type_arguments() const;
    void number_of_type_arguments(const unsigned int v);
    /**@}*/

    /**
     * @brief Parameters associated with the pod which are opaque to SML.
     */
    /**@{*/
    const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters() const;
    std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters();
    void implementation_specific_parameters(const std::vector<std::pair<std::string, std::string> >& v);
    void implementation_specific_parameters(const std::vector<std::pair<std::string, std::string> >&& v);
    /**@}*/

    /**
     * @brief If true, a visitor is to be generated for this type and its descendants.
     *
     * Only applicable if is_parent is true.
     */
    /**@{*/
    bool is_visitable() const;
    void is_visitable(const bool v);
    /**@}*/

    /**
     * @brief If true, do not generate setters for the type's properties.
     */
    /**@{*/
    bool is_immutable() const;
    void is_immutable(const bool v);
    /**@}*/

    /**
     * @brief If true, add a version property to the type.
     */
    /**@{*/
    bool is_versioned() const;
    void is_versioned(const bool v);
    /**@}*/

    /**
     * @brief If true, add key support for the type.
     */
    /**@{*/
    bool is_keyed() const;
    void is_keyed(const bool v);
    /**@}*/

    /**
     * @brief If true, generates the less than operator.
     *
     * A type is only comparable if all of its properties are primitives or strings,
     * or other comparable model types.
     */
    /**@{*/
    bool is_comparable() const;
    void is_comparable(const bool v);
    /**@}*/

    /**
     * @brief If true, generate fluent setters.
     */
    /**@{*/
    bool is_fluent() const;
    void is_fluent(const bool v);
    /**@}*/

    /**
     * @brief If true, this pod is a root of an aggregate.
     */
    /**@{*/
    bool is_aggregate_root() const;
    void is_aggregate_root(const bool v);
    /**@}*/

    /**
     * @brief If the pod is a versioned keyed entity, its versioned key.
     */
    /**@{*/
    const boost::optional<dogen::sml::qname>& versioned_key() const;
    boost::optional<dogen::sml::qname>& versioned_key();
    void versioned_key(const boost::optional<dogen::sml::qname>& v);
    void versioned_key(const boost::optional<dogen::sml::qname>&& v);
    /**@}*/

    /**
     * @brief If the pod is an unversioned keyed entity, its unversioned key.
     */
    /**@{*/
    const boost::optional<dogen::sml::qname>& unversioned_key() const;
    boost::optional<dogen::sml::qname>& unversioned_key();
    void unversioned_key(const boost::optional<dogen::sml::qname>& v);
    void unversioned_key(const boost::optional<dogen::sml::qname>&& v);
    /**@}*/

    /**
     * @brief List of concepts this pod models.
     */
    /**@{*/
    const std::list<dogen::sml::qname>& modeled_concepts() const;
    std::list<dogen::sml::qname>& modeled_concepts();
    void modeled_concepts(const std::list<dogen::sml::qname>& v);
    void modeled_concepts(const std::list<dogen::sml::qname>&& v);
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
    dogen::sml::qname name_;
    std::vector<dogen::sml::property> properties_;
    boost::optional<dogen::sml::qname> parent_name_;
    boost::optional<dogen::sml::qname> original_parent_name_;
    std::list<dogen::sml::qname> leaves_;
    dogen::sml::generation_types generation_type_;
    bool is_parent_;
    dogen::sml::category_types category_type_;
    dogen::sml::pod_types pod_type_;
    std::string documentation_;
    unsigned int number_of_type_arguments_;
    std::vector<std::pair<std::string, std::string> > implementation_specific_parameters_;
    bool is_visitable_;
    bool is_immutable_;
    bool is_versioned_;
    bool is_keyed_;
    bool is_comparable_;
    bool is_fluent_;
    bool is_aggregate_root_;
    boost::optional<dogen::sml::qname> versioned_key_;
    boost::optional<dogen::sml::qname> unversioned_key_;
    std::list<dogen::sml::qname> modeled_concepts_;
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
