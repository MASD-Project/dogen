// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#ifndef DOGEN_TEST_MODELS_NORTHWIND_ODB_REPOSITORY_ODB_ORACLE_HXX
#define DOGEN_TEST_MODELS_NORTHWIND_ODB_REPOSITORY_ODB_ORACLE_HXX

// Begin prologue.
//
#include <odb/boost/version.hxx>
#if ODB_BOOST_VERSION != 2040000 // 2.4.0
#  error ODB and C++ compilers see different libodb-boost interface versions
#endif
#include <boost/shared_ptr.hpp>
#include <odb/boost/smart-ptr/pointer-traits.hxx>
#include <odb/boost/smart-ptr/wrapper-traits.hxx>
#include <odb/boost/optional/wrapper-traits.hxx>
#include <odb/boost/unordered/container-traits.hxx>
#include <odb/boost/date-time/oracle/gregorian-traits.hxx>
#include <odb/boost/date-time/oracle/posix-time-traits.hxx>
#include <odb/boost/multi-index/container-traits.hxx>
#include <odb/boost/uuid/oracle/uuid-traits.hxx>
//
// End prologue.

#include <odb/version.hxx>

#if (ODB_VERSION != 20400UL)
#error ODB runtime version mismatch
#endif

#include <odb/pre.hxx>

#include "dogen/test_models/northwind/types/repository.hpp"

#include "dogen/test_models/northwind/odb/categories-odb-oracle.hxx"
#include "dogen/test_models/northwind/odb/category_id-odb-oracle.hxx"
#include "dogen/test_models/northwind/odb/customer_customer_demo-odb-oracle.hxx"
#include "dogen/test_models/northwind/odb/customer_customer_demo_key-odb-oracle.hxx"
#include "dogen/test_models/northwind/odb/customer_demographics-odb-oracle.hxx"
#include "dogen/test_models/northwind/odb/customer_id-odb-oracle.hxx"
#include "dogen/test_models/northwind/odb/customer_type_id-odb-oracle.hxx"
#include "dogen/test_models/northwind/odb/customers-odb-oracle.hxx"
#include "dogen/test_models/northwind/odb/employee_id-odb-oracle.hxx"
#include "dogen/test_models/northwind/odb/employee_territories-odb-oracle.hxx"
#include "dogen/test_models/northwind/odb/employee_territories_key-odb-oracle.hxx"
#include "dogen/test_models/northwind/odb/employees-odb-oracle.hxx"
#include "dogen/test_models/northwind/odb/order_details-odb-oracle.hxx"
#include "dogen/test_models/northwind/odb/order_details_key-odb-oracle.hxx"
#include "dogen/test_models/northwind/odb/order_id-odb-oracle.hxx"
#include "dogen/test_models/northwind/odb/product_id-odb-oracle.hxx"
#include "dogen/test_models/northwind/odb/products-odb-oracle.hxx"
#include "dogen/test_models/northwind/odb/region-odb-oracle.hxx"
#include "dogen/test_models/northwind/odb/region_id-odb-oracle.hxx"
#include "dogen/test_models/northwind/odb/shipper_id-odb-oracle.hxx"
#include "dogen/test_models/northwind/odb/shippers-odb-oracle.hxx"
#include "dogen/test_models/northwind/odb/supplier-odb-oracle.hxx"
#include "dogen/test_models/northwind/odb/supplier_id-odb-oracle.hxx"
#include "dogen/test_models/northwind/odb/territory-odb-oracle.hxx"
#include "dogen/test_models/northwind/odb/territory_id-odb-oracle.hxx"

#include "dogen/test_models/northwind/odb/repository-odb.hxx"

#include <odb/details/buffer.hxx>

#include <odb/oracle/version.hxx>
#include <odb/oracle/forward.hxx>
#include <odb/oracle/binding.hxx>
#include <odb/oracle/oracle-types.hxx>
#include <odb/oracle/query.hxx>

namespace odb
{
}

#include "dogen/test_models/northwind/odb/repository-odb-oracle.ixx"

#include <odb/post.hxx>

#endif // DOGEN_TEST_MODELS_NORTHWIND_ODB_REPOSITORY_ODB_ORACLE_HXX
