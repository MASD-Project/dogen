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
#ifndef DOGEN_SML_TYPES_TAGS_HPP
#define DOGEN_SML_TYPES_TAGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen {
namespace sml {

/**
 * @brief Constants for all keys that can be used in a opaque
 * parameter.
 */
struct tags {
    /**
     * @brief Key used to denote an ODB pragma.
     *
     * It is expected to be repeated for a given object type; order is
     * kept as provided by user.
     */
    static const std::string odb_pragma;

    /**
     * @brief Key used to denote copyright holders.
     *
     * It is expected to be repeated in a model; order is kept as
     * provided by user.
     */
    static const std::string copyright_holder;

    /**
     * @brief Name of the legal licence to use.
     *
     * Must match licences available in library.
     */
    static const std::string licence_name;

    /**
     * @brief Name of the modeline group to use.
     *
     * Must match licences available in library.
     */
    static const std::string modeline_group_name;

    /**
     * @brief Comment provided by user when dia does not allow for it.
     *
     * For meta-types where comments are available in Dia (e.g. class,
     * properties, etc), this parameter is ignored. For types where
     * they are not (e.g. model, package), it will be used to populate
     * the meta-type's documentation.
     */
    static const std::string comment;

    /**
     * @brief Attribute that provides this entity its identity.
     */
    static const std::string identity_attribute;

    /**
     * @brief If set to true, the preamble will be generated.
     *
     * The preamble is made up of a modeline, copyright
     * information and licensing details.
     */
    static const std::string generate_preamble;

    /**
     * @brief Name of the top-level parent of the inheritance
     * hierarchy.
     */

    static const std::string original_parent_name;

    /**
     * @brief True if the top-level parent of the hierarchy is
     * visitable.
     */
    static const std::string is_original_parent_visitable;

    /**
     * @brief If true, the type cannot be inherited from.
     */
    static const std::string is_final;

    /**
     * @brief Valid values for Boolean types.
     */
    static const std::string bool_true;
    static const std::string bool_false;

    /**
     * @brief Valid statuses.
     */
    static const std::string status_unsupported;
    static const std::string status_supported;
    static const std::string status_handcrafted;

    /**
     * @brief Tags related to the code generation marker.
     */
    struct code_generation_marker {
        /**
         * @brief If true, add the generation date and time to the marker.
         */
        static const std::string add_date_time;

        /**
         * @brief If true, adds a warning not to modify
         * code-generated files.
         */
        static const std::string add_warning;

        /**
         * @brief Message to place on all code-generated files.
         */
        static const std::string message;
    };

    /**
     * @brief All parameters specific to the C++ language.
     */
    struct cpp {
        /**
         * @brief If true, the project will be split.
         *
         * @deprecated used only for backwards compatibility.
         */
        static const std::string split_project;

        /**
         * @brief Extension to use for header files, including the
         * leading dot.
         *
         * Example: @e .hpp, @e .hxx
         */
        static const std::string header_file_extension;

        /**
         * @brief Extension to use for implementation files, including
         * the leading dot.
         *
         * Example: @e .cpp, @e .cxx.
         */
        static const std::string implementation_file_extension;

        /**
         * @brief If true, files for each facet will be placed in a
         * folder for the facet.
         */
        static const std::string enable_facet_folders;

        /**
         * @brief If true, each file in each facet will have a name
         * unique across all facets.
         *
         * This is achieved by using the facet's postfix.
         */
        static const std::string enable_unique_file_names;

        /**
         * @brief Postfix to use for all forward declaration files.
         */
        static const std::string forward_declaration_postfix;

        /**
         * @brief Parameters specific to the @e types facet.
         *
         * The types facet is the main domain facet.
         */
        struct types {
            /**
             * @brief If set to disabled, the @e types facet will not
             * be generated for this type or model.
             */
            static const std::string status;

            /**
             * @brief Name of the folder to use for this facet.
             */
            static const std::string directory_name;

