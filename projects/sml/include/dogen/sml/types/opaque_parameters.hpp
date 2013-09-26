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
#ifndef DOGEN_OM_TYPES_OPAQUE_PARAMETERS_HPP
#define DOGEN_OM_TYPES_OPAQUE_PARAMETERS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen {
namespace om {

/**
 * @brief Constants for all keys that can be used in a opaque
 * parameter.
 */
struct opaque_parameters {
    /**
     * @brief Key used to denote an ODB pragma.
     *
     * It is expected to be repeated for a given object type; order is
     * kept as provided by user.
     */
    static const std::string odb_pragma;

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
     * @brief Valid values for Boolean types.
     */
    static const std::string bool_true;
    static const std::string bool_false;

    /**
     * @brief All parameters specific to the C++ language.
     */
    struct cpp {
        /**
         * @brief C++ specific parameters that apply only to types.
         */
        struct type {
            /**
             * @brief Family of the type.
             *
             * Used for debug printing the object, generating test
             * data, etc.
             */
            static const std::string family;
        };

        /**
         * @brief Parameters specific to the domain facet.
         */
        struct domain {
            /**
             * @brief If set to disabled, the domain facet will not be
             * generated for this type.
             */
            static const std::string status;

            /**
             * @brief If true, a manual default constructor is
             * generated, otherwise the compiler generated will be
             * used.
             */
            static const std::string requires_manual_default_constructor;

            /**
             * @brief If true, a manual move constructor is generated,
             * otherwise the compiler generated will be used.
             */
            static const std::string requires_manual_move_constructor;

            /**
             * @brief Parameters associated with the domain header file.
             */
            struct header {
                /**
                 * @brief Relative file name for the header file.
                 */
                static const std::string file_name;

                /**
                 * @brief If true, the header file will use
                 * angle-brackets in include statements. Quotes are
                 * used otherwise.
                 *
                 */
                static const std::string is_system;
            };
        };

        /**
         * @brief Parameters specific to the hash facet.
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
                 * @brief If set to disabled, the hash facet will not
                 * be generated for this type.
                 */
                static const std::string status;

                /**
                 * @brief Parameters associated with the hash header file.
                 */
                struct header {
                    /**
                     * @brief Relative file name for the header file.
                     */
                    static const std::string file_name;

                    /**
                     * @brief If true, the header file will use
                     * angle-brackets in include statements. Quotes are
                     * used otherwise.
                     *
                     */
                    static const std::string is_system;
                };
            };
        };

        /**
         * @brief Parameters specific to the serialization facet.
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
                 * @brief Parameters associated with the boost
                 * serialization C++ header file.
                 */
                struct header {
                    /**
                     * @brief Relative file name for the header file.
                     */
                    static const std::string file_name;

                    /**
                     * @brief If true, the header file will use
                     * angle-brackets in include statements. Quotes are
                     * used otherwise.
                     *
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
             * @brief Parameters associated with the io C++ header file.
             */
            struct header {
                /**
                 * @brief Relative file name for the header file.
                 */
                static const std::string file_name;

                /**
                 * @brief If true, the header file will use
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
