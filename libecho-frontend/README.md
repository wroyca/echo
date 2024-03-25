# libecho-frontend - A C++ library

The `libecho-frontend` C++ library provides <SUMMARY-OF-FUNCTIONALITY>.


## Usage

To start using `libecho-frontend` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: libecho-frontend ^<VERSION>
```

Then import the library in your `buildfile`:

```
import libs = libecho-frontend%lib{<TARGET>}
```


## Importable targets

This package provides the following importable targets:

```
lib{<TARGET>}
```

<DESCRIPTION-OF-IMPORTABLE-TARGETS>


## Configuration variables

This package provides the following configuration variables:

```
[bool] config.libecho_frontend.<VARIABLE> ?= false
```

<DESCRIPTION-OF-CONFIG-VARIABLES>
