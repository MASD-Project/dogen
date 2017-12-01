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
#ifndef DOGEN_YARN_TYPES_HELPERS_ADAPTER_HPP
#define DOGEN_YARN_TYPES_HELPERS_ADAPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <iosfwd>
#include <boost/shared_ptr.hpp>
#include "dogen/yarn/types/meta_model/element.hpp"
#include "dogen/yarn/types/meta_model/enumerator.hpp"
#include "dogen/yarn/types/meta_model/attribute.hpp"
#include "dogen/yarn/types/meta_model/enumeration.hpp"
#include "dogen/yarn/types/meta_model/primitive.hpp"
#include "dogen/yarn/types/meta_model/exception.hpp"
#include "dogen/yarn/types/meta_model/element.hpp"
#include "dogen/yarn/types/meta_model/object.hpp"
#include "dogen/yarn/types/meta_model/module.hpp"
#include "dogen/yarn/types/meta_model/builtin.hpp"
#include "dogen/yarn/types/meta_model/object_template.hpp"
#include "dogen/yarn/types/meta_model/exoattribute.hpp"
#include "dogen/yarn/types/meta_model/exoelement.hpp"
#include "dogen/yarn/types/transforms/naming_configuration.hpp"

namespace dogen {
namespace yarn {
namespace helpers {

class adapter final {
private:
    /**
     * @brief Ensure the name is not empty.
     */
    void ensure_not_empty(const std::string& n) const;

private:
    /**
     * @brief Creates a yarn name using the dia name provided.
     *
     * @pre n must not be empty.
     * @pre n must be a simple name, not a qualified name.
     */
    meta_model::name to_name(const transforms::naming_configuration& nc,
        const std::string& n) const;

    /**
     * @brief Converts a processed attribute into an yarn attribute.
     *
     * @param a the Dia UML attribute in processed form.
     *
     * @pre name and type of attribute must not be empty.
     */
    meta_model::attribute
    to_attribute(const transforms::naming_configuration& nc,
        const meta_model::exoattribute& ea) const;

    /**
     * @brief Converts a processed attribute into an yarn enumerator.
     *
     * @param a the Dia UML attribute in processed form.
     *
     * @pre name and type of attribute must not be empty.
     */
    meta_model::enumerator
    to_enumerator(const transforms::naming_configuration& nc,
        const meta_model::exoattribute& ea) const;

private:
    /**
     * @brief Populates the meta-model element attributes using the
     * exoelement.
     */
    void populate_element(const transforms::naming_configuration& nc,
        const meta_model::exoelement& ee, meta_model::element& e) const;

public:
    /**
     * @brief Converts an exoelement with a stereotype of yarn::object
     * to a yarn object.
     */
    boost::shared_ptr<meta_model::object>
    to_object(const transforms::naming_configuration& nc,
        const meta_model::exoelement& ee) const;

    /**
     * @brief Converts an exoelement with a stereotype of
     * yarn::object_template to a yarn object template.
     */
    boost::shared_ptr<meta_model::object_template>
    to_object_template(const transforms::naming_configuration& nc,
        const meta_model::exoelement& ee) const;

    /**
     * @brief Converts an exoelement with a stereotype of
     * yarn::exception to a yarn exception.
     */
    boost::shared_ptr<meta_model::exception>
    to_exception(const transforms::naming_configuration& nc,
        const meta_model::exoelement& ee) const;

    /**
     * @brief Converts an exoelement with a stereotype of
     * yarn::primitive to a yarn primitive.
     */
    boost::shared_ptr<meta_model::primitive>
    to_primitive(const transforms::naming_configuration& nc,
        const meta_model::exoelement& ee) const;

    /**
     * @brief Converts an exoelement with a stereotype of
     * yarn::enumeration to a yarn enumeration.
     *
     * @param po the Dia UML class containing an enumeration.
     */
    boost::shared_ptr<meta_model::enumeration>
    to_enumeration(const transforms::naming_configuration& nc,
        const meta_model::exoelement& ee) const;

    /**
     * @brief Converts an exoelement with a stereotype of
     * yarn::module to a yarn module.
     */
    boost::shared_ptr<meta_model::module>
    to_module(const transforms::naming_configuration& nc,
        const meta_model::exoelement& ee) const;

    /**
     * @brief Converts an exoelement with a stereotype of
     * yarn::module to a yarn module.
     */
    boost::shared_ptr<meta_model::builtin>
    to_builtin(const transforms::naming_configuration& nc,
        const meta_model::exoelement& ee) const;
};

} } }

#endif
