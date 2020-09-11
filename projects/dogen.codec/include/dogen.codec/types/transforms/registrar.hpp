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
#ifndef DOGEN_CODEC_TYPES_TRANSFORMS_REGISTRAR_HPP
#define DOGEN_CODEC_TYPES_TRANSFORMS_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <memory>
#include <unordered_map>
#include "dogen.codec/types/transforms/decoding_transform.hpp"
#include "dogen.codec/types/transforms/encoding_transform.hpp"

namespace dogen::codec::transforms {

class registrar final {
private:
    /**
     * @brief Sanity checks the supplied extension.
     */
    void validate_extension(const std::string& ext) const;

public:
    /**
     * @brief Ensures the registrar is ready to be used.
     */
    void validate();

    /**
     * @brief Returns a list of registered extensions for encoding.
     */
    std::list<std::string> registered_encoding_extensions() const;

    /**
     * @brief Returns a list of registered extensions for decoding.
     */
    std::list<std::string> registered_decoding_extensions() const;

    /**
     * @brief Registers an encoding transform.
     *
     * @pre Encoding transform must not yet be registered.
     * @pre Pointer must not be null.
     */
    void register_encoding_transform(
        std::shared_ptr<encoding_transform> t);

    /**
     * @brief Registers a decoding transform.
     *
     * @pre Encoding transform is not yet registered.
     * @pre Pointer must not be null.
     */
    void register_decoding_transform(std::shared_ptr<decoding_transform> t);

    /**
     * @brief Returns the encoding transform that handles the
     * supplied extension.
     *
     * @pre An encoding transform must have been registered for this
     * extension.
     */
    encoding_transform&
    encoding_transform_for_extension(const std::string& ext);

    /**
     * @brief Returns the decoding transform that handles the
     * supplied extension.
     *
     * @pre A decoding transform must have been registered for this
     * extension.
     */
    decoding_transform&
    decoding_transform_for_extension(const std::string& ext);

    /**
     * @brief Returns the encoding transform that handles the
     * supplied path.
     *
     * @pre An encoding transform must have been registered for this
     * extension.
     */
    encoding_transform&
    encoding_transform_for_path(const boost::filesystem::path& p);

    /**
     * @brief Returns the decoding transform that handles the
     * supplied path.
     *
     * @pre An decoding transform must have been registered for this
     * extension.
     */
    decoding_transform&
    decoding_transform_for_path(const boost::filesystem::path& p);

private:
    std::unordered_map<std::string, std::shared_ptr<encoding_transform>>
    encoding_transforms_;
    std::unordered_map<std::string, std::shared_ptr<decoding_transform>>
    decoding_transforms_;
};

}

#endif
