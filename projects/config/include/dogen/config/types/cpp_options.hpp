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
#ifndef DOGEN_CONFIG_TYPES_CPP_OPTIONS_HPP
#define DOGEN_CONFIG_TYPES_CPP_OPTIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include <set>
#include <string>
#include "dogen/config/serialization/cpp_options_fwd_ser.hpp"
#include "dogen/config/types/cpp_facet_types.hpp"

namespace dogen {
namespace config {

/**
 * @brief Options for C++ code generation.
 */
class cpp_options final {
public:
    cpp_options(const cpp_options&) = default;
    ~cpp_options() = default;

public:
    cpp_options();

public:
    cpp_options(cpp_options&& rhs);

public:
    cpp_options(
        const bool split_project,
        const boost::filesystem::path& project_directory,
        const boost::filesystem::path& source_directory,
        const boost::filesystem::path& include_directory,
        const bool disable_backend,
        const bool disable_cmakelists,
        const std::set<dogen::config::cpp_facet_types>& enabled_facets,
        const std::string& header_extension,
        const std::string& source_extension,
        const bool disable_complete_constructor,
        const bool disable_facet_includers,
        const bool disable_facet_folders,
        const bool disable_unique_file_names,
        const std::string& domain_facet_folder,
        const std::string& hash_facet_folder,
        const std::string& io_facet_folder,
        const std::string& serialization_facet_folder,
        const std::string& test_data_facet_folder,
        const std::string& odb_facet_folder,
        const bool disable_xml_serialization,
        const bool use_integrated_io,
        const bool disable_eos_serialization);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const cpp_options& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, cpp_options& v, unsigned int version);

public:
    /**
     * @brief If true, project is split into source and include
     * directories, both configurable.
     *
     * If false, there is only a single top-level directory for the
     * entire project, containing as sub-directories both the source
     * and include directories.
     */
    /**@{*/
    bool split_project() const;
    void split_project(const bool v);
    /**@}*/

