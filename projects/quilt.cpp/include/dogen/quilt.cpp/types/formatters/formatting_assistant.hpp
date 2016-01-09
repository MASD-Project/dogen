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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTERS_FORMATTING_ASSISTANT_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTERS_FORMATTING_ASSISTANT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <sstream>
#include <boost/iostreams/filtering_stream.hpp>
#include "dogen/formatters/types/file.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

class formatting_assistant {
protected:
    formatting_assistant();

public:
    virtual ~formatting_assistant() noexcept = 0;

public:
    /**
     * @brief Returns the stream that is currently being populated.
     */
    std::ostream& stream();

    /**
     * @brief Generates a file with the current contents of the
     * stream.
     */
    dogen::formatters::file make_file(const boost::filesystem::path& full_path,
        const bool overwrite = true) const;

private:
    std::ostringstream stream_;
    boost::iostreams::filtering_ostream filtering_stream_;
};

} } } }

#endif
