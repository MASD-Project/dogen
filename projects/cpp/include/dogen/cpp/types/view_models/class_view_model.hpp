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
#ifndef DOGEN_CPP_TYPES_VIEW_MODELS_CLASS_VIEW_MODEL_HPP
#define DOGEN_CPP_TYPES_VIEW_MODELS_CLASS_VIEW_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include <string>
#include <utility>
#include <vector>
#include "dogen/cpp/serialization/view_models/class_view_model_fwd_ser.hpp"
#include "dogen/cpp/types/view_models/parent_view_model.hpp"
#include "dogen/cpp/types/view_models/property_view_model.hpp"

namespace dogen {
namespace cpp {
namespace view_models {

class class_view_model final {
public:
    class_view_model(const class_view_model&) = default;
    class_view_model(class_view_model&&) = default;
    ~class_view_model() = default;

public:
    class_view_model();

public:
    class_view_model(
        const std::list<std::string>& namespaces,
        const std::string& name,
        const std::list<dogen::cpp::view_models::property_view_model>& properties,
        const std::list<dogen::cpp::view_models::property_view_model>& all_properties,
        const bool has_primitive_properties,
        const bool requires_stream_manipulators,
        const bool requires_manual_move_constructor,
        const bool requires_manual_default_constructor,
        const std::list<dogen::cpp::view_models::parent_view_model>& parents,
        const bool is_parent,
        const std::string& documentation,
        const std::string& original_parent_name,
        const std::string& original_parent_name_qualified,
        const std::list<std::string>& leaves,
        const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters,
        const bool is_comparable,
        const bool is_visitable,
        const bool is_immutable,
        const bool is_original_parent_visitable);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const class_view_model& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, class_view_model& v, unsigned int version);

public:
    /**
     * @brief List of all namespaces containing the class.
     */
    /**@{*/
    const std::list<std::string>& namespaces() const;
    std::list<std::string>& namespaces();
    void namespaces(const std::list<std::string>& v);
    void namespaces(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief Name of the class.
     */
    /**@{*/
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);
    /**@}*/

    /**
     * @brief Properties of the class itself (e.g. excludes inherited
     * properties).
     */
    /**@{*/
    const std::list<dogen::cpp::view_models::property_view_model>& properties() const;
    std::list<dogen::cpp::view_models::property_view_model>& properties();
    void properties(const std::list<dogen::cpp::view_models::property_view_model>& v);
    void properties(const std::list<dogen::cpp::view_models::property_view_model>&& v);
    /**@}*/

    /**
     * @brief All properties of the class including inherited.
     */
    /**@{*/
    const std::list<dogen::cpp::view_models::property_view_model>& all_properties() const;
    std::list<dogen::cpp::view_models::property_view_model>& all_properties();
    void all_properties(const std::list<dogen::cpp::view_models::property_view_model>& v);
    void all_properties(const std::list<dogen::cpp::view_models::property_view_model>&& v);
    /**@}*/

    /**
     * @brief True if the class has at least one property which is a
     * primitive, false otherwise.
     */
    /**@{*/
    bool has_primitive_properties() const;
    void has_primitive_properties(const bool v);
    /**@}*/

    /**
     * @brief True if the class has member variables which require
     * changing the stream with manipulators, false otherwise.
     *
     * Examples are boolean variables, which should be outputted as
     * true or false and as such require boolalpha.
     */
    /**@{*/
    bool requires_stream_manipulators() const;
    void requires_stream_manipulators(const bool v);
    /**@}*/

    /**
     * @brief True if the class requires a manually generated move
     * constructor, false otherwise.
     */
    /**@{*/
    bool requires_manual_move_constructor() const;
    void requires_manual_move_constructor(const bool v);
    /**@}*/

    /**
     * @brief True if the class requires a manually generated default
     * constructor, false otherwise.
     */
    /**@{*/
    bool requires_manual_default_constructor() const;
    void requires_manual_default_constructor(const bool v);
    /**@}*/

    /**
     * @brief Parents for this class.
     */
    /**@{*/
    const std::list<dogen::cpp::view_models::parent_view_model>& parents() const;
    std::list<dogen::cpp::view_models::parent_view_model>& parents();
    void parents(const std::list<dogen::cpp::view_models::parent_view_model>& v);
    void parents(const std::list<dogen::cpp::view_models::parent_view_model>&& v);
    /**@}*/

    /**
     * @brief True if this class is the parent of one or more classes,
     * false otherwise.
     */
    /**@{*/
    bool is_parent() const;
    void is_parent(const bool v);
    /**@}*/

    /**
     * @brief Documentation for the property
     */
    /**@{*/
    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);
    /**@}*/

    /**
     * @brief Parent at the root of a class hierarchy, if any.
     */
    /**@{*/
    const std::string& original_parent_name() const;
    std::string& original_parent_name();
    void original_parent_name(const std::string& v);
    void original_parent_name(const std::string&& v);
    /**@}*/

    const std::string& original_parent_name_qualified() const;
    std::string& original_parent_name_qualified();
    void original_parent_name_qualified(const std::string& v);
    void original_parent_name_qualified(const std::string&& v);

    /**
     * @brief If the class is abstract, list of concrete types that
     * descend from it. Names are in identifiable name format.
     */
    /**@{*/
    const std::list<std::string>& leaves() const;
    std::list<std::string>& leaves();
    void leaves(const std::list<std::string>& v);
    void leaves(const std::list<std::string>&& v);
    /**@}*/

    const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters() const;
    std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters();
    void implementation_specific_parameters(const std::vector<std::pair<std::string, std::string> >& v);
    void implementation_specific_parameters(const std::vector<std::pair<std::string, std::string> >&& v);

    bool is_comparable() const;
    void is_comparable(const bool v);

    bool is_visitable() const;
    void is_visitable(const bool v);

    bool is_immutable() const;
    void is_immutable(const bool v);

    bool is_original_parent_visitable() const;
    void is_original_parent_visitable(const bool v);

public:
    bool operator==(const class_view_model& rhs) const;
    bool operator!=(const class_view_model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(class_view_model& other) noexcept;
    class_view_model& operator=(class_view_model other);

private:
    std::list<std::string> namespaces_;
    std::string name_;
    std::list<dogen::cpp::view_models::property_view_model> properties_;
    std::list<dogen::cpp::view_models::property_view_model> all_properties_;
    bool has_primitive_properties_;
    bool requires_stream_manipulators_;
    bool requires_manual_move_constructor_;
    bool requires_manual_default_constructor_;
    std::list<dogen::cpp::view_models::parent_view_model> parents_;
    bool is_parent_;
    std::string documentation_;
    std::string original_parent_name_;
    std::string original_parent_name_qualified_;
    std::list<std::string> leaves_;
    std::vector<std::pair<std::string, std::string> > implementation_specific_parameters_;
    bool is_comparable_;
    bool is_visitable_;
    bool is_immutable_;
    bool is_original_parent_visitable_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::view_models::class_view_model& lhs,
    dogen::cpp::view_models::class_view_model& rhs) {
    lhs.swap(rhs);
}

}

#endif
