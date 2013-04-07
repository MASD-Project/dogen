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
#ifndef DOGEN_DIA_TO_SML_TYPES_VISIT_STATE_HPP
#define DOGEN_DIA_TO_SML_TYPES_VISIT_STATE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "dogen/dia_to_sml/serialization/visit_state_fwd_ser.hpp"
#include "dogen/sml/hash/qname_hash.hpp"
#include "dogen/sml/types/package.hpp"
#include "dogen/sml/types/pod.hpp"
#include "dogen/sml/types/qname.hpp"

namespace dogen {
namespace dia_to_sml {

/**
 * @brief Collects all the information required by the visitor as it traverses the graph.
 */
class visit_state final {
public:
    visit_state(const visit_state&) = default;
    visit_state(visit_state&&) = default;
    ~visit_state() = default;

public:
    visit_state();

public:
    visit_state(
        const std::string& model_name,
        const std::unordered_map<dogen::sml::qname, dogen::sml::pod>& pods,
        const std::list<std::string>& external_package_path,
        const bool verbose,
        const bool is_target,
        const std::unordered_map<std::string, std::string>& child_to_parent,
        const std::unordered_set<std::string>& parent_ids,
        const std::unordered_map<std::string, dogen::sml::package>& packages_by_id,
        const std::unordered_map<std::string, dogen::sml::qname>& dia_id_to_qname,
        const std::unordered_map<dogen::sml::qname, dogen::sml::qname>& original_parent,
        const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::qname> >& leaves,
        const std::unordered_set<std::string>& dependencies,
        const std::unordered_set<std::string>& top_level_packages);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const visit_state& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, visit_state& v, unsigned int version);

public:
    const std::string& model_name() const;
    std::string& model_name();
    void model_name(const std::string& v);
    void model_name(const std::string&& v);

    const std::unordered_map<dogen::sml::qname, dogen::sml::pod>& pods() const;
    std::unordered_map<dogen::sml::qname, dogen::sml::pod>& pods();
    void pods(const std::unordered_map<dogen::sml::qname, dogen::sml::pod>& v);
    void pods(const std::unordered_map<dogen::sml::qname, dogen::sml::pod>&& v);

    const std::list<std::string>& external_package_path() const;
    std::list<std::string>& external_package_path();
    void external_package_path(const std::list<std::string>& v);
    void external_package_path(const std::list<std::string>&& v);

    bool verbose() const;
    void verbose(const bool v);

    bool is_target() const;
    void is_target(const bool v);

    const std::unordered_map<std::string, std::string>& child_to_parent() const;
    std::unordered_map<std::string, std::string>& child_to_parent();
    void child_to_parent(const std::unordered_map<std::string, std::string>& v);
    void child_to_parent(const std::unordered_map<std::string, std::string>&& v);

    const std::unordered_set<std::string>& parent_ids() const;
    std::unordered_set<std::string>& parent_ids();
    void parent_ids(const std::unordered_set<std::string>& v);
    void parent_ids(const std::unordered_set<std::string>&& v);

    const std::unordered_map<std::string, dogen::sml::package>& packages_by_id() const;
    std::unordered_map<std::string, dogen::sml::package>& packages_by_id();
    void packages_by_id(const std::unordered_map<std::string, dogen::sml::package>& v);
    void packages_by_id(const std::unordered_map<std::string, dogen::sml::package>&& v);

    const std::unordered_map<std::string, dogen::sml::qname>& dia_id_to_qname() const;
    std::unordered_map<std::string, dogen::sml::qname>& dia_id_to_qname();
    void dia_id_to_qname(const std::unordered_map<std::string, dogen::sml::qname>& v);
    void dia_id_to_qname(const std::unordered_map<std::string, dogen::sml::qname>&& v);

    const std::unordered_map<dogen::sml::qname, dogen::sml::qname>& original_parent() const;
    std::unordered_map<dogen::sml::qname, dogen::sml::qname>& original_parent();
    void original_parent(const std::unordered_map<dogen::sml::qname, dogen::sml::qname>& v);
    void original_parent(const std::unordered_map<dogen::sml::qname, dogen::sml::qname>&& v);

    const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::qname> >& leaves() const;
    std::unordered_map<dogen::sml::qname, std::list<dogen::sml::qname> >& leaves();
    void leaves(const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::qname> >& v);
    void leaves(const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::qname> >&& v);

    const std::unordered_set<std::string>& dependencies() const;
    std::unordered_set<std::string>& dependencies();
    void dependencies(const std::unordered_set<std::string>& v);
    void dependencies(const std::unordered_set<std::string>&& v);

    const std::unordered_set<std::string>& top_level_packages() const;
    std::unordered_set<std::string>& top_level_packages();
    void top_level_packages(const std::unordered_set<std::string>& v);
    void top_level_packages(const std::unordered_set<std::string>&& v);

public:
    bool operator==(const visit_state& rhs) const;
    bool operator!=(const visit_state& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(visit_state& other) noexcept;
    visit_state& operator=(visit_state other);

private:
    std::string model_name_;
    std::unordered_map<dogen::sml::qname, dogen::sml::pod> pods_;
    std::list<std::string> external_package_path_;
    bool verbose_;
    bool is_target_;
    std::unordered_map<std::string, std::string> child_to_parent_;
    std::unordered_set<std::string> parent_ids_;
    std::unordered_map<std::string, dogen::sml::package> packages_by_id_;
    std::unordered_map<std::string, dogen::sml::qname> dia_id_to_qname_;
    std::unordered_map<dogen::sml::qname, dogen::sml::qname> original_parent_;
    std::unordered_map<dogen::sml::qname, std::list<dogen::sml::qname> > leaves_;
    std::unordered_set<std::string> dependencies_;
    std::unordered_set<std::string> top_level_packages_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::dia_to_sml::visit_state& lhs,
    dogen::dia_to_sml::visit_state& rhs) {
    lhs.swap(rhs);
}

}

#endif
