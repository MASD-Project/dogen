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
#ifndef DOGEN_STITCH_TYPES_TEXT_TEMPLATE_HPP
#define DOGEN_STITCH_TYPES_TEXT_TEMPLATE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen/stitch/types/properties.hpp"
#include "dogen/stitch/types/text_template_body.hpp"
#include "dogen/stitch/serialization/text_template_fwd_ser.hpp"

namespace dogen {
namespace stitch {

/**
 * @brief Domain representation of a stitch template.
 */
class text_template final {
public:
    text_template() = default;
    text_template(const text_template&) = default;
    ~text_template() = default;

public:
    text_template(text_template&& rhs);

public:
    text_template(
        const boost::filesystem::path& input_path,
        const boost::filesystem::path& output_path,
        const dogen::stitch::properties& properties,
        const std::unordered_map<std::string, std::string>& variables,
        const dogen::stitch::text_template_body& body);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::stitch::text_template& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::stitch::text_template& v, unsigned int version);

public:
    /**
     * @brief Path where the template was read out from, if any.
     */
    /**@{*/
    const boost::filesystem::path& input_path() const;
    boost::filesystem::path& input_path();
    void input_path(const boost::filesystem::path& v);
    void input_path(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Path where the template should be outputted to, if any.
     */
    /**@{*/
    const boost::filesystem::path& output_path() const;
    boost::filesystem::path& output_path();
    void output_path(const boost::filesystem::path& v);
    void output_path(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Properties of the template.
     */
    /**@{*/
    const dogen::stitch::properties& properties() const;
    dogen::stitch::properties& properties();
    void properties(const dogen::stitch::properties& v);
    void properties(const dogen::stitch::properties&& v);
    /**@}*/

    /**
     * @brief Any variables which may have been defined with the template.
     */
    /**@{*/
    const std::unordered_map<std::string, std::string>& variables() const;
    std::unordered_map<std::string, std::string>& variables();
    void variables(const std::unordered_map<std::string, std::string>& v);
    void variables(const std::unordered_map<std::string, std::string>&& v);
    /**@}*/

    /**
     * @brief Body of the text template.
     */
    /**@{*/
    const dogen::stitch::text_template_body& body() const;
    dogen::stitch::text_template_body& body();
    void body(const dogen::stitch::text_template_body& v);
    void body(const dogen::stitch::text_template_body&& v);
    /**@}*/

public:
    bool operator==(const text_template& rhs) const;
    bool operator!=(const text_template& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(text_template& other) noexcept;
    text_template& operator=(text_template other);

private:
    boost::filesystem::path input_path_;
    boost::filesystem::path output_path_;
    dogen::stitch::properties properties_;
    std::unordered_map<std::string, std::string> variables_;
    dogen::stitch::text_template_body body_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::stitch::text_template& lhs,
    dogen::stitch::text_template& rhs) {
    lhs.swap(rhs);
}

}

#endif
