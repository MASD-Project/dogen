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
#ifndef DOGEN_KNIT_TYPES_OUTPUTTERS_FILE_OUTPUTTER_HPP
#define DOGEN_KNIT_TYPES_OUTPUTTERS_FILE_OUTPUTTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <map>
#include <string>
#include <boost/filesystem/path.hpp>
#include "dogen/knit/types/outputters/outputter.hpp"

namespace dogen {
namespace knit {
namespace outputters {

class file_outputter : public outputter {
public:
    file_outputter() = default;
    file_outputter(const file_outputter&) = default;
    file_outputter(file_outputter&&) = default;
    file_outputter& operator=(const file_outputter&) = default;

public:
    explicit file_outputter(bool force_write);
    virtual ~file_outputter() noexcept {}

private:
    /**
     * @brief Log output to standard output.
     */
    /**@{*/
    void log_not_writing_file(boost::filesystem::path path) const;
    void log_writing_file(boost::filesystem::path path) const;
    void log_wrote_file(boost::filesystem::path path) const;
    void log_created_directories(bool created,
        boost::filesystem::path directory) const;
    void log_no_content_changes() const;
    void log_content_changes() const;
    /**@}*/

private:
    bool content_changed(outputter::value_entry_type value) const;

    /**
     * @brief Outputs the pair passed in to a file.
     */
    void to_file(outputter::value_entry_type value) const;

public:
    /**
     * @brief Name of the outputter for logging purposes
     */
    static std::string outputter_name();

    /**
     * @brief Outputs all of the generated code to files.
     */
    void output(outputter::value_type value) const override;

private:
    const bool force_write_;
};

} } }

#endif
