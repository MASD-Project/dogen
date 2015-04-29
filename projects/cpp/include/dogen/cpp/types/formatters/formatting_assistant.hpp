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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_FORMATTING_ASSISTANT_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_FORMATTING_ASSISTANT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <sstream>
#include "dogen/dynamic/schema/types/ownership_hierarchy.hpp"
#include "dogen/formatters/types/file.hpp"
#include "dogen/formatters/types/indent_filter.hpp"
#include "dogen/formatters/types/cpp/scoped_namespace_formatter.hpp"
#include "dogen/formatters/types/cpp/scoped_boilerplate_formatter.hpp"
#include "dogen/cpp/types/formatters/file_types.hpp"
#include "dogen/cpp/types/settings/formatter_settings.hpp"
#include "dogen/cpp/types/formattables/entity.hpp"
#include "dogen/cpp/types/formattables/class_info.hpp"
#include "dogen/cpp/types/formattables/property_info.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

/**
 * @brief Provides a number of utilities to formatters.
 */
class formatting_assistant {
public:
    /**
     * @brief Returns the text to use for a given class for the @code
     * final keyword. If non-empty, includes a trailing space.
     */
    static std::string
    make_final_keyword_text(const formattables::class_info& c);

    /**
     * @brief Returns the by-ref to use given the property.
     */
    static std::string make_by_ref_text(const formattables::property_info& p);

    /**
     * @brief Returns nothing, a comma or end brackets with semi-colon.
     */
    static std::string
    make_parameter_separator_text(const unsigned int number_of_parameters,
        const unsigned int parameter_position);

public:
    formatting_assistant(const formattables::entity& e,
        const dynamic::schema::ownership_hierarchy& oh,
        const formatters::file_types ft);

private:
    /**
     * @brief Obtains the formatter settings for the formatter as
     * given by the ownership hierarchy.
     */
    settings::formatter_settings
    formatter_settings(const std::string& formatter_name) const;

public:
    /**
     * @brief Returns true if the formatter is enabled, false
     * otherwise.
     */
    bool is_formatter_enabled(const std::string& formatter_name) const;

public:
    /**
     * @brief Ensures all expected settings are available and set to
     * valid values.
     */
    void validate() const;

    /**
     * @brief Returns a scoped boilerplate formatter.
     */
    dogen::formatters::cpp::scoped_boilerplate_formatter
    make_scoped_boilerplate_formatter();

    /**
     * @brief Returns a scoped namespace formatter.
     */
    dogen::formatters::cpp::scoped_namespace_formatter
    make_scoped_namespace_formatter();

    /**
     * @brief Returns the stream that is currently being populated.
     */
    std::ostream& stream();

    /**
     * @brief Generates a file with the current contents of the
     * stream.
     */
    dogen::formatters::file make_file() const;

private:
    const formattables::entity& entity_;
    const dynamic::schema::ownership_hierarchy& ownership_hierarchy_;
    const settings::formatter_settings formatter_settings_;
    const formatters::file_types file_type_;
    std::ostringstream stream_;
    boost::iostreams::filtering_ostream filtering_stream_;

};

} } }

#endif