    /**
     * @brief Directory in which to place all of the C++ code.
     *
     * Implies project splitting is off.
     */
    /**@{*/
    const boost::filesystem::path& project_directory() const;
    boost::filesystem::path& project_directory();
    void project_directory(const boost::filesystem::path& v);
    void project_directory(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Directory in which to place the C++ implementation files.
     *
     * Can only be supplied if split project is set to true.
     */
    /**@{*/
    const boost::filesystem::path& source_directory() const;
    boost::filesystem::path& source_directory();
    void source_directory(const boost::filesystem::path& v);
    void source_directory(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Directory in which to place the C++ header files.
     *
     * Can only be supplied if split project is set to true.
     */
    /**@{*/
    const boost::filesystem::path& include_directory() const;
    boost::filesystem::path& include_directory();
    void include_directory(const boost::filesystem::path& v);
    void include_directory(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Disable the C++ backend entirely.
     */
    /**@{*/
    bool disable_backend() const;
    void disable_backend(const bool v);
    /**@}*/

    /**
     * @brief Do not generate CMakeLists.txt for C++ projects.
     */
    /**@{*/
    bool disable_cmakelists() const;
    void disable_cmakelists(const bool v);
    /**@}*/

    /**
     * @brief C++ facets for which to generate code.
     */
    /**@{*/
    const std::set<dogen::config::cpp_facet_types>& enabled_facets() const;
    std::set<dogen::config::cpp_facet_types>& enabled_facets();
    void enabled_facets(const std::set<dogen::config::cpp_facet_types>& v);
    void enabled_facets(const std::set<dogen::config::cpp_facet_types>&& v);
    /**@}*/

    /**
     * @brief Extension to use for C++ header files.
     */
    /**@{*/
    const std::string& header_extension() const;
    std::string& header_extension();
    void header_extension(const std::string& v);
    void header_extension(const std::string&& v);
    /**@}*/

    /**
     * @brief Extension to use for C++ source files.
     */
    /**@{*/
    const std::string& source_extension() const;
    std::string& source_extension();
    void source_extension(const std::string& v);
    void source_extension(const std::string&& v);
    /**@}*/

    /**
     * @brief Do not generate a constructor that takes as arguments as
     * member variables.
     */
    /**@{*/
    bool disable_complete_constructor() const;
    void disable_complete_constructor(const bool v);
    /**@}*/

    /**
     * @brief Do not create a global header file that includes all
     * header files in that facet.
     */
    /**@{*/
    bool disable_facet_includers() const;
    void disable_facet_includers(const bool v);
    /**@}*/

    /**
     * @brief Do not create individual folders for each facet.
     *
     * Instead put all the files in one folder.
     */
    /**@{*/
    bool disable_facet_folders() const;
    void disable_facet_folders(const bool v);
    /**@}*/

    /**
     * @brief Do not generate unique file names for each facet.
     *
     * All file names will use the domain object name.
     */
    /**@{*/
    bool disable_unique_file_names() const;
    void disable_unique_file_names(const bool v);
    /**@}*/

    /**
     * @brief Name of the folder to house domain object code.
     */
    /**@{*/
    const std::string& domain_facet_folder() const;
    std::string& domain_facet_folder();
    void domain_facet_folder(const std::string& v);
    void domain_facet_folder(const std::string&& v);
    /**@}*/

    /**
     * @brief Name of the folder to house hashing code.
     */
    /**@{*/
    const std::string& hash_facet_folder() const;
    std::string& hash_facet_folder();
    void hash_facet_folder(const std::string& v);
    void hash_facet_folder(const std::string&& v);
    /**@}*/

    /**
     * @brief Name of the folder to house IO (streaming) code.
     */
    /**@{*/
    const std::string& io_facet_folder() const;
    std::string& io_facet_folder();
    void io_facet_folder(const std::string& v);
    void io_facet_folder(const std::string&& v);
    /**@}*/

    /**
     * @brief Name of the folder to house boost serialisation code.
     */
    /**@{*/
    const std::string& serialization_facet_folder() const;
    std::string& serialization_facet_folder();
    void serialization_facet_folder(const std::string& v);
    void serialization_facet_folder(const std::string&& v);
    /**@}*/

    /**
     * @brief Name of the folder to house test data generators.
     */
    /**@{*/
    const std::string& test_data_facet_folder() const;
    std::string& test_data_facet_folder();
    void test_data_facet_folder(const std::string& v);
    void test_data_facet_folder(const std::string&& v);
    /**@}*/

    const std::string& odb_facet_folder() const;
    std::string& odb_facet_folder();
    void odb_facet_folder(const std::string& v);
    void odb_facet_folder(const std::string&& v);

    /**
     * @brief Do not use NVP macros in serialisation code.
     *
     * This has the effect of disabling support for boost XML archives.
     */
    /**@{*/
    bool disable_xml_serialization() const;
    void disable_xml_serialization(const bool v);
    /**@}*/

    /**
     * @brief Generate the streaming operators directly in the domain class.
     */
    /**@{*/
    bool use_integrated_io() const;
    void use_integrated_io(const bool v);
    /**@}*/

    /**
     * @brief If true, EOS portable serialisation will not be generated.
     */
    /**@{*/
    bool disable_eos_serialization() const;
    void disable_eos_serialization(const bool v);
    /**@}*/

public:
    bool operator==(const cpp_options& rhs) const;
    bool operator!=(const cpp_options& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(cpp_options& other) noexcept;
    cpp_options& operator=(cpp_options other);

private:
    bool split_project_;
    boost::filesystem::path project_directory_;
    boost::filesystem::path source_directory_;
    boost::filesystem::path include_directory_;
    bool disable_backend_;
    bool disable_cmakelists_;
    std::set<dogen::config::cpp_facet_types> enabled_facets_;
    std::string header_extension_;
    std::string source_extension_;
    bool disable_complete_constructor_;
    bool disable_facet_includers_;
    bool disable_facet_folders_;
    bool disable_unique_file_names_;
    std::string domain_facet_folder_;
    std::string hash_facet_folder_;
    std::string io_facet_folder_;
    std::string serialization_facet_folder_;
    std::string test_data_facet_folder_;
    std::string odb_facet_folder_;
    bool disable_xml_serialization_;
    bool use_integrated_io_;
    bool disable_eos_serialization_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::config::cpp_options& lhs,
    dogen::config::cpp_options& rhs) {
    lhs.swap(rhs);
}

}

#endif
