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
#ifndef DOGEN_TEMPLATING_TYPES_STITCH_TEXT_TEMPLATE_HPP
#define DOGEN_TEMPLATING_TYPES_STITCH_TEXT_TEMPLATE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen.templating/types/stitch/properties.hpp"
#include "dogen.templating/types/stitch/text_template_body.hpp"

namespace dogen::templating::stitch {

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
        const dogen::templating::stitch::properties& properties,
        const std::unordered_map<std::string, std::string>& variables,
        const dogen::templating::stitch::text_template_body& body);

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
    const dogen::templating::stitch::properties& properties() const;
    dogen::templating::stitch::properties& properties();
    void properties(const dogen::templating::stitch::properties& v);
    void properties(const dogen::templating::stitch::properties&& v);
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
    const dogen::templating::stitch::text_template_body& body() const;
    dogen::templating::stitch::text_template_body& body();
    void body(const dogen::templating::stitch::text_template_body& v);
    void body(const dogen::templating::stitch::text_template_body&& v);
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
    dogen::templating::stitch::properties properties_;
    std::unordered_map<std::string, std::string> variables_;
    dogen::templating::stitch::text_template_body body_;
};

}

namespace std {

template<>
inline void swap(
    dogen::templating::stitch::text_template& lhs,
    dogen::templating::stitch::text_template& rhs) {
    lhs.swap(rhs);
}

}

#endif
