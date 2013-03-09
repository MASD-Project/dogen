/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2013 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_DEPENDENCY_DETAILS_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_DEPENDENCY_DETAILS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <unordered_set>
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/hash/qname_hash.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {

/**
 * @brief Contains a break down of all dependencies required by a pod.
 */
class dependency_details {
public:
    dependency_details(const dependency_details&) = default;
    ~dependency_details() = default;
    dependency_details(dependency_details&&) = default;
    dependency_details& operator=(const dependency_details&) = default;

public:
    dependency_details() : has_std_string_(false), has_variant_(false),
                           is_parent_(false), is_child_(false),
                           requires_stream_manipulators_(false) { }

public:
    /**
     * @brief Direct dependencies for this pod which cannot be forward
     * declared.
     */
    const std::unordered_set<sml::qname>& names() const;
    std::unordered_set<sml::qname>& names();
    void names(const std::unordered_set<sml::qname>& v);
    void names(const std::unordered_set<sml::qname>&& v);

    /**
     * @brief Dependencies for this pod which can be forward declared
     * in headers.
     */
    const std::unordered_set<sml::qname>& forward_decls() const;
    std::unordered_set<sml::qname>& forward_decls();
    void forward_decls(const std::unordered_set<sml::qname>& v);
    void forward_decls(const std::unordered_set<sml::qname>&& v);

    /**
     * @brief Keys used by this pod in associative containers.
     */
    const std::unordered_set<sml::qname>& keys() const;
    std::unordered_set<sml::qname>& keys();
    void keys(const std::unordered_set<sml::qname>& v);
    void keys(const std::unordered_set<sml::qname>&& v);

    /**
     * @brief Final descendants of this pod.
     */
    const std::unordered_set<sml::qname>& leaves() const;
    std::unordered_set<sml::qname>& leaves();
    void leaves(const std::unordered_set<sml::qname>& v);
    void leaves(const std::unordered_set<sml::qname>&& v);

    /**
     * @brief Returns true if there is a std::string in the type list.
     */
    bool has_std_string() const;
    void has_std_string(const bool v);

    /**
     * @brief Returns true if there is a boost::variant in the type list.
     */
    bool has_variant() const;
    void has_variant(const bool v);

    /**
     * @brief Returns true if the pod is a parent of another pod.
     */
    bool is_parent() const;
    void is_parent(const bool v);

    /**
     * @brief Returns true if the pod is a descendant of another pod.
     */
    bool is_child() const;
    void is_child(const bool v);

    /**
     * @brief Returns true if the pod is in a inheritance
     * relationship, as either the parent or the child.
     */
    bool is_parent_or_child() const;

    /**
     * @brief Returns true if there is a type in the list of qualified
     * names which requires special formatting.
     *
     * The objective of this function is to determine if one is
     * required to use ios stream state saving or not. For types such
     * as bool, etc we are expected to change the state of the stream
     * so state saving is required.
     */
    bool requires_stream_manipulators() const;
    void requires_stream_manipulators(const bool v);

private:
    std::unordered_set<sml::qname> names_;
    std::unordered_set<sml::qname> forward_decls_;
    std::unordered_set<sml::qname> keys_;
    std::unordered_set<sml::qname> leaves_;
    bool has_std_string_;
    bool has_variant_;
    bool is_parent_;
    bool is_child_;
    bool requires_stream_manipulators_;
};

} } } }

#endif
