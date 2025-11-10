# karmah - create files with simple templates and no tools

This document describes the original design philosophy for karmah.
This needs to be updated

# Why templates
The advantage of the template approach is to provide and maintain uniformity when you have to create and maintain many similar files.
The first `karmah.sh` scripts were created for a project where about 15 different applications needed to deployed in different kubernetes clusters (development, test, production, etc).
Each application had several files (kustomization, deployment, service, ingress, ...) that were very similar, with slight differences.
For each environment, for each application some more files were needed (kustomization, ConfigMaps, patches, property files, ...) some unique, but some nearly identical.
In total it was expected to have over 200 different files.

Manually copying and pasting from template files might be nice for initial setup.
However, often some changes need to be made, and then manually editing all relevant files would become a maintenance nightmare.
It would also become very difficult to provide consistency.
Hence, whenever possible, similar files should be generated from a template.

# Philosophy
- **Don't require any tools**: All that is needed is bash.
  This means that just added the `karmah.sh` scripts to you version control, would allow you to karmah the files on any (Linux or otherwise) system that has bash installed.
   The `karmah` tool provided in the `bin` directory is nice for extra features, but not needed
   It is of course possible to use other tools from the bash script if needed, like grep, sed, etc, but this is not needed.
   You could use other tools like `python` or Jinja templating, but only do so if really needed.
 - **Run without needing any environment variables**: The behaviour of the scripts can be enhanced or influenced with some variables, but it should run fine without.
   The `karmah` tool helps setting these for you.
 - **Just running `karmah.sh` should work**: This is mainly a result of the above rules.
 - **Only karmah files that make sense**: This means files that are very similar.
   For unique files it makes little sense to karmah these.
   Such files can nicely co-exist next to karmahd files.


# Using the karmah tool
To support working with karmah.sh templates a simple tool, called `karmah`, is provided.
This tool basically just calls your own `karmah.sh` script(s), but provides some extra features:
- providing helpful output what is karmahd on different verbosity levels (normal, `--verbose`, `--debug` or `--quiet`)
- viewing which files would be changed with `--status`
- viewing the difference if new files would be karmahd and existing files with `--diff`
- building output based on the created files using `kustomize`
- immediately applying the kustomize output with `kubectl apply`

The current output of `karmah --help` is:
```
Usage: karmah [options] <dir>...

The purpose of karmah is calling karmah.sh to create files
and then optionally execute a command like git or kustomize
Options can be:
    -h|--help      display this help and exit
    -v|--verbose   verbose mode.
    -q|--quiet     quiet mode.
    -i|--init-file use another init file
Only one of the following commands/options should be specified:
    -s|--status   karmah temporary files, show if files are +/new or M/modified
    -d|--diff     karmah temporary files, do: diff per file
    -b|--build    karmah files, do: kustomize build
    -a|--apply    karmah files, do: kustomize build | kubectl apply -f -
If none of the above commands are given, the files are just karmahd
```
Note that `karmah` is still very much under development, and the features and command line options might change.
Some possible changes are
- To use a command like `diff` instead of an option like `--diff`. This was working but the problem was that the default behaviour was just to karmah files, and no command was needed. This needs further design.
- Add extra options, using a init system, and make the two kustomize options just an extension module
- Add anOptionally removing the karmahd files after they has been used (planned feature)
