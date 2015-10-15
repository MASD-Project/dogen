/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#ifndef DOGEN_YARN_TYPES_MODEL_HPP
#define DOGEN_YARN_TYPES_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <boost/optional.hpp>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/module.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/concept.hpp"
#include "dogen/yarn/hash/name_hash.hpp"
#include "dogen/dynamic/types/object.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/origin_types.hpp"
#include "dogen/yarn/types/generation_types.hpp"
#include "dogen/yarn/serialization/model_fwd_ser.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Software representation of a domain model.
 *
 * Wikipedia provides the following definition of a @e domain @e model,
 * (slightly abbreviated and modified):
 *
 * <blockquote>
 * A domain model is a conceptual model of all the topics
 * related to a specific problem. It describes the various entities,
 * their attributes, roles and relationships, plus the constraints that
 * govern the problem domain.
 *
 * The domain model is created in order to represent the vocabulary and
 * key concepts of the problem domain. An important advantage of a domain
 * model is that it describes and constrains the scope of the problem
 * domain. The domain model can be effectively used to verify and
 * validate the understanding of the problem domain among various
 * stakeholders. It defines a vocabulary and is helpful as a
 * communication tool. It can add precision and focus to discussion among
 * the business team as well as between the technical and business teams.
 * </blockquote>
 *
 * The objective of the model class is to encompass all the key members
 * of the domain model which have expression in code.
 */
