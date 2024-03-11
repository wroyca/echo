# echo - An executable

The `echo` executable is a <SUMMARY-OF-FUNCTIONALITY>.


## Usage

To start using this executable in your project, add the following build-time
`depends` value to your `manifest`, adjusting the version constraint as
appropriate:

```
depends: * echo ^<VERSION>
```

Then import the executable in your `buildfile`:

```
import <TARGET> = echo%exe{<TARGET>}
```

Note that the `<TARGET>` executable provides `build2` metadata.


## Importable targets

This package provides the following importable targets:

```
exe{<TARGET>}
```

<DESCRIPTION-OF-IMPORTABLE-TARGETS>


## Configuration variables

This package provides the following configuration variables:

```
[bool] config.echo.<VARIABLE> ?= false
```

<DESCRIPTION-OF-CONFIG-VARIABLES>
