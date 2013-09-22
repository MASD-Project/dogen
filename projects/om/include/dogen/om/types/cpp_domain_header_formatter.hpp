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
#ifndef DOGEN_OM_TYPES_CPP_DOMAIN_HEADER_FORMATTER_HPP
#define DOGEN_OM_TYPES_CPP_DOMAIN_HEADER_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <ostream>
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/types/type_visitor.hpp"
#include "dogen/om/types/comment_formatter.hpp"
#include "dogen/om/types/type_formatter_interface.hpp"

namespace dogen {
namespace om {

class cpp_domain_header_formatter : public type_formatter_interface,
                                    private sml::type_visitor {
public:
    cpp_domain_header_formatter(const cpp_domain_header_formatter&) = default;
    cpp_domain_header_formatter(cpp_domain_header_formatter&&) = default;

public:
    cpp_domain_header_formatter();
    virtual ~cpp_domain_header_formatter() noexcept { }

private:
    using sml::type_visitor::visit;
    void visit(const dogen::sml::enumeration& e) const override;

private:
    std::list<std::string> namespaces(const sml::qname& qn) const;

public:
    void format(std::ostream& s, const sml::type& t, const licence& l,
        const modeline& m, const std::string& marker,
        const sml::model& model) const override;

private:
    mutable std::ostream* stream_ = nullptr;
    comment_formatter doxygen_next_;
    comment_formatter doxygen_previous_;
};

} }

#endif
