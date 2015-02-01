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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_PROJECT_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_PROJECT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include <list>
#include "dogen/cpp/serialization/formattables/project_fwd_ser.hpp"
#include "dogen/cpp/types/formattables/cmakelists_info.hpp"
#include "dogen/cpp/types/formattables/entity_fwd.hpp"
#include "dogen/cpp/types/formattables/file_info.hpp"
#include "dogen/cpp/types/formattables/odb_options_info.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Represents a project composed of makefiles and C++ source code.
 */
class project final {
public:
    project() = default;
    project(const project&) = default;
    ~project() = default;

public:
    project(project&& rhs);

public:
    project(
        const std::list<dogen::cpp::formattables::file_info>& files,
        const dogen::cpp::formattables::odb_options_info& odb_options,
        const dogen::cpp::formattables::cmakelists_info& src_cmakelists,
        const boost::optional<dogen::cpp::formattables::cmakelists_info>& include_cmakelists,
        const std::list<boost::shared_ptr<dogen::cpp::formattables::entity> >& entities);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const project& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, project& v, unsigned int version);

public:
    /**
     * @brief All C++ files, interfaces and implementation.
     */
    /**@{*/
    const std::list<dogen::cpp::formattables::file_info>& files() const;
    std::list<dogen::cpp::formattables::file_info>& files();
    void files(const std::list<dogen::cpp::formattables::file_info>& v);
    void files(const std::list<dogen::cpp::formattables::file_info>&& v);
    /**@}*/

    /**
     * @brief The ODB options file.
     */
    /**@{*/
    const dogen::cpp::formattables::odb_options_info& odb_options() const;
    dogen::cpp::formattables::odb_options_info& odb_options();
    void odb_options(const dogen::cpp::formattables::odb_options_info& v);
    void odb_options(const dogen::cpp::formattables::odb_options_info&& v);
    /**@}*/

    /**
     * @brief The CMake makefile for the source directory.
     */
    /**@{*/
    const dogen::cpp::formattables::cmakelists_info& src_cmakelists() const;
    dogen::cpp::formattables::cmakelists_info& src_cmakelists();
    void src_cmakelists(const dogen::cpp::formattables::cmakelists_info& v);
    void src_cmakelists(const dogen::cpp::formattables::cmakelists_info&& v);
    /**@}*/

    /**
     * @brief The CMake makefile for the include directory.
     */
    /**@{*/
    const boost::optional<dogen::cpp::formattables::cmakelists_info>& include_cmakelists() const;
    boost::optional<dogen::cpp::formattables::cmakelists_info>& include_cmakelists();
    void include_cmakelists(const boost::optional<dogen::cpp::formattables::cmakelists_info>& v);
    void include_cmakelists(const boost::optional<dogen::cpp::formattables::cmakelists_info>&& v);
    /**@}*/

    /**
     * @brief All entities in this project.
     */
    /**@{*/
    const std::list<boost::shared_ptr<dogen::cpp::formattables::entity> >& entities() const;
    std::list<boost::shared_ptr<dogen::cpp::formattables::entity> >& entities();
    void entities(const std::list<boost::shared_ptr<dogen::cpp::formattables::entity> >& v);
    void entities(const std::list<boost::shared_ptr<dogen::cpp::formattables::entity> >&& v);
    /**@}*/

public:
    bool operator==(const project& rhs) const;
    bool operator!=(const project& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(project& other) noexcept;
    project& operator=(project other);

private:
    std::list<dogen::cpp::formattables::file_info> files_;
    dogen::cpp::formattables::odb_options_info odb_options_;
    dogen::cpp::formattables::cmakelists_info src_cmakelists_;
    boost::optional<dogen::cpp::formattables::cmakelists_info> include_cmakelists_;
    std::list<boost::shared_ptr<dogen::cpp::formattables::entity> > entities_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::formattables::project& lhs,
    dogen::cpp::formattables::project& rhs) {
    lhs.swap(rhs);
}

}

#endif
