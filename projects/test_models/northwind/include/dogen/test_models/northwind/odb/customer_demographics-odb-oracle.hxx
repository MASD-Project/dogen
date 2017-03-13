// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#ifndef DOGEN_TEST_MODELS_NORTHWIND_ODB_CUSTOMER_DEMOGRAPHICS_ODB_ORACLE_HXX
#define DOGEN_TEST_MODELS_NORTHWIND_ODB_CUSTOMER_DEMOGRAPHICS_ODB_ORACLE_HXX

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

#include "dogen/test_models/northwind/types/customer_demographics.hpp"

#include "dogen/test_models/northwind/odb/customer_type_id-odb-oracle.hxx"

#include "dogen/test_models/northwind/odb/customer_demographics-odb.hxx"

#include <odb/details/buffer.hxx>

#include <odb/oracle/version.hxx>
#include <odb/oracle/forward.hxx>
#include <odb/oracle/binding.hxx>
#include <odb/oracle/oracle-types.hxx>
#include <odb/oracle/query.hxx>

namespace odb
{
  // customer_demographics
  //
  template <typename A>
  struct query_columns< ::dogen::test_models::northwind::customer_demographics, id_oracle, A >
  {
    // customer_type_id
    //
    struct customer_type_id_class_
    {
      customer_type_id_class_ ()
      {
      }

      // value
      //
      typedef
      oracle::query_column<
        oracle::value_traits<
          ::std::string,
          oracle::id_string >::query_type,
        oracle::id_string >
      value_type_;

      static const value_type_ value;
    };

    static const customer_type_id_class_ customer_type_id;

    // customer_description
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    customer_description_type_;

    static const customer_description_type_ customer_description;
  };

  template <typename A>
  const typename query_columns< ::dogen::test_models::northwind::customer_demographics, id_oracle, A >::customer_type_id_class_::value_type_
  query_columns< ::dogen::test_models::northwind::customer_demographics, id_oracle, A >::customer_type_id_class_::
  value (A::table_name, "\"CUSTOMER_TYPE_ID\"", 0, 512);

  template <typename A>
  const typename query_columns< ::dogen::test_models::northwind::customer_demographics, id_oracle, A >::customer_type_id_class_
  query_columns< ::dogen::test_models::northwind::customer_demographics, id_oracle, A >::customer_type_id;

  template <typename A>
  const typename query_columns< ::dogen::test_models::northwind::customer_demographics, id_oracle, A >::customer_description_type_
  query_columns< ::dogen::test_models::northwind::customer_demographics, id_oracle, A >::
  customer_description (A::table_name, "\"CUSTOMER_DESCRIPTION\"", 0, 512);

  template <typename A>
  struct pointer_query_columns< ::dogen::test_models::northwind::customer_demographics, id_oracle, A >:
    query_columns< ::dogen::test_models::northwind::customer_demographics, id_oracle, A >
  {
  };

  template <>
  class access::object_traits_impl< ::dogen::test_models::northwind::customer_demographics, id_oracle >:
    public access::object_traits< ::dogen::test_models::northwind::customer_demographics >
  {
    public:
    static const std::size_t batch = 1UL;

    struct id_image_type
    {
      composite_value_traits< ::dogen::test_models::northwind::customer_type_id, id_oracle >::image_type id_value;

      std::size_t version;
    };

    struct image_type
    {
      // customer_type_id_
      //
      composite_value_traits< ::dogen::test_models::northwind::customer_type_id, id_oracle >::image_type customer_type_id_value;

      // customer_description_
      //
      char customer_description_value[512];
      ub2 customer_description_size;
      sb2 customer_description_indicator;

      std::size_t version;

      oracle::change_callback change_callback_;

      oracle::change_callback*
      change_callback ()
      {
        return &change_callback_;
      }
    };

    struct extra_statement_cache_type;

    using object_traits<object_type>::id;

    static id_type
    id (const image_type&);

    static void
    bind (oracle::bind*,
          image_type&,
          oracle::statement_kind);

    static void
    bind (oracle::bind*, id_image_type&);

    static void
    init (image_type&,
          const object_type&,
          oracle::statement_kind);

    static void
    init (object_type&,
          const image_type&,
          database*);

    static void
    init (id_image_type&, const id_type&);

    typedef oracle::object_statements<object_type> statements_type;

    typedef oracle::query_base query_base_type;

    static const std::size_t column_count = 2UL;
    static const std::size_t id_column_count = 1UL;
    static const std::size_t inverse_column_count = 0UL;
    static const std::size_t readonly_column_count = 0UL;
    static const std::size_t managed_optimistic_column_count = 0UL;

    static const std::size_t separate_load_column_count = 0UL;
    static const std::size_t separate_update_column_count = 0UL;

    static const bool versioned = false;

    static const char persist_statement[];
    static const char find_statement[];
    static const char update_statement[];
    static const char erase_statement[];
    static const char query_statement[];
    static const char erase_query_statement[];

    static const char table_name[];

    static void
    persist (database&, const object_type&);

    static pointer_type
    find (database&, const id_type&);

    static bool
    find (database&, const id_type&, object_type&);

    static bool
    reload (database&, object_type&);

    static void
    update (database&, const object_type&);

    static void
    erase (database&, const id_type&);

    static void
    erase (database&, const object_type&);

    static result<object_type>
    query (database&, const query_base_type&);

    static unsigned long long
    erase_query (database&, const query_base_type&);

    public:
    static bool
    find_ (statements_type&,
           const id_type*);

    static void
    load_ (statements_type&,
           object_type&,
           bool reload);
  };

  // customer_demographics
  //
}

#include "dogen/test_models/northwind/odb/customer_demographics-odb-oracle.ixx"

#include <odb/post.hxx>

#endif // DOGEN_TEST_MODELS_NORTHWIND_ODB_CUSTOMER_DEMOGRAPHICS_ODB_ORACLE_HXX
