# `karmah`: Kubernetes Application Rendering MAnifest Helper

The program `karmah` is a simple but flexible tool to render manifests for kubernetes.

The purpose is to render the manifests for a specific application (`appname`) and a specific environment.

# Environments
Some examples of environments are:
- `lab`: meant for infra structure testing
- `tst`: meant for testing applications
- `stg`: staging
- `prd`: production
- `all`: all environments of an application
In general it is recommended to use short (e.g. 3 letter) names for environments.

# Render Definitions


# Running `karmah`
It can be run with the following options:

```
karmah [ option | command | path ]...

Options:
  -h|--help|help      show this help and exit
  -v|--verbose        give more output
  -s|--show-cmd       show the commands being executed
  -q|--quiet          no output
  -n|--dry-run        do not execute the actual commands
  -s|--subdir <dir>   add subdir to list of subdirs (can be comma separated list)
  -t|--to <path>      other path to render to (default is tmp/manifests)
  -w|--with <path>    used for comparison between two manifest trees
  -u|--update <expr>  update source files before rendering
Commands:
  aliases       show all defined aliases
  forall        run actions for all paths
  install-kapp  install the tool kapp from carvel
Paths:
  Each path defines an application definition, that will be sourced,
  This can either be a file, or a directory that contains exactly 1 file with a name '*.def'.
  When one or more --subdirs are specfied, these will be append to the path

Note:
  Options, commands and paths can be mixed freely
  If multiple commands are given, only last command will be used
```

# Installation
The only requirement is to have a recent version of `bash` available.

Additionally the following tools are needed for some commands:
- `helm`: for rendering helm templates
- `yq`: is needed for splitting the output of `helm template` to individual files
- `git`: for the `pull` and `commit` commands
- `kubectl`: with a correct kubeconfig file for the `diff` and `apply`

Installation can be done by copying the `karmah` script to the correct location.
```
curl -OL https://raw.githubusercontent.com/kisst-org/karmah/refs/heads/main/karmah
chmod 755 karmah
```
No further file need to be downloaded

# Directory structure
The script can be placed in the directory with all the manifests definitions.

The following directory structure is recommended when using `helm` as renderer:
- `karmah`: the script itself
- `apps/<appname>/render-app-<appname>.def`: render-definitions for an application and environments
- `apps/<appname>/values-app-<appname>.yaml`:  helm values file for all environments of an application (included before the environment specifc values)
- `apps/<appname>/values-<appname>-<env>.yaml`: helm values file for a specific environment of an application
- Optionally `apps/<appname>/render-appenv-<appname>-<env>.def`: render-definition for a specific environment of an application. Only needed if this
- `helm/charts`: the helm-charts that can be referred to in the render definitions
- `helm/env-value-files/values-<env>.def`: values specific for this environment
- `tmp/manifests`: the location where the rendered manifests are stored
- `deployed/manifests`: the location to store rendered manifests that are actually are dpeloyed
