# kreate-hooy: Kubernetes Rendering Environment Applications with Template (with Helm Or Other Yaml-tools)

The program `kreate` is a simple but flexible tool to render manifests for kubernetes.

The working is to render the manifest for a specific application (`appname`) and a specific environment.

# Environments
Some examples of environments are:
- `lab`: meant for infra structure testing
- `tst`: meant for testing applications
- `stg`: staging
- `prd`: production
- `all`: all environments of an application
In general it is recommended to use short (e.g. 3 letter) names for environments.

# Render Definitions


# Running `kreate`
It can be run with the following options:

```
kreate [ option | command/alias | render-def ]...

Options:
  -h|--help     show this help
  -v|--verbose  give more output
  -q|--quiet    no output
  -e|--env=<e>  add environment <e> to render
Commands
  help          show_help
  diff          run 'kubectl diff' with the rendered manifests
  apply         run 'kubectl apply' with the rendered manifests
  compare       compare to same appname in other directory
  update:<expr> for helm update the final values with yq expression
  commit        TODO: run 'git commit' (pull is implied)
  pull          TODO: run 'git pull' before starting to render, to avoid merge conflicts

Render Definitions:
Can either be a file, that will be sourced, or a directory that contains exactly 1 file with a name 'render*.def'.

Aliases:
  User defined
```

# Installation
The only requirement is to have a recent version of `bash` available.

Additionally the following tools are needed for some commands:
- `helm`: for rendering helm templates
- `yq`: is needed for splitting the output of `helm template` to individual files
- `git`: for the `pull` and `commit` commands
- `kubectl`: with a correct kubeconfig file for the `diff` and `apply`

Installation can be done by copying the `kreate` script to the correct location.
```
curl -OL https://raw.githubusercontent.com/kisst-org/kreate-hooy/refs/heads/main/bin/kreate
chmod 755 kreate
```
No further file need to be downloaded

# Directory structure
The script can be placed in the directory with all the manifests definitions.

The following directory structure is recommended when using `helm` as renderer:
- `kreate`: the script itself
- `apps/<appname>/render-app-<appname>.def`: render-definitions for an application and environments
- `apps/<appname>/values-app-<appname>.yaml`:  helm values file for all environments of an application (included before the environment specifc values)
- `apps/<appname>/values-<appname>-<env>.yaml`: helm values file for a specific environment of an application
- Optionally `apps/<appname>/render-appenv-<appname>-<env>.def`: render-definition for a specific environment of an application. Only needed if this
- `helm/charts`: the helm-charts that can be referred to in the render definitions
- `helm/env-value-files/values-<env>.def`: values specific for this environment
- `tmp/manifests`: the location where the rendered manifests are stored
- `deployed/manifests`: the location to store rendered manifests that are actually are dpeloyed
