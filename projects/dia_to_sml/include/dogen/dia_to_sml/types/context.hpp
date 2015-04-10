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

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/hash/qname_hash.hpp"
#include "dogen/dia_to_sml/serialization/context_fwd_ser.hpp"

namespace dogen {
namespace dia_to_sml {

/**
 * @brief Collects all the information required by the visitor as it traverses the graph.
 */
class context final {
public:
    context() = default;
    context(const context&) = default;
    context(context&&) = default;
    ~context() = default;

public:
    context(
        const std::unordered_map<std::string, std::list<std::string> >& child_id_to_parent_ids,
        const std::unordered_set<std::string>& parent_ids,
        const std::unordered_map<std::string, dogen::sml::qname>& id_to_qname,
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
    /**
     * @brief List of parent object IDs for a given child ID.
     */
    /**@{*/
    const std::unordered_map<std::string, std::list<std::string> >& child_id_to_parent_ids() const;
    std::unordered_map<std::string, std::list<std::string> >& child_id_to_parent_ids();
    void child_id_to_parent_ids(const std::unordered_map<std::string, std::list<std::string> >& v);
    void child_id_to_parent_ids(const std::unordered_map<std::string, std::list<std::string> >&& v);
    /**@}*/

    /**
     * @brief All dia object IDs of classes that are parents in a generalisation.
     */
    /**@{*/
    const std::unordered_set<std::string>& parent_ids() const;
    std::unordered_set<std::string>& parent_ids();
    void parent_ids(const std::unordered_set<std::string>& v);
    void parent_ids(const std::unordered_set<std::string>&& v);
    /**@}*/

    /**
     * @brief The QName corresponding to a dia object ID.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::sml::qname>& id_to_qname() const;
    std::unordered_map<std::string, dogen::sml::qname>& id_to_qname();
    void id_to_qname(const std::unordered_map<std::string, dogen::sml::qname>& v);
    void id_to_qname(const std::unordered_map<std::string, dogen::sml::qname>&& v);
    /**@}*/

    /**
     * @brief Maps a QName to its corresponding top-most parent in an inheritance tree.
     */
    /**@{*/
    const std::unordered_map<dogen::sml::qname, dogen::sml::qname>& original_parent() const;
    std::unordered_map<dogen::sml::qname, dogen::sml::qname>& original_parent();
    void original_parent(const std::unordered_map<dogen::sml::qname, dogen::sml::qname>& v);
    void original_parent(const std::unordered_map<dogen::sml::qname, dogen::sml::qname>&& v);
    /**@}*/

    /**
     * @brief All outermost derived objects in an inheritance tree.
     */
    /**@{*/
    const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::qname> >& leaves() const;
    std::unordered_map<dogen::sml::qname, std::list<dogen::sml::qname> >& leaves();
    void leaves(const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::qname> >& v);
    void leaves(const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::qname> >&& v);
    /**@}*/

    /**
     * @brief All modules that sit just below the model.
     */
    /**@{*/
    const std::unordered_set<std::string>& top_level_module_names() const;
    std::unordered_set<std::string>& top_level_module_names();
    void top_level_module_names(const std::unordered_set<std::string>& v);
    void top_level_module_names(const std::unordered_set<std::string>&& v);
    /**@}*/

    /**
     * @brief SML model we are currently building.
     */
    /**@{*/
    const dogen::sml::model& model() const;
    dogen::sml::model& model();
    void model(const dogen::sml::model& v);
    void model(const dogen::sml::model&& v);
    /**@}*/

public:
    bool operator==(const context& rhs) const;
    bool operator!=(const context& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(context& other) noexcept;
    context& operator=(context other);

private:
    std::unordered_map<std::string, std::list<std::string> > child_id_to_parent_ids_;
    std::unordered_set<std::string> parent_ids_;
    std::unordered_map<std::string, dogen::sml::qname> id_to_qname_;
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
