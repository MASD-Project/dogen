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
#ifndef DOGEN_FORMATTERS_TYPES_FILESYSTEM_WRITER_HPP
#define DOGEN_FORMATTERS_TYPES_FILESYSTEM_WRITER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>
#include "dogen/formatters/types/file_writer_interface.hpp"

namespace dogen {
namespace formatters {

/**
 * @brief Writes files to the filesystem.
 */
class filesystem_writer : public file_writer_interface {
public:
    explicit filesystem_writer(const bool force_write);

private:
    /**
     * @brief Returns true if the file needs to be written to the
     * file system, false otherwise.
     */
    bool requires_writing(const artefact& f) const;

    /**
     * @brief Creates directories to house the file, if they do not
     * yet exist.
     */
    void create_directories(const boost::filesystem::path& file_path) const;

    /**
     * @brief Handle the special case of writing empty files.
     *
     * FIXME: this is a hack for now.
     */
    void write_empty_file(const formatters::artefact& f) const;

    /**
     * @brief Writes the file.
     */
    void write(const formatters::artefact& f) const;

public:
    void write(const std::forward_list<artefact>& files) const override;

private:
    const bool force_write_;
};

} }

#endif
