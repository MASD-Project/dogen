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
#ifndef DOGEN_OM_TYPES_CPP_FILE_HPP
#define DOGEN_OM_TYPES_CPP_FILE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <iosfwd>
#include <list>
#include "dogen/om/serialization/cpp_file_fwd_ser.hpp"
#include "dogen/om/types/cpp_feature_fwd.hpp"
#include "dogen/om/types/doxygen_command.hpp"
#include "dogen/om/types/text_file.hpp"

namespace dogen {
namespace om {

class cpp_file final : public dogen::om::text_file {
public:
    cpp_file() = default;
    cpp_file(const cpp_file&) = default;
    cpp_file(cpp_file&&) = default;

    virtual ~cpp_file() noexcept { }

public:
    cpp_file(
        const boost::filesystem::path& full_path,
        const boost::filesystem::path& relative_path,
        const dogen::om::modeline& modeline,
        const boost::optional<dogen::om::code_generation_marker>& marker,
        const dogen::om::licence& licence,
        const std::list<dogen::om::doxygen_command>& commands,
        const std::list<boost::shared_ptr<dogen::om::cpp_feature> >& features);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const cpp_file& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, cpp_file& v, unsigned int version);

public:
    void to_stream(std::ostream& s) const override;

public:
    const std::list<dogen::om::doxygen_command>& commands() const;
    std::list<dogen::om::doxygen_command>& commands();
    void commands(const std::list<dogen::om::doxygen_command>& v);
    void commands(const std::list<dogen::om::doxygen_command>&& v);

    const std::list<boost::shared_ptr<dogen::om::cpp_feature> >& features() const;
    std::list<boost::shared_ptr<dogen::om::cpp_feature> >& features();
    void features(const std::list<boost::shared_ptr<dogen::om::cpp_feature> >& v);
    void features(const std::list<boost::shared_ptr<dogen::om::cpp_feature> >&& v);

public:
    bool operator==(const cpp_file& rhs) const;
    bool operator!=(const cpp_file& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::om::text_file& other) const override;

public:
    void swap(cpp_file& other) noexcept;
    cpp_file& operator=(cpp_file other);

private:
    std::list<dogen::om::doxygen_command> commands_;
    std::list<boost::shared_ptr<dogen::om::cpp_feature> > features_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::om::cpp_file& lhs,
    dogen::om::cpp_file& rhs) {
    lhs.swap(rhs);
}

}

#endif
