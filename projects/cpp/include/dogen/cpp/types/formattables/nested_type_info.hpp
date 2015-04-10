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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_NESTED_TYPE_INFO_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_NESTED_TYPE_INFO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "dogen/cpp/types/formattables/family_types.hpp"
#include "dogen/cpp/types/formattables/nested_type_info.hpp"
#include "dogen/cpp/serialization/formattables/nested_type_info_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Represents a declaration of a C++ type with nesting.
 */
class nested_type_info final {
public:
    nested_type_info(const nested_type_info&) = default;
    nested_type_info(nested_type_info&&) = default;
    ~nested_type_info() = default;

public:
    nested_type_info();

public:
    nested_type_info(
        const std::string& name,
        const std::string& identifiable_name,
        const std::string& complete_name,
        const std::string& complete_identifiable_name,
        const bool is_primitive,
        const bool is_enumeration,
        const bool is_string_like,
        const bool is_char_like,
        const bool is_int_like,
        const bool is_sequence_container,
        const bool is_associative_container,
        const bool is_smart_pointer,
        const bool is_optional_like,
        const bool is_variant_like,
        const std::list<dogen::cpp::formattables::nested_type_info>& children,
        const std::list<std::string>& namespaces,
        const bool is_filesystem_path,
        const bool is_date,
        const bool is_ptime,
        const bool is_time_duration,
        const bool is_pair,
        const bool is_ptree,
        const dogen::cpp::formattables::family_types& family_type);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const nested_type_info& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, nested_type_info& v, unsigned int version);

public:
    /**
     * @brief Name of the entity.
     *
     * Must be valid according to the rules for C++ names.
     */
    /**@{*/
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);
    /**@}*/

    /**
     * @brief Name of the type taking into account all contained types.
     *
     * Does not use characters which are not valid for C++ identifiers.
     */
    /**@{*/
    const std::string& identifiable_name() const;
    std::string& identifiable_name();
    void identifiable_name(const std::string& v);
    void identifiable_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Fully qualified name.
     */
    /**@{*/
    const std::string& complete_name() const;
    std::string& complete_name();
    void complete_name(const std::string& v);
    void complete_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Fully qualified name with complete type nesting.
     */
    /**@{*/
    const std::string& complete_identifiable_name() const;
    std::string& complete_identifiable_name();
    void complete_identifiable_name(const std::string& v);
    void complete_identifiable_name(const std::string&& v);
    /**@}*/

    /**
     * @brief If true, the type is primitive.
     */
    /**@{*/
    bool is_primitive() const;
    void is_primitive(const bool v);
    /**@}*/

    /**
     * @brief If true the type is an enumeration
     */
    /**@{*/
    bool is_enumeration() const;
    void is_enumeration(const bool v);
    /**@}*/

    /**
     * @brief If true, the type is a std::string or another string like type.
     */
    /**@{*/
    bool is_string_like() const;
    void is_string_like(const bool v);
    /**@}*/

    /**
     * @brief If true, the type is a std::string, char, unsigned char or another char like type.
     */
    /**@{*/
    bool is_char_like() const;
    void is_char_like(const bool v);
    /**@}*/

    /**
     * @brief If true, the type is an int, unsigned int or another int like type.
     */
    /**@{*/
    bool is_int_like() const;
    void is_int_like(const bool v);
    /**@}*/

    /**
     * @brief If true, the type is a sequence container like std::list or std::vector.
     */
    /**@{*/
    bool is_sequence_container() const;
    void is_sequence_container(const bool v);
    /**@}*/

    /**
     * @brief If true, the type is a associative container like std::map or std::unordered_set.
     */
    /**@{*/
    bool is_associative_container() const;
    void is_associative_container(const bool v);
    /**@}*/

    /**
     * @brief If true, the type is a smart pointer like std::shared_ptr.
     */
    /**@{*/
    bool is_smart_pointer() const;
    void is_smart_pointer(const bool v);
    /**@}*/

    /**
     * @brief If true, the type is boost::optional.
     */
    /**@{*/
    bool is_optional_like() const;
    void is_optional_like(const bool v);
    /**@}*/

    /**
     * @brief If true, the type is boost::variant.
     */
    /**@{*/
    bool is_variant_like() const;
    void is_variant_like(const bool v);
    /**@}*/

    /**
     * @brief Contained types.
     */
    /**@{*/
    const std::list<dogen::cpp::formattables::nested_type_info>& children() const;
    std::list<dogen::cpp::formattables::nested_type_info>& children();
    void children(const std::list<dogen::cpp::formattables::nested_type_info>& v);
    void children(const std::list<dogen::cpp::formattables::nested_type_info>&& v);
    /**@}*/

    /**
     * @brief Namespaces to which the type belongs to.
     */
    /**@{*/
    const std::list<std::string>& namespaces() const;
    std::list<std::string>& namespaces();
    void namespaces(const std::list<std::string>& v);
    void namespaces(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief If true the type is boost::filesystem::path.
     */
    /**@{*/
    bool is_filesystem_path() const;
    void is_filesystem_path(const bool v);
    /**@}*/

    /**
     * @brief If true the type is boost::date_time::date.
     */
    /**@{*/
    bool is_date() const;
    void is_date(const bool v);
    /**@}*/

    /**
     * @brief If true the type is boost::date_time::ptime
     */
    /**@{*/
    bool is_ptime() const;
    void is_ptime(const bool v);
    /**@}*/

    /**
     * @brief If true the type is boost::date_time::time_duration.
     */
    /**@{*/
    bool is_time_duration() const;
    void is_time_duration(const bool v);
    /**@}*/

    /**
     * @brief If true the type is std::pair.
     */
    /**@{*/
    bool is_pair() const;
    void is_pair(const bool v);
    /**@}*/

    /**
     * @brief If true, the type is boost::property_tree::ptree.
     */
    /**@{*/
    bool is_ptree() const;
    void is_ptree(const bool v);
    /**@}*/

    dogen::cpp::formattables::family_types family_type() const;
    void family_type(const dogen::cpp::formattables::family_types& v);

public:
    bool operator==(const nested_type_info& rhs) const;
    bool operator!=(const nested_type_info& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(nested_type_info& other) noexcept;
    nested_type_info& operator=(nested_type_info other);

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
    std::list<dogen::cpp::formattables::nested_type_info> children_;
    std::list<std::string> namespaces_;
    bool is_filesystem_path_;
    bool is_date_;
    bool is_ptime_;
    bool is_time_duration_;
    bool is_pair_;
    bool is_ptree_;
    dogen::cpp::formattables::family_types family_type_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::formattables::nested_type_info& lhs,
    dogen::cpp::formattables::nested_type_info& rhs) {
    lhs.swap(rhs);
}

}

#endif
