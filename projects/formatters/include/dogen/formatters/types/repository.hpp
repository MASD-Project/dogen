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
#ifndef DOGEN_FORMATTERS_TYPES_REPOSITORY_HPP
#define DOGEN_FORMATTERS_TYPES_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <boost/shared_ptr.hpp>
#include "dogen/formatters/types/transformer_interface_fwd.hpp"
#include "dogen/formatters/types/file_formatter_interface_fwd.hpp"

namespace dogen {
namespace formatters {

/**
 * @brief Repository of instances of formatters and transformers.
 */
class repository {
public:
    repository() = default;
    repository(const repository&) = default;
    repository(repository&&) = default;
    ~repository() noexcept = default;

public:
    typedef std::list<boost::shared_ptr<file_formatter_interface> >
    file_formatters_type;

    typedef std::list<boost::shared_ptr<transformer_interface> >
    transformers_type;

public:
    /**
     * @brief Clears all containers in the repository.
     */
    void clear();

    /**
     * @brief Returns true if all containers are empty.
     */
    bool empty() const;

public:
    /**
     * @brief Collection of file formatters.
     */
    /**@{*/
    const file_formatters_type& file_formatters() const;
    file_formatters_type& file_formatters();
    void file_formatters(const file_formatters_type& v);
    void file_formatters(const file_formatters_type&& v);
    /**@}*/

    /**
     * @brief Collection of transformers.
     */
    /**@{*/
    const transformers_type& transformers() const;
    transformers_type& transformers();
    void transformers(const transformers_type& v);
    void transformers(const transformers_type&& v);
    /**@}*/

private:
    file_formatters_type file_formatters_;
    transformers_type transformers_;
};

} }

#endif
