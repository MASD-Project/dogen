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
#ifndef MASD_DOGEN_EXTRACTION_TYPES_META_MODEL_MODEL_HPP
#define MASD_DOGEN_EXTRACTION_TYPES_META_MODEL_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "masd.dogen.extraction/types/meta_model/artefact.hpp"
#include "masd.dogen.extraction/serialization/meta_model/model_fwd_ser.hpp"

namespace masd::dogen::extraction::meta_model {

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
        const std::list<masd::dogen::extraction::meta_model::artefact>& artefacts,
        const std::list<boost::filesystem::path>& managed_directories,
        const bool force_write,
        const bool delete_extra_files,
        const std::vector<std::string>& ignore_files_matching_regex,
        const boost::filesystem::path& cpp_headers_output_directory);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const masd::dogen::extraction::meta_model::model& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, masd::dogen::extraction::meta_model::model& v, unsigned int version);

public:
    const std::list<masd::dogen::extraction::meta_model::artefact>& artefacts() const;
    std::list<masd::dogen::extraction::meta_model::artefact>& artefacts();
    void artefacts(const std::list<masd::dogen::extraction::meta_model::artefact>& v);
    void artefacts(const std::list<masd::dogen::extraction::meta_model::artefact>&& v);

    const std::list<boost::filesystem::path>& managed_directories() const;
    std::list<boost::filesystem::path>& managed_directories();
    void managed_directories(const std::list<boost::filesystem::path>& v);
    void managed_directories(const std::list<boost::filesystem::path>&& v);

    /**
     * @brief Always write files, even when there are no differences.
     */
    /**@{*/
    bool force_write() const;
    void force_write(const bool v);
    /**@}*/

    /**
     * @brief If true, deletes any files that are not known to Dogen .
     */
    /**@{*/
    bool delete_extra_files() const;
    void delete_extra_files(const bool v);
    /**@}*/

    /**
     * @brief Files matching the supplied regular expressions will be ignored by Dogen.
     *
     * Only applicable when deleting extra files.
     */
    /**@{*/
    const std::vector<std::string>& ignore_files_matching_regex() const;
    std::vector<std::string>& ignore_files_matching_regex();
    void ignore_files_matching_regex(const std::vector<std::string>& v);
    void ignore_files_matching_regex(const std::vector<std::string>&& v);
    /**@}*/

    /**
     * @brief Directory in which to place C++ header files. Must be a relative path.
     */
    /**@{*/
    const boost::filesystem::path& cpp_headers_output_directory() const;
    boost::filesystem::path& cpp_headers_output_directory();
    void cpp_headers_output_directory(const boost::filesystem::path& v);
    void cpp_headers_output_directory(const boost::filesystem::path&& v);
    /**@}*/

public:
    bool operator==(const model& rhs) const;
    bool operator!=(const model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(model& other) noexcept;
    model& operator=(model other);

private:
    std::list<masd::dogen::extraction::meta_model::artefact> artefacts_;
    std::list<boost::filesystem::path> managed_directories_;
    bool force_write_;
    bool delete_extra_files_;
    std::vector<std::string> ignore_files_matching_regex_;
    boost::filesystem::path cpp_headers_output_directory_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::extraction::meta_model::model& lhs,
    masd::dogen::extraction::meta_model::model& rhs) {
    lhs.swap(rhs);
}

}

#endif
