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
#ifndef DOGEN_CPP_TYPES_CPP_HPP
#define DOGEN_CPP_TYPES_CPP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {

/**
 * @brief CPP is the C++ model.
 *
 * CPP is responsible for converting a generic SML representation
 * into compilable C++ code, according to a set of well-defined
 * conventions.
 *
 * <b>Info postfix</b>
 *
 * The types in the C++ meta-model should not have any prefixes or post-fixes
 * since they naturally belong to the CPP model. However, because names like
 * class and namespace clash with keywords, and to maintain consistency -
 * perhaps foolishly - it was decided to use the postfix @e info on all types
 * which are part of the meta-model. Info was chosen very randomly, but it is
 * used by @e type_info, so that's at least one excuse.
 *
 * <b>Using Clang AST as a C++ meta model</b>
 *
 * If implemented properly, the C++ model should really just generate
 * Clang AST and use the clang framework to perform the code generation.
 * However, it is non-trivial to create such transformers able to make a
 * valid AST for all the use cases we have (say boost serialisation, etc).
 * So we took the easy approach which is to create what can be thought of
 * as a high-level AST model, that represents C++ meta model concepts in
 * in a very high-level form. This form is suitable for our formatters.
 *
 * In the future we should consider a Clang based C++ backend, but we should
 * not reuse any of this code as its too far apart. On the plus side we can
 * start working on it side-by-side such that we have both backends and only
 * switch to Clang when it has 100% feature coverage.
 *
 */
namespace cpp {
} }

#endif
