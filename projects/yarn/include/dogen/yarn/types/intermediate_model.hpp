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
#ifndef DOGEN_YARN_TYPES_INTERMEDIATE_MODEL_HPP
#define DOGEN_YARN_TYPES_INTERMEDIATE_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/module.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/builtin.hpp"
#include "dogen/yarn/types/concept.hpp"
#include "dogen/yarn/types/visitor.hpp"
#include "dogen/yarn/hash/name_hash.hpp"
#include "dogen/yarn/types/exception.hpp"
#include "dogen/yarn/types/languages.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/types/element_fwd.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/origin_types.hpp"
#include "dogen/annotations/types/scribble_group.hpp"
#include "dogen/yarn/types/orm_model_configuration.hpp"
#include "dogen/yarn/serialization/intermediate_model_fwd_ser.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Intermediate representation of a yarn model.
 */
class intermediate_model final {
public:
    intermediate_model(const intermediate_model&) = default;
    ~intermediate_model() = default;

public:
    intermediate_model();

public:
    intermediate_model(intermediate_model&& rhs);

public:
    intermediate_model(
        const dogen::yarn::name& name,
        const dogen::yarn::origin_types origin_type,
        const std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types>& references,
        const std::unordered_set<dogen::yarn::name>& leaves,
        const std::unordered_map<std::string, dogen::yarn::module>& modules,
        const std::unordered_map<std::string, dogen::yarn::concept>& concepts,
        const std::unordered_map<std::string, dogen::yarn::builtin>& builtins,
        const std::unordered_map<std::string, dogen::yarn::enumeration>& enumerations,
        const std::unordered_map<std::string, dogen::yarn::primitive>& primitives,
        const std::unordered_map<std::string, dogen::yarn::object>& objects,
        const std::unordered_map<std::string, dogen::yarn::exception>& exceptions,
        const std::unordered_map<std::string, dogen::yarn::visitor>& visitors,
        const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::element> >& injected_elements,
        const bool has_generatable_types,
        const dogen::yarn::module& root_module,
        const dogen::yarn::languages input_language,
        const std::list<dogen::yarn::languages>& output_languages,
        const std::unordered_map<std::string, dogen::annotations::scribble_group>& scribble_groups,
        const boost::optional<dogen::yarn::orm_model_configuration>& orm_configuration);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::intermediate_model& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::intermediate_model& v, unsigned int version);

