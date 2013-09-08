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
#ifndef DOGEN_OM_TYPES_ODB_OPTIONS_FILE_HPP
#define DOGEN_OM_TYPES_ODB_OPTIONS_FILE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <iosfwd>
#include <list>
#include "dogen/om/serialization/odb_options_file_fwd_ser.hpp"
#include "dogen/om/types/odb_option_fwd.hpp"
#include "dogen/om/types/text_file.hpp"

namespace dogen {
namespace om {

/**
 * @brief File containing all of the command line options for ODB.
 */
class odb_options_file final : public dogen::om::text_file {
public:
    odb_options_file() = default;
    odb_options_file(const odb_options_file&) = default;
    odb_options_file(odb_options_file&&) = default;

    virtual ~odb_options_file() noexcept { }

public:
    odb_options_file(
        const boost::filesystem::path& full_path,
        const boost::filesystem::path& relative_path,
        const dogen::om::modeline& modeline,
        const boost::optional<dogen::om::code_generation_marker>& marker,
        const dogen::om::licence& licence,
        const std::list<boost::shared_ptr<dogen::om::odb_option> >& features);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const odb_options_file& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, odb_options_file& v, unsigned int version);

public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief ODB command line obtions.
     */
    /**@{*/
    const std::list<boost::shared_ptr<dogen::om::odb_option> >& features() const;
    std::list<boost::shared_ptr<dogen::om::odb_option> >& features();
    void features(const std::list<boost::shared_ptr<dogen::om::odb_option> >& v);
    void features(const std::list<boost::shared_ptr<dogen::om::odb_option> >&& v);
    /**@}*/

public:
    bool operator==(const odb_options_file& rhs) const;
    bool operator!=(const odb_options_file& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::om::text_file& other) const override;

public:
    void swap(odb_options_file& other) noexcept;
    odb_options_file& operator=(odb_options_file other);

private:
    std::list<boost::shared_ptr<dogen::om::odb_option> > features_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::om::odb_options_file& lhs,
    dogen::om::odb_options_file& rhs) {
    lhs.swap(rhs);
}

}

#endif
