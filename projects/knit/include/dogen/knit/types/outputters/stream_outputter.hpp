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
#ifndef DOGEN_KNIT_TYPES_OUTPUTTERS_STREAM_OUTPUTTER_HPP
#define DOGEN_KNIT_TYPES_OUTPUTTERS_STREAM_OUTPUTTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <map>
#include <string>
#include <ostream>
#include <boost/filesystem/path.hpp>
#include "dogen/knit/types/outputters/outputter.hpp"

namespace dogen {
namespace knit {
namespace outputters {

class stream_outputter : public outputter {
public:
    stream_outputter() = default;
    stream_outputter(const stream_outputter&) = default;
    stream_outputter(stream_outputter&&) = default;
    stream_outputter& operator=(const stream_outputter&) = default;

public:
    stream_outputter(std::ostream& stream);
    virtual ~stream_outputter() noexcept {}

public:
    /**
     * @brief Name of the outputter for logging purposes
     */
    static std::string outputter_name();

    void output(
        const std::forward_list<formatters::file>& files) const override;

private:
    std::ostream& stream_;
};

} } }

#endif
