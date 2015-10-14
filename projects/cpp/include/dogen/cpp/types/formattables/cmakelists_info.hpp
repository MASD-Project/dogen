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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_CMAKELISTS_INFO_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_CMAKELISTS_INFO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen/formatters/types/general_settings.hpp"
#include "dogen/cpp/types/formattables/formattable.hpp"
#include "dogen/cpp/serialization/formattables/cmakelists_info_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Represents a CMakeLists.txt top-level makefile.
 */
class cmakelists_info final : public dogen::cpp::formattables::formattable {
public:
    cmakelists_info(const cmakelists_info&) = default;

public:
    cmakelists_info();

    virtual ~cmakelists_info() noexcept { }

public:
    cmakelists_info(cmakelists_info&& rhs);

public:
    cmakelists_info(
        const std::string& identity,
        const dogen::cpp::formattables::origin_types origin_type,
        const boost::filesystem::path& file_path,
        const std::string& model_name,
        const std::string& product_name,
        const std::string& file_name,
        const boost::filesystem::path& source_file_path,
        const boost::filesystem::path& include_file_path,
        const boost::optional<dogen::formatters::general_settings>& general_settings,
        const std::string& odb_folder,
        const bool odb_enabled);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const cmakelists_info& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, cmakelists_info& v, unsigned int version);

public:
    virtual void accept(const formattable_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(formattable_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(const formattable_visitor& v) override {
        v.visit(*this);
    }

    virtual void accept(formattable_visitor& v) override {
        v.visit(*this);
    }

public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief Location of the CMake file.
     */
    /**@{*/
    const boost::filesystem::path& file_path() const;
    boost::filesystem::path& file_path();
    void file_path(const boost::filesystem::path& v);
    void file_path(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Name of the model for which the make file is being generated.
     */
    /**@{*/
    const std::string& model_name() const;
    std::string& model_name();
    void model_name(const std::string& v);
    void model_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Name of the product which contains this make file.
     */
    /**@{*/
    const std::string& product_name() const;
    std::string& product_name();
    void product_name(const std::string& v);
    void product_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Name for the CMake file.
     */
    /**@{*/
    const std::string& file_name() const;
    std::string& file_name();
    void file_name(const std::string& v);
    void file_name(const std::string&& v);
    /**@}*/

    const boost::filesystem::path& source_file_path() const;
    boost::filesystem::path& source_file_path();
    void source_file_path(const boost::filesystem::path& v);
    void source_file_path(const boost::filesystem::path&& v);

    const boost::filesystem::path& include_file_path() const;
    boost::filesystem::path& include_file_path();
    void include_file_path(const boost::filesystem::path& v);
    void include_file_path(const boost::filesystem::path&& v);

    const boost::optional<dogen::formatters::general_settings>& general_settings() const;
    boost::optional<dogen::formatters::general_settings>& general_settings();
    void general_settings(const boost::optional<dogen::formatters::general_settings>& v);
    void general_settings(const boost::optional<dogen::formatters::general_settings>&& v);

    const std::string& odb_folder() const;
    std::string& odb_folder();
    void odb_folder(const std::string& v);
    void odb_folder(const std::string&& v);

    bool odb_enabled() const;
    void odb_enabled(const bool v);

public:
    bool operator==(const cmakelists_info& rhs) const;
    bool operator!=(const cmakelists_info& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::cpp::formattables::formattable& other) const override;

public:
    void swap(cmakelists_info& other) noexcept;
    cmakelists_info& operator=(cmakelists_info other);

private:
    boost::filesystem::path file_path_;
    std::string model_name_;
    std::string product_name_;
    std::string file_name_;
    boost::filesystem::path source_file_path_;
    boost::filesystem::path include_file_path_;
    boost::optional<dogen::formatters::general_settings> general_settings_;
    std::string odb_folder_;
    bool odb_enabled_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::formattables::cmakelists_info& lhs,
    dogen::cpp::formattables::cmakelists_info& rhs) {
    lhs.swap(rhs);
}

}

#endif