            /**
             * @brief Postfix for all file names in the facet.
             */
            static const std::string postfix;

            /**
             * @brief Family of the type.
             *
             * Used for debug printing the object, generating test
             * data, etc.
             */
            static const std::string family;

            /**
             * @brief If true, the type is either a primitive or an
             * enumeration.
             */
            static const std::string is_simple_type;

            /**
             * @brief Contains the complete name, as required for the
             * type of a variable or argument.
             *
             * Only makes sense for a property.
             */
            static const std::string complete_name;

            /**
             * @brief Fully-qualified name of the type.
             */
            static const std::string qualified_name;

            /**
             * @brief Fully-qualified name of the top-level parent of
             * the hierarchy.
             */
            static const std::string qualified_original_parent_name;

            /**
             * @brief If set to true, all special defaulted functions
             * will be generated.
             *
             * Note that other tags may still influence specific
             * defaulted functions.
             */
            static const std::string generate_defaulted_functions;

            /**
             * @brief If set to true, a default constructor will be
             * generated.
             */
            static const std::string generate_explicit_default_constructor;

            /**
             * @brief If set to true, a move constructor will be
             * generated.
             */
            static const std::string generate_explicit_move_constructor;

            /**
             * @brief If set to true, a destructor will be
             * generated.
             */
            static const std::string generate_explicit_destructor;

            /**
             * @brief If set to true, an assignment operator will be
             * generated.
             */
            static const std::string generate_explicit_assignment_operator;

            /**
             * @brief If set to true, a complete constructor will be
             * generated.
             */
            static const std::string generate_complete_constructor;

            /**
             * @brief If set to true, the equality operator will be
             * generated.
             */
            static const std::string generate_equality;

            /**
             * @brief If set to true, friends will be declared.
             */
            static const std::string generate_friends;

            /**
             * @brief If set to true, streaming methods will be
             * generated.
             */
            static const std::string generate_to_stream;

            /**
             * @brief If set to true, the visitor accept methods will
             * be generated.
             */
            static const std::string generate_accept;

            /**
             * @brief If set to true, swap function will be
             * generated.
             */
            static const std::string generate_swap;

            /**
             * @brief Parameters associated with the types header file.
             */
            struct header_file {
                /**
                 * @brief If set to true, the file will be generated
                 * for this entity.
                 */
                static const std::string generate;

                /**
                 * @brief Relative file name for the file.
                 */
                static const std::string file_name;

                /**
                 * @brief If true, the file will be included using
                 * angle-brackets in include statements. Quotes are
                 * used otherwise.
                 */
                static const std::string is_system;
            };

            /**
             * @brief Parameters associated with the implementation
             * file.
             */
            struct implementation_file {
                /**
                 * @brief If set to true, the file will be generated
                 * for this entity.
                 */
                static const std::string generate;

                /**
                 * @brief Relative file name for the file.
                 */
                static const std::string file_name;

                /**
                 * @brief If true, the file will be included using
                 * angle-brackets in include statements. Quotes are
                 * used otherwise.
                 */
                static const std::string is_system;
            };

            /**
             * @brief Parameters associated with the forward
             * declaration file.
             */
            struct forward_declarations_file {
                /**
                 * @brief If set to true, the file will be generated
                 * for this entity.
                 */
                static const std::string generate;

                /**
                 * @brief Relative file name for the file.
                 */
                static const std::string file_name;

                /**
                 * @brief If true, the file will be included using
                 * angle-brackets in include statements. Quotes are
                 * used otherwise.
                 */
                static const std::string is_system;
            };

            /**
             * @brief Parameters associated with the includers file.
             */
            struct includers_file {
                /**
                 * @brief If set to true, the file will be generated
                 * for this entity.
                 */
                static const std::string generate;

                /**
                 * @brief Relative file name for the file.
                 */
                static const std::string file_name;

