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
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_VIEW_MODELS_NESTED_TYPE_VIEW_MODEL_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_VIEW_MODELS_NESTED_TYPE_VIEW_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace view_models {

class nested_type_view_model {
public:
    nested_type_view_model(const nested_type_view_model&) = default;
    ~nested_type_view_model() = default;
    nested_type_view_model(nested_type_view_model&&) = default;
    nested_type_view_model& operator=(const nested_type_view_model&) = default;

public:
    nested_type_view_model() : is_primitive_(false), is_string_like_(false),
                               is_char_like_(false), is_int_like_(false),
                               is_sequence_container_(false),
                               is_associative_container_(false),
                               is_smart_pointer_(false) {}

    explicit nested_type_view_model(const std::string& name)
        : name_(name), is_primitive_(false), is_string_like_(false),
          is_char_like_(false), is_int_like_(false),
          is_sequence_container_(false), is_associative_container_(false),
          is_smart_pointer_(false) {}

public:
    /**
     * @brief Fully qualified name of the top-level type.
     */
    /**@{*/
    std::string name() const { return name_; }
    void name(const std::string& value) { name_ = value; }
    /**@}*/

    /**
     * @brief Representation of the type name which is can be used to
     * generate identifier names.
     *
     * For example, if the type is unsigned long, its identifiable
     * type is unsigned_long.
     */
    /**@{*/
    std::string identifiable_name() const { return identifiable_name_; }
    void identifiable_name(std::string value) { identifiable_name_ = value; }
    /**@}*/

    /**
     * @brief Complete name, including all type arguments
     */
    /**@{*/
    std::string complete_name() const { return complete_name_; }
    void complete_name(const std::string& v) { complete_name_ = v; }
    /**@}*/

    /**
     * @brief Complete name as an identifiable string.
     */
    /**@{*/
    std::string complete_identifiable_name() const {
        return complete_identifiable_name_;
    }
    void complete_identifiable_name(const std::string& v) {
        complete_identifiable_name_ = v;
    }
    /**@}*/

    /**
     * @brief If true, the meta type of the top-level type is primitive.
     */
    /**@{*/
    bool is_primitive() const { return is_primitive_; }
    void is_primitive(bool value) { is_primitive_ = value; }
    /**@}*/

    /**
     * @brief If true, the meta type of the top-level type is enumeration.
     */
    /**@{*/
    bool is_enumeration() const { return is_enumeration_; }
    void is_enumeration(bool value) { is_enumeration_ = value; }
    /**@}*/

    /**
     * @brief If true, the type of the top-level type is either string,
     * char or unsigned char.
     */
    /**@{*/
    bool is_string_like() const { return is_string_like_; }
    void is_string_like(bool value) { is_string_like_ = value; }
    /**@}*/

    /**
     * @brief If true, the meta type of the top-level type is either char or
     * unsigned char.
     */
    /**@{*/
    bool is_char_like() const { return is_char_like_; }
    void is_char_like(bool value) { is_char_like_ = value; }
    /**@}*/

    /**
     * @brief If true, the meta type of the top-level type is short,
     * int, long, long long or their unsigned counterparts.
     */
    /**@{*/
    bool is_int_like() const { return is_int_like_; }
    void is_int_like(bool value) { is_int_like_ = value; }
    /**@}*/

    /**
     * @brief If true, type is a sequence container.
     */
    /**@{*/
    bool is_sequence_container() const { return is_sequence_container_; }
    void is_sequence_container(bool v) { is_sequence_container_ = v; }
    /**@}*/

    /**
     * @brief If true, the type is an associative container.
     */
    /**@{*/
    bool is_associative_container() const { return is_associative_container_; }
    void is_associative_container(bool v) { is_associative_container_ = v; }
    /**@}*/

    /**
     * @brief If true, the type is a smart pointer.
     */
    /**@{*/
    bool is_smart_pointer() const { return is_smart_pointer_; }
    void is_smart_pointer(bool v) { is_smart_pointer_ = v; }
    /**@}*/

    /**
     * @brief If true, the type is an optional like type.
     */
    /**@{*/
    bool is_optional_like() const { return is_optional_like_; }
    void is_optional_like(bool v) { is_optional_like_ = v; }
    /**@}*/

    /**
     * @brief If true, the type is a variant like type.
     */
    /**@{*/
    bool is_variant_like() const { return is_variant_like_; }
    void is_variant_like(bool v) { is_variant_like_ = v; }
    /**@}*/

    /**
     * @brief If the type is a generic type, returns all the type
     * arguments.
     */
    /**@{*/
    std::list<nested_type_view_model> children() const { return children_; }
    void children(std::list<nested_type_view_model> v) { children_ = v; }
    /**@}*/

    /**
     * @brief List of all namespaces containing the class.
     */
    /**@{*/
    std::list<std::string> namespaces() const { return namespaces_; }
    void namespaces(const std::list<std::string>& value) {
        namespaces_ = value;
    }
    /**@}*/

private:
    std::string name_;
    std::string identifiable_name_;
    std::string complete_name_;
    std::string complete_identifiable_name_;
    bool is_primitive_;
    bool is_enumeration_;
    bool is_string_like_;
    bool is_char_like_;
    bool is_int_like_;
    bool is_sequence_container_;
    bool is_associative_container_;
    bool is_smart_pointer_;
    bool is_optional_like_;
    bool is_variant_like_;
    std::list<nested_type_view_model> children_;
    std::list<std::string> namespaces_;
};

} } } } }

#endif
