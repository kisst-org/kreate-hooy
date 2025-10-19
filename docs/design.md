# kreate - create files with simple templates and no tools

This document describes the original design philosophy for kreate.
This needs to be updated

# Why templates
The advantage of the template approach is to provide and maintain uniformity when you have to create and maintain many similar files.
The first `kreate.sh` scripts were created for a project where about 15 different applications needed to deployed in different kubernetes clusters (development, test, production, etc).
Each application had several files (kustomization, deployment, service, ingress, ...) that were very similar, with slight differences.
For each environment, for each application some more files were needed (kustomization, ConfigMaps, patches, property files, ...) some unique, but some nearly identical.
In total it was expected to have over 200 different files.

Manually copying and pasting from template files might be nice for initial setup.
However, often some changes need to be made, and then manually editing all relevant files would become a maintenance nightmare.
It would also become very difficult to provide consistency.
Hence, whenever possible, similar files should be generated from a template.

# Philosophy
- **Don't require any tools**: All that is needed is bash.
  This means that just added the `kreate.sh` scripts to you version control, would allow you to kreate the files on any (Linux or otherwise) system that has bash installed.
   The `kreate` tool provided in the `bin` directory is nice for extra features, but not needed
   It is of course possible to use other tools from the bash script if needed, like grep, sed, etc, but this is not needed.
   You could use other tools like `python` or Jinja templating, but only do so if really needed.
 - **Run without needing any environment variables**: The behaviour of the scripts can be enhanced or influenced with some variables, but it should run fine without.
   The `kreate` tool helps setting these for you.
 - **Just running `kreate.sh` should work**: This is mainly a result of the above rules.
 - **Only kreate files that make sense**: This means files that are very similar.
   For unique files it makes little sense to kreate these.
   Such files can nicely co-exist next to kreated files.


# Using the kreate tool
To support working with kreate.sh templates a simple tool, called `kreate`, is provided.
This tool basically just calls your own `kreate.sh` script(s), but provides some extra features:
- providing helpful output what is kreated on different verbosity levels (normal, `--verbose`, `--debug` or `--quiet`)
- viewing which files would be changed with `--status`
- viewing the difference if new files would be kreated and existing files with `--diff`
- building output based on the created files using `kustomize`
- immediately applying the kustomize output with `kubectl apply`

The current output of `kreate --help` is:
```
Usage: kreate [options] <dir>...

The purpose of kreate is calling kreate.sh to create files
and then optionally execute a command like git or kustomize
Options can be:
    -h|--help      display this help and exit
    -v|--verbose   verbose mode.
    -q|--quiet     quiet mode.
    -i|--init-file use another init file
Only one of the following commands/options should be specified:
    -s|--status   kreate temporary files, show if files are +/new or M/modified
    -d|--diff     kreate temporary files, do: diff per file
    -b|--build    kreate files, do: kustomize build
    -a|--apply    kreate files, do: kustomize build | kubectl apply -f -
If none of the above commands are given, the files are just kreated
```
Note that `kreate` is still very much under development, and the features and command line options might change.
Some possible changes are
- To use a command like `diff` instead of an option like `--diff`. This was working but the problem was that the default behaviour was just to kreate files, and no command was needed. This needs further design.
- Add extra options, using a init system, and make the two kustomize options just an extension module
- Add anOptionally removing the kreated files after they has been used (planned feature)