                /**
                 * @brief If true, the file will be included using
                 * angle-brackets in include statements. Quotes are
                 * used otherwise.
                 */
                static const std::string is_system;
            };
        };

        /**
         * @brief Parameters specific to the @e hash facet.
         */
        struct hash {
            /**
             * @brief Parameters specific to standard library hashing.
             *
             * Note: we do not use @e std because it causes strange
             * compilation errors, most likely due to a clash with the
             * @e std namespace.
             */
            struct standard {
                /**
                 * @brief If set to disabled, the @e hash facet will not
                 * be generated for this type.
                 */
                static const std::string status;

                /**
                 * @brief Name of the folder to use for this facet.
                 */
                static const std::string directory_name;

                /**
                 * @brief Postfix for all file names in the facet.
                 */
                static const std::string postfix;

                /**
                 * @brief If set to true, an include file that includes
                 * all types in this facet will be generated.
                 */
                static const std::string generate_includers;

                /**
                 * @brief Parameters associated with the hash header file.
                 */
                struct header_file {
                    /**
                     * @brief If set to true, the file will be generated
                     * for this entity.
                     */
                    static const std::string generate;

                    /**
                     * @brief Relative file name for the file.
                     */
                    static const std::string file_name;

                    /**
                     * @brief If true, the file will be included using
                     * angle-brackets in include statements. Quotes are
                     * used otherwise.
                     */
                    static const std::string is_system;
                };

                /**
                 * @brief Parameters associated with the implementation
                 * file.
                 */
                struct implementation_file {
                    /**
                     * @brief If set to true, the file will be generated
                     * for this entity.
                     */
                    static const std::string generate;

                    /**
                     * @brief Relative file name for the file.
                     */
                    static const std::string file_name;

                    /**
                     * @brief If true, the file will be included using
                     * angle-brackets in include statements. Quotes are
                     * used otherwise.
                     */
                    static const std::string is_system;
                };

                /**
                 * @brief Parameters associated with the forward
                 * declaration file.
                 */
                struct forward_declarations_file {
                    /**
                     * @brief If set to true, the file will be generated
                     * for this entity.
                     */
                    static const std::string generate;

                    /**
                     * @brief Relative file name for the file.
                     */
                    static const std::string file_name;

                    /**
                     * @brief If true, the file will be included using
                     * angle-brackets in include statements. Quotes are
                     * used otherwise.
                     */
                    static const std::string is_system;
                };

                /**
                 * @brief Parameters associated with the includers file.
                 */
                struct includers_file {
                    /**
                     * @brief If set to true, the file will be generated
                     * for this entity.
                     */
                    static const std::string generate;

                    /**
                     * @brief Relative file name for the file.
                     */
                    static const std::string file_name;

                    /**
                     * @brief If true, the file will be included using
                     * angle-brackets in include statements. Quotes are
                     * used otherwise.
                     */
                    static const std::string is_system;
                };
            };
        };

        /**
         * @brief Parameters specific to the @e serialization facet.
         */
        struct serialization {
            /**
             * @brief Parameters specific to boost serialization.
             */
            struct boost {
                /**
                 * @brief If set to disabled, the serialization facet
                 * will not be generated for this type.
                 */
                static const std::string status;

                /**
                 * @brief Name of the folder to use for this facet.
                 */
                static const std::string directory_name;

                /**
                 * @brief Postfix for all file names in the facet.
                 */
                static const std::string postfix;

                /**
                 * @brief If true, serialization code will cater for
                 * boost XML serialization.
                 */
                static const std::string enable_xml_serialization;

                /**
                 * @brief Parameters associated with the boost
                 * serialization C++ header file.
                 */
                struct header_file {
                    /**
                     * @brief If set to true, the file will be generated
                     * for this entity.
                     */
                    static const std::string generate;

                    /**
                     * @brief Relative file name for the file.
                     */
                    static const std::string file_name;

