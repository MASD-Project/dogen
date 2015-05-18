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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_FORMATTABLES_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_FORMATTABLES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace cpp {

/**
 * @brief Formattables contains all types required by the formatters
 * and those used to generate them.
 *
 * @section cpp_1 Inclusion Directive and Inclusion Dependency
 *
 * In this module we use two similar terms with very different meanings:
 * inclusion directive and inclusion dependency.
 *
 * An inclusion directive is a string with delimiters but without the
 * #include pragma. For example "a/b/c,hpp" and <a/b/c.hpp> are
 * inclusion directives; note that the quotes and angle brackets are part
 * of the directive. There should be an inclusion directive associated
 * with every pair (qname, formatter name). The inclusion directive
 * repository contains the complete set of inclusion directives - the
 * inclusion directives universe if you'd like.
 *
 * Inclusion dependencies are a set of inclusion directives.  They are
 * also associated with a pair (qname, formatter).  The inclusion
 * dependences for each formatter are created by the inclusion
 * dependencies providers. Each formatter is expected to supply one of
 * one of these. It uses the inclusion directives available n the
 * repository to assemble the inclusion dependencies that the formatter
 * needs in order to generate a compilable C++ file.
 *
 */
namespace formattables {
}

} }

#endif
