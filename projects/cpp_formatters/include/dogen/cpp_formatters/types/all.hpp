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
#include "dogen/cpp_formatters/types/class_declaration.hpp"
#include "dogen/cpp_formatters/types/class_implementation.hpp"
#include "dogen/cpp_formatters/types/domain_class_declaration.hpp"
#include "dogen/cpp_formatters/types/domain_class_implementation.hpp"
#include "dogen/cpp_formatters/types/domain_header.hpp"
#include "dogen/cpp_formatters/types/domain_implementation.hpp"
#include "dogen/cpp_formatters/types/doxygen_comments.hpp"
#include "dogen/cpp_formatters/types/enum_declaration.hpp"
#include "dogen/cpp_formatters/types/exception_declaration.hpp"
#include "dogen/cpp_formatters/types/facet_includer.hpp"
#include "dogen/cpp_formatters/types/factory.hpp"
#include "dogen/cpp_formatters/types/file_formatter.hpp"
#include "dogen/cpp_formatters/types/formatting_error.hpp"
#include "dogen/cpp_formatters/types/forward_declarations_header.hpp"
#include "dogen/cpp_formatters/types/generator_header.hpp"
#include "dogen/cpp_formatters/types/generator_implementation.hpp"
#include "dogen/cpp_formatters/types/hash_header.hpp"
#include "dogen/cpp_formatters/types/hash_implementation.hpp"
#include "dogen/cpp_formatters/types/header_guards.hpp"
#include "dogen/cpp_formatters/types/include_cmakelists.hpp"
#include "dogen/cpp_formatters/types/includes.hpp"
#include "dogen/cpp_formatters/types/indenter.hpp"
#include "dogen/cpp_formatters/types/inserter_implementation.hpp"
#include "dogen/cpp_formatters/types/io_header.hpp"
#include "dogen/cpp_formatters/types/io_implementation.hpp"
#include "dogen/cpp_formatters/types/key_class_declaration.hpp"
#include "dogen/cpp_formatters/types/key_class_implementation.hpp"
#include "dogen/cpp_formatters/types/licence.hpp"
#include "dogen/cpp_formatters/types/namespace_documentation.hpp"
#include "dogen/cpp_formatters/types/namespace_formatter.hpp"
#include "dogen/cpp_formatters/types/namespace_helper.hpp"
#include "dogen/cpp_formatters/types/null_formatter.hpp"
#include "dogen/cpp_formatters/types/odb_header.hpp"
#include "dogen/cpp_formatters/types/odb_options.hpp"
#include "dogen/cpp_formatters/types/production_failure.hpp"
#include "dogen/cpp_formatters/types/qname.hpp"
#include "dogen/cpp_formatters/types/registrar_header.hpp"
#include "dogen/cpp_formatters/types/registrar_implementation.hpp"
#include "dogen/cpp_formatters/types/serialization_header.hpp"
#include "dogen/cpp_formatters/types/serialization_implementation.hpp"
#include "dogen/cpp_formatters/types/src_cmakelists.hpp"
#include "dogen/cpp_formatters/types/utility.hpp"
#include "dogen/cpp_formatters/types/visitor.hpp"
