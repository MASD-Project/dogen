// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#include <odb/pre.hxx>

#include "dogen/test_models/northwind/odb/order_details_key-odb-oracle.hxx"

#include <cassert>
#include <cstring>  // std::memcpy

#include <odb/schema-catalog-impl.hxx>

#include <odb/oracle/traits.hxx>
#include <odb/oracle/database.hxx>
#include <odb/oracle/transaction.hxx>
#include <odb/oracle/connection.hxx>
#include <odb/oracle/statement.hxx>
#include <odb/oracle/statement-cache.hxx>
#include <odb/oracle/container-statements.hxx>
#include <odb/oracle/exceptions.hxx>

namespace odb
{
  // order_details_key
  //

  void access::composite_value_traits< ::dogen::test_models::northwind::order_details_key, id_oracle >::
  bind (oracle::bind* b,
        image_type& i,
        oracle::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (b);
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace oracle;

    std::size_t n (0);
    ODB_POTENTIALLY_UNUSED (n);

    // product_id_
    //
    composite_value_traits< ::dogen::test_models::northwind::product_id, id_oracle >::bind (
      b + n, i.product_id_value, sk);
    n += 1UL;

    // order_id_
    //
    composite_value_traits< ::dogen::test_models::northwind::order_id, id_oracle >::bind (
      b + n, i.order_id_value, sk);
    n += 1UL;
  }

  void access::composite_value_traits< ::dogen::test_models::northwind::order_details_key, id_oracle >::
  init (image_type& i,
        const value_type& o,
        oracle::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace oracle;

    // product_id_
    //
    {
      ::dogen::test_models::northwind::product_id const& v =
        o.product_id ();

      composite_value_traits< ::dogen::test_models::northwind::product_id, id_oracle >::init (
        i.product_id_value,
        v,
        sk);
    }

    // order_id_
    //
    {
      ::dogen::test_models::northwind::order_id const& v =
        o.order_id ();

      composite_value_traits< ::dogen::test_models::northwind::order_id, id_oracle >::init (
        i.order_id_value,
        v,
        sk);
    }
  }

  void access::composite_value_traits< ::dogen::test_models::northwind::order_details_key, id_oracle >::
  init (value_type& o,
        const image_type&  i,
        database* db)
  {
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (db);

    // product_id_
    //
    {
      ::dogen::test_models::northwind::product_id& v =
        o.product_id ();

      composite_value_traits< ::dogen::test_models::northwind::product_id, id_oracle >::init (
        v,
        i.product_id_value,
        db);
    }

    // order_id_
    //
    {
      ::dogen::test_models::northwind::order_id& v =
        o.order_id ();

      composite_value_traits< ::dogen::test_models::northwind::order_id, id_oracle >::init (
        v,
        i.order_id_value,
        db);
    }
  }
}

#include <odb/post.hxx>
