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
 * @section cpp_0 Objective
 *
 * CPP aims to model the types available in the C++ type system as faithfuly
 * as possible. However, for historical reasons, there are a number of types
 * that do not follow this approach such as @e visitor, @e registrar, etc. Over
 * time these types will be reimplemented in terms of the basic building blocks
 * such as class, etc.
 *
 * @section cpp_1 Info postfix
 *
 * The types in the C++ meta-model should not have any prefixes or post-fixes
 * since they naturally belong to the CPP model. However, because names like
 * @e class and @e namespace clash with keywords, and to maintain consistency -
 * perhaps foolishly - it was decided to use the postfix @e info on all types
 * which are part of the meta-model. Info was chosen very randomly, but it is
 * used by @e type_info, so that's at least one excuse.
 *
 * @section cpp_2 Using Clang AST as a C++ meta model
 *
 * If implemented properly, dogen should really just generate a C++ AST via
 * Clang and use the LLVM framework to perform the code generation. However,
 * it is non-trivial to create transformers able to make a valid AST for
 * all the use cases we have (say boost serialisation, etc). So we took the
 * easy way out which is to create what can be thought of as a high-level AST
 * model and hard-code all of the source in the @e cpp_transformers model.
 *
 * In the future we should consider a Clang based C++ backend. We will probably
 * not reuse any of the code in the various C++ models as its too far apart
 * from the Clang approach. On the plus side we can start working on it
 * side-by-side such that we have both backends and only switch to Clang when
 * it has 100% feature coverage.
 *
 */
namespace cpp {
} }

#endif
