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
#ifndef DOGEN_OM_TYPES_CPP_TYPES_HEADER_FORMATTER_HPP
#define DOGEN_OM_TYPES_CPP_TYPES_HEADER_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <memory>
#include <ostream>
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/types/type_visitor.hpp"
#include "dogen/sml/types/property_cache_interface.hpp"
#include "dogen/om/types/context.hpp"
#include "dogen/om/types/comment_formatter.hpp"
#include "dogen/om/types/type_formatter_interface.hpp"

namespace dogen {
namespace om {

/**
 * @brief Formats SML types into their C++ representation.
 */
class cpp_types_header_formatter : public type_formatter_interface,
                                   private sml::type_visitor {
public:
    cpp_types_header_formatter(const cpp_types_header_formatter&) = default;
    cpp_types_header_formatter(cpp_types_header_formatter&&) = default;

public:
    cpp_types_header_formatter();
    virtual ~cpp_types_header_formatter() noexcept { }

private:
    /**
     * @brief Returns all of the C++ namespaces implied by the qname.
     */
    std::list<std::string> namespaces(const sml::qname& qn) const;

    /**
     * @brief Returns a C++ qualified name for the SML qname.
     */
    std::string cpp_qualified_name(const sml::qname& qn) const;

private:
    /**
     * @brief Formats open class statements for the object.
     */
    void open_class(const sml::abstract_object& o) const;

    /**
     * @brief Formats close class statements for the object.
     */
    void close_class() const;

    /**
     * @brief Formats the constructors that are compiler generated via
     * the explicit default keyword.
     */
    void explicitly_defaulted_functions(const sml::abstract_object& o) const;

    /**
     * @brief Formats the default constructor.
     */
    void default_constructor(const sml::abstract_object& o) const;

    /**
     * @brief Formats the move constructor.
     */
    void move_constructor(const sml::abstract_object& o) const;

    /**
     * @brief Formats the complete constructor.
     *
     * A complete constructor is one that takes every member variable
     * as an input.
     */
    void complete_constructor(const sml::abstract_object& o) const;

    /**
     * @brief Formats the destructor.
     */
    void destructor(const sml::abstract_object& o) const;

    /**
     * @brief Formats all the friend declarations.
     */
    void friends(const sml::abstract_object& o) const;

    /**
     * @brief Formats the getter and setter for a simple type.
     */
    void simple_type_getter_and_setter(const std::string& owner_name,
        const sml::property& p) const;

    /**
     * @brief Formats the getter and setter for a compound type.
     */
    void compound_type_getter_and_setter(const std::string& owner_name,
        const sml::property& p) const;

    /**
     * @brief Top-level method that expands all properties into
     * getters and setters.
     */
    void getters_and_setters(const sml::abstract_object& o) const;

    void member_variables(const sml::abstract_object& o) const;
    void equality(const sml::abstract_object& o) const;
    void to_stream(const sml::abstract_object& o) const;
    void swap(const sml::abstract_object& o) const;
    void assignment(const sml::abstract_object& o) const;
    void visitor_method(const sml::abstract_object& o) const;
    void format(const sml::abstract_object& o) const;

private:
    using sml::type_visitor::visit;
    void visit(const sml::enumeration& e) const override;
    void visit(const sml::service& s) const override;
    void visit(const sml::factory& f) const override;
    void visit(const sml::repository& r) const override;
    void visit(const sml::value_object& vo) const override;
    void visit(const sml::keyed_entity& ke) const override;
    void visit(const sml::entity& e) const override;

public:
    void format(std::ostream& s, const sml::type& t, const licence& l,
        const modeline& m, const std::string& marker,
        const sml::property_cache_interface& c) const override;

private:
    mutable std::unique_ptr<context> context_;
    comment_formatter doxygen_next_;
    comment_formatter doxygen_previous_;
};

} }

#endif