class model final {
public:
    model(const model&) = default;
    ~model() = default;

public:
    model();

public:
    model(model&& rhs);

public:
    model(
        const std::string& documentation,
        const dogen::dynamic::object& extensions,
        const dogen::yarn::name& name,
        const dogen::yarn::generation_types generation_type,
        const dogen::yarn::origin_types origin_type,
        const boost::optional<dogen::yarn::name>& containing_module,
        const std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types>& references,
        const std::unordered_set<dogen::yarn::name>& leaves,
        const std::unordered_map<dogen::yarn::name, dogen::yarn::module>& modules,
        const std::unordered_map<dogen::yarn::name, dogen::yarn::concept>& concepts,
        const std::unordered_map<dogen::yarn::name, dogen::yarn::primitive>& primitives,
        const std::unordered_map<dogen::yarn::name, dogen::yarn::enumeration>& enumerations,
        const std::unordered_map<dogen::yarn::name, dogen::yarn::object>& objects,
        const bool is_target,
        const bool has_generatable_types);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const model& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, model& v, unsigned int version);

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
    const dogen::yarn::name& name() const;
    dogen::yarn::name& name();
    void name(const dogen::yarn::name& v);
    void name(const dogen::yarn::name&& v);
    /**@}*/

    /**
     * @brief What to do with this type in terms of code generation.
     */
    /**@{*/
    dogen::yarn::generation_types generation_type() const;
    void generation_type(const dogen::yarn::generation_types v);
    /**@}*/

    /**
     * @brief How was this model element originated.
     */
    /**@{*/
    dogen::yarn::origin_types origin_type() const;
    void origin_type(const dogen::yarn::origin_types v);
    /**@}*/

    /**
     * @brief Name of the module in which we are contained.
     */
    /**@{*/
    const boost::optional<dogen::yarn::name>& containing_module() const;
    boost::optional<dogen::yarn::name>& containing_module();
    void containing_module(const boost::optional<dogen::yarn::name>& v);
    void containing_module(const boost::optional<dogen::yarn::name>&& v);
    /**@}*/

    /**
     * @brief All other models that this model depends on, mapped to their origin.
     */
    /**@{*/
    const std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types>& references() const;
    std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types>& references();
    void references(const std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types>& v);
    void references(const std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types>&& v);
    /**@}*/

    /**
     * @brief All leaf types in this model.
     *
     * Leaves are types concrete types which have a parent.
     */
    /**@{*/
    const std::unordered_set<dogen::yarn::name>& leaves() const;
    std::unordered_set<dogen::yarn::name>& leaves();
    void leaves(const std::unordered_set<dogen::yarn::name>& v);
    void leaves(const std::unordered_set<dogen::yarn::name>&& v);
    /**@}*/

    /**
     * @brief Modules contained in the model.
     */
    /**@{*/
    const std::unordered_map<dogen::yarn::name, dogen::yarn::module>& modules() const;
    std::unordered_map<dogen::yarn::name, dogen::yarn::module>& modules();
    void modules(const std::unordered_map<dogen::yarn::name, dogen::yarn::module>& v);
    void modules(const std::unordered_map<dogen::yarn::name, dogen::yarn::module>&& v);
    /**@}*/

    /**
     * @brief All the concepts available in this model.
     */
    /**@{*/
    const std::unordered_map<dogen::yarn::name, dogen::yarn::concept>& concepts() const;
    std::unordered_map<dogen::yarn::name, dogen::yarn::concept>& concepts();
    void concepts(const std::unordered_map<dogen::yarn::name, dogen::yarn::concept>& v);
    void concepts(const std::unordered_map<dogen::yarn::name, dogen::yarn::concept>&& v);
    /**@}*/

    /**
     * @brief All primitives contained in this model.
     */
    /**@{*/
    const std::unordered_map<dogen::yarn::name, dogen::yarn::primitive>& primitives() const;
    std::unordered_map<dogen::yarn::name, dogen::yarn::primitive>& primitives();
    void primitives(const std::unordered_map<dogen::yarn::name, dogen::yarn::primitive>& v);
    void primitives(const std::unordered_map<dogen::yarn::name, dogen::yarn::primitive>&& v);
    /**@}*/

    /**
     * @brief All enumerations contained in this model.
     */
    /**@{*/
    const std::unordered_map<dogen::yarn::name, dogen::yarn::enumeration>& enumerations() const;
    std::unordered_map<dogen::yarn::name, dogen::yarn::enumeration>& enumerations();
    void enumerations(const std::unordered_map<dogen::yarn::name, dogen::yarn::enumeration>& v);
    void enumerations(const std::unordered_map<dogen::yarn::name, dogen::yarn::enumeration>&& v);
    /**@}*/

    /**
     * @brief All objects contained in this model.
     */
    /**@{*/
    const std::unordered_map<dogen::yarn::name, dogen::yarn::object>& objects() const;
    std::unordered_map<dogen::yarn::name, dogen::yarn::object>& objects();
    void objects(const std::unordered_map<dogen::yarn::name, dogen::yarn::object>& v);
    void objects(const std::unordered_map<dogen::yarn::name, dogen::yarn::object>&& v);
    /**@}*/

    /**
     * @brief If true, this model is the target model.
     */
    /**@{*/
    bool is_target() const;
    void is_target(const bool v);
    /**@}*/

    /**
     * @brief If true the model has at least one generable type, false otherwise.
     */
    /**@{*/
    bool has_generatable_types() const;
    void has_generatable_types(const bool v);
    /**@}*/

public:
    bool operator==(const model& rhs) const;
    bool operator!=(const model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(model& other) noexcept;
    model& operator=(model other);

private:
    std::string documentation_;
    dogen::dynamic::object extensions_;
    dogen::yarn::name name_;
    dogen::yarn::generation_types generation_type_;
    dogen::yarn::origin_types origin_type_;
    boost::optional<dogen::yarn::name> containing_module_;
    std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types> references_;
    std::unordered_set<dogen::yarn::name> leaves_;
    std::unordered_map<dogen::yarn::name, dogen::yarn::module> modules_;
    std::unordered_map<dogen::yarn::name, dogen::yarn::concept> concepts_;
    std::unordered_map<dogen::yarn::name, dogen::yarn::primitive> primitives_;
    std::unordered_map<dogen::yarn::name, dogen::yarn::enumeration> enumerations_;
    std::unordered_map<dogen::yarn::name, dogen::yarn::object> objects_;
    bool is_target_;
    bool has_generatable_types_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::model& lhs,
    dogen::yarn::model& rhs) {
    lhs.swap(rhs);
}

}

#endif
