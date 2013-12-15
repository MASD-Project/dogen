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
#ifndef DOGEN_SML_TO_CPP_TYPES_TRANSFORMER_HPP
#define DOGEN_SML_TO_CPP_TYPES_TRANSFORMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <tuple>
#include <unordered_set>
#include <boost/optional.hpp>
#include "dogen/sml/types/type.hpp"
#include "dogen/sml/types/abstract_object.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/hash/qname_hash.hpp"
#include "dogen/sml/types/module.hpp"
#include "dogen/sml/types/enumeration.hpp"
#include "dogen/sml/types/nested_qname.hpp"
#include "dogen/sml/types/type_visitor.hpp"
#include "dogen/cpp/types/class_info.hpp"
#include "dogen/cpp/types/namespace_info.hpp"
#include "dogen/cpp/types/exception_info.hpp"
#include "dogen/cpp/types/enum_info.hpp"
#include "dogen/cpp/types/nested_type_info.hpp"
#include "dogen/cpp/types/registrar_info.hpp"
#include "dogen/cpp/types/visitor_info.hpp"
#include "dogen/sml_to_cpp/types/context.hpp"


namespace dogen {
namespace sml_to_cpp {

/**
 * @brief Transforms an SML type into its corresponding CPP type.
 */
class transformer : public sml::type_visitor {
public:
    transformer() = delete;
    transformer(const transformer&) = default;
    transformer& operator=(const transformer&) = delete;
    transformer(transformer&& rhs) = default;

public:
    transformer(const sml::model& m, context& c);
    virtual ~transformer() noexcept { }

public:
    typedef boost::optional<cpp::class_info> optional_class_info;

private:
    /**
     * @brief Converts an SML qname into a C++ qualified name.
     */
    std::string to_qualified_name(const sml::qname& qn) const;

    /**
     * @brief Flattens all the SML namespace information stored in qname
     * into a list of strings with C++ namespaces.
     */
    std::list<std::string> to_namespace_list(const sml::qname& qn) const;

    /**
     * @brief Transforms the SML nested qname into a nested type info.
     */
    void to_nested_type_info(const sml::nested_qname& nqn,
        cpp::nested_type_info& nti, std::string& complete_name,
        bool& requires_stream_manipulators) const;

    /**
     * @brief Transforms an SML property into a property info.
     *
     * The four Boolean values on the tuple work as follows:
     *
     * @li position 1: if true, the property has a top-level primitive
     * type.
     *
     * @li position 2: if true, the property requires stream
     * manipulators.
     *
     * @li position 3: if true, the property invalidates the compiler
     * generated move constructor.
     *
     * @li position 4: if true, the property invalidates the compiler
     * generated default constructor.
     */
    std::tuple<cpp::property_info, bool, bool, bool, bool>
    to_property_info(const sml::property p, const bool is_immutable,
        const bool is_fluent) const;

    /**
     * @brief Transforms an SML property to an enumerator info.
     */
    cpp::enumerator_info to_enumerator_info(const sml::enumerator& e) const;

    /**
     * @brief Transforms a SML value containing an enumeration into an
     * enumeration info.
     */
    cpp::enum_info to_enumeration_info(const sml::enumeration& e) const;

    /**
     * @brief Transforms a SML value containing an exception into an
     * exception info.
     */
    cpp::exception_info to_exception_info(const sml::value_object& vo) const;

    /**
     * @brief Transform a SML object into a class info.
     *
     * @param ao object to transform.
     */
    cpp::class_info to_class_info(const sml::abstract_object& ao) const;

    /**
     * @brief Transform a SML object representing a visitor into a
     * visitor info.
     *
     * @pre value object must have a visitor type.
     */
    cpp::visitor_info to_visitor(const sml::object& v) const;

private:
    /**
     * @brief Adds the class info to the context.
     */
    void add_class(const sml::qname& qn, const cpp::class_info& ci);

private:
    using type_visitor::visit;
    void visit(const dogen::sml::object& f) override;
    void visit(const dogen::sml::enumeration& e) override;
    void visit(const dogen::sml::value_object& vo) override;

public:
    /**
     * @brief Transforms an SML type into the appropriate C++ object.
     */
    void from_type(const sml::type& t);

    /**
     * @brief Transforms a SML module into a namespace info.
     */
    void to_namespace_info(const sml::module& m);

    /**
     * @brief Transforms a SML model into a namespace info.
     *
     * @todo Create an attribute of type module in model.
     */
    void model_to_namespace_info();

    /**
     * @brief Transforms a SML model into a registrar info.
     */
    void model_to_registrar_info();

private:
    const sml::model& model_;
    context& context_;
};

} }

#endif