                    /**
                     * @brief If true, the file will be included using
                     * angle-brackets in include statements. Quotes are
                     * used otherwise.
                     */
                    static const std::string is_system;
                };

                /**
                 * @brief Parameters associated with the implementation
                 * file.
                 */
                struct implementation_file {
                    /**
                     * @brief If set to true, the file will be generated
                     * for this entity.
                     */
                    static const std::string generate;

                    /**
                     * @brief Relative file name for the file.
                     */
                    static const std::string file_name;

                    /**
                     * @brief If true, the file will be included using
                     * angle-brackets in include statements. Quotes are
                     * used otherwise.
                     */
                    static const std::string is_system;
                };

                /**
                 * @brief Parameters associated with the forward
                 * declaration file.
                 */
                struct forward_declarations_file {
                    /**
                     * @brief If set to true, the file will be generated
                     * for this entity.
                     */
                    static const std::string generate;

                    /**
                     * @brief Relative file name for the file.
                     */
                    static const std::string file_name;

                    /**
                     * @brief If true, the file will be included using
                     * angle-brackets in include statements. Quotes are
                     * used otherwise.
                     */
                    static const std::string is_system;
                };

                /**
                 * @brief Parameters associated with the includers file.
                 */
                struct includers_file {
                    /**
                     * @brief If set to true, the file will be generated
                     * for this entity.
                     */
                    static const std::string generate;

                    /**
                     * @brief Relative file name for the file.
                     */
                    static const std::string file_name;

                    /**
                     * @brief If true, the file will be included using
                     * angle-brackets in include statements. Quotes are
                     * used otherwise.
                     */
                    static const std::string is_system;
                };
            };
        };

        /**
         * @brief Parameters specific to the io facet.
         */
        struct io {
            /**
             * @brief If set to disabled, the serialization facet
             * will not be generated for this type.
             */
            static const std::string status;

            /**
             * @brief Name of the folder to use for this facet.
             */
            static const std::string directory_name;

            /**
             * @brief Postfix for all file names in the facet.
             */
            static const std::string postfix;

            /**
             * @brief If true, IO operations will be in the class
             * itself rather than on a separate facet.
             */
            static const std::string enable_integrated_io;

            /**
             * @brief Parameters associated with the io C++ header file.
             */
            struct header_file {
                /**
                 * @brief If set to true, the file will be generated
                 * for this entity.
                 */
                static const std::string generate;

                /**
                 * @brief Relative file name for the file.
                 */
                static const std::string file_name;

                /**
                 * @brief If true, the file will be included using
                 * angle-brackets in include statements. Quotes are
                 * used otherwise.
                 */
                static const std::string is_system;
            };

            /**
             * @brief Parameters associated with the implementation
             * file.
             */
            struct implementation_file {
                /**
                 * @brief If set to true, the file will be generated
                 * for this entity.
                 */
                static const std::string generate;

                /**
                 * @brief Relative file name for the file.
                 */
                static const std::string file_name;

                /**
                 * @brief If true, the file will be included using
                 * angle-brackets in include statements. Quotes are
                 * used otherwise.
                 */
                static const std::string is_system;
            };

            /**
             * @brief Parameters associated with the forward
             * declaration file.
             */
            struct forward_declarations_file {
                /**
                 * @brief If set to true, the file will be generated
                 * for this entity.
                 */
                static const std::string generate;

                /**
                 * @brief Relative file name for the file.
                 */
                static const std::string file_name;

                /**
                 * @brief If true, the file will be included using
                 * angle-brackets in include statements. Quotes are
                 * used otherwise.
                 */
                static const std::string is_system;
            };

            /**
             * @brief Parameters associated with the includers file.
             */
            struct includers_file {
                /**
                 * @brief If set to true, the file will be generated
                 * for this entity.
                 */
                static const std::string generate;

                /**
                 * @brief Relative file name for the file.
                 */
                static const std::string file_name;

