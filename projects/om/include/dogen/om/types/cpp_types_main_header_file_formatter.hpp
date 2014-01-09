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
#ifndef DOGEN_OM_TYPES_CPP_TYPES_MAIN_HEADER_FILE_FORMATTER_HPP
#define DOGEN_OM_TYPES_CPP_TYPES_MAIN_HEADER_FILE_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <memory>
#include <ostream>
#include <boost/filesystem/path.hpp>
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/types/type_visitor.hpp"
#include "dogen/om/types/cpp_includes.hpp"
#include "dogen/om/types/comment_formatter.hpp"
#include "dogen/om/types/type_formatter_interface.hpp"
#include "dogen/om/types/module_formatter_interface.hpp"

namespace dogen {
namespace om {

/**
 * @brief Formats SML types into their C++ representation.
 */
class cpp_types_main_header_file_formatter : public type_formatter_interface,
                                             public module_formatter_interface,
                                             private sml::type_visitor {
public:
    cpp_types_main_header_file_formatter(
        const cpp_types_main_header_file_formatter&) = default;
    cpp_types_main_header_file_formatter(
        cpp_types_main_header_file_formatter&&) = default;

private:
    class helper;

public:
    /**
     * @brief Initialise types formatter.
     *
     * @param model underlying model
     * @param include_directory directory in which the header files
     * will be placed.
     * @param legacy_mode if true, formatter output will match legacy
     * formatters.
     */
    cpp_types_main_header_file_formatter(
        const sml::model& model,
        const boost::filesystem::path& include_directory,
        const bool legacy_mode = false);
    virtual ~cpp_types_main_header_file_formatter() noexcept { }

private:
    /**
     * @brief Returns all of the C++ namespaces implied by the qname.
     */
    std::list<std::string> namespaces(const sml::qname& qn) const;

    /**
     * @brief Throws if helper is null.
     */
    void ensure_non_null_helper() const;

    /**
     * @brief Uses the current state of the helper to create a file.
     */
    file build_file(const boost::property_tree::ptree& meta_data) const;

private:
    /**
     * @brief Formats open class statements for the object.
     */
    void open_class(const sml::object& o) const;

    /**
     * @brief Formats close class statements for the object.
     */
    void close_class() const;

    /**
     * @brief Formats the constructors that are compiler generated via
     * the explicit default keyword.
     */
    void explicitly_defaulted_functions(const sml::object& o) const;

    /**
     * @brief Formats the default constructor.
     */
    void default_constructor(const sml::object& o) const;

    /**
     * @brief Formats the move constructor.
     */
    void move_constructor(const sml::object& o) const;

    /**
     * @brief Formats the complete constructor.
     *
     * A complete constructor is one that takes every member variable
     * as an input.
     */
    void complete_constructor(const sml::object& o) const;

    /**
     * @brief Formats the destructor.
     */
    void destructor(const sml::object& o) const;

    /**
     * @brief Formats all the friend declarations.
     */
    void friends(const sml::object& o) const;

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
    void getters_and_setters(const sml::object& o) const;

    /**
     * @brief Formats member variables.
     */
    void member_variables(const sml::object& o) const;

    /**
     * @brief Formats the in-class equality operator.
     */
    void internal_equality(const sml::object& o) const;

    /**
     * @brief Formats the to stream method.
     */
    void to_stream(const sml::object& o) const;

    /**
     * @brief Formats in-class swap method.
     */
    void internal_swap(const sml::object& o) const;

    /**
     * @brief Formats the in-class assignment operator.
     */
    void internal_assignment(const sml::object& o) const;

    /**
     * @brief Formats the visitor pattern related methods.
     */
    void visitor_method(const sml::object& o) const;

private:
    /**
     * @brief Formats the out-of-class equality operator.
     */
    void external_equality(const sml::object& o) const;

    /**
     * @brief Formats out-of-class swap method.
     */
    void external_swap(const sml::object& o) const;

    /**
     * @brief Formats out-class inserter operator.
     */
    void external_inserter(const sml::object& o) const;

    /**
     * @brief Formats a destructor implementation.
     */
    void destructor_implementation(const sml::object& o) const;

private:
    /**
     * @brief Formats non-specialised objects such as entities, value
     * objects, etc.
     */
    void format_non_specialised_object(const sml::object& o) const;

private:
    using sml::type_visitor::visit;
    void visit(const sml::enumeration& e) const override;
    void visit(const sml::object& o) const override;

public:
    bool generate(const boost::property_tree::ptree& meta_data) const override;

    file format(const sml::module& module, const annotation& a) const override;

    file format(const sml::type& t, const annotation& a) const override;

private:
    const sml::model model_;
    const boost::filesystem::path include_directory_;
    mutable std::shared_ptr<helper> helper_;
    comment_formatter doxygen_next_;
    comment_formatter doxygen_previous_;
    const bool legacy_mode_;
};

} }

#endif
