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
#include "dogen/formatters/types/indent_filter.hpp"
#include "dogen/cpp/types/formatters/formatting_assistant.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

formatting_assistant::formatting_assistant() {
    dogen::formatters::indent_filter::push(filtering_stream_, 4);
    filtering_stream_.push(stream_);
}

formatting_assistant::~formatting_assistant() noexcept { }

std::ostream& formatting_assistant::stream() {
    return filtering_stream_;
}

dogen::formatters::file formatting_assistant::make_file(
    const boost::filesystem::path& full_path, const bool overwrite) const {
    dogen::formatters::file r;
    r.content(stream_.str());
    r.path(full_path);
    r.overwrite(overwrite);
    return r;
}

} } }
