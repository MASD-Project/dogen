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
#ifndef DOGEN_DIA_TO_SML_TYPES_CONTEXT_HPP
#define DOGEN_DIA_TO_SML_TYPES_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "dogen/dia_to_sml/serialization/context_fwd_ser.hpp"
#include "dogen/sml/hash/qname_hash.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/qname.hpp"

namespace dogen {
namespace dia_to_sml {

/**
 * @brief Collects all the information required by the visitor as it traverses the graph.
 */
class context final {
public:
    context(const context&) = default;
    context(context&&) = default;
    ~context() = default;

public:
    context();

public:
    context(
        const bool is_target,
        const std::unordered_map<std::string, std::string>& child_to_parent,
        const std::unordered_set<std::string>& parent_ids,
        const std::unordered_map<std::string, dogen::sml::qname>& dia_id_to_qname,
        const std::unordered_map<dogen::sml::qname, dogen::sml::qname>& original_parent,
        const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::qname> >& leaves,
        const std::unordered_set<std::string>& top_level_module_names,
        const dogen::sml::model& model);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const context& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, context& v, unsigned int version);

public:
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

    const std::unordered_set<std::string>& top_level_module_names() const;
    std::unordered_set<std::string>& top_level_module_names();
    void top_level_module_names(const std::unordered_set<std::string>& v);
    void top_level_module_names(const std::unordered_set<std::string>&& v);

    const dogen::sml::model& model() const;
    dogen::sml::model& model();
    void model(const dogen::sml::model& v);
    void model(const dogen::sml::model&& v);

public:
    bool operator==(const context& rhs) const;
    bool operator!=(const context& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(context& other) noexcept;
    context& operator=(context other);

private:
    bool is_target_;
    std::unordered_map<std::string, std::string> child_to_parent_;
    std::unordered_set<std::string> parent_ids_;
    std::unordered_map<std::string, dogen::sml::qname> dia_id_to_qname_;
    std::unordered_map<dogen::sml::qname, dogen::sml::qname> original_parent_;
    std::unordered_map<dogen::sml::qname, std::list<dogen::sml::qname> > leaves_;
    std::unordered_set<std::string> top_level_module_names_;
    dogen::sml::model model_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::dia_to_sml::context& lhs,
    dogen::dia_to_sml::context& rhs) {
    lhs.swap(rhs);
}

}

#endif
