# `karmah`: Kubernetes Application Rendering MAnifest Helper

The program `karmah` is a simple but flexible tool to render manifests for kubernetes.

The purpose is to render the manifests for a specific application (`appname`) and a specific environment.

# Render Definitions


# Running `karmah`
It can be run with the following options:

```
karmah [ option | command | action | path ]...

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
  -a|--action <act>   add action to list of actions to perform
  -m|--message <msg>  set message to us with git commit
Commands:
  aliases       show all defined aliases
  forall        run actions for all paths
  install-kapp  install the tool kapp from carvel
Actions:
  compare       render manifests to --to <path> (default tmp/manifests) and then compare with --with path (default deployed/manifests)
  deploy        render to deployed/manifests and optionally deploy to kubernetes
  git-add       adds the changes to source and rendered manifests to git, for committing
  git-commit    commits the changes to source and rendered manifests to git
  git-diff      shows the changes to source and rendered manifests with git
  kapp-deploy   deploy the application with kapp
  kapp-diff     show what resources will be updated, including detailed diffs
  kapp-plan     show what resources will be updated
  kube-apply    apply rendered manifests with cluster (kubectl apply)
  kube-diff     compare rendered manifests with cluster (kubectl diff)
  kube-get      get current manifests from cluster to --to <path> (default) deployed/manifests
  render        render manifests to --to <path> (default tmp/manifests)
  update        update source files with expressions from --update
Paths:
  Each path defines an application definition, that will be sourced,
  This can either be a file, or a directory that contains exactly 1 file with a name '*.karmah'.
  When one or more --subdirs are specfied, these will be append to the path

Note:
  Options, commands, actions and paths can be mixed freely
  If multiple commands are given, only last command will be used
```

# Installation
The only requirement is to have a recent version of `bash` available.

Additionally the following tools are needed for some commands:
- `helm`: for rendering helm templates
- `yq`: is needed for splitting the output of `helm template` to individual files
- `git`: for the `pull` and `commit` commands
- `kubectl`: with a correct kubeconfig file for the `diff` and `apply`
- `kapp`: if this functionality is used

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
- `apps/<appname>/<env>/render-app-<appname>-<env>.karmah`: render-definitions for an application and environment
- `apps/<appname>/<env>/values-app-<appname>-<env>.yaml`:  helm values file for an environment of an application
- `apps/<appname>/common/values-<appname>.yaml`: helm values file for all environments of an application
- `helm/charts`: the helm-charts that can be referred to in the render definitions
- `helm/env-value-files/values-<env>.karmah`: values specific for this environment
- `tmp/manifests`: the location where the rendered manifests are stored
- `deployed/manifests`: the location to store rendered manifests that are actually are deployed
- `config.d`: specific configuration, e.g. kubenertes details or aliasses
