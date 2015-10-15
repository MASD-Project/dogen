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
#ifndef DOGEN_YARN_TYPES_PROPERTIES_EXPANDER_HPP
#define DOGEN_YARN_TYPES_PROPERTIES_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

<<<<<<< 24090da86c0fe4a597dfa9c7b5e3ed377e4b57f4:projects/tack/include/dogen/tack/types/properties_expander.hpp
#include <string>
#include "dogen/tack/types/identifier_parser.hpp"
#include "dogen/tack/types/nested_name.hpp"
#include "dogen/tack/types/model.hpp"
=======
#include "dogen/yarn/types/identifier_parser.hpp"
#include "dogen/yarn/types/model.hpp"
>>>>>>> rename tack to yarn:projects/yarn/include/dogen/yarn/types/properties_expander.hpp

namespace dogen {
namespace yarn {

class properties_expander {
private:
    std::unordered_set<std::string>
    obtain_top_level_module_names(const model& m) const;

    identifier_parser make_identifier_parser(const model& m) const;

    nested_name make_nested_name(const identifier_parser& ip,
        const std::string& s) const;

public:
    void expand(model& m) const;
};

} }

#endif