public:
    /**
     * @brief Fully qualified name.
     */
    /**@{*/
    const dogen::yarn::name& name() const;
    dogen::yarn::name& name();
    void name(const dogen::yarn::name& v);
    void name(const dogen::yarn::name&& v);
    /**@}*/

    /**
     * @brief How was this model element originated.
     */
    /**@{*/
    dogen::yarn::origin_types origin_type() const;
    void origin_type(const dogen::yarn::origin_types v);
    /**@}*/

    /**
     * @brief All other intermediate models that this intermediate model depends on, mapped to their origin.
     */
    /**@{*/
    const std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types>& references() const;
    std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types>& references();
    void references(const std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types>& v);
    void references(const std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types>&& v);
    /**@}*/

    /**
     * @brief All leaf types in this intermediate model.
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
     * @brief Modules contained in the intermediate model.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::yarn::module>& modules() const;
    std::unordered_map<std::string, dogen::yarn::module>& modules();
    void modules(const std::unordered_map<std::string, dogen::yarn::module>& v);
    void modules(const std::unordered_map<std::string, dogen::yarn::module>&& v);
    /**@}*/

    /**
     * @brief All the concepts available in this intermediate model.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::yarn::concept>& concepts() const;
    std::unordered_map<std::string, dogen::yarn::concept>& concepts();
    void concepts(const std::unordered_map<std::string, dogen::yarn::concept>& v);
    void concepts(const std::unordered_map<std::string, dogen::yarn::concept>&& v);
    /**@}*/

    /**
     * @brief All built-ins contained in this intermediate model.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::yarn::builtin>& builtins() const;
    std::unordered_map<std::string, dogen::yarn::builtin>& builtins();
    void builtins(const std::unordered_map<std::string, dogen::yarn::builtin>& v);
    void builtins(const std::unordered_map<std::string, dogen::yarn::builtin>&& v);
    /**@}*/

    /**
     * @brief All enumerations contained in this intermediate model.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::yarn::enumeration>& enumerations() const;
    std::unordered_map<std::string, dogen::yarn::enumeration>& enumerations();
    void enumerations(const std::unordered_map<std::string, dogen::yarn::enumeration>& v);
    void enumerations(const std::unordered_map<std::string, dogen::yarn::enumeration>&& v);
    /**@}*/

    /**
     * @brief All primitives in this intermediate model.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::yarn::primitive>& primitives() const;
    std::unordered_map<std::string, dogen::yarn::primitive>& primitives();
    void primitives(const std::unordered_map<std::string, dogen::yarn::primitive>& v);
    void primitives(const std::unordered_map<std::string, dogen::yarn::primitive>&& v);
    /**@}*/

    /**
     * @brief All objects contained in this intermediate model.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::yarn::object>& objects() const;
    std::unordered_map<std::string, dogen::yarn::object>& objects();
    void objects(const std::unordered_map<std::string, dogen::yarn::object>& v);
    void objects(const std::unordered_map<std::string, dogen::yarn::object>&& v);
    /**@}*/

    /**
     * @brief All exceptions in this model.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::yarn::exception>& exceptions() const;
    std::unordered_map<std::string, dogen::yarn::exception>& exceptions();
    void exceptions(const std::unordered_map<std::string, dogen::yarn::exception>& v);
    void exceptions(const std::unordered_map<std::string, dogen::yarn::exception>&& v);
    /**@}*/

    /**
     * @brief All visitors in this model.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::yarn::visitor>& visitors() const;
    std::unordered_map<std::string, dogen::yarn::visitor>& visitors();
    void visitors(const std::unordered_map<std::string, dogen::yarn::visitor>& v);
    void visitors(const std::unordered_map<std::string, dogen::yarn::visitor>&& v);
    /**@}*/

    const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::element> >& injected_elements() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::element> >& injected_elements();
    void injected_elements(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::element> >& v);
    void injected_elements(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::element> >&& v);

    /**
     * @brief If true the intermediate model has at least one generable type, false otherwise.
     */
    /**@{*/
    bool has_generatable_types() const;
    void has_generatable_types(const bool v);
    /**@}*/

    const dogen::yarn::module& root_module() const;
    dogen::yarn::module& root_module();
    void root_module(const dogen::yarn::module& v);
    void root_module(const dogen::yarn::module&& v);

    /**
     * @brief Language in which this model was written.
     */
    /**@{*/
    dogen::yarn::languages input_language() const;
    void input_language(const dogen::yarn::languages v);
    /**@}*/

    /**
     * @brief Languages in which to output this model.
     */
    /**@{*/
    const std::list<dogen::yarn::languages>& output_languages() const;
    std::list<dogen::yarn::languages>& output_languages();
    void output_languages(const std::list<dogen::yarn::languages>& v);
    void output_languages(const std::list<dogen::yarn::languages>&& v);
    /**@}*/

    const std::unordered_map<std::string, dogen::annotations::scribble_group>& scribble_groups() const;
    std::unordered_map<std::string, dogen::annotations::scribble_group>& scribble_groups();
    void scribble_groups(const std::unordered_map<std::string, dogen::annotations::scribble_group>& v);
    void scribble_groups(const std::unordered_map<std::string, dogen::annotations::scribble_group>&& v);

    const boost::optional<dogen::yarn::orm_model_configuration>& orm_configuration() const;
    boost::optional<dogen::yarn::orm_model_configuration>& orm_configuration();
    void orm_configuration(const boost::optional<dogen::yarn::orm_model_configuration>& v);
    void orm_configuration(const boost::optional<dogen::yarn::orm_model_configuration>&& v);

public:
    bool operator==(const intermediate_model& rhs) const;
    bool operator!=(const intermediate_model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(intermediate_model& other) noexcept;
    intermediate_model& operator=(intermediate_model other);

private:
    dogen::yarn::name name_;
    dogen::yarn::origin_types origin_type_;
    std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types> references_;
    std::unordered_set<dogen::yarn::name> leaves_;
    std::unordered_map<std::string, dogen::yarn::module> modules_;
    std::unordered_map<std::string, dogen::yarn::concept> concepts_;
    std::unordered_map<std::string, dogen::yarn::builtin> builtins_;
    std::unordered_map<std::string, dogen::yarn::enumeration> enumerations_;
    std::unordered_map<std::string, dogen::yarn::primitive> primitives_;
    std::unordered_map<std::string, dogen::yarn::object> objects_;
    std::unordered_map<std::string, dogen::yarn::exception> exceptions_;
    std::unordered_map<std::string, dogen::yarn::visitor> visitors_;
    std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::element> > injected_elements_;
    bool has_generatable_types_;
    dogen::yarn::module root_module_;
    dogen::yarn::languages input_language_;
    std::list<dogen::yarn::languages> output_languages_;
    std::unordered_map<std::string, dogen::annotations::scribble_group> scribble_groups_;
    boost::optional<dogen::yarn::orm_model_configuration> orm_configuration_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::intermediate_model& lhs,
    dogen::yarn::intermediate_model& rhs) {
    lhs.swap(rhs);
}

}

#endif
