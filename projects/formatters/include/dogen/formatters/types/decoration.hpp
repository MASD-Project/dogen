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
#ifndef DOGEN_FORMATTERS_TYPES_DECORATION_HPP
#define DOGEN_FORMATTERS_TYPES_DECORATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen/formatters/types/licence.hpp"
#include "dogen/formatters/types/modeline.hpp"
#include "dogen/formatters/serialization/decoration_fwd_ser.hpp"

namespace dogen {
namespace formatters {

/**
 * @brief Aggregates all the file meta-data in one place.
 */
class decoration final {
public:
    decoration() = default;
    decoration(const decoration&) = default;
    ~decoration() = default;

public:
    decoration(decoration&& rhs);

public:
    decoration(
        const boost::optional<dogen::formatters::modeline>& modeline,
        const boost::optional<dogen::formatters::licence>& licence,
        const std::string& code_generation_marker);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::formatters::decoration& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::formatters::decoration& v, unsigned int version);

public:
    /**
     * @brief Modeline to use in this file, if any.
     */
    /**@{*/
    const boost::optional<dogen::formatters::modeline>& modeline() const;
    boost::optional<dogen::formatters::modeline>& modeline();
    void modeline(const boost::optional<dogen::formatters::modeline>& v);
    void modeline(const boost::optional<dogen::formatters::modeline>&& v);
    /**@}*/

    /**
     * @brief Licence to use in this file, if any.
     */
    /**@{*/
    const boost::optional<dogen::formatters::licence>& licence() const;
    boost::optional<dogen::formatters::licence>& licence();
    void licence(const boost::optional<dogen::formatters::licence>& v);
    void licence(const boost::optional<dogen::formatters::licence>&& v);
    /**@}*/

    /**
     * @brief Code generation marker to use in this file.
     */
    /**@{*/
    const std::string& code_generation_marker() const;
    std::string& code_generation_marker();
    void code_generation_marker(const std::string& v);
    void code_generation_marker(const std::string&& v);
    /**@}*/

public:
    bool operator==(const decoration& rhs) const;
    bool operator!=(const decoration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(decoration& other) noexcept;
    decoration& operator=(decoration other);

private:
    boost::optional<dogen::formatters::modeline> modeline_;
    boost::optional<dogen::formatters::licence> licence_;
    std::string code_generation_marker_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::formatters::decoration& lhs,
    dogen::formatters::decoration& rhs) {
    lhs.swap(rhs);
}

}

#endif
