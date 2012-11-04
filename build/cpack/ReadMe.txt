Dogen is a code generator designed to target domain models.

Dogen is required for Kitanda because we use a intensively domain
driven approach to software engineering, resulting in a very large
number of domain specific languages (DSLs). Dogen was created to make
the modeling process simpler: the user creates a domain model using a
UML tool and Dogen uses it to generate its source code
representation. The generated code contains most of the services
required from a typical C++ domain object such as serialisation,
hashing, streaming and so on.
