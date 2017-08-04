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
#ifndef DOGEN_YARN_TYPES_META_MODEL_MODEL_HPP
#define DOGEN_YARN_TYPES_META_MODEL_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include "dogen/yarn/types/meta_model/name.hpp"
#include "dogen/yarn/types/meta_model/languages.hpp"
#include "dogen/yarn/types/meta_model/module_fwd.hpp"
#include "dogen/yarn/types/meta_model/element_fwd.hpp"
#include "dogen/yarn/types/meta_model/facet_properties.hpp"
#include "dogen/yarn/types/meta_model/orm_model_properties.hpp"
#include "dogen/yarn/serialization/meta_model/model_fwd_ser.hpp"

namespace dogen {
namespace yarn {
namespace meta_model {

/**
 * @brief Yarn model.
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
        const dogen::yarn::meta_model::name& name,
        const dogen::yarn::meta_model::name& meta_name,
        const std::vector<boost::shared_ptr<dogen::yarn::meta_model::element> >& elements,
        const boost::shared_ptr<dogen::yarn::meta_model::module>& root_module,
        const std::unordered_set<std::string>& module_ids,
        const bool has_generatable_types,
        const dogen::yarn::meta_model::languages input_language,
        const dogen::yarn::meta_model::languages output_language,
        const boost::optional<dogen::yarn::meta_model::orm_model_properties>& orm_properties,
        const std::unordered_map<std::string, dogen::yarn::meta_model::facet_properties>& facet_properties);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::meta_model::model& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::meta_model::model& v, unsigned int version);

public:
    /**
     * @brief Fully qualified name.
     */
    /**@{*/
    const dogen::yarn::meta_model::name& name() const;
    dogen::yarn::meta_model::name& name();
    void name(const dogen::yarn::meta_model::name& v);
    void name(const dogen::yarn::meta_model::name&& v);
    /**@}*/

    /**
     * @brief Name of the element in the meta-model that this instance conforms to.
     */
    /**@{*/
    const dogen::yarn::meta_model::name& meta_name() const;
    dogen::yarn::meta_model::name& meta_name();
    void meta_name(const dogen::yarn::meta_model::name& v);
    void meta_name(const dogen::yarn::meta_model::name&& v);
    /**@}*/

    const std::vector<boost::shared_ptr<dogen::yarn::meta_model::element> >& elements() const;
    std::vector<boost::shared_ptr<dogen::yarn::meta_model::element> >& elements();
    void elements(const std::vector<boost::shared_ptr<dogen::yarn::meta_model::element> >& v);
    void elements(const std::vector<boost::shared_ptr<dogen::yarn::meta_model::element> >&& v);

    /**
     * @brief The module that represents the model.
     */
    /**@{*/
    const boost::shared_ptr<dogen::yarn::meta_model::module>& root_module() const;
    boost::shared_ptr<dogen::yarn::meta_model::module>& root_module();
    void root_module(const boost::shared_ptr<dogen::yarn::meta_model::module>& v);
    void root_module(const boost::shared_ptr<dogen::yarn::meta_model::module>&& v);
    /**@}*/

    /**
     * @brief IDs of all of the model elements which are modules.
     */
    /**@{*/
    const std::unordered_set<std::string>& module_ids() const;
    std::unordered_set<std::string>& module_ids();
    void module_ids(const std::unordered_set<std::string>& v);
    void module_ids(const std::unordered_set<std::string>&& v);
    /**@}*/

    /**
     * @brief If true the intermediate model has at least one generable type, false otherwise.
     */
    /**@{*/
    bool has_generatable_types() const;
    void has_generatable_types(const bool v);
    /**@}*/

    /**
     * @brief Language in which this model was written.
     */
    /**@{*/
    dogen::yarn::meta_model::languages input_language() const;
    void input_language(const dogen::yarn::meta_model::languages v);
    /**@}*/

    /**
     * @brief Language in which to output the model.
     */
    /**@{*/
    dogen::yarn::meta_model::languages output_language() const;
    void output_language(const dogen::yarn::meta_model::languages v);
    /**@}*/

    const boost::optional<dogen::yarn::meta_model::orm_model_properties>& orm_properties() const;
    boost::optional<dogen::yarn::meta_model::orm_model_properties>& orm_properties();
    void orm_properties(const boost::optional<dogen::yarn::meta_model::orm_model_properties>& v);
    void orm_properties(const boost::optional<dogen::yarn::meta_model::orm_model_properties>&& v);

    const std::unordered_map<std::string, dogen::yarn::meta_model::facet_properties>& facet_properties() const;
    std::unordered_map<std::string, dogen::yarn::meta_model::facet_properties>& facet_properties();
    void facet_properties(const std::unordered_map<std::string, dogen::yarn::meta_model::facet_properties>& v);
    void facet_properties(const std::unordered_map<std::string, dogen::yarn::meta_model::facet_properties>&& v);

public:
    bool operator==(const model& rhs) const;
    bool operator!=(const model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(model& other) noexcept;
    model& operator=(model other);

private:
    dogen::yarn::meta_model::name name_;
    dogen::yarn::meta_model::name meta_name_;
    std::vector<boost::shared_ptr<dogen::yarn::meta_model::element> > elements_;
    boost::shared_ptr<dogen::yarn::meta_model::module> root_module_;
    std::unordered_set<std::string> module_ids_;
    bool has_generatable_types_;
    dogen::yarn::meta_model::languages input_language_;
    dogen::yarn::meta_model::languages output_language_;
    boost::optional<dogen::yarn::meta_model::orm_model_properties> orm_properties_;
    std::unordered_map<std::string, dogen::yarn::meta_model::facet_properties> facet_properties_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::meta_model::model& lhs,
    dogen::yarn::meta_model::model& rhs) {
    lhs.swap(rhs);
}

}

#endif