                /**
                 * @brief If true, the file will be included using
                 * angle-brackets in include statements. Quotes are
                 * used otherwise.
                 */
                static const std::string is_system;
            };
        };

        /**
         * @brief Parameters specific to the io facet.
         */
        struct test_data {
            /**
             * @brief If set to disabled, the @e test_data facet
             * will not be generated for this type.
             */
            static const std::string status;

            /**
             * @brief Name of the folder to use for this facet.
             */
            static const std::string directory_name;

            /**
             * @brief Postfix for all file names in the facet.
             */
            static const std::string postfix;

            /**
             * @brief Parameters associated with the @e test_data C++
             * header file.
             */
            struct header_file {
                /**
                 * @brief If set to true, the file will be generated
                 * for this entity.
                 */
                static const std::string generate;

                /**
                 * @brief Relative file name for the file.
                 */
                static const std::string file_name;

                /**
                 * @brief If true, the file will be included using
                 * angle-brackets in include statements. Quotes are
                 * used otherwise.
                 */
                static const std::string is_system;
            };

            /**
             * @brief Parameters associated with the implementation
             * file.
             */
            struct implementation_file {
                /**
                 * @brief If set to true, the file will be generated
                 * for this entity.
                 */
                static const std::string generate;

                /**
                 * @brief Relative file name for the file.
                 */
                static const std::string file_name;

                /**
                 * @brief If true, the file will be included using
                 * angle-brackets in include statements. Quotes are
                 * used otherwise.
                 */
                static const std::string is_system;
            };

            /**
             * @brief Parameters associated with the forward
             * declaration file.
             */
            struct forward_declarations_file {
                /**
                 * @brief If set to true, the file will be generated
                 * for this entity.
                 */
                static const std::string generate;

                /**
                 * @brief Relative file name for the file.
                 */
                static const std::string file_name;

                /**
                 * @brief If true, the file will be included using
                 * angle-brackets in include statements. Quotes are
                 * used otherwise.
                 */
                static const std::string is_system;
            };

            /**
             * @brief Parameters associated with the includers file.
             */
            struct includers_file {
                /**
                 * @brief If set to true, the file will be generated
                 * for this entity.
                 */
                static const std::string generate;

                /**
                 * @brief Relative file name for the file.
                 */
                static const std::string file_name;

                /**
                 * @brief If true, the file will be included using
                 * angle-brackets in include statements. Quotes are
                 * used otherwise.
                 */
                static const std::string is_system;
            };
        };

        /**
         * @brief Parameters specific to the @e odb facet.
         */
        struct odb {
            /**
             * @brief If set to disabled, the @e odb facet will not be
             * generated for this type.
             */
            static const std::string status;

            /**
             * @brief Name of the folder to use for this facet.
             */
            static const std::string directory_name;

            /**
             * @brief Postfix for all file names in the facet.
             */
            static const std::string postfix;

            /**
             * @brief Parameters associated with the io C++ header file.
             */
            struct header_file {
                /**
                 * @brief If set to true, the file will be generated
                 * for this entity.
                 */
                static const std::string generate;

                /**
                 * @brief Relative file name for the file.
                 */
                static const std::string file_name;

                /**
                 * @brief If true, the file will be included using
                 * angle-brackets in include statements. Quotes are
                 * used otherwise.
                 */
                static const std::string is_system;
            };

            /**
             * @brief Parameters associated with the includers file.
             */
            struct includers_file {
                /**
                 * @brief If set to true, the file will be generated
                 * for this entity.
                 */
                static const std::string generate;

                /**
                 * @brief Relative file name for the file.
                 */
                static const std::string file_name;

                /**
                 * @brief If true, the file will be included using
                 * angle-brackets in include statements. Quotes are
                 * used otherwise.
                 */
                static const std::string is_system;
            };
        };
    };
};

} }

#endif
