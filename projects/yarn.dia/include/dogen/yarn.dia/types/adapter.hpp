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
#ifndef DOGEN_YARN_DIA_TYPES_ADAPTER_HPP
#define DOGEN_YARN_DIA_TYPES_ADAPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <memory>
#include <utility>
#include <boost/shared_ptr.hpp>
#include "dogen/dia/types/object.hpp"
#include "dogen/dia/types/attribute.hpp"
#include "dogen/yarn/types/meta_model/enumeration.hpp"
#include "dogen/yarn/types/meta_model/primitive.hpp"
#include "dogen/yarn/types/meta_model/exception.hpp"
#include "dogen/yarn/types/meta_model/element.hpp"
#include "dogen/yarn/types/meta_model/object.hpp"
#include "dogen/yarn/types/meta_model/module.hpp"
#include "dogen/yarn/types/meta_model/object_template.hpp"
#include "dogen/yarn.dia/types/processed_object.hpp"
#include "dogen/yarn.dia/types/processed_attribute.hpp"
#include "dogen/yarn.dia/types/context.hpp"

namespace dogen {
namespace yarn {
namespace dia {

/**
 * @brief Transforms Dia objects into their yarn counterpart.
 */
class adapter {
public:
    adapter() = delete;
    adapter(const adapter&) = delete;
    adapter(adapter&&) = default;
    ~adapter() noexcept = default;

public:
    /**
     * @brief Initialises the adapter.
     *
     * @pre context pre-prepopulated with all the names and IDs
     * required for the transformations requested.
     */
    explicit adapter(const context& ctx);

private:
    /**
     * @brief Ensure the dia object name is valid.
     */
    void validate_dia_object_name(const std::string& n) const;

private:
    /**
     * @brief Creates a yarn name using the dia name provided.
     *
     * @pre n must not be empty.
     * @pre n must be a simple name, not a qualified name.
     */
    meta_model::name to_name(const std::string& n) const;

    /**
     * @brief Creates a name using the name provided, which is
     * interpreted as belonging to supplied module name.
     *
     * @pre n must not be empty.
     * @pre n must be a simple name, not a qualified name.
     */
    meta_model::name to_name(const std::string& n,
        const meta_model::name& module_name) const;

    /**
     * @brief Converts a processed attribute into an yarn attribute.
     *
     * @param a the Dia UML attribute in processed form.
     *
     * @pre name and type of attribute must not be empty.
     */
    meta_model::attribute to_attribute(const processed_attribute& a) const;

    /**
     * @brief Converts a processed attribute into an yarn enumerator.
     *
     * @param a the Dia UML attribute in processed form.
     *
     * @pre name and type of attribute must not be empty.
     */
    meta_model::enumerator to_enumerator(const processed_attribute& a) const;

private:
    /**
     * @brief Populates the yarn element attributes using the
     * processed object.
     */
    void populate_element(const processed_object& po,
        meta_model::element& e) const;

public:
    /**
     * @brief Generates a scribble group from the processed object.
     *
     * FIXME: public for now until we fix module processing.
     */
    annotations::scribble_group to_scribble_group(
        const processed_object& po, const bool is_root_module) const;

    /**
     * @brief Converts a processed object containing a UML class with a
     * stereotype of exception to a yarn exception.
     *
     * @param po the Dia UML class containing an enumeration.
     *
     * @pre processed object must have the exception flag set.
     */
    std::pair<annotations::scribble_group,
              boost::shared_ptr<meta_model::exception>>
    to_exception(const processed_object& po) const;

    /**
     * @brief Converts Dia a object containing a UML class with a
     * stereotype of value object or service to a yarn object.
     *
     * @param po the Dia UML class containing a value object or
     * service.
     *
     * @pre processed object must have the value object flag set.
     */
    std::pair<annotations::scribble_group,
              boost::shared_ptr<meta_model::object>>
    to_object(const processed_object& po) const;

    /**
     * @brief Converts a Dia object containing a class into an
     * enumeration.
     *
     * @param po the Dia UML class containing an enumeration.
     */
    std::pair<annotations::scribble_group,
              boost::shared_ptr<meta_model::enumeration>>
    to_enumeration(const processed_object& po) const;

    /**
     * @brief Converts a Dia object containing a class into a
     * primitive.
     *
     * @param po the Dia UML class containing a primitive.
     */
    std::pair<annotations::scribble_group,
              boost::shared_ptr<meta_model::primitive>>
    to_primitive(const processed_object& po) const;

    /**
     * @brief Converts a Dia object of type large UML package into a
     * module in yarn.
     *
     * @param po Dia object which contains a UML package.
     */
    boost::shared_ptr<meta_model::module>
    to_module(const processed_object& po) const;

    /**
     * @brief Converts a dia object with a stereotype of object
     * template into a yarn object template.
     *
     * @param po Dia object which contains a concept.
     */
    std::pair<annotations::scribble_group,
              boost::shared_ptr<meta_model::object_template>>
    to_object_template(const processed_object& o) const;

private:
    const context& context_;
};

} } }

#endif
