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
#ifndef DOGEN_CODEC_DIA_TYPES_PROCESSED_COMMENT_FACTORY_HPP
#define DOGEN_CODEC_DIA_TYPES_PROCESSED_COMMENT_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include "dogen.codec.dia/types/processed_comment.hpp"

namespace dogen::codec::dia {

/**
 * @brief Processes comments in dia diagrams.
 *
 * Comments can be stored in class objects, member functions, note
 * objects, etc.
 *
 * Any line starting with the well defined marker @e #DOGEN - known as
 * the instruction marker - will be interpreted as carrying an
 * instruction in a key-value pair form, where the key and the
 * value are separated by the assignment operator @e =.
 */
class processed_comment_factory {
public:
    /**
     * @brief Parses a string carrying the comments in the dia object.
     *
     * Note that the @e # markers used by dia are expected to have
     * already been removed.
     *
     * @pre lines starting with the instruction marker must follow the
     * defined syntax or else a parsing_error is thrown.
     */
    static processed_comment make(const std::string& c);
};

}

#endif
